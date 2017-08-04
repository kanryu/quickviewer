#include <QtWidgets>


#include "mainwindow.h"
#include "imageview.h"
#include "ui_mainwindow.h"
#include "fileloaderdirectory.h"
#include "qv_init.h"
#include "qvapplication.h"
#include "keyconfigdialog.h"
#include "mouseconfigdialog.h"
#include "optionsdialog.h"
#include "catalogwindow.h"
#include "folderwindow.h"
#include "renamedialog.h"
#include "exifdialog.h"
#include "qnamedpipe.h"
#include "qmousesequence.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_sliderChanging(false)
    , m_viewerWindowStateMaximized(false)
//    , contextMenu(this)
    , m_pageManager(this)
    , m_folderWindow(nullptr)
    , m_catalogWindow(nullptr)
    , m_exifDialog(nullptr)
{
    ui->setupUi(this);

    ui->actionFullscreen->setVisible(false);
    auto fullscreenButton = new QToolButton(this);
    fullscreenButton->setToolTip(tr("&Fullscreen"));
    fullscreenButton->setCheckable(true);
    fullscreenButton->setIcon(QIcon(":/icons/fullscreen"));
    connect(fullscreenButton, SIGNAL(clicked(bool)), this, SLOT(on_fullscreen_triggered()));
    connect(ui->actionFullscreen, SIGNAL(toggled(bool)), fullscreenButton, SLOT(setChecked(bool)));
    ui->menuBar->setCornerWidget(fullscreenButton);

    ui->graphicsView->setPageManager(&m_pageManager);
    setAcceptDrops(true);
    ui->pageSlider->hide();
    //QVApplication* myapp = qApp;

    // Mapping to Key-Action Table and Key Config Dialog
    qApp->registActions(ui);
    resetShortcutKeys();

    // setup checkable menus
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

    ui->actionShowSubfolders->setChecked(qApp->ShowSubfolders());

    ui->actionAutoLoaded->setChecked(qApp->AutoLoaded());

    ui->actionDontEnlargeSmallImagesOnFitting->setChecked(qApp->DontEnlargeSmallImagesOnFitting());
    ui->actionRestoreWindowState->setChecked(qApp->RestoreWindowState());
    ui->actionBeginAsFullscreen->setChecked(qApp->BeginAsFullscreen());
    ui->actionShowFullscreenSignage->setChecked(qApp->ShowFullscreenSignage());
    ui->actionShowFullscreenTitleBar->setChecked(qApp->ShowFullscreenTitleBar());

    // Languages
    qApp->languageSelector()->initializeMenu(ui->menuChange_Language);
    connect(qApp->languageSelector(), SIGNAL(languageChanged(QString)), this, SLOT(on_languageChanged_triggered(QString)));

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
    ui->pageFrame->hide();

    // History
    makeHistoryMenu();
    connect(ui->menuHistory, SIGNAL(triggered(QAction*)), this, SLOT(on_historyMenu_triggered(QAction*)) );

    // Bookmarks
    makeBookmarkMenu();
    ui->actionLoadBookmark->setMenu(ui->menuLoadBookmark);
    connect(ui->menuLoadBookmark, SIGNAL(triggered(QAction*)), this, SLOT(on_loadBookmarkMenu_triggered(QAction*)) );

    // Folders
    ui->actionOpenVolumeWithProgress->setChecked(qApp->OpenVolumeWithProgress());
    ui->actionShowReadProgress->setChecked(qApp->ShowReadProgress());

    // Catalogs
    ui->actionSearchTitleWithOptions->setChecked(qApp->SearchTitleWithOptions());
    ui->actionCatalogTitleWithoutOptions->setChecked(qApp->TitleWithoutOptions());
    ui->actionShowTagBar->setChecked(qApp->ShowTagBar());

    switch(qApp->CatalogViewModeSetting()) {
    case qvEnums::List: ui->actionCatalogViewList->setChecked(true); break;
    case qvEnums::Icon: ui->actionCatalogViewIcon->setChecked(true); break;
    case qvEnums::IconNoText: ui->actionCatalogViewIconNoText->setChecked(true); break;
    }

    ui->statusBar->addPermanentWidget(ui->statusLabel);
    ui->statusLabel->setText(tr("Any folder or archive is not loaded.", "The text of the status bar to be displayed when there is no image to be displayed immediately after the application is activated"));

    // Shader
    m_shaderMenuGroup
            << ui->actionShaderNearestNeighbor
            << ui->actionShaderBilinear
            << ui->actionShaderBicubic
            << ui->actionShaderLanczos
            << ui->actionShaderBilinearBeforeCpuBicubic
            << ui->actionShaderCpuBicubic;
    switch(qApp->Effect()) {
    case qvEnums::NearestNeighbor: ui->actionShaderNearestNeighbor->setChecked(true); break;
    case qvEnums::Bilinear: ui->actionShaderBilinear->setChecked(true); break;
    case qvEnums::Bicubic: ui->actionShaderBicubic->setChecked(true); break;
    case qvEnums::Lanczos: ui->actionShaderLanczos->setChecked(true); break;
    case qvEnums::BilinearAndCpuBicubic:  ui->actionShaderBilinearBeforeCpuBicubic->setChecked(true); break;
    case qvEnums::CpuBicubic: ui->actionShaderCpuBicubic->setChecked(true); break;
    }

    ui->graphicsView->installEventFilter(this);
    ui->mainToolBar->installEventFilter(this);
    ui->pageFrame->installEventFilter(this);

    // Context menus(independent from menuBar)
    ui->menuBar->removeAction(ui->menuContextMenu->menuAction());
    m_contextMenu = ui->menuContextMenu;

    connect(&m_pageManager, SIGNAL(pageChanged()), this, SLOT(on_pageChanged_triggered()));
    connect(&m_pageManager, SIGNAL(volumeChanged(QString)), this, SLOT(on_volumeChanged_triggered(QString)));

    setWindowTitle(QString("%1 v%2").arg(qApp->applicationName()).arg(qApp->applicationVersion()));
    // WindowState Restoreing
    if(qApp->BeginAsFullscreen()) {
        showFullScreen();
    } else if(qApp->RestoreWindowState()) {
        restoreGeometry(qApp->WindowGeometry());
        restoreState(qApp->WindowState());
    }
    if(isFullScreen()) {
        menuBar()->hide();
        ui->mainToolBar->hide();
        ui->pageFrame->hide();
        statusBar()->hide();
        ui->actionFullscreen->setChecked(true);
        ui->graphicsView->setWillFullscreen(true);
        ui->graphicsView->readyForPaint();
    }

    // when drop a folder/archive icon to this app
    if(qApp->arguments().length() >= 2) {
        loadVolume(qApp->arguments().last());
        return;
    }
    // auto restore
    if(qApp->AutoLoaded() && qApp->Bookmarks().size() > 0) {
        QString bookmark = qApp->Bookmarks().takeFirst();
        loadVolume(bookmark);
        makeBookmarkMenu();
    }
}


MainWindow::~MainWindow()
{
    if(qApp->AutoLoaded() && m_pageManager.currentPageCount() > 0) {
        QString path = QDir::fromNativeSeparators(m_pageManager.currentPagePath());
        qApp->addBookMark(path, true);
    }
    delete ui;
    m_pageManager.dispose();
    qApp->saveSettings();
}

void MainWindow::resetShortcutKeys()
{
    QMap<QString, QAction*>& actions = qApp->ActionMapByName();
    foreach(const QString& name, actions.keys()) {
        auto a = actions[name];
        auto seq = qApp->getKey(name);
        a->setShortcut(seq);
    }
}

void MainWindow::dragEnterEvent(QDragEnterEvent *e)
{
    if(e->mimeData()->hasFormat("text/uri-list"))
    {
        e->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent *e)
{
    if(e->mimeData()->hasUrls()) {
        QList<QUrl> urlList = e->mimeData()->urls();
        for (int i = 0; i < 1; i++) {
            QUrl url = urlList[i];
            loadVolume(QDir::toNativeSeparators(url.toLocalFile()));
        }
    }
}
static bool needContextMenu = false;

void MainWindow::wheelEvent(QWheelEvent *e)
{
    int delta = e->delta() < 0 ? -Q_MOUSE_DELTA : e->delta() > 0 ? Q_MOUSE_DELTA : 0;
    QMouseValue mv(QKeySequence(qApp->keyboardModifiers()), e->buttons(), delta);
    QAction* action = qApp->getActionFromMouse(mv);
    if(e->buttons() & Qt::RightButton)
        needContextMenu = false;
    if(action == ui->actionZoomIn || action == ui->actionZoomOut) {
        action->trigger();
        e->accept();
        return;
    }
    if(ui->graphicsView->isScrollMode())
        return;
    action->trigger();
    e->accept();
//    if(e->buttons() & Qt::RightButton || qApp->keyboardModifiers() & Qt::ControlModifier) {
//        if(e->delta() < 0) {
//            ui->actionZoomOut->trigger();
//        }
//        if(e->delta() > 0) {
//            ui->actionZoomIn->trigger();
//        }
//        e->accept();
//        needContextMenu = false;
//        return;
//    }
//    if(ui->graphicsView->isScrollMode())
//        return;
//    if(e->delta() < 0) {
//        ui->actionNextPage->trigger();
//    }
//    if(e->delta() > 0) {
//        ui->actionPrevPage->trigger();
//    }
//    e->accept();
}

//void MainWindow::contextMenuEvent(QContextMenuEvent *e)
//{
//    if(!needContextMenu)
//        return;
//    QWidget *child = childAt(e->pos());
////    qDebug() << child << child->parent();
//    if(child->parent() == ui->graphicsView && m_contextMenu)
//        m_contextMenu->exec(QCursor::pos());
//}

//void MainWindow::mousePressEvent(QMouseEvent *e)
//{
////    needContextMenu = true;
////    QMouseValue mv(QKeySequence(qApp->keyboardModifiers()), e->buttons(), 0);
////    if(mv.Key != "+::LeftButton" && mv.Key != "+::RightButton") {
////        QAction* action = qApp->getActionFromMouse(mv);
////        if(action) {
////            if(action == ui->actionFitting)
////                needContextMenu = false;
////            action->trigger();
////            e->accept();
////        }
////    }

////    if(e->buttons() & Qt::MiddleButton) {
////        if(e->buttons() & Qt::RightButton || qApp->keyboardModifiers() & Qt::ControlModifier) {
////            ui->actionFitting->trigger();
////            needContextMenu = false;
////        } else {
////            on_fullscreen_triggered();
////        }
////        e->accept();
////    }
//    QMainWindow::mousePressEvent(e);
////    if(e->button() == Qt::RightButton) {
////        if(contextMenu)
////            contextMenu->exec(QCursor::pos());
//    //    }
//}


void MainWindow::closeEvent(QCloseEvent *)
{
    on_manageCatalogsClosed_triggered();
    delete m_contextMenu;
    m_contextMenu = nullptr;
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
    case QEvent::MouseButtonDblClick:
        if(obj == ui->graphicsView) {
            mouseEvent = dynamic_cast<QMouseEvent*>(event);
//            // 5 buttons mouse forward for browsers
//            if(mouseEvent->button() == Qt::ForwardButton) {
//                ui->actionNextPage->trigger();
//                return true;
//            }
//            // 5 buttons mouse back for browsers
//            if(mouseEvent->button() == Qt::BackButton) {
//                ui->actionPrevPage->trigger();
//                return true;
//            }
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
            // The ContextMenu event is valid only when RightButton is pushed alone
            // and it is invalidated when the other button is pushed or the wheel moves
            if(mouseEvent->buttons() == Qt::RightButton)
                needContextMenu = true;
            if((mouseEvent->buttons() & Qt::RightButton) && (mouseEvent->buttons() & ~Qt::RightButton))
                needContextMenu = false;
            QMouseValue mv(QKeySequence(qApp->keyboardModifiers()), mouseEvent->buttons(), 0);
            // Processed in ContextMenu event
            if(mv.Key == "+::RightButton")
                break;
            // If isScrollMode () is enabled, priority is given to screen drag scroll
            if(mv.Key == "+::LeftButton" && ui->graphicsView->isScrollMode())
                break;
            QAction* action = qApp->getActionFromMouse(mv);
            if(action) {
                action->trigger();
                return true;
            }
        }
        break;
    // ContextMenu event occurs when releasing the RightButton
    case QEvent::ContextMenu:
        if(obj == ui->graphicsView) {
            QContextMenuEvent *contextMenuEvent = dynamic_cast<QContextMenuEvent*>(event);
//            qDebug() << contextMenuEvent;
            QMouseValue mv(QKeySequence(qApp->keyboardModifiers()), Qt::RightButton, 0);
            QAction* action = qApp->getActionFromMouse(mv);
            if(action && needContextMenu) {
                action->trigger();
                needContextMenu = false;
            }
            return true;
        }
        if(obj == ui->mainToolBar) {
            return true;
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
        if(!isFullScreen() && qApp->ShowSliderBar())
            ui->pageFrame->show();
        return;
    }

    ui->statusLabel->setText(tr("Image file not found. Can't be opened", "Text to display in the status bar when failed to open the specified Volume"));
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

void MainWindow::setThumbnailManager(ThumbnailManager *manager)
{
    m_thumbManager = manager;
}

const static QKeySequence seqReturn("Return");
const static QKeySequence seqEnter("Num+Enter");
/**
 * @brief Support for Customized Shortcut Keys
 */
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    //int key = event->key();
    QKeySequence seq(event->key() | event->modifiers());
//    qDebug() << seq;

    if(this->focusWidget() != ui->graphicsView)
        return;
//    // if the focus is on searchbar on CatalogWindow
//    if(seq == seqReturn || seq == seqEnter) {
//        if(isCatalogSearching()) {
//            return;
//        }
//        if(isFolderSearching()) {
//            m_folderWindow->on_currentItem_triggered();
//            return;
//        }
//    }
    QAction* action = qApp->getActionFromKey(seq);
    if(action)
        action->trigger();
}


void MainWindow::on_exit_triggered()
{
    QApplication::quit();
    QCoreApplication::quit();
}

void MainWindow::on_prohibitMultipleRunning_triggered(bool enable)
{
    qApp->setProhibitMultipleRunning(enable);
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
    ui->graphicsView->readyForPaint();
}

void MainWindow::on_fullscreen_triggered()
{
    qDebug() << "on_fullscreen_triggered";
    if(isFullScreen()) {
        ui->graphicsView->setWillFullscreen(false);
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
        if(ui->graphicsView->isSlideShow())
            ui->graphicsView->toggleSlideShow();
    } else {
        ui->graphicsView->setWillFullscreen(true);
        ui->graphicsView->skipRisizeEvent(true);
        m_viewerWindowStateMaximized = isMaximized();

        menuBar()->hide();
        ui->mainToolBar->hide();
        ui->pageFrame->hide();
        statusBar()->hide();
        ui->actionFullscreen->setChecked(true);
        showFullScreen();
    }
    ui->graphicsView->readyForPaint();
}

void MainWindow::on_stayOnTop_triggered(bool top)
{
    qApp->setStayOnTop(top);
    // Qt's StayOnTop mechanism is not working correctly in Windows.
    // so win32api calling manually
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
}

void MainWindow::on_fittingChanged(bool fitting)
{
    ui->actionFitting->setChecked(fitting);
}

void MainWindow::on_pageChanged_triggered()
{
    //qDebug() << "on_pageChanged_triggered";
    // PageSlider
    ui->pageLabel->setText(m_pageManager.currentPageNumAsString());
    m_sliderChanging = true;
    int maxVolume = m_pageManager.size();

    // at DualView Mode, last 2 page should be [volume.size()-2, volume.size()-1]
    // so the last page should not changed by the slider
    // the logical last page is [volume.size()-2]
    if(qApp->DualView() && ((m_pageManager.size()-m_pageManager.currentPage()) & 0x1)==0)
        maxVolume--;

    ui->pageSlider->setMaximum(maxVolume);
    ui->pageSlider->setValue(m_pageManager.currentPage()+1);
    m_sliderChanging = false;
    ui->pageSlider->show();

    // StatusBar
    m_pageCaption = m_pageManager.currentPageStatusAsString();

    // Elide text(Otherwise the width of the main window will be forcibly changed)
    QFontMetrics fontMetrics(ui->statusLabel->font());
    QString statusLabelTxt = fontMetrics.elidedText(m_pageCaption, Qt::ElideMiddle, width()-100);
    ui->statusLabel->setText(statusLabelTxt);

    if(!qApp->ShowStatusBar())
        setWindowTitle(QString("%1 - %2").arg(m_pageCaption).arg(qApp->applicationName()));

    if(m_exifDialog && m_pageManager.currentPageCount() > 0) {
        const easyexif::EXIFInfo& info = m_pageManager.currentPageContent()[0].Info;
        m_exifDialog->setExif(info);
    }
}

void MainWindow::on_volumeChanged_triggered(QString path)
{
    if(path.isEmpty()) {
        on_pageNolongerNeeded_triggered();
        return;
    }
    qApp->addHistory(path);

    m_volumeCaption = QString("%1 - %2")
            .arg(path).arg(qApp->applicationName());
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

void MainWindow::on_pageNolongerNeeded_triggered()
{
    setWindowTitle(QString("%1 v%2").arg(qApp->applicationName()).arg(qApp->applicationVersion()));
    ui->pageFrame->hide();
    ui->statusLabel->setText(tr("Image file was not found. Can't be opened.", "Text to display in the status bar when failed to open the specified Volume"));
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

void MainWindow::on_languageChanged_triggered(QString language)
{
    qApp->setUiLanguage(language);
    ui->retranslateUi(this);
    ui->menuLoadBookmark->setTitle(QApplication::translate("MainWindow", "LoadBookmark", Q_NULLPTR));
}

void MainWindow::on_registAssocs_triggered()
{
    QProcess::startDetached("AssociateFilesWithQuickViewer",
                            QStringList(),
                            QDir::toNativeSeparators(qApp->applicationDirPath()));
}

void MainWindow::on_contextMenu_triggered()
{
    m_contextMenu->exec(QCursor::pos());
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

#define EXIF_DIALOG_WIDTH 250

void MainWindow::resizeEvent(QResizeEvent *e)
{
    if(m_exifDialog && m_exifDialog->parent()) {
        auto sizes = ui->catalogSplitter->sizes();
        int sum = sizes[0]+sizes[1];
        sizes[1] = EXIF_DIALOG_WIDTH;
        sizes[0] = sum-sizes[1];
        ui->catalogSplitter->setSizes(sizes);
    }
    QMainWindow::resizeEvent(e);
}

void MainWindow::on_folderWindow_triggered()
{
    if(m_folderWindow) {
        bool isChild = m_folderWindow->parent();
        QString oldpath = m_folderWindow->currentPath();
        on_folderWindowClosed_triggered();
        if(isChild) {
            // close child widget, and recreate as independent window
            m_folderWindow = new FolderWindow(nullptr, ui);
            QRect self = geometry();
            m_folderWindow->setGeometry(self.left()-100, self.top()+100, self.width(), self.height());
            m_folderWindow->setAsToplevelWindow();
            m_folderWindow->setFolderPath(oldpath, false);
            connect(m_folderWindow, SIGNAL(closed()), this, SLOT(on_folderWindowClosed_triggered()));
            connect(m_folderWindow, SIGNAL(openVolume(QString)), this, SLOT(on_openVolumeByFolder_triggered(QString)));
            connect(&m_pageManager, SIGNAL(volumeChanged(QString)), m_folderWindow, SLOT(on_volumeChanged_triggered(QString)));
            m_folderWindow->show();
        }
        return;
    }
    if(m_catalogWindow && m_catalogWindow->parent())
        on_manageCatalogsClosed_triggered();
    if(m_exifDialog && m_exifDialog->parent())
        on_openExifDialogClosed_triggered();
    m_folderWindow = new FolderWindow(nullptr, ui);
    QString path = m_pageManager.volumePath();
    if(path.isEmpty())
        path = qApp->HomeFolderPath();
    m_folderWindow->setFolderPath(path, false);
    connect(m_folderWindow, SIGNAL(closed()), this, SLOT(on_folderWindowClosed_triggered()));
    connect(m_folderWindow, SIGNAL(openVolume(QString)), this, SLOT(on_openVolumeByFolder_triggered(QString)));
    connect(&m_pageManager, SIGNAL(volumeChanged(QString)), m_folderWindow, SLOT(on_volumeChanged_triggered(QString)));
    ui->catalogSplitter->insertWidget(0, m_folderWindow);
    auto sizes = ui->catalogSplitter->sizes();
    int sum = sizes[0]+sizes[1];
    sizes[0] = 200;
    sizes[1] = sum-sizes[0];
    ui->catalogSplitter->setSizes(sizes);
    m_folderWindow->setAsInnerWidget();
}

void MainWindow::on_folderWindowClosed_triggered()
{
    if(m_folderWindow) {
        delete m_folderWindow;
        m_folderWindow = nullptr;
    }
}

void MainWindow::on_openVolumeByFolder_triggered(QString path)
{
    loadVolume(path);
}


void MainWindow::on_openVolumeWithProgress_triggered(bool enabled)
{
    qApp->setOpenVolumeWithProgress(enabled);
}

void MainWindow::on_showReadProgress_triggered(bool enabled)
{
    qApp->setShowReadProgress(enabled);
    if(m_folderWindow) {
        m_folderWindow->reset();
    }
}

void MainWindow::on_manageCatalogs_triggered()
{
    if(m_catalogWindow) {
        bool isChild = m_catalogWindow->parent();
        on_manageCatalogsClosed_triggered();
        if(isChild) {
            m_catalogWindow = new CatalogWindow(nullptr, ui);
            m_catalogWindow->setThumbnailManager(m_thumbManager);
            connect(m_catalogWindow, SIGNAL(closed()), this, SLOT(on_manageCatalogsClosed_triggered()));
            connect(m_catalogWindow, SIGNAL(openVolume(QString)), this, SLOT(on_openVolumeByCatalog_triggered(QString)));
            m_catalogWindow->setAsToplevelWindow();
            QRect self = geometry();
            m_catalogWindow->setGeometry(self.left()-100, self.top()+100, self.width(), self.height());
            m_catalogWindow->show();
        }
        return;
    }
    if(m_folderWindow && m_folderWindow->parent())
        on_folderWindowClosed_triggered();
    if(m_exifDialog && m_exifDialog->parent())
        on_openExifDialogClosed_triggered();
    m_catalogWindow = new CatalogWindow(nullptr, ui);
    m_catalogWindow->setThumbnailManager(m_thumbManager);
    connect(m_catalogWindow, SIGNAL(closed()), this, SLOT(on_manageCatalogsClosed_triggered()));
    connect(m_catalogWindow, SIGNAL(openVolume(QString)), this, SLOT(on_openVolumeByCatalog_triggered(QString)));
    ui->catalogSplitter->insertWidget(0, m_catalogWindow);
    auto sizes = ui->catalogSplitter->sizes();
    int sum = sizes[0]+sizes[1];
    sizes[0] = 200;
    sizes[1] = sum-sizes[0];
    ui->catalogSplitter->setSizes(sizes);
    m_catalogWindow->setAsInnerWidget();
//    m_catalogWindow->resize(180, m_catalogWindow->height());
//    m_catalogWindow->show();
}

void MainWindow::on_manageCatalogsClosed_triggered()
{
    if(m_catalogWindow) {
        delete m_catalogWindow;
        m_catalogWindow = nullptr;
    }
}

bool MainWindow::isCatalogSearching()
{
    if(!m_catalogWindow || !m_catalogWindow->parent())
        return false;
    return m_catalogWindow->isCatalogSearching();
}

bool MainWindow::isFolderSearching()
{
    if(!m_folderWindow || !m_folderWindow->parent())
        return false;
    return true;
}

void MainWindow::on_openExifDialog_triggered()
{
    if(m_exifDialog || m_pageManager.currentPageCount()==0)
        return;
    const easyexif::EXIFInfo& info = m_pageManager.currentPageContent()[0].Info;
    if(info.ImageWidth == 0)
        return;
    if(m_catalogWindow && m_catalogWindow->parent())
        on_manageCatalogsClosed_triggered();
    if(m_folderWindow && m_folderWindow->parent())
        on_folderWindowClosed_triggered();

    m_exifDialog = new ExifDialog();
    m_exifDialog->setExif(info);
    connect(m_exifDialog, SIGNAL(closed()), this, SLOT(on_openExifDialogClosed_triggered()));

    ui->catalogSplitter->insertWidget(1, m_exifDialog);
    auto sizes = ui->catalogSplitter->sizes();
    int sum = sizes[0]+sizes[1];
    sizes[1] = EXIF_DIALOG_WIDTH;
    sizes[0] = sum-sizes[1];
    ui->catalogSplitter->setSizes(sizes);
}

void MainWindow::on_openExifDialogClosed_triggered()
{
    if(m_exifDialog) {
        delete m_exifDialog;
        m_exifDialog = nullptr;
    }
}


void MainWindow::on_openVolumeByCatalog_triggered(QString path)
{
    loadVolume(path);
    setWindowTop();
}

void MainWindow::on_windowTop()
{
    setWindowTop();
}

void MainWindow::on_searchTitleWithOptions_triggered(bool enable)
{
    qApp->setSearchTitleWithOptions(enable);
    if(m_catalogWindow)
        m_catalogWindow->resetVolumes();
}

void MainWindow::on_catalogTitleWithoutOptions_triggered(bool enable)
{
    qApp->setTitleWithoutOptions(enable);
    if(m_catalogWindow)
        m_catalogWindow->searchByWord(true);
}

void MainWindow::on_catalogViewList_triggered()
{
    qApp->setCatalogViewModeSetting(qvEnums::List);
    ui->actionCatalogViewList->setChecked(true);
    ui->actionCatalogViewIcon->setChecked(false);
    ui->actionCatalogViewIconNoText->setChecked(false);
    if(m_catalogWindow)
        m_catalogWindow->resetVolumes();
}

void MainWindow::on_catalogViewIcon_triggered()
{
    qApp->setCatalogViewModeSetting(qvEnums::Icon);
    ui->actionCatalogViewList->setChecked(false);
    ui->actionCatalogViewIcon->setChecked(true);
    ui->actionCatalogViewIconNoText->setChecked(false);
    if(m_catalogWindow)
        m_catalogWindow->resetVolumes();
}

void MainWindow::on_catalogViewNotext_triggered()
{
    qApp->setCatalogViewModeSetting(qvEnums::IconNoText);
    ui->actionCatalogViewList->setChecked(false);
    ui->actionCatalogViewIcon->setChecked(false);
    ui->actionCatalogViewIconNoText->setChecked(true);
    if(m_catalogWindow)
        m_catalogWindow->resetVolumes();
}

void MainWindow::on_catalogShowTagBar_triggered(bool enable)
{
    qApp->setShowTagBar(enable);
    if(m_catalogWindow)
        m_catalogWindow->on_showTagBar_triggered(enable);
}

void MainWindow::on_catalogIconLongText_triggered(bool enable)
{
    qApp->setIconLongText(enable);
    if(m_catalogWindow)
        m_catalogWindow->resetViewMode();
}

void MainWindow::on_openfolder_triggered()
{
    QString filter = tr("All Files( *.*);;Images (*.jpg *.jpeg *.png *.tif *.tiff *.ico);;Archives( *.zip *.7z *.rar)", "Text that specifies the file extension to be displayed when opening a file with OpenFileFolder");
    QString folder = QFileDialog::getOpenFileName(this, tr("Please select the image or archive", "Title of the dialog displayed when opening a file with OpenFileFolder"), "", filter);
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
//    if(!showMenuBar) {
//        QMessageBox msgBox(this);
//        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
//        msgBox.setDefaultButton(QMessageBox::Cancel);
//        msgBox.setWindowTitle(tr("Confirmation"));
//        msgBox.setIcon(QMessageBox::Warning);

//        msgBox.setTextFormat(Qt::RichText);
//        QString message = QString("<h2>%1</h2>"
//                                  "<p>%2</p>")
//                .arg(tr("Do you really want to hide the main menu?", "Message confirming to hide the main menu"))
//                .arg(tr("Press F8(default), or Show a context menu on the title bar, <br />and select <strong>'Show/Hide MainMenuBar'</strong>", "Message confirming to hide the main menu"));
//        msgBox.setText(message);
//        if(msgBox.exec() == QMessageBox::Cancel) {
//            ui->actionShowMenuBar->setChecked(true);
//            return;
//        }
//    }
    if(showMenuBar) {
        if(qApp->ShowToolBar()) ui->mainToolBar->hide();
        menuBar()->show();
        if(qApp->ShowToolBar()) ui->mainToolBar->show();
    }
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
    } else {
        resetShortcutKeys();
    }
}

void MainWindow::on_openMouseConfig_triggered()
{
    MouseConfigDialog dialog(this);
    int result = dialog.exec();
    if(result == QDialog::Rejected) {
        dialog.revertMouseChanges();
    }
}

void MainWindow::on_openOptionsDialog_triggered()
{
    OptionsDialog dialog(this);
    QColor back = qApp->BackgroundColor();
    QColor back2 = qApp->BackgroundColor2();
    bool checkered = qApp->UseCheckeredPattern();
    if(dialog.exec() == QDialog::Accepted) {
        dialog.reflectResults();
        if(back != qApp->BackgroundColor()
           || back2 != qApp->BackgroundColor2()
           || checkered != qApp->UseCheckeredPattern()) {
            ui->graphicsView->resetBackgroundColor();
        }
    }
}

void MainWindow::on_beginAsFullscreen_triggered(bool enable)
{
    qApp->setBeginAsFullscreen(enable);
}

void MainWindow::on_showFullscreenSignage_triggered(bool enable)
{
    qApp->setShowFullscreenSignage(enable);
}

void MainWindow::on_showFullscreenTitleBar_triggered(bool enable)
{
    qApp->setShowFullscreenTitleBar(enable);
}

void MainWindow::on_projectPage_triggered()
{
    QUrl url = QString("https://kanryu.github.io/quickviewer/");
    QDesktopServices::openUrl(url);
}

void MainWindow::on_checkVersion_triggered()
{
    QUrl url = QString("https://kanryu.github.io/quickviewer/checkversion/?ver=%1").arg(qApp->applicationVersion());
    QDesktopServices::openUrl(url);
}

void MainWindow::on_exitApplicationOrFullscreen_triggered()
{
    if(m_catalogWindow) {
        on_manageCatalogsClosed_triggered();
        return;
    }
    if(isFullScreen())
        ui->actionFullscreen->trigger();
    else
        ui->actionExit->trigger();
}

void MainWindow::on_mailAttachment_triggered()
{
    if(m_pageManager.isArchive())
        return;
    QString path = m_pageManager.currentPagePath();
    if(!path.length())
        return;
    setMailAttachment(path);
}

void MainWindow::on_renameImageFile_triggered()
{
    if(!m_pageManager.isFolder() || m_pageManager.currentPageCount() == 0)
        return;
    RenameDialog dialog(this, m_pageManager.realVolumePath(), m_pageManager.currentPageName());
    if(dialog.exec() == QDialog::Accepted) {
        m_pageManager.loadVolume(QDir(m_pageManager.realVolumePath()).absoluteFilePath(dialog.newName()));
    }
}

void MainWindow::on_confirmDeletePage_triggered(bool enable)
{
    qApp->setConfirmDeletePage(enable);
}

void MainWindow::on_deletePage_triggered()
{
    if(m_pageManager.currentPageCount() <= 0 || !m_pageManager.isFolder())
        return;
    QString path = m_pageManager.currentPagePath();
    if(!path.length())
        return;
    if(qApp->ConfirmDeletePage()) {
        QMessageBox msgBox(this);
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        msgBox.setWindowTitle(tr("Confirmation", "Confirm putting displayed file in Recycle Box MessageBox title"));

        //text
        msgBox.setTextFormat(Qt::RichText);
        QString message = QString("<h2>%1</h2><p>%2</p>" )
                .arg(tr("Are you sure you want to delete this image?", "Confirm putting displayed file in Recycle Box Message Box body"))
                .arg(path);
        msgBox.setText(message);

        //icon
        QVector<ImageContent> ic = m_pageManager.currentPageContent();
        QImage image = ic[0].Image;
        image = image.scaled(QSize(100, 100), Qt::KeepAspectRatio);
        msgBox.setIconPixmap(QPixmap::fromImage(image));


        if(msgBox.exec() == QMessageBox::Cancel) {
            return;
        }
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

void MainWindow::on_slideShow_triggered(bool )
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
    qApp->setEffect(qvEnums::NearestNeighbor);
    ui->actionShaderNearestNeighbor->setChecked(true);
    ui->graphicsView->readyForPaint();
}

void MainWindow::on_shaderBilinear_triggered()
{
    uncheckAllShaderMenus();
    ui->actionShaderBilinear->setChecked(true);
    qApp->setEffect(qvEnums::Bilinear);
    ui->graphicsView->readyForPaint();
}

void MainWindow::on_shaderBicubic_triggered()
{
    uncheckAllShaderMenus();
    qApp->setEffect(qvEnums::Bicubic);
    ui->actionShaderBicubic->setChecked(true);
    ui->graphicsView->readyForPaint();
}

void MainWindow::on_shaderLanczos_triggered()
{
    uncheckAllShaderMenus();
    qApp->setEffect(qvEnums::Lanczos);
    ui->actionShaderLanczos->setChecked(true);
    ui->graphicsView->readyForPaint();
}

void MainWindow::on_shaderBilinearBeforeCpuBicubic_triggered()
{
    uncheckAllShaderMenus();
    qApp->setEffect(qvEnums::BilinearAndCpuBicubic);
    ui->actionShaderBilinearBeforeCpuBicubic->setChecked(true);
    ui->graphicsView->readyForPaint();
}

void MainWindow::on_shaderCpuBicubic_triggered()
{
    uncheckAllShaderMenus();
    qApp->setEffect(qvEnums::CpuBicubic);
    ui->actionShaderCpuBicubic->setChecked(true);
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
    m_pageManager.loadVolume(QDir::toNativeSeparators(path));
}

void MainWindow::on_messageReceived(QString data)
{
    qDebug() << "on_messageReceived: " << data;
}
