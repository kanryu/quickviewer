#include "filevolume.h"
#include <QDir>
#include "filevolumedirectory.h"
#include "filevolumeziparchive.h"
#include "filevolume7zarchive.h"

IFileVolume::IFileVolume(QObject *parent)
    : QObject(parent)
    , m_cnt(0)
{
}

void IFileVolume::on_ready()
{
    if(m_cnt < 0 || m_cnt >= m_filelist.size())
        return;

    QVector<int> offsets = {0, 1, 2, 3, -1, -2, 4, 5, -3, -4, 6, 7, -5, -6};
    foreach (const int of, offsets) {
        int cnt = m_cnt+of;
        if(cnt < 0 || cnt >= m_filelist.size())
            continue;
        if(m_pageCache.contains(cnt))
            m_pageCache.removeOne(cnt);
        else {
            qDebug() << "add cached:" << cnt;
            m_imageCache[cnt] = QtConcurrent::run(futureLoadImageFromFileVolume, this, m_filelist[cnt]);
        }
        m_pageCache.push_front(cnt);
    }
    m_currentCache = m_imageCache[m_cnt];
    while(m_pageCache.size() > 16) {
        int cnt = m_pageCache.takeLast();
        m_imageCache.remove(cnt);
        qDebug() << "remove cached:" << cnt;
    }
}

QPixmap IFileVolume::getIndexedImage(int idx)
{
    future_pixmap& cache = m_imageCache[idx];
    if(!cache.isFinished())
        cache.waitForFinished();
    return cache;
}

bool IFileVolume::nextPage()
{
//    qDebug() << "nextPage: " << m_cnt << m_filelist.size() <<  "prevCache.size()" << m_prevCache.size() << "nextCache.size()" << m_nextCache.size();
    if(!nextFile()) {
        return false;
    }
    on_ready();
    return true;
}

bool IFileVolume::prevPage()
{
//    qDebug() << "prevPage: " << m_cnt << m_filelist.size() <<  "prevCache.size()" << m_prevCache.size() << "nextCache.size()" << m_nextCache.size();
    if(!prevFile()) {
        return false;
    }
    on_ready();
    return true;
}

bool IFileVolume::findPageByIndex(int idx)
{
    if(m_cnt == idx)
        return true;
    if(idx < 0 || idx >= m_filelist.size())
        return false;
    bool result = findImageByIndex(idx);
    on_ready();
    return true;
}

static IFileVolume* CreateVolumeImpl(QObject* parent, QString path)
{
    QDir dir(path);

    if(dir.exists() && dir.entryList(QDir::Files, QDir::Name).size() > 0) {
        return new FileVolumeDirectory(parent, path);
    }
    QString lower = path.toLower();
    if(lower.endsWith(".zip")) {
        return new FileVolumeZipArchive(parent, path);
    }
    if(lower.endsWith(".7z")) {
        return new FileVolume7zArchive(parent, path);
    }
    if(IFileVolume::isImageFile(path)) {
        dir.cdUp();
        QString dirpath = dir.canonicalPath();
        FileVolumeDirectory* fvd = new FileVolumeDirectory(parent, dirpath);
        bool result = fvd->findImageByName(path.mid(dirpath.length()+1));
        return fvd;
    }
    return nullptr;
}

IFileVolume* IFileVolume::CreateVolume(QObject* parent, QString path, QString subfilename)
{
    IFileVolume* fv = CreateVolumeImpl(parent, path);
    if(!fv)
        return fv;
    if(fv->size() == 0) {
        delete fv;
        return nullptr;
    }
    if(subfilename.length() > 0)
    {
        fv->findImageByName(subfilename);
    }
    fv->on_ready();
    return fv;
}

bool IFileVolume::isImageFile(QString path)
{
    QStringList exts = {".jpg", ".jpeg", ".bmp", ".gif", ".dds", ".ico", ".tga", ".tif", ".tiff", ".webp", ".wbp"};
    QString lower = path.toLower();
    foreach(const QString& e, exts) {
        if(lower.endsWith(e))
            return true;
    }
    return false;
}

QPixmap IFileVolume::futureLoadImageFromFileVolume(IFileVolume* volume, QString path)
{
    return volume->loadImageByName(path);
}
