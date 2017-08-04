#include "pagemanager.h"
#include "qvapplication.h"
#include "imageview.h"
#include "fileloadersubdirectory.h"

PageManager::PageManager(QObject* parent)
    : QObject(parent)
    , m_currentPage(0)
    , m_wideImage(false)
    , m_fileVolume(nullptr)
    , m_volumes(qApp->MaxVolumesCache())
{

}

bool PageManager::loadVolume(QString path, bool coverOnly)
{
    if(m_fileVolume && m_pages.size() == 2) {
        m_fileVolume->prevPage();
    }
    clearPages();
    m_fileVolume = nullptr;
    IFileVolume* newer = addVolumeCache(path, coverOnly);
    if(!newer) {
        emit volumeChanged("");
        return false;
    }
    m_fileVolume = newer;
    if(coverOnly) {
        m_fileVolume->setCacheMode(IFileVolume::CoverOnly);
    } else {
        m_volumenames = QStringList();
    }
    m_currentPage = 0;
    emit volumeChanged(m_fileVolume->volumePath());
    // if volume is folder and the path incluces filename, pageCount() != 0
    selectPage(coverOnly ? 0 : m_fileVolume->pageCount());
    return true;
}

#define PRE_LOAD_VOLUMES 4

void PageManager::nextVolume()
{
    if(!m_fileVolume)
        return;
    QDir dir(m_fileVolume->volumePath());
    QFileInfo fileinfo(m_fileVolume->volumePath());
    QString current = fileinfo.fileName();
    if(!dir.cdUp())
        return;
    if(m_volumenames.size() == 0) {
        m_volumenames = dir.entryList(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Files, QDir::Name);
        IFileLoader::sortFiles(m_volumenames);
    }
    bool beforeMatch = true;
    int preloadCount = 0;
    foreach (const QString& name, m_volumenames) {
        if(beforeMatch) {
            if(name == current)
                beforeMatch = false;
            continue;
        }
        QString path = dir.filePath(name);
        if(preloadCount++==0) {
            // if load new volume failed, search continue
            if(!loadVolume(path, true))
                preloadCount = 0;
        } else {
            addVolumeCache(path, true, false);
        }
        // preloadCount <- MaxVolumesCache()
        // 0            <- 1
        // 0            <- 2
        // 1            <- 3
        // 1            <- 4
        // 2            <- 5
        // 3            <- 6
        // 4            <- 7
        // 4            <- 8
        // 5            <- 9
        // 6            <-10
        if(preloadCount >= (qApp->MaxVolumesCache()-1)*2/3)
            break;
    }
}

void PageManager::prevVolume()
{
    if(!m_fileVolume)
        return;
    QDir dir(m_fileVolume->volumePath());
    QFileInfo fileinfo(m_fileVolume->volumePath());
    QString current = fileinfo.fileName();
    if(!dir.cdUp())
        return;
    int matchCount = 0;
    if(m_volumenames.size() == 0) {
        m_volumenames = dir.entryList(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Files, QDir::Name);
        IFileLoader::sortFiles(m_volumenames);
    }
    QListIterator<QString> it(m_volumenames);it.toBack();
    bool beforeMatch = true;
    while(it.hasPrevious()) {
        QString name = it.previous();
        if(beforeMatch) {
            if(name == current)
                beforeMatch = false;
            continue;
        }
        QString path = dir.filePath(name);
        if(matchCount++==0) {
            // if load new volume failed, search continue
            if(!loadVolume(path, true))
                matchCount = 0;
        } else {
            addVolumeCache(path, true, false);
        }
        if(matchCount >= qApp->MaxVolumesCache()*3/2-1)
            break;
    }
}


IFileVolume* PageManager::addVolumeCache(QString path, bool onlyCover, bool immediate)
{
    IFileVolume* newer = nullptr;
    QString pathbase = IFileVolume::FullPathToVolumePath(path);
    QString subfilename = IFileVolume::FullPathToSubFilePath(path);
    if(m_volumes.contains(pathbase)) {
        if(!immediate)
            return nullptr;
        IFileVolume* cached = m_volumes.object(pathbase);
        if(!cached) {
            m_volumes.remove(pathbase);
            return nullptr;
        }
        // If the subdirectory search is switched valid, we need to recreate the instance
        if(!cached->isArchive() &&
                ((qApp->ShowSubfolders() && dynamic_cast<FileLoaderSubDirectory*>(cached)!=nullptr)
                 || (!qApp->ShowSubfolders() && dynamic_cast<FileLoaderSubDirectory*>(cached)==nullptr))) {
            m_volumes.remove(pathbase);
        }
    }
    if(!m_volumes.contains(pathbase)) {
        if(immediate) {
            newer = createVolume(path, onlyCover);
            if(newer)
                m_volumes.insert(pathbase, QtConcurrent::run(this, &PageManager::passThrough, newer));
            return newer;
        } else {
            m_volumes.insert(pathbase, QtConcurrent::run(this, &PageManager::createVolume, path, onlyCover));
        }
    } else {
        m_volumes.retain(pathbase);
        newer = m_volumes.object(pathbase);
        if(subfilename.length())
            newer->findImageByName(subfilename);
    }
    return newer;
}

IFileVolume *PageManager::createVolume(QString path, bool onlyCover)
{
    IFileVolume* newer = onlyCover
            ? IFileVolume::CreateVolumeWithOnlyCover(nullptr, path, this)
            : IFileVolume::CreateVolume(nullptr, path, this);
    if(newer) {
        // change page by progress.ini
        QString volumepath = QDir::fromNativeSeparators(newer->volumePath());
        if(qApp->OpenVolumeWithProgress()
           && !newer->openedWithSpecifiedImageFile()
           && qApp->bookshelfManager()->contains(volumepath)) {
            BookProgress book = qApp->bookshelfManager()->at(volumepath);
            newer->findPageByIndex(book.Current);
        }
        newer->moveToThread(thread());
    }
    return newer;
}

void PageManager::nextPage()
{
    //qDebug() << "ImageView::nextPage()" << m_currentPage;
    if(m_fileVolume == nullptr || m_fileVolume->pageCount() >= m_fileVolume->size()-1) return;

    m_fileVolume->setCacheMode(IFileVolume::NormalForward);
    bool result = m_fileVolume->nextPage();
    if(!result) return;

    int pageIncr = m_pages.size();
    m_currentPage += pageIncr;
    if(m_currentPage >= m_fileVolume->size() - 1)
        m_currentPage = m_fileVolume->size() - 1;


    reloadCurrentPage();
    bookProgress();
    emit pageChanged();
}

void PageManager::prevPage()
{
    if(m_fileVolume == nullptr) return;
    if(m_fileVolume->pageCount() < m_pages.size()) return;

    m_fileVolume->setCacheMode(IFileVolume::NormalBackward);
    bool result = m_fileVolume->prevPage();
    if(!result) return;
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

    bookProgress();

    selectPage(m_currentPage, IFileVolume::NormalBackward);
}

#define PAGE_INTERVAL 10

void PageManager::fastForwardPage()
{
    if(m_fileVolume == nullptr) return;
    if(m_fileVolume->pageCount() == m_fileVolume->size() -1) return;
    m_currentPage += PAGE_INTERVAL;
    if(m_currentPage >= m_fileVolume->size() -1)
        m_currentPage = m_fileVolume->size() -1;

    selectPage(m_currentPage, IFileVolume::FastForward);
}

void PageManager::fastBackwardPage()
{
    if(m_fileVolume == nullptr) return;
    if(m_fileVolume->pageCount() < m_pages.size()) return;

    m_currentPage -= PAGE_INTERVAL;
    if(m_currentPage < 0)
        m_currentPage = 0;
    selectPage(m_currentPage, IFileVolume::FastForward);
}

void PageManager::selectPage(int idx, IFileVolume::CacheMode cacheMode)
{
    //qDebug() << "PageManager::selectPage()" << idx;
    if(m_fileVolume == nullptr) return;
    m_fileVolume->setCacheMode(cacheMode);
    bool result = m_fileVolume->findPageByIndex(idx);
    if(!result) return;
    m_currentPage = idx;

    reloadCurrentPage();
    emit pageChanged();
}

void PageManager::firstPage()
{
    m_fileVolume->setCacheMode(IFileVolume::Normal);
    selectPage(0);
}

void PageManager::lastPage()
{
    if(m_fileVolume && m_fileVolume->size() > 0) {
        m_fileVolume->setCacheMode(IFileVolume::Normal);
        selectPage(m_fileVolume->size()-1);
    }
}

void PageManager::nextOnlyOnePage()
{
    if(m_fileVolume == nullptr || m_fileVolume->pageCount() == m_fileVolume->size() -1) return;
    m_fileVolume->setCacheMode(IFileVolume::Normal);
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
    m_fileVolume->setCacheMode(IFileVolume::Normal);

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
    ic.initialize();
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

QSize PageManager::viewportSize()
{
    return m_imaveView->viewport()->size();
}

void PageManager::bookProgress()
{
    QString path = QDir::fromNativeSeparators(m_fileVolume->volumePath());
    BookProgress book = {
        QFileInfo(m_fileVolume->volumePath()).fileName(),
        path,
        m_fileVolume->getIndexedFileName(m_currentPage),
        m_fileVolume->size(),
        m_currentPage,
        false
    };
    if(m_currentPage + m_pages.size() >= size()) {
        book.Completed = true;
        book.Current = 0;
    }
    qApp->bookshelfManager()->insert(path, book);
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

QString PageManager::pageSignage(int page) const
{
    if(m_pages.size() <= page)
        return "";
    return QString("%1 (%2/%3)")
            .arg(QDir::toNativeSeparators(m_fileVolume->getPathByFileName(m_pages[page].Path)))
            .arg(m_currentPage+1+page)
            .arg(m_fileVolume->size());
}
bool PageManager::canDualView() const
{
    QVApplication* myapp = qApp;
    return qApp->DualView() && !(m_wideImage && myapp->WideImageAsOnePageInDualView());
}
