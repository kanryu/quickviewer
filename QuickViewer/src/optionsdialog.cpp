#include "optionsdialog.h"
#include "ui_optionsdialog.h"
#include "qvapplication.h"

OptionsDialog::OptionsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::OptionsDialog)
{
    ui->setupUi(this);

    m_slideShowWait = qApp->SlideShowWait();
    m_maxVolumesCache = qApp->MaxVolumesCache();
    m_backgroundColor = qApp->BackgroundColor();
    m_backgroundColor2 = qApp->BackgroundColor2();
    m_useCheckeredPattern = qApp->UseCheckeredPattern();

    ui->spinSlideshow->setValue(m_slideShowWait);
    ui->spinVolumes->setValue(m_maxVolumesCache);
    ui->checkBoxCheckeredPattern->setChecked(m_useCheckeredPattern);
    ui->checkBoxProhibitMultipleRunning->setChecked(qApp->ProhibitMultipleRunning());

    resetColorButton(ui->btnColorSelect, m_backgroundColor);
    resetColorButton(ui->btnColorSelect2, m_backgroundColor2);
    resetColorBox();
}

OptionsDialog::~OptionsDialog()
{

}

void OptionsDialog::reflectResults()
{
    qApp->setSlideShowWait(ui->spinSlideshow->value());
    qApp->setMaxVolumesCache(ui->spinVolumes->value());
    qApp->setBackgroundColor(m_backgroundColor);
    qApp->setBackgroundColor2(m_backgroundColor2);
    qApp->setUseCheckeredPattern(m_useCheckeredPattern);
    qApp->setProhibitMultipleRunning(ui->checkBoxProhibitMultipleRunning->isChecked());
}

void OptionsDialog::resetColorButton(QPushButton* btn, QColor color)
{
    QPixmap pix(16, 16);
    pix.fill(color);
    QIcon icon(pix);
    btn->setIcon(icon);
}

void OptionsDialog::resetColorBox()
{
    QPixmap pattern(48, 48);
    QBrush brush;
    if(!m_useCheckeredPattern) {
        brush = QBrush(m_backgroundColor, Qt::SolidPattern);

        ui->labelColor2->setEnabled(false);
        ui->btnColorSelect2->setEnabled(false);
    } else {
        QPixmap pix(16, 16);
        pix.fill(m_backgroundColor);
        QPainter paint(&pix);
        QBrush brush2(m_backgroundColor2, Qt::SolidPattern);
        paint.fillRect(QRect(0, 0, 8, 8), brush2);
        paint.fillRect(QRect(8, 8, 8, 8), brush2);
        brush = QBrush(pix);

        ui->labelColor2->setEnabled(true);
        ui->btnColorSelect2->setEnabled(true);
    }
    QPainter paint(&pattern);
    paint.fillRect(QRect(0, 0, 48, 48), brush);
    ui->labelBgSample->setPixmap(pattern);
}

void OptionsDialog::on_changeColor_triggered()
{
    QColorDialog dialog(this);
    dialog.setCurrentColor(m_backgroundColor);
    if(dialog.exec() == QDialog::Accepted) {
        m_backgroundColor = dialog.currentColor();
        resetColorButton(ui->btnColorSelect, m_backgroundColor);
        resetColorBox();
    }
}

void OptionsDialog::on_changeColor2_triggered()
{
    QColorDialog dialog(this);
    dialog.setCurrentColor(m_backgroundColor2);
    if(dialog.exec() == QDialog::Accepted) {
        m_backgroundColor2 = dialog.currentColor();
        resetColorButton(ui->btnColorSelect2, m_backgroundColor2);
        resetColorBox();
    }
}

void OptionsDialog::on_useCheckeredPattern_triggered(bool enabled)
{
    m_useCheckeredPattern = enabled;
    resetColorBox();
}
