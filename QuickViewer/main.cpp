#include <QTranslator>
#include <QDebug>
#include "qv_init.h"
#include "qvapplication.h"

#if defined(Q_OS_WIN)
  #include "mainwindowforwindows.h"
#else
  #include "mainwindow.h"
#endif

int main(int argc, char *argv[])
{
    QVApplication app(argc, argv);

    // multi-language-support
    QTranslator translator;
    bool exist = translator.load(QLocale::system(),
                                 "translations/", "quickviewer_", qApp->applicationDirPath());
    if(exist) {
        app.installTranslator(&translator);
    }
#ifdef Q_OS_WIN
    MainWindowForWindows w;
#else
    MainWindow w;
#endif
    w.show();

    return app.exec();
}
