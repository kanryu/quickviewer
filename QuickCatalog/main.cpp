#include "catalogwindow.h"
#include "managedatabasedialog.h"
#include "thumbnailmanager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CatalogWindow w;
    ThumbnailManager manager(&w, "database/thumbnail.sqlite3.db");
    w.setThumbnailManager(&manager);
    w.show();
//    ManageDatabaseDialog d;
//    ThumbnailManager manager(&d, "database/thumbnail.sqlite3.db");
//    d.setThumbnailManager(&manager);
//    d.show();

    return a.exec();
}
