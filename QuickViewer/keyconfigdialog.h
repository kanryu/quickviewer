#ifndef KEYCONFIGDIALOG_H
#define KEYCONFIGDIALOG_H

#include <QDialog>

namespace Ui {
class ExifDialog;
}
class KeyConfigDialog : public QDialog
{
    Q_OBJECT
public:
    explicit KeyConfigDialog(QWidget *parent = 0);
    ~KeyConfigDialog();

signals:

public slots:

private:
    Ui::ExifDialog *ui;
};


#endif // KEYCONFIGDIALOG_H
