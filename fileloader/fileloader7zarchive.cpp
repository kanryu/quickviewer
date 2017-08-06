#include "fileloader7zarchive.h"
#include "qt7zpackage.h"
#include "qt7zfileinfo.h"

class FileLoader7zArchivePrivate
{
public:
    Qt7zPackage m_reader;
    QMap<QString, Qt7zFileInfo> m_fileinfomap;

    FileLoader7zArchivePrivate(QString sevenzippath)
     : m_reader(sevenzippath) {}
};

FileLoader7zArchive::FileLoader7zArchive(QObject* parent, QString sevenzippath)
    : IFileLoader(parent)
    , d(new FileLoader7zArchivePrivate(sevenzippath))
    , m_volumepath(sevenzippath)
    , m_valid(false)
{
    if(!(m_valid = d->m_reader.open()))
        return;
}

QStringList FileLoader7zArchive::contents()
{
    if(m_imageFileList.empty())
        initialize();
    return m_imageFileList;
}

void FileLoader7zArchive::initialize()
{
    foreach(const Qt7zFileInfo& info, d->m_reader.fileInfoList()) {
        if(!info.isDir) {
            if(IFileLoader::isImageFile(info.fileName)) {
                m_imageFileList.append(info.fileName);
                d->m_fileinfomap[info.fileName] = info;
            } else if(IFileLoader::isArchiveFile(info.fileName)) {
                m_subArchiveList.append(info.fileName);
                d->m_fileinfomap[info.fileName] = info;
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
    mutex.lock();
    if(m_imageFileList.contains(name)) {
        Qt7zFileInfo info = d->m_fileinfomap[name];

        QBuffer iobuffer(&bytes, this);
        iobuffer.open(QIODevice::WriteOnly);
        d->m_reader.extractFile(name, &iobuffer);
    }
    mutex.unlock();
    return bytes;
}

FileLoader7zArchive::~FileLoader7zArchive() {if(d){delete d;d=nullptr;}}
