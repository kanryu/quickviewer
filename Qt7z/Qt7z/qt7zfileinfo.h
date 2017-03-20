#ifndef QT7ZFILEINFO_H
#define QT7ZFILEINFO_H

#include <QtGlobal>
#include <QString>

#include "qt7z_global.h"

struct QT7ZSHARED_EXPORT Qt7zFileInfo
{
    QString fileName;
    QString arcName;
    quint64 size;
    bool isDir;
    bool isCrcDefined;
    quint32 crc;
};

#endif // QT7ZFILEINFO_H
