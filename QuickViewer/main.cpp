#include "mainwindow.h"
#include "qv_init.h"
#include "qvapplication.h"

int main(int argc, char *argv[])
{
    QVApplication app(argc, argv);

    MainWindow w;
    w.show();

    return app.exec();
}
