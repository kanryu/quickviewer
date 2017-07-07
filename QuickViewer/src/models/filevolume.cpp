#include <QtGui>

#include "filevolume.h"
#include "fileloaderdirectory.h"
#include "fileloadersubdirectory.h"
#include "fileloaderziparchive.h"
#include "fileloader7zarchive.h"
#include "fileloaderrararchive.h"
#include "ResizeHalf.h"
#include "qvapplication.h"
#include "qzimg.h"
#include "pagemanager.h"

IFileVolume::IFileVolume(QObject *parent, IFileLoader* loader, PageManager* pageManager)
    : QObject(parent)
    , m_cnt(0)
    , m_loader(loader)
    , m_cacheMode(CacheMode::Normal)
    , m_pageManager(pageManager)
    , m_imageCache(20)
    , m_openedWithSpecifiedImageFile(false)
{
    m_filelist = m_loader->contents();
}

void IFileVolume::on_ready()
{
    if(m_cnt < 0 || m_cnt >= m_filelist.size())
        return;

//    qDebug() << "on_ready: m_cnt" << m_cnt;
    QVector<int> offsets;
    switch(m_cacheMode) {
    case CacheMode::Normal: offsets = {0, 1, 2, 3, -1, -2, 4, 5, -3, -4, 6, 7, -5, -6}; break;
    case CacheMode::FastFowrard: offsets = {0, 1, 10, 11, -10, -9, 20, 21, -20, 19}; break;
    case CacheMode::CoverOnly: offsets = {0, 1}; break;
    case CacheMode::NoAsync:
        m_currentCacheSync = futureLoadImageFromFileVolume(this, m_filelist[m_cnt], QSize());
        return;
    }
    foreach (const int of, offsets) {
        int cnt = m_cnt+of;
        if(cnt < 0 || cnt >= m_filelist.size())
            continue;
        if(m_imageCache.contains(cnt) && qApp->Effect() < qvEnums::UsingFixedShader) {
            ImageContent ic = m_imageCache.object(cnt).result();
            if(ic.ImportSize.isValid()) {
                QSize resized = m_pageManager->viewportSize();
                resized.setWidth(ic.ImportSize.width()*resized.height()/ic.ImportSize.height());
                if(ic.ResizedImage.size() != resized) {
//                    qDebug() << ic.ResizedImage.size() << resized;
                    m_imageCache.insert(cnt, QtConcurrent::run(futureReizeImage, ic, m_pageManager->viewportSize()));
                }
            }
        }
        if(m_imageCache.checkShouldBeInserted(cnt))
            m_imageCache.insertNoChecked(cnt, QtConcurrent::run(
                 futureLoadImageFromFileVolume,
                 this,
                 m_filelist[cnt],
                 (m_pageManager && qApp->Effect() < qvEnums::UsingFixedShader)
                     ? m_pageManager->viewportSize()
                     : QSize())
            );
    }
    m_currentCache = m_imageCache.object(m_cnt);
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

bool IFileVolume::findImageByIndex(int idx) {
    if(idx < 0 || idx >= m_filelist.size())
        return false;
    m_cnt = idx;
    on_ready();
    return true;
}

bool IFileVolume::findImageByName(QString name) {
    int idx = m_filelist.indexOf(name);
    if(idx < 0)
        return false;
    m_cnt = idx;
    on_ready();
    return true;
}

static IFileVolume* CreateVolumeImpl(QObject* parent, QString path, PageManager* pageManager)
{
    QDir dir(path);

    //    if(dir.exists() && dir.entryList(QDir::Files, QDir::Name).size() > 0) {
    if(dir.exists()) {
        return new IFileVolume(parent, qApp->ShowSubfolders() ? new FileLoaderSubDirectory(parent, path) : new FileLoaderDirectory(parent, path), pageManager);
    }
    QString lower = path.toLower();
    if(lower.endsWith(".zip") || lower.endsWith(".cbz")) {
        return new IFileVolume(parent, new FileLoaderZipArchive(parent, path), pageManager);
    }
    if(lower.endsWith(".7z")) {
        return new IFileVolume(parent, new FileLoader7zArchive(parent, path), pageManager);
    }
    if(lower.endsWith(".rar") || lower.endsWith(".cbr")) {
        return new IFileVolume(parent, new FileLoaderRarArchive(parent, path), pageManager);
    }
    if(IFileLoader::isImageFile(path)) {
        dir.cdUp();
        QString dirpath = dir.canonicalPath();
        IFileVolume* fvd = new IFileVolume(parent, qApp->ShowSubfolders() ? new FileLoaderSubDirectory(parent, path) : new FileLoaderDirectory(parent, dirpath), pageManager);
        fvd->findImageByName(path.mid(dirpath.length()+1));
        fvd->setOpenedWithSpecifiedImageFile(true);
        return fvd;
    }
    return nullptr;
}

IFileVolume* IFileVolume::CreateVolume(QObject* parent, QString path, PageManager* pageManager)
{
    QString pathbase = path;
    QString subfilename;
    if(path.contains("::")) {
        QStringList seps = path.split("::");
        pathbase = seps[0];
        subfilename = seps[1];
    }
    IFileVolume* fv = CreateVolumeImpl(parent, QDir::toNativeSeparators(pathbase), pageManager);
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

IFileVolume *IFileVolume::CreateVolumeWithOnlyCover(QObject *parent, QString path, PageManager* pageManager, CacheMode mode)
{
    IFileVolume* fv = CreateVolumeImpl(parent, QDir::toNativeSeparators(path), pageManager);
    if(!fv)
        return fv;
    if(fv->size() == 0) {
        delete fv;
        return nullptr;
    }
    fv->m_cacheMode = mode;
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


ImageContent IFileVolume::futureLoadImageFromFileVolume(IFileVolume* volume, QString path, QSize pageSize)
{
    int maxTextureSize = qApp->maxTextureSize();
    easyexif::EXIFInfo info;

    QByteArray bytes = volume->loadByteArrayByName(path);
    QBuffer buffer(&bytes);
    QString aformat = IFileLoader::isExifJpegImageFile(path) && IFileLoader::isImageFile("turbojpeg")
            ? TURBO_JPEG_FMT : QFileInfo(path.toLower()).suffix();

    // the image maybe a animated image
    if(IFileLoader::isAnimatedImageFile(path)) {
        Movie movie = Movie(bytes, aformat.toUtf8());
//        QMovie* qm = movie.data();
//        qDebug() << qm->isValid() << qm->jumpToFrame(0);
//        QPixmap firstFrame = qm->currentPixmap();
//        ImageContent ic(firstFrame, path, firstFrame.size(), info);
        ImageContent ic;
        ic.Path = path;
        ic.Movie = movie;
//        ic.Movie.moveToThread(qApp->mainThread());
        return ic;
    }

    // turbjpeg can turbo rescaling when loading
    QImageReader reader(&buffer, aformat.toUtf8());
    reader.canRead();
    QSize baseSize = reader.size();
    QSize loadingSize = baseSize;
    // qrawspeed plugin can also load rescaled raw images(using built in thumbnail),
    // but usualy thumbnails are too small, so we don't use
    if(aformat == TURBO_JPEG_FMT) {
        while(loadingSize.width() > maxTextureSize || loadingSize.height() > maxTextureSize)
            loadingSize = QSize((loadingSize.width()+1) >> 1,(loadingSize.height()+1) >> 1);
        reader.setScaledSize(loadingSize);
    }
    QImage src;
#ifdef Q_OS_WIN
    {
        QImage tmp = reader.read();
        src = QZimg::toPackedImage(tmp);
    }
#else
    src = reader.read();
#endif
    if(src.isNull()) {
        src = QImage::fromData(bytes, QFileInfo(path.toLower()).suffix().toUtf8());
    }

    // parsing JPEG EXIF
    if(src.width() > 0 && IFileLoader::isExifJpegImageFile(path)) {
        info.parseFrom(reinterpret_cast<const unsigned char*>(bytes.constData()), bytes.length());
    }

    if(src.width() > 0 && IFileLoader::isExifRawImageFile(path)) {
        parseExifTextExtents(src, info);
    }


    ImageContent ic(QPixmap::fromImage(src), path, baseSize, info);
    if(src.width() <= maxTextureSize && src.height() <= maxTextureSize) {
    } else {
        // resample for too big images
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

//        ImageContent ic(QPixmap::fromImage(half), path, srcSizeReal, info);
        ic.Image = QPixmap::fromImage(half);
        ic.ImportSize = srcSizeReal;
    }
    if(!pageSize.isEmpty() && !ic.Image.isNull()) {
        QSize newsize = ic.Info.Orientation==6 || ic.Info.Orientation==8 ? QSize(pageSize.height(), pageSize.width()) : pageSize;
        ic.ResizedImage = QPixmap::fromImage(QZimg::scaled(ic.Image.toImage(), newsize, Qt::KeepAspectRatio));
    }

    return ic;
}

ImageContent IFileVolume::futureReizeImage(ImageContent ic, QSize pageSize)
{
    QSize newsize = ic.Info.Orientation==6 || ic.Info.Orientation==8 ? QSize(pageSize.height(), pageSize.width()) : pageSize;
    ic.ResizedImage = QPixmap::fromImage(QZimg::scaled(ic.Image.toImage(), newsize, Qt::KeepAspectRatio));
    return ic;
}
