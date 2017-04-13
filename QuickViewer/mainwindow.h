#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include "filevolume.h"
#include "imageview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    virtual bool moveToTrush(QString path) {return false;}

    void keyPressEvent(QKeyEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);
    void loadVolume(QString path);
    void makeHistoryMenu();
    void resetVolume(IFileVolume* newer);
    void uncheckAllShaderMenus() {
        foreach(QAction* action, m_shaderMenuGroup) {
            action->setChecked(false);
        }
    }

protected:
    void dragEnterEvent(QDragEnterEvent *e);
    void dropEvent(QDropEvent *e);
//    void paintEvent( QPaintEvent *event );
    void wheelEvent(QWheelEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void closeEvent(QCloseEvent *e);

public slots:
    void on_file_changed(QString path);
    void on_clearHistory_triggered();
    void on_fullscreen_triggered();
    void on_stayOnTop_triggered(bool top);
    void on_pageChanged_triggered();
    void on_volumeChanged_triggered();
    void on_pageSlider_changed(int value);
    void on_appVersion_triggered();
    void on_autoloaded_triggered(bool autoreload);
    void on_historymenu_triggered(QAction *action);
    void on_openfolder_triggered();
    void on_showToolBar_triggered(bool showToolBar);
    void on_showSliderBar_triggered(bool showSliderBar);
    void on_showStatusBar_triggered(bool showStatusBar);
    void on_showMenuBar_triggered(bool showMenuBar);
    void on_openKeyConfig_triggered();
    void on_checkVersion_triggered();
    void on_exitApplicationOrFullscreen_triggered();
    void on_exit_triggered();
    void on_deletePage_triggered();
    void on_maximizeOrNormal_triggered();
    void on_restoreWindowState_triggered(bool saveState);

    void on_shaderNearestNeighbor_triggered();
    void on_shaderBilinear_triggered();
    void on_shaderBicubic_triggered();
    void on_shaderLanczos_triggered();

private slots:
    void on_hover_anchor(Qt::AnchorPoint anchor);


protected:
    Ui::MainWindow *ui;
    bool m_viewerWindowStateMaximized;
    bool m_sliderChanging;

    QMenu contextMenu;

    QString m_volumeCaption;
    QString m_pageCaption;

    PageManager m_pageManager;
    QList<QAction*> m_shaderMenuGroup;
};


#endif // MAINWINDOW_H
