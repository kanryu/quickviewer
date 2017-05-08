#include <Windows.h>
#include <Shellapi.h>
#include <QDebug>

#include "qvapplication.h"
#include "mainwindowforwindows.h"
#include "ui_mainwindow.h"

#define IDM_SHOWMAINMENU 2

MainWindowForWindows* MainWindowForWindows::MainWindowForWindows_self;
WNDPROC MainWindowForWindows::DefStaticProc;

MainWindowForWindows::MainWindowForWindows(QWidget *parent)
    : MainWindow(parent), bFirstView(true)
{
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
    ::SetWindowPos(hwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
}

// This method is used because QShowEvent may not be called
bool MainWindowForWindows::nativeEvent(const QByteArray &, void *, long *)
{
    if(!bFirstView)
        return false;

//    int mes = reinterpret_cast<int>(message);
    auto hwnd = reinterpret_cast<HWND>(winId());
    m_showMainMenu = ::GetSystemMenu(hwnd, false);

    QString menutxt = tr("Sh&ow/Hide MainMenuBar");

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
