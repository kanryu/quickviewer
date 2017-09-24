#include "optionsdialog.h"
#include "ui_optionsdialog.h"
#include "qvapplication.h"

OptionsDialog::OptionsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::OptionsDialog)
{
    ui->setupUi(this);
#ifndef Q_OS_WIN
    ui->checkBoxUseDirect2D->setVisible(false);
#endif
    m_slideShowWait = qApp->SlideShowWait();
    m_maxVolumesCache = qApp->MaxVolumesCache();
    m_backgroundColor = qApp->BackgroundColor();
    m_backgroundColor2 = qApp->BackgroundColor2();
    m_useCheckeredPattern = qApp->UseCheckeredPattern();

    ui->spinSlideshow->setValue(m_slideShowWait);
    ui->spinVolumes->setValue(m_maxVolumesCache);
    ui->spinImages->setValue(qApp->MaxImagesCache());
    ui->spinMaxTextureSize->setValue(qApp->MaxTextureSize());
    ui->checkBoxCheckeredPattern->setChecked(m_useCheckeredPattern);
    ui->checkBoxUseFastDctForJPEG->setChecked(qApp->UseFastDCTForJPEG());
    ui->checkBoxProhibitMultipleRunning->setChecked(qApp->ProhibitMultipleRunning());
    ui->checkBoxUseDirect2D->setChecked(qApp->UseDirect2D());
    ui->checkBoxHidePageBarParmanently->setChecked(qApp->HidePageBarParmanently());
    ui->checkBoxHideScrollBarInFullscreen->setChecked(qApp->HideScrollBarInFullscreen());

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
    qApp->setMaxImagesCache(ui->spinImages->value());
    qApp->setMaxTextureSize(ui->spinMaxTextureSize->value());
    qApp->setBackgroundColor(m_backgroundColor);
    qApp->setBackgroundColor2(m_backgroundColor2);
    qApp->setUseCheckeredPattern(m_useCheckeredPattern);
    qApp->setUseFastDCTForJPEG(ui->checkBoxUseFastDctForJPEG->isChecked());
    qApp->setProhibitMultipleRunning(ui->checkBoxProhibitMultipleRunning->isChecked());
    qApp->setUseDirect2D(ui->checkBoxUseDirect2D->isChecked());
    qApp->setHidePageBarParmanently(ui->checkBoxHidePageBarParmanently->isChecked());
    qApp->setHideScrollBarInFullscreen(ui->checkBoxHideScrollBarInFullscreen->isChecked());
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

void OptionsDialog::onBtnColorSelect_clicked()
{
    QColorDialog dialog(this);
    dialog.setCurrentColor(m_backgroundColor);
    if(dialog.exec() == QDialog::Accepted) {
        m_backgroundColor = dialog.currentColor();
        resetColorButton(ui->btnColorSelect, m_backgroundColor);
        resetColorBox();
    }
}

void OptionsDialog::onBtnColorSelect2_clicked()
{
    QColorDialog dialog(this);
    dialog.setCurrentColor(m_backgroundColor2);
    if(dialog.exec() == QDialog::Accepted) {
        m_backgroundColor2 = dialog.currentColor();
        resetColorButton(ui->btnColorSelect2, m_backgroundColor2);
        resetColorBox();
    }
}

void OptionsDialog::onCheckBoxCheckeredPattern_clicked(bool enabled)
{
    m_useCheckeredPattern = enabled;
    resetColorBox();
}
