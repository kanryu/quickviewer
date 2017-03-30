#ifndef FILELOADERRARARCHIVE_H
#define FILELOADERRARARCHIVE_H


#include <QObject>
#include <QMap>
#include "fileloader.h"
#include "qtrar.h"

class FileLoaderRarArchive : public IFileLoader
{
public:
    /**
     * @brief 新しいディレクトリを設定する
     * @param dir
     */
    FileLoaderRarArchive(QObject* parent, QString rarpath);

    ~FileLoaderRarArchive() {}
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
    QtRAR m_archive;
//    QMap<QString, Qt7zFileInfo> m_fileinfomap;
    QStringList m_imageFileList;
    QStringList m_subArchiveList;
    bool m_valid;
};

class FileLoaderRarPlugin : public QObject, public FileLoaderPluginInterface
{
    Q_OBJECT
//    Q_PLUGIN_METADATA(IID "com.quickviewer.FileLoader7zPlugin" FILE "fileloader7zplugin.json")
//    Q_INTERFACES(FileLoaderPluginInterface)
public:
    ~FileLoaderRarPlugin() {}
    IFileLoader* getFileLoader(QString path) { return new FileLoaderRarArchive(this, path); }
    /**
     * @brief isSupported
     * @return true, if the file is supported as the archive
     */
    bool isSupported(QString path) { return path.toLower().endsWith(".rar"); }
};
#endif // FILELOADERRARARCHIVE_H
