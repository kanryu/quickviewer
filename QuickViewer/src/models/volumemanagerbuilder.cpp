#include "volumemanagerbuilder.h"
#include "fileloaderdirectory.h"
#include "fileloadersubdirectory.h"
#include "fileloader7zarchive.h"
#include "fileloaderrararchive.h"
#include "pagemanager.h"
#include "qvapplication.h"

#ifndef Q_OS_WIN
#include "fileloaderziparchive.h"
#endif

VolumeManager* VolumeManagerBuilder::CreateVolume(QObject* parent, QString path, PageManager* pageManager)
{
    QDir dir(path);

    //    if(dir.exists() && dir.entryList(QDir::Files, QDir::Name).size() > 0) {
    if(dir.exists()) {
        return new VolumeManager(parent, qApp->ShowSubfolders() ? new FileLoaderSubDirectory(parent, path) : new FileLoaderDirectory(parent, path), pageManager);
    }

    QFileInfo pathinfo(path);
    QString ext = pathinfo.completeSuffix().toLower();

    // Mapping extension aliases to original names
    QString fmt = pathinfo.suffix().toLower();
    if(ext.right(3) == "cbz") { fmt = "zip"; }
    if(ext.right(3) == "cbr") { fmt = "rar"; }
    if(ext.right(3) == "cb7") { fmt = "7z"; }
    if(ext.right(6) == "tar.gz") { fmt = "tgz"; }
    if(ext.right(7) == "tar.bz2") { fmt = "tbz2"; }
    if(ext.right(6) == "tar.xz") { fmt = "txz"; }

    // RAR deploys using unrar directly
    if(fmt == "rar") {
        return new VolumeManager(parent, new FileLoaderRarArchive(parent, path), pageManager);
    }
    // Automatically recognizes various archive formats that SevenZip can deploy
    if(FileLoader7zArchive::st_supportedArchiveFormats.contains(fmt)) {
        return new VolumeManager(parent, new FileLoader7zArchive(parent, path, fmt, qApp->ExtractSolidArchiveToTemporaryDir()), pageManager);
    }




//    QString lower = path.toLower();
//    if(lower.endsWith(".zip") || lower.endsWith(".cbz")) {
////#ifdef Q_OS_WIN
////        return new VolumeManager(parent, new FileLoader7zArchive(parent, path), pageManager);
////#else
////        return new VolumeManager(parent, new FileLoaderZipArchive(parent, path), pageManager);
////#endif
//        return new VolumeManager(parent, new FileLoader7zArchive(parent, path, "zip", qApp->ExtractSolidArchiveToTemporaryDir()), pageManager);
//    }
//    if(lower.endsWith(".7z")) {
//        return new VolumeManager(parent, new FileLoader7zArchive(parent, path, "7z", qApp->ExtractSolidArchiveToTemporaryDir()), pageManager);
//    }
//    if(lower.endsWith(".rar") || lower.endsWith(".cbr")) {
//        return new VolumeManager(parent, new FileLoaderRarArchive(parent, path), pageManager);
//    }
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

VolumeManagerBuilder::VolumeManagerBuilder(QString path, PageManager *pageManager)
    : QObject(pageManager)
    , Path(path)
    , m_pageManager(pageManager)
    , m_volumeManager(nullptr)
{
//    connect(&m_watcher, SIGNAL(finished()), this, SLOT(on_enumerated()));
}

VolumeManager *VolumeManagerBuilder::build(bool onlyCover)
{
    QString pathbase = QDir::toNativeSeparators(Path);
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
    if(m_volumeManager->size() == 0) {
        delete m_volumeManager;
        return m_volumeManager = nullptr;
    }
    VolumeManager::CacheMode mode = onlyCover ? VolumeManager::CoverOnly : VolumeManager::Normal;
    m_volumeManager->setCacheMode(mode);
    if(Filenames.isEmpty()) {
        checkBookProgress();
    } else if(subfilename.length() > 0) {
        m_volumeManager->findImageByName(subfilename);
    }
    m_volumeManager->on_ready();
    return m_volumeManager;
}

VolumeManager* VolumeManagerBuilder::buildAsync(QString path, PageManager* manager, bool onlyCover)
{
    VolumeManagerBuilder builder(path, manager);
    return builder.build(onlyCover);
}

VolumeManager *VolumeManagerBuilder::buildForAssoc()
{
    QDir dir(QDir::toNativeSeparators(Path));
    dir.cdUp();
    // If it is the root directory of the Windows drive, the separator will be attached at the end
    // e.g. "C:/"
    QString volumeFolder = dir.canonicalPath();
    m_subfilename = volumeFolder.length()==3 && volumeFolder[1]==':'
            ? Path.mid(volumeFolder.length())
            : Path.mid(volumeFolder.length()+1);
    if(!(m_volumeManager = CreateVolume(nullptr, dir.canonicalPath(), m_pageManager)))
        return m_volumeManager;
    if(m_volumeManager->isArchive()) {
        delete m_volumeManager;
        return m_volumeManager = nullptr;
    }

    m_volumeManager->moveToThread(QThread::currentThread());
    // load the image
    Ic = m_volumeManager->getImageBeforeEnmumerate(m_subfilename);

    return m_volumeManager;
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
