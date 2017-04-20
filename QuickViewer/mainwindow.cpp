#include <QDragEnterEvent>
#include <QDropEvent>
#include <QWheelEvent>
#include <QMimeData>
#include <QMessageBox>
#include <QFileDialog>
#include <QDesktopServices>
#include <QDesktopWidget>
#include <QWindow>

#include "mainwindow.h"
#include "imageview.h"
#include "ui_mainwindow.h"
#include "fileloaderdirectory.h"
#include "qv_init.h"
#include "qvapplication.h"
#include "keyconfigdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_sliderChanging(false)
    , m_viewerWindowStateMaximized(false)
    , contextMenu(this)
    , m_pageManager(this)
{
    ui->setupUi(this);
    ui->graphicsView->setPageManager(&m_pageManager);
    setAcceptDrops(true);
    ui->pageSlider->hide();
    QVApplication* myapp = qApp;

    // Mapping to Key-Action Table and Key Config Dialog
    qApp->registActions(ui);

    m_shaderMenuGroup
            << ui->actionShaderNearestNeighbor
            << ui->actionShaderBilinear
            << ui->actionShaderBicubic
            << ui->actionShaderLanczos;

    ui->actionFitting->setChecked(qApp->Fitting());
    ui->graphicsView->on_fitting_triggered(qApp->Fitting());

    ui->actionDualView->setChecked(qApp->DualView());
    ui->graphicsView->on_dualView_triggered(qApp->DualView());

    ui->actionStayOnTop->setChecked(qApp->StayOnTop());
    ui->actionStayOnTop->triggered(qApp->StayOnTop());

    ui->graphicsView->on_rightSideBook_triggered(qApp->RightSideBook());
    ui->actionRightSideBook->setChecked(qApp->RightSideBook());

    ui->actionWideImageAsOneView->setChecked(qApp->WideImageAsOnePageInDualView());
    ui->actionFirstImageAsOneView->setChecked(qApp->FirstImageAsOnePageInDualView());

    ui->actionAutoLoaded->setChecked(qApp->AutoLoaded());

    // ToolBar/PageBar/StatusBar/MenuBar
    ui->actionShowToolBar->setChecked(qApp->ShowToolBar());
    ui->actionShowToolBar->triggered(qApp->ShowToolBar());
    ui->actionShowPageBar->setChecked(qApp->ShowSliderBar());
    ui->actionShowPageBar->triggered(qApp->ShowSliderBar());
    ui->actionShowStatusBar->setChecked(qApp->ShowStatusBar());
    ui->actionShowStatusBar->triggered(qApp->ShowStatusBar());
    ui->actionShowMenuBar->setChecked(qApp->ShowMenuBar());
    if(!qApp->ShowMenuBar())
        menuBar()->hide();

    // History
    makeHistoryMenu();
    connect(ui->menuHistory, SIGNAL(triggered(QAction*)), this, SLOT(on_historyMenu_triggered(QAction*)) );

    // Bookmarks
    makeBookmarkMenu();
    ui->actionLoadBookmark->setMenu(ui->menuLoadBookmark);
    connect(ui->menuLoadBookmark, SIGNAL(triggered(QAction*)), this, SLOT(on_loadBookmarkMenu_triggered(QAction*)) );

    ui->statusBar->addPermanentWidget(ui->statusLabel);
    ui->statusLabel->setText(tr("any folder or archive is not loaded."));

    switch(qApp->Effect()) {
    case ShaderManager::NearestNeighbor: ui->actionShaderNearestNeighbor->setChecked(true); break;
    case ShaderManager::Bilinear: ui->actionShaderBilinear->setChecked(true); break;
    case ShaderManager::Bicubic: ui->actionShaderBicubic->setChecked(true); break;
    case ShaderManager::Lanczos: ui->actionShaderLanczos->setChecked(true); break;
    }


    ui->graphicsView->installEventFilter(this);
    ui->mainToolBar->installEventFilter(this);
    ui->pageFrame->installEventFilter(this);

    // Context menus
    contextMenu.addAction(ui->actionNextOnePage);
    contextMenu.addAction(ui->actionPrevOnePage);
    contextMenu.addSeparator();
    contextMenu.addAction(ui->actionCopyPage);
    contextMenu.addAction(ui->actionDeletePage);
    contextMenu.addAction(ui->actionCopyFile);
    contextMenu.addSeparator();
    contextMenu.addAction(ui->actionOpenFiler);
    contextMenu.addAction(ui->actionOpenExif);
    contextMenu.addSeparator();
    contextMenu.addAction(ui->actionWideImageAsOneView);
    contextMenu.addAction(ui->actionFirstImageAsOneView);

    connect(ui->graphicsView, SIGNAL(anchorHovered(Qt::AnchorPoint)), this, SLOT(on_hover_anchor(Qt::AnchorPoint)) );
//    connect(ui->graphicsView, SIGNAL(pageChanged()), this, SLOT(on_pageChanged_triggered()) );
    connect(ui->pageSlider, SIGNAL(valueChanged(int)), this, SLOT(on_pageSlider_changed(int)) );
    connect(&m_pageManager, SIGNAL(pageChanged()), this, SLOT(on_pageChanged_triggered()));
    connect(&m_pageManager, SIGNAL(volumeChanged()), this, SLOT(on_volumeChanged_triggered()));

    setWindowTitle(QString("%1 v%2").arg(qApp->applicationName()).arg(qApp->applicationVersion()));
    // WindowState Restoreing
    if(qApp->RestoreWindowState()) {
        ui->actionRestoreWindowState->setChecked(qApp->RestoreWindowState());
        restoreGeometry(qApp->WindowGeometry());
        restoreState(qApp->WindowState());
        if(isFullScreen()) {
            menuBar()->hide();
            ui->mainToolBar->hide();
            ui->pageFrame->hide();
            statusBar()->hide();
            ui->actionFullscreen->setChecked(true);
            ui->graphicsView->readyForPaint();
        }
    }

    if(qApp->arguments().length() >= 2) {
        loadVolume(qApp->arguments().last());
        return;
    }
    if(qApp->AutoLoaded() && qApp->History().size() > 0) {
        loadVolume(qApp->History().at(0));
    }
}


MainWindow::~MainWindow()
{
    delete ui;
    m_pageManager.dispose();
    qApp->saveSettings();
}

void MainWindow::dragEnterEvent(QDragEnterEvent *e)
{
//    if(e->mimeData()->hasFormat("text/uri-list"))
//    {
//        //視覚的にドロップを受付られることを
//        //表示し、ドラッグ＆ドロップを受け付ける
//        //これがないと受付られない。
////        e->acceptProposedAction();
//        e->accept();
//    }
     e->accept();
}

void MainWindow::dropEvent(QDropEvent *e)
{
    if(e->mimeData()->hasUrls()) {
        QList<QUrl> urlList = e->mimeData()->urls();
        for (int i = 0; i < 1; i++) {
            QUrl url = urlList[i];
            loadVolume(url.toLocalFile());
        }
    }
}

void MainWindow::wheelEvent(QWheelEvent *e)
{
    if(e->delta() < 0) {
        ui->actionNextPage->trigger();
    }
    if(e->delta() > 0) {
        ui->actionPrevPage->trigger();
    }
    e->accept();
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::MiddleButton) {
        on_fullscreen_triggered();
    }
    if(e->button() == Qt::RightButton) {
        contextMenu.exec(QCursor::pos());
    }
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    qApp->setWindowGeometry(saveGeometry());
    qApp->setWindowState(saveState());
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    QKeyEvent *keyEvent = NULL;//event data, if this is a keystroke event
    QMouseEvent *mouseEvent = NULL;//event data, if this is a keystroke event
    //QDragEnterEvent  *dragEnterEvent = NULL;//event data, if this is a keystroke event
    //QDropEvent *dropEvent = NULL;//event data, if this is a keystroke event

//    if(obj == ui->graphicsView) {
//        qDebug() << "graphicsView <= " << event->type();
//    } else {
//        qDebug() << obj << " <= " << event->type();
//    }

    switch (event->type()) {
    case QEvent::KeyPress:
        if(obj == ui->graphicsView) {
            keyEvent = dynamic_cast<QKeyEvent*>(event);
            this->keyPressEvent(keyEvent);
            return true;
        }
        break;
    case QEvent::MouseButtonPress:
        if(obj == ui->graphicsView) {
            mouseEvent = dynamic_cast<QMouseEvent*>(event);
            // 5 buttons mouse forward for browsers
            if(mouseEvent->button() == Qt::ForwardButton) {
                ui->actionNextPage->trigger();
                return true;
            }
            // 5 buttons mouse back for browsers
            if(mouseEvent->button() == Qt::BackButton) {
                ui->actionPrevPage->trigger();
                return true;
            }
            // tap left/right of window
            if(mouseEvent->button() == Qt::LeftButton) {
                if(ui->graphicsView->hoverState() == Qt::AnchorLeft) {
                    if(qApp->RightSideBook())
                        ui->actionNextPage->trigger();
                    else
                        ui->actionPrevPage->trigger();
                    return true;
                }
                if(ui->graphicsView->hoverState() == Qt::AnchorRight) {
                    if(qApp->RightSideBook())
                        ui->actionPrevPage->trigger();
                    else
                        ui->actionNextPage->trigger();
                    return true;
                }
            }
        }
        break;
    case QEvent::Leave:
        if(obj == ui->mainToolBar && isFullScreen()) {
            ui->mainToolBar->hide();
            return true;
        }
        if(obj == ui->pageFrame && isFullScreen()) {
            ui->pageFrame->hide();
            return true;
        }
        break;
    default:
        break;
    }
    return QObject::eventFilter(obj, event);
}

void MainWindow::loadVolume(QString path)
{
    if(m_pageManager.loadVolume(path)) {
        return;
    }
    QMessageBox msgBox(this);
    msgBox.setWindowTitle(tr("open error"));
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setText(QApplication::applicationVersion());
    QString message = QString("<h2>%1</h2><p>%2</p>")
            .arg(tr("Can't be opened. Is there no images?"))
            .arg(path);
    msgBox.setText(message);
    msgBox.exec();
}


void MainWindow::makeHistoryMenu()
{
    static const QString shortcuts = "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    ui->menuHistory->clear();
    QStringList history = qApp->History();
    for(int i = 0; i < history.size(); i++) {
        QString text = QString("&%1: %2").arg(shortcuts.mid(i, 1)).arg(history.at(i));
        ui->menuHistory->addAction(text);
    }
}

void MainWindow::makeBookmarkMenu()
{
    static const QString shortcuts = "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    ui->menuLoadBookmark->clear();
    QStringList bookmarks = qApp->Bookmarks();
    if(!bookmarks.size())
        return;
    for(int i = 0; i < bookmarks.size(); i++) {
        QString path = bookmarks[i];
        QFileInfo info(path);
        QString text = QString("&%1: %2 - %3")
                .arg(shortcuts.mid(i, 1))
                .arg(info.fileName())
                .arg(info.dir().dirName());
        QAction* action = ui->menuLoadBookmark->addAction(text);
        action->setData(path);
    }
    ui->menuLoadBookmark->addSeparator();
    ui->menuLoadBookmark->addAction(ui->actionClearBookmarks);
}

/**
 * @brief 固定的なホットキーの設定
 */
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    QKeySequence seq(event->key() | event->modifiers());
    qDebug() << seq;
    QAction* action = qApp->getAction(seq);
    if(action)
        action->trigger();
}


void MainWindow::on_exit_triggered()
{
    QApplication::quit();
    QCoreApplication::quit();
}



void MainWindow::on_file_changed(QString path)
{
    //qDebug() << "[MainWindow] newImage:" << path;

}

void MainWindow::on_clearHistory_triggered()
{
    qApp->clearHistory();
    makeHistoryMenu();
}

void MainWindow::on_fullscreen_triggered()
{

    if(isFullScreen()) {
        ui->graphicsView->skipRisizeEvent(true);
        if(qApp->ShowMenuBar())
            menuBar()->show();
        if(qApp->ShowToolBar())
            ui->mainToolBar->show();
        if(qApp->ShowSliderBar())
            ui->pageFrame->show();
        if(qApp->ShowStatusBar())
            statusBar()->show();
        ui->actionFullscreen->setChecked(false);
        ui->graphicsView->skipRisizeEvent(false);

        if(m_viewerWindowStateMaximized) {
            showMaximized();
        } else {
            showNormal();
        }
        ui->graphicsView->readyForPaint();
        if(ui->graphicsView->isSlideShow())
            ui->graphicsView->toggleSlideShow();
    } else {
        ui->graphicsView->skipRisizeEvent(true);
        m_viewerWindowStateMaximized = isMaximized();

        menuBar()->hide();
        ui->mainToolBar->hide();
        ui->pageFrame->hide();
        statusBar()->hide();
        ui->actionFullscreen->setChecked(true);
        showFullScreen();
        ui->graphicsView->readyForPaint();
    }
}

void MainWindow::on_stayOnTop_triggered(bool top)
{
    qApp->setStayOnTop(top);
    if(setStayOnTop(top))
        return;
    Qt::WindowFlags flags = windowFlags();
    if(top) {
        flags |= Qt::WindowStaysOnTopHint;
    } else {
        flags &= ~Qt::WindowStaysOnTopHint;
    }
//    flags |= Qt::WindowFullscreenButtonHint;
    setWindowFlags(flags);
    show();
//    setParent(nullptr);
}

void MainWindow::on_hover_anchor(Qt::AnchorPoint anchor)
{
    if(!isFullScreen()) {
        return;
    }
    if(anchor == Qt::AnchorTop) {
        ui->mainToolBar->show();
    }
    if(anchor == Qt::AnchorBottom) {
        if(qApp->ShowSliderBar())
            ui->pageFrame->show();
    }
    if(anchor == Qt::AnchorHorizontalCenter) {
        ui->mainToolBar->hide();
        ui->pageFrame->hide();
    }
}

void MainWindow::on_pageChanged_triggered()
{
    //qDebug() << "on_pageChanged_triggered";
    // PageSlider
    ui->pageLabel->setText(m_pageManager.currentPageNumAsString());
    m_sliderChanging = true;
    int maxVolume = m_pageManager.size();

    // at DualView Mode, last 2 page shoud be [volume.size()-2, volume.size()-1]
    if(qApp->DualView() && ((m_pageManager.size()-m_pageManager.currentPage()) & 0x1)==0)
        maxVolume--;

    ui->pageSlider->setMaximum(maxVolume);
    ui->pageSlider->setValue(m_pageManager.currentPage()+1);
    m_sliderChanging = false;
    ui->pageSlider->show();

    // StatusBar
    m_pageCaption = m_pageManager.currentPageStatusAsString();
    ui->statusLabel->setText(m_pageCaption);
    if(!qApp->ShowStatusBar())
        setWindowTitle(QString("%1 - %2").arg(m_pageCaption).arg(qApp->applicationName()));
}

void MainWindow::on_volumeChanged_triggered()
{
    qApp->addHistory(m_pageManager.volumePath());

    m_volumeCaption = QString("%1 - %2")
            .arg(m_pageManager.volumePath()).arg(qApp->applicationName());
    setWindowTitle(m_volumeCaption);
    makeHistoryMenu();

}


void MainWindow::on_pageSlider_changed(int value)
{
    //qDebug() << "on_pageSlider_changed " << value << m_sliderChanging;
    if(m_sliderChanging)
        return;
    m_sliderChanging = true;
    m_pageManager.selectPage(value-1);
    m_sliderChanging = false;
}

void MainWindow::on_appVersion_triggered()
{
    QMessageBox msgBox(this);
    msgBox.setWindowTitle(QString("about %1").arg(QApplication::applicationName()));
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setTextFormat(Qt::RichText);
//    msgBox.setText(QApplication::applicationVersion());
    QString message = QString("<h1>%1 %2</h1><p>%3&lt;<a href=\"mailto:k.kanryu@gmail.com\">k.kanryu@gmail.com&gt;</a> All rights reserved.</p>"
                              "<p>Project Webpage: <a href=\"https://kanryu.github.io/quickviewer/\">https://kanryu.github.io/quickviewer/</a></p>"
                              "<p>This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.</p>")
            .arg(QApplication::applicationName())
            .arg(QApplication::applicationVersion())
            .arg(APP_COPYRIGHT);
    msgBox.setText(message);
    msgBox.exec();
}

void MainWindow::on_autoloaded_triggered(bool autoloaded)
{
    qApp->setAutoLoaded(autoloaded);
}

void MainWindow::on_historyMenu_triggered(QAction *action)
{
    //qDebug() << action;
    loadVolume(action->text().mid(4));
}

void MainWindow::on_openfolder_triggered()
{
    QString filter = tr("All Files( *.*);;Images (*.jpg *.jpeg *.png *.tif *.tiff *.ico);;Archives( *.zip *.7z *.rar)");
    QString folder = QFileDialog::getOpenFileName(this, tr("Open a image or archive"), "", filter);
//    QFileDialog dialog = QFileDialog(this, tr("Open a image folder"));
//    if(dialog.exec()) {
    if(folder.length() > 0) {
        //qDebug() << folder;
//        QDir dir(folder);
//        if(dir.exists())
//            loadVolume(folder);
        loadVolume(folder);
    }
}

void MainWindow::on_showToolBar_triggered(bool showToolBar)
{
    if(showToolBar)
        ui->mainToolBar->show();
    else
        ui->mainToolBar->hide();
    qApp->setShowToolBar(showToolBar);
}

void MainWindow::on_showSliderBar_triggered(bool showSliderBar)
{
    if(showSliderBar)
        ui->pageFrame->show();
    else
        ui->pageFrame->hide();
    qApp->setShowSliderBar(showSliderBar);
}

void MainWindow::on_showStatusBar_triggered(bool showStatusBar)
{
    if(showStatusBar) {
        setWindowTitle(m_volumeCaption);
        ui->statusBar->show();
        ui->statusLabel->setText(m_pageCaption);
    } else {
        ui->statusBar->hide();
        setWindowTitle(m_pageCaption);
    }
    qApp->setShowStatusBar(showStatusBar);
}

void MainWindow::on_showMenuBar_triggered(bool showMenuBar)
{
    if(!showMenuBar) {
        QMessageBox msgBox(this);
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        msgBox.setWindowTitle(tr("Confirmation"));
        msgBox.setIcon(QMessageBox::Warning);

        msgBox.setTextFormat(Qt::RichText);
        QString message = QString("<h2>%1</h2>"
                                  "<p>%2</p>")
                .arg(tr("Do you really want to clear the main menu?"))
                .arg(tr("Press F8(default), or Show a context menu on the title bar, <br />and select <strong>'Show/Hide MainMenuBar'</strong>"));
        msgBox.setText(message);
        if(msgBox.exec() == QMessageBox::Cancel) {
            ui->actionShowMenuBar->setChecked(true);
            return;
        }
    }
    if(showMenuBar)
        menuBar()->show();
    else
        menuBar()->hide();
    qApp->setShowMenuBar(showMenuBar);

}

void MainWindow::on_openKeyConfig_triggered()
{
    KeyConfigDialog dialog(this);
    int result = dialog.exec();
    if(result == QDialog::Rejected) {
        dialog.revertKeyChanges();
    }
}

void MainWindow::on_checkVersion_triggered()
{
    QUrl url = QString("https://kanryu.github.io/quickviewer/checkversion/?ver=%1").arg(qApp->applicationVersion());
    QDesktopServices::openUrl(url);
}

void MainWindow::on_exitApplicationOrFullscreen_triggered()
{
    if(isFullScreen())
        ui->actionFullscreen->trigger();
    else
        ui->actionExit->trigger();
}

void MainWindow::on_deletePage_triggered()
{
    if(m_pageManager.currentPageCount() <= 0 || !m_pageManager.isFolder())
        return;
    QString path = m_pageManager.currentPagePath();
    if(!path.length())
        return;
    QMessageBox msgBox(this);
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    msgBox.setWindowTitle(tr("Confirmation"));

    //text
    msgBox.setTextFormat(Qt::RichText);
    QString message = QString("<h2>%1</h2><p>%2</p>" )
            .arg(tr("Are you sure you delete the image?"))
            .arg(path);
    msgBox.setText(message);

    //icon
    QVector<ImageContent> ic = m_pageManager.currentPageContent();
    QImage image = ic[0].Image.toImage();
    image = image.scaled(QSize(100, 100), Qt::KeepAspectRatio);
    msgBox.setIconPixmap(QPixmap::fromImage(image));


    if(msgBox.exec() == QMessageBox::Cancel) {
        return;
    }
    if(moveToTrush(path))  {
        // if deletion successed, reload the volume
        QString volumepath = m_pageManager.volumePath();
        if(m_pageManager.nextPagePathAfterDeleted().length())
            volumepath = m_pageManager.nextPagePathAfterDeleted();
        loadVolume(volumepath);
    }
}

void MainWindow::on_maximizeOrNormal_triggered()
{
    if(isFullScreen()) {
        ui->actionFullscreen->trigger();
    } else if(isMaximized()) {
        showNormal();
    } else {
        showMaximized();
    }
}

void MainWindow::on_restoreWindowState_triggered(bool saveState)
{
    qApp->setRestoreWindowState(saveState);
}

void MainWindow::on_slideShow_triggered(bool enable)
{
    if(m_pageManager.size() == 0)
        return;
    if(!isFullScreen())
        ui->actionFullscreen->trigger();
    ui->graphicsView->toggleSlideShow();
}

void MainWindow::on_shaderNearestNeighbor_triggered()
{
    uncheckAllShaderMenus();
    qApp->setEffect(ShaderManager::NearestNeighbor);
    ui->actionShaderNearestNeighbor->setChecked(true);
    ui->graphicsView->readyForPaint();
}

void MainWindow::on_shaderBilinear_triggered()
{
    uncheckAllShaderMenus();
    ui->actionShaderBilinear->setChecked(true);
    qApp->setEffect(ShaderManager::Bilinear);
    ui->graphicsView->readyForPaint();
}

void MainWindow::on_shaderBicubic_triggered()
{
    uncheckAllShaderMenus();
    qApp->setEffect(ShaderManager::Bicubic);
    ui->actionShaderBicubic->setChecked(true);
    ui->graphicsView->readyForPaint();
}

void MainWindow::on_shaderLanczos_triggered()
{
    uncheckAllShaderMenus();
    qApp->setEffect(ShaderManager::Lanczos);
    ui->actionShaderLanczos->setChecked(true);
    ui->graphicsView->readyForPaint();
}

void MainWindow::on_saveBookmark_triggered()
{
    if(!m_pageManager.currentPageCount())
        return;
    QString path = QDir::fromNativeSeparators(m_pageManager.currentPagePath());
    qApp->addBookMark(path);
    makeBookmarkMenu();
    ui->statusBar->showMessage(tr("Bookmark Saved."));
}

void MainWindow::on_clearBookmarks_triggered()
{
    qApp->clearBookmarks();
    makeBookmarkMenu();
}

void MainWindow::on_loadBookmark_triggered()
{
    QWidget* widget = ui->mainToolBar->widgetForAction(ui->actionLoadBookmark);

    QPoint p = widget->mapToGlobal(QPoint(0, widget->height()));
    ui->menuLoadBookmark->exec(p);
}

void MainWindow::on_loadBookmarkMenu_triggered(QAction *action)
{
    if(action == ui->actionClearBookmarks) {
        return;
    }
    QString path = action->data().toString();
    m_pageManager.loadVolume(path);
}
