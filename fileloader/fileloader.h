#ifndef FILELOADER_H
#define FILELOADER_H

#include <QObject>
#include <QMutex>
#include <QtCore/qplugin.h>



/**
 * @brief The FileLoader class
 * Abstract file reading processing.
 * It can be external plugin.
 */
class IFileLoader : public QObject
{
    Q_OBJECT
    enum ScanMode {
        Normal,
        ToFastImage, // header scan, and return an image, and end(without worker)
        ToAllFilesExtract, // header scan, and read all archived file under worker thread
    };

public:
    IFileLoader(QObject* parent) : QObject(parent) {}
    virtual ~IFileLoader() {}
    /**
     * @brief isImageFile check the file will be a image file
     * @param path
     * @return return true, if path of file maybe a image file
     */
    static bool isImageFile(QString path);
    /**
     * @brief isArchiveFile check the file will be an archive file
     * @param path
     * @return return true, if path of file maybe an archive file
     */
    static bool isArchiveFile(QString path);
    /**
     * @brief isExifImageFile check the file will have exif
     * @param path
     * @return return true, if path of file maybe have exif
     */
    static bool isExifJpegImageFile(QString path);
    static bool isExifRawImageFile(QString path);
    /**
     * @brief fileSort sort the filenames as current sorting policy
     * @param filenames
     * @return
     */
    static void sortFiles(QStringList& filenames);
    static bool caseInsensitiveLessThan(const QString &s1, const QString &s2);
    /**
     * @brief volumePath
     * @return path which is param of constructor
     */
    virtual QString volumePath()=0;
    virtual QString realVolumePath()=0;
    /**
     * @brief isArchive
     * @return return true, if the instance treates an archive file
     */
    virtual bool isArchive()=0;
    /**
     * @brief isValid
     * @return return true, if the instance can load images
     */
    virtual bool isValid()=0;
    /**
     * @brief contents
     * @return all image files without parent path(filename only)
     */
    virtual QStringList contents()=0;
    /**
     * @brief subArchives
     * @return all archive files with in the instance
     */
    virtual QStringList subArchives()=0;
    /**
     * @brief getFile get a file specified by filename
     * @param filename
     * @param mutex if the method needs to lock resource, must be use the mutex
     * @return file binary data
     */
    virtual QByteArray getFile(QString filename, QMutex& mutex)=0;

signals:
    void imageLoaded(QString name, QByteArray data);
    void loadFinished();

private:
    static QList<QByteArray> st_supportedImageFormats;
    static QStringList st_exifJpegImageFormats;
    static QStringList st_exifRawImageFormats;
};

class FileLoaderPluginInterface
{
public:
    virtual ~FileLoaderPluginInterface() {}
    virtual IFileLoader* getFileLoader(QString path)=0;
    /**
     * @brief isSupported
     * @return true, if the file is supported as the archive
     */
    virtual bool isSupported(QString path)=0;
};

//Q_DECLARE_INTERFACE(FileLoaderPluginInterface,
//                    "com.quickviewer.FileLoaderPlugin/1.0")

#endif // FILELOADER_H
