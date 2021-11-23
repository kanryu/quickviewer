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
#ifdef Q_OS_WIN
    {
        // Activate the direct2d QPA plugin when 'UseDirect2D' of quickviewer.ini is true.
        // Since initialization of QPA is processed in the constructor of QGuiApplication,
        // it must be set to the QT_QPA_PLATFORM environment variable before that.
#  ifdef QV_PORTABLE
        QString inipath = QDir::toNativeSeparators(QFileInfo(argv[0]).path());
        QDir iniSubDir = QDir(inipath + "\\" CONFIG_SUBDIR);
        if (iniSubDir.exists()) {
        	inipath += "\\" CONFIG_SUBDIR;
        }
        inipath += "\\" APP_INI;
#  else
        QString inipath = QDir(QStandardPaths::writableLocation(QStandardPaths::DataLocation)).filePath(APP_INI);
#  endif
        std::wstring winipath = inipath.toStdWString();
        WCHAR value[128];
        qDebug() << ::GetPrivateProfileString(L"View", L"UseDirect2D", L"false", value, sizeof(value)-1, winipath.c_str());
        if(::lstrcmp(value, L"true")==0)
            qputenv("QT_QPA_PLATFORM", "direct2d");
    }
#elif defined(Q_OS_MAC)
    {
        // hide icons on application menu.
        QApplication::instance()->setAttribute(Qt::AA_DontShowIconsInMenus, true);
    }
#endif

    QVApplication app(argc, argv);
    app.setEffectEnabled(Qt::UI_AnimateCombo, false);
    app.myInstallTranslator();
    int result = 0;
    {
        QNamedPipe pipe(app.applicationName(), qApp->ProhibitMultipleRunning());
        if(!pipe.isServerMode()) {
            qDebug() << app.arguments();
            if(app.arguments().length() > 1) {
                pipe.send(app.arguments()[1].toUtf8());
            } else
                pipe.send("b");
            return 0;
        }
        pipe.waitAsync();

#ifdef Q_OS_WIN
        MainWindowForWindows w;
#else
        MainWindow w;
#endif
        QString dbpath = app.CatalogDatabasePath();
        ThumbnailManager manager(&w, dbpath);
        w.setThumbnailManager(&manager);
        w.connect(&pipe, &QNamedPipe::received, &w, [&](QByteArray bytes) {
            if(bytes.size() == 1) {
                w.setWindowTop(false);
            }
            else if(bytes.size() > 0) {
                auto string = QString::fromUtf8(bytes);
                w.loadVolumeWithAssoc(string);
            }
        });
        w.show();
        result = app.exec();
    }
    return result;
}
