#include "fileloader.h"
#include <algorithm>
#include <QImageReader>
#include <QDebug>

#ifdef Q_OS_WIN
#include <Shlwapi.h>
#endif

QList<QByteArray> IFileLoader::st_supportedImageFormats;
QStringList IFileLoader::st_exifJpegImageFormats;
QStringList IFileLoader::st_exifRawImageFormats;
QStringList IFileLoader::st_animatedImageFormats;

bool IFileLoader::isImageFile(QString path)
{
    if(st_supportedImageFormats.size() == 0) {
        st_exifJpegImageFormats << "jpg" << "jpeg"; // standard
        st_exifRawImageFormats << "crw" << "cr2" << "arw" << "nef" << "raf" << "dng" << "tif" << "tiff"; // raw images
        st_animatedImageFormats << "gif" << "apng";
        st_supportedImageFormats = QImageReader::supportedImageFormats();
//        foreach(const QString& e, st_supportedImageFormats) {
//            qDebug()<<  QString(e);
//        }
#ifdef QT_DEBUG
        qDebug() << st_supportedImageFormats;
#endif
    }
//    QStringList exts = {".jpg", ".jpeg", ".bmp", ".gif", ".png", ".dds", ".ico", ".tga", ".tif", ".tiff", ".webp", ".wbp"};
    QString lower = path.toLower().mid(path.lastIndexOf(".")+1);
    foreach(const QString& e, st_supportedImageFormats) {
        if(lower == e)
            return true;
    }
    return false;
}

bool IFileLoader::isArchiveFile(QString path)
{
    QStringList exts = {".zip", ".7z", ".rar", ".cbr", ".cbz"};
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

bool IFileLoader::isAnimatedImageFile(QString path)
{
    QString lower = path.toLower();
    foreach(const QString& e, st_animatedImageFormats) {
        if(lower.endsWith(e))
            return true;
    }
    return false;
}

void IFileLoader::sortFiles(QStringList &filenames)
{
//    qSort(filenames.begin(), filenames.end(), caseInsensitiveLessThan);
    std::sort(filenames.begin(), filenames.end(), caseInsensitiveLessThan);
}

#ifdef Q_OS_WIN
// Windows Filename sorting is not usual caseInsensitive, so call Win32Api
// to see https://msdn.microsoft.com/ja-jp/library/windows/desktop/bb759947(v=vs.85).aspx
bool IFileLoader::caseInsensitiveLessThan(const QString &s1, const QString &s2)
{
    std::wstring ss1(s1.toStdWString());
    std::wstring ss2(s2.toStdWString());
    return ::StrCmpLogicalW(ss1.c_str(), ss2.c_str()) < 0;
}
#else
bool IFileLoader::caseInsensitiveLessThan(const QString &s1, const QString &s2)
{
    return s1.toLower() < s2.toLower();
}
#endif

