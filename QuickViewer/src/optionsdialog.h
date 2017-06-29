#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QtWidgets>

namespace Ui {
class OptionsDialog;
}


class OptionsDialog : public QDialog
{
public:
    OptionsDialog(QWidget *parent);
    ~OptionsDialog();

    void reflectResults();

private:
    Ui::OptionsDialog *ui;
};

#endif // OPTIONSDIALOG_H
