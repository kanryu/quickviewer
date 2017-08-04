#include <QtDebug>
#include "fileloaderziparchive.h"
#include "quazip.h"
#include "quazipfile.h"

FileLoaderZipArchive::FileLoaderZipArchive(QObject* parent, QString zippath)
    : IFileLoader(parent)
    , m_volumepath(zippath)
    , d(new QuaZip(zippath))
    , m_valid(false)
{
    d->open(QuaZip::mdUnzip);
    if(!(m_valid = d->isOpen()))
        return;

    foreach(const QString& name, d->getFileNameList()) {
        if(IFileLoader::isImageFile(name)) {
            m_imageFileList.append(name);
        } else if(IFileLoader::isArchiveFile(name)) {
            m_subArchiveList.append(name);
        }
    }
    IFileLoader::sortFiles(m_imageFileList);
    IFileLoader::sortFiles(m_subArchiveList);
    m_valid = true;
}

QByteArray FileLoaderZipArchive::getFile(QString name, QMutex& mutex)
{
    QByteArray bytes;
    mutex.lock();
    if(m_imageFileList.contains(name)) {
        bool check = d->setCurrentFile(name);
        if(!check) {
            qDebug() << name << "can't be found in the zip:" << volumePath();
        }
        QuaZipFile zipFile(d);
        zipFile.open(QIODevice::ReadOnly, nullptr);
        bytes = zipFile.readAll();
    }
    mutex.unlock();
    return bytes;
}
