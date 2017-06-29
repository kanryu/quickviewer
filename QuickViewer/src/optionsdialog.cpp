#include "optionsdialog.h"
#include "ui_optionsdialog.h"
#include "qvapplication.h"

OptionsDialog::OptionsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::OptionsDialog)
{
    ui->setupUi(this);

    ui->spinSlideshow->setValue(qApp->SlideShowWait());
    ui->spinVolumes->setValue(qApp->MaxVolumesCache());
}

OptionsDialog::~OptionsDialog()
{

}

void OptionsDialog::reflectResults()
{
    qApp->setSlideShowWait(ui->spinSlideshow->value());
    qApp->setMaxVolumesCache(ui->spinVolumes->value());
}
