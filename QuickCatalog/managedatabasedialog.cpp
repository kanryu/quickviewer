#include "managedatabasedialog.h"
#include "databasesettingdialog.h"
#include "ui_cataloglist.h"
#include "qc_init.h"

ManageDatabaseDialog::ManageDatabaseDialog(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::ManageDatabaseDialog)
{
    ui->setupUi(this);
    ui->progressBar->setVisible(false);

    ui->treeWidget->sortByColumn(1, Qt::DescendingOrder);
    QTreeWidgetItem *header = ui->treeWidget->headerItem();
    header->setText(0, tr("Name"));
    header->setText(1, tr("Created"));
    header->setText(2, tr("Path"));
    header->setHidden(false);

    // REMOVE ME
    auto catalog = CatalogRecord();
    catalog.id = 333;
    catalog.name = "a";
    catalog.created_at = QDateTime::currentDateTime();
    catalog.path = "b";
    m_catalogs[catalog.id] = catalog;

    resetCatalogList();

}

ManageDatabaseDialog::~ManageDatabaseDialog()
{
    delete ui;
}

void ManageDatabaseDialog::resetCatalogList()
{
    ui->treeWidget->clear();
    foreach(int id, m_catalogs.keys()) {
        const CatalogRecord& catalog = m_catalogs[id];
        QTreeWidgetItem* item = new QTreeWidgetItem;
        item->setText(0, catalog.name);
        item->setText(1, ThumbnailManager::DateTimeToIsoString(catalog.created_at));
        item->setText(2, catalog.path);
        item->setData(0, Qt::UserRole, QVariant(catalog.id));
        ui->treeWidget->addTopLevelItem(item);
    }
    if(m_catalogs.isEmpty()) {
        ui->editButton->setEnabled(false);
        ui->deleteButton->setEnabled(false);
        ui->updateButton->setEnabled(false);
        ui->deleteAllButton->setEnabled(false);
        ui->updateAllButton->setEnabled(false);
    } else {
        ui->editButton->setEnabled(true);
        ui->deleteButton->setEnabled(true);
        ui->updateButton->setEnabled(true);
        ui->deleteAllButton->setEnabled(true);
        ui->updateAllButton->setEnabled(true);
    }
}

void ManageDatabaseDialog::on_addNew_triggered()
{
    if(!m_thumbManager)
        return;
    DatabaseSettingDialog dialog(this);
    int result = dialog.exec();
    if(result == QDialog::Rejected) {
        return;
    }
    CatalogRecord catalog = m_thumbManager->createCatalog(dialog.name(), dialog.path());
    m_catalogs[catalog.id] = catalog;

    resetCatalogList();
}

void ManageDatabaseDialog::on_edit_triggered()
{
    if(!m_thumbManager)
        return;
    QTreeWidgetItem *current = ui->treeWidget->currentItem();
    if(!current)
        return;

    int id = current->data(0, Qt::UserRole).toInt();
    CatalogRecord catalog = m_catalogs[id];
    DatabaseSettingDialog dialog(this);
    dialog.setName(catalog.name);
    dialog.setPath(catalog.path);

    int result = dialog.exec();
    if(result == QDialog::Rejected) {
        return;
    }
    catalog.name = dialog.name();
    m_thumbManager->updateCatalogName(id, catalog.name);
    m_catalogs[id] = catalog;

    resetCatalogList();
}

void ManageDatabaseDialog::on_delete_triggered()
{
    if(!m_thumbManager)
        return;
    QTreeWidgetItem *current = ui->treeWidget->currentItem();
    if(!current)
        return;
    int id = current->data(0, Qt::UserRole).toInt();
    m_thumbManager->deleteCatalog(id);
    m_catalogs.remove(id);

    resetCatalogList();
}

void ManageDatabaseDialog::on_update_triggered()
{

}

void ManageDatabaseDialog::on_deleteAll_triggered()
{
    if(!m_thumbManager)
        return;
    m_thumbManager->deleteAllCatalogs();
    m_catalogs.clear();

    resetCatalogList();
}

void ManageDatabaseDialog::on_updateAll_triggered()
{

}
