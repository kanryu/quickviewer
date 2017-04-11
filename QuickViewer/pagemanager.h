#ifndef PAGEMANAGER_H
#define PAGEMANAGER_H

#include <QtGui>
#include <filevolume.h>

class IFileVolume;

class PageManager
{
public:
    PageManager();
    bool nextPage();
    bool prevPage();
    bool selectPage(int pageNum);

    bool nextVolume();
    bool prevVolume();

    bool loadVolume(QString path);

    QList<ImageContent>& currentPage() { return pageContents; }
    QString currentPagePath() {
        if(!m_fileVolume || m_fileVolume->isArchive() || pageContents.empty())
            return "";
        return m_fileVolume->getPathByFileName(pageContents[0].Path);
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
    bool isArchive() { return m_fileVolume ? m_fileVolume->isArchive() : false; }

    int size() { return m_fileVolume ? m_fileVolume->size() : 0; }

signals:
    /**
     * @brief pagesNolongerNeeded pages is no longer needed. page will be cleared
     */
    void pagesNolongerNeeded();
    /**
     * @brief pageChanged pages have been changed
     */
    void pageChanged();
    /**
     * @brief addNewPage add a new page. if it is dual view, 2 times called
     * @param pageNum
     */
    void addNewPage(ImageContent ic);
private:
    /**
     * @brief 現在表示しているページのうち最も若い番号。filevolume側の内部ページと異なる場合があるので注意
     */
    int m_currentPage;

    bool m_wideImage;
    IFileVolume* m_fileVolume;
    QList<ImageContent> pageContents;
};

#endif // PAGEMANAGER_H
