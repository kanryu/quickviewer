#include "fullscreentopframe.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <Windows.h>
#include <windowsx.h>

FullscreenTopFrame::FullscreenTopFrame(MainWindow* mainWindow, Ui::MainWindow *ui_, QWidget *parent)
    : QMainWindow(parent)
    , m_mainWindow(mainWindow)
    , ui(ui_)
    , m_wasFullscreen(false)
    , m_mouseleft(false)
    , m_toShowNormal(false)
    , m_valid(true)
    , initializeCount(2)
{


    Qt::WindowFlags flags = windowFlags();
    flags |= Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint;
    setWindowFlags(flags);

//    qDebug() << ui->mainToolBar;
    addToolBar(Qt::TopToolBarArea, ui->mainToolBar);
    ui->mainToolBar->setVisible(true);
    setMenuBar(ui->menuBar);
    ui->menuBar->setVisible(true);

    setWindowTitle(mainWindow->windowTitle());
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    QRect rectMain = mainWindow->geometry();
    setGeometry(QRect(QPoint(rectMain.left()+2, rectMain.top()+2), QSize(100, 10)));

}

FullscreenTopFrame::~FullscreenTopFrame()
{
}

void FullscreenTopFrame::changeEvent(QEvent *event)
{
//    qDebug() << "FullscreenTopFrame::changeEvent";
    QWindowStateChangeEvent * winEvent=nullptr;
    if(event->type() == QEvent::WindowStateChange && (winEvent = dynamic_cast<QWindowStateChangeEvent*>(event)) != nullptr) {
//        qDebug() << winEvent << winEvent->oldState();
//        qDebug() << windowHandle()->windowState();
        switch(windowHandle()->windowState()) {
            case Qt::WindowMaximized:
                if(winEvent->oldState() == Qt::WindowMinimized) {
                    m_mainWindow->setVisible(true);
                    m_mouseleft = true;
                    close();
                    break;
                }
                // Since Qt::WindowMaximized is called twice and needs to be dealt with
                --initializeCount;
                if(initializeCount > 0) {
                    setMaximumHeight(size().height());
                } else {
                    auto hwnd = reinterpret_cast<HWND>(winId());
                    RECT rect;
                    ::GetWindowRect(hwnd, &rect);
                    QRect rectMain = m_mainWindow->geometry();
                    ::SetWindowPos(hwnd, HWND_TOPMOST, rectMain.left(), rectMain.top(), rectMain.width(), rect.bottom-rect.top, 0);

                    m_wasFullscreen = true;
                }
                break;
            case Qt::WindowMinimized:
                // Close the window while keeping the full screen mode.
                // Leave this window and hide the MainWindow
                m_mainWindow->setVisible(false);
                break;
            case Qt::WindowNoState:
                if(m_wasFullscreen) {
                    closeAndShowNormal();
                }
                break;
        }
    }
    return QMainWindow::changeEvent(event);
}

void FullscreenTopFrame::closeAndShowNormal()
{
    m_toShowNormal = true;
    close();
}

void FullscreenTopFrame::moveEvent(QMoveEvent *event)
{
//    qDebug() << "FullscreenTopFrame::moveEvent";
    if(isMaximized()) {
        event->ignore();
        return;
    }
    return QMainWindow::moveEvent(event);
}


// This method is used because QShowEvent may not be called
bool FullscreenTopFrame::nativeEvent(const QByteArray &, void *message, long *result)
{
    MSG *msg = reinterpret_cast<MSG*>(message);
    auto hwnd = msg->hwnd;
    // Only react when the mouse cursor moves below the window
    if(msg->message == WM_NCMOUSELEAVE && cursor().pos().y() > 30) {
        m_mouseleft = true;
        close();
    }
    // Prevent movement of the window by dragging the title bar of FullscreenTopFrame
    if(isMaximized() && (msg->message == WM_NCLBUTTONDOWN || msg->message == WM_NCLBUTTONUP)) {
        LRESULT hitid = ::DefWindowProcW(hwnd, WM_NCHITTEST, 0, msg->lParam);
//        qDebug() << hitid << QPoint(GET_X_LPARAM(msg->lParam), GET_Y_LPARAM(msg->lParam));
        if(hitid != HTCAPTION)
            return false;
        *result = 0;
        return true;
    }
    return false;
}

void FullscreenTopFrame::closeEvent(QCloseEvent *event)
{
//    qDebug() << "FullscreenTopFrame::closeEvent";
    m_valid = false;
    m_mainWindow->addToolBar(ui->mainToolBar);
    m_mainWindow->setMenuBar(ui->menuBar);
    if(m_toShowNormal) {
        m_mainWindow->on_fullscreen_triggered();
        return;
    }
    ui->menuBar->setVisible(false);
    ui->mainToolBar->setVisible(false);

    if(!m_mouseleft) {
        m_mainWindow->close();
    }
    QMainWindow::closeEvent(event);
}
