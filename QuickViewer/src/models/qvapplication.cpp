#include <QtGui>
#include <QtOpenGL>

#ifdef Q_OS_WIN
#include <shlobj.h>
#endif

#include "qvapplication.h"
#include "qv_init.h"
#include "ui_mainwindow.h"

QVApplication::QVApplication(int &argc, char **argv)
    : QApplication(argc, argv)
    , m_settings(getApplicationFilePath(APP_INI), QSettings::IniFormat, this)
    , m_effect(qvEnums::Bilinear)
    , m_glInitialized(false)
    , m_maxTextureSize(4096)
    , m_bookshelfManager(nullptr)
    , m_mainThread(QThread::currentThread())
    , m_translator(nullptr)
{
    setApplicationVersion(APP_VERSION);
    setApplicationName(APP_NAME);
    setOrganizationName(APP_ORGANIZATION);

    m_settings.setIniCodec(QTextCodec::codecForName("UTF-8"));

    registDefaultKeyMap();
    loadSettings();
}

QString QVApplication::getApplicationFilePath(QString subFilePath)
{
    return QDir::toNativeSeparators(QString("%1/%2").arg(applicationDirPath()).arg(subFilePath));
}

void QVApplication::installTranslator()
{
    // multi-language-support
    if(m_translator) {
        removeTranslator(m_translator);
        delete m_translator;
    }
    m_translator = new QTranslator;
    bool exist = m_translator->load(QLocale(qApp->UiLanguage()),
                                 "translations/", "quickviewer_", qApp->applicationDirPath());
    if(exist) {
        QApplication::installTranslator(m_translator);
    } else {
        delete m_translator;
        m_translator = nullptr;
    }
}

void QVApplication::registDefaultKeyMap()
{
    // Default key configs
    m_keyConfigDefauls["actionExitApplicationOrFullscreen"] = QKeySequence("Esc");
    m_keyConfigDefauls["actionNextPage"] = QKeySequence("L, Right, Space");
    m_keyConfigDefauls["actionPrevPage"] = QKeySequence("H, Left, Backspace");
    m_keyConfigDefauls["actionFastForward"] = QKeySequence("Shift+L, Num+3");
    m_keyConfigDefauls["actionFastBackward"] = QKeySequence("Shift+H, Num+1");
    m_keyConfigDefauls["actionLastPage"] = QKeySequence("Ctrl+L, End");
    m_keyConfigDefauls["actionFirstPage"] = QKeySequence("Ctrl+H, Home");
    m_keyConfigDefauls["actionNextVolume"] = QKeySequence("Ctrl+J, PgDown");
    m_keyConfigDefauls["actionPrevVolume"] = QKeySequence("Ctrl+K, PgUp");

    m_keyConfigDefauls["actionZoomIn"] = QKeySequence("K, Num++");
    m_keyConfigDefauls["actionZoomOut"] = QKeySequence("J, Num+-");

    m_keyConfigDefauls["actionRenameImageFile"] = QKeySequence("F2");
    m_keyConfigDefauls["actionShowFolder"] = QKeySequence("F4");
    m_keyConfigDefauls["actionShowCatalog"] = QKeySequence("Ctrl+/, F6");
    m_keyConfigDefauls["actionSlideShow"] = QKeySequence("F7");
    m_keyConfigDefauls["actionStayOnTop"] = QKeySequence("F8");
    m_keyConfigDefauls["actionShowMenuBar"] = QKeySequence("F9");
    m_keyConfigDefauls["actionDualView"] = QKeySequence("Y, F10");
    m_keyConfigDefauls["actionFullscreen"] = QKeySequence("F11");
    m_keyConfigDefauls["actionFitting"] = QKeySequence("M, F12, Num+*");

    m_keyConfigDefauls["actionRotate"] = QKeySequence("R");
    m_keyConfigDefauls["actionDeletePage"] = QKeySequence("Del");

    m_keyConfigDefauls["actionCopyPage"] = QKeySequence("Ctrl+C");
    m_keyConfigDefauls["actionCopyFile"] = QKeySequence("Ctrl+Shift+C");

    m_keyConfigDefauls["actionLoadBookmark"] = QKeySequence("Q");
    m_keyConfigDefauls["actionSaveBookmark"] = QKeySequence("W");

    m_keyConfigDefauls["actionMaximizeOrNormal"] = QKeySequence("Return, Num+Enter");

    m_keyConfigs = m_keyConfigDefauls;
    m_keyConfigs.detach();
}

void QVApplication::registActions(Ui::MainWindow *ui)
{
    // File
    registAction("actionOpenFolder", ui->actionOpenFolder);
    registAction("actionClearHistory", ui->actionClearHistory);
    registAction("actionAutoLoaded", ui->actionAutoLoaded);
    registAction("actionExit", ui->actionExit);

    // Bookmark
    registAction("actionClearBookmarks", ui->actionClearBookmarks);
    registAction("actionLoadBookmark", ui->actionLoadBookmark);
    registAction("actionSaveBookmark", ui->actionSaveBookmark);

    // Navigation
    registAction("actionNextPage", ui->actionNextPage);
    registAction("actionPrevPage", ui->actionPrevPage);
    registAction("actionFastForward", ui->actionFastForward);
    registAction("actionFastBackward", ui->actionFastBackward);
    registAction("actionLastPage", ui->actionLastPage);
    registAction("actionFirstPage", ui->actionFirstPage);
    registAction("actionNextVolume", ui->actionNextVolume);
    registAction("actionPrevVolume", ui->actionPrevVolume);
    registAction("actionNextOnePage", ui->actionNextOnePage);
    registAction("actionPrevOnePage", ui->actionPrevOnePage);
    registAction("actionSlideShow", ui->actionSlideShow);

    // Folder
    registAction("actionShowFolder", ui->actionShowFolder);

    // Catalog
    registAction("actionShowCatalog", ui->actionShowCatalog);
    registAction("actionSearchTitleWithOptions", ui->actionSearchTitleWithOptions);
    registAction("actionCatalogTitleWithoutOptions", ui->actionCatalogTitleWithoutOptions);
    registAction("actionCatalogIconLongText", ui->actionCatalogIconLongText);

    // View
    registAction("actionRotate", ui->actionRotate);
    registAction("actionFitting", ui->actionFitting);
    registAction("actionZoomIn", ui->actionZoomIn);
    registAction("actionZoomOut", ui->actionZoomOut);
    registAction("actionDontEnlargeSmallImagesOnFitting", ui->actionDontEnlargeSmallImagesOnFitting);

    registAction("actionDualView", ui->actionDualView);
    registAction("actionRightSideBook", ui->actionRightSideBook);
    registAction("actionWideImageAsOneView", ui->actionWideImageAsOneView);
    registAction("actionFirstImageAsOneView", ui->actionFirstImageAsOneView);

    registAction("actionRestoreWindowState", ui->actionRestoreWindowState);
    registAction("actionFullscreen", ui->actionFullscreen);
    registAction("actionStayOnTop", ui->actionStayOnTop);

    registAction("actionExitApplicationOrFullscreen", ui->actionExitApplicationOrFullscreen);
    registAction("actionMaximizeOrNormal", ui->actionMaximizeOrNormal);

    // Toolbar
    registAction("actionShowToolBar", ui->actionShowToolBar);
    registAction("actionShowStatusBar", ui->actionShowStatusBar);
    registAction("actionShowPageBar", ui->actionShowPageBar);
    registAction("actionShowMenuBar", ui->actionShowMenuBar);

    // ContextMenu
    registAction("actionOpenFiler", ui->actionOpenFiler);
    registAction("actionOpenExif", ui->actionOpenExif);
    registAction("actionCopyPage", ui->actionCopyPage);
    registAction("actionCopyFile", ui->actionCopyFile);
    registAction("actionDeletePage", ui->actionDeletePage);
    registAction("actionMailAttachment", ui->actionMailAttachment);
    registAction("actionRenameImageFile", ui->actionRenameImageFile);

    // Shader
    registAction("actionShaderNearestNeighbor", ui->actionShaderNearestNeighbor);
    registAction("actionShaderBilinear", ui->actionShaderBilinear);
    registAction("actionShaderBicubic", ui->actionShaderBicubic);
    registAction("actionShaderLanczos", ui->actionShaderLanczos);
    registAction("actionShaderBilinearBeforeCpuBicubic", ui->actionShaderBilinearBeforeCpuBicubic);
    registAction("actionShaderCpuBicubic", ui->actionShaderCpuBicubic);

    // Help
    registAction("actionOpenKeyConfig", ui->actionOpenKeyConfig);
    registAction("actionOpenOptionsDialog", ui->actionOpenOptionsDialog);
    registAction("actionCheckVersion", ui->actionCheckVersion);
    registAction("actionProjectWeb", ui->actionProjectWeb);
    registAction("actionAppVersion", ui->actionAppVersion);
}

void QVApplication::onGLInitialized()
{
    const QGLContext* c0 = QGLContext::currentContext();
    if(c0) {
        QOpenGLContext* c1 = QOpenGLContext::currentContext();
        //QOpenGLContext* c2 = c0->contextHandle();
        if(c1 && c1->isValid()) {
            c1->functions()->glGetIntegerv(GL_MAX_TEXTURE_SIZE, &m_maxTextureSize);
            qDebug() << m_maxTextureSize;
        }
    }
}

void QVApplication::addHistory(QString path)
{
    const QString unixpath = QDir::fromNativeSeparators(path);
    if(m_history.contains(unixpath)) {
        m_history.removeOne(unixpath);
    }
    m_history.push_front(unixpath);
    while(m_history.size() > m_maxHistoryCount)
        m_history.pop_back();
}

void QVApplication::addBookMark(QString path, bool canDumplication)
{
    const QString unixpath = QDir::fromNativeSeparators(path);
    if(canDumplication) {
        m_bookmarks.push_front(unixpath);
        return;
    }
    if(m_bookmarks.contains(unixpath)) {
        m_bookmarks.removeOne(unixpath);
    }
    m_bookmarks.push_front(unixpath);
    while(m_bookmarks.size() > m_maxBookmarkCount)
        m_bookmarks.pop_back();
}


QString QVApplication::getDefaultPictureFolderPath()
{
    QString path = "./";
#ifdef Q_OS_WIN
    int nFolder = CSIDL_MYPICTURES;
    HRESULT result;
    LPITEMIDLIST pidl;
    std::string str;
    IMalloc *pMalloc;
    WCHAR szPath[MAX_PATH+1];

    SHGetMalloc(&pMalloc);
    result = ::SHGetSpecialFolderLocation(NULL, nFolder, &pidl);

    if (SUCCEEDED(result))
    {
        ::SHGetPathFromIDList(pidl, szPath);
        path = QString::fromWCharArray(szPath);
        pMalloc->Free(pidl);
    }
    pMalloc->Release();
#else
    path = "~/";
#endif
    return path;
}

void QVApplication::loadSettings()
{
    bool bRightSideBookDefault = QLocale::system().language() == QLocale::Japanese;
    m_settings.beginGroup("View");
    m_fitting = m_settings.value("Fitting", true).toBool();
    m_dualView = m_settings.value("DualView", false).toBool();
    m_stayOnTop = m_settings.value("StayOnTop", false).toBool();

    m_rightSideBook = m_settings.value("RightSideBook", bRightSideBookDefault).toBool();
    m_wideImageAsOnePageInDualView = m_settings.value("WideImageAsOnePageInDualView", true).toBool();
    m_firstImageAsOnePageInDualView = m_settings.value("FirstImageAsOnePageInDualView", false).toBool();

    m_showToolBar = m_settings.value("ShowToolBar", true).toBool();
    m_showSliderBar = m_settings.value("ShowSliderBar", true).toBool();
    m_showStatusBar = m_settings.value("ShowStatusBar", true).toBool();
    m_showMenuBar = m_settings.value("ShowMenuBar", true).toBool();
    m_showSubfolders = m_settings.value("ShowSubfolders", false).toBool();
    m_slideShowWait = m_settings.value("SlideShowWait", 5000).toInt();
#ifdef Q_OS_WIN64
    m_maxVolumesCache = m_settings.value("MaxVolumesCache", 3).toInt();
#else
    m_maxVolumesCache = m_settings.value("MaxVolumesCache", 1).toInt();
#endif
    m_backgroundColor = QColor(m_settings.value("BackgroundColor", "0x797979").toString().toUInt(nullptr, 16));
    m_backgroundColor2 = QColor(m_settings.value("BackgroundColor2", "0x5e5e5e").toString().toUInt(nullptr, 16));
    m_useCheckeredPattern  = m_settings.value("UseCheckeredPattern", true).toBool();
    m_dontEnlargeSmallImagesOnFitting  = m_settings.value("DontEnlargeSmallImagesOnFitting", true).toBool();
    m_showFullscreenSignage  = m_settings.value("ShowFullscreenSignage", true).toBool();
    m_settings.endGroup();

    m_settings.beginGroup("WindowState");
    m_restoreWindowState  = m_settings.value("RestoreWindowState", false).toBool();
    m_windowGeometry  = m_settings.value("WindowGeometry", "").toByteArray();
    m_windowState  = m_settings.value("WindowState", "").toByteArray();
    m_beginAsFullscreen  = m_settings.value("BeginAsFullscreen", false).toBool();
    m_settings.endGroup();

    m_settings.beginGroup("File");
    m_autoLoaded  = m_settings.value("AutoLoaded", true).toBool();
    m_history = m_settings.value("History", QStringList()).value<QStringList>();
    m_maxHistoryCount = m_settings.value("MaxHistoryCount", 36).toInt();
    m_bookmarks = m_settings.value("Bookmarks", QStringList()).value<QStringList>();
    m_maxBookmarkCount = m_settings.value("MaxBookmarkCount", 20).toInt();
    m_settings.endGroup();

    m_settings.beginGroup("Folder");
    QString defaultPath = getDefaultPictureFolderPath();
    m_homeFolderPath = m_settings.value("HomeFolderPath", defaultPath).toString();
    {
        QString folderSortModestring = m_settings.value("FolderSortMode", "OrderByName").toString();
        int enumIdx = qvEnums::staticMetaObject.indexOfEnumerator("FolderViewSort");
        m_folderSortMode = (qvEnums::FolderViewSort)qvEnums::staticMetaObject.enumerator(enumIdx).keysToValue(folderSortModestring.toLatin1().data());
    }
    m_openVolumeWithProgress = m_settings.value("OpenVolumeWithProgress", true).toBool();
    m_showReadProgress = m_settings.value("ShowReadProgress", true).toBool();
    m_settings.endGroup();

    m_settings.beginGroup("Catalog");
    {
        QString viewModestring = m_settings.value("CatalogViewModeSetting", "Icon").toString();
        int enumIdx = qvEnums::staticMetaObject.indexOfEnumerator("CatalogViewMode");
        m_catalogViewModeSetting = (qvEnums::CatalogViewMode)qvEnums::staticMetaObject.enumerator(enumIdx).keysToValue(viewModestring.toLatin1().data());
    }
    m_catalogDatabasePath = m_settings.value("CatalogDatabasePath", "database/thumbnail.sqlite3.db").toString();
    m_maxSearchByCharChanged = m_settings.value("MaxSearchByCharChanged", 10000).toInt();
    m_maxShowFrontpage = m_settings.value("MaxShowFrontpage", 1000).toInt();
    m_titleWithoutOptions = m_settings.value("TitleWithoutOptions", false).toBool();
    m_searchTitleWithOptions = m_settings.value("SearchTitleWithOptions", false).toBool();
    m_showTagBar = m_settings.value("ShowTagBar", true).toBool();
    m_iconLongText = m_settings.value("IconLongText", false).toBool();
    m_settings.endGroup();

    m_settings.beginGroup("KeyConfig");
    foreach(const QString& action, m_settings.childKeys()) {
        QString str = m_settings.value(action, "").toString();
        m_keyConfigs[action] = QKeySequence(str);
    }
    m_settings.endGroup();

    m_settings.beginGroup("Shader");
    QString effectstring = m_settings.value("Effect", "Bilinear").toString();
    m_effect = ShaderManager::stringToShaderEffect(effectstring);
    m_bicubicShaderPath = m_settings.value("BicubicShaderPath", "shaders/bicubic.frag").toString();
    m_lanczosShaderPath = m_settings.value("LanczosShaderPath", "shaders/lanczos.frag").toString();
    m_settings.endGroup();

    m_settings.beginGroup("Others");
    m_uiLanguage = m_settings.value("UiLanguage", QLocale::system().name()).toString();
    m_settings.endGroup();

    m_bookshelfManager = new BookProgressManager(this);
}

void QVApplication::saveSettings()
{
    m_settings.beginGroup("View");
    m_settings.setValue("Fitting", m_fitting);
    m_settings.setValue("DualView", m_dualView);
    m_settings.setValue("StayOnTop", m_stayOnTop);

    m_settings.setValue("RightSideBook", m_rightSideBook);
    m_settings.setValue("WideImageAsOnePageInDualView", m_wideImageAsOnePageInDualView);
    m_settings.setValue("FirstImageAsOnePageInDualView", m_firstImageAsOnePageInDualView);

    m_settings.setValue("ShowToolBar", m_showToolBar);
    m_settings.setValue("ShowSliderBar", m_showSliderBar);
    m_settings.setValue("ShowStatusBar", m_showStatusBar);
    m_settings.setValue("ShowMenuBar", m_showMenuBar);
    m_settings.setValue("ShowSubfolders", m_showSubfolders);
    m_settings.setValue("SlideShowWait", m_slideShowWait);
    m_settings.setValue("MaxVolumesCache", m_maxVolumesCache);
    QString rgbstring;
    rgbstring.setNum(m_backgroundColor.rgb(), 16);
    m_settings.setValue("BackgroundColor", rgbstring);
    rgbstring.setNum(m_backgroundColor2.rgb(), 16);
    m_settings.setValue("BackgroundColor2", rgbstring);
    m_settings.setValue("UseCheckeredPattern", m_useCheckeredPattern);
    m_settings.setValue("DontEnlargeSmallImagesOnFitting", m_dontEnlargeSmallImagesOnFitting);
    m_settings.setValue("ShowFullscreenSignage", m_showFullscreenSignage);
    m_settings.endGroup();

    m_settings.beginGroup("WindowState");
    m_settings.setValue("RestoreWindowState", m_restoreWindowState);
    m_settings.setValue("WindowGeometry", m_windowGeometry);
    m_settings.setValue("WindowState", m_windowState);
    m_settings.setValue("BeginAsFullscreen", m_beginAsFullscreen);
    m_settings.endGroup();

    m_settings.beginGroup("File");
    m_settings.setValue("AutoLoaded", m_autoLoaded);
    m_settings.setValue("MaxHistoryCount", m_maxHistoryCount);
    m_settings.setValue("History", QVariant::fromValue(m_history));
    m_settings.setValue("MaxBookmarkCount", m_maxBookmarkCount);
    m_settings.setValue("Bookmarks", QVariant::fromValue(m_bookmarks));
    m_settings.endGroup();

    m_settings.beginGroup("Folder");
    m_settings.setValue("HomeFolderPath", m_homeFolderPath);
    {
        int enumIdx = qvEnums::staticMetaObject.indexOfEnumerator("FolderViewSort");
        QString folderSortModestring = QString(qvEnums::staticMetaObject.enumerator(enumIdx).valueToKey(m_folderSortMode));
        m_settings.setValue("FolderSortMode", folderSortModestring);
    }
    m_settings.setValue("OpenVolumeWithProgress", m_openVolumeWithProgress);
    m_settings.setValue("ShowReadProgress", m_showReadProgress);
    m_settings.endGroup();

    m_settings.beginGroup("Catalog");
    {
        int enumIdx = qvEnums::staticMetaObject.indexOfEnumerator("CatalogViewMode");
        QString viewModestring = QString(qvEnums::staticMetaObject.enumerator(enumIdx).valueToKey(m_catalogViewModeSetting));
        m_settings.setValue("CatalogViewModeSetting", viewModestring);
    }
    m_settings.setValue("MaxSearchByCharChanged", m_maxSearchByCharChanged);
    m_settings.setValue("MaxShowFrontpage", m_maxShowFrontpage);
    m_settings.setValue("TitleWithoutOptions", m_titleWithoutOptions);
    m_settings.setValue("SearchTitleWithOptions", m_searchTitleWithOptions);
    m_settings.setValue("ShowTagBar", m_showTagBar);
    m_settings.setValue("IconLongText", m_iconLongText);
    m_settings.endGroup();

    m_settings.beginGroup("KeyConfig");
    foreach(const QString& action, m_keyConfigs.keys()) {
        QKeySequence seqs = m_keyConfigs[action];
        m_settings.setValue(action, seqs.toString());
    }
    m_settings.endGroup();

    m_settings.beginGroup("Shader");
    m_settings.setValue("Effect", ShaderManager::shaderEffectToString(m_effect));
    m_settings.setValue("BicubicShaderPath", m_bicubicShaderPath);
    m_settings.setValue("LanczosShaderPath", m_lanczosShaderPath);
    m_settings.endGroup();

    m_settings.beginGroup("Others");
    m_settings.setValue("UiLanguage", m_uiLanguage);
    m_settings.endGroup();


    m_settings.sync();

    m_bookshelfManager->save();
}
