#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include "models/volumemanager.h"
#include "imageview.h"
#include "imagestring.h"
#include "qlanguageselector.h"

namespace Ui {
class MainWindow;
}
class FolderWindow;
class CatalogWindow;
class ThumbnailManager;
class BrightnessWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    virtual bool moveToTrush(QString ) {return false;}
    virtual bool setStayOnTop(bool ) {return false;}
    virtual void setWindowTop(bool ) {}
    virtual void setMailAttachment(QString ) {}
    virtual bool eventFilter(QObject *obj, QEvent *event);

    /**
     * @brief loadVolume
     * @param prohibitProhibit2Page prohbit 2 page viewing
     */
    void loadVolume(QString path, bool prohibitProhibit2Page=false);
    void loadVolumeWithAssoc(QString path);

    void resetShortcutKeys();
    void makeHistoryMenu();
    void resetVolume(VolumeManager* newer);
    void uncheckAllShaderMenus() {
        foreach(QAction* action, m_shaderMenuGroup) {
            action->setChecked(false);
        }
    }
    void uncheckAllLanguageMenus() {
        foreach(QAction* action, m_languageMenuGroup) {
            action->setChecked(false);
        }
    }
    void makeBookmarkMenu();
    void setThumbnailManager(ThumbnailManager* manager);
    void resetVolumeCaption();
    void resetShortCut(const QString name, const QString shortcuttext, bool removed);

    void closeAllDockedWindow();

    // FolderWindow
    bool isFolderSearching();
    void createFolderWindow(bool docked, QString path="");
    bool changeFolderPath(QString path);

    // CatalogWindow
    bool isCatalogSearching();
    void createCatalogWindow(bool docked);

    // BrightnessWindow
    void createBrightnessWindow(bool docked);


protected:
    void dragEnterEvent(QDragEnterEvent *e) override;
    void dropEvent(QDropEvent *e) override;
//    void paintEvent( QPaintEvent *event ) override;
    void wheelEvent(QWheelEvent *e) override;
    void keyPressEvent(QKeyEvent *event);
//    void contextMenuEvent(QContextMenuEvent *e) override;
//    void mousePressEvent(QMouseEvent *e) override;
    void closeEvent(QCloseEvent *e) override;
    void resizeEvent(QResizeEvent *e) override;
    void on_pageNolongerNeeded_triggered();
	void touchEvent(QTouchEvent* e);

signals:
    void changingFullscreen(bool);

public slots:
    // File
    void onActionAutoLoaded_triggered(bool autoreload);
    void onActionClearHistory_triggered();
    void onMenuHistory_triggered(QAction *action);
    void onActionExit_triggered();
    void onSavingHistory_triggered(bool enable);

    // Folder
    void onActionShowFolder_triggered();
    void onFolderWindow_closed();
    void onFolderWindow_openVolume(QString path);
    void onActionOpenVolumeWithProgress_triggered(bool enabled);
    void onActionShowReadProgress_triggered(bool enabled);
    void onActionSaveReadProgress_triggered(bool enable);
    void onActionSaveFolderViewWidth_triggered(bool enable);

    // Catalog
    void onActionShowCatalog_triggered();
    void onCatalogWindow_closed();
    void onCatalogWindow_openVolume(QString path);
    void onActionSearchTitleWithOptions_triggered(bool enable);
    void onActionCatalogTitleWithoutOptions_triggered(bool enable);
    void onActionCatalogViewList_triggered();
    void onActionCatalogViewIcon_triggered();
    void onActionCatalogViewIconNoText_triggered();
    void onActionShowTagBar_triggered(bool enable);
    void onActionCatalogIconLongText_triggered(bool enable);
    void onActionSaveCatalogViewWidth_triggered(bool enable);

    // RetouchWindow
    void onActionShowBrightnessWindow_triggered(bool enable);
    void onBrightnessWindow_closed();

    // Navigation
    void onActionTurnPageOnLeft_triggered();
    void onActionTurnPageOnRight_triggered();

    // Exif
    void onActionOpenExif_triggered();
    void onExifDialog_closed();

    // PageBar
    void onPageManager_pageChanged();
    void onPageManager_volumeChanged(QString path);
    void onPageSlider_valueChanged(int value);

    // View
    virtual void onActionFullscreen_triggered();
    void onActionStayOnTop_triggered(bool top);
    void onActionRestoreWindowState_triggered(bool saveState);
    void onActionMaximizeOrNormal_triggered();
    void onActionOpenOptionsDialog_triggered();
    void onActionBeginAsFullscreen_triggered(bool enable);
//    void onActionShowFullscreenTitleBar_triggered(bool enable);
    void onActionShowPanelSeparateWindow_triggered(bool enable);
    void onActionLargeToolbarIcons_triggered(bool enable);

    // SlideShow
    void onActionSlideShow_triggered(bool enable);

    // Toolbars
    void onActionShowToolBar_triggered(bool showToolBar);
    void onActionShowPageBar_triggered(bool showSliderBar);
    void onActionShowStatusBar_triggered(bool showStatusBar);
    void onActionShowMenuBar_triggered(bool showMenuBar);

    // Help
    void onActionOpenKeyConfig_triggered();
    void onActionOpenMouseConfig_triggered();
    void onActionProjectWeb_triggered();
    void onActionCheckVersion_triggered();
    void onActionAppVersion_triggered();
//    void on_languageEnglish_triggered();
//    void on_languageJapanese_triggered();
//    void on_languageSpanish_triggered();
//    void on_languageChinese_triggered();
    void onLanguageSelector_languageChanged(QString language);
    void onLanguageSelector_openTextEditorForLanguage(LanguageInfo info);
    void onActionRegistAssocs_triggered();
    void onActionRegistAssocsUAC_triggered();

    // ContextMenus
    void onActionContextMenu_triggered();
    void onActionOpenfolder_triggered();
    void onActionRecyclePage_triggered();
    void onActionDeletePage_triggered();
    void onActionExitApplicationOrFullscreen_triggered();
    void onActionMailAttachment_triggered();
    void onActionRenameImageFile_triggered();
    void onActionConfirmDeletePage_triggered(bool enable);

    // Shaders
    void onActionShaderNearestNeighbor_triggered();
    void onActionShaderBilinear_triggered();
    void onActionShaderBicubic_triggered();
    void onActionShaderLanczos_triggered();
    void onActionShaderBilinearBeforeCpuBicubic_triggered();
    void onActionShaderCpuBicubic_triggered();
    void onActionShaderCpuSpline16_triggered();
    void onActionShaderCpuSpline36_triggered();
    void onActionShaderCpuLanczos3_triggered();
    void onActionShaderCpuLanczos4_triggered();

    // Bookmark
    void onActionSaveBookmark_triggered();
    void onActionClearBookmarks_triggered();
    void onActionLoadBookmark_triggered();
    void onMenuLoadBookmark_triggered(QAction *action);

    // Others
    virtual void onGraphicsView_anchorHovered(Qt::AnchorPoint anchor);
    void onScrollModeChanged(bool scrolled);

private slots:
    void onGraphicsView_fittingChanged(qvEnums::FitMode mode);


protected:
    Ui::MainWindow *ui;
    bool m_viewerWindowStateMaximized;
    bool m_sliderChanging;
    bool m_onWindowClosing;

    /**
     * @brief m_contextMenu Define on the context menu mainwindow.ui for the main screen and separate at startup
     */
    QMenu* m_contextMenu;

    QString m_volumeCaption;
    QString m_pageCaption;

    PageManager m_pageManager;
    ImageString m_imageString;
    QList<QAction*> m_shaderMenuGroup;
    QList<QAction*> m_languageMenuGroup;
    ThumbnailManager* m_thumbManager;
    FolderWindow* m_folderWindow;
    CatalogWindow* m_catalogWindow;
    BrightnessWindow* m_brightnessWindow;
    ExifDialog* m_exifDialog;
    QToolButton* m_fullscreenButton;
    uint m_menubarFontSize;
	uint m_pageSliderHeight;
};


#endif // MAINWINDOW_H
