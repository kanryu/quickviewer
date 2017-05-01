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

int ThumbnailManager::createVolumes(QString dirpath, int parent_id)
{
    QDir dir(dirpath);
    if(!dir.exists())
        return -1;
    int volume_id = createVolumeInternal(dirpath, parent_id);
    if(volume_id < 0) return -1;

    QStringList files = dir.entryList(QDir::Files, QDir::Unsorted);
    if(files.size() > 0) {
        createVolume(dirpath, volume_id);
    }
    QSqlQuery t_volumeorders(m_db);
    t_volumeorders.prepare("INSERT INTO t_volumeorders (id,parent_id,volumename_asc)"
                      " VALUES (:id,:parent_id,:volumename_asc)");
    QStringList subdirs = dir.entryList(QDir::Dirs|QDir::NoDotAndDotDot, QDir::Unsorted);
    sortFiles(subdirs);
    int volumeame_asc = 0;
    foreach(QString sub, subdirs) {
        QString subpath = dir.filePath(sub);
        int sub_id = createVolumes(subpath, volume_id);
        if(sub_id < 0)
            continue;
        t_volumeorders.bindValue(":id", sub_id);
        t_volumeorders.bindValue(":parent_id", volume_id);
        t_volumeorders.bindValue(":volumename_asc", volumeame_asc++);
        if(!execInsertQuery(t_volumeorders, "t_volumeorders")) return -1;

    }
    return volume_id;
}

int ThumbnailManager::createVolumeInternal(QString dirpath, int parent_id)
{
    QFileInfo info(dirpath);
    qDebug() << "volume: " << info.fileName();
    QSqlQuery t_volumes(m_db);
    t_volumes.prepare("INSERT INTO t_volumes (realname, path, parent_id) VALUES (:realname,:path,:parent_id)");
    t_volumes.bindValue(":realname", info.fileName());
    t_volumes.bindValue(":path", QDir::toNativeSeparators(dirpath));
    t_volumes.bindValue(":parent_id", parent_id);
    if(!execInsertQuery(t_volumes, "t_volumes")) return -1;

    int volume_id = t_volumes.lastInsertId().toInt();
    return volume_id;
}

CatalogRecord ThumbnailManager::createCatalog(QString name, QString path)
{
    static int id =1; // FIXME
    auto catalog = CatalogRecord();
    catalog.id = id++;
    catalog.name = name;
    catalog.path = path;
    catalog.created_at = QDateTime::currentDateTime();
    return catalog;
}

void ThumbnailManager::deleteCatalog(int id)
{

}

void ThumbnailManager::updateCatalogName(int id, QString name)
{

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


int ThumbnailManager::createVolume(QString dirpath, int volume_id)
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
    foreach(QString filename, files) {
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
    return volume_id;
}

bool ThumbnailManager::execInsertQuery(QSqlQuery &query, const QString& tablename)
{
    if(!query.exec()) {
        qDebug() << tablename << " insert failed: " << query.lastError();
        return false;
    }
    return true;
}
