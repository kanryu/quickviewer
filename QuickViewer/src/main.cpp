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
#if defined(Q_OS_WIN)
    {
        // Activate the direct2d QPA plugin when 'UseDirect2D' of quickviewer.ini is true.
        // Since initialization of QPA is processed in the constructor of QGuiApplication,
        // it must be set to the QT_QPA_PLATFORM environment variable before that.
        QString inipath = QDir::toNativeSeparators(QFileInfo(argv[0]).path());
        inipath += "\\" APP_INI;
        std::wstring winipath = inipath.toStdWString();
        WCHAR value[128];
        qDebug() << ::GetPrivateProfileString(L"View", L"UseDirect2D", L"false", value, sizeof(value)-1, winipath.c_str());
        if(::lstrcmp(value, L"true")==0)
            qputenv("QT_QPA_PLATFORM", "direct2d");
    }
#endif
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
    w.connect(&pipe, SIGNAL(open(QString)), &w, SLOT(onCatalogWindow_openVolume(QString)));
    w.connect(&pipe, SIGNAL(beetUp()), &w, SLOT(on_windowTop()));
    w.show();

    return app.exec();
}
