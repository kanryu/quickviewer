#ifndef PAGEMANAGER_H
#define PAGEMANAGER_H

#include <QtGui>
#include "volumemanager.h"
#include "volumemanagerbuilder.h"

class VolumeManager;
class ImageView;

class PageManagerProtocol
{
public:
    virtual int size()=0;
    virtual int currentPage()=0;
    virtual QString volumePath()=0;
};


class PageManager : public QObject, public PageManagerProtocol
{
    Q_OBJECT
public:
    PageManager(QObject* parent);

    // Volumes
    bool loadVolume(QString path, bool coverOnly=false);
    bool loadVolumeWithFile(QString path, bool prohibitProhibit2Page=false);
    void nextVolume();
    void prevVolume();
    void reloadVolumeAfterRemoveImage();

    // Pages
    void nextPage();
    void prevPage();
    void fastForwardPage();
    void fastBackwardPage();
    void selectPage(int pageNum, VolumeManager::CacheMode cacheMode=VolumeManager::Normal);
    void firstPage();
    void lastPage();
    void nextOnlyOnePage();
    void prevOnlyOnePage();
    void reloadCurrentPage(bool pageNext = true);
    void addNewPage(ImageContent ic, bool pageNext);
    void clearPages();
    QSize viewportSize();
    void setImageView(ImageView* view){m_imaveView = view;}
    void bookProgress();

    // Get String
    int currentPageCount() { return m_pages.size(); }
    int currentPage() override { return m_currentPage; }
    QVector<ImageContent>& currentPageContent() { return m_pages; }
    QString currentPagePath() {
        if(!m_fileVolume)
            return "";
        return QDir::toNativeSeparators(m_fileVolume->getPathByFileName(m_pages[0].Path));
    }
    QString nextPagePathAfterDeleted() {
        if(!m_fileVolume || m_fileVolume->isArchive() || m_fileVolume->size() <= 1)
            return "";
        int idx = m_fileVolume->size()-1==m_currentPage ? m_currentPage-1 : m_currentPage+1;
        return QDir::toNativeSeparators(m_fileVolume->getPathByIndex(idx));
    }
    QString currentPageName() { return m_pages[0].Path; }

    /**
     * @brief currentPageNumAsString: for the label text on PageBar
     * @return (10-11/2182)
     *      or (10/2182)
     */
    QString currentPageNumAsString() const;
    /**
     * @brief currentPageStatusAsString: for statusbar
     * @return some1.jpg (10-11/2182)[WIDTHxHEIGHT] | some2.jpg [WIDTHxHEIGHT]
     *      or some1.jpg (10/2182)[WIDTHxHEIGHT]
     */
    QString currentPageStatusAsString() const;
    QString pageSignage(int page) const;

    QString volumePath() override { return m_fileVolume ? m_fileVolume->volumePath() : ""; }
    QString realVolumePath() { return m_fileVolume ? m_fileVolume->realVolumePath() : ""; }
    bool isArchive() {
        if(!m_fileVolume) return false;
        return m_fileVolume->isArchive();
    }
    bool isFolder() {
        if(!m_fileVolume) return false;
        return !m_fileVolume->isArchive();
    }

    int size() override { return m_fileVolume ? m_fileVolume->size() : 0; }
    bool canDualView() const;
    void dispose() {
//        if(m_fileVolume && m_volumes.empty()) {
//            delete m_fileVolume;
//            m_pages.resize(0);
//        }
        m_pages.resize(0);
        m_fileVolume = nullptr;
        m_volumes.clear();
    }
    QStringList enumVolumes(QDir dir);

signals:
    /**
     * @brief pagesNolongerNeeded pages is no longer needed. page will be cleared
     */
    void pagesNolongerNeeded();

    void readyForPaint();
    /**
     * @brief pageChanged pages have been changed
     */
    void pageChanged();
    /**
     * @brief volumeChanged the volume has been changed
     */
    void volumeChanged(QString path);
    /**
     * @brief addNewPage add a new page. if it is dual view, 2 times called
     * @param pageNum
     */
    void pageAdded(ImageContent ic, bool pageNext);

public slots:
    void on_pageEnumerated();


private:
    VolumeManager* addVolumeCache(QString path, bool onlyCover=false, bool immediate=true);
    VolumeManager* createVolume(QString path, bool onlyCover);
    VolumeManager* passThrough(VolumeManager* vol) { return vol; }
    /**
     * @brief younger page number
     */
    int m_currentPage;

    bool m_wideImage;
    bool m_prohibit2Pages;
    QVector<ImageContent> m_pages;
    TimeOrderdCacheFuturePtr<QString, VolumeManager> m_volumes;
    QStringList m_volumenames;

    VolumeManager* m_fileVolume;
    ImageView * m_imaveView;
//    VolumeManagerBuilder m_builderForAssoc;
};

#endif // PAGEMANAGER_H
