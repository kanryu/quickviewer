#include <QtGui>
#include "filevolume.h"
#include "fileloaderdirectory.h"
#include "fileloaderziparchive.h"
#include "fileloader7zarchive.h"
#include "fileloaderrararchive.h"
#include "ResizeHalf.h"
#include "qvapplication.h"

IFileVolume::IFileVolume(QObject *parent, IFileLoader* loader)
    : QObject(parent)
    , m_cnt(0)
    , m_loader(loader)
    , m_cacheMode(CacheMode::Normal)
{
    m_filelist = m_loader->contents();
}

void IFileVolume::on_ready()
{
    if(m_cnt < 0 || m_cnt >= m_filelist.size())
        return;

//    qDebug() << "on_ready: m_cnt" << m_cnt;
    QVector<int> offsets = {0, 1, 2, 3, -1, -2, 4, 5, -3, -4, 6, 7, -5, -6};
    if(m_cacheMode == CacheMode::CoverOnly) {
        offsets = {0, 1};
    }
    if(m_cacheMode == CacheMode::FastFowrard) {
        offsets = {0, 1, 10, 11, -10, -9, 20, 21, -20, 19};
    }
    foreach (const int of, offsets) {
        int cnt = m_cnt+of;
        if(cnt < 0 || cnt >= m_filelist.size())
            continue;
//        if(m_pageCache.contains(cnt))
//            m_pageCache.removeOne(cnt);
//        else {
////            qDebug() << "add cached:" << cnt;
//            m_imageCache[cnt] = QtConcurrent::run(futureLoadImageFromFileVolume, this, m_filelist[cnt]);
//        }
//        m_pageCache.push_front(cnt);
        if(m_imageCache.checkShouldBeInserted(cnt))
            m_imageCache.insertNoChecked(cnt, QtConcurrent::run(futureLoadImageFromFileVolume, this, m_filelist[cnt]));
    }
//    m_currentCache = m_imageCache[m_cnt];
    m_currentCache = m_imageCache.object(m_cnt);
//    while(m_pageCache.size() > 16) {
//        int cnt = m_pageCache.takeLast();
//        m_imageCache.remove(cnt);
////        qDebug() << "remove cached:" << cnt;
//    }
}

const ImageContent IFileVolume::getIndexedImageContent(int idx)
{
//    future_image cache = m_imageCache[idx];
    future_image cache = m_imageCache.object(idx);
    if(!cache.isFinished())
        cache.waitForFinished();
    return cache.result();
}

bool IFileVolume::nextPage()
{
//    qDebug() << "nextPage: " << m_cnt << m_filelist.size() <<  "prevCache.size()" << m_prevCache.size() << "nextCache.size()" << m_nextCache.size();
    if(m_cnt >= m_filelist.size())
        return false;
    m_cnt++;
    on_ready();
    return true;
}

bool IFileVolume::prevPage()
{
//    qDebug() << "prevPage: " << m_cnt << m_filelist.size() <<  "prevCache.size()" << m_prevCache.size() << "nextCache.size()" << m_nextCache.size();
    if(m_cnt <= 0)
        return false;
    m_cnt--;
    on_ready();
    return true;
}

bool IFileVolume::findPageByIndex(int idx)
{
    if(m_cnt == idx)
        return true;
    if(idx < 0 || idx >= m_filelist.size())
        return false;
    m_cnt = idx;
//    bool result = findImageByIndex(idx);
    on_ready();
    return true;
}

static IFileVolume* CreateVolumeImpl(QObject* parent, QString path)
{
    QDir dir(path);

    if(dir.exists() && dir.entryList(QDir::Files, QDir::Name).size() > 0) {
        return new IFileVolume(parent, new FileLoaderDirectory(parent, path));
    }
    QString lower = path.toLower();
    if(lower.endsWith(".zip") || lower.endsWith(".cbz")) {
        return new IFileVolume(parent, new FileLoaderZipArchive(parent, path));
    }
    if(lower.endsWith(".7z")) {
        return new IFileVolume(parent, new FileLoader7zArchive(parent, path));
    }
    if(lower.endsWith(".rar") || lower.endsWith(".cbr")) {
        return new IFileVolume(parent, new FileLoaderRarArchive(parent, path));
    }
    if(IFileLoader::isImageFile(path)) {
        dir.cdUp();
        QString dirpath = dir.canonicalPath();
        IFileVolume* fvd = new IFileVolume(parent, new FileLoaderDirectory(parent, dirpath));
        bool result = fvd->findImageByName(path.mid(dirpath.length()+1));
        return fvd;
    }
    return nullptr;
}

IFileVolume* IFileVolume::CreateVolume(QObject* parent, QString path)
{
    QString pathbase = path;
    QString subfilename;
    if(path.contains("::")) {
        QStringList seps = path.split("::");
        pathbase = seps[0];
        subfilename = seps[1];
    }
    IFileVolume* fv = CreateVolumeImpl(parent, QDir::toNativeSeparators(pathbase));
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


QString IFileVolume::FullPathToVolumePath(QString path)
{
    if(!path.contains("::")) {
        return path;
    }
    return path.left(path.indexOf("::"));
}

QString IFileVolume::FullPathToSubFilePath(QString path)
{
    if(!path.contains("::")) {
        return "";
    }
    return path.mid(path.indexOf("::")+2);
}

IFileVolume *IFileVolume::CreateVolumeWithOnlyCover(QObject *parent, QString path)
{
    IFileVolume* fv = CreateVolumeImpl(parent, QDir::toNativeSeparators(path));
    if(!fv)
        return fv;
    if(fv->size() == 0) {
        delete fv;
        return nullptr;
    }
    fv->m_cacheMode = CacheMode::CoverOnly;
    fv->on_ready();
    return fv;
}

static void parseExifTextExtents(QImage& img, easyexif::EXIFInfo& info)
{
    info.Make = img.text("Make").toStdString();
    info.Model = img.text("Model").toStdString();
    info.Orientation = img.text("Software").toInt();
    info.BitsPerSample = img.text("BitsPerSample").toInt();
    info.Software = img.text("Software").toStdString();
    info.DateTime = img.text("DateTime").toStdString();
    info.ExposureTime = img.text("ExposureTime").toDouble();
    info.FNumber = img.text("FNumber").toDouble();
    info.ISOSpeedRatings = img.text("ISOSpeedRatings").toInt();
    info.Flash = img.text("Flash").toInt();
    info.ImageWidth = img.text("ImageWidth").toInt();
    info.ImageHeight = img.text("ImageHeight").toInt();
}

#define TURBO_JPEG_FMT "turbojpeg"

ImageContent IFileVolume::futureLoadImageFromFileVolume(IFileVolume* volume, QString path)
{
    int maxTextureSize = qApp->maxTextureSize();

    QByteArray bytes = volume->loadByteArrayByName(path);
    QBuffer buffer(&bytes);
    QString aformat = IFileLoader::isExifJpegImageFile(path) && IFileLoader::isImageFile("turbojpeg")
            ? TURBO_JPEG_FMT : QFileInfo(path.toLower()).suffix();

    // turbjpeg can turbo rescaling when loading
    QImageReader reader(&buffer, aformat.toUtf8());
    bool readerable = reader.canRead();
    QSize baseSize = reader.size();
    QSize loadingSize = baseSize;
    // qrawspeed plugin can also load rescaled raw images(using built in thumbnail),
    // but usualy thumbnails are too small, so we don't use
    if(aformat == TURBO_JPEG_FMT) {
        while(loadingSize.width() > maxTextureSize || loadingSize.height() > maxTextureSize)
            loadingSize = QSize((loadingSize.width()+1) >> 1,(loadingSize.height()+1) >> 1);
        reader.setScaledSize(loadingSize);
    }
    QImage src = reader.read();

    // parsing JPEG EXIF
    easyexif::EXIFInfo info;
    if(src.width() > 0 && IFileLoader::isExifJpegImageFile(path)) {
        int result = info.parseFrom(reinterpret_cast<const unsigned char*>(bytes.constData()), bytes.length());
    }

    if(src.width() > 0 && IFileLoader::isExifRawImageFile(path)) {
        parseExifTextExtents(src, info);
    }


    if(src.width() <= maxTextureSize && src.height() <= maxTextureSize)
        return ImageContent(QPixmap::fromImage(src), path, baseSize, info);

    // resample for too big images
//    qDebug() << path << "[1]Source:" <<  src;
    QSize srcSizeReal = src.size();
    QImage src2;
    switch(src.depth()) {
    case 32:
        if((src.width() | 0x3) > 0) {
            src2 = src.copy(QRect(0, 0, src.width() >> 2 << 2, src.height() >> 1 << 1));
            //qDebug() << path << "[4]Source:" <<  src2;
            src = src2;
        }
        break;
    default:
        if(src.format() != QImage::Format::Format_Grayscale8 && src.format() != QImage::Format::Format_RGB888) {
            src = src.convertToFormat(QImage::Format::Format_RGB888);
        }
        if((src.width() | 0xF) > 0) {
            src2 = src.copy(QRect(0, 0, src.width() >> 4 << 4, src.height() >> 1 << 1));
            //qDebug() << path << "[4]Source:" <<  src2;
            src = src2;
        }
        break;
    }

    QSize srcSize = src.size();
    QSize halfSize = QSize((srcSize.width())/2, (srcSize.height())/2);

    //qDebug() << path << "[3]width:" << srcSize;
    QImage half = QImage(halfSize.width(), halfSize.height(), src.format());
    //qDebug() << path << "[2]Dest:" <<  half;

    ResizeHalf::FMT fmt = (ResizeHalf::FMT)(src.depth() >> 3);
    ResizeHalf resizer(fmt);
    resizer.resizeHV(half.bits(), src.bits(), src.width(), srcSize.height(), half.bytesPerLine(), src.bytesPerLine());

    return ImageContent(QPixmap::fromImage(half), path, srcSizeReal, info);
}

