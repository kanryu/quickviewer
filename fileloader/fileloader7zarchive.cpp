#ifdef _WIN32
#include <windows.h>
#endif
#include <iostream>

#include <QtCore>
#include "fileloader7zarchive.h"
#include <lib7zip.h>

using namespace lib7zip;


class Qt7zStreamReader : public C7ZipInStream
{
private:
    QIODevice *m_inStream;
    std::string m_strFileName;
    wstring m_strFileExt;
    int m_nFileSize;
public:
    Qt7zStreamReader(std::string fileName) :
        m_inStream(nullptr),
        m_strFileName(fileName),
        m_strFileExt(L"7z")
    {
    }

    virtual ~Qt7zStreamReader()
    {
    }
    void setFile(QIODevice *inStream) {
        m_inStream = inStream;
    }
    virtual wstring GetExt() const
    {
        wprintf(L"GetExt:%ls\n", m_strFileExt.c_str());
        return m_strFileExt;
    }

    virtual int Read(void *data, unsigned int size, unsigned int *processedSize)
    {
        if (!m_inStream)
            return 1;
        auto readBytes = m_inStream->read((char*)data, size);

        wprintf(L"Read:%d %d\n", size, readBytes);

        if (readBytes >= 0) {
            if (processedSize != nullptr)
                *processedSize = readBytes;

            return 0;
        }

        return 1;
    }

    virtual int Seek(__int64 offset, unsigned int seekOrigin, unsigned __int64 *newPosition)
    {
        bool result = false;
        if(!m_inStream)
            return 1;
        switch(seekOrigin) {
        case SEEK_SET:
            result = m_inStream->seek(offset);
            break;
        case SEEK_CUR:
            {
                auto pos = m_inStream->pos();
                result = m_inStream->seek(pos+offset);
                break;
            }
        case SEEK_END:
            {
                auto sz = m_inStream->size();
                result = m_inStream->seek(sz+offset);
                break;
            }
        }
        if(newPosition) {
            qint64 pos2 = m_inStream->pos();
            *newPosition = pos2;
        }
        return result == true ? 0 : 1;
    }

    virtual int GetSize(unsigned __int64 * size)
    {
        if (size)
            *size = m_inStream->size();
        return 0;
    }
};

/** Used by lib7zip to write binary streams.
 *  Specifically, it is used when expanding from 7z content files.
 */
class Qt7zStreamWriter : public C7ZipOutStream
{
private:
    QIODevice *m_outStream;
    QString m_strFileName;
    wstring m_strFileExt;
    int m_nFileSize;
public:
    Qt7zStreamWriter(QIODevice *outStream, QString fileName) :
      m_outStream(outStream),
      m_strFileName(fileName),
      m_strFileExt(L"7z")
    {
    }

    virtual ~Qt7zStreamWriter()
    {
    }

    int GetFileSize() const
    {
        return m_outStream->size();
    }

    virtual int Write(const void *data, unsigned int size, unsigned int *processedSize)
    {
        auto writeBytes = m_outStream->write((char*)data, size);
        wprintf(L"Write:%d %d\n", size, writeBytes);

        if (writeBytes >= 0)
        {
            if (processedSize != NULL)
                *processedSize = writeBytes;

            m_nFileSize += writeBytes;
            return 0;
        }

        return 1;
    }

    virtual int Seek(__int64 offset, unsigned int seekOrigin, unsigned __int64 *newPosition)
    {
        bool result = false;
        switch(seekOrigin) {
        case SEEK_SET:
            result = m_outStream->seek(offset);
            break;
        case SEEK_CUR:
            {
                qint64 pos = m_outStream->pos();
                result = m_outStream->seek(pos+offset);
                break;
            }
        case SEEK_END:
            {
                auto sz = m_outStream->size();
                result = m_outStream->seek(sz+offset);
                break;
            }
        }
        if(newPosition) {
            qint64 pos2 = m_outStream->pos();
            *newPosition = pos2;
        }
        return result == true ? 0 : 1;
    }

    virtual int SetSize(unsigned __int64 size)
    {
        wprintf(L"SetFileSize:%ld\n", size);
        return 0;
    }
};

const wchar_t * index_names[] = {
        L"kpidPackSize", //(Packed Size)
        L"kpidAttrib", //(Attributes)
        L"kpidCTime", //(Created)
        L"kpidATime", //(Accessed)
        L"kpidMTime", //(Modified)
        L"kpidSolid", //(Solid)
        L"kpidEncrypted", //(Encrypted)
        L"kpidUser", //(User)
        L"kpidGroup", //(Group)
        L"kpidComment", //(Comment)
        L"kpidPhySize", //(Physical Size)
        L"kpidHeadersSize", //(Headers Size)
        L"kpidChecksum", //(Checksum)
        L"kpidCharacts", //(Characteristics)
        L"kpidCreatorApp", //(Creator Application)
        L"kpidTotalSize", //(Total Size)
        L"kpidFreeSpace", //(Free Space)
        L"kpidClusterSize", //(Cluster Size)
        L"kpidVolumeName", //(Label)
        L"kpidPath", //(FullPath)
        L"kpidIsDir", //(IsDir)
};

static C7ZipLibrary* c7zipLib = nullptr;
static bool c7ziplib_alive = true;

bool FileLoader7zArchive::initializeLib()
{
    if(!c7zipLib) {
        c7zipLib = new C7ZipLibrary();
        c7ziplib_alive = c7zipLib->Initialize();
        return c7ziplib_alive;
    }
    return false;
}

bool FileLoader7zArchive::isInitialized()
{
    return c7zipLib && c7ziplib_alive;
}

void FileLoader7zArchive::uninitializeLib()
{
    if(c7zipLib) {
        delete c7zipLib;
        c7zipLib = nullptr;
    }
}

struct Qt7zFileInfo
{
    QString fileName;
    QString arcName;
    quint64 size;
    size_t pre_total;
    bool isDir;
    bool isCrcDefined;
    quint32 crc;
    bool isEncrypted;
};

static Qt7zFileInfo fromC7ZipArchiveItem(C7ZipArchiveItem& item, QString packagePath, size_t pre_total) {
    Qt7zFileInfo prop;
    std::wstring strVal;
//    item.GetStringProperty(PropertyIndexEnum::kpidSolid, strVal);
//    prop.Comment = QString::fromStdWString(strVal);
//    item.GetStringProperty(PropertyIndexEnum::kpidCharacts, strVal);
//    prop.Characteristics = QString::fromStdWString(strVal);
//    item.GetStringProperty(PropertyIndexEnum::kpidCreatorApp, strVal);
//    prop.CreatorApplication = QString::fromStdWString(strVal);
//    item.GetStringProperty(PropertyIndexEnum::kpidVolumeName, strVal);
//    prop.Label = QString::fromStdWString(strVal);
    item.GetStringProperty(PropertyIndexEnum::kpidPath, strVal);
    QString filename = QString::fromStdWString(strVal);
    prop.fileName = QDir::fromNativeSeparators(filename);
    prop.arcName = packagePath;
//    item.GetStringProperty(PropertyIndexEnum::kpidUser, strVal);
//    prop.User = QString::fromStdWString(strVal);
//    item.GetStringProperty(PropertyIndexEnum::kpidGroup, strVal);
//    prop.Group = QString::fromStdWString(strVal);

    uint64_t uintval;
    item.GetUInt64Property(PropertyIndexEnum::kpidSize, uintval);
    prop.size = (size_t) uintval;
    prop.pre_total = (size_t) pre_total;
//    item.GetUInt64Property(PropertyIndexEnum::kpidPackSize, prop.PackSize);
//    item.GetUInt64Property(PropertyIndexEnum::kpidAttrib, prop.Attributes);
//    item.GetUInt64Property(PropertyIndexEnum::kpidPhySize, prop.PhysicalSize);
//    item.GetUInt64Property(PropertyIndexEnum::kpidHeadersSize, prop.HeadersSize);
    item.GetUInt64Property(PropertyIndexEnum::kpidChecksum, uintval);
    prop.crc = quint32(uintval);
    prop.isCrcDefined = false;
//    item.GetUInt64Property(PropertyIndexEnum::kpidTotalSize, prop.TotalSize);
//    item.GetUInt64Property(PropertyIndexEnum::kpidFreeSpace, prop.FreeSpace);
//    item.GetUInt64Property(PropertyIndexEnum::kpidClusterSize, prop.ClusterSize);

//    item.GetFileTimeProperty(PropertyIndexEnum::kpidCTime, prop.Created);
//    item.GetFileTimeProperty(PropertyIndexEnum::kpidATime, prop.Accessed);
//    item.GetFileTimeProperty(PropertyIndexEnum::kpidMTime, prop.Modified);

//    item.GetBoolProperty(PropertyIndexEnum::kpidSolid, prop.IsSolid);
    item.GetBoolProperty(PropertyIndexEnum::kpidEncrypted, prop.isEncrypted);
    item.GetBoolProperty(PropertyIndexEnum::kpidIsDir, prop.isDir);
    return prop;
}

class FileLoader7zArchivePrivate
{
public:
    QString m_packagePath;
    C7ZipArchive* m_pArchive;
    Qt7zStreamReader stream;
    QMap<QString, Qt7zFileInfo> m_fileinfomap;
    QTemporaryFile m_tempFile;
    QList<Qt7zFileInfo> m_fileInfoList;
    QStringList m_fileNameList;
    QHash<QString, uint32_t> m_fileNameToIndex;
    QFile m_archiveFile;

    FileLoader7zArchivePrivate(QString sevenzippath)
        : m_packagePath(sevenzippath)
        , m_pArchive(nullptr)
        , stream(sevenzippath.toStdString())
    {
        m_archiveFile.setFileName(sevenzippath);
        qDebug() << m_archiveFile;
        if(!m_archiveFile.open(QIODevice::ReadOnly)) {
            m_pArchive = nullptr;
            return;
        }
        stream.setFile(&m_archiveFile);
        if (!c7zipLib->OpenArchive(&stream, &m_pArchive)) {
            m_pArchive = nullptr;
            return;
        }
        unsigned int numItems = 0;

        m_pArchive->GetItemCount(&numItems);

        wprintf(L"%d\n", numItems);

        size_t pre_total = 0;
        for(unsigned int i = 0;i < numItems;i++) {
            C7ZipArchiveItem * pArchiveItem = nullptr;

            if (m_pArchive->GetItemInfo(i, &pArchiveItem)) {
                wprintf(L"%d,%ls,%d\n", pArchiveItem->GetArchiveIndex(),
                        pArchiveItem->GetFullPath().c_str(),
                        pArchiveItem->IsDir());

                // add each path of the content file
                wstring fullpath = pArchiveItem->GetFullPath();
                QString fileName = QDir::fromNativeSeparators(
                    QString::fromStdWString(fullpath));
                m_fileNameList << fileName;

                Qt7zFileInfo props = fromC7ZipArchiveItem(*pArchiveItem, m_packagePath, pre_total);
                pre_total += props.size;
                m_fileInfoList << props;

                m_fileNameToIndex.insert(fileName, i);

                wprintf(L"get all properties\n");
                for(lib7zip::PropertyIndexEnum index = lib7zip::kpidPackSize;
                    index <= lib7zip::kpidIsDir;
                    index = (lib7zip::PropertyIndexEnum)(index + 1)) {
                    wstring strVal = L"";
                    unsigned __int64 val = 0;
                    bool bVal = false;

                    bool result = pArchiveItem->GetUInt64Property(index, val);

                    wprintf(L"\n\nGetProperty:%d %ls\n", (int)index,
                            index_names[(int)index]);

                    wprintf(L"UInt64 result:%ls val=%ld\n",
                            result ? L"true" : L"false",
                            val);

                    result = pArchiveItem->GetBoolProperty(index, bVal);

                    wprintf(L"Bool result:%ls val=%ls\n",
                            result ? L"true" : L"false",
                            bVal ? L"true" : L"false");

                    result = pArchiveItem->GetStringProperty(index, strVal);

                    wprintf(L"String result:%ls val=%ls\n",
                            result ? L"true" : L"false",
                            strVal.c_str());

                    result = pArchiveItem->GetFileTimeProperty(index, val);

                    wprintf(L"FileTime result:%ls val=%ld\n",
                            result ? L"true" : L"false",
                            val);
                }

            } //if
        }//for

    }
    bool extractFile(const QString &name, QIODevice *outStream)
    {
        if (!outStream || !outStream->isWritable()) {
            qWarning() << "Qt7z: Extract output stream is null or not writable!";
            return false;
        }

        if (m_pArchive == nullptr) {
            return false;
        }

//        if (m_tempDir) {
//            uint32_t index = m_p->m_fileNameToIndex[name];
//            const QString abso = QDir(m_tempDir->path()).filePath(QString::number(index));
//            QFile file(abso);
//            file.open(QIODevice::ReadOnly);
//            QByteArray bytes = file.readAll();
//            outStream->write(bytes);
//            return true;
//        }
        qDebug() << name << m_fileNameToIndex;
        auto indexIt = m_fileNameToIndex.find(name);
        if (indexIt == m_fileNameToIndex.end()) {
            qWarning() << "Qt7z: Fail to find file" << name;
            return false;
        }
        uint32_t index = *indexIt;
        Qt7zStreamWriter oStream(outStream, name);
        m_pArchive->Extract(index, &oStream);

        return true;
    }

};

FileLoader7zArchive::FileLoader7zArchive(QObject* parent, QString sevenzippath, bool extractSolidArchiveToTemporaryDir)
    : IFileLoader(parent)
    , d(new FileLoader7zArchivePrivate(sevenzippath))
    , m_volumepath(sevenzippath)
    , m_valid(d->m_pArchive != nullptr)
    , m_extractSolidArchiveToTemporaryDir(extractSolidArchiveToTemporaryDir)
    , m_temp(nullptr)
{
    initialize();
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
    foreach(const Qt7zFileInfo& info, d->m_fileInfoList) {
        if(!info.isDir) {
            QString filename = QDir::fromNativeSeparators(info.fileName);
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
//    if(m_extractSolidArchiveToTemporaryDir && d->m_reader.isSolid()) {
//        QString tempdir = QString("%1/qv_%2").arg(QDir::tempPath()).arg(++s_archiveCnt, 3, 10, QLatin1Char('0'));
//        d->m_reader.extractToDir(QDir::toNativeSeparators(tempdir));
//    }
    m_valid = true;
}

QByteArray FileLoader7zArchive::getFile(QString name, QMutex& mutex)
{
    QByteArray bytes;
    mutex.lock();
    qDebug() << name << d->m_fileNameToIndex;
    qDebug() << m_imageFileList;
    if(m_imageFileList.contains(name)) {
        Qt7zFileInfo info = d->m_fileinfomap[name];

        QBuffer iobuffer(&bytes);
        iobuffer.open(QIODevice::WriteOnly);
        d->extractFile(info.fileName, &iobuffer);
    }
    mutex.unlock();
    return bytes;
}

FileLoader7zArchive::~FileLoader7zArchive() {if(d){delete d;d=nullptr;}}
