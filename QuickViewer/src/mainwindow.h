#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include "models/volumemanager.h"
#include "imageview.h"

namespace Ui {
class MainWindow;
}
class FolderWindow;
class CatalogWindow;
class ThumbnailManager;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    virtual bool moveToTrush(QString ) {return false;}
    virtual bool setStayOnTop(bool ) {return false;}
    virtual void setWindowTop() {}
    virtual void setMailAttachment(QString ) {}
    virtual bool eventFilter(QObject *obj, QEvent *event);

    void loadVolume(QString path, bool prohibitProhibit2Page=false);
    void resetShortcutKeys();
    void keyPressEvent(QKeyEvent *event);
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
    bool isCatalogSearching();
    bool isFolderSearching();

protected:
    void dragEnterEvent(QDragEnterEvent *e) override;
    void dropEvent(QDropEvent *e) override;
//    void paintEvent( QPaintEvent *event ) override;
    void wheelEvent(QWheelEvent *e) override;
//    void contextMenuEvent(QContextMenuEvent *e) override;
//    void mousePressEvent(QMouseEvent *e) override;
    void closeEvent(QCloseEvent *e) override;
    void resizeEvent(QResizeEvent *e) override;
    void on_pageNolongerNeeded_triggered();

signals:
    void changingFullscreen(bool);

public slots:
    // File
    void onActionAutoLoaded_triggered(bool autoreload);
    void onActionClearHistory_triggered();
    void onMenuHistory_triggered(QAction *action);
    void onActionExit_triggered();

    // Folder
    void onActionShowFolder_triggered();
    void onFolderWindow_closed();
    void onFolderWindow_openVolume(QString path);
    void onActionOpenVolumeWithProgress_triggered(bool enabled);
    void onActionShowReadProgress_triggered(bool enabled);

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
    void onActionShowFullscreenSignage_triggered(bool enable);
//    void onActionShowFullscreenTitleBar_triggered(bool enable);
    void on_windowTop();

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

    // Bookmark
    void onActionSaveBookmark_triggered();
    void onActionClearBookmarks_triggered();
    void onActionLoadBookmark_triggered();
    void onMenuLoadBookmark_triggered(QAction *action);

    // Others
    virtual void onGraphicsView_anchorHovered(Qt::AnchorPoint anchor);

private slots:
    void onGraphicsView_fittingChanged(bool fitting);


protected:
    Ui::MainWindow *ui;
    bool m_viewerWindowStateMaximized;
    bool m_sliderChanging;

    /**
     * @brief m_contextMenu Define on the context menu mainwindow.ui for the main screen and separate at startup
     */
    QMenu* m_contextMenu;

    QString m_volumeCaption;
    QString m_pageCaption;

    PageManager m_pageManager;
    QList<QAction*> m_shaderMenuGroup;
    QList<QAction*> m_languageMenuGroup;
    ThumbnailManager* m_thumbManager;
    FolderWindow* m_folderWindow;
    CatalogWindow* m_catalogWindow;
    ExifDialog* m_exifDialog;
};


#endif // MAINWINDOW_H
