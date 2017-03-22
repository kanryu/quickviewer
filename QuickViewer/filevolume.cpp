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
}

bool IFileVolume::nextPage()
{
    bool result = nextFile();
//    if(result) on_ready();
    return result;
}

bool IFileVolume::prevPage()
{
    bool result = prevFile();
//    if(result) on_ready();
    return result;
}

IFileVolume* IFileVolume::CreateVolume(QObject* parent, QString path)
{
    QDir dir(path);

    if(dir.exists()) {
        return new FileVolumeDirectory(parent, path);
    }
    QString lower = path.toLower();
    if(lower.endsWith(".zip")) {
        return new FileVolumeZipArchive(parent, path);
    }
    if(lower.endsWith(".7z")) {
        return new FileVolume7zArchive(parent, path);
    }
    if(isImageFile(path)) {
        dir.cdUp();
        QString dirpath = dir.canonicalPath();
        FileVolumeDirectory* fvd = new FileVolumeDirectory(parent, dirpath);
        bool result = fvd->findImageByName(path.mid(dirpath.length()+1));
        return fvd;
    }
    return nullptr;
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
