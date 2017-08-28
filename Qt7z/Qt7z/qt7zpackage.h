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
    class Client
    {
    public:
        virtual void openPasswordRequired(QString &password) = 0;
        virtual void extractPasswordRequired(QString &password) = 0;
    };

    Qt7zPackage();
    Qt7zPackage(const QString &packagePath);
    ~Qt7zPackage();

    bool open();
    void close();
    bool isSolid() { return m_solid; }

    bool isOpen() const;
    QStringList getFileNameList() const;

    QStringList fileNameList() const;
    QList<Qt7zFileInfo> &fileInfoList() const;

    Client *client() const;
    void setClient(Client *client);

    bool extractFile(const QString &name, QIODevice *outStream);

private:
    void reset();

    Qt7zPackagePrivate *m_p;
    bool m_solid;
};

#endif // QT7ZPACKAGE_H
