#include <Windows.h>
#include <mapi.h>
#include <Shellapi.h>
#include <QtCore>

#include "qvapplication.h"
#include "mainwindowforwindows.h"
#include "ui_mainwindow.h"

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

void MainWindowForWindows::setWindowTop(bool signalOnly)
{
    auto hwnd = reinterpret_cast<HWND>(winId());
    if(!hwnd) return;
    if(!isMaximized())
        ::ShowWindow(hwnd,SW_RESTORE);
//    ::SwitchToThisWindow(hwnd, false);
    int foregroundID;
    if(!signalOnly) {
        foregroundID = ::GetWindowThreadProcessId( ::GetForegroundWindow(), NULL);
        ::AttachThreadInput( ::GetCurrentThreadId(), foregroundID, TRUE);
    }

    ::SetForegroundWindow(hwnd);
    ::SetActiveWindow(hwnd);
    ::SetFocus(hwnd);
    ::SetWindowPos(hwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);

    if(!signalOnly) {
        ::AttachThreadInput( ::GetCurrentThreadId(), foregroundID, FALSE);
    }
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
    default:
        break;
    }
    return MainWindow::eventFilter(obj, event);
}


// // This method is used because QShowEvent may not be called
// bool MainWindowForWindows::nativeEvent(const QByteArray &, void *, long *)
// {
//     if(!bFirstView)
//         return false;

// //    int mes = reinterpret_cast<int>(message);
//     auto hwnd = reinterpret_cast<HWND>(winId());
//     m_showMainMenu = ::GetSystemMenu(hwnd, false);

//     QString menutxt = ui->actionShowMainMenuBar->text();

//     ::AppendMenu(m_showMainMenu, MF_SEPARATOR, IDM_SHOWMAINMENU-1, 0);
//     ::AppendMenu(m_showMainMenu, MF_STRING, IDM_SHOWMAINMENU,
//                  reinterpret_cast<LPCWSTR>(menutxt.utf16()));

// #ifdef _WIN64
//     DefStaticProc = (WNDPROC)GetWindowLongPtr(hwnd , GWLP_WNDPROC);
//     SetWindowLongPtr(hwnd , GWLP_WNDPROC , reinterpret_cast<LONG_PTR>(StaticProc));
// #else
//     DefStaticProc = (WNDPROC)GetWindowLongPtr(hwnd , GWL_WNDPROC);
//     SetWindowLongPtr(hwnd , GWL_WNDPROC , reinterpret_cast<LONG_PTR>(StaticProc));
// #endif
//     bFirstView = false;
//     return false;
// }


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
