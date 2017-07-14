#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include "models/filevolume.h"
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
    virtual bool moveToTrush(QString path) {return false;}
    virtual bool setStayOnTop(bool ) {return false;}
    virtual void setWindowTop() {}
    virtual void setMailAttachment(QString path) {}

    void resetShortcutKeys();
    void keyPressEvent(QKeyEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);
    void makeHistoryMenu();
    void resetVolume(IFileVolume* newer);
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
    void loadVolume(QString path);
    bool isCatalogSearching();
    bool isFolderSearching();

protected:
    void dragEnterEvent(QDragEnterEvent *e) override;
    void dropEvent(QDropEvent *e) override;
//    void paintEvent( QPaintEvent *event ) override;
    void wheelEvent(QWheelEvent *e) override;
    void contextMenuEvent(QContextMenuEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void closeEvent(QCloseEvent *e) override;
    void resizeEvent(QResizeEvent *e) override;
    void changeEvent(QEvent *e) override;

public slots:
    // File
    void on_file_changed(QString path);
    void on_autoloaded_triggered(bool autoreload);
    void on_clearHistory_triggered();
    void on_historyMenu_triggered(QAction *action);
    void on_exit_triggered();

    // Folder
    void on_folderWindow_triggered();
    void on_folderWindowClosed_triggered();
    void on_openVolumeByFolder_triggered(QString path);
    void on_openVolumeWithProgress_triggered(bool enabled);
    void on_showReadProgress_triggered(bool enabled);

    // Catalog
    void on_manageCatalogs_triggered();
    void on_manageCatalogsClosed_triggered();
    void on_openVolumeByCatalog_triggered(QString path);
    void on_searchTitleWithOptions_triggered(bool enable);
    void on_catalogTitleWithoutOptions_triggered(bool enable);
    void on_catalogViewList_triggered();
    void on_catalogViewIcon_triggered();
    void on_catalogViewNotext_triggered();
    void on_catalogShowTagBar_triggered(bool enable);
    void on_catalogIconLongText_triggered(bool enable);

    // Exif
    void on_openExifDialog_triggered();
    void on_openExifDialogClosed_triggered();

    // PageBar
    void on_pageChanged_triggered();
    void on_volumeChanged_triggered(QString path);
    void on_pageSlider_changed(int value);
    void on_pageNolongerNeeded_triggered();

    // View
    void on_fullscreen_triggered();
    void on_stayOnTop_triggered(bool top);
    void on_restoreWindowState_triggered(bool saveState);
    void on_maximizeOrNormal_triggered();
    void on_openOptionsDialog_triggered();
    void on_beginAsFullscreen_triggered(bool enable);
    void on_showFullscreenSignage_triggered(bool enable);

    // SlideShow
    void on_slideShow_triggered(bool enable);

    // Toolbars
    void on_showToolBar_triggered(bool showToolBar);
    void on_showSliderBar_triggered(bool showSliderBar);
    void on_showStatusBar_triggered(bool showStatusBar);
    void on_showMenuBar_triggered(bool showMenuBar);

    // Help
    void on_openKeyConfig_triggered();
    void on_projectPage_triggered();
    void on_checkVersion_triggered();
    void on_appVersion_triggered();
    void on_languageEnglish_triggered();
    void on_languageJapanese_triggered();
    void on_languageSpanish_triggered();
    void on_languageChinese_triggered();

    // ContextMenus
    void on_openfolder_triggered();
    void on_deletePage_triggered();
    void on_exitApplicationOrFullscreen_triggered();
    void on_mailAttachment_triggered();
    void on_renameImageFile_triggered();

    // Shaders
    void on_shaderNearestNeighbor_triggered();
    void on_shaderBilinear_triggered();
    void on_shaderBicubic_triggered();
    void on_shaderLanczos_triggered();
    void on_shaderBilinearBeforeCpuBicubic_triggered();
    void on_shaderCpuBicubic_triggered();

    // Bookmark
    void on_saveBookmark_triggered();
    void on_clearBookmarks_triggered();
    void on_loadBookmark_triggered();
    void on_loadBookmarkMenu_triggered(QAction *action);

    void on_messageReceived(QString data);

private slots:
    void on_hover_anchor(Qt::AnchorPoint anchor);
    void on_fittingChanged(bool fitting);


protected:
    Ui::MainWindow *ui;
    bool m_viewerWindowStateMaximized;
    bool m_sliderChanging;

    QMenu* contextMenu;

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
