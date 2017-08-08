#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QtWidgets>

namespace Ui {
class OptionsDialog;
}


class OptionsDialog : public QDialog
{
    Q_OBJECT
public:
    OptionsDialog(QWidget *parent);
    ~OptionsDialog();
    void reflectResults();
    void resetColorButton(QPushButton* btn, QColor color);
    void resetColorBox();

public slots:
    void onBtnColorSelect_clicked();
    void onBtnColorSelect2_clicked();
    void onCheckBoxCheckeredPattern_clicked(bool enabled);

private:
    Ui::OptionsDialog *ui;

    int m_slideShowWait;
    int m_maxVolumesCache;
    QColor m_backgroundColor;
    QColor m_backgroundColor2;
    bool m_useCheckeredPattern;
};

#endif // OPTIONSDIALOG_H
