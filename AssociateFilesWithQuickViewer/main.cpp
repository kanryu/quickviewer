#include "fileassocdialog.h"
#include <QApplication>
#include "qlanguageselector.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QLanguageSelector selector("quickviewer_", "translations/");
    selector.resetTranslator("");

    FileAssocDialog w;
    w.show();

    return a.exec();
}
