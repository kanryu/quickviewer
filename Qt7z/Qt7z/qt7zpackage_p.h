#ifndef QT7ZPACKAGE_P_H
#define QT7ZPACKAGE_P_H

#include <QtCore>
#include <lib7zip.h>

#include "qt7zpackage.h"
#include "qt7zfileinfo.h"


using namespace lib7zip;

//class ExtractCallback;
//class Qt7zPackagePrivate;

//struct CListUInt64Def
//{
//  UInt64 Val;
//  bool Def;

//  CListUInt64Def(): Val(0), Def(false) {}
//  void Add(UInt64 v) { Val += v; Def = true; }
//  void Add(const CListUInt64Def &v) { if (v.Def) Add(v.Val); }
//};

///** Property structure of each content file extracted by lib7zip
// */
//struct Qt7zArchiveItemProperties
//{
//public:
//    /* by GetStringProperty() */
//    QString Comment;             // PropertyIndexEnum::kpidComment
//    QString Characteristics;     // PropertyIndexEnum::kpidCharacts
//    QString CreatorApplication;  // PropertyIndexEnum::kpidCreatorApp
//    QString Label;               // PropertyIndexEnum::kpidVolumeName
//    QString FullPath;            // PropertyIndexEnum::kpidPath
//    QString User;                // PropertyIndexEnum::kpidUser
//    QString Group;               // PropertyIndexEnum::kpidGroup
//    /* by GetUInt64Property() */
//    uint64_t UncompressedSize; // PropertyIndexEnum::kpidSize
//    uint64_t PackSize;         // PropertyIndexEnum::kpidPackSize
//    uint64_t Attributes;       // PropertyIndexEnum::kpidAttrib
//    uint64_t PhysicalSize;     // PropertyIndexEnum::kpidPhySize
//    uint64_t HeadersSize;      // PropertyIndexEnum::kpidHeadersSize
//    uint64_t Checksum;         // PropertyIndexEnum::kpidChecksum
//    uint64_t TotalSize;        // PropertyIndexEnum::kpidTotalSize
//    uint64_t FreeSpace;        // PropertyIndexEnum::kpidFreeSpace
//    uint64_t ClusterSize;      // PropertyIndexEnum::kpidClusterSize
//    /* by GetFileTimeProperty() */
//    uint64_t Created;          // PropertyIndexEnum::kpidCTime
//    uint64_t Accessed;         // PropertyIndexEnum::kpidATime
//    uint64_t Modified;         // PropertyIndexEnum::kpidMTime
//    /* by GetBoolProperty() */
//    bool IsSolid;     // PropertyIndexEnum::kpidSolid
//    bool IsEncrypted; // PropertyIndexEnum::kpidEncrypted
//    bool IsDir;       // PropertyIndexEnum::kpidIsDir

//    Qt7zArchiveItemProperties() {
//        UncompressedSize = 0;
//        PackSize = 0;
//        Attributes = 0;
//        PhysicalSize = 0;
//        HeadersSize = 0;
//        Checksum = 0;
//        TotalSize = 0;
//        FreeSpace = 0;
//        ClusterSize = 0;
//        IsSolid = false;
//        IsEncrypted = false;
//        IsDir = false;
//    }
//    Qt7zArchiveItemProperties(const Qt7zArchiveItemProperties& rhs) {
//        Comment = rhs.Comment;
//        Characteristics = rhs.Characteristics;
//        CreatorApplication = rhs.CreatorApplication;
//        Label = rhs.Label;
//        FullPath = rhs.FullPath;
//        User = rhs.User;
//        Group = rhs.Group;
//        UncompressedSize = rhs.UncompressedSize;
//        PackSize = rhs.PackSize;
//        Attributes = rhs.Attributes;
//        PhysicalSize = rhs.PhysicalSize;
//        HeadersSize = rhs.HeadersSize;
//        Checksum = rhs.Checksum;
//        TotalSize = rhs.TotalSize;
//        FreeSpace = rhs.FreeSpace;
//        ClusterSize = rhs.ClusterSize;
//        IsSolid = rhs.IsSolid;
//        IsEncrypted = rhs.IsEncrypted;
//        IsDir = rhs.IsDir;
//    }

//    static Qt7zArchiveItemProperties fromC7ZipArchiveItem(C7ZipArchiveItem& item) {
//        Qt7zArchiveItemProperties prop;
//        std::wstring strVal;
//        item.GetStringProperty(PropertyIndexEnum::kpidSolid, strVal);
//        prop.Comment = QString::fromStdWString(strVal);
//        item.GetStringProperty(PropertyIndexEnum::kpidCharacts, strVal);
//        prop.Characteristics = QString::fromStdWString(strVal);
//        item.GetStringProperty(PropertyIndexEnum::kpidCreatorApp, strVal);
//        prop.CreatorApplication = QString::fromStdWString(strVal);
//        item.GetStringProperty(PropertyIndexEnum::kpidVolumeName, strVal);
//        prop.Label = QString::fromStdWString(strVal);
//        item.GetStringProperty(PropertyIndexEnum::kpidPath, strVal);
//        prop.FullPath = QString::fromStdWString(strVal);
//        item.GetStringProperty(PropertyIndexEnum::kpidUser, strVal);
//        prop.User = QString::fromStdWString(strVal);
//        item.GetStringProperty(PropertyIndexEnum::kpidGroup, strVal);
//        prop.Group = QString::fromStdWString(strVal);

//        item.GetUInt64Property(PropertyIndexEnum::kpidSize, prop.UncompressedSize);
//        item.GetUInt64Property(PropertyIndexEnum::kpidPackSize, prop.PackSize);
//        item.GetUInt64Property(PropertyIndexEnum::kpidAttrib, prop.Attributes);
//        item.GetUInt64Property(PropertyIndexEnum::kpidPhySize, prop.PhysicalSize);
//        item.GetUInt64Property(PropertyIndexEnum::kpidHeadersSize, prop.HeadersSize);
//        item.GetUInt64Property(PropertyIndexEnum::kpidChecksum, prop.Checksum);
//        item.GetUInt64Property(PropertyIndexEnum::kpidTotalSize, prop.TotalSize);
//        item.GetUInt64Property(PropertyIndexEnum::kpidFreeSpace, prop.FreeSpace);
//        item.GetUInt64Property(PropertyIndexEnum::kpidClusterSize, prop.ClusterSize);
        
//        item.GetFileTimeProperty(PropertyIndexEnum::kpidCTime, prop.Created);
//        item.GetFileTimeProperty(PropertyIndexEnum::kpidATime, prop.Accessed);
//        item.GetFileTimeProperty(PropertyIndexEnum::kpidMTime, prop.Modified);
        
//        item.GetBoolProperty(PropertyIndexEnum::kpidSolid, prop.IsSolid);
//        item.GetBoolProperty(PropertyIndexEnum::kpidEncrypted, prop.IsEncrypted);
//        item.GetBoolProperty(PropertyIndexEnum::kpidIsDir, prop.IsDir);
//        return prop;
//    }
//};

class Qt7zPackagePrivate
{
    friend class Qt7zPackage;
public:
    Qt7zPackagePrivate(Qt7zPackage *q);
    Qt7zPackagePrivate(Qt7zPackage *q, const QString &packagePath);
    ~Qt7zPackagePrivate();
    bool open();
    bool extractToDir(const QString &dirpath);

    Qt7zPackage::Client *m_client;
    Qt7zPackage *m_q;
    QList<Qt7zFileInfo> m_fileInfoList;
    QStringList m_fileNameList;
    static C7ZipLibrary* lib7zip;
    static bool lib7zip_fatal_error;

private:
    void init();
    void reset();

    QString m_packagePath;
    bool m_isOpen;
    QHash<QString, uint32_t> m_fileNameToIndex;
    
    QFile m_file;
    C7ZipArchive* m_pArchive;
    C7ZipInStream* m_pInStream;

//    QScopedPointer<CCodecs> m_codecs;
};


















#endif // QT7ZPACKAGE_P_H
