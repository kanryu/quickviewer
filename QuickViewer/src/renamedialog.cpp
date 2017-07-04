#include "renamedialog.h"
#include "ui_renamedialog.h"

RenameDialog::RenameDialog(QWidget *parent, QString path, QString filename)
    : QDialog(parent)
    , ui(new Ui::RenameDialog)
{
    ui->setupUi(this);
    m_path = QDir::toNativeSeparators(path);
    m_filename = filename;
    ui->editFilename->setText(m_filename);
    ui->labelErrorMessage->setVisible(false);
}

QString RenameDialog::newName()
{
    return ui->editFilename->text();
}

void RenameDialog::on_textChanged_triggered(QString text)
{
//    QDir dir(m_path);
//    QFileInfo info(QDir::toNativeSeparators(dir.absoluteFilePath(text)));
//    info.exists();
    if(text.isEmpty()) {
        ui->labelErrorMessage->setText(tr("Filename can't be empty."));
        ui->labelErrorMessage->setVisible(true);
    } else {
        ui->labelErrorMessage->setVisible(false);
    }
}

void RenameDialog::on_tryChangingFilenameAndAccept_triggered()
{
    QDir dir(m_path);
    if(dir.rename(m_filename, ui->editFilename->text())) {
        accept();
        return;
    }
    ui->labelErrorMessage->setText(tr("Rename failed. Does the same file name exist?"));
    ui->labelErrorMessage->setVisible(true);
}
