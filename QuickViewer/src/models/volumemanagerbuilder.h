#ifndef VOLUMEMANAGERBUILDER_H
#define VOLUMEMANAGERBUILDER_H

#include <QtGui>
#include <QtConcurrent>
#include "volumemanager.h"

class VolumeManagerBuilder : QObject
{
    Q_OBJECT
public:
    QString Path;
    QStringList Filenames;
    ImageContent Ic;

    VolumeManagerBuilder(QString path, PageManager* pageManager=nullptr, QStringList images=QStringList());

    /**
     * @brief build
     * @param onlyCover specifies to prefetch only the cover page
     *
     * Generate VolumeManager synchronously.
     */
    VolumeManager* build(bool onlyCover);

    /**
     * @brief build
     * @param onlyCover specifies to prefetch only the cover page
     *
     * Generate VolumeManager asynchronously.
     */
    static VolumeManager* buildAsync(QString path, PageManager* manager, bool onlyCover);

    /**
     * @brief buildForAssoc
     *
     * Special initialization method to skip the enumeration of image files
     * in the Volume and read the first image faster.
     */
    VolumeManager* buildForAssoc();

    /**
     * @brief thumbnail
     *
     * Read and return the image of the youngest file name in Volume
     */
    ImageContent thumbnail();

    void checkBookProgress();
    /**
     * @brief A factory function that returns an instance of IFileVolume from the path of the specified file or directory
     * @return An object that inherits the IFileVolume interface. It is null if generation failed
     */
    static VolumeManager* CreateVolume(QObject* parent, QString path, PageManager* pageManager);

//public slots:
//    void on_enumerated();

private:
    PageManager* m_pageManager;
    VolumeManager* m_volumeManager;
//    QFutureWatcher<void> m_watcher;
    QString m_subfilename;
};


#endif // VOLUMEMANAGERBUILDER_H
