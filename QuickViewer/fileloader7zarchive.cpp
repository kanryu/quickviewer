#include "fileloader7zarchive.h"


FileLoader7zArchive::FileLoader7zArchive(QObject* parent, QString sevenzippath)
    : IFileLoader(parent)
    , m_reader(sevenzippath)
    , m_volumepath(sevenzippath)
    , m_valid(false)
{
    if(!(m_valid = m_reader.open()))
        return;

    foreach(const Qt7zFileInfo& info, m_reader.fileInfoList()) {
        if(!info.isDir) {
            if(IFileLoader::isImageFile(info.fileName)) {
                m_imageFileList.append(info.fileName);
                m_fileinfomap[info.fileName] = info;
            } else if(IFileLoader::isArchiveFile(info.fileName)) {
                m_subArchiveList.append(info.fileName);
                m_fileinfomap[info.fileName] = info;
            }
        }
    }
    IFileLoader::sortFiles(m_imageFileList);
    IFileLoader::sortFiles(m_subArchiveList);
    m_valid = true;
}

QByteArray FileLoader7zArchive::getFile(QString name, QMutex& mutex)
{
    QByteArray bytes;
    if(m_imageFileList.contains(name)) {
        mutex.lock();
        Qt7zFileInfo info = m_fileinfomap[name];

        QBuffer iobuffer(&bytes, this);
        iobuffer.open(QIODevice::WriteOnly);
        bool result = m_reader.extractFile(name, &iobuffer);
        mutex.unlock();
    }
    return bytes;
}

