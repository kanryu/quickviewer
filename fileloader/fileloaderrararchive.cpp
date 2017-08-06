#include "fileloaderrararchive.h"
#include "rarextractor.h"

FileLoaderRarArchive::FileLoaderRarArchive(QObject* parent, QString rarpath)
    : IFileLoader(parent)
//    , m_archive(rarpath)
    , m_volumepath(rarpath)
    , m_valid(false)
    , d(new RarExtractor(rarpath))
{
    if(!(m_valid = d->open(RarExtractor::OpenModeList, "")))
        return;
}

QStringList FileLoaderRarArchive::contents()
{
    if(m_imageFileList.empty())
        initialize();
    return m_imageFileList;
}

void FileLoaderRarArchive::initialize()
{
    foreach(const QString& name, d->fileNameList()) {
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
    mutex.lock();
    if(m_imageFileList.contains(name)) {
        bytes = d->fileData(name);
    }
    mutex.unlock();
    return bytes;
}

