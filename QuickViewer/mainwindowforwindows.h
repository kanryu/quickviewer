#ifndef MAINWINDOWFORWINDOWS_H
#define MAINWINDOWFORWINDOWS_H

#include "mainwindow.h"
#include <Windows.h>

class MainWindowForWindows : public MainWindow
{
public:
    explicit MainWindowForWindows(QWidget *parent = 0);
    bool moveToTrush(QString path);

public slots:
//    void showEvent(QShowEvent * event);
//    void focusInEvent(QFocusEvent * event);
//    void enterEvent(QEnterEvent* event);
//    bool winEvent(MSG * message, long * result);
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);

private:
    bool bFirstView;
    HMENU m_showMainMenu; // HMENU

    static MainWindowForWindows* MainWindowForWindows_self;
    static WNDPROC DefStaticProc;
    static LRESULT CALLBACK StaticProc(HWND hwnd , UINT msg , WPARAM wp , LPARAM lp);
};

#endif // MAINWINDOWFORWINDOWS_H
