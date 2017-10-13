#include "fileloader7zarchive.h"
#include "qt7zpackage.h"
#include "qt7zfileinfo.h"

class FileLoader7zArchivePrivate
{
public:
    Qt7zPackage m_reader;
    QMap<QString, Qt7zFileInfo> m_fileinfomap;
    QTemporaryFile m_tempFile;

    FileLoader7zArchivePrivate(QString sevenzippath)
     : m_reader(sevenzippath) {}
};

FileLoader7zArchive::FileLoader7zArchive(QObject* parent, QString sevenzippath, bool extractSolidArchiveToTemporaryDir)
    : IFileLoader(parent)
    , d(new FileLoader7zArchivePrivate(sevenzippath))
    , m_volumepath(sevenzippath)
    , m_valid(false)
    , m_extractSolidArchiveToTemporaryDir(extractSolidArchiveToTemporaryDir)
    , m_temp(nullptr)
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

static uint s_archiveCnt;

void FileLoader7zArchive::initialize()
{
    foreach(const Qt7zFileInfo& info, d->m_reader.fileInfoList()) {
        if(!info.isDir) {
            QString filename = QDir::toNativeSeparators(info.fileName);
            if(IFileLoader::isImageFile(filename)) {
                m_imageFileList.append(filename);
                d->m_fileinfomap[filename] = info;
            } else if(IFileLoader::isArchiveFile(filename)) {
                m_subArchiveList.append(filename);
                d->m_fileinfomap[filename] = info;
            }
        }
    }
    IFileLoader::sortFiles(m_imageFileList);
    IFileLoader::sortFiles(m_subArchiveList);
    if(m_extractSolidArchiveToTemporaryDir && d->m_reader.isSolid()) {
        QString tempdir = QString("%1/qv_%2").arg(QDir::tempPath()).arg(++s_archiveCnt, 3, 10, QLatin1Char('0'));
        d->m_reader.extractToDir(QDir::toNativeSeparators(tempdir));
    }
    m_valid = true;
}

QByteArray FileLoader7zArchive::getFile(QString name, QMutex& mutex)
{
    QByteArray bytes;
    mutex.lock();
    if(m_imageFileList.contains(name)) {
        Qt7zFileInfo info = d->m_fileinfomap[name];

        QBuffer iobuffer(&bytes);
        iobuffer.open(QIODevice::WriteOnly);
        d->m_reader.extractFile(info.fileName, &iobuffer);
    }
    mutex.unlock();
    return bytes;
}

FileLoader7zArchive::~FileLoader7zArchive() {if(d){delete d;d=nullptr;}}
