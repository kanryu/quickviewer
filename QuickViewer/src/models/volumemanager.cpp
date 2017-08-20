#include <QtGui>

#include "volumemanager.h"
#include "ResizeHalf.h"
#include "qvapplication.h"
#include "qzimg.h"
#include "pagemanager.h"
#include "fileloader.h"

static ImageContent pathThrough(ImageContent ic) { return ic; }

VolumeManager::VolumeManager(QObject *parent, IFileLoader* loader, PageManager* pageManager)
    : QObject(parent)
    , m_cnt(0)
    , m_loader(loader)
    , m_cacheMode(CacheMode::Normal)
    , m_pageManager(pageManager)
    , m_enumerated(false)
    , m_imageCache(qApp->MaxImagesCache())
    , m_openedWithSpecifiedImageFile(false)
{
    m_volumePath = m_loader->volumePath();
    connect(&m_watcher, SIGNAL(finished()), this, SLOT(on_enmumerated()));
}

VolumeManager::~VolumeManager() {
    m_imageCache.clear();
    if(m_loader) {
        delete m_loader;
        m_loader = nullptr;
    }
}

void VolumeManager::enumerate()
{
    m_filelist = m_loader->contents();
    m_enumerated = true;
}

ImageContent VolumeManager::getImageBeforeEnmumerate(QString subfilename)
{
    m_subfilename = subfilename;
    m_currentCacheSync = VolumeManager::futureLoadImageFromFileVolume(this, subfilename, QSize());
    m_watcher.setFuture(QtConcurrent::run(this, &VolumeManager::enumerate));
    return m_currentCacheSync;
}

void VolumeManager::on_enmumerated()
{
    m_imageCache.insert(m_filelist.indexOf(m_subfilename), QtConcurrent::run(pathThrough, m_currentCacheSync));
    findImageByName(m_subfilename);
    setCacheMode(VolumeManager::Normal);
    on_ready();
    m_pageManager->on_pageEnumerated();
}

void VolumeManager::on_ready()
{
    if(!m_enumerated)
        enumerate();
    if(m_cnt < 0 || m_cnt >= m_filelist.size() || m_loader->contents().size()==0)
        return;

//    qDebug() << "on_ready: m_cnt" << m_cnt;
    QList<int> offsets;
    switch(m_cacheMode) {
    case CacheMode::Normal:
        offsets = {0, 1, 2, 3, -1, -2, 4, 5, -3, -4, 6, 7, -5, -6};
        while(offsets.size() > qApp->MaxImagesCache())
            offsets.removeLast();
        break;
    case CacheMode::NormalForward:
        offsets = {10, 11, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7};
        if(offsets.size() > qApp->MaxImagesCache())  {
            QMutableListIterator<int> i(offsets);
            while (i.hasNext()) {
                if (i.next() >= qApp->MaxImagesCache())
                    i.remove();
            }
        }
        break;
    case CacheMode::NormalBackward:
        offsets = {-9, -10, -7, -8, 0, 1, -1, -2, -3, -4, -5, -6};
        if(offsets.size() > qApp->MaxImagesCache())  {
            QMutableListIterator<int> i(offsets);
            while (i.hasNext()) {
                if (i.next() < -qApp->MaxImagesCache()+2)
                    i.remove();
            }
        }
        break;
    case CacheMode::FastForward:
        offsets = {0, 1, 10, 11, -10, -9, 20, 21, -20, 19};
        while(offsets.size() > qApp->MaxImagesCache())
            offsets.removeLast();
        break;
    case CacheMode::CreateThumbnail:
        m_currentCacheSync = futureLoadImageFromFileVolume(this, 0, QSize());
        return;
    case CacheMode::CoverOnly:
        offsets = {0, 1};
        foreach (const int of, offsets) {
            int cnt = m_cnt+of;
            if(cnt < 0 || cnt >= m_filelist.size())
                continue;
            ImageContent ic = futureLoadImageFromFileVolume(this, m_filelist[cnt], QSize());
            m_imageCache.insert(cnt, QtConcurrent::run(pathThrough, ic));
        }
        return;
    }
    foreach (const int of, offsets) {
        int cnt = m_cnt+of;
        if(cnt < 0 || cnt >= m_filelist.size())
            continue;
        if(qApp->Effect() < qvEnums::UsingFixedShader && m_imageCache.contains(cnt) && m_imageCache.object(cnt).isFinished() ) {
            ImageContent ic = m_imageCache.object(cnt).result();
            if(ic.ImportSize.isValid()) {
                QSize pageSize = m_pageManager->viewportSize();
                QSize resized = ic.Info.Orientation==6 || ic.Info.Orientation==8 ? QSize(pageSize.height(), pageSize.width()) : pageSize;
                resized.setWidth(ic.ImportSize.width()*resized.height()/ic.ImportSize.height());

                if(ic.ResizedImage.size() != resized && !ic.Image.isNull()) {
                    qDebug() << ic.ResizedImage.size() << resized;
                    m_imageCache.insert(cnt, QtConcurrent::run(futureReizeImage, ic, m_pageManager->viewportSize()));
                }
            }
        }
        if(m_imageCache.checkShouldBeInserted(cnt)) {
//            qDebug() << "on_ready()" << m_filelist[cnt];
            m_imageCache.insertNoChecked(cnt, QtConcurrent::run(
                 futureLoadImageFromFileVolume,
                 this,
                 m_filelist[cnt],
                 (m_pageManager && qApp->Effect() < qvEnums::UsingFixedShader)
                     ? m_pageManager->viewportSize()
                     : QSize())
            );
        }
    }
    m_currentCache = m_imageCache.object(m_cnt);
}

const ImageContent VolumeManager::getIndexedImageContent(int idx)
{
//    future_image cache = m_imageCache[idx];
    future_image& cache = m_imageCache.object(idx);
//    if(!cache.isFinished())
//        cache.waitForFinished();
    return cache.result();
}

void VolumeManager::moveToThread(QThread *targetThread)
{
    QObject::moveToThread(targetThread);
    m_loader->moveToThread(targetThread);
}

bool VolumeManager::nextPage()
{
//    qDebug() << "nextPage: " << m_cnt << m_filelist.size() <<  "prevCache.size()" << m_prevCache.size() << "nextCache.size()" << m_nextCache.size();
    if(m_cnt >= m_filelist.size() || m_loader->contents().size()==0)
        return false;
    m_cnt++;
    on_ready();
    return true;
}

bool VolumeManager::prevPage()
{
//    qDebug() << "prevPage: " << m_cnt << m_filelist.size() <<  "prevCache.size()" << m_prevCache.size() << "nextCache.size()" << m_nextCache.size();
    if(m_cnt <= 0 || m_loader->contents().size()==0)
        return false;
    m_cnt--;
    on_ready();
    return true;
}

bool VolumeManager::findPageByIndex(int idx)
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

bool VolumeManager::findImageByIndex(int idx) {
    if(idx < 0 || idx >= m_filelist.size())
        return false;
    m_cnt = idx;
    on_ready();
    return true;
}

bool VolumeManager::findImageByName(QString name) {
    int idx = m_filelist.indexOf(name);
    if(idx < 0)
        return false;
    m_cnt = idx;
    on_ready();
    return true;
}

QString VolumeManager::FullPathToVolumePath(QString path)
{
    if(!path.contains("::")) {
        return path;
    }
    return path.left(path.indexOf("::"));
}

QString VolumeManager::FullPathToSubFilePath(QString path)
{
    if(!path.contains("::")) {
        return "";
    }
    return path.mid(path.indexOf("::")+2);
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


static ImageContent loadWithSpecifiedFormat(QString path, QSize pageSize, QByteArray bytes, QString aformat)
{
    for(;;) {
        int maxTextureSize = qApp->MaxTextureSize();
        easyexif::EXIFInfo info;
        QBuffer buffer(&bytes);
        QImageReader reader(&buffer, aformat.toUtf8());

//        QElapsedTimer et_canRead; et_canRead.start();
        if(!reader.canRead()) {
            aformat = "";
            break;
        }
//        qint64 t_canRead = et_canRead.elapsed();
//        // Emptying the format of QImageReader will get the format of the internal QImageIoHandler
//        reader.setFormat("");

//        QElapsedTimer et_supportsAnimation; et_supportsAnimation.start();
        if(reader.supportsAnimation()) {
            QvMovie movie = QvMovie(bytes, aformat.toUtf8());
            ImageContent ic;
            ic.Path = path;
            ic.Movie = movie;
            ic.BaseSize = ic.ImportSize = reader.size();
            return ic;
        }
//        qint64 t_supportsAnimation = et_supportsAnimation.elapsed();
//        qDebug() << path << t_canRead << t_supportsAnimation;

        if(aformat == "apng") {
            bool lodepng_exist = IFileLoader::isImageFile("lodepng");
            aformat = lodepng_exist ? "lodepng" : "png";
            break;
        }
        // turbjpeg can turbo rescaling when loading
        QSize baseSize = reader.size();
        QSize loadingSize = baseSize;
        // qrawspeed plugin can also load rescaled raw images(using built in thumbnail),
        // but usualy thumbnails are too small, so we don't use
        if(reader.format() == TURBO_JPEG_FMT) {
            while(loadingSize.width() > maxTextureSize || loadingSize.height() > maxTextureSize)
                loadingSize = QSize((loadingSize.width()+1) >> 1,(loadingSize.height()+1) >> 1);
            reader.setScaledSize(loadingSize);
        }
        QImage src;
        {
            QImage tmp;
            // QImage processing sometimes fails
            for(int count = 1; ; count++) {
                tmp = reader.read();
                if(!tmp.isNull()) break;
                qDebug() << "[0]" << path << tmp << count;
                if(count >= 100) return ImageContent();
                QThread::currentThread()->usleep(40000);
            }
            src = QZimg::toPackedImage(tmp);
            if(src.isNull()) return ImageContent();
        }

        // parsing JPEG EXIF
        if(src.width() > 0 && IFileLoader::isExifJpegImageFile(path)) {
            info.parseFrom(reinterpret_cast<const unsigned char*>(bytes.constData()), bytes.length());
        }

        if(src.width() > 0 && IFileLoader::isExifRawImageFile(path)) {
            parseExifTextExtents(src, info);
        }


    //    ImageContent ic(QPixmap::fromImage(src), path, baseSize, info);
        ImageContent ic;
        ic.Path = path;
        ic.BaseSize = baseSize;
        ic.Info = info;
        if(src.isNull())
            return ic;
        if(src.width() <= maxTextureSize && src.height() <= maxTextureSize) {
            ic = ImageContent(src, path, baseSize, info);;
        } else {
            // resample for too big images
            QSize srcSizeReal = src.size();
            QImage src2;
            switch(src.depth()) {
            case 32:
                if((src.width() | 0x3) > 0) {
                    // QImage processing sometimes fails
                    for(int count = 1; ; count++) {
                        src2 = src.copy(QRect(0, 0, src.width() >> 2 << 2, src.height() >> 1 << 1));
                        if(!src2.isNull()) break;
                        qDebug() << "[2]" << path << src2 << count;
                        if(count >= 100) return ImageContent();
                        QThread::currentThread()->usleep(40000);
                    }
                    src.swap(src2);
                }
                break;
            default:
                if(src.format() != QImage::Format::Format_Grayscale8 && src.format() != QImage::Format::Format_RGB888) {
                    src = src.convertToFormat(QImage::Format::Format_RGB888);
                }
                if((src.width() | 0xF) > 0) {
                    // QImage processing sometimes fails
                    int count = 0;
                    do {
                        src2 = src.copy(QRect(0, 0, src.width() >> 4 << 4, src.height() >> 1 << 1));
                        qDebug() << "[2]" << path << src2 << count;
                        if(!src2.isNull())
                            break;
                        if(src2.isNull() && count++ < 1000) {
                            QThread::currentThread()->usleep(1000);
                            continue;
                        }
                        return ImageContent();
                    } while(1);
                    src.swap(src2);
                }
                break;
            }

            QSize srcSize = src.size();
            QSize halfSize = QSize((srcSize.width())/2, (srcSize.height())/2);

            //qDebug() << path << "[3]width:" << srcSize;
            QImage half = QImage(halfSize.width(), halfSize.height(), src.format());
            //qDebug() << path << "[2]Dest:" <<  half;

    //        qDebug() << path << src;
            ResizeHalf::FMT fmt = (ResizeHalf::FMT)(src.depth() >> 3);
            ResizeHalf resizer(fmt);
            resizer.resizeHV(half.bits(), src.bits(), src.width(), srcSize.height(), half.bytesPerLine(), src.bytesPerLine());

    //        ImageContent ic(QPixmap::fromImage(half), path, srcSizeReal, info);
            ic.Image = half;
            ic.ImportSize = srcSizeReal;
        }
        // CPU resizing before Page Viewing
        if(!pageSize.isEmpty() && !ic.Image.isNull()) {
            QSize newsize = ic.Info.Orientation==6 || ic.Info.Orientation==8 ? QSize(pageSize.height(), pageSize.width()) : pageSize;
            ic.ResizedImage = QZimg::scaled(ic.Image, newsize, Qt::KeepAspectRatio);
        }
        return ic;
    }
    return loadWithSpecifiedFormat(path, pageSize, bytes, aformat);
}



static ImageContent futureLoadImageFromFileVolumeImpl(VolumeManager* volume, QString path, QSize pageSize)
{
//    qDebug() << "futureLoadImageFromFileVolume" << path << QThread::currentThread();

    QByteArray bytes = volume->loadByteArrayByName(path);
    QString aformat = IFileLoader::isExifJpegImageFile(path) && IFileLoader::isImageFile("turbojpeg")
            ? TURBO_JPEG_FMT : QFileInfo(path.toLower()).suffix();
    // extention "png" might be a apng
    if(aformat == "png" && IFileLoader::isImageFile("apng")) {
        aformat = "apng";
    }
//    if(aformat == "png") {
//        bool lodepng_exist = IFileLoader::isImageFile("lodepng");
//        aformat = lodepng_exist ? "lodepng" : "png";
//    }
    return loadWithSpecifiedFormat(path, pageSize, bytes, aformat);
}

ImageContent VolumeManager::futureLoadImageFromFileVolume(VolumeManager* volume, QString path, QSize pageSize)
{
    QElapsedTimer et_load; et_load.start();
    ImageContent ic = futureLoadImageFromFileVolumeImpl(volume, path, pageSize);
    qint64 t_load = et_load.elapsed();

    qDebug() << "futureLoadImageFromFileVolume" << path << t_load << "ms, ResizedImage=" << !ic.ResizedImage.isNull();
    return ic;
}

ImageContent VolumeManager::futureReizeImage(ImageContent ic, QSize pageSize)
{
//    qDebug() << "futureReizeImage:" << ic.Path;
    QSize newsize = ic.Info.Orientation==6 || ic.Info.Orientation==8 ? QSize(pageSize.height(), pageSize.width()) : pageSize;
    ic.ResizedImage = QZimg::scaled(ic.Image, newsize, Qt::KeepAspectRatio);
    return ic;
}

