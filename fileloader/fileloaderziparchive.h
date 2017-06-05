#ifndef FILEVOLUMEZIPARCHIVE_H
#define FILEVOLUMEZIPARCHIVE_H

#include <QObject>
//#include <QtGui/private/qzipreader_p.h>
#include "fileloader.h"

class QuaZip;

class FileLoaderZipArchive : public IFileLoader
{
public:
    FileLoaderZipArchive(QObject* parent, QString zippath);

    ~FileLoaderZipArchive() {}
    /**
     * @brief isArchive
     * @return return true, if the instance treates an archive file
     */
    bool isArchive() { return true; }
    /**
     * @brief isValid
     * @return return true, if the instance can load images
     */
    bool isValid() { return m_valid; }
    /**
     * @brief volumePath
     * @return the path of the instance
     */
    QString volumePath() { return m_volumepath; }
    QString realVolumePath() { return volumePath(); }

    /**
     * @brief contents
     * @return all image files without parent path(filename only)
     */
    QStringList contents() { return m_imageFileList; }
    /**
     * @brief subArchives
     * @return all archive files with in the instance
     */
    QStringList subArchives() { return m_subArchiveList; }
    /**
     * @brief getFile get a file specified by filename
     * @param filename
     * @param mutex if the method needs to lock resource, must be use the mutex
     * @return file binary data
     */
    QByteArray getFile(QString filename, QMutex& mutex);

protected:
    QString m_volumepath;
    QuaZip* d;
    QStringList m_imageFileList;
    QStringList m_subArchiveList;
    bool m_valid;
};

class FileLoaderZipPlugin : public QObject, public FileLoaderPluginInterface
{
    Q_OBJECT
//    Q_PLUGIN_METADATA(IID "com.quickviewer.FileLoaderZipPlugin" FILE "fileloaderzipplugin.json")
//    Q_INTERFACES(FileLoaderPluginInterface)
public:
    ~FileLoaderZipPlugin() {}
    IFileLoader* getFileLoader(QString path) { return new FileLoaderZipArchive(this, path); }
    /**
     * @brief isSupported
     * @return true, if the file is supported as the archive
     */
    bool isSupported(QString path) { return path.toLower().endsWith(".zip"); }
};


#endif // FILEVOLUMEZIPARCHIVE_H
