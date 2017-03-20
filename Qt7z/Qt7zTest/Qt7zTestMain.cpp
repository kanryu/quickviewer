#include <QCoreApplication>
#include <QTest>

#include "TestQt7zPackage.h"

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    int err = 0;
    {
        TestQt7zPackage testQt7zPackage;
        err = qMax(err, QTest::qExec(&testQt7zPackage, app.arguments()));
    }

    if (err != 0) {
        qWarning("There were errors in some of the tests above.");
    }

    return err;
}
