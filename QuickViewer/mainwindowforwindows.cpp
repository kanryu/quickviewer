#include <QWindow>
#include <QMenuBar>
#include <qpa/qplatformnativeinterface.h>

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

// This method is used because QShowEvent may not be called
bool MainWindowForWindows::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    if(!bFirstView)
        return false;

    int mes = (int)message;
    QWindow* window = windowHandle();
    if (!window) {
        const QWidget* f_native_parent = nativeParentWidget();
        if (f_native_parent)
            window = f_native_parent->windowHandle();
    }
    HWND hwnd = static_cast<HWND>(QGuiApplication::platformNativeInterface()
                                    ->nativeResourceForWindow(QByteArrayLiteral("handle"), window));
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
