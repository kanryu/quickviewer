#include <QtCore>

#include "qv_init.h"
#include "qvapplication.h"
#include "thumbnailmanager.h"

#if defined(Q_OS_WIN)
  #include "mainwindowforwindows.h"
#else
  #include "mainwindow.h"
#endif

int main(int argc, char *argv[])
{
    QVApplication app(argc, argv);

    // multi-language-support
//    QTranslator translator;
//    bool exist = translator.load(QLocale(qApp->UiLanguage()),
//                                 "translations/", "quickviewer_", qApp->applicationDirPath());
//    if(exist) {
//        app.installTranslator(&translator);
//    }
    app.myInstallTranslator();
#ifdef Q_OS_WIN
    MainWindowForWindows w;
#else
    MainWindow w;
#endif
    ThumbnailManager manager(&w, app.CatalogDatabasePath());
    w.setThumbnailManager(&manager);
    w.show();

    return app.exec();
}
