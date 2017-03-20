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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
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

    ui->actionAutoLoaded->setChecked(qApp->AutoLoaded());
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

    if(obj == ui->graphicsView) {
        qDebug() << "graphicsView <= " << event->type();
    } else {
        qDebug() << obj << " <= " << event->type();
    }

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
    if(fv) {
        m_fileVolume = fv;
        ui->graphicsView->setFileVolume(m_fileVolume);
        ui->graphicsView->setIndexedPage(0);
        qApp->addHistory(path);

        setWindowTitle(QString("%1 - %2").arg(path).arg(qApp->applicationName()));
        makeHistoryMenu();
    }
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
    case Qt::Key_F11:
        on_fullscreen_triggered();
        break;
    case Qt::Key_Escape:
        if(isFullScreen())
            on_fullscreen_triggered();
        break;
    case Qt::Key_Left:case Qt::Key_ApplicationLeft:
        on_prevPage_triggered();
        break;
    case Qt::Key_Right:case Qt::Key_ApplicationRight:
        on_nextPage_triggered();
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

void MainWindow::on_fullscreen_triggered()
{

    if(isFullScreen()) {
        if(viewerWindowStateMaximized) {
            showMaximized();
        } else {
            showNormal();
        }

        menuBar()->show();
        ui->mainToolBar->show();
        ui->pageFrame->show();
//        statusBar()->show();
        ui->actionFullscreen->setChecked(false);
    } else {
        viewerWindowStateMaximized = isMaximized();
        showFullScreen();

        menuBar()->hide();
        ui->mainToolBar->hide();
        ui->pageFrame->hide();
//        statusBar()->hide();
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
    ui->pageLabel->setText(QString("(%1)").arg(ui->graphicsView->currentPageAsString()));
    ui->pageSlider->setMaximum(m_fileVolume->size());
    ui->pageSlider->setValue(ui->graphicsView->currentPage());
    ui->pageSlider->show();
}


void MainWindow::on_pageSlider_changed(int value)
{
    static bool sliderChanging = false;
    qDebug() << "on_pageSlider_changed " << value << sliderChanging;
    if(sliderChanging)
        return;
    sliderChanging = true;
    ui->graphicsView->setIndexedPage(value-1);
    sliderChanging = false;
}

void MainWindow::on_appVersion_triggered()
{
    QMessageBox msgBox(this);
    msgBox.setWindowTitle(QString("about %1").arg(QApplication::applicationName()));
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setTextFormat(Qt::RichText);
//    msgBox.setText(QApplication::applicationVersion());
    QString message = QString("<h1>%1 %2</h1><p>%3 All rights reserved.</p>"
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
