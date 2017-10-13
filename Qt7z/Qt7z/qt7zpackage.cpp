#include "qt7zpackage_p.h"

using namespace NWindows;
using namespace NFile;

#ifdef QT7Z_STATIC_LINK

#define NAMESPACE_FORCE_LINK(CODEC) \
    namespace N##CODEC { \
        extern bool g_forceLink; \
    }

#define NAMESPACE_FORCE_LINK64(CODEC) \
    namespace N##CODEC { \
        extern bool g_forceLink64; \
    }

namespace NArchive {
    NAMESPACE_FORCE_LINK(7z)
    NAMESPACE_FORCE_LINK(Zip)
}

namespace NCompress {
    NAMESPACE_FORCE_LINK(Bcj)
    NAMESPACE_FORCE_LINK(Bcj2)
    NAMESPACE_FORCE_LINK(Branch)
    NAMESPACE_FORCE_LINK(Copy)
    NAMESPACE_FORCE_LINK(Lzma)
    NAMESPACE_FORCE_LINK(Lzma2)
    NAMESPACE_FORCE_LINK(Ppmd)
    NAMESPACE_FORCE_LINK(Deflate)
    NAMESPACE_FORCE_LINK64(Deflate)
}

namespace NCrypto {
    NAMESPACE_FORCE_LINK(7z)
    NAMESPACE_FORCE_LINK(Aes)
}

extern bool g_forceLinkCRC;

struct ForceLinkCodecs
{
    ForceLinkCodecs()
    {
        static bool forceLinkCRC = g_forceLinkCRC;

#define REFER_TO_FORCE_LINK(NAMESPACE, CODEC) \
    bool forceLink##NAMESPACE##CODEC = N##NAMESPACE::N##CODEC::g_forceLink;

#define REFER_TO_FORCE_LINK64(NAMESPACE, CODEC) \
    bool forceLink##NAMESPACE##CODEC##64 = N##NAMESPACE::N##CODEC::g_forceLink64;

        REFER_TO_FORCE_LINK(Archive, 7z)
        REFER_TO_FORCE_LINK(Archive, Zip)
        REFER_TO_FORCE_LINK(Compress, Bcj)
        REFER_TO_FORCE_LINK(Compress, Bcj2)
        REFER_TO_FORCE_LINK(Compress, Branch)
        REFER_TO_FORCE_LINK(Compress, Copy)
        REFER_TO_FORCE_LINK(Compress, Lzma)
        REFER_TO_FORCE_LINK(Compress, Lzma2)
        REFER_TO_FORCE_LINK(Compress, Ppmd)
        REFER_TO_FORCE_LINK(Compress, Deflate)
        REFER_TO_FORCE_LINK64(Compress, Deflate)
        REFER_TO_FORCE_LINK(Crypto, 7z)
        REFER_TO_FORCE_LINK(Crypto, Aes)
    }

};

#ifdef Q_OS_WIN
__declspec(selectany)ForceLinkCodecs forceLink;
#else
ForceLinkCodecs forceLink;
#endif

#endif // QT7Z_STATIC_LINK

#ifndef Q_OS_WIN
extern "C"
{
extern int global_use_utf16_conversion;
}
#endif

static HRESULT GetUInt64Value(IInArchive *archive, UInt32 index, PROPID propID, CListUInt64Def &value)
{
  value.Val = 0;
  value.Def = false;
  NWindows::NCOM::CPropVariant prop;
  RINOK(archive->GetProperty(index, propID, &prop));
  value.Def = ConvertPropVariantToUInt64(prop, value.Val);
  return S_OK;
}



HRESULT SequentialStreamAdapter::Write(const void *data, UInt32 size, UInt32 *processedSize)
{
    *processedSize = m_device->write(reinterpret_cast<const char *>(data), size);
    return S_OK;
}

HRESULT SequentialStreamAdapter::OutStreamFinish()
{
    return S_OK;
}

HRESULT OpenCallback::Open_CheckBreak()
{
    return S_OK;
}

HRESULT OpenCallback::Open_SetTotal(const UInt64 *files, const UInt64 *bytes)
{
    return S_OK;
}

HRESULT OpenCallback::Open_SetCompleted(const UInt64 *files, const UInt64 *bytes)
{
    return S_OK;
}

HRESULT OpenCallback::Open_Finished()
{
    return S_OK;
}

HRESULT OpenCallback::Open_CryptoGetTextPassword(BSTR *password)
{
    if (m_client) {
        QString requestedPassword;
        m_client->openPasswordRequired(requestedPassword);
        std::wstring wpassword = requestedPassword.toStdWString();
        *password = SysAllocStringLen(wpassword.data(), wpassword.size());
    }
    return S_OK;
}


ExtractCallback::ExtractCallback(Qt7zPackagePrivate *qt7zprivate) :
    m_p(qt7zprivate),
    m_client(qt7zprivate->m_client),
    m_opRes(NArchive::NExtract::NOperationResult::kOK),
    m_unpackFinished(-1)
{
}

HRESULT ExtractCallback::GetStream(UInt32 index, ISequentialOutStream **outStream, Int32 askExtractMode)
{
    return S_OK;
}

void ExtractCallback::WriteFileFinished(UInt32 index, QIODevice *device)
{
    m_unpackFinished = (int)index;
}

HRESULT ExtractCallback::SetTotal(UInt64 total)
{
    return S_OK;
}

HRESULT ExtractCallback::SetCompleted(const UInt64 *completeValue)
{
    return S_OK;
}

HRESULT ExtractCallback::PrepareOperation(Int32 askExtractMode)
{
    return S_OK;
}

HRESULT ExtractCallback::SetOperationResult(Int32 opRes)
{
    m_opRes = opRes;

    switch (opRes)
    {
      case NArchive::NExtract::NOperationResult::kUnsupportedMethod:
        qWarning() << "Qt7z: Extract operation result: Unsupported method";
        break;
      case NArchive::NExtract::NOperationResult::kCRCError:
        if (m_fileInfo.isEncrypted) {
            qWarning() << "Qt7z: Extract operation result: CRC failed in encrypted file. Wrong password?";
        } else {
            qWarning() << "Qt7z: Extract operation result: CRC failed";
        }
        break;
      case NArchive::NExtract::NOperationResult::kDataError:
        if (m_fileInfo.isEncrypted) {
            qWarning() << "Qt7z: Extract operation result: Data error in encrypted file. Wrong password?";
        } else {
            qWarning() << "Qt7z: Extract operation result: Data error";
        }
        break;
      case NArchive::NExtract::NOperationResult::kUnavailable:
        qWarning() << "Qt7z: Extract operation result: Unavailable data";
        break;
      case NArchive::NExtract::NOperationResult::kUnexpectedEnd:
        qWarning() << "Qt7z: Extract operation result: Unexpected end of data";
        break;
      case NArchive::NExtract::NOperationResult::kDataAfterEnd:
        qWarning() << "Qt7z: Extract operation result: There are some data after the end of the payload data";
        break;
      case NArchive::NExtract::NOperationResult::kIsNotArc:
        qWarning() << "Qt7z: Extract operation result: Is not archive";
        break;
      case NArchive::NExtract::NOperationResult::kHeadersError:
        qWarning() << "Qt7z: Extract operation result: Headers error";
        break;
      case NArchive::NExtract::NOperationResult::kWrongPassword:
        qWarning() << "Qt7z: Extract operation result: Wrong password";
        break;
    }
    WriteFileFinished(m_index, m_device);

    return S_OK;
}

HRESULT ExtractCallback::CryptoGetTextPassword(BSTR *password)
{
    if (m_client) {
        QString requestedPassword;
        m_client->openPasswordRequired(requestedPassword);
        std::wstring wpassword = requestedPassword.toStdWString();
        *password = SysAllocStringLen(wpassword.data(), wpassword.size());
    }
    return S_OK;
}

ExtractFileCallback::ExtractFileCallback(Qt7zPackagePrivate *qt7zprivate, const Qt7zFileInfo fileInfo, QIODevice *outStream) :
    ExtractCallback(qt7zprivate),
    m_outStream(outStream)
{
    m_fileInfo = fileInfo;
}

HRESULT ExtractFileCallback::GetStream(UInt32 index, ISequentialOutStream **outStream, Int32 askExtractMode)
{
    m_index = index;
    if (askExtractMode != NArchive::NExtract::NAskMode::kExtract) {
        *outStream = nullptr;
        return S_OK;
    }
    m_device = m_outStream;
    CMyComPtr<ISequentialOutStream> stream(new SequentialStreamAdapter(m_device, index, this));
    *outStream = stream.Detach();
    return S_OK;
}

void ExtractFileCallback::WriteFileFinished(UInt32 index, QIODevice *device)
{
    m_unpackFinished = (int)index;
}

ExtractArchiveCallback::ExtractArchiveCallback(Qt7zPackagePrivate *qt7zprivate, QString toDirPath) :
    ExtractCallback(qt7zprivate),
    m_toDirPath(toDirPath)
{
}


HRESULT ExtractArchiveCallback::GetStream(UInt32 index, ISequentialOutStream **outStream, Int32 askExtractMode)
{
    m_index = index;
    *outStream = nullptr;
    if (askExtractMode != NArchive::NExtract::NAskMode::kExtract) {
        return S_OK;
    }
    QString subpath = QDir::fromNativeSeparators(m_p->m_fileNameList.at(index));
    m_fileInfo = m_p->m_fileInfoList[index];
    if(m_fileInfo.isDir) {
        QDir parent(QDir::fromNativeSeparators(m_toDirPath));
//        qDebug() << "parent:" << parent.path() << parent.exists();
//        bool mkpathresult =
                parent.mkdir(subpath);
//        qDebug() << "mkpath:" << mkpathresult << QDir(parent.filePath(subpath)).exists();
        m_device = nullptr;
        return S_OK;
    }
    QString fullpath = QDir(m_toDirPath).filePath(subpath);
    m_device = new QFile(fullpath);
    bool opened = m_device->open(QIODevice::WriteOnly | QIODevice::Unbuffered);
    CMyComPtr<ISequentialOutStream> stream(new SequentialStreamAdapter(m_device, index, this));
    *outStream = stream.Detach();
    return S_OK;
}

void ExtractArchiveCallback::WriteFileFinished(UInt32 index, QIODevice *device)
{
    m_unpackFinished = (int)index;
    if(device) {
        device->close();
        delete device;
    }
}

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


static CCodecs* s_codecs;

static CCodecs* getMyCodecs()
{
    if(!s_codecs) {
        s_codecs = new CCodecs;
#ifndef Q_OS_WIN
        QString dirpath = qApp->applicationDirPath() + "/../lib/";
        qputenv("P7ZIP_HOME_DIR",  dirpath.toUtf8());
#endif
        try {
            if (s_codecs->Load() != S_OK) {
                qWarning() << "Qt7z: Failed to load codecs";
            }
        } catch(...) {
            qWarning() << "Qt7z: Failed to load codecs()";
        }
    }
    return s_codecs;
}



void Qt7zPackagePrivate::init()
{
//    m_codecs.reset(getMyCodecs());
    m_codecs = getMyCodecs();
//    m_codecs.reset(new CCodecs);
//    if (m_codecs.data()->Load() != S_OK) {
//        qWarning() << "Qt7z: Failed to load codecs";
//    }
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

    m_p->m_arcLink.NonOpen_ErrorInfo.ClearErrors_Full();

    CObjectVector<CProperty> props;
    CObjectVector<COpenType> types;   // TODO: ok to leave blank?
    CIntVector excludedFormats;

    COpenOptions options;
    options.props = &props;
//    options.codecs = m_p->m_codecs.data();
    options.codecs = m_p->m_codecs;
    options.types = &types;
    options.excludedFormats = &excludedFormats;
    options.stdInMode = false;
    options.stream = nullptr;

    std::wstring packagePathW = m_p->m_packagePath.toStdWString();
    options.filePath = UString(packagePathW.data());

    OpenCallback callback(m_p->m_client);

    HRESULT res;
    try {
#ifdef Q_OS_WIN
        res = m_p->m_arcLink.Open_Strict(options, &callback);
#else
#  ifdef LOCALE_IS_UTF8
        // Although it is not a very good solution to directly change the internal flag,
        // but the current operation of p7zip is inevitable to be incomplete.
        global_use_utf16_conversion = 1;
#  endif
        global_use_utf16_conversion = 1;
        res = m_p->m_arcLink.Open3(options, &callback);
#endif
    }
    catch (...) {
        qWarning() << "Qt7z: Exception caught when opening archive";
        return false;
    }

    if (res != S_OK) {
        QString errMessage = QString::fromWCharArray(m_p->m_arcLink.NonOpen_ErrorInfo.ErrorMessage.Ptr(),
                                                     m_p->m_arcLink.NonOpen_ErrorInfo.ErrorMessage.Len());
        qWarning() << "Qt7z: Fail to open archive with result" << res << errMessage;
        return false;
    }

    // TODO: Process error info?
    // for (unsigned i = 0; i < arcLink.Size(); i++) {
    //     const CArcErrorInfo &arc = arcLink.Arcs[i].ErrorInfo;
    // }

    const CArc &arc = m_p->m_arcLink.Arcs.Back();
    IInArchive *archive = arc.Archive;

    NCOM::CPropVariant prop;
    if(archive->GetArchiveProperty(kpidSolid, &prop) == S_OK)
        m_solid = prop.boolVal;

    UInt32 numItems;
    if (archive->GetNumberOfItems(&numItems) != S_OK) {
        qWarning() << "Qt7z: Fail to get number of items";
        return false;
    }

    CReadArcItem item;
    UStringVector pathParts;
    size_t pre_total = 0;

    for (UInt32 i = 0; i < numItems; i++) {
        UString filePath;
        if (arc.GetItemPath2(i, filePath) != S_OK) {
            qWarning() << "Qt7z: Fail to get file path of index" << i;
            return false;
        }

        QString fileName = QDir::fromNativeSeparators(
            QString::fromWCharArray(filePath.Ptr(), filePath.Len()));
        m_p->m_fileNameList << fileName;

        Qt7zFileInfo fileInfo;
        fileInfo.fileName = fileName;
        fileInfo.arcName = m_p->m_packagePath;

        if (Archive_IsItem_Dir(archive, i, fileInfo.isDir) != S_OK) {
            qWarning() << "Qt7z: Fail to determine if directory of index" << i;
            return false;
        }

        CListUInt64Def sizeDef;
        if (GetUInt64Value(archive, i, kpidSize, sizeDef) != S_OK) {
            qWarning() << "Qt7z: Fail to file size of index" << i;
            return false;
        }
        fileInfo.pre_total = pre_total;
        pre_total += sizeDef.Val;
        fileInfo.size = sizeDef.Val;

        CListUInt64Def crcDef;
        if (GetUInt64Value(archive, i, kpidCRC, crcDef) != S_OK) {
            qWarning() << "Qt7z: Fail to CRC of index" << i;
            return false;
        }
        fileInfo.isCrcDefined = crcDef.Def;
        fileInfo.crc = crcDef.Val;

        if (Archive_GetItemBoolProp(archive, i, kpidEncrypted, fileInfo.isEncrypted) != S_OK) {
            qWarning() << "Qt7z: Fail to determine if encrypted of index" << i;
            return false;
        }

        m_p->m_fileInfoList << fileInfo;
        m_p->m_fileNameToIndex.insert(fileName, i);
    }

    m_p->m_isOpen = true;

    return true;
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
        const QString abso = m_tempDir->filePath(name);
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
    UInt32 index = *indexIt;
    Qt7zFileInfo fileInfo = m_p->m_fileInfoList[index];

    const CArc &arc = m_p->m_arcLink.Arcs.Back();
    IInArchive *archive = arc.Archive;
    CRecordVector<UInt32> realIndices;
    realIndices.Add(index);
    Int32 testMode = 0;

    CMyComPtr<ExtractFileCallback> callback(new ExtractFileCallback(m_p, fileInfo, outStream));
    HRESULT res = archive->Extract(&realIndices.Front(), realIndices.Size(), testMode, callback);

    if (res != S_OK) {
        qWarning() << "Qt7z: Fail to extract file" << name << "with result" << res;
        return false;
    }
    if (callback->opRes() != NArchive::NExtract::NOperationResult::kOK) {
        qWarning() << "Qt7z: Fail to extract file" << name << "with op res" << callback->opRes();
        return false;
    }

    return true;
}

bool Qt7zPackage::extractToDir(const QString &dirpath)
{
    m_tempDir = new QTemporaryDir(dirpath);
    m_tempDir->setAutoRemove(true);
    qDebug() << "tempdir:" << m_tempDir->path();
    const CArc &arc = m_p->m_arcLink.Arcs.Back();
    IInArchive *archive = arc.Archive;
    CMyComPtr< ExtractArchiveCallback > extractCallback = new ExtractArchiveCallback(m_p, m_tempDir->path());
    HRESULT hr = archive->Extract(nullptr, uint(-1), false, extractCallback);

    return hr==0;
}

