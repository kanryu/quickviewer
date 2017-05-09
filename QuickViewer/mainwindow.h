#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include "filevolume.h"
#include "imageview.h"

namespace Ui {
class MainWindow;
}
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

    void keyPressEvent(QKeyEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);
    void makeHistoryMenu();
    void resetVolume(IFileVolume* newer);
    void uncheckAllShaderMenus() {
        foreach(QAction* action, m_shaderMenuGroup) {
            action->setChecked(false);
        }
    }
    void makeBookmarkMenu();
    void setThumbnailManager(ThumbnailManager* manager);
    void loadVolume(QString path);

protected:
    void dragEnterEvent(QDragEnterEvent *e);
    void dropEvent(QDropEvent *e);
//    void paintEvent( QPaintEvent *event );
    void wheelEvent(QWheelEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void closeEvent(QCloseEvent *e);

public slots:
    // File
    void on_file_changed(QString path);
    void on_autoloaded_triggered(bool autoreload);
    void on_clearHistory_triggered();
    void on_historyMenu_triggered(QAction *action);
    // Catalog
    void on_manageCatalogs_triggered();
    void on_manageCatalogsClosed_triggered();
    void on_openVolumeByCatalog_triggered(QString path);

    // PageBar
    void on_pageChanged_triggered();
    void on_volumeChanged_triggered();
    void on_pageSlider_changed(int value);
    void on_exit_triggered();

    // View
    void on_fullscreen_triggered();
    void on_stayOnTop_triggered(bool top);
    void on_restoreWindowState_triggered(bool saveState);
    void on_maximizeOrNormal_triggered();

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

    // ContextMenus
    void on_openfolder_triggered();
    void on_deletePage_triggered();
    void on_exitApplicationOrFullscreen_triggered();

    // Shaders
    void on_shaderNearestNeighbor_triggered();
    void on_shaderBilinear_triggered();
    void on_shaderBicubic_triggered();
    void on_shaderLanczos_triggered();

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
    ThumbnailManager* m_thumbManager;
    CatalogWindow* m_catalogWindow;
};


#endif // MAINWINDOW_H
