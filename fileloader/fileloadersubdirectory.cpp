#include "fileloadersubdirectory.h"

FileLoaderSubDirectory::FileLoaderSubDirectory(QObject* parent, QString path)
    : FileLoaderDirectory(parent, path, 1)
{
    m_directory.setPath(path);
    if(!(m_valid = m_directory.exists()))
        return;

    initialize();
}

void FileLoaderSubDirectory::initialize()
{
    getFilesWithSubdirs(m_directory.path(), "");
    m_valid = true;
}

void FileLoaderSubDirectory::getFilesWithSubdirs(QString path, QString subpath)
{
    QStringList files, imgs, subdirs;
    QDir subdir(subpath);
    QDir dir(path);
    files = dir.entryList(QDir::Files, QDir::Name);
    foreach(const QString name, files) {
        if(IFileLoader::isImageFile(name)) {
            imgs.append(QDir::toNativeSeparators(subpath.isEmpty() ? name : subdir.filePath(name)));
        }
    }
    subdirs = dir.entryList(QDir::AllDirs |QDir::NoDotAndDotDot);
    IFileLoader::sortFiles(imgs);
    IFileLoader::sortFiles(subdirs);
    m_imageFileList.append(imgs);

    foreach(const QString& sub, subdirs) {
        getFilesWithSubdirs(dir.filePath(sub), subpath.isEmpty() ? sub : subdir.filePath(sub));
    }
}
