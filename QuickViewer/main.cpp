#ifdef WIN32
  #include "mainwindowforwindows.h"
#else
  #include "mainwindow.h"
#endif
#include "qv_init.h"
#include "qvapplication.h"
#include <QTranslator>

int main(int argc, char *argv[])
{
    QVApplication app(argc, argv);

    // multi-language-support
    QTranslator translator;
    QString tr_filename = QString("translations/quickviewer_%1.qm").arg(QLocale::system().name());
    bool exist = translator.load(tr_filename);
    if(exist) {
        app.installTranslator(&translator);
    }
#ifdef WIN32
    MainWindowForWindows w;
#else
    MainWindow w;
#endif
    w.show();

    return app.exec();
}
