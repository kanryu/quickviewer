#include <QtDebug>
#include "fileloaderziparchive.h"

FileLoaderZipArchive::FileLoaderZipArchive(QObject* parent, QString zippath)
    : IFileLoader(parent)
    , m_reader(zippath)
    , m_volumepath(zippath)
    , m_valid(false)
{
    if(!(m_valid = m_reader.exists()))
        return;

    foreach(const QZipReader::FileInfo& info, m_reader.fileInfoList()) {
        if(!info.isFile)
            continue;
        if(IFileLoader::isImageFile(info.filePath)) {
            m_imageFileList.append(info.filePath);
        } else if(IFileLoader::isArchiveFile(info.filePath)) {
            m_subArchiveList.append(info.filePath);
        }
    }
    IFileLoader::sortFiles(m_imageFileList);
    IFileLoader::sortFiles(m_subArchiveList);
    m_valid = true;
}

QByteArray FileLoaderZipArchive::getFile(QString name, QMutex& mutex)
{
    QByteArray bytes;
    if(m_imageFileList.contains(name)) {
        mutex.lock();
        bytes = m_reader.fileData(name);
        mutex.unlock();
    }
    return bytes;
}
