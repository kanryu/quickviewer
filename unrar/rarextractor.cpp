#include "rarextractor.h"
#include "unrar/rar.hpp"


struct RARFileWriter
{
    RARFileInfo* info;
    QBuffer buffer;
    RARFileWriter(RARFileInfo* i) : info(i) {buffer.open(QIODevice::ReadWrite);}
    static int CALLBACK procCallback(UINT msg, LPARAM self, LPARAM addr, LPARAM size);
    void commit() {
        buffer.seek(0);
//        qDebug() << "commit:" << info->fileName << buffer.size();
        info->data = buffer.readAll();
    }
};


int RARFileWriter::procCallback(UINT msg, LPARAM rawSelf,
                                   LPARAM p1, LPARAM p2)
{
    RARFileWriter *self = reinterpret_cast<RARFileWriter *>(rawSelf);

    if (msg == UCM_PROCESSDATA) {
        const char *data = reinterpret_cast<const char *>(p1);
        qint64 size = p2;
        self->buffer.write(data, size);
    } else if (msg == UCM_NEEDPASSWORD) {
        char *passBuf = reinterpret_cast<char *>(p1);
        int passBufSize = p2;
        std::string str = self->info->m_password.toStdString();
        strncpy(passBuf, str.c_str(),
                qMin(str.length(), (std::string::size_type)passBufSize));
    }

    return 1;
}

RarExtractor::RarExtractor()
    : m_hArc(nullptr)
    , m_mode(OpenModeNotOpen)
    , m_error(ERAR_SUCCESS)
    , m_isHeadersEncrypted(false)
    , m_isFilesEncrypted(false)
    , m_hasScaned(false)
    , m_curIndex(0)
{}
RarExtractor::RarExtractor(const QString &arcName)
    : m_hArc(nullptr)
    , m_mode(OpenModeNotOpen)
    , m_error(ERAR_SUCCESS)
    , m_arcName(arcName)
    , m_isHeadersEncrypted(false)
    , m_isFilesEncrypted(false)
    , m_hasScaned(false)
    , m_curIndex(0)
{
}
bool RarExtractor::open(OpenMode mode, const QString &password)
{
    RAROpenArchiveDataEx arcData = {0};
    wchar_t arcNameW[RarExtractor::MAX_ARC_NAME_SIZE] = {0};
    int arcNameLen = m_arcName
            .left(RarExtractor::MAX_ARC_NAME_SIZE - 1)
            .toWCharArray(arcNameW);
//    arcNameW[arcNameLen] = '\0';
    arcData.ArcNameW = arcNameW;
    arcData.ArcName = 0;
    arcData.CmtBuf = new char[RarExtractor::MAX_COMMENT_SIZE];
    arcData.CmtBufSize = RarExtractor::MAX_COMMENT_SIZE;
    arcData.Callback = 0;
    arcData.UserData = 0;
    arcData.OpenMode = RAR_OM_EXTRACT;

    m_hArc = RAROpenArchiveEx(&arcData);
    m_error = arcData.OpenResult;
    m_curIndex = 0;
    m_comment.clear();

    bool isSuccess = (m_error == ERAR_SUCCESS);
    if (isSuccess) {
        m_mode = mode;

        if (arcData.CmtSize > 0) {
            // Comment buffer ends with '\0'
            std::string cstr(arcData.CmtBuf, arcData.CmtSize - 1);
            m_comment = QString::fromStdString(cstr);
        }

        m_isHeadersEncrypted = (arcData.Flags & 0x0080);
        scanFileInfo();
    } else {
        m_mode = RarExtractor::OpenModeNotOpen;
    }

    delete arcData.CmtBuf;
    return isSuccess;
}

void RarExtractor::reset()
{
    m_fileInfoList.clear();
    m_comment.clear();
    m_isHeadersEncrypted = false;
    m_isFilesEncrypted = false;
    m_password.clear();
    m_curIndex = 0;
    m_error = ERAR_SUCCESS;
    m_hArc = 0;
    m_mode = OpenModeNotOpen;
    m_hasScaned = false;
}

void RarExtractor::scanFileInfo()
{
    if (!isOpen() || m_hasScaned) {
        return;
    }

    m_fileInfoList.clear();

    RARHeaderDataEx hData;
    int i = 0;
    while (RARReadHeaderEx(m_hArc, &hData) == ERAR_SUCCESS) {
        RARFileInfo info;

        info.fileName = QString::fromWCharArray(hData.FileNameW);
        info.arcName = m_arcName;
        info.flags = hData.Flags;
        info.packSize = hData.PackSize;
        info.unpSize = hData.UnpSize;
        info.hostOS = hData.HostOS;
        info.fileCRC = hData.FileCRC;
        info.fileTime = hData.FileTime;
        info.unpVer = hData.UnpVer;
        info.method = hData.Method;
        info.fileAttr = hData.FileAttr;
        info.comment = m_comment;

        RARFileWriter writer(&info);
        RARSetCallback(m_hArc,
                       RARFileWriter::procCallback,
                       reinterpret_cast<LPARAM>(&writer));


        if (info.flags & 0x04) {
            m_isFilesEncrypted = true;
        }

        if (RARProcessFile(m_hArc, RAR_TEST, NULL, NULL) != ERAR_SUCCESS) {
            break;
        }
        writer.commit();
        m_fileInfoList << info;
        m_fileNameToIndexSensitive.insert(info.fileName, i);
        m_fileNameToIndexInsensitive.insert(info.fileName.toLower(), i);
        i++;
    };

    m_hasScaned = true;

    // Reopen to reset cursor
    reopen();
}

QStringList RarExtractor::fileNameList() const
{
    QStringList list;
    foreach (const RARFileInfo &info, m_fileInfoList) {
        list << info.fileName;
    }
    return list;
}
