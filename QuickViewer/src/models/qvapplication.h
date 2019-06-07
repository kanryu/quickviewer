#ifndef QVAPPLICATION_H
#define QVAPPLICATION_H

#include <QtGui>
#include <QtCore>
#include <QtWidgets>

#include "qv_init.h"
#include "bookprogressmanager.h"
#include "qlanguageselector.h"
#include "qmousesequence.h"
#include "qactionmanager.h"

#if defined(qApp)
#undef qApp
#endif
#define qApp (static_cast<QVApplication *>(QCoreApplication::instance()))



namespace Ui {
class MainWindow;
}

class QAction;
//typedef QList<QKeySequence> QKeySequenceList;


class QVApplication : public QApplication
{
    Q_OBJECT

    // File
    Q_PROPERTY(bool AutoLoaded READ AutoLoaded WRITE setAutoLoaded)
    Q_PROPERTY(int MaxHistoryCount READ MaxHistoryCount WRITE setMaxHistoryCount)
    Q_PROPERTY(bool ProhibitMultipleRunning READ ProhibitMultipleRunning WRITE setProhibitMultipleRunning)
    // Bookmark
//    Q_PROPERTY(int MaxBookmarkCount READ MaxBookmarkCount WRITE setMaxBookmarkCount)

    // View
    Q_PROPERTY(int SlideShowWait READ SlideShowWait WRITE setSlideShowWait)
    Q_PROPERTY(int MaxVolumesCache READ MaxVolumesCache WRITE setMaxVolumesCache)
    Q_PROPERTY(int MaxImagesCache READ MaxImagesCache WRITE setMaxImagesCache)
    Q_PROPERTY(bool Fitting READ Fitting WRITE setFitting)
    Q_PROPERTY(QColor BackgroundColor READ BackgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor BackgroundColor2 READ BackgroundColor2 WRITE setBackgroundColor2)
    Q_PROPERTY(bool UseCheckeredPattern READ UseCheckeredPattern WRITE setUseCheckeredPattern)
    Q_PROPERTY(bool DontEnlargeSmallImagesOnFitting READ DontEnlargeSmallImagesOnFitting WRITE setDontEnlargeSmallImagesOnFitting)
    Q_PROPERTY(bool ShowFullscreenSignage READ ShowFullscreenSignage WRITE setShowFullscreenSignage)
//    Q_PROPERTY(bool ShowFullscreenTitleBar READ ShowFullscreenTitleBar WRITE setShowFullscreenTitleBar)

    // DualView
    Q_PROPERTY(bool DualView READ DualView WRITE setDualView)
    Q_PROPERTY(bool StayOnTop READ StayOnTop WRITE setStayOnTop)
    Q_PROPERTY(bool RightSideBook READ RightSideBook WRITE setRightSideBook)
    Q_PROPERTY(bool WideImageAsOnePageInDualView READ WideImageAsOnePageInDualView WRITE setWideImageAsOnePageInDualView)
    Q_PROPERTY(bool FirstImageAsOnePageInDualView READ FirstImageAsOnePageInDualView WRITE setFirstImageAsOnePageInDualView)
    Q_PROPERTY(bool ShowSubfolders READ ShowSubfolders WRITE setShowSubfolders)

    // ToolBars
    Q_PROPERTY(bool ShowToolBar READ ShowToolBar WRITE setShowToolBar)
    Q_PROPERTY(bool ShowSliderBar READ ShowSliderBar WRITE setShowSliderBar)
    Q_PROPERTY(bool ShowStatusBar READ ShowStatusBar WRITE setShowStatusBar)
    Q_PROPERTY(bool ShowMenuBar READ ShowMenuBar WRITE setShowMenuBar)

    // WindowStates
    Q_PROPERTY(bool RestoreWindowState READ RestoreWindowState WRITE setRestoreWindowState)
    Q_PROPERTY(QByteArray WindowGeometry READ WindowGeometry WRITE setWindowGeometry)
    Q_PROPERTY(QByteArray WindowState READ WindowState WRITE setWindowState)
    Q_PROPERTY(bool BeginAsFullscreen READ BeginAsFullscreen WRITE setBeginAsFullscreen)

    // Folder
    Q_PROPERTY(QString HomeFolderPath READ HomeFolderPath WRITE setHomeFolderPath)
    Q_PROPERTY(qvEnums::FolderViewSort FolderSortMode READ FolderSortMode WRITE setFolderSortMode)
    Q_PROPERTY(bool OpenVolumeWithProgress READ OpenVolumeWithProgress WRITE setOpenVolumeWithProgress)
    Q_PROPERTY(bool ShowReadProgress READ ShowReadProgress WRITE setShowReadProgress)

    // Catalog
    Q_PROPERTY(qvEnums::CatalogViewMode CatalogViewModeSetting READ CatalogViewModeSetting WRITE setCatalogViewModeSetting)
    Q_PROPERTY(QString CatalogDatabasePath READ CatalogDatabasePath WRITE setCatalogDatabasePath)
    Q_PROPERTY(int MaxSearchByCharChanged READ MaxSearchByCharChanged WRITE setMaxSearchByCharChanged)
    Q_PROPERTY(int MaxShowFrontpage READ MaxShowFrontpage WRITE setMaxShowFrontpage)
    Q_PROPERTY(bool TitleWithoutOptions READ TitleWithoutOptions WRITE setTitleWithoutOptions)
    Q_PROPERTY(bool SearchTitleWithOptions READ SearchTitleWithOptions WRITE setSearchTitleWithOptions)
    Q_PROPERTY(bool ShowTagBar READ ShowTagBar WRITE setShowTagBar)
    Q_PROPERTY(bool IconLongText READ IconLongText WRITE setIconLongText)

    // Key Config

    // Shaders
    Q_PROPERTY(qvEnums::ShaderEffect Effect READ Effect WRITE setEffect)
    Q_PROPERTY(QString BicubicShaderPath READ BicubicShaderPath WRITE setBicubicShaderPath)
    Q_PROPERTY(QString LanczosShaderPath READ LanczosShaderPath WRITE setLanczosShaderPath)

    // Other
    Q_PROPERTY(QString UiLanguage READ UiLanguage WRITE setUiLanguage)
    Q_PROPERTY(bool ConfirmDeletePage READ ConfirmDeletePage WRITE setConfirmDeletePage)

    // Theme
    Q_PROPERTY(QString UiTheme READ UiTheme WRITE setUiTheme)

public:
    typedef QActionManager<QKeySequence, QKeySequence, QAction*> KeyActionManager;
    typedef QActionManager<QMouseSequence, QMouseValue, QAction*> MouseActionManager;
    explicit QVApplication(int &argc, char **argv);
    ~QVApplication();
    QString getApplicationFilePath(QString subFilePath);
    /**
     * @brief Returns the path of the setting file according to the execution environment of the application
     * @param subFilePath
     * @return
     */
    QString getFilePathOfApplicationSetting(QString subFilePath);
    QString getUserHomeFilePath(QString subFilePath);
    QString getTranslationPath();

    void myInstallTranslator();

    // Image
    int SlideShowWait() { return m_slideShowWait; }
    void setSlideShowWait (int slideShowWait) { m_slideShowWait = slideShowWait; }
    int MaxVolumesCache() { return m_maxVolumesCache; }
    void setMaxVolumesCache (int maxVolumesCache) { m_maxVolumesCache = maxVolumesCache; }
    int MaxImagesCache() { return m_maxImagesCache; }
    void setMaxImagesCache (int maxImagesCache) { m_maxImagesCache = maxImagesCache; }
    bool DontEnlargeSmallImagesOnFitting() { return m_dontEnlargeSmallImagesOnFitting; }
    void setDontEnlargeSmallImagesOnFitting (bool dontEnlargeSmallImagesOnFitting) { m_dontEnlargeSmallImagesOnFitting = dontEnlargeSmallImagesOnFitting; }
    int MaxTextureSize() { return m_maxTextureSize; }
    void setMaxTextureSize(int maxTextureSize) { m_maxTextureSize = maxTextureSize; }
    bool UseFastDCTForJPEG() { return m_useFastDCTForJPEG; }
    void setUseFastDCTForJPEG(bool useFastDCTForJPEG) { m_useFastDCTForJPEG = useFastDCTForJPEG; }

    // Navigations

    // View
    qvEnums::ImageSortBy ImageSortBy() { return m_imageSortBy; }
    void setImageSortBy(qvEnums::ImageSortBy sortBy) { m_imageSortBy = sortBy; }
    bool Fitting() { return m_fitting; }
    void setFitting (bool fitting) { m_fitting = fitting; }
    qvEnums::FitMode ImageFitMode() { return m_fitMode; }
    void setImageFitMode(qvEnums::FitMode fitMode) { m_fitMode = fitMode; }
    QColor BackgroundColor() { return m_backgroundColor; }
    void setBackgroundColor (QColor backgroundColor) { m_backgroundColor = backgroundColor; }
    QColor BackgroundColor2() { return m_backgroundColor2; }
    void setBackgroundColor2 (QColor backgroundColor) { m_backgroundColor2 = backgroundColor; }
    bool UseCheckeredPattern() { return m_useCheckeredPattern; }
    void setUseCheckeredPattern (bool useCheckeredPattern) { m_useCheckeredPattern = useCheckeredPattern; }
    bool ShowFullscreenSignage() { return m_showFullscreenSignage; }
    void setShowFullscreenSignage (bool showFullscreenSignage) { m_showFullscreenSignage = showFullscreenSignage; }
    bool UseDirect2D() { return m_useDirect2D; }
    void setUseDirect2D(bool useDirect2D) { m_useDirect2D = useDirect2D; }
    bool ShowPanelSeparateWindow() { return m_showPanelSeparateWindow; }
    void setShowPanelSeparateWindow(bool showPanelSeparateWindow) { m_showPanelSeparateWindow = showPanelSeparateWindow; }
    bool LargeToolbarIcons() { return m_largeToolbarIcons; }
    void setLargeToolbarIcons(bool largeToolbarIcons) { m_largeToolbarIcons = largeToolbarIcons; }

    bool HideMenuBarParmanently() { return m_hideMenuBarParmanently; }
    void setHideMenuBarParmanently(bool hideMenuBarParmanently) { m_hideMenuBarParmanently = hideMenuBarParmanently; }
    bool HideToolBarParmanently() { return m_hideToolBarParmanently; }
    void setHideToolBarParmanently(bool hideToolBarParmanently) { m_hideToolBarParmanently = hideToolBarParmanently; }
    bool HidePageBarParmanently() { return m_hidePageBarParmanently; }
    void setHidePageBarParmanently(bool hidePageBarParmanently) { m_hidePageBarParmanently = hidePageBarParmanently; }

    bool HideMenuBarInFullscreen() { return m_hideMenuBarInFullscreen; }
    void setHideMenuBarInFullscreen(bool hideMenuBarInFullscreen) { m_hideMenuBarInFullscreen = hideMenuBarInFullscreen; }
    bool HideToolBarInFullscreen() { return m_hideToolBarInFullscreen; }
    void setHideToolBarInFullscreen(bool hideToolBarInFullscreen) { m_hideToolBarInFullscreen = hideToolBarInFullscreen; }
    bool HidePageBarInFullscreen() { return m_hidePageBarInFullscreen; }
    void setHidePageBarInFullscreen(bool hidePageBarInFullscreen) { m_hidePageBarInFullscreen = hidePageBarInFullscreen; }
    bool HideScrollBarInFullscreen() { return m_hideScrollBarInFullscreen; }
    void setHideScrollBarInFullscreen(bool hideScrollBarInFullscreen) { m_hideScrollBarInFullscreen = hideScrollBarInFullscreen; }
    bool HideMouseCursorInFullscreen() { return !InnerFrameShowing() && m_hideMouseCursorInFullscreen; }
    void setHideMouseCursorInFullscreen(bool hideMouseCursorInFullscreen) { m_hideMouseCursorInFullscreen = hideMouseCursorInFullscreen; }
    bool InnerFrameShowing() { return m_innerFrameShowing; }
    void setInnerFrameShowing(bool innerFrameShowing) { m_innerFrameShowing = innerFrameShowing; }

    QString TitleTextFormat() { return m_titleTextFormat; }
    void setTitleTextFormat(QString titleTextFormat) { m_titleTextFormat = titleTextFormat; }
    QString StatusTextFormat() { return m_statusTextFormat; }
    void setStatusTextFormat(QString statusTextFormat) { m_statusTextFormat = statusTextFormat; }
    bool TopWindowWhenRunWithAssoc() { return m_topWindowWhenRunWithAssoc; }
    void setTopWindowWhenRunWithAssoc(bool topWindowWhenRunWithAssoc) { m_topWindowWhenRunWithAssoc = topWindowWhenRunWithAssoc; }
    bool TopWindowWhenDropped() { return m_topWindowWhenDropped; }
    void setTopWindowWhenDropped(bool topWindowWhenDropped) { m_topWindowWhenDropped = topWindowWhenDropped; }
    bool LoupeTool() { return m_loupeTool; }
    void setLoupeTool(bool loupeTool) { m_loupeTool = loupeTool; }
    bool ScrollWithCursorWhenZooming() { return m_scrollWithCursorWhenZooming; }
    void setScrollWithCursorWhenZooming(bool scrollWithCursorWhenZooming) { m_scrollWithCursorWhenZooming = scrollWithCursorWhenZooming; }
    qvEnums::OptionViewOnStartup ShowOptionViewOnStartup() { return m_showOptionViewOnStartup; }
    void setShowOptionViewOnStartup(qvEnums::OptionViewOnStartup fitMode) { m_showOptionViewOnStartup = fitMode; }
    bool SlideShowOnNormalWindow() { return m_slideShowOnNormalWindow; }
    void setSlideShowOnNormalWindow(bool slideShowOnNormalWindow) { m_slideShowOnNormalWindow = slideShowOnNormalWindow; }
    bool SlideShowRandomly() { return m_slideShowRandomly; }
    void setSlideShowRandomly(bool slideshowRandomly) { m_slideShowRandomly = slideshowRandomly; }


    // DualView
    bool DualView() { return m_dualView; }
    void setDualView (bool dualView) { m_dualView = dualView; }
    bool StayOnTop() { return m_stayOnTop; }
    void setStayOnTop (bool stayOnTop) { m_stayOnTop = stayOnTop; }
    bool RightSideBook() { return m_rightSideBook; }
    void setRightSideBook (bool rightSideBook) { m_rightSideBook = rightSideBook; }
    bool WideImageAsOnePageInDualView() { return m_wideImageAsOnePageInDualView; }
    void setWideImageAsOnePageInDualView (bool wideImageAsOnePageInDualView) { m_wideImageAsOnePageInDualView = wideImageAsOnePageInDualView; }
    bool FirstImageAsOnePageInDualView() { return m_firstImageAsOnePageInDualView; }
    void setFirstImageAsOnePageInDualView (bool firstImageAsOnePageInDualView) { m_firstImageAsOnePageInDualView = firstImageAsOnePageInDualView; }
    bool SeparatePagesWhenWideImage() { return m_separatePagesWhenWideImage; }
    void setSeparatePagesWhenWideImage(bool separatePagesWhenWideImage) { m_separatePagesWhenWideImage = separatePagesWhenWideImage; }

    // Show Bars
    bool ShowToolBar() { return m_showToolBar; }
    void setShowToolBar (bool showToolBar) { m_showToolBar = showToolBar; }
    bool ShowSliderBar() { return m_showSliderBar; }
    void setShowSliderBar (bool showSliderBar) { m_showSliderBar = showSliderBar; }
    bool ShowStatusBar() { return m_showStatusBar; }
    void setShowStatusBar (bool showStatusBar) { m_showStatusBar = showStatusBar; }
    bool ShowMenuBar() { return m_showMenuBar; }
    void setShowMenuBar (bool showMenuBar) { m_showMenuBar = showMenuBar; }

    // RestoreWindowState
    bool RestoreWindowState() { return m_restoreWindowState; }
    void setRestoreWindowState (bool restoreWindowState) { m_restoreWindowState = restoreWindowState; }
    QByteArray WindowGeometry() { return m_windowGeometry; }
    void setWindowGeometry (QByteArray windowGeometry) { m_windowGeometry = windowGeometry; }
    QByteArray WindowState() { return m_windowState; }
    void setWindowState (QByteArray windowState) { m_windowState = windowState; }
    bool BeginAsFullscreen() { return m_beginAsFullscreen; }
    void setBeginAsFullscreen (bool beginAsFullscreen) { m_beginAsFullscreen = beginAsFullscreen; }

    // File
    bool AutoLoaded() { return m_autoLoaded; }
    void setAutoLoaded(bool autoLoaded) { m_autoLoaded = autoLoaded; }
    bool ProhibitMultipleRunning() { return m_prohibitMultipleRunning; }
    void setProhibitMultipleRunning (bool prohibitMultipleRunning) { m_prohibitMultipleRunning = prohibitMultipleRunning; }
    QString LastViewPath() { return m_lastViewPath; }
    void setLastViewPath (QString lastViewPath) { m_lastViewPath = lastViewPath; }
    bool DontSavingHistory() { return m_dontSavingHistory; }
    void setDontSavingHistory(bool savingHistory) { m_dontSavingHistory = savingHistory; }
    bool ExtractSolidArchiveToTemporaryDir() { return m_extractSolidArchiveToTemporaryDir; }
    void setExtractSolidArchiveToTemporaryDir(bool extractSolidArchiveToTemporaryDir) { m_extractSolidArchiveToTemporaryDir = extractSolidArchiveToTemporaryDir; }
    QString LastOpenedFolderPath() { return m_lastOpenedFolderPath; }
    void setLastOpenedFolderPath(QString lastOpenedFolderPath) { m_lastOpenedFolderPath = lastOpenedFolderPath; }

    // History
    int MaxHistoryCount() { return m_maxHistoryCount; }
    void setMaxHistoryCount (int maxHistoryCount) { m_maxHistoryCount = maxHistoryCount; }
    const QStringList& History() const { return m_history; }
    void clearHistory() { m_history.clear(); }
    /**
     * @brief addHistory add a path int History. if it is already in History, it will be top of this.
     * @param path
     */
    void addHistory(QString path);

    // BookMark
    QStringList& Bookmarks() { return m_bookmarks; }
    void clearBookmarks() { m_bookmarks.clear(); }
    void addBookMark(QString path, bool canDumplication=false);

    // Folder
    QString getDefaultPictureFolderPath();
    QString HomeFolderPath() { return m_homeFolderPath; }
    void setHomeFolderPath(QString path) { m_homeFolderPath = path; }
    qvEnums::FolderViewSort FolderSortMode() { return m_folderSortMode; }
    void setFolderSortMode(qvEnums::FolderViewSort mode) { m_folderSortMode = mode; }
    BookProgressManager* bookshelfManager() { return m_bookshelfManager; }
    bool OpenVolumeWithProgress() { return m_openVolumeWithProgress; }
    void setOpenVolumeWithProgress (bool openVolumeWithProgress) { m_openVolumeWithProgress = openVolumeWithProgress; }
    bool ShowReadProgress() { return m_showReadProgress; }
    void setShowReadProgress (bool showReadProgress) { m_showReadProgress = showReadProgress; }
    bool ShowSubfolders() { return m_showSubfolders; }
    void setShowSubfolders (bool showSubfolders) { m_showSubfolders = showSubfolders; }
    bool SaveReadProgress() { return m_saveReadProgress; }
    void setSaveReadProgress(bool saveReadProgress) { m_saveReadProgress = saveReadProgress; }
    bool SaveFolderViewWidth() { return m_saveFolderViewWidth; }
    void setSaveFolderViewWidth (bool saveFolderViewWidth) { m_saveFolderViewWidth = saveFolderViewWidth; }
    int FolderViewWidth() { return m_folderViewWidth; }
    void setFolderViewWidth(int folderViewWidth) { m_folderViewWidth = folderViewWidth; }

    // Catalog
    qvEnums::CatalogViewMode CatalogViewModeSetting() { return m_catalogViewModeSetting; }
    void setCatalogViewModeSetting (qvEnums::CatalogViewMode catalogViewModeSetting) { m_catalogViewModeSetting = catalogViewModeSetting; }
    QString CatalogDatabasePath();
    void setCatalogDatabasePath (QString catalogDatabasePath) { m_catalogDatabasePath = catalogDatabasePath; }
    int MaxSearchByCharChanged() { return m_maxSearchByCharChanged; }
    void setMaxSearchByCharChanged (int maxSearchByCharChanged) { m_maxSearchByCharChanged = maxSearchByCharChanged; }
    int MaxShowFrontpage() { return m_maxShowFrontpage; }
    void setMaxShowFrontpage (int maxShowFrontpage) { m_maxShowFrontpage = maxShowFrontpage; }
    bool TitleWithoutOptions() { return m_titleWithoutOptions; }
    void setTitleWithoutOptions (bool titleWithoutOptions) { m_titleWithoutOptions = titleWithoutOptions; }
    bool SearchTitleWithOptions() { return m_searchTitleWithOptions; }
    void setSearchTitleWithOptions (bool searchTitleWithOptions) { m_searchTitleWithOptions = searchTitleWithOptions; }
    bool ShowTagBar() { return m_showTagBar; }
    void setShowTagBar (bool showTagBar) { m_showTagBar = showTagBar; }
    bool IconLongText() { return m_iconLongText; }
    void setIconLongText (bool iconLongText) { m_iconLongText = iconLongText; }
    bool SaveCatalogViewWidth() { return m_saveCatalogViewWidth; }
    void setSaveCatalogViewWidth (bool saveCatalogViewWidth) { m_saveCatalogViewWidth = saveCatalogViewWidth; }
    int CatalogViewWidth() { return m_catalogViewWidth; }
    void setCatalogViewWidth(int catalogViewWidth) { m_catalogViewWidth = catalogViewWidth; }

    // ShaderEffect
    qvEnums::ShaderEffect Effect() { return m_effect; }
    void setEffect (qvEnums::ShaderEffect shaderEffect) { m_effect = shaderEffect; }
    QString BicubicShaderPath() { return getApplicationFilePath(m_bicubicShaderPath); }
    void setBicubicShaderPath (QString bicubicShaderPath) { m_bicubicShaderPath = bicubicShaderPath; }
    QString LanczosShaderPath() { return getApplicationFilePath(m_lanczosShaderPath); }
    void setLanczosShaderPath (QString lanczosShaderPath) { m_lanczosShaderPath = lanczosShaderPath; }

    // Others
    QString UiLanguage() { return m_uiLanguage; }
    void setUiLanguage (QString uiLanguage) { m_uiLanguage = uiLanguage; }
    QLanguageSelector* languageSelector() { return &m_languageSelector; }
    bool ConfirmDeletePage() { return m_confirmDeletePage; }
    void setConfirmDeletePage(bool confirmDeletePage) { m_confirmDeletePage = confirmDeletePage; }

    // Key Config
    KeyActionManager& keyActions() { return m_keyActions; }
    MouseActionManager& mouseActions() { return m_mouseActions; }

    // Appearance
    QString UiTheme() { return m_uiTheme; }
    void setUiTheme (QString uiTheme) {
        m_uiTheme = uiTheme;
        //QString themeFilePath = getApplicationFilePath(":/themes/"+m_uiTheme+".qss"); //Local files
        QString themeFilePath(":/themes/"+m_uiTheme+".qss"); // Resource files
        QFile File(themeFilePath);
        File.open(QFile::ReadOnly);
        QString styleSheet = QString(File.readAll());
        QApplication::setStyleSheet(styleSheet);
    }

    void registDefaultKeyMap();
    void registDefaultMouseMap();
    void registActions(Ui::MainWindow* ui);

    /**
     * @brief load settings from "quickviewer.ini"
     */
    void loadSettings();
    /**
     * @brief save settings int "quickviewer.ini"
     */
    void saveSettings();
    QThread* mainThread() { return m_mainThread; }

private:
    QThread* m_mainThread;
    int m_maxTextureSize;

    // Navigations
    bool m_slideShowRandomly;

    // View
    qvEnums::ImageSortBy m_imageSortBy;
    bool m_fitting;
//    bool m_fitToWidth;
    qvEnums::FitMode m_fitMode;
    bool m_dualView;
    bool m_stayOnTop;
    /**
     * @brief if true, it will be supported for 'bound on the left side books'(e.g. books in Japan)
     */
    bool m_rightSideBook;
    /**
     * @brief if true, a wide image must be one view whether dual view is enabled
     */
    bool m_wideImageAsOnePageInDualView;
    bool m_firstImageAsOnePageInDualView;
    bool m_showSubfolders;
    int m_slideShowWait;
    int m_maxVolumesCache;
    int m_maxImagesCache;
    QColor m_backgroundColor;
    QColor m_backgroundColor2;
    bool m_useCheckeredPattern;
    bool m_dontEnlargeSmallImagesOnFitting;
    bool m_showFullscreenSignage;
//    bool m_showFullscreenTitleBar;
    bool m_useDirect2D;
    bool m_useFastDCTForJPEG;
    bool m_showPanelSeparateWindow;
    bool m_largeToolbarIcons;

    bool m_hideMenuBarParmanently;
    bool m_hideToolBarParmanently;
    bool m_hidePageBarParmanently;

    bool m_hideMenuBarInFullscreen;
    bool m_hideToolBarInFullscreen;
    bool m_hidePageBarInFullscreen;
    bool m_hideScrollBarInFullscreen;
    bool m_hideMouseCursorInFullscreen;

    bool m_topWindowWhenRunWithAssoc;
    bool m_topWindowWhenDropped;
    bool m_separatePagesWhenWideImage;
    bool m_loupeTool;
    QString m_titleTextFormat;
    QString m_statusTextFormat;
    bool m_scrollWithCursorWhenZooming;
    qvEnums::OptionViewOnStartup m_showOptionViewOnStartup;
    bool m_slideShowOnNormalWindow;

    // ToolBars
    bool m_showToolBar;
    bool m_showSliderBar;
    bool m_showStatusBar;
    bool m_showMenuBar;

    // WindowStates
    bool m_restoreWindowState;
    QByteArray m_windowGeometry;
    QByteArray m_windowState;
    bool m_beginAsFullscreen;
    bool m_innerFrameShowing;

    // File
    bool m_autoLoaded;
    QStringList m_history;
    int m_maxHistoryCount;
    QStringList m_bookmarks;
    int m_maxBookmarkCount;
    bool m_prohibitMultipleRunning;
    QString m_lastViewPath;
    bool m_dontSavingHistory;
    bool m_extractSolidArchiveToTemporaryDir;
    QString m_lastOpenedFolderPath;

    // Folder
    QString m_homeFolderPath;
    qvEnums::FolderViewSort m_folderSortMode;
    bool m_openVolumeWithProgress;
    bool m_showReadProgress;
    bool m_saveReadProgress;
    bool m_saveFolderViewWidth;
    int m_folderViewWidth;

    // Catalog
    qvEnums::CatalogViewMode m_catalogViewModeSetting;
    QString m_catalogDatabasePath;
    int m_maxSearchByCharChanged;
    int m_maxShowFrontpage;
    bool m_titleWithoutOptions;
    bool m_searchTitleWithOptions;
    bool m_switchVolumesWhenCatalogShowing;
    bool m_showTagBar;
    bool m_iconLongText;
    bool m_saveCatalogViewWidth;
    int m_catalogViewWidth;

    // KeyConfig
    QActionManager<QKeySequence, QKeySequence, QAction*> m_keyActions;
    QActionManager<QMouseSequence, QMouseValue, QAction*> m_mouseActions;


    // Shader Effect
    qvEnums::ShaderEffect m_effect;
    QString m_bicubicShaderPath;
    QString m_lanczosShaderPath;

    // Others
    QString m_uiLanguage;
    QTranslator *m_translator;
    bool m_confirmDeletePage;

    // Appearance
    QString m_uiTheme;

    QSettings* m_settings;
    BookProgressManager* m_bookshelfManager;

    QLanguageSelector m_languageSelector;
    QLanguageSelector m_qtbaseLanguageSelector;

#if defined(Q_OS_WIN)
    // System Dependable
    bool m_portable;
#endif
};

#endif // QVAPPLICATION_H
