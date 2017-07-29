#include <Windows.h>
#include <mapi.h>
#include <Shellapi.h>
#include <QtCore>

#include "qvapplication.h"
#include "mainwindowforwindows.h"
#include "ui_mainwindow.h"
#include "qfullscreenframe.h"

#define IDM_SHOWMAINMENU 2

MainWindowForWindows* MainWindowForWindows::MainWindowForWindows_self;
WNDPROC MainWindowForWindows::DefStaticProc;

MainWindowForWindows::MainWindowForWindows(QWidget *parent)
    : MainWindow(parent), bFirstView(true)
{
    QString menutxt = tr("Sh&ow/Hide MainMenuBar", "An additional menu displayed when right-clicking the title bar, which is used when undoing the main menu when it is hidden");
    menutxt = ui->actionShowMainMenuBar->text();

    MainWindowForWindows_self = this;
}

bool MainWindowForWindows::moveToTrush(QString path)
{
    WCHAR from[ MAX_PATH+2048 ] = {0};
    path.toWCharArray( from );
    SHFILEOPSTRUCT fileop = {0};
    fileop.wFunc = FO_DELETE;
    fileop.pFrom = from;
    fileop.fFlags = FOF_ALLOWUNDO | FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_SILENT;
    int rv = SHFileOperation( &fileop );
    if( 0 != rv ){
        qDebug() << rv << QString::number( rv ).toInt( 0, 8 );
        return false;
    }

    qDebug() << rv << path;
    return true;
}

bool MainWindowForWindows::setStayOnTop(bool top)
{
    auto hwnd = reinterpret_cast<HWND>(winId());
    if(!hwnd) return false;
    // Place window A on top
    if(top)
        ::SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
    else
        ::SetWindowPos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
    return true;
}

void MainWindowForWindows::setWindowTop()
{
    auto hwnd = reinterpret_cast<HWND>(winId());
    if(!hwnd) return;
    ::ShowWindow(hwnd,SW_RESTORE);
    ::SwitchToThisWindow(hwnd, false);
//    ::SetForegroundWindow(hwnd);
    ::SetWindowPos(hwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
}

static LPSTR qStringToLPSTR(const QString& qString)
{
    // return qString.toLocal8Bit().data();
    return qString.toLatin1().data();
}

static QString mapi32path()
{
    // // try to determine default Simple MAPI handler
    // // first, look for current user's default client
    // registry::tstring default_client =  registry::const_key(HKEY_CURRENT_USER, "Software\\Clients\\Mail")[""].reg_sz("");
    //
    // if (default_client.empty()) {
    // 	// then look for machine-wide settings
    // 	default_client =  registry::const_key(HKEY_LOCAL_MACHINE, "Software\\Clients\\Mail")[""].reg_sz("");
    // }
    //
    // if (!default_client.empty()) {
    // 	registry::const_key regClient(HKEY_LOCAL_MACHINE, registry::tstring("Software\\Clients\\Mail\\" + default_client).c_str());
    // 	registry::tstring s = regClient["DLLPath"].reg_sz("");
    //
    // 	if (s.empty())
    // 		s = regClient["DLLPathEx"].reg_sz("");
    //
    // 	if (!s.empty())
    // 		dllpath = s;
    // }

    return "mapi32";
}

void MainWindowForWindows::setMailAttachment(QString path)
{
    QLibrary lib("mapi32");
#ifdef _MSC_VER
    if( LPMAPISENDMAILW mapi = LPMAPISENDMAILW(lib.resolve("MAPISendMailW")) )
    {
        QString filePath = QDir::toNativeSeparators( path );
        QString fileName = QFileInfo( path ).fileName();
//        QString subject = q.queryItemValue( "subject", QUrl::FullyDecoded );
        MapiFileDescW doc = { 0, 0, 0, 0, 0, 0 };
        doc.nPosition = -1;
        doc.lpszPathName = PWSTR(filePath.utf16());
        doc.lpszFileName = PWSTR(fileName.utf16());
        MapiMessageW message = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
//        message.lpszSubject = PWSTR(subject.utf16());
//        message.lpszNoteText = L"";
        message.nFileCount = 1;
        message.lpFiles = lpMapiFileDescW(&doc);
        switch( mapi( NULL, 0, &message, MAPI_LOGON_UI|MAPI_DIALOG, 0 ) )
        {
        case SUCCESS_SUCCESS:
        case MAPI_E_USER_ABORT:
        case MAPI_E_LOGIN_FAILURE:
            return;
        default: break;
        }
    }
    else
#endif
        if( LPMAPISENDMAIL mapi = LPMAPISENDMAIL(lib.resolve("MAPISendMail")) )
    {
        QByteArray filePath = QDir::toNativeSeparators( path ).toLocal8Bit();
        QByteArray fileName = QFileInfo( path ).fileName().toLocal8Bit();
//        QByteArray subject = q.queryItemValue( "subject", QUrl::FullyDecoded ).toLocal8Bit();
        MapiFileDesc doc = { 0, 0, 0, 0, 0, 0 };
        doc.nPosition = -1;
        std::string flpath = filePath.toStdString();
        std::string flname = fileName.toStdString();
        doc.lpszPathName = LPSTR(flpath.c_str());
        doc.lpszFileName = LPSTR(flname.c_str());
        MapiMessage message = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
//        message.lpszSubject = LPSTR(subject.constData());
//        message.lpszNoteText = "";
        message.nFileCount = 1;
        message.lpFiles = lpMapiFileDesc(&doc);
        switch( mapi( NULL, 0, &message, MAPI_LOGON_UI|MAPI_DIALOG, 0 ) )
        {
        case SUCCESS_SUCCESS:
        case MAPI_E_USER_ABORT:
        case MAPI_E_LOGIN_FAILURE:
            return;
        default: break;
        }
        }
}

bool MainWindowForWindows::eventFilter(QObject *obj, QEvent *event)
{
    switch (event->type()) {
    case QEvent::Leave:
//        if(obj == ui->pageFrame && isFullScreen()) {
//            ui->pageFrame->hide();
//            return true;
//        }
        return QObject::eventFilter(obj, event);
    }
    return MainWindow::eventFilter(obj, event);
}

static QFullscreenFrame *fullscreenFrame;
void MainWindowForWindows::on_hover_anchor(Qt::AnchorPoint anchor)
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
        fullscreenFrame = new QFullscreenFrame((showToolbar || showMenubar) && !fullscreen ? (QWidget*)ui->graphicsView : (QWidget*)this);
        connect(fullscreenFrame, &QFullscreenFrame::init, this, [=]{
            qDebug() << showToolbar << showMenubar << fullscreen;
            if(showToolbar || fullscreen) {
                fullscreenFrame->addToolBar(Qt::TopToolBarArea, ui->mainToolBar);
                ui->mainToolBar->setVisible(true);
            }
            if(showMenubar || fullscreen) {
                fullscreenFrame->setMenuBar(ui->menuBar);
                ui->menuBar->setVisible(true);
            }
        });
        connect(fullscreenFrame, &QFullscreenFrame::deinit, this, [=]{
            qDebug() << showToolbar << showMenubar << fullscreen;
            if(showToolbar || fullscreen) {
                ui->mainToolBar->setVisible(false);
                addToolBar(ui->mainToolBar);
                if(qApp->ShowToolBar())
                    ui->mainToolBar->setVisible(true);
            }
            if(showMenubar || fullscreen) {
                ui->menuBar->setVisible(false);
                setMenuBar(ui->menuBar);
                if(qApp->ShowMenuBar())
                    ui->menuBar->setVisible(true);
            }
        });
        connect(fullscreenFrame, SIGNAL(toShowNormal()), this, SLOT(on_fullscreen_triggered()));
        connect(fullscreenFrame, SIGNAL(exitApp()), this, SLOT(close()));

        if(fullscreen && qApp->ShowFullscreenTitleBar())
            fullscreenFrame->showWithTitlebar();
        else
            fullscreenFrame->showWithoutTitleBar();
    }
    if(anchor == Qt::AnchorBottom && (showPageBar || fullscreen)) {
        fullscreenFrame = new QFullscreenFrame(showPageBar && !fullscreen ? (QWidget*)ui->graphicsView : (QWidget*)this, Qt::AnchorBottom);
        connect(fullscreenFrame, &QFullscreenFrame::init, this, [&]{
            fullscreenFrame->setCentralWidget(ui->pageFrame);
            ui->pageFrame->show();
        });
        connect(fullscreenFrame, &QFullscreenFrame::deinit, this, [&]{
            ui->pageFrame->hide();
            ui->verticalViewPage->layout()->addWidget(ui->pageFrame);
        });
        fullscreenFrame->showWithoutTitleBar();
//        if(qApp->ShowSliderBar())
//            ui->pageFrame->show();
    }
    if(anchor == Qt::AnchorHorizontalCenter) {
//        ui->pageFrame->hide();
    }
    ui->graphicsView->readyForPaint();
}

void MainWindowForWindows::on_fullscreen_triggered()
{
    if(fullscreenFrame && fullscreenFrame->isValid()) {
        fullscreenFrame->closeAndShowNormal();
        return;
    }
    MainWindow::on_fullscreen_triggered();
}

// This method is used because QShowEvent may not be called
bool MainWindowForWindows::nativeEvent(const QByteArray &, void *, long *)
{
    if(!bFirstView)
        return false;

//    int mes = reinterpret_cast<int>(message);
    auto hwnd = reinterpret_cast<HWND>(winId());
    m_showMainMenu = ::GetSystemMenu(hwnd, false);

    QString menutxt = ui->actionShowMainMenuBar->text();

    ::AppendMenu(m_showMainMenu, MF_SEPARATOR, IDM_SHOWMAINMENU-1, 0);
    ::AppendMenu(m_showMainMenu, MF_STRING, IDM_SHOWMAINMENU,
                 reinterpret_cast<LPCWSTR>(menutxt.utf16()));

#ifdef _WIN64
    DefStaticProc = (WNDPROC)GetWindowLongPtr(hwnd , GWLP_WNDPROC);
    SetWindowLongPtr(hwnd , GWLP_WNDPROC , reinterpret_cast<LONG_PTR>(StaticProc));
#else
    DefStaticProc = (WNDPROC)GetWindowLongPtr(hwnd , GWL_WNDPROC);
    SetWindowLongPtr(hwnd , GWL_WNDPROC , reinterpret_cast<LONG_PTR>(StaticProc));
#endif
    bFirstView = false;
    return false;
}


LRESULT CALLBACK MainWindowForWindows::StaticProc(HWND hwnd , UINT msg , WPARAM wp , LPARAM lp) {
    switch(msg) {
    case WM_SYSCOMMAND:
        if (LOWORD(wp) == IDM_SHOWMAINMENU) {
                if(qApp->ShowMenuBar()) {
                    MainWindowForWindows_self->ui->actionShowMenuBar->setChecked(false);
                    MainWindowForWindows_self->ui->actionShowMenuBar->triggered(false);
                }
                else {
                    MainWindowForWindows_self->ui->actionShowMenuBar->setChecked(true);
                    MainWindowForWindows_self->ui->actionShowMenuBar->triggered(true);
                }
            return 0;
        }
    }
    return CallWindowProc(DefStaticProc , hwnd , msg , wp , lp);
}
