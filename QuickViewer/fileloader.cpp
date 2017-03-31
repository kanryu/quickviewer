#include "fileloader.h"
#include <QImageReader>
#include <QDebug>

QList<QByteArray> IFileLoader::st_supportedImageFormats;
QStringList IFileLoader::st_exifJpegImageFormats;
QStringList IFileLoader::st_exifRawImageFormats;

bool IFileLoader::isImageFile(QString path)
{
    if(st_supportedImageFormats.size() == 0) {
        st_exifJpegImageFormats << "jpg" << "jpeg"; // standard
        st_exifRawImageFormats << "crw" << "cr2" << "arw" << "nef" << "raf" << "dng" << "tif" << "tiff"; // raw images
        st_supportedImageFormats = QImageReader::supportedImageFormats();
        foreach(const QString& e, st_supportedImageFormats) {
            qDebug() << QString(e);
        }
    }
//    QStringList exts = {".jpg", ".jpeg", ".bmp", ".gif", ".png", ".dds", ".ico", ".tga", ".tif", ".tiff", ".webp", ".wbp"};
    QString lower = path.toLower();
    foreach(const QString& e, st_supportedImageFormats) {
        if(lower.endsWith(e))
            return true;
    }
    return false;
}

bool IFileLoader::isArchiveFile(QString path)
{
    QStringList exts = {".zip", ".7z", ".rar"};
    QString lower = path.toLower();
    foreach(const QString& e, exts) {
        if(lower.endsWith(e))
            return true;
    }
    return false;
}

bool IFileLoader::isExifJpegImageFile(QString path)
{
    QString lower = path.toLower();
    foreach(const QString& e, st_exifJpegImageFormats) {
        if(lower.endsWith(e))
            return true;
    }
    return false;
}

bool IFileLoader::isExifRawImageFile(QString path)
{
    QString lower = path.toLower();
    foreach(const QString& e, st_exifRawImageFormats) {
        if(lower.endsWith(e))
            return true;
    }
    return false;
}

void IFileLoader::sortFiles(QStringList &filenames)
{
    qSort(filenames);
}

