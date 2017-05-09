#include "fileloaderdirectory.h"


FileLoaderDirectory::FileLoaderDirectory(QObject* parent, QString path)
    : IFileLoader(parent)
    , m_volumepath(path)
    , m_valid(false)
{
    m_directory.setPath(path);
    if(!(m_valid = m_directory.exists()))
        return;

    QStringList files = m_directory.entryList(QDir::Files, QDir::Name);
    m_subArchiveList = m_directory.entryList(QDir::Dirs, QDir::Name);

    foreach(const QString name, files) {
        if(IFileLoader::isImageFile(name)) {
            m_imageFileList.append(name);
        } else if(IFileLoader::isArchiveFile(name)) {
            m_subArchiveList.append(name);
        }
    }
    IFileLoader::sortFiles(m_imageFileList);
    IFileLoader::sortFiles(m_subArchiveList);
    m_valid = true;
}

QByteArray FileLoaderDirectory::getFile(QString name, QMutex& )
{
    QByteArray bytes;
    if(m_imageFileList.contains(name)) {
        const QString abso = m_directory.absoluteFilePath(name);
        QFile file(abso);
        file.open(QIODevice::ReadOnly);
        bytes = file.readAll();
        return bytes;
    }
    return bytes;
}

