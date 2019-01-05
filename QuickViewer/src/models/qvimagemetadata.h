#ifndef QVIMAGEMETADATA_H
#define QVIMAGEMETADATA_H

#include <QtCore>

class VolumeManager;

/**
 * @brief The QvImageMetadata class
 *
 * This class holds various attributes of image files, such as file names and file sizes,
 * and provides a function to retrieve them when necessary.
 */
class QvImageMetadata : QObject
{
    Q_OBJECT
public:
    QvImageMetadata(VolumeManager* volume, QString filename);
    QvImageMetadata(const QvImageMetadata& rhs)
    {
        *this = rhs;
    }
    QvImageMetadata& operator=(const QvImageMetadata& rhs)
    {
        m_volume = rhs.m_volume;
        m_filename = rhs.m_filename;
        m_info = rhs.m_info;
        m_dimension = rhs.m_dimension;
        return *this;
    }

    QString filename() const {return m_filename;}
    QDateTime getMTime();
    qint64 getFileSize();
    QSize getDimension();


private:
    void initFileInfo();
    VolumeManager* m_volume;
    QString m_filename;
    QFileInfo m_info;
    QSize m_dimension;
};

#endif // QVIMAGEMETADATA_H
