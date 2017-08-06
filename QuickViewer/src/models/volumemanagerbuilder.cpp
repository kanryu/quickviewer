#include "volumemanagerbuilder.h"
#include "fileloaderdirectory.h"
#include "fileloadersubdirectory.h"
#include "fileloaderziparchive.h"
#include "fileloader7zarchive.h"
#include "fileloaderrararchive.h"
#include "pagemanager.h"
#include "qvapplication.h"

VolumeManager* VolumeManagerBuilder::CreateVolume(QObject* parent, QString path, PageManager* pageManager)
{
    QDir dir(path);

    //    if(dir.exists() && dir.entryList(QDir::Files, QDir::Name).size() > 0) {
    if(dir.exists()) {
        return new VolumeManager(parent, qApp->ShowSubfolders() ? new FileLoaderSubDirectory(parent, path) : new FileLoaderDirectory(parent, path), pageManager);
    }
    QString lower = path.toLower();
    if(lower.endsWith(".zip") || lower.endsWith(".cbz")) {
        return new VolumeManager(parent, new FileLoaderZipArchive(parent, path), pageManager);
    }
    if(lower.endsWith(".7z")) {
        return new VolumeManager(parent, new FileLoader7zArchive(parent, path), pageManager);
    }
    if(lower.endsWith(".rar") || lower.endsWith(".cbr")) {
        return new VolumeManager(parent, new FileLoaderRarArchive(parent, path), pageManager);
    }
    if(IFileLoader::isImageFile(path)) {
        dir.cdUp();
        QString dirpath = dir.canonicalPath();
        VolumeManager* fvd = new VolumeManager(parent, qApp->ShowSubfolders() ? new FileLoaderSubDirectory(parent, path) : new FileLoaderDirectory(parent, dirpath), pageManager);
        fvd->findImageByName(path.mid(dirpath.length()+1));
        fvd->setOpenedWithSpecifiedImageFile(true);
        return fvd;
    }
    return nullptr;
}

VolumeManagerBuilder::VolumeManagerBuilder(QString path, PageManager *pageManager, QStringList images)
    : QObject(pageManager)
    , Path(path)
    , Filenames(images)
    , m_pageManager(pageManager)
    , m_volumeManager(nullptr)
{
    connect(&m_watcher, SIGNAL(finished()), this, SLOT(on_enumerated()));
}

VolumeManager *VolumeManagerBuilder::build(bool onlyCover)
{
    QString pathbase = Path;
    QString subfilename;
    if(Path.contains("::")) {
        QStringList seps = Path.split("::");
        pathbase = seps[0];
        subfilename = seps[1];
    }
    if(!(m_volumeManager = CreateVolume(nullptr, pathbase, m_pageManager)))
        return m_volumeManager;

    m_volumeManager->moveToThread(QThread::currentThread());
    m_volumeManager->enumerate();
    VolumeManager::CacheMode mode = onlyCover ? VolumeManager::Normal : VolumeManager::CoverOnly;
    m_volumeManager->setCacheMode(mode);
    if(Filenames.isEmpty()) {
        checkBookProgress();
    } else if(subfilename.length() > 0) {
        m_volumeManager->findImageByName(subfilename);
    }
    m_volumeManager->on_ready();
    return m_volumeManager;
}

QFuture<VolumeManager *> VolumeManagerBuilder::buildAsync(bool onlyCover)
{
    return QtConcurrent::run(this, &VolumeManagerBuilder::build, onlyCover);
}

VolumeManager *VolumeManagerBuilder::buildForAssoc()
{
    QDir dir(Path);
    dir.cdUp();
    m_subfilename = Path.mid(dir.canonicalPath().length()+1);
    if(!(m_volumeManager = CreateVolume(nullptr, dir.canonicalPath(), m_pageManager)))
        return m_volumeManager;

    m_volumeManager->moveToThread(QThread::currentThread());
    m_watcher.setFuture(QtConcurrent::run(m_volumeManager, &VolumeManager::enumerate));

    // load the image
    Ic = VolumeManager::futureLoadImageFromFileVolume(m_volumeManager, m_subfilename, QSize());

    return m_volumeManager;
}

void VolumeManagerBuilder::on_enumerated()
{
    static int cnt = 0;cnt++;
    qDebug() << "on_enumerated" << cnt;
    m_volumeManager->findImageByName(m_subfilename);
    m_volumeManager->setCacheMode(VolumeManager::Normal);
    m_volumeManager->on_ready();
    m_pageManager->on_pageEnumerated();
}

ImageContent VolumeManagerBuilder::thumbnail()
{
    if(!(m_volumeManager = CreateVolume(nullptr, Path, m_pageManager)))
        return ImageContent();
    checkBookProgress();
    m_volumeManager->setCacheMode(VolumeManager::CreateThumbnail);
    m_volumeManager->on_ready();
    auto ic = m_volumeManager->currentImage();
    delete m_volumeManager;
    return ic;
}

void VolumeManagerBuilder::checkBookProgress()
{
    // change page by progress.ini
    QString volumepath = QDir::fromNativeSeparators(m_volumeManager->volumePath());
    if(qApp->OpenVolumeWithProgress()
       && !m_volumeManager->openedWithSpecifiedImageFile()
       && qApp->bookshelfManager()->contains(volumepath)) {
        BookProgress book = qApp->bookshelfManager()->at(volumepath);
        m_volumeManager->findPageByIndex(book.Current);
    }
    m_volumeManager->moveToThread(QThread::currentThread());
}
