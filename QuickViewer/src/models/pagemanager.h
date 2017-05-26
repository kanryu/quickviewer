#ifndef PAGEMANAGER_H
#define PAGEMANAGER_H

#include <QtGui>
#include "filevolume.h"

class IFileVolume;

class PageManager : public QObject
{
    Q_OBJECT
public:
    PageManager(QObject* parent);

    // Pages
    void nextPage();
    void prevPage();
    void fastForwardPage();
    void fastBackwardPage();
    void selectPage(int pageNum, IFileVolume::CacheMode cacheMode=IFileVolume::Normal);
    void firstPage();
    void lastPage();
    void nextOnlyOnePage();
    void prevOnlyOnePage();
    void reloadCurrentPage(bool pageNext = true);
    void addNewPage(ImageContent ic, bool pageNext);
    void clearPages();

    // Volumes
    bool loadVolume(QString path, bool coverOnly=false);
    void nextVolume();
    void prevVolume();

    // Get String
    int currentPageCount() { return m_pages.size(); }
    int currentPage() { return m_currentPage; }
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
    QString volumePath(){ return m_fileVolume ? m_fileVolume->volumePath() : ""; }
    bool isArchive() {
        if(!m_fileVolume) return false;
        return m_fileVolume->isArchive();
    }
    bool isFolder() {
        if(!m_fileVolume) return false;
        return !m_fileVolume->isArchive();
    }

    int size() { return m_fileVolume ? m_fileVolume->size() : 0; }
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
    void volumeChanged();
    /**
     * @brief addNewPage add a new page. if it is dual view, 2 times called
     * @param pageNum
     */
    void pageAdded(ImageContent ic, bool pageNext);

private:
    IFileVolume* addVolumeCache(QString path, bool onlyCover=false);
    /**
     * @brief younger page number
     */
    int m_currentPage;

    bool m_wideImage;
    IFileVolume* m_fileVolume;
    QVector<ImageContent> m_pages;
    TimeOrderdCachePtr<QString, IFileVolume> m_volumes;
    QStringList m_volumenames;
};

#endif // PAGEMANAGER_H
