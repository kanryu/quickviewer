#include "filevolume.h"
#include <QDir>
#include "filevolumedirectory.h"
#include "filevolumeziparchive.h"
#include "filevolume7zarchive.h"
#include "ResizeHalf.h"

IFileVolume::IFileVolume(QObject *parent)
    : QObject(parent)
    , m_cnt(0)
{
}

void IFileVolume::on_ready()
{
    if(m_cnt < 0 || m_cnt >= m_filelist.size())
        return;

    qDebug() << "on_ready: m_cnt" << m_cnt;
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

const ImageContent IFileVolume::getIndexedImageContent(int idx)
{
    future_image cache = m_imageCache[idx];
    if(!cache.isFinished())
        cache.waitForFinished();
    return cache.result();
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

ImageContent IFileVolume::futureLoadImageFromFileVolume(IFileVolume* volume, QString path)
{
    QImage src = volume->loadImageByName(path);
    if(src.size().width() <= 4096 && src.size().height() <= 4096)
        return ImageContent(QPixmap::fromImage(src), path, src.size());

    qDebug() << path << "[1]Source:" <<  src;
    QSize srcSize = QSize((src.width() >> 5) << 5, (src.height() >> 1) << 1);
    QSize halfSize = QSize(srcSize.width()/2, srcSize.height()/2);
//    ResizeHalf resizer(ResizeHalf::GREY8);
    ResizeHalf resizer(src.depth() == 8 ? ResizeHalf::GREY8 : ResizeHalf::RGBA8888);

//    int width = srcSize.width();
//    switch(src.depth()) {
//    case 8: width = srcSize.width(); break;
//    case 16: width = srcSize.width() * 2; break;
//    case 24: width = srcSize.width() * 3; break;
//    case 32: width = srcSize.width() * 4; break;
//    }
    int width = srcSize.width();
    switch(src.depth()) {
    case 8: width = srcSize.width(); break;
    case 16: width = srcSize.width() / 2; break;
    case 24: width = srcSize.width() / 4 * 3; break;
    case 32: width = srcSize.width(); break;
    }
    qDebug() << path << "[3]width:" << width << srcSize;
    QImage half = QImage(halfSize.width(), halfSize.height(), src.format());
    qDebug() << path << "[2]Dest:" <<  half;
//    resizer.resizeHV(src.bits(), width, srcSize.height(), src.bytesPerLine());
    resizer.resizeHV(half.bits(), src.bits(), width, srcSize.height(), half.bytesPerLine(), src.bytesPerLine());

    return ImageContent(QPixmap::fromImage(half), path, src.size());
}

