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
    , m_fileVolume(nullptr)
    , contextMenu(this)
{
    ui->setupUi(this);
    setAcceptDrops(true);
    ui->pageSlider->hide();

    // Mapping to Key-Action Table and Key Config Dialog
    qApp->registAction("actionExit", ui->actionExit);
    qApp->registAction("actionClearHistory", ui->actionClearHistory);
    qApp->registAction("actionExitApplicationOrFullscreen", ui->actionExitApplicationOrFullscreen);
    qApp->registAction("actionNextPage", ui->actionNextPage);
    qApp->registAction("actionPrevPage", ui->actionPrevPage);
    qApp->registAction("actionScaleUp", ui->actionScaleUp);
    qApp->registAction("actionScaleDown", ui->actionScaleDown);
    qApp->registAction("actionFitting", ui->actionFitting);
    qApp->registAction("actionDualView", ui->actionDualView);
    qApp->registAction("actionFullscreen", ui->actionFullscreen);
    qApp->registAction("actionStayOnTop", ui->actionStayOnTop);
    qApp->registAction("actionAppVersion", ui->actionAppVersion);
    qApp->registAction("actionAutoLoaded", ui->actionAutoLoaded);
    qApp->registAction("actionRightSideBook", ui->actionRightSideBook);
    qApp->registAction("actionOpenFolder", ui->actionOpenFolder);
    qApp->registAction("actionWideImageAsOneView", ui->actionWideImageAsOneView);
    qApp->registAction("actionFirstImageAsOneView", ui->actionFirstImageAsOneView);
    qApp->registAction("actionLastPage", ui->actionLastPage);
    qApp->registAction("actionFirstPage", ui->actionFirstPage);
    qApp->registAction("actionShowToolBar", ui->actionShowToolBar);
    qApp->registAction("actionShowStatusBar", ui->actionShowStatusBar);
    qApp->registAction("actionShowPageBar", ui->actionShowPageBar);
    qApp->registAction("actionShowMenuBar", ui->actionShowMenuBar);
    qApp->registAction("actionOpenFiler", ui->actionOpenFiler);
    qApp->registAction("actionOpenExif", ui->actionOpenExif);
    qApp->registAction("actionOpenKeyConfig", ui->actionOpenKeyConfig);
    qApp->registAction("actionCheckVersion", ui->actionCheckVersion);
    qApp->registAction("actionNextVolume", ui->actionNextVolume);
    qApp->registAction("actionPrevVolume", ui->actionPrevVolume);
    qApp->registAction("actionNextOnePage", ui->actionNextOnePage);
    qApp->registAction("actionPrevOnePage", ui->actionPrevOnePage);


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

    ui->actionShowToolBar->setChecked(qApp->ShowToolBar());
    ui->actionShowToolBar->triggered(qApp->ShowToolBar());
    ui->actionShowPageBar->setChecked(qApp->ShowSliderBar());
    ui->actionShowPageBar->triggered(qApp->ShowSliderBar());
    ui->actionShowStatusBar->setChecked(qApp->ShowStatusBar());
    ui->actionShowStatusBar->triggered(qApp->ShowStatusBar());
    ui->actionShowMenuBar->setChecked(qApp->ShowMenuBar());
    if(!qApp->ShowMenuBar())
        menuBar()->hide();

    makeHistoryMenu();

    ui->graphicsView->installEventFilter(this);
    ui->mainToolBar->installEventFilter(this);
    ui->pageFrame->installEventFilter(this);
//    ui->graphicsView->scene()->installEventFilter(this);

    // Context menus
    contextMenu.addAction(ui->actionNextOnePage);
    contextMenu.addAction(ui->actionPrevOnePage);
    contextMenu.addSeparator();
    contextMenu.addAction(ui->actionOpenFiler);
    contextMenu.addAction(ui->actionOpenExif);
    contextMenu.addSeparator();
    contextMenu.addAction(ui->actionWideImageAsOneView);
    contextMenu.addAction(ui->actionFirstImageAsOneView);

    connect(ui->graphicsView, SIGNAL(anchorHovered(Qt::AnchorPoint)), this, SLOT(on_hover_anchor(Qt::AnchorPoint)) );
    connect(ui->graphicsView, SIGNAL(pageChanged()), this, SLOT(on_pageChanged_triggered()) );
    connect(ui->pageSlider, SIGNAL(valueChanged(int)), this, SLOT(on_pageSlider_changed(int)) );
    connect(ui->menuHistory, SIGNAL(triggered(QAction*)), this, SLOT(on_historymenu_triggered(QAction*)) );

    setWindowTitle(QString("%1 v%2").arg(qApp->applicationName()).arg(qApp->applicationVersion()));
    QVApplication* myapp = qApp;
    QStringList args = qApp->arguments();
    qDebug() << args;
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
    if(m_fileVolume)
        delete m_fileVolume;
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
        ui->graphicsView->nextPage();
    }
    if(e->delta() > 0) {
        ui->graphicsView->prevPage();
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
    IFileVolume* fv = IFileVolume::CreateVolume(this, path);
    if(fv) {
        resetVolume(fv);
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

void MainWindow::resetVolume(IFileVolume *newer)
{
    if(m_fileVolume)
        delete m_fileVolume;
    m_fileVolume = newer;
    ui->graphicsView->setFileVolume(m_fileVolume);
    ui->graphicsView->setIndexedPage(m_fileVolume->pageCount());
    qApp->addHistory(m_fileVolume->volumePath());
    m_volumeCaption = QString("%1 - %2").arg(m_fileVolume->volumePath()).arg(qApp->applicationName());
    setWindowTitle(m_volumeCaption);
    makeHistoryMenu();
}

/**
 * @brief 固定的なホットキーの設定
 */
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    QKeySequence seq(event->key() | event->modifiers());
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
    qDebug() << "[MainWindow] newImage:" << path;

}

void MainWindow::on_clearHistory_triggered()
{
    qApp->clearHistory();
    makeHistoryMenu();
}


//void MainWindow::on_nextPage_triggered()
//{
////    m_fileVolume->nextFile();
//    ui->graphicsView->nextPage();
//}

//void MainWindow::on_prevPage_triggered()
//{
////    m_fileVolume->prevFile();
//    ui->graphicsView->prevPage();
//}

//void MainWindow::on_firstPage_triggered()
//{
//    ui->graphicsView->setIndexedPage(0);
//}

//void MainWindow::on_lastPage_triggered()
//{
//    if(m_fileVolume && m_fileVolume->size() > 0)
//        ui->graphicsView->setIndexedPage(m_fileVolume->size()-1);
//}

//void MainWindow::on_nextOnlyOnePage_triggered()
//{

//}

//void MainWindow::on_prevOnlyOnePage_triggered()
//{

//}

void MainWindow::on_nextVolume_triggered()
{
    if(!m_fileVolume)
        return;
    QDir dir(m_fileVolume->volumePath());
    QString current = dir.absolutePath();
    if(!dir.cdUp())
        return;
    foreach (const QString& name, dir.entryList(QDir::Dirs | QDir::Files, QDir::Name)) {
        QString path = dir.filePath(name);
        if(path <= current)
            continue;
        IFileVolume* fv = IFileVolume::CreateVolumeWithOnlyCover(this, path);
        if(fv) {
            resetVolume(fv);
            fv->setSuppressCache(false);
            return;
        }
    }
}

void MainWindow::on_prevVolume_triggered()
{
    if(!m_fileVolume)
        return;
    QDir dir(m_fileVolume->volumePath());
    QString current = dir.absolutePath();
    if(!dir.cdUp())
        return;
    QStringList list = dir.entryList(QDir::Dirs | QDir::Files, QDir::Name);
    QListIterator<QString> it(list);it.toBack();
    while(it.hasPrevious()) {
        QString path = dir.filePath(it.previous());
        if(path >= current)
            continue;
        IFileVolume* fv = IFileVolume::CreateVolumeWithOnlyCover(this, path);
        if(fv) {
            resetVolume(fv);
            fv->setSuppressCache(false);
            return;
        }
    }
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
    Qt::WindowFlags flags = windowFlags();
    if(top) {
        flags |= Qt::WindowStaysOnTopHint;
    } else {
        flags &= ~Qt::WindowStaysOnTopHint;
    }
    setWindowFlags(flags);
    show();
    setParent(nullptr);
    qApp->setStayOnTop(top);
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
    qDebug() << "on_pageChanged_triggered";
    // PageSlider
    QString pagestr = QString("(%1)").arg(ui->graphicsView->currentPageAsString());
    ui->pageLabel->setText(pagestr);
    m_sliderChanging = true;
    ui->pageSlider->setMaximum(m_fileVolume->size());
    int currentPage = ui->graphicsView->currentPage();
    ui->pageSlider->setValue(currentPage);
    m_sliderChanging = false;
    ui->pageSlider->show();

    // StatusBar
    int pages = ui->graphicsView->currentPageCount();
    QString status;
    if(pages == 1) {
        const ImageContent ic1 = m_fileVolume->getIndexedImageContent(ui->graphicsView->currentPage()-1);
        status = QString("%1 %2[%3x%4]")
                    .arg(ic1.Path)
                    .arg(pagestr)
                    .arg(ic1.BaseSize.width()).arg(ic1.BaseSize.height());
    } else {
        const ImageContent ic1 = m_fileVolume->getIndexedImageContent(ui->graphicsView->currentPage()-1);
        const ImageContent ic2 = m_fileVolume->getIndexedImageContent(ui->graphicsView->currentPage());
        status = QString("%1 %2[%3x%4] | %5 [%6x%7]")
                    .arg(ic1.Path)
                    .arg(pagestr)
                    .arg(ic1.BaseSize.width()).arg(ic1.BaseSize.height())
                    .arg(ic2.Path)
                    .arg(ic2.BaseSize.width()).arg(ic2.BaseSize.height());
    }
    ui->statusBar->showMessage(status);
    m_pageCaption = QString("%1 - %2").arg(status).arg(qApp->applicationName());
    if(!qApp->ShowStatusBar())
        setWindowTitle(m_pageCaption);
}


void MainWindow::on_pageSlider_changed(int value)
{
    qDebug() << "on_pageSlider_changed " << value << m_sliderChanging;
    if(m_sliderChanging)
        return;
    m_sliderChanging = true;
    ui->graphicsView->setIndexedPage(value-1);
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

void MainWindow::on_historymenu_triggered(QAction *action)
{
    qDebug() << action;
    loadVolume(action->text().mid(4));
}

void MainWindow::on_openfolder_triggered()
{
    QString filter = tr("All Files( *.*);;Images (*.jpg *.jpeg *.png *.tif *.tiff *.ico);;Archives( *.zip *.7z *.rar)");
    QString folder = QFileDialog::getOpenFileName(this, tr("Open a image or archive"), "", filter);
//    QFileDialog dialog = QFileDialog(this, tr("Open a image folder"));
//    if(dialog.exec()) {
    if(folder.length() > 0) {
        qDebug() << folder;
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
        ui->statusBar->showMessage(m_pageCaption);
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
