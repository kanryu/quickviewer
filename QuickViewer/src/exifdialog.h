#ifndef EXIFDIALOG_H
#define EXIFDIALOG_H

#include <QDialog>
#include "exif.h"

namespace Ui {
class ExifDialog;
}

class ExifDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExifDialog(QWidget *parent = 0);
    ~ExifDialog();

    void setExif(const easyexif::EXIFInfo& info);

private:
    Ui::ExifDialog *ui;
    QString generateFlash(char flash);
    QString generateOrientation(unsigned short orient);
};

#endif // EXIFDIALOG_H
