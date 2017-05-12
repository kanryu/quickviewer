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

bool ThumbnailManager::caseInsensitiveLessThanWString(const std::wstring &s1, const std::wstring &s2)
{
    return ::StrCmpLogicalW(s1.c_str(), s2.c_str()) < 0;
}
#else
bool ThumbnailManager::caseInsensitiveLessThan(const QString &s1, const QString &s2)
{
    return s1.toLower() < s2.toLower();
}
bool ThumbnailManager::caseInsensitiveLessThanWString(const std::wstring &s1, const std::wstring &s2)
{
    return s1 < s2;
}
#endif

ThumbnailManager::ThumbnailManager(QObject* parent, QString dbpath)
    : QObject(parent)
    , m_db(QSqlDatabase::addDatabase("QSQLITE"))
    , m_transaction(false)
    , m_catalogWatcher(this)
    , m_volumesDurty(true)
{

    m_db.setDatabaseName(dbpath);
    if (!m_db.open())
    {
       qDebug() << "Error: connection with database fail";
    }
    else
    {
       qDebug() << "Database: connection ok";
       QtConcurrent::run(this, &ThumbnailManager::volumes);
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

VolumeWorker ThumbnailManager::createSubVolumesConcurrent(QString dirpath, int volume_id, int parent_id)
{
    VolumeWorker vw = {0};
    vw.frontPage.asc = -1;
    vw.dirpath = dirpath;
    vw.volume_id = volume_id;
    vw.parent_id = parent_id;
    QDir dir(dirpath);
    QStringList subdirs = dir.entryList(QDir::Dirs|QDir::NoDotAndDotDot, QDir::Unsorted);
    sortFiles(subdirs);
    if(m_catalogWatcher.isStarted() && subdirs.size()>0) {
        m_catalogWorkMax += subdirs.size();
        emit m_catalogWatcher.progressRangeChanged(0, m_catalogWorkMax);
    }
    vw.subpaths = subdirs;

    QStringList files = dir.entryList(QDir::Files, QDir::Unsorted);
    sortFiles(files);
    for(int i = 0; i < files.size(); i++) {
        if(m_catalogWatcher.isCanceled())
            break;
        QString filename = files[i];
        if(!isImageFile(filename))
            continue;
        QString filepath = dir.filePath(filename);
        vw.frontPage = createFileRecord(filename, filepath, 0);
        break; // ONLY FRONT PAGE
    }
    if(m_catalogWatcher.isStarted()) {
        emit m_catalogWatcher.progressValueChanged(m_catalogWorkProgress++);
    }
    return vw;
}

int ThumbnailManager::createVolumesFrontPageOnly(QString dirpath, int catalog_id)
{
    int volume_id = createVolumeInternal(dirpath, catalog_id, -1);
    if(volume_id < 0) return -1;

    QSqlQuery t_files(m_db);
    t_files.prepare("INSERT INTO t_files (volume_id,name,size,width,height,thumb_id,created_at,updated_at,alternated)"
                      " VALUES (:volume_id,:name,:size,:width,:height,:thumb_id,:created_at,:updated_at,:alternated)");
    QSqlQuery t_fileorders(m_db);
    t_fileorders.prepare("INSERT INTO t_fileorders (id,volume_id,filename_asc)"
                      " VALUES (:id,:volume_id,:filename_asc)");
    QSqlQuery t_thumbs(m_db);
    t_thumbs.prepare("INSERT INTO t_thumbnails (width,height,thumbnail,created_at)"
                       " VALUES (:width,:height,:thumbnail,:created_at)");
    QSqlQuery t_volumes(m_db);
    t_volumes.prepare("UPDATE t_volumes SET frontpage_id=:frontpage_id, thumb_id=:thumb_id WHERE id=:id");

    QList<VolumeWorker> parentworkers;
    {
        QDir dir(dirpath);
        VolumeWorker root = {0};
        root.dirpath = dirpath;
        root.volume_id = volume_id;
        root.catalog_id = catalog_id;
        root.parent_id = -1;
        root.subpaths = dir.entryList(QDir::Dirs|QDir::NoDotAndDotDot, QDir::Unsorted);
        sortFiles(root.subpaths);
        parentworkers << root;
    }
    QList<QFuture<VolumeWorker>> workers;
    do {
        foreach(const VolumeWorker& p, parentworkers) {
            QDir dir(p.dirpath);
            QStringList subdirs = p.subpaths;
            if(m_catalogWatcher.isStarted() && subdirs.size()>0) {
                m_catalogWorkMax += subdirs.size();
                emit m_catalogWatcher.progressRangeChanged(0, m_catalogWorkMax);
            }
            foreach(QString sub, subdirs) {
                QString subpath = dir.filePath(sub);
                if(m_catalogWatcher.isCanceled())
                    return -1;
                int sub_id = createVolumeInternal(subpath, catalog_id, p.parent_id);
                if(sub_id < 0) return -1;
                workers.append(QtConcurrent::run(this, &ThumbnailManager::createSubVolumesConcurrent, subpath, sub_id, p.volume_id));

            }
        }
        parentworkers.clear();

        foreach(const QFuture<VolumeWorker>& w, workers) {
            VolumeWorker& v = w.result();
            if(m_catalogWatcher.isCanceled())
                return -1;
            if(v.volume_id < 0)
                continue;
            if(v.frontPage.asc >= 0) {
                QFileInfo info(v.dirpath);
                emit m_catalogWatcher.progressTextChanged(info.fileName());

                t_thumbs.bindValue(":width", v.frontPage.thumb.width());
                t_thumbs.bindValue(":height", v.frontPage.thumb.height());
                t_thumbs.bindValue(":thumbnail", v.frontPage.thumbbytes);
                t_thumbs.bindValue(":created_at", QDateTime::currentDateTime());
                if(!execInsertQuery(t_thumbs, "t_thumbs")) return -1;

                t_files.bindValue(":volume_id", volume_id);
                t_files.bindValue(":name", v.frontPage.filename);
                t_files.bindValue(":size", v.frontPage.info.size());
                t_files.bindValue(":width", v.frontPage.imagesize.width());
                t_files.bindValue(":height", v.frontPage.imagesize.height());
                t_files.bindValue(":thumb_id", t_thumbs.lastInsertId());
                t_files.bindValue(":created_at", v.frontPage.info.created());
                t_files.bindValue(":updated_at", v.frontPage.info.lastModified());
                if(!execInsertQuery(t_files, "t_files")) return -1;

                t_fileorders.bindValue(":volume_id", volume_id);
                t_fileorders.bindValue(":id", t_files.lastInsertId());
                t_fileorders.bindValue(":filename_asc", v.frontPage.asc);
                if(!execInsertQuery(t_fileorders, "t_fileorders")) return -1;

                t_volumes.bindValue(":frontpage_id", t_files.lastInsertId());
                t_volumes.bindValue(":thumb_id", t_thumbs.lastInsertId());
                t_volumes.bindValue(":id", v.volume_id);
                if(!execInsertQuery(t_volumes, "t_volumes")) return -1;
            }

            if(v.subpaths.size() > 0)
                parentworkers << v;
        }
        workers.clear();
    } while(parentworkers.size() > 0);


    return volume_id;

}

static QString realname2BookTitle(QString realname)
{
    // Extract book title from folder name
    // from: <<<(TAG1) [Publisher(Author)] book title (TAG2) (TAG3) ...>>>
    //   to: <<<[Publisher(Author)] book title>>>
    //
    // e.g. 'Star Wars - Han Solo (2017) (Digital) (newcomic.info)'
    //
    // from: <<<# [TAG1] [TAG2] [Publisher(Author)] book title (TAG2) [TAG4] ...>>>
    //   to: <<<[Publisher(Author)] book title>>>
    //
    // TAGs will save other fields

    QList<QChar> parenthesis;
    parenthesis << '?';
    QStringList clist;
    QStringList tag;
    int cnt=0;
    bool NumberSign = false;
    bool authorExported = false;
    foreach(QChar c, realname) {
        switch(c.unicode()) {
        case '#':
            if(cnt==0) {
                NumberSign = true;
                parenthesis << c;
            }
            else if(parenthesis.last() == '#')
                tag << c;
            else
                clist << c;
            break;
        case '[':
            parenthesis << c;
            if(tag.size())
                tag.clear();
            tag << c;
            break;
        case ']':
            if(parenthesis.size() == 1)
                break;
            parenthesis.removeLast();
            tag << c;
            if(!NumberSign && !authorExported) {
                clist << tag.join("");
                tag.clear();
                authorExported = true;
            }
            break;
        case '(':
            if(parenthesis.last() == '[')
                tag << c;
            else {
                tag.clear();
                if(parenthesis.last() == '#') {
                    parenthesis.removeLast();
                    NumberSign = false;
                }
                parenthesis << c;
            }
            break;
        case ')':
            if(parenthesis.size() == 1)
                break;
            if(parenthesis.last() == '[')
                tag << c;
            else
                parenthesis.removeLast();
            break;
        default:
            if(parenthesis.last() == '[')
                tag << c;
            else {
                if(parenthesis.last() == '#') {
                    if(c != ' ')
                        tag << c;
                    else
                        parenthesis.removeLast();
                }
                else if (NumberSign && c != ' ' && tag.size()) {
                    // last tag will be Publisher/Author
                    clist << tag.join("") << " " << c;
                    tag.clear();
                    NumberSign = false;
                }
                else if(parenthesis.last() == '(')
                    tag << c;
                else
                    clist << c;
            }
        }
        cnt++;
    }
    QString result = clist.join("");
    return result.trimmed();
}

int ThumbnailManager::createVolumeInternal(QString dirpath, int catalog_id, int parent_id)
{
    QFileInfo info(dirpath);
    QString realname = info.fileName();
    qDebug() << "volume: " << realname;
    emit m_catalogWatcher.progressTextChanged(realname);

    QSqlQuery t_volumes(m_db);
    t_volumes.prepare("INSERT INTO t_volumes (name, realname, path, catalog_id, parent_id) VALUES (:name, :realname,:path,:catalog_id,:parent_id)");
    t_volumes.bindValue(":name", realname2BookTitle(realname));
    t_volumes.bindValue(":realname", realname);
    t_volumes.bindValue(":path", QDir::toNativeSeparators(dirpath));
    t_volumes.bindValue(":catalog_id", catalog_id);
    t_volumes.bindValue(":parent_id", parent_id);
    if(!execInsertQuery(t_volumes, "t_volumes")) return -1;

    int volume_id = t_volumes.lastInsertId().toInt();
    return volume_id;
}

static bool caseInsensitiveLessThanVolumeOrder(const VolumeOrder* s1, const VolumeOrder* s2)
{
    return ThumbnailManager::caseInsensitiveLessThanWString(s1->realname, s2->realname);
}


void ThumbnailManager::updateVolumeOrders()
{
    QSqlQuery t_volumeorders(m_db);
    t_volumeorders.prepare("DELETE FROM t_volumeorders");
    if(!execInsertQuery(t_volumeorders, "t_volumeorders")) return;

    QSqlQuery t_volumes(m_db);
    t_volumes.prepare("SELECT id, parent_id, realname FROM t_volumes");
    if(!execInsertQuery(t_volumes, "t_volumes")) return;

    QVector<VolumeOrder> volumes;
    {
        QList<VolumeOrder> vollist;
        while(t_volumes.next()) {
            VolumeOrder vr = {0};
            vr.id = t_volumes.value("id").toInt();
            vr.parent_id = t_volumes.value("parent_id").toInt();
            vr.realname = t_volumes.value("realname").toString().toLower().toStdWString();
            vollist.append(vr);
        }
        volumes = vollist.toVector();
    }
    QVector<VolumeOrder*> volumes_pt;
    //int sz = t_volumes.numRowsAffected();
    volumes_pt.resize(volumes.size());
    for(int i=0; i < volumes.size();i++) {
        volumes_pt[i] = &volumes[i];
    }

    qSort(volumes_pt.begin(), volumes_pt.end(), caseInsensitiveLessThanVolumeOrder);
    t_volumeorders.prepare("INSERT INTO t_volumeorders (id,parent_id,volumename_asc)"
                      " VALUES (:id,:parent_id,:volumename_asc)");
    for(int i = 0; i < volumes_pt.size(); i++) {
        t_volumeorders.bindValue(":id", volumes_pt[i]->id);
        t_volumeorders.bindValue(":parent_id", volumes_pt[i]->parent_id);
        t_volumeorders.bindValue(":volumename_asc", i);
        if(!execInsertQuery(t_volumeorders, "t_volumeorders")) return;
    }
}

FileWorker ThumbnailManager::createFileRecord(QString filename, QString filepath, int filename_asc)
{
    FileWorker result;
    result.filename = filename;
    result.filepath = filepath;
    result.info.setFile(filepath);
    result.asc = filename_asc;
    QImage img(filepath);
    if(!img.width()) {
        result.asc = -1;
        return result;
    }
    result.imagesize = img.size();

    QImage thumb = img.scaledToWidth(2*THUMB_WIDTH, Qt::FastTransformation);
    thumb = thumb.scaledToWidth(THUMB_WIDTH, Qt::SmoothTransformation);
    QBuffer thumbdat;
    thumbdat.open(QBuffer::ReadWrite);
    if(!thumb.save(&thumbdat, "JPEG", 90)) {
        result.asc = -1;
        return result;
    }
    result.thumb = thumb;
    result.thumbbytes = thumbdat.data();
    result.created_at = QDateTime::currentDateTime();

//    QBuffer alternated;
//    if(ThumbnailManager::isHeavyImageFile(filename) || img.width() > MAX_WIDTH || img.height() > MAX_HEIGHT) {
//        QDesktopWidget* desktop = QApplication::desktop();
//        QRect rect = desktop->screenGeometry();
////            qDebug() << rect;
//        QImage alter = img.scaled(rect.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
//        alternated.open(QBuffer::ReadWrite);
//        if(!alter.save(&alternated, "JPEG", 90)) {
//            return result;
//        }
//        result.alternated = alternated.data();
//    }
    return result;
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
    QList<QFuture<FileWorker>> workers;
    for(int i = 0; i < files.size(); i++) {
//    foreach(QString filename, files) {
        if(m_catalogWatcher.isStarted()) {
//            int progressValue = m_catalogWatcher.progressValue();
            emit m_catalogWatcher.progressValueChanged(m_catalogWorkProgress++);
        }
        if(m_catalogWatcher.isCanceled())
            break;
        QString filename = files[i];
//        qDebug() << "  file: " << filename;
        if(!isImageFile(filename))
            continue;
        QString filepath = dir.filePath(filename);
        workers.append(QtConcurrent::run(this, &ThumbnailManager::createFileRecord, filename, filepath, filename_asc++));
    }
    foreach(auto worker, workers) {
        FileWorker& w = worker.result();
        if(w.asc<0) {
            filename_asc--;
            continue;
        }
        if(m_catalogWatcher.isCanceled())
            break;
        t_thumbs.bindValue(":width", w.thumb.width());
        t_thumbs.bindValue(":height", w.thumb.height());
        t_thumbs.bindValue(":thumbnail", w.thumbbytes);
        t_thumbs.bindValue(":created_at", currentDateTimeAsString());
        if(!execInsertQuery(t_thumbs, "t_thumbs")) return -1;

        t_files.bindValue(":volume_id", volume_id);
        t_files.bindValue(":name", w.filename);
        t_files.bindValue(":size", w.info.size());
        t_files.bindValue(":width", w.imagesize.width());
        t_files.bindValue(":height", w.imagesize.height());
        t_files.bindValue(":thumb_id", t_thumbs.lastInsertId());
        t_files.bindValue(":created_at", DateTimeToIsoString(w.info.created()));
        t_files.bindValue(":updated_at", DateTimeToIsoString(w.info.lastModified()));
        t_files.bindValue(":alternated", w.alternated.size()==0 ? nullptr : w.alternated);
        if(!execInsertQuery(t_files, "t_files")) return -1;

        t_fileorders.bindValue(":volume_id", volume_id);
        t_fileorders.bindValue(":id", t_files.lastInsertId());
        t_fileorders.bindValue(":filename_asc", w.asc);
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

    return filename_asc;
}


CatalogRecord ThumbnailManager::createCatalog(QString name, QString path)
{
    CatalogRecord catalog = {0};
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
//    int basevolume_id = createSubVolumes(path, catalog_id);
    int basevolume_id = createVolumesFrontPageOnly(path, catalog_id);
    if(basevolume_id > 0) {
        t_catalogs.prepare("UPDATE t_catalogs SET basevolume_id=:basevolume_id WHERE id=:id");
        t_catalogs.bindValue(":basevolume_id", basevolume_id);
        t_catalogs.bindValue(":id", catalog_id);
        if(!execInsertQuery(t_catalogs, "t_catalogs")) return catalog;
    }


    if(m_catalogWatcher.isCanceled()) {
        rollback();
        return catalog;
    }
    commit();
    catalog.created = true;
    m_volumesDurty = true;
    emit catalogCreated(catalog);

    return catalog;
}

QList<CatalogRecord> ThumbnailManager::callCreateCatalog(const QList<CatalogRecord>& newers)
{
    QList<CatalogRecord> result;
    foreach(const CatalogRecord& r, newers) {
        result << createCatalog(r.name, r.path);
        if(m_catalogWatcher.isCanceled())
            break;
    }
    if(result.size() > 1 || result[0].created) {
        transaction();
        updateVolumeOrders();
        commit();
    }

    return result;
}


QFutureWatcher<QList<CatalogRecord> > *ThumbnailManager::createCatalogAsync(QList<CatalogRecord> newers)
{
    QFuture<QList<CatalogRecord>> future = QtConcurrent::run(this, &ThumbnailManager::callCreateCatalog, newers);
    m_catalogWatcher.setFuture(future);
    return &m_catalogWatcher;
}

void ThumbnailManager::cancelCreateCatalogAsync()
{
    if(!m_catalogWatcher.isRunning())
        return;
    m_catalogWatcher.cancel();
}

QMap<int, CatalogRecord> ThumbnailManager::catalogs()
{
    QMap<int, CatalogRecord> result;
    QSqlQuery t_catalogs(m_db);
    t_catalogs.prepare("SELECT * FROM t_catalogs");
    if(!execInsertQuery(t_catalogs, "t_catalogs")) result;
    while(t_catalogs.next()) {
        CatalogRecord cr;
        cr.id = t_catalogs.value("id").toInt();
        cr.basevolume_id = t_catalogs.value("basevolume_id").toInt();
        cr.name = t_catalogs.value("name").toString();
        cr.path = t_catalogs.value("path").toString();
        cr.created_at = t_catalogs.value("created_at").toDateTime();
        cr.created = true;
        result[cr.id] = cr;
    }
    return result;
}

QList<VolumeThumbRecord> ThumbnailManager::volumes()
{
    if(!m_volumesDurty) {
        return m_volumesCacne;
    }
    QList<VolumeThumbRecord> result;
    QSqlQuery v_volumethm(m_db);
    v_volumethm.prepare("SELECT * FROM v_volumethm");
    if(!execInsertQuery(v_volumethm, "v_volumethm")) result;
    while(v_volumethm.next()) {
        VolumeThumbRecord vtr;
        vtr.id = v_volumethm.value("id").toInt();
        vtr.name = v_volumethm.value("name").toString();
        vtr.nameNoCase = vtr.name.toLower();
        vtr.realname = v_volumethm.value("realname").toString();
        vtr.realnameNoCase = vtr.realname.toLower();
        vtr.path = v_volumethm.value("path").toString();
        vtr.frontpage_id = v_volumethm.value("frontpage_id").toInt();
        vtr.parent_id = v_volumethm.value("parent_id").toInt();
        vtr.thumbnail = v_volumethm.value("thumbnail").toByteArray();
        result.append(vtr);
    }
    m_volumesDurty = false;
    return m_volumesCacne = result;
}

static VolumeThumbRecord thumbnail2Icon(VolumeThumbRecord vtr)
{
    QString aformat = IFileLoader::isImageFile("turbojpeg") ? TURBO_JPEG_FMT : "jpg";
    QPixmap pixmap = QPixmap::fromImage(QImage::fromData(vtr.thumbnail, aformat.toUtf8()));
//    QPixmap pixmap = QPixmap::fromImage(QImage::fromData(vtr.thumbnail));
    vtr.icon = QIcon(pixmap);
//    vtr.thumbnail.clear();
    return vtr;
}

QList<VolumeThumbRecord> ThumbnailManager::volumes2()
{
    if(!m_volumesDurty) {
        return m_volumesCacne;
    }
    QList<VolumeThumbRecord> result;
    QList<QFuture<VolumeThumbRecord> > resultasync;
    QSqlQuery v_volumethm(m_db);
    v_volumethm.prepare("SELECT * FROM v_volumethm");
    if(!execInsertQuery(v_volumethm, "v_volumethm")) result;
    while(v_volumethm.next()) {
        VolumeThumbRecord vtr;
        vtr.id = v_volumethm.value("id").toInt();
        vtr.name = v_volumethm.value("name").toString();
        vtr.nameNoCase = vtr.name.toLower();
        vtr.realname = v_volumethm.value("realname").toString();
        vtr.realnameNoCase = vtr.realname.toLower();
        vtr.path = v_volumethm.value("path").toString();
        vtr.frontpage_id = v_volumethm.value("frontpage_id").toInt();
        vtr.parent_id = v_volumethm.value("parent_id").toInt();
        vtr.thumbnail = v_volumethm.value("thumbnail").toByteArray();
        resultasync.append(QtConcurrent::run(thumbnail2Icon, vtr));
    }
    foreach(auto a, resultasync) {
        result.append(a.result());
    }
    m_volumesDurty = false;
    return m_volumesCacne = result;
}


void ThumbnailManager::deleteCatalog(int id)
{
    QSqlQuery t_thumbs(m_db);
    t_thumbs.prepare("DELETE FROM t_thumbnails WHERE id IN (SELECT thumb_id FROM t_files WHERE volume_id IN (SELECT id FROM t_volumes WHERE catalog_id=:catalog_id))");
    t_thumbs.bindValue(":catalog_id", id);
    if(!execInsertQuery(t_thumbs, "t_thumbnails")) return;

    m_volumesDurty = true;

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
    transaction();
    QSqlQuery t_thumbs(m_db);
    do {
        if(!t_thumbs.exec("DELETE FROM t_thumbnails")) break;
        if(!t_thumbs.exec("DELETE FROM t_fileorders")) break;
        if(!t_thumbs.exec("DELETE FROM t_volumeorders")) break;
        if(!t_thumbs.exec("DELETE FROM t_files")) break;
        if(!t_thumbs.exec("DELETE FROM t_volumes")) break;
        if(!t_thumbs.exec("DELETE FROM t_catalogs")) break;
        commit();
        vacuum();
        m_volumesDurty = true;
        return;
    } while(0);
    qDebug() << " query failed: " << t_thumbs.lastError();
    rollback();
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

void ThumbnailManager::vacuum()
{
    QSqlQuery t_thumbs(m_db);
    do {
        if(!t_thumbs.exec("VACUUM")) break;
        return;
    } while(0);
    qDebug() << " query failed: " << t_thumbs.lastError();

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
