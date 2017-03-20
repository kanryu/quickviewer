#ifndef QT7ZPACKAGE_H
#define QT7ZPACKAGE_H

#include <QBuffer>
#include <QString>
#include <QStringList>

#include "qt7z_global.h"

struct Qt7zFileInfo;
class Qt7zPackagePrivate;

class QT7ZSHARED_EXPORT Qt7zPackage
{
    friend class Qt7zPackagePrivate;
public:
    Qt7zPackage();
    Qt7zPackage(const QString &packagePath);
    ~Qt7zPackage();

    bool open();
    void close();

    bool isOpen() const;
    QStringList getFileNameList() const;

    QStringList fileNameList() const;
    QList<Qt7zFileInfo> &fileInfoList() const;

    bool extractFile(const QString &name, QIODevice *outStream);

private:
    void reset();

    Qt7zPackagePrivate *m_p;
};

#endif // QT7ZPACKAGE_H
