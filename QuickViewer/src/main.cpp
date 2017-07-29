#include <QtCore>

#include "qv_init.h"
#include "qvapplication.h"
#include "thumbnailmanager.h"
#include "qnamedpipe.h"

#if defined(Q_OS_WIN)
  #include "mainwindowforwindows.h"
#else
  #include "mainwindow.h"
#endif

int main(int argc, char *argv[])
{
    QVApplication app(argc, argv);
    app.myInstallTranslator();

    QNamedPipe pipe(app.applicationName(), qApp->ProhibitMultipleRunning());
    if(!pipe.isServerMode()) {
        qDebug() << app.arguments();
        if(app.arguments().length() > 1) {
            pipe.sendMessage(app.arguments()[1].toUtf8());
        } else
            pipe.sendMessage("0");
        return 0;
    }
    pipe.waitAsync();

#ifdef Q_OS_WIN
    MainWindowForWindows w;
#else
    MainWindow w;
#endif
    ThumbnailManager manager(&w, app.CatalogDatabasePath());
    w.setThumbnailManager(&manager);
    w.connect(&pipe, SIGNAL(open(QString)), &w, SLOT(on_openVolumeByCatalog_triggered(QString)));
    w.connect(&pipe, SIGNAL(beetUp()), &w, SLOT(on_windowTop()));
    w.show();

    return app.exec();
}
