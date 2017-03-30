#include "fileloaderrararchive.h"
#include "qtrarfile.h"

FileLoaderRarArchive::FileLoaderRarArchive(QObject* parent, QString rarpath)
    : IFileLoader(parent)
    , m_archive(rarpath)
    , m_volumepath(rarpath)
    , m_valid(false)
{
    if(!(m_valid = m_archive.open(QtRAR::OpenModeExtract)))
        return;

    foreach(const QString& name, m_archive.fileNameList()) {
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

QByteArray FileLoaderRarArchive::getFile(QString name, QMutex& mutex)
{
    QByteArray bytes;
    if(m_imageFileList.contains(name)) {
        mutex.lock();
        QtRARFile file(&m_archive);
        file.setFileName(name);
        file.open(QIODevice::ReadOnly);
        bytes = file.readAll();
        mutex.unlock();
    }
    return bytes;
}

