#include "filevolume.h"
#include <QDir>
#include "filevolumedirectory.h"
#include "filevolumeziparchive.h"
#include "filevolume7zarchive.h"

IFileVolume::IFileVolume(QObject *parent)
    : QObject(parent)
{
}

void IFileVolume::on_ready()
{
//    emit changing(currentImage());
//    emit changed(currentPath());
    // current pages
    m_currentCache = QtConcurrent::run(futureLoadImageFromFileVolume, this, m_filelist[m_cnt]);
    // next pages
    for(int i = 1; i <= 4; i++) {
        if(m_cnt+i >= m_filelist.size())
            break;
        if(i <= m_nextCache.size())
            continue;
        m_nextCache.push_back(QtConcurrent::run(futureLoadImageFromFileVolume, this, m_filelist[m_cnt+i]));
    }
    while(m_nextCache.size() > 4)
        m_nextCache.pop_back();
    // prev pages
    for(int i = 1; i <= 4; i++) {
        if(m_cnt < i)
            break;
        if(i <= m_prevCache.size())
            continue;
        m_prevCache.push_back(QtConcurrent::run(futureLoadImageFromFileVolume, this, m_filelist[m_cnt-i]));
    }
    while(m_prevCache.size() > 4)
        m_prevCache.pop_back();
}

bool IFileVolume::nextPage()
{
    qDebug() << "nextPage: " << m_cnt << m_filelist.size() <<  "prevCache.size()" << m_prevCache.size() << "nextCache.size()" << m_nextCache.size();
    if(m_nextCache.size() == 0)
        return false;
    m_prevCache.push_front(m_currentCache);
    if(m_prevCache.size() > 8)
        m_prevCache.pop_back();

    for(int i = 1; i <= 6; i++) {
        if(m_cnt+i >= m_filelist.size())
            break;
        if(i <= m_nextCache.size())
            continue;
        m_nextCache.push_back(QtConcurrent::run(futureLoadImageFromFileVolume, this, m_filelist[m_cnt+i]));
    }

    m_currentCache = m_nextCache.first();
    if(m_nextCache.size() == 1)
        m_nextCache.clear();
    else
        m_nextCache.pop_front();
    bool result = nextFile();

    return true;
}

bool IFileVolume::prevPage()
{
    qDebug() << "prevPage: " << m_cnt << m_filelist.size() <<  "prevCache.size()" << m_prevCache.size() << "nextCache.size()" << m_nextCache.size();
    if(m_prevCache.size() == 0)
        return false;
    m_nextCache.push_front(m_currentCache);
    if(m_nextCache.size() > 8)
        m_nextCache.pop_back();

    for(int i = 1; i <= 6; i++) {
        if(m_cnt < i)
            break;
        if(i <= m_prevCache.size())
            continue;
        m_prevCache.push_back(QtConcurrent::run(futureLoadImageFromFileVolume, this, m_filelist[m_cnt-i]));
    }

    m_currentCache = m_prevCache.first();
    if(m_prevCache.size() == 1)
        m_prevCache.clear();
    else
        m_prevCache.pop_front();

    bool result = prevFile();
    return true;
}

bool IFileVolume::findPageByIndex(int idx)
{
    if(m_cnt == idx)
        return true;
    if(idx < 0 || idx >= m_filelist.size())
        return false;
    if(idx > m_cnt)
    {
        if(idx - m_cnt <= m_nextCache.size()) {
            while(m_cnt < idx)
                nextPage();
            return true;
        }
    } else {
        if(m_cnt - idx <= m_prevCache.size()) {
            while(m_cnt > idx)
                prevPage();
            return true;
        }
    }
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
    if(subfilename.length() > 0)
    {
        fv->findImageByName(subfilename);
    }
    fv->on_ready();
    return fv;
}

bool IFileVolume::isImageFile(QString path)
{
//    const char* exts[] = {".jpg", ".jpeg", ".bmp", ".gif", ".dds", ".ico", ".tga", ".tif", ".tiff", ".webp", ".wbp", nullptr};
    QStringList exts = {".jpg", ".jpeg", ".bmp", ".gif", ".dds", ".ico", ".tga", ".tif", ".tiff", ".webp", ".wbp", nullptr};
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
