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
#include "fileloader.h"
#include "qinnerframe.h"

#ifdef Q_OS_WIN
#include "fileassocdialog.h"
#endif

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
    m_menubarFontSize = ui->menuBar->font().pointSize();
	m_pageSliderHeight = ui->pageSlider->height();
    m_imageString.initialize(&m_pageManager, ui->graphicsView);

#ifndef Q_OS_WIN
    ui->actionRegistAssocsUAC->setVisible(false);
    ui->actionRegistAssocs->setVisible(false);
#endif

	m_fullscreenButton = new QToolButton(this);
    m_fullscreenButton->setToolTip(tr("&Fullscreen"));
    m_fullscreenButton->setCheckable(true);
    m_fullscreenButton->setIcon(QIcon(":/icons/fullscreen"));
    connect(m_fullscreenButton, SIGNAL(clicked(bool)), this, SLOT(onActionFullscreen_triggered()));
    connect(ui->actionFullscreen, SIGNAL(toggled(bool)), m_fullscreenButton, SLOT(setChecked(bool)));
    ui->menuBar->setCornerWidget(m_fullscreenButton);

    ui->graphicsView->setPageManager(&m_pageManager);
    setAcceptDrops(true);

    // Mapping to Key-Action Table and Key Config Dialog
    qApp->registActions(ui);
    resetShortcutKeys();

    // Context menus(independent from menuBar)
    ui->menuBar->removeAction(ui->menuContextMenu->menuAction());
    m_contextMenu = ui->menuContextMenu;

    // setup checkable menus
    ui->actionFitting->setChecked(qApp->Fitting());
    ui->graphicsView->on_fitting_triggered(qApp->Fitting());
    ui->actionFitToWidth->setChecked(qApp->FitToWidth());
    ui->graphicsView->on_fitToWidth_triggered(qApp->FitToWidth());

    ui->actionDualView->setChecked(qApp->DualView());
    ui->graphicsView->on_dualView_triggered(qApp->DualView());

    ui->actionStayOnTop->setChecked(qApp->StayOnTop());
    ui->actionStayOnTop->triggered(qApp->StayOnTop());

    ui->actionLargeToolbarIcons->setChecked(qApp->LargeToolbarIcons());
    ui->actionLargeToolbarIcons->triggered(qApp->LargeToolbarIcons());

    ui->graphicsView->on_rightSideBook_triggered(qApp->RightSideBook());
    ui->actionRightSideBook->setChecked(qApp->RightSideBook());
    ui->actionLoupeTool->setChecked(qApp->LoupeTool());
    ui->actionScrollWithCursorWhenZooming->setChecked(qApp->ScrollWithCursorWhenZooming());

    ui->actionWideImageAsOneView->setChecked(qApp->WideImageAsOnePageInDualView());
    ui->actionFirstImageAsOneView->setChecked(qApp->FirstImageAsOnePageInDualView());
    ui->actionSeparatePagesWhenWideImage->setChecked(qApp->SeparatePagesWhenWideImage());

    ui->actionShowSubfolders->setChecked(qApp->ShowSubfolders());

    ui->actionAutoLoaded->setChecked(qApp->AutoLoaded());
    ui->actionSavingHistory->setChecked(qApp->DontSavingHistory());

    ui->actionDontEnlargeSmallImagesOnFitting->setChecked(qApp->DontEnlargeSmallImagesOnFitting());
    ui->actionRestoreWindowState->setChecked(qApp->RestoreWindowState());
    ui->actionBeginAsFullscreen->setChecked(qApp->BeginAsFullscreen());
    ui->actionShowFullscreenSignage->setChecked(qApp->ShowFullscreenSignage());
    ui->actionShowPanelSeparateWindow->setChecked(qApp->ShowPanelSeparateWindow());
//    ui->actionShowFullscreenTitleBar->setChecked(qApp->ShowFullscreenTitleBar());

    // Languages
    qApp->languageSelector()->initializeMenu(ui->menuChange_Language);
    connect(qApp->languageSelector(), SIGNAL(languageChanged(QString)), this, SLOT(onLanguageSelector_languageChanged(QString)));

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
    connect(ui->menuHistory, SIGNAL(triggered(QAction*)), this, SLOT(onMenuHistory_triggered(QAction*)) );

    // Bookmarks
    makeBookmarkMenu();
    ui->actionLoadBookmark->setMenu(ui->menuLoadBookmark);
    connect(ui->menuLoadBookmark, SIGNAL(triggered(QAction*)), this, SLOT(onMenuLoadBookmark_triggered(QAction*)) );

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
#ifdef QV_WITHOUT_OPENGL
    ui->actionShaderBicubic->setVisible(false);
    ui->actionShaderLanczos->setVisible(false);
#endif
    m_shaderMenuGroup
            << ui->actionShaderNearestNeighbor
            << ui->actionShaderBilinear
           #ifndef QV_WITHOUT_OPENGL
            << ui->actionShaderBicubic
            << ui->actionShaderLanczos
           #endif
            << ui->actionShaderBilinearBeforeCpuBicubic
            << ui->actionShaderCpuBicubic;
    switch(qApp->Effect()) {
    case qvEnums::NearestNeighbor: ui->actionShaderNearestNeighbor->setChecked(true); break;
    case qvEnums::Bilinear: ui->actionShaderBilinear->setChecked(true); break;
#ifndef QV_WITHOUT_OPENGL
    case qvEnums::Bicubic: ui->actionShaderBicubic->setChecked(true); break;
    case qvEnums::Lanczos: ui->actionShaderLanczos->setChecked(true); break;
#endif
    case qvEnums::BilinearAndCpuBicubic:  ui->actionShaderBilinearBeforeCpuBicubic->setChecked(true); break;
    case qvEnums::CpuBicubic: ui->actionShaderCpuBicubic->setChecked(true); break;
    default: break;
    }

    ui->graphicsView->installEventFilter(this);
    ui->mainToolBar->installEventFilter(this);
    ui->pageFrame->installEventFilter(this);

    connect(&m_pageManager, SIGNAL(pageChanged()), this, SLOT(onPageManager_pageChanged()));
    connect(&m_pageManager, SIGNAL(volumeChanged(QString)), this, SLOT(onPageManager_volumeChanged(QString)));
    connect(ui->graphicsView, SIGNAL(scrollModeChanged(bool)), this, SLOT(onScrollModeChanged(bool)));
    connect(ui->graphicsView, SIGNAL(zoomingChanged()), this, SLOT(onPageManager_pageChanged()));
    connect(ui->graphicsView, SIGNAL(fittingChanged(PageContent::FitMode)), this, SLOT(onGraphicsView_fittingChanged(PageContent::FitMode)));

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
        setWindowTop(!qApp->TopWindowWhenRunWithAssoc());
        return;
    }
    // auto restore
    if(qApp->AutoLoaded() && !qApp->LastViewPath().isEmpty()) {
        QString bookmark = qApp->LastViewPath();
        loadVolume(bookmark, true);
        makeBookmarkMenu();
    }
}


MainWindow::~MainWindow()
{
    if(qApp->AutoLoaded() && m_pageManager.currentPageCount() > 0) {
        QString path = QDir::fromNativeSeparators(m_pageManager.currentPagePath());
        qApp->setLastViewPath(path);
    }
    delete ui;
    m_pageManager.dispose();
    qApp->saveSettings();
}

void MainWindow::resetShortcutKeys()
{
    QMap<QString, QAction*>& actions = qApp->keyActions().actions();
    QMap<QString, QKeySequence> & seqMap = qApp->keyActions().keyMaps();
    foreach(const QString& name, actions.keys()) {
        auto a = actions[name];
        QKeySequence seq = seqMap[name];
//        a->setShortcut(seq);

        QList<QKeySequence> seqlist;
        for(int i = 0; i < seq.count(); i++) {
            seqlist << QKeySequence(seq[i]);
        }
        a->setShortcuts(seqlist);
//        a->setShortcutContext(Qt::ApplicationShortcut);
    }
    onScrollModeChanged(ui->graphicsView->isScrollMode());
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
            if(qApp->TopWindowWhenDropped())
                setWindowTop(false);
        }
    }
}
static bool needContextMenu = false;

void MainWindow::wheelEvent(QWheelEvent *e)
{
    int delta = e->delta() < 0 ? -Q_MOUSE_DELTA : e->delta() > 0 ? Q_MOUSE_DELTA : 0;
    QMouseValue mv(QKeySequence(qApp->keyboardModifiers()), e->buttons(), delta);
    QAction* action = qApp->mouseActions().getActionByKey(mv);
    if(e->buttons() & Qt::RightButton)
        needContextMenu = false;
    if(action == ui->actionZoomIn || action == ui->actionZoomOut) {
        action->trigger();
        e->accept();
        return;
    }
    if(ui->graphicsView->isScrollMode() && !qApp->ScrollWithCursorWhenZooming())
        return;
    if(action) {
        action->trigger();
        e->accept();
        return;
    }
    QMainWindow::wheelEvent(e);
}

/**
 * @brief Support for Customized Shortcut Keys
 */
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    QKeySequence seq(event->key() | event->modifiers());
    qDebug() << seq.toString() << focusWidget();

    if(this->focusWidget() != ui->graphicsView)
        return;
    if(ui->graphicsView->isScrollMode() && !qApp->ScrollWithCursorWhenZooming()) {
        if(QString("Left, Right, Up, Down").contains(seq.toString())) {
            if(seq.toString()=="Left")
                ui->graphicsView->horizontalScrollBar()->setValue(ui->graphicsView->horizontalScrollBar()->value()-300);
            if(seq.toString()=="Right")
                ui->graphicsView->horizontalScrollBar()->setValue(ui->graphicsView->horizontalScrollBar()->value()+300);
            if(seq.toString()=="Up")
                ui->graphicsView->verticalScrollBar()->setValue(ui->graphicsView->verticalScrollBar()->value()-300);
            if(seq.toString()=="Down")
                ui->graphicsView->verticalScrollBar()->setValue(ui->graphicsView->verticalScrollBar()->value()+300);
            return;
        }
    }

    QAction* action = qApp->keyActions().getActionByKey(seq);
    if(action) {
        action->trigger();
        event->accept();
        return;
    }
}

void MainWindow::closeEvent(QCloseEvent *)
{
    onCatalogWindow_closed();
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
    case QEvent::ShortcutOverride:
        return true;
	case QEvent::TouchBegin:
	case QEvent::TouchUpdate:
	case QEvent::TouchEnd: {
		auto touchEv = dynamic_cast<QTouchEvent*>(event);
		if (touchEv) {
			touchEvent(touchEv);
			return true;
		}
		break;
	}
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
            // tap left/right of window
            if(mouseEvent->button() == Qt::LeftButton) {
                if(ui->graphicsView->hoverState() == Qt::AnchorLeft) {
                    ui->actionTurnPageOnLeft->triggered();
                    return true;
                }
                if(ui->graphicsView->hoverState() == Qt::AnchorRight) {
                    ui->actionTurnPageOnRight->triggered();
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
            QAction* action = qApp->mouseActions().getActionByKey(mv);
            if(action) {
                action->trigger();
                return true;
            }
        }
        break;
    // ContextMenu event occurs when releasing the RightButton
    case QEvent::ContextMenu:
        if(obj == ui->graphicsView) {
//            QContextMenuEvent *contextMenuEvent = dynamic_cast<QContextMenuEvent*>(event);
//            qDebug() << contextMenuEvent;
            QMouseValue mv(QKeySequence(qApp->keyboardModifiers()), Qt::RightButton, 0);
            QAction* action = qApp->mouseActions().getActionByKey(mv);
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

void MainWindow::loadVolume(QString path, bool prohibitProhibit2Page)
{
    QStringList seps = path.split("::");
    if(!IFileLoader::isArchiveFile(seps[0]) && IFileLoader::isImageFile(path)) {
        m_pageManager.loadVolumeWithFile(path, prohibitProhibit2Page);
        return;
    }
    if(m_pageManager.loadVolume(path)) {
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

void MainWindow::onActionExit_triggered()
{
    QApplication::quit();
    QCoreApplication::quit();
}

void MainWindow::onSavingHistory_triggered(bool enable)
{
    qApp->setDontSavingHistory(enable);
}

void MainWindow::onActionClearHistory_triggered()
{
    qApp->clearHistory();
    makeHistoryMenu();
}

void MainWindow::onGraphicsView_anchorHovered(Qt::AnchorPoint anchor)
{
    bool showMenubar = !qApp->ShowMenuBar();
    bool showToolbar = !qApp->ShowToolBar();
    bool showPageBar = !qApp->ShowSliderBar();
    bool fullscreen = isFullScreen();
    if(!fullscreen) {
        if(!showToolbar && !showMenubar && !showPageBar)
            return;
    }
    if(anchor == Qt::AnchorTop && (showMenubar || showToolbar || fullscreen)) {
        QInnerFrame *innerFrame = new QInnerFrame(ui->graphicsView);
        connect(innerFrame, &QInnerFrame::init, this, [=]{
            if(showMenubar || fullscreen) {
                innerFrame->layout()->addWidget(ui->menuBar);
                ui->menuBar->setVisible(true);
            }
            if(showToolbar || fullscreen) {
                innerFrame->layout()->addWidget(ui->mainToolBar);
                ui->mainToolBar->setVisible(true);
            }
        });
        connect(innerFrame, &QInnerFrame::deinit, this, [=]{
//            qDebug() << showToolbar << showMenubar << fullscreen;
            bool fullscreen2 = isFullScreen();
            if(showToolbar || fullscreen2) {
                ui->mainToolBar->setVisible(false);
                addToolBar(ui->mainToolBar);
                if(!fullscreen2 && qApp->ShowToolBar())
                    ui->mainToolBar->setVisible(true);
            }
            if(showMenubar || fullscreen2) {
                ui->menuBar->setVisible(false);
                setMenuBar(ui->menuBar);
                if(!fullscreen2 && qApp->ShowMenuBar())
                    ui->menuBar->setVisible(true);
            }
        });
        connect(this, SIGNAL(changingFullscreen(bool)), innerFrame, SLOT(close()));
        connect(innerFrame, &QInnerFrame::closed, this, [=]{
            delete innerFrame;
        });
        innerFrame->showWithoutTitleBar();
    }
    if(anchor == Qt::AnchorBottom && !qApp->HidePageBarParmanently() && (showPageBar || fullscreen)) {
        QInnerFrame *innerFrame = new QInnerFrame(ui->graphicsView, Qt::AnchorBottom, qApp->LargeToolbarIcons() ? 60 : 30);
        connect(innerFrame, &QInnerFrame::init, this, [&]{
            innerFrame->layout()->addWidget(ui->pageFrame);
            ui->pageFrame->show();
        });
        connect(innerFrame, &QInnerFrame::deinit, this, [&]{
            ui->pageFrame->hide();
            ui->verticalViewPage->layout()->addWidget(ui->pageFrame);
        });
        connect(this, SIGNAL(changingFullscreen(bool)), innerFrame, SLOT(close()));
        connect(innerFrame, &QInnerFrame::closed, this, [=]{
            delete innerFrame;
        });
        innerFrame->showWithoutTitleBar();
    }
    if(anchor == Qt::AnchorHorizontalCenter) {
//        ui->pageFrame->hide();
    }
    ui->graphicsView->readyForPaint();
}

void MainWindow::onScrollModeChanged(bool scrolled)
{
    QStringList cusors = {"Left", "Right", "Up", "Down"};
    // enable/disable cursor key shortcuts
    foreach(const QString& c, cusors) {
        QString name = qApp->keyActions().getNameByValue(QKeySequence(c));
        if(!name.isEmpty())
            resetShortCut(name, c, scrolled);
    }
}

void MainWindow::resetShortCut(const QString name, const QString shortcuttext, bool removed)
{
    QMap<QString, QAction*>& actions = qApp->keyActions().actions();
    QMap<QString, QKeySequence> & seqMap = qApp->keyActions().keyMaps();
    auto a = actions[name];
    QKeySequence seq = seqMap[name];

    QList<QKeySequence> seqlist;
    for(int i = 0; i < seq.count(); i++) {
        seqlist << QKeySequence(seq[i]);
    }
    if(removed)
        seqlist.removeOne(QKeySequence(shortcuttext));
    a->setShortcuts(seqlist);
}

void MainWindow::createCatalogWindow(bool docked)
{
    if(m_catalogWindow)
        onCatalogWindow_closed();
    if(docked) {
        if(m_folderWindow && m_folderWindow->parent())
            onFolderWindow_closed();
        if(m_exifDialog && m_exifDialog->parent())
            onExifDialog_closed();
        m_catalogWindow = new CatalogWindow(nullptr, ui);
        m_catalogWindow->setThumbnailManager(m_thumbManager);
        connect(m_catalogWindow, SIGNAL(closed()), this, SLOT(onCatalogWindow_closed()));
        connect(m_catalogWindow, SIGNAL(openVolume(QString)), this, SLOT(onCatalogWindow_openVolume(QString)));
        ui->catalogSplitter->insertWidget(0, m_catalogWindow);
        auto sizes = ui->catalogSplitter->sizes();
        int sum = sizes[0]+sizes[1];
        sizes[0] = 200;
        sizes[1] = sum-sizes[0];
        ui->catalogSplitter->setSizes(sizes);
        m_catalogWindow->setAsInnerWidget();
    } else {
        m_catalogWindow = new CatalogWindow(nullptr, ui);
        m_catalogWindow->setThumbnailManager(m_thumbManager);
        connect(m_catalogWindow, SIGNAL(closed()), this, SLOT(onCatalogWindow_closed()));
        connect(m_catalogWindow, SIGNAL(openVolume(QString)), this, SLOT(onCatalogWindow_openVolume(QString)));
        m_catalogWindow->setAsToplevelWindow();
        QRect self = geometry();
        m_catalogWindow->setGeometry(self.left()-100, self.top()+100, self.width(), self.height());
        m_catalogWindow->show();
    }
}

void MainWindow::createFolderWindow(bool docked)
{
    QString oldpath;
    if(m_folderWindow) {
        oldpath = m_folderWindow->currentPath();
        onFolderWindow_closed();
    }
    if(oldpath.isEmpty()) {
        oldpath = m_pageManager.volumePath();
        if(oldpath.isEmpty())
            oldpath = qApp->HomeFolderPath();
    }
    if(docked) {
        if(m_catalogWindow && m_catalogWindow->parent())
            onCatalogWindow_closed();
        if(m_exifDialog && m_exifDialog->parent())
            onExifDialog_closed();
        m_folderWindow = new FolderWindow(nullptr, ui);
        m_folderWindow->setFolderPath(oldpath, false);
        connect(m_folderWindow, SIGNAL(closed()), this, SLOT(onFolderWindow_closed()));
        connect(m_folderWindow, SIGNAL(openVolume(QString)), this, SLOT(onFolderWindow_openVolume(QString)));
        connect(&m_pageManager, SIGNAL(volumeChanged(QString)), m_folderWindow, SLOT(onPageManager_volumeChanged(QString)));
        ui->catalogSplitter->insertWidget(0, m_folderWindow);
        auto sizes = ui->catalogSplitter->sizes();
        int sum = sizes[0]+sizes[1];
        sizes[0] = 200;
        sizes[1] = sum-sizes[0];
        ui->catalogSplitter->setSizes(sizes);
        m_folderWindow->setAsInnerWidget();
        return;
    } else {
        // close child widget, and recreate as independent window
        m_folderWindow = new FolderWindow(nullptr, ui);
        QRect self = geometry();
        m_folderWindow->setGeometry(self.left()-100, self.top()+100, self.width(), self.height());
        m_folderWindow->setAsToplevelWindow();
        m_folderWindow->setFolderPath(oldpath, false);
        connect(m_folderWindow, SIGNAL(closed()), this, SLOT(onFolderWindow_closed()));
        connect(m_folderWindow, SIGNAL(openVolume(QString)), this, SLOT(onFolderWindow_openVolume(QString)));
        connect(&m_pageManager, SIGNAL(volumeChanged(QString)), m_folderWindow, SLOT(onPageManager_volumeChanged(QString)));
        m_folderWindow->show();
    }
}

void MainWindow::onActionFullscreen_triggered()
{
    qDebug() << "on_fullscreen_triggered";
    if(isFullScreen()) {
        emit changingFullscreen(false);
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
        emit changingFullscreen(true);
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

void MainWindow::onActionStayOnTop_triggered(bool top)
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

void MainWindow::onGraphicsView_fittingChanged(PageContent::FitMode mode)
{
    ui->actionFitting->setChecked(mode == PageContent::FitToRect);
    ui->actionFitToWidth->setChecked(mode == PageContent::FitToWidth);
}

void MainWindow::onPageManager_pageChanged()
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

    // StatusBar
//    m_pageCaption = m_pageManager.currentPageStatusAsString();
    m_pageCaption = m_imageString.getStatusBarText();

    // Elide text(Otherwise the width of the main window will be forcibly changed)
    QFontMetrics fontMetrics(ui->statusLabel->font());
    QString statusLabelTxt = fontMetrics.elidedText(m_pageCaption, Qt::ElideMiddle, width()-100);
    ui->statusLabel->setText(statusLabelTxt);
    resetVolumeCaption();

    if(!qApp->ShowStatusBar())
        setWindowTitle(QString("%1 - %2").arg(m_pageCaption).arg(qApp->applicationName()));

    if(m_exifDialog && m_pageManager.currentPageCount() > 0) {
        m_exifDialog->setExif(m_pageManager.currentPageContent()[0]);
    }
}

void MainWindow::onPageManager_volumeChanged(QString path)
{
    if(path.isEmpty()) {
        on_pageNolongerNeeded_triggered();
        return;
    }
    if(!qApp->DontSavingHistory())
        qApp->addHistory(path);
    if(!isFullScreen() && qApp->ShowSliderBar())
        ui->pageFrame->show();

    resetVolumeCaption();
    makeHistoryMenu();

}


void MainWindow::onPageSlider_valueChanged(int value)
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

void MainWindow::onActionAppVersion_triggered()
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

void MainWindow::onLanguageSelector_languageChanged(QString language)
{
    qApp->setUiLanguage(language);
    ui->retranslateUi(this);
    ui->menuLoadBookmark->setTitle(QApplication::translate("MainWindow", "LoadBookmark", Q_NULLPTR));
}

void MainWindow::onActionRegistAssocs_triggered()
{
#ifdef Q_OS_WIN
    FileAssocDialog dialog(this);
    int result = dialog.exec();
    if(result == QDialog::Rejected) {
    } else {
    }
#endif
}

void MainWindow::onActionRegistAssocsUAC_triggered()
{
    QProcess::startDetached(qApp->getApplicationFilePath("AssociateFilesWithQuickViewer.exe"),
                            QStringList(),
                            QDir::toNativeSeparators(qApp->applicationDirPath()));
}

void MainWindow::onActionContextMenu_triggered()
{
    m_contextMenu->exec(QCursor::pos());
}

void MainWindow::onActionAutoLoaded_triggered(bool autoloaded)
{
    qApp->setAutoLoaded(autoloaded);
}

void MainWindow::onMenuHistory_triggered(QAction *action)
{
    //qDebug() << action;
    loadVolume(action->text().mid(4));
}

#define EXIF_DIALOG_WIDTH 280

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

static int touchCount = -1;
static QTouchEvent::TouchPoint touchBegin;
static QTouchEvent::TouchPoint touchEnd;
//static QTouchEvent::TouchPoint touchPrev;
static QPoint scrollBarBegin;
static bool touchFirst = false;
static bool rescaling = false;
static int twoFingersCount = 0;

void MainWindow::touchEvent(QTouchEvent * e)
{
	qDebug() << "type:" << e->type() << "count:" << e->touchPoints().count();
	switch (e->type()) {
	case QEvent::TouchBegin:
		touchFirst = true;
        rescaling = false;
		break;
	case QEvent::TouchUpdate:
		if (touchFirst) {
            touchCount = qMax(touchCount,e->touchPoints().count());
            touchBegin = e->touchPoints().first();
//            touchBegin = touchPrev = e->touchPoints().first();
            touchFirst = false;
            scrollBarBegin = QPoint(ui->graphicsView->horizontalScrollBar()->value(), ui->graphicsView->verticalScrollBar()->value());
            if (touchCount == 2)
                twoFingersCount++;
		} else {
//            touchPrev = touchEnd;
			touchEnd = e->touchPoints().first();
            qreal beginx = 1.0*touchBegin.pos().x() / ui->graphicsView->width();
            qreal beginy = 1.0*touchBegin.pos().y() / ui->graphicsView->height();
            // finger operations are effective only in the center of the screen
            if(beginx < 0.25 || 0.75 < beginx || beginy < 0.25 || 0.75 < beginy )
                break;
            if (touchCount == 1) {
//                ui->graphicsView->updateViewportOffset(
//                    QPointF(
//                        touchEnd.pos().x()-touchPrev.pos().x(),
//                        touchEnd.pos().y()-touchPrev.pos().y()));

//                ui->graphicsView->horizontalScrollBar()->setValue(ui->graphicsView->horizontalScrollBar()->value()-touchEnd.pos().x()+touchPrev.pos().x());
//                ui->graphicsView->verticalScrollBar()->setValue(ui->graphicsView->verticalScrollBar()->value()-touchEnd.pos().y()+touchPrev.pos().y());

                ui->graphicsView->horizontalScrollBar()->setValue(scrollBarBegin.x()-touchEnd.pos().x()+touchEnd.startPos().x());
                ui->graphicsView->verticalScrollBar()->setValue(scrollBarBegin.y()-touchEnd.pos().y()+touchEnd.startPos().y());

                break;
            }
            else if (touchCount > 2 || e->touchPoints().count() < 2) {
                break;
            }
            // determine scale and rotate factor
            const QTouchEvent::TouchPoint &touchPoint0 = e->touchPoints().first();
            const QTouchEvent::TouchPoint &touchPoint1 = e->touchPoints().last();
            if(!rescaling) {
                // Do not process when two fingers move in parallel
                QPointF move = (touchPoint0.pos()-touchPoint0.startPos())-(touchPoint1.pos()-touchPoint1.startPos());
                rescaling = move.x()*move.x()+move.y()*move.y() > 1000;
            }
            if(rescaling) {
                qreal currentScale =
                        QLineF(touchPoint0.pos(), touchPoint1.pos()).length()
                        / QLineF(touchPoint0.startPos(), touchPoint1.startPos()).length();
                QLineF line0(touchPoint0.startPos(), touchPoint1.startPos());
                QLineF line1(touchPoint0.scenePos(), touchPoint1.scenePos());
                ui->graphicsView->updateViewportFactors(currentScale, line1.angleTo(line0));
            }
        }
		break;
	case QEvent::TouchEnd:
		int ofsX = touchEnd.pos().x() - touchBegin.pos().x();
		int ofsY = touchEnd.pos().y() - touchBegin.pos().y();
		// React only at the bottom 1/3 of the screen
        qreal endy = 1.0*touchEnd.pos().y() / ui->graphicsView->height();
        if (touchCount == 1 && 0.75 < endy) {
			if (ofsX > 30) {
                ui->actionTurnPageOnLeft->trigger();
			}
			else if (ofsX < -30) {
                ui->actionTurnPageOnRight->trigger();
			}
		}
		if (touchCount == 2) {
            if(twoFingersCount >= 2) {
                // Double tap with 2 fingers to cancel scale
                ui->graphicsView->resetViewportFactors();
                twoFingersCount = 0;
            }
            else if(rescaling) {
                // Confirm scale with the last input content
                ui->graphicsView->commitViewportFactors();
                twoFingersCount = 0;
            }
            else if (ofsY < -30 && endy < 0.25) {
				ui->actionFullscreen->trigger();
			}
            else if (ofsX > 30 && 0.75 < endy) {
				ui->actionNextOnePage->trigger();
			}
            else if (ofsX < -30 && 0.75 < endy) {
				ui->actionPrevOnePage->trigger();
			}
		}
		touchCount = -1;
		break;
	}
}

void MainWindow::onActionShowFolder_triggered()
{
    if(m_folderWindow) {
        onFolderWindow_closed();
        return;
    }
    createFolderWindow(!qApp->ShowPanelSeparateWindow());
}

void MainWindow::onFolderWindow_closed()
{
    if(m_folderWindow) {
        delete m_folderWindow;
        m_folderWindow = nullptr;
    }
}

void MainWindow::onFolderWindow_openVolume(QString path)
{
    loadVolume(path);
}


void MainWindow::onActionOpenVolumeWithProgress_triggered(bool enabled)
{
    qApp->setOpenVolumeWithProgress(enabled);
}

void MainWindow::onActionShowReadProgress_triggered(bool enabled)
{
    qApp->setShowReadProgress(enabled);
    if(m_folderWindow) {
        m_folderWindow->reset();
    }
}

void MainWindow::onActionShowCatalog_triggered()
{
    if(m_catalogWindow) {
        onCatalogWindow_closed();
        return;
    }
    createCatalogWindow(!qApp->ShowPanelSeparateWindow());
}

void MainWindow::onCatalogWindow_closed()
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

void MainWindow::resetVolumeCaption()
{
    m_volumeCaption = m_imageString.getTitleBarText();
    setWindowTitle(m_volumeCaption);
}

void MainWindow::onActionOpenExif_triggered()
{
    if(m_exifDialog || m_pageManager.currentPageCount()==0)
        return;
    const easyexif::EXIFInfo& info = m_pageManager.currentPageContent()[0].Info;
    if(info.ImageWidth == 0)
        return;
    if(m_catalogWindow && m_catalogWindow->parent())
        onCatalogWindow_closed();
    if(m_folderWindow && m_folderWindow->parent())
        onFolderWindow_closed();

    m_exifDialog = new ExifDialog();
    m_exifDialog->setExif(m_pageManager.currentPageContent()[0]);
    connect(m_exifDialog, SIGNAL(closed()), this, SLOT(onExifDialog_closed()));

    ui->catalogSplitter->insertWidget(1, m_exifDialog);
    auto sizes = ui->catalogSplitter->sizes();
    int sum = sizes[0]+sizes[1];
    sizes[1] = EXIF_DIALOG_WIDTH;
    sizes[0] = sum-sizes[1];
    ui->catalogSplitter->setSizes(sizes);
}

void MainWindow::onExifDialog_closed()
{
    if(m_exifDialog) {
        delete m_exifDialog;
        m_exifDialog = nullptr;
    }
}


void MainWindow::onCatalogWindow_openVolume(QString path)
{
    loadVolume(path);
    setWindowTop(false);
}

void MainWindow::loadVolumeWithAssoc(QString path)
{
    loadVolume(path);
    setWindowTop(!qApp->TopWindowWhenRunWithAssoc());
}

void MainWindow::onActionSearchTitleWithOptions_triggered(bool enable)
{
    qApp->setSearchTitleWithOptions(enable);
    if(m_catalogWindow)
        m_catalogWindow->resetVolumes();
}

void MainWindow::onActionCatalogTitleWithoutOptions_triggered(bool enable)
{
    qApp->setTitleWithoutOptions(enable);
    if(m_catalogWindow)
        m_catalogWindow->searchByWord(true);
}

void MainWindow::onActionCatalogViewList_triggered()
{
    qApp->setCatalogViewModeSetting(qvEnums::List);
    ui->actionCatalogViewList->setChecked(true);
    ui->actionCatalogViewIcon->setChecked(false);
    ui->actionCatalogViewIconNoText->setChecked(false);
    if(m_catalogWindow)
        m_catalogWindow->resetVolumes();
}

void MainWindow::onActionCatalogViewIcon_triggered()
{
    qApp->setCatalogViewModeSetting(qvEnums::Icon);
    ui->actionCatalogViewList->setChecked(false);
    ui->actionCatalogViewIcon->setChecked(true);
    ui->actionCatalogViewIconNoText->setChecked(false);
    if(m_catalogWindow)
        m_catalogWindow->resetVolumes();
}

void MainWindow::onActionCatalogViewIconNoText_triggered()
{
    qApp->setCatalogViewModeSetting(qvEnums::IconNoText);
    ui->actionCatalogViewList->setChecked(false);
    ui->actionCatalogViewIcon->setChecked(false);
    ui->actionCatalogViewIconNoText->setChecked(true);
    if(m_catalogWindow)
        m_catalogWindow->resetVolumes();
}

void MainWindow::onActionShowTagBar_triggered(bool enable)
{
    qApp->setShowTagBar(enable);
    if(m_catalogWindow)
        m_catalogWindow->on_showTagBar_triggered(enable);
}

void MainWindow::onActionCatalogIconLongText_triggered(bool enable)
{
    qApp->setIconLongText(enable);
    if(m_catalogWindow)
        m_catalogWindow->resetViewMode();
}

void MainWindow::onActionTurnPageOnLeft_triggered()
{
    if(qApp->RightSideBook())
        ui->actionNextPage->trigger();
    else
        ui->actionPrevPage->trigger();
}

void MainWindow::onActionTurnPageOnRight_triggered()
{
    if(qApp->RightSideBook())
        ui->actionPrevPage->trigger();
    else
        ui->actionNextPage->trigger();
}

void MainWindow::onActionOpenfolder_triggered()
{
    QString filter = tr("All Files( *.*);;Images (*.jpg *.jpeg *.png *.tif *.tiff *.ico);;Archives( *.zip *.7z *.rar)", "Text that specifies the file extension to be displayed when opening a file with OpenFileFolder");
    QString folder = QFileDialog::getOpenFileName(
                this,
                tr("Please select the image or archive", "Title of the dialog displayed when opening a file with OpenFileFolder"),
                qApp->LastOpenedFolderPath(),
                filter);
//    QFileDialog dialog = QFileDialog(this, tr("Open a image folder"));
//    if(dialog.exec()) {
    if(folder.length() > 0) {
        //qDebug() << folder;
//        QDir dir(folder);
//        if(dir.exists())
//            loadVolume(folder);
        loadVolume(folder);
        qApp->setLastOpenedFolderPath(folder);
    }
}

void MainWindow::onActionShowToolBar_triggered(bool showToolBar)
{
    if(showToolBar)
        ui->mainToolBar->show();
    else
        ui->mainToolBar->hide();
    qApp->setShowToolBar(showToolBar);
}

void MainWindow::onActionShowPageBar_triggered(bool showSliderBar)
{
    if(showSliderBar)
        ui->pageFrame->show();
    else
        ui->pageFrame->hide();
    qApp->setShowSliderBar(showSliderBar);
}

void MainWindow::onActionShowStatusBar_triggered(bool showStatusBar)
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

void MainWindow::onActionShowMenuBar_triggered(bool showMenuBar)
{
    if(showMenuBar) {
        if(qApp->ShowToolBar()) ui->mainToolBar->hide();
        menuBar()->show();
        if(qApp->ShowToolBar()) ui->mainToolBar->show();
    }
    else
        menuBar()->hide();
    qApp->setShowMenuBar(showMenuBar);

}

void MainWindow::onActionOpenKeyConfig_triggered()
{
    KeyConfigDialog dialog(qApp->keyActions(), this);
    int result = dialog.exec();
    if(result == QDialog::Accepted) {
        qApp->keyActions() = dialog.keyActions();
        resetShortcutKeys();
    }
}

void MainWindow::onActionOpenMouseConfig_triggered()
{
    MouseConfigDialog dialog(qApp->mouseActions(), this);
    int result = dialog.exec();
    if(result == QDialog::Accepted) {
        qApp->mouseActions() = dialog.mouseActions();
    }
}

void MainWindow::onActionOpenOptionsDialog_triggered()
{
    OptionsDialog dialog(this);
    QColor back = qApp->BackgroundColor();
    QColor back2 = qApp->BackgroundColor2();
    bool checkered = qApp->UseCheckeredPattern();
    if(dialog.exec() == QDialog::Accepted) {
        dialog.reflectResults();
        if(m_pageManager.size() > 0)
            onPageManager_pageChanged();
        if(back != qApp->BackgroundColor()
           || back2 != qApp->BackgroundColor2()
           || checkered != qApp->UseCheckeredPattern()) {
            ui->graphicsView->resetBackgroundColor();
        }
    }
}

void MainWindow::onActionBeginAsFullscreen_triggered(bool enable)
{
    qApp->setBeginAsFullscreen(enable);
}

void MainWindow::onActionShowPanelSeparateWindow_triggered(bool enable)
{
    qApp->setShowPanelSeparateWindow(enable);
    if(m_folderWindow)
        createFolderWindow(!qApp->ShowPanelSeparateWindow());
    if(m_catalogWindow)
        createCatalogWindow(!qApp->ShowPanelSeparateWindow());
}

template<typename MenuTypePtr>
static void setMenuAndSubmenuFont(MenuTypePtr parent, QFont font)
{
    parent->setFont(font);
    foreach(QObject* obj , parent->children()) {
        QMenu* menu = dynamic_cast<QMenu*>(obj);
        if(menu)
            setMenuAndSubmenuFont(menu, font);
    }
}


void MainWindow::onActionLargeToolbarIcons_triggered(bool enable)
{
    qApp->setLargeToolbarIcons(enable);
    ui->mainToolBar->setIconSize(
        enable ? QSize(qvEnums::Large2Icon, qvEnums::Large2Icon)
               : QSize(qvEnums::NormalIcon, qvEnums::NormalIcon));
    int fontsize = enable ? (int)(1.5*m_menubarFontSize) : m_menubarFontSize;
    m_fullscreenButton->setIconSize(QSize(2*fontsize, 2*fontsize));
    QFont font = ui->menuBar->font();
    font.setPointSize(fontsize);

    setMenuAndSubmenuFont(ui->menuBar, font);
    setMenuAndSubmenuFont(m_contextMenu, font);
	ui->pageLabel->setFont(font);
	ui->pageLabel->setMinimumWidth(fontsize * 10);
	if (enable) {
//		int sliderHeight = (int)(1.5*m_pageSliderHeight);
		ui->pageSlider->setMinimumHeight(m_pageSliderHeight);
		if (ui->pageFrame->isVisible()) {
			ui->pageFrame->setVisible(false);
			ui->pageFrame->setVisible(true);
		}
	}
	else {
		ui->pageSlider->setMinimumHeight(0);
    }
}

//void MainWindow::onActionShowFullscreenTitleBar_triggered(bool enable)
//{
//    qApp->setShowFullscreenTitleBar(enable);
//}

void MainWindow::onActionProjectWeb_triggered()
{
    QUrl url = QString("https://kanryu.github.io/quickviewer/");
    QDesktopServices::openUrl(url);
}

void MainWindow::onActionCheckVersion_triggered()
{
    QUrl url = QString("https://kanryu.github.io/quickviewer/checkversion/?ver=%1").arg(qApp->applicationVersion());
    QDesktopServices::openUrl(url);
}

void MainWindow::onActionExitApplicationOrFullscreen_triggered()
{
    if(m_catalogWindow) {
        onCatalogWindow_closed();
        return;
    }
    if(isFullScreen())
        ui->actionFullscreen->trigger();
    else
        ui->actionExit->trigger();
}

void MainWindow::onActionMailAttachment_triggered()
{
    if(m_pageManager.isArchive())
        return;
    QString path = m_pageManager.currentPagePath();
    if(!path.length())
        return;
    setMailAttachment(path);
}

void MainWindow::onActionRenameImageFile_triggered()
{
    if(!m_pageManager.isFolder() || m_pageManager.currentPageCount() == 0)
        return;
    RenameDialog dialog(this, m_pageManager.realVolumePath(), m_pageManager.currentPageName());
    if(dialog.exec() == QDialog::Accepted) {
        m_pageManager.loadVolume(QDir(m_pageManager.realVolumePath()).absoluteFilePath(dialog.newName()));
    }
}

void MainWindow::onActionConfirmDeletePage_triggered(bool enable)
{
    qApp->setConfirmDeletePage(enable);
}

void MainWindow::onActionRecyclePage_triggered()
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
        msgBox.setWindowTitle(tr("Confirmation", "Confirm putting displayed file in Recycle Bing MessageBox title"));

        //text
        msgBox.setTextFormat(Qt::RichText);
        QString message = QString("<h2>%1</h2><p>%2</p>" )
                .arg(tr("Are you sure you want to move the image to Recycle Bin?", "Confirm putting displayed file in Recycle Box Message Box body"))
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
        m_pageManager.reloadVolumeAfterRemoveImage();
    }
}

void MainWindow::onActionDeletePage_triggered()
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
        msgBox.setWindowTitle(tr("Confirmation", "Confirm deleting image file on MessageBox title"));

        //text
        msgBox.setTextFormat(Qt::RichText);
        QString message = QString("<h2>%1</h2><p>%2</p>" )
                .arg(tr("Are you sure you want to delete this image?", "Confirm deleting image file on Message Box body"))
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
    QFile file(path);
    if(file.remove()) {
        m_pageManager.reloadVolumeAfterRemoveImage();
    }
}

void MainWindow::onActionMaximizeOrNormal_triggered()
{
    if(isFullScreen()) {
        ui->actionFullscreen->trigger();
    } else if(isMaximized()) {
        showNormal();
    } else {
        showMaximized();
    }
}

void MainWindow::onActionRestoreWindowState_triggered(bool saveState)
{
    qApp->setRestoreWindowState(saveState);
}

void MainWindow::onActionSlideShow_triggered(bool )
{
    if(m_pageManager.size() == 0)
        return;
    if(!isFullScreen())
        ui->actionFullscreen->trigger();
    ui->graphicsView->toggleSlideShow();
}

void MainWindow::onActionShaderNearestNeighbor_triggered()
{
    uncheckAllShaderMenus();
    qApp->setEffect(qvEnums::NearestNeighbor);
    ui->actionShaderNearestNeighbor->setChecked(true);
    ui->graphicsView->readyForPaint();
}

void MainWindow::onActionShaderBilinear_triggered()
{
    uncheckAllShaderMenus();
    ui->actionShaderBilinear->setChecked(true);
    qApp->setEffect(qvEnums::Bilinear);
    ui->graphicsView->readyForPaint();
}

void MainWindow::onActionShaderBicubic_triggered()
{
#ifndef QV_WITHOUT_OPENGL
    uncheckAllShaderMenus();
    qApp->setEffect(qvEnums::Bicubic);
    ui->actionShaderBicubic->setChecked(true);
    ui->graphicsView->readyForPaint();
#endif
}

void MainWindow::onActionShaderLanczos_triggered()
{
#ifndef QV_WITHOUT_OPENGL
    uncheckAllShaderMenus();
    qApp->setEffect(qvEnums::Lanczos);
    ui->actionShaderLanczos->setChecked(true);
    ui->graphicsView->readyForPaint();
#endif
}

void MainWindow::onActionShaderBilinearBeforeCpuBicubic_triggered()
{
    uncheckAllShaderMenus();
    qApp->setEffect(qvEnums::BilinearAndCpuBicubic);
    ui->actionShaderBilinearBeforeCpuBicubic->setChecked(true);
    ui->graphicsView->readyForPaint();
}

void MainWindow::onActionShaderCpuBicubic_triggered()
{
    uncheckAllShaderMenus();
    qApp->setEffect(qvEnums::CpuBicubic);
    ui->actionShaderCpuBicubic->setChecked(true);
    ui->graphicsView->readyForPaint();
}

void MainWindow::onActionSaveBookmark_triggered()
{
    if(!m_pageManager.currentPageCount())
        return;
    QString path = QDir::fromNativeSeparators(m_pageManager.currentPagePath());
    qApp->addBookMark(path);
    makeBookmarkMenu();
    ui->statusBar->showMessage(tr("Bookmark Saved."));
}

void MainWindow::onActionClearBookmarks_triggered()
{
    qApp->clearBookmarks();
    makeBookmarkMenu();
}

void MainWindow::onActionLoadBookmark_triggered()
{
    QWidget* widget = ui->mainToolBar->widgetForAction(ui->actionLoadBookmark);

    QPoint p = widget->mapToGlobal(QPoint(0, widget->height()));
    ui->menuLoadBookmark->exec(p);
}

void MainWindow::onMenuLoadBookmark_triggered(QAction *action)
{
    if(action == ui->actionClearBookmarks) {
        return;
    }
    QString path = action->data().toString();
    m_pageManager.loadVolume(QDir::toNativeSeparators(path));
}
