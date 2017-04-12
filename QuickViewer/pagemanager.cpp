#include "pagemanager.h"
#include "qvapplication.h"

PageManager::PageManager(QObject* parent)
    : QObject(parent)
    , m_currentPage(0)
    , m_wideImage(false)
    , m_fileVolume(nullptr)
    , m_volumes(8)
{

}

void PageManager::nextPage()
{
    //qDebug() << "ImageView::nextPage()" << m_currentPage;
    if(m_fileVolume == nullptr) return;
    bool result = (m_fileVolume->pageCount() == m_fileVolume->size() -1) ||  m_fileVolume->nextPage();
    if(!result) return;
    m_fileVolume->setSuppressCache(false);

    int pageIncr = m_pages.size();
    m_currentPage += pageIncr;
    if(m_currentPage >= m_fileVolume->size() - pageIncr)
        m_currentPage = m_fileVolume->size() - pageIncr;

    reloadCurrentPage();
    emit pageChanged();
}

void PageManager::prevPage()
{
    if(m_fileVolume == nullptr) return;

    if(m_fileVolume->pageCount() < m_pages.size()) return;
    m_fileVolume->setSuppressCache(false);

    //QVApplication* app = qApp;
    m_currentPage--;
    if(qApp->DualView() && m_currentPage >= 1) {
        const ImageContent ic0 = m_fileVolume->getIndexedImageContent(m_currentPage);
        const ImageContent ic1 = m_fileVolume->getIndexedImageContent(m_currentPage-1);
        if(!qApp->WideImageAsOnePageInDualView() || (!ic0.wideImage() && !ic1.wideImage()))
            m_currentPage--;
    }
    if(m_currentPage < 0)
        m_currentPage = 0;
    selectPage(m_currentPage);
}

void PageManager::selectPage(int idx)
{
    //qDebug() << "PageManager::selectPage()" << idx;
    if(m_fileVolume == nullptr) return;
    bool result = m_fileVolume->findPageByIndex(idx);
    if(!result) return;
    m_currentPage = idx;

    m_fileVolume->setSuppressCache(false);
    reloadCurrentPage();
    emit pageChanged();
}

void PageManager::firstPage()
{
    m_fileVolume->setSuppressCache(false);
    selectPage(0);
}

void PageManager::lastPage()
{
    if(m_fileVolume && m_fileVolume->size() > 0) {
        m_fileVolume->setSuppressCache(false);
        selectPage(m_fileVolume->size()-1);
    }
}

void PageManager::nextOnlyOnePage()
{
    if(m_fileVolume == nullptr || m_fileVolume->pageCount() == m_fileVolume->size() -1) return;
    m_fileVolume->setSuppressCache(false);
    if(m_pages.size() == 1) {
        m_fileVolume->nextPage();
    }
    m_currentPage++;
    if(m_currentPage >= m_fileVolume->size() - 1)
        m_currentPage = m_fileVolume->size() - 1;
    reloadCurrentPage();
    emit pageChanged();
}

void PageManager::prevOnlyOnePage()
{
    if(m_fileVolume == nullptr) return;

    if(m_fileVolume->pageCount() < m_pages.size()) return;
    m_fileVolume->setSuppressCache(false);

    //QVApplication* app = qApp;
    m_currentPage--;
    if(m_currentPage < 0)
        m_currentPage = 0;
    selectPage(m_currentPage);
}

void PageManager::reloadCurrentPage(bool )
{
    //qDebug() << "ImageView::reloadCurrentPage()";
    if(m_fileVolume == nullptr) return;
    clearPages();

    const ImageContent ic0 = m_fileVolume->getIndexedImageContent(m_currentPage);
    addNewPage(ic0, true);
    m_wideImage = ic0.wideImage();
    if(!(m_currentPage==0 && qApp->FirstImageAsOnePageInDualView()) && canDualView()) {
        if(m_fileVolume->pageCount() < m_fileVolume->size()-1) {
            const ImageContent ic1 = m_fileVolume->getIndexedImageContent(m_currentPage+1);
            if(!qApp->WideImageAsOnePageInDualView() || (!ic0.wideImage() && !ic1.wideImage())) {
                m_fileVolume->nextPage();
                addNewPage(ic1, true);
            }
        }
    }
    emit readyForPaint();
}


void PageManager::addNewPage(ImageContent ic, bool pageNext)
{
    if(pageNext)
        m_pages.push_back(ic);
    else
        m_pages.push_front(ic);
    emit pageAdded(ic, pageNext);
}

void PageManager::clearPages()
{
    m_pages.resize(0);;
    emit pagesNolongerNeeded();
}

bool PageManager::loadVolume(QString path, bool onlyCover)
{
    IFileVolume* newer = addVolumeCache(path, onlyCover);
    if(!newer) {
        return false;
    }
    m_fileVolume = newer;
    m_fileVolume->setSuppressCache(onlyCover);
    m_currentPage = 0;
    // if volume is folder and the path incluces filename, pageCount() != 0
    selectPage(onlyCover ? 0 : m_fileVolume->pageCount());
    emit volumeChanged();
    return true;
}

#define PRE_LOAD_VOLUMES 4

void PageManager::nextVolume()
{
    if(!m_fileVolume)
        return;
    QDir dir(m_fileVolume->volumePath());
    QString current = dir.absolutePath();
    if(!dir.cdUp())
        return;
    int matchCount = 0;
    foreach (const QString& name, dir.entryList(QDir::Dirs | QDir::Files, QDir::Name)) {
        QString path = dir.filePath(name);
        if(path <= current)
            continue;
        if(matchCount++==0) {
            // if load new volume failed, search continue
            if(!loadVolume(path, true))
                matchCount = 0;
        } else {
            addVolumeCache(path, true);
        }
        if(matchCount >= PRE_LOAD_VOLUMES)
            break;
    }
}

void PageManager::prevVolume()
{
    if(!m_fileVolume)
        return;
    QDir dir(m_fileVolume->volumePath());
    QString current = dir.absolutePath();
    if(!dir.cdUp())
        return;
    int matchCount = 0;
    QStringList list = dir.entryList(QDir::Dirs | QDir::Files, QDir::Name);
    QListIterator<QString> it(list);it.toBack();
    while(it.hasPrevious()) {
        QString path = dir.filePath(it.previous());
        if(path >= current)
            continue;
        if(matchCount++==0) {
            // if load new volume failed, search continue
            if(!loadVolume(path, true))
                matchCount = 0;
        } else {
            addVolumeCache(path, true);
        }
        if(matchCount >= PRE_LOAD_VOLUMES)
            break;
    }
}


IFileVolume* PageManager::addVolumeCache(QString path, bool onlyCover)
{
    IFileVolume* newer = nullptr;
    if(!m_volumes.contains(path)) {
        newer = onlyCover
                ? IFileVolume::CreateVolumeWithOnlyCover(this, path)
                : IFileVolume::CreateVolume(this, path);
        if(newer)
            m_volumes.insert(path, newer);
    } else {
        m_volumes.retain(path);
        newer = m_volumes.object(path);
    }
    return newer;
}


QString PageManager::currentPageNumAsString() const
{
    if(m_pages.size() == 2) {
        return QString("(%1-%2/%3)").arg(m_currentPage+1).arg(m_currentPage+2).arg(m_fileVolume->size());
    } else {
        return QString("(%1/%3)").arg(m_currentPage+1).arg(m_fileVolume->size());
    }
}

QString PageManager::currentPageStatusAsString() const
{
    // StatusBar
    QString pagestr = currentPageNumAsString();
    QString status;
    switch(m_pages.size()) {
    case 1:
        status = QString("%1 %2[%3x%4]")
                    .arg(m_pages[0].Path)
                    .arg(pagestr)
                    .arg(m_pages[0].BaseSize.width()).arg(m_pages[0].BaseSize.height());
        break;
    case 2:
        status = QString("%1 %2[%3x%4] | %5 [%6x%7]")
                    .arg(m_pages[0].Path)
                    .arg(pagestr)
                    .arg(m_pages[0].BaseSize.width()).arg(m_pages[0].BaseSize.height())
                    .arg(m_pages[1].Path)
                    .arg(m_pages[1].BaseSize.width()).arg(m_pages[1].BaseSize.height());
        break;
    default:
        break;
    }
    return status;
}
bool PageManager::canDualView() const
{
    QVApplication* myapp = qApp;
    return qApp->DualView() && !(m_wideImage && myapp->WideImageAsOnePageInDualView());
}
