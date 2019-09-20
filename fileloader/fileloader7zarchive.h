#ifndef FILEVOLUME7ZARCHIVE_H
#define FILEVOLUME7ZARCHIVE_H

#include <QtCore>
#include "fileloader.h"
class FileLoader7zArchivePrivate;

class FileLoader7zArchive : public IFileLoader
{
public:
    FileLoader7zArchive(QObject* parent, QString sevenzippath, QString extensionOfFile, bool extractSolidArchiveToTemporaryDir=false);

    ~FileLoader7zArchive();
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
    bool hasSubDirectories() override { return true; }
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
    QStringList contents();
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

    /**
     * @brief getCacheMode
     *
     * Indicates the state when Volume created or has already been decompressed.
     */
    InflateCacheMode getCacheMode() { return m_cacheMode; }

    static bool initializeLib();
    static bool isInitialized();
    static void uninitializeLib();
    static QStringList st_supportedArchiveFormats;

protected:
    FileLoader7zArchivePrivate* d;
    QString m_volumepath;
    QString m_extensionOfFile;
    QStringList m_imageFileList;
    QStringList m_subArchiveList;
    bool m_valid;
    InflateCacheMode m_cacheMode;

    bool m_extractSolidArchiveToTemporaryDir;
    QFutureWatcher<void> watcher;
    QTemporaryDir* m_temp;


    void initialize();
};

//class FileLoader7zPlugin : public QObject, public FileLoaderPluginInterface
//{
//    Q_OBJECT
////    Q_PLUGIN_METADATA(IID "com.quickviewer.FileLoader7zPlugin" FILE "fileloader7zplugin.json")
////    Q_INTERFACES(FileLoaderPluginInterface)
//public:
//    ~FileLoader7zPlugin() {}
//    IFileLoader* getFileLoader(QString path) { return new FileLoader7zArchive(this, path); }
//    /**
//     * @brief isSupported
//     * @return true, if the file is supported as the archive
//     */
//    bool isSupported(QString path) { return path.toLower().endsWith(".7z"); }
//};



#endif // FILEVOLUME7ZARCHIVE_H
