#ifndef VOLUMEMANAGER_H
#define VOLUMEMANAGER_H

#include <QtCore>
#include <QtGui>
#include <QtConcurrent>

#include "fileloader.h"
#include "timeorderdcache.h"
#include "pagecontent.h"

class PageManager;
class VolumeManagerBuilder;
/**
 * @brief The VolumeManager class
 *
 * This class manages a Volume (Folder or Archive).
 * Image pre-reading is performed by the prefetch algorithm specified by CacheMode.
 * Images in Volume are listed in advance and can be opened with numbers or subpaths.
 * The loaded image is cached by the FIFO method(TimeOrderdCache).
 */
class VolumeManager : public QObject
{
    Q_OBJECT
//    Q_DISABLE_COPY(IFileVolume)
public:
    enum CacheMode
    {
        Normal,
        NormalForward,
        NormalBackward,
        FastForward,
        FastBackrard,
        CoverOnly,
        CreateThumbnail,
    };

    typedef QFuture<ImageContent> future_image;

    explicit VolumeManager(QObject *parent, IFileLoader* loader, PageManager* pageManager);
    ~VolumeManager();
    void enumerate();
    bool enumerated() { return m_enumerated; }
    ImageContent getImageBeforeEnmumerate(QString subfilename);

    static ImageContent futureLoadImageFromFileVolume(VolumeManager* volume, QString path, QSize pageSize);
    static ImageContent futureReizeImage(ImageContent ic, QSize pageSize);
    static QString FullPathToVolumePath(QString path);
    static QString FullPathToSubFilePath(QString path);

    bool isArchive() const { return m_loader->isArchive(); }
    bool hasSubDirectories() const { return m_loader->hasSubDirectories(); }


    QString currentPath() {
        if(m_loader->isArchive())
            return QString("%1::%2")
                    .arg(QDir::fromNativeSeparators(m_loader->volumePath()))
                    .arg(m_filelist[m_cnt]);
        else
            return QDir::fromNativeSeparators(QDir(m_loader->volumePath()).absoluteFilePath(m_filelist[m_cnt]));
    }
    QString getPathByFileName(QString name) {
        if(m_loader->isArchive())
            return QString("%1::%2")
                    .arg(QDir::fromNativeSeparators(m_loader->volumePath()))
                    .arg(name);
        else
            return QDir(m_loader->realVolumePath()).absoluteFilePath(name);
    }
    QString getIndexedFileName(int idx) {
        if(idx < 0 || idx >= m_filelist.size())
            return "";
        return m_filelist[idx];
    }
    QString getPathByIndex(int idx) {
        if(idx < 0 || idx >= m_filelist.size())
            return "";
        return QDir(m_loader->volumePath()).absoluteFilePath(m_filelist[idx]);
    }
    void setCacheMode(CacheMode cachemode) { m_cacheMode = cachemode; }
    CacheMode cacheMode() const { return m_cacheMode; }


    const ImageContent currentImage() { return m_cacheMode == CreateThumbnail ? m_currentCacheSync : m_currentCache.result(); }
    QString volumePath() { return m_loader->volumePath(); }
    QString realVolumePath() { return m_loader->realVolumePath(); }

    bool nextPage();
    bool prevPage();
    bool findPageByIndex(int idx);

    /**
     * @brief Move to the file corresponding to the idx value specified in the file list(Max is size()-1)
     */
    bool findImageByIndex(int idx);

    /**
     * @brief Move to the file corresponding to the file name specified in the current file list
     */
    bool findImageByName(QString name);

    /**
     * @brief loadImageByName Reads and returns the image corresponding to the file name specified in the file list without advancing the internal counter
     */
    QByteArray loadByteArrayByName(const QString& name) { return m_loader->getFile(name, m_mutex); }
    /**
     * @brief Returns the number of pages the volume has
     */
    int size() { return m_filelist.size(); }
    /**
     * @brief on_ready Called when the application is ready. First, or the image to be displayed next and its file path are emitted
     */
    void on_ready();
    int pageCount() { return m_cnt; }

//    QPixmap getIndexedImage(int idx);
//    QString getIndexedImageName(int idx) { return m_filelist[idx]; }
//    QString currentImageName() const { return m_filelist[m_cnt]; }
    const ImageContent getIndexedImageContent(int idx);
    bool openedWithSpecifiedImageFile() { return m_openedWithSpecifiedImageFile; }
    void setOpenedWithSpecifiedImageFile(bool openedWithSpecifiedImageFile) { m_openedWithSpecifiedImageFile = openedWithSpecifiedImageFile; }
    void moveToThread(QThread *targetThread);

public slots:
    void on_enmumerated();

private:
    /**
     * @brief m_cnt File counter in the volume
     */
    int m_cnt;
    QList<QString> m_filelist;
    future_image m_currentCache;
    ImageContent m_currentCacheSync;

    TimeOrderdCacheFuture<int, ImageContent> m_imageCache;
//    QMap<int, future_image> m_imageCache;
//    QList<int> m_pageCache;

    QMutex m_mutex;

    IFileLoader* m_loader;
    CacheMode m_cacheMode;
    PageManager* m_pageManager;
    bool m_enumerated;
    bool m_openedWithSpecifiedImageFile;
    QString m_volumePath;

    // fast image loading
    QString m_subfilename;
    QFutureWatcher<void> m_watcher;

    friend class VolumeManagerBuilder;
};


#endif // VOLUMEMANAGER_H
