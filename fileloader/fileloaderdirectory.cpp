#include "fileloaderdirectory.h"
#include <QtConcurrent>

FileLoaderDirectory::FileLoaderDirectory(QObject* parent, QString path)
    : IFileLoader(parent)
    , m_volumepath(path)
    , m_valid(false)
{
    m_directory.setPath(path);
    if(!(m_valid = m_directory.exists()))
        return;

    initialize();
//    m_valid = true;
//    QtConcurrent::run(this, FileLoaderDirectory::initialize);
}

FileLoaderDirectory::FileLoaderDirectory(QObject *parent, QString path, int forsubclass)
    : IFileLoader(parent)
    , m_volumepath(path)
    , m_valid(false)
{

}


QByteArray FileLoaderDirectory::getFile(QString name, QMutex& )
{
    QByteArray bytes;
//    if(m_imageFileList.contains(name)) {
        const QString abso = m_directory.absoluteFilePath(name);
        QFile file(abso);
        file.open(QIODevice::ReadOnly);
        bytes = file.readAll();
        return bytes;
//    }
//    return bytes;
}

void FileLoaderDirectory::initialize()
{
    QStringList files;
    do {
        files = m_directory.entryList(QDir::Files, QDir::Name);
        m_subArchiveList = m_directory.entryList(QDir::AllDirs |QDir::NoDotAndDotDot);
        if(files.size()>0 || m_subArchiveList.size() == 0)
            break;
        if(m_subArchiveList.size() > 1)
            return;
        m_directory.setPath(m_directory.absoluteFilePath(m_subArchiveList[0]));
    } while(1);

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
    emit loadFinished();
}

