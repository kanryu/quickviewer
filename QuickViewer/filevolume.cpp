#include "filevolume.h"
#include <QDir>
#include "filevolumedirectory.h"
#include "filevolumeziparchive.h"
#include "filevolume7zarchive.h"

void IFileVolume::on_ready()
{
    emit changing(currentImage());
    emit changed(currentPath());
}

bool IFileVolume::nextPage()
{
    bool result = nextFile();
    if(result) on_ready();
    return result;
}

bool IFileVolume::prevPage()
{
    bool result = prevFile();
    if(result) on_ready();
    return result;
}

IFileVolume* IFileVolume::CreateVolume(QObject* parent, QString path)
{
    QDir dir(path);

    if(dir.exists()) {
        return new FileVolumeDirectory(parent, path);
    }
    if(path.toLower().endsWith(".zip")) {
        return new FileVolumeZipArchive(parent, path);
    }
    if(path.toLower().endsWith(".7z")) {
        return new FileVolume7zArchive(parent, path);
    }
    return nullptr;
}
