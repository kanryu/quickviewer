#ifndef RAREXTRACTOR_H
#define RAREXTRACTOR_H

#include <QtCore>

struct RARFileInfo
{
    QString fileName;
    QString arcName;
    QString m_password;
    unsigned int flags;
    unsigned int packSize;
    unsigned int unpSize;
    unsigned int hostOS;
    unsigned int fileCRC;
    unsigned int fileTime;
    unsigned int unpVer;
    unsigned int method;
    unsigned int fileAttr;
    QString comment;
    QByteArray data;
    RARFileInfo() {}
    RARFileInfo(const RARFileInfo& rhs)
        : fileName(rhs.fileName)
        , arcName(rhs.arcName)
        , m_password(rhs.m_password)
        , flags(rhs.flags)
        , packSize(rhs.packSize)
        , unpSize(rhs.unpSize)
        , hostOS(rhs.hostOS)
        , fileCRC(rhs.fileCRC)
        , fileTime(rhs.fileTime)
        , unpVer(rhs.unpVer)
        , method(rhs.method)
        , fileAttr(rhs.fileAttr)
        , comment(rhs.comment)
        , data(rhs.data)
    {}
    bool isEncrypted() const {return flags & 0x04;}
};

class RarExtractor
{
public:
    enum OpenMode {
        OpenModeNotOpen,
        OpenModeList,
        OpenModeExtract,
    };
    static const int MAX_COMMENT_SIZE = 64 * 1024;
    static const int MAX_ARC_NAME_SIZE = 2048;

    RarExtractor();
    RarExtractor(const QString &arcName);

    bool open(OpenMode mode, const QString &password);
    void reset();
    bool reopen() {return true;}
    void scanFileInfo();
    bool isOpen() const { return m_mode != OpenModeNotOpen; }
    QStringList fileNameList() const;
    RARFileInfo& getFileInfo(QString filename) {
        int idx = m_fileNameToIndexInsensitive[filename.toLower()];
        return m_fileInfoList[idx];
    }
    bool contains(QString filename) { return m_fileNameToIndexInsensitive.contains(filename.toLower()); }


    Qt::HANDLE m_hArc;
    int m_error;
    QString m_arcName;
    QString m_comment;
    QString m_password;
    bool m_isHeadersEncrypted;
    bool m_isFilesEncrypted;
    bool m_hasScaned;
    int m_curIndex;
    QList<RARFileInfo> m_fileInfoList;
    OpenMode m_mode;

    QHash<QString, int> m_fileNameToIndexSensitive;
    QHash<QString, int> m_fileNameToIndexInsensitive;
};


#endif // RAREXTRACTOR_H
