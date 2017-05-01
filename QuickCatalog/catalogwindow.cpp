#include "catalogwindow.h"
#include "ui_catalogwindow.h"

CatalogWindow::CatalogWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CatalogWindow)
{
    ui->setupUi(this);

    ui->folderTree->setRootPath("C:/Program Files");

}

CatalogWindow::~CatalogWindow()
{
    delete ui;
}

void CatalogWindow::on_treeItemChanged(QString path)
{
    ui->pathCombo->setCurrentText(QDir::toNativeSeparators(path));
}
