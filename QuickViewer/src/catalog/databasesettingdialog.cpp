#include "databasesettingdialog.h"
#include "ui_createdb.h"
#include <QButtonGroup>
#include <QFileDialog>

DatabaseSettingDialog::DatabaseSettingDialog(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::DatabaseSettingDialog)

{
    ui->setupUi(this);
    setAcceptDrops(true);

}

DatabaseSettingDialog::~DatabaseSettingDialog()
{
    delete ui;
}

int DatabaseSettingDialog::exec()
{
    if(!m_name.isEmpty())
        ui->nameEdit->setText(m_name);
    if(!m_path.isEmpty())
        ui->pathEdit->setText(m_path);
    if(m_editing) {
        ui->pathEdit->setEnabled(false);
        ui->selectFolderButton->setEnabled(false);
        setAcceptDrops(false);
    }
    checkAcceptable();
    return QDialog::exec();
}

void DatabaseSettingDialog::dragEnterEvent(QDragEnterEvent *e)
{
    if(e->mimeData()->hasFormat("text/uri-list"))
    {
        e->acceptProposedAction();
    }
}
void DatabaseSettingDialog::dropEvent(QDropEvent *e)
{
    if(e->mimeData()->hasUrls())
        return;
    QList<QUrl> urlList = e->mimeData()->urls();
    for (int i = 0; i < 1; i++) {
        QUrl url = urlList[i];
        QFileInfo info(url.toLocalFile());
        if(info.isDir()) {
            ui->pathEdit->setText(QDir::toNativeSeparators(info.absoluteFilePath()));
            if(ui->nameEdit->text().isEmpty())
                ui->nameEdit->setText(info.fileName());
        } else if(info.isFile()) {
            ui->pathEdit->setText(QDir::toNativeSeparators(info.path()));
            if(ui->nameEdit->text().isEmpty())
                ui->nameEdit->setText(info.baseName());
        }
    }
}

void DatabaseSettingDialog::checkAcceptable()
{
    bool enabled = false;
    do {
        if(m_name.isEmpty())
            break;
        if(m_path.isEmpty() || !QFileInfo(m_path).exists())
            break;
        enabled = true;
    } while(false);

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(enabled);
}

void DatabaseSettingDialog::onNameEdit_textChanged(QString name)
{
     setName(name);
     checkAcceptable();
}

void DatabaseSettingDialog::onSelectFolderButton_clicked()
{
    QString folder = QFileDialog::getExistingDirectory(this, tr("Please select a folder containing Images or Archives", "Caption of FolderSelectDialog urging selection of folders containing Images and Archives"));
    if(!folder.isEmpty()) {
        ui->pathEdit->setText(folder);
    }
}
