#include <QtGui>
//#include <QtOpenGL>

#ifdef Q_OS_WIN
#include <shlobj.h>
#endif

#include "qvapplication.h"
#include "qv_init.h"
#include "ui_mainwindow.h"

QVApplication::QVApplication(int &argc, char **argv)
    : QApplication(argc, argv)
    , m_mainThread(QThread::currentThread())
    , m_maxTextureSize(4096)
    , m_effect(qvEnums::Bilinear)
    , m_translator(nullptr)
#ifdef Q_OS_WIN
    , m_settings(getApplicationFilePath(APP_INI), QSettings::IniFormat, this)
#else
    , m_settings(getUserHomeFilePath(APP_INI), QSettings::IniFormat, this)
#endif
    , m_bookshelfManager(nullptr)
//    , m_languageSelector("quickviewer_", "translations/")
    // ATTENTION:
    // default 'QLibraryInfo::location(TranslationsPath)' is "[QTDIR]/translations"
    , m_languageSelector("quickviewer_", QLibraryInfo::location(QLibraryInfo::TranslationsPath))
    , m_qtbaseLanguageSelector("qt_", QLibraryInfo::location(QLibraryInfo::TranslationsPath))
{
    setApplicationVersion(APP_VERSION);
    setApplicationName(APP_NAME);
    setOrganizationName(APP_ORGANIZATION);

    m_settings.setIniCodec(QTextCodec::codecForName("UTF-8"));
    connect(&m_languageSelector, SIGNAL(languageChanged(QString)), &m_qtbaseLanguageSelector, SLOT(resetTranslator(QString)));
    registDefaultKeyMap();
    registDefaultMouseMap();
    loadSettings();
}

QString QVApplication::getApplicationFilePath(QString subFilePath)
{
    return QDir::toNativeSeparators(QString("%1/%2").arg(applicationDirPath()).arg(subFilePath));
}

QString QVApplication::getUserHomeFilePath(QString subFilePath)
{
    return QDir::toNativeSeparators(QString("%1/%2").arg(QString(qgetenv("HOME"))).arg(subFilePath));
}

QString QVApplication::CatalogDatabasePath()
{
#ifdef Q_OS_WIN
    return getApplicationFilePath(m_catalogDatabasePath);
#else
    return m_catalogDatabasePath;
#endif
}

void QVApplication::myInstallTranslator()
{
    m_languageSelector.resetTranslator(UiLanguage());
    // It is "" when it is started for the first time,
    // but it is better to set the value in order to cause unnecessary processing
    if(m_uiLanguage.isEmpty())
        setUiLanguage(m_languageSelector.language());
}

void QVApplication::registDefaultKeyMap()
{
    // Default key configs
    m_keyActions.addDefaultKey("actionExitApplicationOrFullscreen", QKeySequence("Esc"));
    m_keyActions.addDefaultKey("actionNextPage", QKeySequence("L, Right, Space"));
    m_keyActions.addDefaultKey("actionPrevPage", QKeySequence("H, Left, Backspace"));
    m_keyActions.addDefaultKey("actionFastForward", QKeySequence("Shift+L, Num+3"));
    m_keyActions.addDefaultKey("actionFastBackward", QKeySequence("Shift+H, Num+1"));
    m_keyActions.addDefaultKey("actionLastPage", QKeySequence("Ctrl+L, End"));
    m_keyActions.addDefaultKey("actionFirstPage", QKeySequence("Ctrl+H, Home"));
    m_keyActions.addDefaultKey("actionNextVolume", QKeySequence("Ctrl+J, PgDown"));
    m_keyActions.addDefaultKey("actionPrevVolume", QKeySequence("Ctrl+K, PgUp"));
    m_keyActions.addDefaultKey("actionZoomIn", QKeySequence("K, Num++"));
    m_keyActions.addDefaultKey("actionZoomOut", QKeySequence("J, Num+-"));
    m_keyActions.addDefaultKey("actionRenameImageFile", QKeySequence("F2"));
    m_keyActions.addDefaultKey("actionShowFolder", QKeySequence("F4"));
    m_keyActions.addDefaultKey("actionShowCatalog", QKeySequence("Ctrl+/, F6"));
    m_keyActions.addDefaultKey("actionSlideShow", QKeySequence("F7"));
    m_keyActions.addDefaultKey("actionStayOnTop", QKeySequence("F8"));
    m_keyActions.addDefaultKey("actionShowMenuBar", QKeySequence("F9"));
    m_keyActions.addDefaultKey("actionDualView", QKeySequence("Y, F10"));
    m_keyActions.addDefaultKey("actionFullscreen", QKeySequence("F11"));
    m_keyActions.addDefaultKey("actionFitting", QKeySequence("M, F12, Num+*"));
    m_keyActions.addDefaultKey("actionRotate", QKeySequence("R"));
    m_keyActions.addDefaultKey("actionRecyclePage", QKeySequence("Del"));
    m_keyActions.addDefaultKey("actionDeletePage", QKeySequence("Shift+Del"));
    m_keyActions.addDefaultKey("actionCopyPage", QKeySequence("Ctrl+C"));
    m_keyActions.addDefaultKey("actionCopyFile", QKeySequence("Ctrl+Shift+C"));
    m_keyActions.addDefaultKey("actionLoadBookmark", QKeySequence("Q"));
    m_keyActions.addDefaultKey("actionSaveBookmark", QKeySequence("W"));
    m_keyActions.addDefaultKey("actionMaximizeOrNormal", QKeySequence("Return, Num+Enter"));
}

void QVApplication::registDefaultMouseMap()
{
    // Default mouse configs
    m_mouseActions.addDefaultKey("actionNextPage", QMouseSequence("+::WheelDown, +::ForwardButton"));
    m_mouseActions.addDefaultKey("actionPrevPage", QMouseSequence("+::WheelUp, +::BackButton"));
    m_mouseActions.addDefaultKey("actionContextMenu", QMouseSequence("+::RightButton"));
    m_mouseActions.addDefaultKey("actionFitting", QMouseSequence("+::RightButton+MiddleButton, Ctrl+::MiddleButton"));
    m_mouseActions.addDefaultKey("actionZoomIn", QMouseSequence("+::RightButton+WheelUp, Ctrl+::WheelUp"));
    m_mouseActions.addDefaultKey("actionZoomOut", QMouseSequence("+::RightButton+WheelDown, Ctrl+::WheelDown"));
    m_mouseActions.addDefaultKey("actionFullscreen", QMouseSequence("+::MiddleButton"));
}

void QVApplication::registActions(Ui::MainWindow *ui)
{
    // File
    QString groupName = tr("File", "File Action Group");
    m_keyActions.registAction("actionOpenFolder", ui->actionOpenFolder, groupName);
    m_keyActions.registAction("actionClearHistory", ui->actionClearHistory, groupName);
    m_keyActions.registAction("actionAutoLoaded", ui->actionAutoLoaded, groupName);
    m_keyActions.registAction("actionExit", ui->actionExit, groupName);


    // Bookmark
    groupName = tr("Bookmark", "Bookmark Action Group");
    m_keyActions.registAction("actionClearBookmarks", ui->actionClearBookmarks, groupName);
    m_keyActions.registAction("actionLoadBookmark", ui->actionLoadBookmark, groupName);
    m_keyActions.registAction("actionSaveBookmark", ui->actionSaveBookmark, groupName);

    // Navigation
    groupName = tr("Bookmark", "Bookmark Action Group");
    m_keyActions.registAction("actionNextPage", ui->actionNextPage, groupName);
    m_keyActions.registAction("actionPrevPage", ui->actionPrevPage, groupName);
    m_keyActions.registAction("actionFastForward", ui->actionFastForward, groupName);
    m_keyActions.registAction("actionFastBackward", ui->actionFastBackward, groupName);
    m_keyActions.registAction("actionLastPage", ui->actionLastPage, groupName);
    m_keyActions.registAction("actionFirstPage", ui->actionFirstPage, groupName);
    m_keyActions.registAction("actionNextVolume", ui->actionNextVolume, groupName);
    m_keyActions.registAction("actionPrevVolume", ui->actionPrevVolume, groupName);
    m_keyActions.registAction("actionNextOnePage", ui->actionNextOnePage, groupName);
    m_keyActions.registAction("actionPrevOnePage", ui->actionPrevOnePage, groupName);
    m_keyActions.registAction("actionSlideShow", ui->actionSlideShow, groupName);

    // Folder
    groupName = tr("Folder", "Folder Action Group");
    m_keyActions.registAction("actionShowFolder", ui->actionShowFolder, groupName);

    // Catalog
    groupName = tr("Catalog", "Catalog Action Group");
    m_keyActions.registAction("actionShowCatalog", ui->actionShowCatalog, groupName);
    m_keyActions.registAction("actionSearchTitleWithOptions", ui->actionSearchTitleWithOptions, groupName);
    m_keyActions.registAction("actionCatalogTitleWithoutOptions", ui->actionCatalogTitleWithoutOptions, groupName);
    m_keyActions.registAction("actionCatalogIconLongText", ui->actionCatalogIconLongText, groupName);

    // View
    groupName = tr("View", "View Action Group");
    m_keyActions.registAction("actionRotate", ui->actionRotate, groupName);
    m_keyActions.registAction("actionFitting", ui->actionFitting, groupName);
    m_keyActions.registAction("actionZoomIn", ui->actionZoomIn, groupName);
    m_keyActions.registAction("actionZoomOut", ui->actionZoomOut, groupName);
    m_keyActions.registAction("actionDontEnlargeSmallImagesOnFitting", ui->actionDontEnlargeSmallImagesOnFitting, groupName);

    m_keyActions.registAction("actionDualView", ui->actionDualView, groupName);
    m_keyActions.registAction("actionRightSideBook", ui->actionRightSideBook, groupName);
    m_keyActions.registAction("actionWideImageAsOneView", ui->actionWideImageAsOneView, groupName);
    m_keyActions.registAction("actionFirstImageAsOneView", ui->actionFirstImageAsOneView, groupName);

    // WindowState
    groupName = tr("WindowState", "WindowState Action Group");
    m_keyActions.registAction("actionRestoreWindowState", ui->actionRestoreWindowState, groupName);
    m_keyActions.registAction("actionFullscreen", ui->actionFullscreen, groupName);
    m_keyActions.registAction("actionStayOnTop", ui->actionStayOnTop, groupName);
    m_keyActions.registAction("actionExitApplicationOrFullscreen", ui->actionExitApplicationOrFullscreen, groupName);
    m_keyActions.registAction("actionMaximizeOrNormal", ui->actionMaximizeOrNormal, groupName);

    // Toolbar
    groupName = tr("Toolbar", "Toolbar Action Group");
    m_keyActions.registAction("actionShowToolBar", ui->actionShowToolBar, groupName);
    m_keyActions.registAction("actionShowStatusBar", ui->actionShowStatusBar, groupName);
    m_keyActions.registAction("actionShowPageBar", ui->actionShowPageBar, groupName);
    m_keyActions.registAction("actionShowMenuBar", ui->actionShowMenuBar, groupName);

    // ContextMenu
    groupName = tr("ContextMenu", "ContextMenu Action Group");
    m_keyActions.registAction("actionContextMenu", ui->actionContextMenu, groupName);
    m_keyActions.registAction("actionOpenFiler", ui->actionOpenFiler, groupName);
    m_keyActions.registAction("actionOpenExif", ui->actionOpenExif, groupName);
    m_keyActions.registAction("actionCopyPage", ui->actionCopyPage, groupName);
    m_keyActions.registAction("actionCopyFile", ui->actionCopyFile, groupName);
    m_keyActions.registAction("actionRecyclePage", ui->actionRecyclePage, groupName);
    m_keyActions.registAction("actionDeletePage", ui->actionDeletePage, groupName);
    m_keyActions.registAction("actionMailAttachment", ui->actionMailAttachment, groupName);
    m_keyActions.registAction("actionRenameImageFile", ui->actionRenameImageFile, groupName);
    m_keyActions.registAction("actionShowToolBar", ui->actionShowToolBar, groupName);
    m_keyActions.registAction("actionShowToolBar", ui->actionShowToolBar, groupName);
    m_keyActions.registAction("actionShowToolBar", ui->actionShowToolBar, groupName);

    // Shader
    groupName = tr("Shader", "Shader Action Group");
    m_keyActions.registAction("actionShaderNearestNeighbor", ui->actionShaderNearestNeighbor, groupName);
    m_keyActions.registAction("actionShaderBilinear", ui->actionShaderBilinear, groupName);
    m_keyActions.registAction("actionShaderBicubic", ui->actionShaderBicubic, groupName);
    m_keyActions.registAction("actionShaderLanczos", ui->actionShaderLanczos, groupName);
    m_keyActions.registAction("actionShaderBilinearBeforeCpuBicubic", ui->actionShaderBilinearBeforeCpuBicubic, groupName);
    m_keyActions.registAction("actionShaderCpuBicubic", ui->actionShaderCpuBicubic, groupName);

    // Help
    groupName = tr("Help", "Help Action Group");
    m_keyActions.registAction("actionOpenKeyConfig", ui->actionOpenKeyConfig, groupName);
    m_keyActions.registAction("actionOpenOptionsDialog", ui->actionOpenOptionsDialog, groupName);
    m_keyActions.registAction("actionCheckVersion", ui->actionCheckVersion, groupName);
    m_keyActions.registAction("actionCheckVersion", ui->actionCheckVersion, groupName);
    m_keyActions.registAction("actionProjectWeb", ui->actionProjectWeb, groupName);
    m_keyActions.registAction("actionAppVersion", ui->actionAppVersion, groupName);

    m_mouseActions.actions() = m_keyActions.actions();
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
    m_maxTextureSize = m_settings.value("MaxTextureSize", 4096).toInt();
#ifdef Q_PROCESSOR_X86_64
    m_maxVolumesCache = m_settings.value("MaxVolumesCache", 5).toInt();
    m_maxImagesCache = m_settings.value("MaxImagesCache", 22).toInt();
#else
    m_maxVolumesCache = m_settings.value("MaxVolumesCache", 1).toInt();
    m_maxImagesCache = m_settings.value("MaxImagesCache", 6).toInt();
#endif
    m_backgroundColor = QColor(m_settings.value("BackgroundColor", "0x797979").toString().toUInt(nullptr, 16));
    m_backgroundColor2 = QColor(m_settings.value("BackgroundColor2", "0x5e5e5e").toString().toUInt(nullptr, 16));
    m_useCheckeredPattern  = m_settings.value("UseCheckeredPattern", true).toBool();
    m_dontEnlargeSmallImagesOnFitting  = m_settings.value("DontEnlargeSmallImagesOnFitting", true).toBool();
    m_showFullscreenSignage  = m_settings.value("ShowFullscreenSignage", true).toBool();
//    m_showFullscreenTitleBar = m_settings.value("ShowFullscreenTitleBar", true).toBool();
    m_useDirect2D = m_settings.value("UseDirect2D", false).toBool();
    m_useFastDCTForJPEG = m_settings.value("UseFastDCTForJPEG", true).toBool();
    m_showFullpathOfVolume  = m_settings.value("ShowFullpathOfVolume", true).toBool();
    m_showPanelSeparateWindow  = m_settings.value("ShowPanelSeparateWindow", false).toBool();
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
    m_prohibitMultipleRunning  = m_settings.value("ProhibitMultipleRunning", false).toBool();
    m_lastViewPath = m_settings.value("LastViewPath", "").toString();
    m_dontSavingHistory  = m_settings.value("DontSavingHistory", false).toBool();
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
#ifdef Q_OS_WIN
    m_catalogDatabasePath = m_settings.value("CatalogDatabasePath", "database/thumbnail.sqlite3.db").toString();
#else
    m_catalogDatabasePath = m_settings.value("CatalogDatabasePath", getUserHomeFilePath(".quickviewer/thumbnail.sqlite3.db")).toString();
#endif
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
        m_keyActions.updateKey(action,  QKeySequence(str), true);
    }
    m_settings.endGroup();

    m_settings.beginGroup("MouseConfig");
    foreach(const QString& action, m_settings.childKeys()) {
        QString str = m_settings.value(action, "").toString();
        m_mouseActions.updateKey(action, QMouseSequence(str), true);
    }
    m_settings.endGroup();

    m_settings.beginGroup("Shader");
    QString effectstring = m_settings.value("Effect", "Bilinear").toString();
    m_effect = ShaderManager::stringToShaderEffect(effectstring);
    m_bicubicShaderPath = m_settings.value("BicubicShaderPath", "shaders/bicubic.frag").toString();
    m_lanczosShaderPath = m_settings.value("LanczosShaderPath", "shaders/lanczos.frag").toString();
    m_settings.endGroup();

    m_settings.beginGroup("Others");
    m_uiLanguage = m_settings.value("UiLanguage", "").toString();
    m_confirmDeletePage = m_settings.value("ConfirmDeletePage", true).toBool();
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
    m_settings.setValue("MaxTextureSize", m_maxTextureSize);
    m_settings.setValue("MaxVolumesCache", m_maxVolumesCache);
    m_settings.setValue("MaxImagesCache", m_maxImagesCache);
    QString rgbstring;
    rgbstring.setNum(m_backgroundColor.rgb(), 16);
    m_settings.setValue("BackgroundColor", rgbstring);
    rgbstring.setNum(m_backgroundColor2.rgb(), 16);
    m_settings.setValue("BackgroundColor2", rgbstring);
    m_settings.setValue("UseCheckeredPattern", m_useCheckeredPattern);
    m_settings.setValue("DontEnlargeSmallImagesOnFitting", m_dontEnlargeSmallImagesOnFitting);
    m_settings.setValue("ShowFullscreenSignage", m_showFullscreenSignage);
//    m_settings.setValue("ShowFullscreenTitleBar", m_showFullscreenTitleBar);
    m_settings.setValue("UseDirect2D", m_useDirect2D);
    m_settings.setValue("UseFastDCTForJPEG", m_useFastDCTForJPEG);
    m_settings.setValue("ShowFullpathOfVolume", m_showFullpathOfVolume);
    m_settings.setValue("ShowPanelSeparateWindow", m_showPanelSeparateWindow);
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
    m_settings.setValue("ProhibitMultipleRunning", m_prohibitMultipleRunning);
    m_settings.setValue("LastViewPath", m_lastViewPath);
    m_settings.setValue("DontSavingHistory", m_dontSavingHistory);
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
    foreach(const QString& action, m_keyActions.keyMaps().keys()) {
        QKeySequence seqs = m_keyActions.keyMaps()[action];
        m_settings.setValue(action, seqs.toString());
    }
    m_settings.endGroup();

    m_settings.beginGroup("MouseConfig");
    foreach(const QString& action, m_mouseActions.keyMaps().keys()) {
        QMouseSequence seqs = m_mouseActions.keyMaps()[action];
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
    m_settings.setValue("ConfirmDeletePage", m_confirmDeletePage);
    m_settings.endGroup();


    m_settings.sync();

    m_bookshelfManager->save();
}
