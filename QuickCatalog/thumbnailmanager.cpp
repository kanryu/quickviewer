#include <QtGui>
#include <QtSql>
#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>

#ifdef Q_OS_WIN
#include <Shlwapi.h>
#endif

#include "thumbnailmanager.h"
#include "qc_init.h"

QList<QByteArray> ThumbnailManager::st_supportedImageFormats;
QStringList ThumbnailManager::st_jpegpegImageFormats;
QStringList ThumbnailManager::st_heavyImageFormats;

bool ThumbnailManager::isImageFile(QString path)
{
    if(st_supportedImageFormats.size() == 0) {
        st_jpegpegImageFormats << "jpg" << "jpeg";
        st_heavyImageFormats << "crw" << "cr2" << "arw" << "nef" << "raf" << "dng"; // heavy images
        st_supportedImageFormats = QImageReader::supportedImageFormats();
    }
    QString lower = path.toLower();
    foreach(const QString& e, st_supportedImageFormats) {
        if(lower.endsWith(e))
            return true;
    }
    return false;
}

bool ThumbnailManager::isArchiveFile(QString path)
{
    QStringList exts = {".zip", ".7z", ".rar"};
    QString lower = path.toLower();
    foreach(const QString& e, exts) {
        if(lower.endsWith(e))
            return true;
    }
    return false;
}

bool ThumbnailManager::isJpegImageFile(QString path)
{
    QString lower = path.toLower();
    foreach(const QString& e, st_jpegpegImageFormats) {
        if(lower.endsWith(e))
            return true;
    }
    return false;
}

bool ThumbnailManager::isHeavyImageFile(QString path)
{
    QString lower = path.toLower();
    foreach(const QString& e, st_heavyImageFormats) {
        if(lower.endsWith(e))
            return true;
    }
    return false;
}

void ThumbnailManager::sortFiles(QStringList &filenames)
{
    qSort(filenames.begin(), filenames.end(), caseInsensitiveLessThan);
}


QString ThumbnailManager::DateTimeToIsoString(QDateTime datetime)
{
    return datetime.toString(ISO_DATETIMEFMT);
}
QString ThumbnailManager::currentDateTimeAsString()
{
    QDateTime current = QDateTime::currentDateTime();
    return DateTimeToIsoString(current);
}

#ifdef Q_OS_WIN
// Windows Filename sorting is not usual caseInsensitive, so call Win32Api
// to see https://msdn.microsoft.com/ja-jp/library/windows/desktop/bb759947(v=vs.85).aspx
bool ThumbnailManager::caseInsensitiveLessThan(const QString &s1, const QString &s2)
{
    std::wstring ss1(s1.toStdWString());
    std::wstring ss2(s2.toStdWString());
    return ::StrCmpLogicalW(ss1.c_str(), ss2.c_str()) < 0;
}
#else
bool ThumbnailManager::caseInsensitiveLessThan(const QString &s1, const QString &s2)
{
    return s1.toLower() < s2.toLower();
}
#endif

ThumbnailManager::ThumbnailManager(QObject* parent, QString dbpath)
    : QObject(parent)
    , m_db(QSqlDatabase::addDatabase("QSQLITE"))
    , m_transaction(false)
    , m_catalogWatcher(this)
{

    m_db.setDatabaseName(dbpath);
    if (!m_db.open())
    {
       qDebug() << "Error: connection with database fail";
    }
    else
    {
       qDebug() << "Database: connection ok";
    }
}

#define DEFAULT_FILES_COUNT 30

int ThumbnailManager::createSubVolumes(QString dirpath, int catalog_id, int parent_id)
{
    QDir dir(dirpath);
    if(!dir.exists())
        return -1;
    int volume_id = createVolumeInternal(dirpath, catalog_id, parent_id);
    if(volume_id < 0) return -1;

    QSqlQuery t_volumeorders(m_db);
    t_volumeorders.prepare("INSERT INTO t_volumeorders (id,parent_id,volumename_asc)"
                      " VALUES (:id,:parent_id,:volumename_asc)");
    QStringList subdirs = dir.entryList(QDir::Dirs|QDir::NoDotAndDotDot, QDir::Unsorted);
    sortFiles(subdirs);
    if(m_catalogWatcher.isStarted() && subdirs.size()>0) {
        m_catalogWorkMax += subdirs.size()*DEFAULT_FILES_COUNT;
        emit m_catalogWatcher.progressRangeChanged(0, m_catalogWorkMax);
    }
    int volumeame_asc = 0;
    foreach(QString sub, subdirs) {
        QString subpath = dir.filePath(sub);
        if(m_catalogWatcher.isCanceled())
            break;
        int sub_id = createSubVolumes(subpath, catalog_id, volume_id);
        if(sub_id < 0)
            continue;
        t_volumeorders.bindValue(":id", sub_id);
        t_volumeorders.bindValue(":parent_id", volume_id);
        t_volumeorders.bindValue(":volumename_asc", volumeame_asc++);
        if(!execInsertQuery(t_volumeorders, "t_volumeorders")) return -1;

    }
    QStringList files = dir.entryList(QDir::Files, QDir::Unsorted);
    int filecount = 0;
    if(files.size() > 0) {
        filecount = createVolumeContent(dirpath, volume_id);
    }
    m_catalogWorkMax = m_catalogWorkMax + filecount - DEFAULT_FILES_COUNT;
    emit m_catalogWatcher.progressRangeChanged(0, m_catalogWorkMax);

    return volume_id;
}

int ThumbnailManager::createVolumeInternal(QString dirpath, int catalog_id, int parent_id)
{
    QFileInfo info(dirpath);
    qDebug() << "volume: " << info.fileName();
    QSqlQuery t_volumes(m_db);
    t_volumes.prepare("INSERT INTO t_volumes (realname, path, catalog_id, parent_id) VALUES (:realname,:path,:catalog_id,:parent_id)");
    t_volumes.bindValue(":realname", info.fileName());
    t_volumes.bindValue(":path", QDir::toNativeSeparators(dirpath));
    t_volumes.bindValue(":catalog_id", catalog_id);
    t_volumes.bindValue(":parent_id", parent_id);
    if(!execInsertQuery(t_volumes, "t_volumes")) return -1;

    int volume_id = t_volumes.lastInsertId().toInt();
    return volume_id;
}


int ThumbnailManager::createVolumeContent(QString dirpath, int volume_id)
{
    QDir dir(dirpath);
    if(!dir.exists())
        return -1;
    forceTransaction();

    QSqlQuery t_files(m_db);
    t_files.prepare("INSERT INTO t_files (volume_id,name,size,width,height,thumb_id,created_at,updated_at,alternated)"
                      " VALUES (:volume_id,:name,:size,:width,:height,:thumb_id,:created_at,:updated_at,:alternated)");
    QSqlQuery t_fileorders(m_db);
    t_fileorders.prepare("INSERT INTO t_fileorders (id,volume_id,filename_asc)"
                      " VALUES (:id,:volume_id,:filename_asc)");
    QSqlQuery t_thumbs(m_db);
    t_thumbs.prepare("INSERT INTO t_thumbnails (width,height,thumbnail,created_at)"
                       " VALUES (:width,:height,:thumbnail,:created_at)");
    QStringList files = dir.entryList(QDir::Files, QDir::Unsorted);
    sortFiles(files);
    bool bFrontPage = true;
    int filename_asc = 0;
    for(int i = 0; i < files.size(); i++) {
//    foreach(QString filename, files) {
        if(m_catalogWatcher.isStarted()) {
//            int progressValue = m_catalogWatcher.progressValue();
            emit m_catalogWatcher.progressValueChanged(m_catalogWorkProgress++);
        }
        if(m_catalogWatcher.isCanceled())
            break;
        QString filename = files[i];
        qDebug() << "  file: " << filename;
        if(!isImageFile(filename))
            continue;
        QString filepath = dir.filePath(filename);
        QImage img(filepath);
        if(!img.width())
            continue;

        QImage thumb = img.scaledToWidth(2*THUMB_WIDTH, Qt::FastTransformation);
        thumb = thumb.scaledToWidth(THUMB_WIDTH, Qt::SmoothTransformation);
        QBuffer thumbdat;
        thumbdat.open(QBuffer::ReadWrite);
        if(!thumb.save(&thumbdat, "JPEG", 90)) {
            qDebug() << "thumbnail.save() failed: " << filename;
            return -1;
        }
        t_thumbs.bindValue(":width", thumb.width());
        t_thumbs.bindValue(":height", thumb.height());
        t_thumbs.bindValue(":thumbnail", thumbdat.buffer());
        t_thumbs.bindValue(":created_at", currentDateTimeAsString());
        if(!execInsertQuery(t_thumbs, "t_thumbs")) return -1;

        QBuffer alternated;
        if(isHeavyImageFile(filename) || img.width() > MAX_WIDTH || img.height() > MAX_HEIGHT) {
            QDesktopWidget* desktop = QApplication::desktop();
            QRect rect = desktop->screenGeometry();
//            qDebug() << rect;
            QImage alter = img.scaled(rect.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            alternated.open(QBuffer::ReadWrite);
            if(!alter.save(&alternated, "JPEG", 90)) {
                qDebug() << "alternative.save() failed: " << filename;
                return -1;
            }
        }
        QFileInfo info(filepath);
        t_files.bindValue(":volume_id", volume_id);
        t_files.bindValue(":name", filename);
        t_files.bindValue(":size", info.size());
        t_files.bindValue(":width", img.width());
        t_files.bindValue(":height", img.height());
        t_files.bindValue(":thumb_id", t_thumbs.lastInsertId());
        t_files.bindValue(":created_at", info.created());
        t_files.bindValue(":updated_at", info.lastModified());
        t_files.bindValue(":alternated", alternated.size()==0 ? nullptr : alternated.buffer());
        if(!execInsertQuery(t_files, "t_files")) return -1;

        t_fileorders.bindValue(":volume_id", volume_id);
        t_fileorders.bindValue(":id", t_files.lastInsertId());
        t_fileorders.bindValue(":filename_asc", filename_asc++);
        if(!execInsertQuery(t_fileorders, "t_fileorders")) return -1;

        if(bFrontPage) {
            QSqlQuery t_volumes(m_db);
            t_volumes.prepare("UPDATE t_volumes SET frontpage_id=:frontpage_id, thumb_id=:thumb_id WHERE id=:id");
            t_volumes.bindValue(":frontpage_id", t_files.lastInsertId());
            t_volumes.bindValue(":thumb_id", t_thumbs.lastInsertId());
            t_volumes.bindValue(":id", volume_id);
            if(!t_volumes.exec()) {
                qDebug() << "t_volumes update failed: " << t_volumes.lastError();
                return -1;
            }
            bFrontPage = false;
        }
    }
//    if(!m_db.commit()) {
//        qDebug() << "m_db commit failed: " << m_db.lastError();
//        return -1;
//    }
    return filename_asc;
}
CatalogRecord ThumbnailManager::createCatalog(QString name, QString path)
{
    static int id =1; // FIXME
    auto catalog = CatalogRecord();
    catalog.name = name;
    catalog.path = path;
    catalog.created_at = QDateTime::currentDateTime();

    transaction();

    QSqlQuery t_catalogs(m_db);
    t_catalogs.prepare("INSERT INTO t_catalogs (name,path,created_at,updated_at)"
                       " VALUES (:name,:path,:created_at,:updated_at)");
    t_catalogs.bindValue(":name", name);
    t_catalogs.bindValue(":path", QDir::toNativeSeparators(path));
    t_catalogs.bindValue(":created_at", catalog.created_at);
    t_catalogs.bindValue(":updated_at", catalog.created_at);
    if(!execInsertQuery(t_catalogs, "t_catalogs")) return catalog;

    m_catalogWorkProgress = 0;
    m_catalogWorkMax = 0;
    int catalog_id = catalog.id = t_catalogs.lastInsertId().toInt();
    int basevolume_id = createSubVolumes(path, catalog_id);
    t_catalogs.prepare("UPDATE t_catalogs SET basevolume_id=:basevolume_id WHERE id=:id");
    t_catalogs.bindValue(":basevolume_id", basevolume_id);
    t_catalogs.bindValue(":id", catalog_id);
    if(!execInsertQuery(t_catalogs, "t_catalogs")) return catalog;

    if(m_catalogWatcher.isCanceled())
        rollback();
    else
        commit();

    return catalog;
}

static CatalogRecord callCreateCatalog(ThumbnailManager* manager, QString name, QString path)
{
    return manager->createCatalog(name, path);
}


QFutureWatcher<CatalogRecord>* ThumbnailManager::createCatalogAsync(QString name, QString path)
{
//    QFutureWatcher<CatalogRecord> watcher;
//    connect(&watcher, SIGNAL(finished()), this, SLOT(on_catalogCreated()));
    // Start the computation.
    QFuture<CatalogRecord> future = QtConcurrent::run(callCreateCatalog, this, name, path);
    m_catalogWatcher.setFuture(future);
    return &m_catalogWatcher;
}

void ThumbnailManager::cancelCreateCatalogAsync()
{
    if(!m_catalogWatcher.isRunning())
        return;
    m_catalogWatcher.cancel();
}


void ThumbnailManager::deleteCatalog(int id)
{
    QSqlQuery t_thumbs(m_db);
    t_thumbs.prepare("DELETE FROM t_thumbnails WHERE id IN (SELECT thumb_id FROM t_files WHERE volume_id IN (SELECT id FROM t_volumes WHERE catalog_id=:catalog_id))");
    t_thumbs.bindValue(":catalog_id", id);
    if(!execInsertQuery(t_thumbs, "t_thumbnails")) return;

    QSqlQuery t_files(m_db);
    t_files.prepare("DELETE FROM t_files WHERE volume_id IN (SELECT id FROM t_volumes WHERE catalog_id=:catalog_id)");
    t_files.bindValue(":catalog_id", id);
    if(!execInsertQuery(t_files, "t_files")) return;

    QSqlQuery t_fileorders(m_db);
    t_fileorders.prepare("DELETE FROM t_fileorders WHERE volume_id IN (SELECT id FROM t_volumes WHERE catalog_id=:catalog_id)");
    t_fileorders.bindValue(":catalog_id", id);
    if(!execInsertQuery(t_fileorders, "t_fileorders")) return;

    QSqlQuery t_volumeorders(m_db);
    t_volumeorders.prepare("DELETE FROM t_volumeorders WHERE id IN (SELECT id FROM t_volumes WHERE catalog_id=:catalog_id)");
    t_volumeorders.bindValue(":catalog_id", id);
    if(!execInsertQuery(t_volumeorders, "t_volumeorders")) return;

    QSqlQuery t_volumes(m_db);
    t_volumes.prepare("DELETE FROM t_volumes WHERE catalog_id=:catalog_id");
    t_volumes.bindValue(":catalog_id", id);
    if(!execInsertQuery(t_volumes, "t_volumes")) return;

    QSqlQuery t_catalogs(m_db);
    t_catalogs.prepare("DELETE FROM t_catalogs WHERE id=:id");
    t_catalogs.bindValue(":id", id);
    if(!execInsertQuery(t_catalogs, "t_catalogs")) return;
}

void ThumbnailManager::updateCatalogName(int id, QString name)
{
    QSqlQuery t_catalogs(m_db);
    t_catalogs.prepare("UPDATE t_catalogs SET name=:name WHERE id=:id");
    t_catalogs.bindValue(":id", id);
    t_catalogs.bindValue(":name", name);
    if(!execInsertQuery(t_catalogs, "t_catalogs")) return;
}

void ThumbnailManager::deleteAllCatalogs()
{

}

void ThumbnailManager::transaction()
{
    if(m_transaction)
        return;
    if(!m_db.transaction()) {
        qDebug() << "m_db transaction failed: " << m_db.lastError();
        return;
    }
    m_transaction = true;
}

void ThumbnailManager::forceTransaction()
{
    if(m_transaction)
        return;
    qDebug() << "force transaction!";
    transaction();
}

void ThumbnailManager::commit()
{
    if(!m_transaction)
        return;
    if(!m_db.commit()) {
        qDebug() << "m_db commit failed: " << m_db.lastError();
        return;
    }
    m_transaction = false;
}

void ThumbnailManager::rollback()
{
    if(!m_transaction)
        return;
    if(!m_db.rollback()) {
        qDebug() << "m_db rollback failed: " << m_db.lastError();
        return;
    }
    m_transaction = false;
}

void ThumbnailManager::dispose()
{
    m_db.close();
}



bool ThumbnailManager::execInsertQuery(QSqlQuery &query, const QString& tablename)
{
    if(!query.exec()) {
        qDebug() << tablename << " insert failed: " << query.lastError();
        return false;
    }
    return true;
}
