#include "qvimagemetadata.h"
#include "volumemanager.h"

QvImageMetadata::QvImageMetadata(VolumeManager *volume, QString filename)
    :QObject (volume)
{
    m_volume = volume;
    m_filename = filename;
}

QDateTime QvImageMetadata::getMTime()
{
    if(m_info.fileName().isEmpty())
        initFileInfo();
    return m_info.lastModified();
}

qint64 QvImageMetadata::getFileSize()
{
    if(m_info.fileName().isEmpty())
        initFileInfo();
    return m_info.size();
}

QSize QvImageMetadata::getDimension()
{
    if(!m_dimension.isEmpty())
        return m_dimension;
    QString aformat = IFileLoader::isExifJpegImageFile(m_filename) && IFileLoader::isImageFile("turbojpeg")
            ? TURBO_JPEG_FMT : QFileInfo(m_filename.toLower()).suffix();
    QByteArray bytes = m_volume->loadByteArrayByName(m_filename);
    QBuffer buffer(&bytes);
    QImageReader reader(&buffer, aformat.toUtf8());
    return m_dimension = reader.size();
}

void QvImageMetadata::initFileInfo()
{
    if(!m_volume->isArchive())
        m_info = QFileInfo(m_volume->getPathByFileName(m_filename));
}
