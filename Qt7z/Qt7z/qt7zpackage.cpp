#include <qcoreapplication.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include <lib7zip.h>
#include "qt7zpackage_p.h"



/** Used by lib7zip when reading binary streams.
 *  Specifically, read 7z from the file
 */
class Qt7zStreamReader : public C7ZipInStream
{
private:
    QIODevice *m_inStream;
    QString m_strFileName;
    wstring m_strFileExt;
    int m_nFileSize;
public:
    Qt7zStreamReader(QIODevice *inStream, QString fileName) :
        m_inStream(inStream),
        m_strFileName(fileName),
        m_strFileExt(L"7z")
    {
    }

    virtual ~Qt7zStreamReader()
    {
    }

public:
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

public:
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
                auto pos = m_outStream->pos();
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
        return result == true ? 0 : 1;
    }

    virtual int SetSize(unsigned __int64 size)
    {
        wprintf(L"SetFileSize:%ld\n", size);
        return 0;
    }
};

Qt7zPackagePrivate::Qt7zPackagePrivate(Qt7zPackage *q) :
    m_q(q) ,
    m_client(nullptr) ,
    m_isOpen(false)
{
    init();
}

Qt7zPackagePrivate::Qt7zPackagePrivate(Qt7zPackage *q,
                                       const QString &packagePath) :
    m_q(q) ,
    m_packagePath(packagePath) ,
    m_client(nullptr) ,
    m_isOpen(false)
{
    init();
}

Qt7zPackagePrivate::~Qt7zPackagePrivate()
{
//    m_codecs.reset(nullptr);
}

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
    prop.fileName = QString::fromStdWString(strVal);
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

bool Qt7zPackagePrivate::open()
{
    if (!lib7zip_fatal_error) {
        return false;
    }
    std::string packagePath = m_packagePath.toStdString();
    m_file.setFileName(m_packagePath);
    m_pInStream = new Qt7zStreamReader(&m_file, m_packagePath);

    if(lib7zip->OpenArchive(m_pInStream, &m_pArchive)) {
        unsigned int numItems = 0;

        m_pArchive->GetItemCount(&numItems);

        wprintf(L"%d\n", numItems);
        size_t pre_total = 0;

        for(uint32_t i = 0;i < numItems;i++) {
            C7ZipArchiveItem * pArchiveItem = NULL;

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
            } //if
        }//for
    }
    else {
        wprintf(L"open archive Test7Zip.7z fail\n");
    }
    m_isOpen = true;
    return true;
}

bool Qt7zPackagePrivate::extractToDir(const QString &dirpath)
{
    unsigned int numItems = 0;

    m_pArchive->GetItemCount(&numItems);

    wprintf(L"%d\n", numItems);
    size_t pre_total = 0;

    for(uint32_t i = 0;i < numItems;i++) {
        Qt7zFileInfo info = m_fileInfoList[i];
        const QString abso = QDir(dirpath).filePath(QString::number(i));
        QFile file(abso);
        if(file.open(QIODevice::ReadOnly)) {
            Qt7zStreamWriter oStream(&file, info.fileName);
            m_pArchive->Extract(i, &oStream);
            file.close();
        } else {
            qDebug() << "Qt7zPackagePrivate::extractToDir()" << "file:" << abso << "can't open";
            return false;
        }
    }//for
    return true;
}

void Qt7zPackagePrivate::init()
{
    if(lib7zip == nullptr) {
        lib7zip = new C7ZipLibrary();
        if (!lib7zip->Initialize()) {
    		wprintf(L"initialize fail!\n");
            lib7zip_fatal_error = true;
    		return;
    	}
    }
}

void Qt7zPackagePrivate::reset()
{
    m_packagePath.clear();
    m_isOpen = false;
    m_fileNameList.clear();
    m_fileInfoList.clear();
}

Qt7zPackage::Qt7zPackage() :
    m_p(new Qt7zPackagePrivate(this))
    , m_solid(false)
{
}

Qt7zPackage::Qt7zPackage(const QString &packagePath)
  : m_p(new Qt7zPackagePrivate(this, packagePath))
  , m_tempDir(nullptr)
  , m_solid(false)
  , m_extractSolidArchiveToDir(false)
{
}

Qt7zPackage::~Qt7zPackage()
{
    close();
    if (m_p) {
        delete m_p;
    }
    if(m_tempDir) {
        delete m_tempDir;
    }
}

bool Qt7zPackage::open()
{
    if (m_p->m_isOpen) {
        return false;
    }

    if (!QFile::exists(m_p->m_packagePath)) {
        qWarning() << "Qt7z: File does not exist:" << m_p->m_packagePath;
        return false;
    }
    return m_p->open();
}

void Qt7zPackage::close()
{
    if (m_p->m_isOpen) {
        m_p->m_isOpen = false;
    }
}

bool Qt7zPackage::isOpen() const
{
    return m_p->m_isOpen;
}

QStringList Qt7zPackage::getFileNameList() const
{
    return m_p->m_fileNameList;
}

QStringList Qt7zPackage::fileNameList() const
{
    return m_p->m_fileNameList;
}

QList<Qt7zFileInfo> &Qt7zPackage::fileInfoList() const
{
    return m_p->m_fileInfoList;
}

Qt7zPackage::Client *Qt7zPackage::client() const
{
    return m_p->m_client;
}

void Qt7zPackage::setClient(Qt7zPackage::Client *client)
{
    m_p->m_client = client;
}

bool Qt7zPackage::extractFile(const QString &name, QIODevice *outStream)
{
    if (!outStream || !outStream->isWritable()) {
        qWarning() << "Qt7z: Extract output stream is null or not writable!";
        return false;
    }

    if (!m_p->m_isOpen) {
        if (!open()) {
            qWarning() << "Qt7z: Fail to extract file" << name << "due to unable to open archive" << m_p->m_packagePath;
            return false;
        }
    }

    if (m_tempDir) {
        uint32_t index = m_p->m_fileNameToIndex[name];
        const QString abso = QDir(m_tempDir->path()).filePath(QString::number(index));
        QFile file(abso);
        file.open(QIODevice::ReadOnly);
        QByteArray bytes = file.readAll();
        outStream->write(bytes);
        return true;
    }

    auto indexIt = m_p->m_fileNameToIndex.find(name);
    if (indexIt == m_p->m_fileNameToIndex.end()) {
        qWarning() << "Qt7z: Fail to find file" << name;
        return false;
    }
    uint32_t index = *indexIt;
//    Qt7zArchiveItemProperties fileInfo = m_p->m_fileInfoList[index];
    
//	C7ZipArchiveItem * pArchiveItem = nullptr;
//    if (!m_p->m_pArchive->GetItemInfo(index, &pArchiveItem)) {
//        qWarning() << "Qt7z: Fail to extract file" << name;
//    }

//    Qt7zStreamWriter oStream(outStream, name);
//    m_p->m_pArchive->Extract(pArchiveItem, &oStream);
    Qt7zStreamWriter oStream(outStream, name);
    m_p->m_pArchive->Extract(index, &oStream);

    return true;
}

bool Qt7zPackage::extractToDir(const QString &dirpath)
{
    m_tempDir = new QTemporaryDir(dirpath);
    m_tempDir->setAutoRemove(true);
    qDebug() << "tempdir:" << m_tempDir->path();
    return m_p->extractToDir(m_tempDir->path());
}

