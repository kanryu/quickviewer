#include "fileloader.h"

bool IFileLoader::isImageFile(QString path)
{
    QStringList exts = {".jpg", ".jpeg", ".bmp", ".gif", ".png", ".dds", ".ico", ".tga", ".tif", ".tiff", ".webp", ".wbp"};
    QString lower = path.toLower();
    foreach(const QString& e, exts) {
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

void IFileLoader::sortFiles(QStringList &filenames)
{
    qSort(filenames);
}

