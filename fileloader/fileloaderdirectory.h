#ifndef FILEVOLUMEDIRECTORY_H
#define FILEVOLUMEDIRECTORY_H

#include <QObject>
#include <QDir>
#include "fileloader.h"


class FileLoaderDirectory : public IFileLoader
{
public:
    FileLoaderDirectory(QObject* parent, QString path);

    virtual ~FileLoaderDirectory() {}
    /**
     * @brief isArchive
     * @return return true, if the instance treates an archive file
     */
    bool isArchive() { return false; }
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
    QString realVolumePath() { return m_directory.path(); }
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
    FileLoaderDirectory(QObject* parent, QString path, int forsubclass);
    QString m_volumepath;
    QDir m_directory;
    QStringList m_imageFileList;
    QStringList m_subArchiveList;
    bool m_valid;


    virtual void initialize();
};

//class FileLoaderDirectoryPlugin : public QObject, public FileLoaderPluginInterface
//{
//    Q_OBJECT
////    Q_PLUGIN_METADATA(IID "com.quickviewer.FileLoaderDirectoryPlugin" FILE "fileloaderdirectoryplugin.json")
////    Q_INTERFACES(FileLoaderPluginInterface)
//public:
//    ~FileLoaderDirectoryPlugin() {}
//    IFileLoader* getFileLoader(QString path) { return new FileLoaderDirectory(this, path); }
//    /**
//     * @brief isSupported
//     * @return true, if the file is supported as the archive
//     */
//    bool isSupported(QString path) {
//        QDir dir(path);
//        return dir.exists() && dir.entryList(QDir::Files, QDir::Name).size() > 0;
//    }
//};

#endif // FILEVOLUMEDIRECTORY_H
