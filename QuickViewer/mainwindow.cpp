#include "mainwindow.h"
#include "imageview.h"
#include "ui_mainwindow.h"
#include "filevolumedirectory.h"
#include "qv_init.h"
#include "qvapplication.h"

#include <QDragEnterEvent>
#include <QDropEvent>
#include <QWheelEvent>
#include <QMimeData>
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_sliderChanging(false)
    , m_viewerWindowStateMaximized(false)
    , m_fileVolume(nullptr)
{
    ui->setupUi(this);
    setAcceptDrops(true);
    ui->pageSlider->hide();

    ui->actionFitting->setChecked(qApp->Fitting());
    ui->graphicsView->on_fitting_triggered(qApp->Fitting());

    ui->actionDualView->setChecked(qApp->DualView());
    ui->graphicsView->on_dualView_triggered(qApp->DualView());

    ui->graphicsView->on_rightSideBook_triggered(qApp->RightSideBook());
    ui->actionRightSideBook->setChecked(qApp->RightSideBook());

    ui->actionWideImageAsOneView->setChecked(qApp->WideImageAsOnePageInDualView());

    ui->actionAutoLoaded->setChecked(qApp->AutoLoaded());

    ui->actionShowPageBar->setChecked(qApp->ShowSliderBar());
    on_showSliderBar_triggered(qApp->ShowSliderBar());
    ui->actionShowStatusBar->setChecked(qApp->ShowStatusBar());
    on_showStatusBar_triggered(qApp->ShowStatusBar());

    makeHistoryMenu();

    ui->graphicsView->installEventFilter(this);
    ui->mainToolBar->installEventFilter(this);
    ui->pageFrame->installEventFilter(this);
//    ui->graphicsView->scene()->installEventFilter(this);

    connect(ui->graphicsView, SIGNAL(anchorHovered(Qt::AnchorPoint)), this, SLOT(on_hover_anchor(Qt::AnchorPoint)) );
    connect(ui->graphicsView, SIGNAL(pageChanged()), this, SLOT(on_pageChanged_triggered()) );
    connect(ui->pageSlider, SIGNAL(valueChanged(int)), this, SLOT(on_pageSlider_changed(int)) );
    connect(ui->menuHistory, SIGNAL(triggered(QAction*)), this, SLOT(on_historymenu_triggered(QAction*)) );

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
    if(e->button() == Qt::MiddleButton)
        on_fullscreen_triggered();
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    QKeyEvent *keyEvent = NULL;//event data, if this is a keystroke event
    QMouseEvent *mouseEvent = NULL;//event data, if this is a keystroke event
    QDragEnterEvent  *dragEnterEvent = NULL;//event data, if this is a keystroke event
    QDropEvent *dropEvent = NULL;//event data, if this is a keystroke event
    bool result = false;//return true to consume the keystroke

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
                this->on_nextPage_triggered();
                return true;
            }
            // 5 buttons mouse back for browsers
            if(mouseEvent->button() == Qt::BackButton) {
                this->on_prevPage_triggered();
                return true;
            }
            // tap left/right of window
            if(mouseEvent->button() == Qt::LeftButton) {
                if(ui->graphicsView->hoverState() == Qt::AnchorLeft) {
                    this->on_nextPage_triggered();
                    return true;
                }
                if(ui->graphicsView->hoverState() == Qt::AnchorRight) {
                    this->on_prevPage_triggered();
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
    if(!fv) {
        QMessageBox msgBox(this);
        msgBox.setWindowTitle(tr("open error"));
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText(QApplication::applicationVersion());
        QString message = QString("<h2>%1</h2><p>%2</p>")
                .arg(tr("Can't be opened. Is there no images?"))
                .arg(path);
        msgBox.setText(message);
        msgBox.exec();
        return;
    }
    if(m_fileVolume)
        delete m_fileVolume;
    m_fileVolume = fv;
    ui->graphicsView->setFileVolume(m_fileVolume);
    ui->graphicsView->setIndexedPage(m_fileVolume->pageCount());
    qApp->addHistory(m_fileVolume->volumePath());
    m_volumeCaption = QString("%1 - %2").arg(path).arg(qApp->applicationName());
    setWindowTitle(m_volumeCaption);
    makeHistoryMenu();
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

/**
 * @brief 固定的なホットキーの設定
 */
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()) {
    case Qt::Key_F11: case Qt::Key_Enter: case Qt::Key_Return:
        on_fullscreen_triggered();
        break;
    case Qt::Key_Escape:
        if(isFullScreen())
            on_fullscreen_triggered();
        break;
    case Qt::Key_Left:case Qt::Key_ApplicationLeft:
        on_prevPage_triggered();
        break;
    case Qt::Key_Right:case Qt::Key_ApplicationRight: case Qt::Key_Space:
        on_nextPage_triggered();
        break;
    case Qt::Key_Home:
        on_firstPage_triggered();
        break;
    case Qt::Key_End:
        on_lastPage_triggered();
        break;
    case Qt::Key_Plus:
        ui->graphicsView->on_scaleUp_triggered();
        break;
    case Qt::Key_Minus:
        ui->graphicsView->on_scaleDown_triggered();
        break;
    }
}


void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
    QCoreApplication::quit();
}



void MainWindow::on_file_changed(QString path)
{
    qDebug() << "[MainWindow] newImage:" << path;

}


void MainWindow::on_nextPage_triggered()
{
//    m_fileVolume->nextFile();
    ui->graphicsView->nextPage();
}

void MainWindow::on_prevPage_triggered()
{
//    m_fileVolume->prevFile();
    ui->graphicsView->prevPage();
}

void MainWindow::on_firstPage_triggered()
{
    ui->graphicsView->setIndexedPage(0);
}

void MainWindow::on_lastPage_triggered()
{
    if(m_fileVolume && m_fileVolume->size() > 0)
        ui->graphicsView->setIndexedPage(m_fileVolume->size()-1);
}

void MainWindow::on_fullscreen_triggered()
{

    if(isFullScreen()) {
        if(m_viewerWindowStateMaximized) {
            showMaximized();
        } else {
            showNormal();
        }

        menuBar()->show();
        ui->mainToolBar->show();
        if(qApp->ShowSliderBar())
            ui->pageFrame->show();
        if(qApp->ShowStatusBar())
            statusBar()->show();
        ui->actionFullscreen->setChecked(false);
    } else {
        m_viewerWindowStateMaximized = isMaximized();
        showFullScreen();

        menuBar()->hide();
        ui->mainToolBar->hide();
        ui->pageFrame->hide();
        statusBar()->hide();
        ui->actionFullscreen->setChecked(true);
    }
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
    QString filter = tr("All Files( *.*);;Images (*.jpg *.jpeg *.png *.tif *.tiff *.ico);;Archives( *.zip *.7z)");
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
