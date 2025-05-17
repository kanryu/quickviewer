#include <QMessageBox>

#include "managedatabasedialog.h"
#include "databasesettingdialog.h"
#include "ui_cataloglist.h"
#include "qc_init.h"

ManageDatabaseDialog::ManageDatabaseDialog(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::ManageDatabaseDialog)
    , m_catalogWatcher(nullptr)
{
    ui->setupUi(this);
    ui->progressBar->setVisible(false);
    qRegisterMetaType<CatalogRecord>("CatalogRecord");

    // CatalogTree
    ui->treeWidget->sortByColumn(1, Qt::DescendingOrder);
    QTreeWidgetItem *header = ui->treeWidget->headerItem();
    header->setText(0, tr("Name", "Title of the column in the list part of the folder registered as Catalog"));
    header->setText(1, tr("CreationTime", "Title of the column in the list part of the folder registered as Catalog"));
    header->setText(2, tr("Path", "Title of the column in the list part of the folder registered as Catalog"));
    header->setHidden(false);

    // Buttons
    ui->updateAllButton->setVisible(false);
    ui->updateButton->setVisible(false);

    resetCatalogList();

}

ManageDatabaseDialog::~ManageDatabaseDialog()
{
    delete ui;
}

void ManageDatabaseDialog::setThumbnailManager(ThumbnailManager* manager)
{
     m_thumbManager = manager;
     m_catalogs = m_thumbManager->catalogs();
     resetCatalogList();
     normalButtonStates();
}

void ManageDatabaseDialog::normalButtonStates()
{
    ui->addButton->setEnabled(true);
    if(m_catalogs.isEmpty() && m_makeCatalogs.isEmpty()) {
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
    ui->buttonBox->setEnabled(true);

    if(m_makeCatalogs.size() == 0) {
        ui->cancelButton->setVisible(false);
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    } else {
        ui->cancelButton->setVisible(true);
        ui->cancelButton->setText(tr("Start Work", "Button to start catalog creation for specified folder"));
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
    ui->progressBar->setVisible(false);
    ui->volumeNameLabel->setVisible(false);
}

void ManageDatabaseDialog::progressButtonStates()
{
    ui->addButton->setEnabled(false);
    ui->editButton->setEnabled(false);
    ui->deleteButton->setEnabled(false);
    ui->updateButton->setEnabled(false);
    ui->deleteAllButton->setEnabled(false);
    ui->updateAllButton->setEnabled(false);
    ui->buttonBox->setEnabled(false);

    ui->progressBar->setVisible(true);
    ui->cancelButton->setText(tr("Cancel Work", "Button to cancel the catalog being generated"));
    ui->cancelButton->setVisible(true);
    ui->volumeNameLabel->setVisible(true);
}

void ManageDatabaseDialog::resetCatalogList()
{
    ui->treeWidget->clear();
    // Existing catalogs
    foreach(int id, m_catalogs.keys()) {
        const CatalogRecord& catalog = m_catalogs[id];
        QTreeWidgetItem* item = new QTreeWidgetItem;
        item->setText(0, catalog.name);
        item->setText(1, ThumbnailManager::DateTimeToIsoString(catalog.created_at));
        item->setText(2, catalog.path);
        item->setData(0, Qt::UserRole, QVariant(catalog.id));
        ui->treeWidget->addTopLevelItem(item);
    }
    // Making catalogs
    {
        int cnt = -100;
        foreach(const CatalogRecord& catalog, m_makeCatalogs) {
            QTreeWidgetItem* item = new QTreeWidgetItem;
            item->setText(0, "* "  + catalog.name);
            item->setText(1, tr("approach to", "Representation of time indicating that the catalog is not currently created and will be generated from now"));
            item->setText(2, catalog.path);
            item->setData(0, Qt::UserRole, cnt--);
            item->setBackground(0, QBrush(QColor("lightgreen")));
            QFont font = item->font(0);
            font.setItalic(true);
            item->setFont(0, font);
            ui->treeWidget->addTopLevelItem(item);
        }
    }
}

void ManageDatabaseDialog::dragEnterEvent(QDragEnterEvent *e)
{
    if(e->mimeData()->hasFormat("text/uri-list"))
    {
        e->acceptProposedAction();
    }
}

void ManageDatabaseDialog::onAddButton_clicked()
{
    CatalogRecord catalog = {0};
    if(!databaseSettingDialog(catalog, false))
        return;
    m_makeCatalogs << catalog;

    resetCatalogList();
    normalButtonStates();
}

void ManageDatabaseDialog::dropEvent(QDropEvent *e)
{
    if(!e->mimeData()->hasUrls())
        return;
    QList<QUrl> urlList = e->mimeData()->urls();
    for (int i = 0; i < urlList.size(); i++) {
        QUrl url = urlList[i];
        QFileInfo info(url.toLocalFile());
        CatalogRecord catalog = {0};
        if(info.isDir()) {
//            createCatalog(info.fileName(), QDir::toNativeSeparators(info.absoluteFilePath()));
            catalog.name = info.fileName();
            catalog.path = QDir::toNativeSeparators(info.absoluteFilePath());
        } else if(info.isFile()) {
//            createCatalog(info.baseName(), QDir::toNativeSeparators(info.path()));
            catalog.name = info.baseName();
            catalog.path = QDir::toNativeSeparators(info.path());
        }
        m_makeCatalogs << catalog;
    }

    resetCatalogList();
    normalButtonStates();
}

bool ManageDatabaseDialog::databaseSettingDialog(CatalogRecord& catalog, bool editing)
{
    DatabaseSettingDialog dialog(this);
    dialog.setName(catalog.name);
    dialog.setPath(catalog.path);
    dialog.setForEditing(editing);
    if(editing)
        dialog.setWindowTitle(tr("Edit Catalog", "Button for editing contents of already created catalog"));

    int result = dialog.exec();
    if(result == QDialog::Rejected) {
        return false;
    }
    catalog.name = dialog.name();
    catalog.path = dialog.path();
    return true;
}

void ManageDatabaseDialog::createCatalog()
{
    if(!m_thumbManager)
        return;
}

void ManageDatabaseDialog::on_catalogCreated(const CatalogRecord cr)
{
    if(!cr.created)
        return;
    m_catalogs[cr.id] = cr;
    int i = 0;
    foreach(const CatalogRecord& c, m_makeCatalogs) {
        if(cr.path == c.path)
            break;
        i++;
    }
    if(i < m_makeCatalogs.size()) {
        m_makeCatalogs.removeAt(i);
    }

    resetCatalogList();
}

void ManageDatabaseDialog::on_catalogCreateFinished()
{
    if(!m_catalogWatcher)
        return;
    disconnect(m_thumbManager, SIGNAL(catalogCreated(CatalogRecord)), this, SLOT(on_catalogCreated(CatalogRecord)));
    disconnect(m_catalogWatcher, SIGNAL(finished()), this, SLOT(on_catalogCreateFinished()));
    disconnect(m_catalogWatcher, SIGNAL(progressRangeChanged(int,int)), ui->progressBar, SLOT(setRange(int,int)));
    disconnect(m_catalogWatcher, SIGNAL(progressValueChanged(int)), ui->progressBar, SLOT(setValue(int)));
  //  disconnect(m_catalogWatcher, SIGNAL(progressTextChanged(QString)), ui->progressBar, SLOT(setWindowTitle(QString)));
    disconnect(m_catalogWatcher, SIGNAL(progressTextChanged(QString)), ui->volumeNameLabel, SLOT(setText(QString)));

    m_catalogWatcher = nullptr;

    resetCatalogList();
    normalButtonStates();

    QMessageBox msgBox(this);
    msgBox.setWindowTitle(tr("Successed!", "Title of message box when catalog generation finished successfully"));
    QString message = QString(tr("Creating Catalog is Completed", "Body of message box when catalog generation finished successfully"));

    msgBox.setText(message);
    msgBox.exec();
}

void ManageDatabaseDialog::onCancelButton_clicked()
{
    if(!m_thumbManager)
        return;
    if(!m_catalogWatcher) {
        connect(m_thumbManager, SIGNAL(catalogCreated(CatalogRecord)), this, SLOT(on_catalogCreated(CatalogRecord)));
        m_catalogWatcher = m_thumbManager->createCatalogAsync(m_makeCatalogs);
        connect(m_catalogWatcher, SIGNAL(finished()), this, SLOT(on_catalogCreateFinished()));
        connect(m_catalogWatcher, SIGNAL(progressRangeChanged(int,int)), ui->progressBar, SLOT(setRange(int,int)));
        connect(m_catalogWatcher, SIGNAL(progressValueChanged(int)), ui->progressBar, SLOT(setValue(int)));
        connect(m_catalogWatcher, SIGNAL(progressTextChanged(QString)), ui->volumeNameLabel, SLOT(setText(QString)));

        progressButtonStates();
    } else {
        disconnect(m_thumbManager, SIGNAL(catalogCreated(CatalogRecord)), this, SLOT(on_catalogCreated(CatalogRecord)));
        disconnect(m_catalogWatcher, SIGNAL(finished()), this, SLOT(on_catalogCreateFinished()));
        disconnect(m_catalogWatcher, SIGNAL(progressRangeChanged(int,int)), ui->progressBar, SLOT(setRange(int,int)));
        disconnect(m_catalogWatcher, SIGNAL(progressValueChanged(int)), ui->progressBar, SLOT(setValue(int)));
        m_thumbManager->cancelCreateCatalogAsync();
        m_catalogWatcher = nullptr;

        resetCatalogList();
        normalButtonStates();

        QMessageBox msgBox(this);
        msgBox.setWindowTitle(tr("Cancelled!", "Title of message box when catalog generation was canceled"));
        QString message = QString(tr("Creationing Catalog is Cancelled", "Body of message box when catalog generation is canceled"));
        msgBox.setText(message);
        msgBox.exec();
    }
}


void ManageDatabaseDialog::closeEvent(QCloseEvent *)
{
    m_thumbManager->vacuum();
}

void ManageDatabaseDialog::onEditButton_clicked()
{
    if(!m_thumbManager)
        return;
    QTreeWidgetItem *current = ui->treeWidget->currentItem();
    if(!current)
        return;

    int id = current->data(0, Qt::UserRole).toInt();
    CatalogRecord catalog;
    bool editing = false;
    if(id >= 0) {
        catalog = m_catalogs[id];
        editing = true;
    } else {
        id = -100 - id;
        catalog = m_makeCatalogs[id];
    }
    if(!databaseSettingDialog(catalog, editing))
        return;
    m_thumbManager->updateCatalogName(id, catalog.name);
    m_catalogs[id] = catalog;

    resetCatalogList();
}

void ManageDatabaseDialog::onDeleteButton_clicked()
{
    if(!m_thumbManager)
        return;
    QTreeWidgetItem *current = ui->treeWidget->currentItem();
    if(!current)
        return;
    int id = current->data(0, Qt::UserRole).toInt();
    if(id >= 0) {
        m_thumbManager->deleteCatalog(id);
        m_catalogs.remove(id);
    } else {
        id = -100 - id;
        if(id < m_makeCatalogs.size())
            m_makeCatalogs.removeAt(id);
    }

    resetCatalogList();
    normalButtonStates();
}

void ManageDatabaseDialog::onUpdateButton_clicked()
{

}

void ManageDatabaseDialog::onDeleteAllButton_clicked()
{
    if(!m_thumbManager)
        return;
    m_thumbManager->deleteAllCatalogs();
    m_catalogs.clear();
    m_makeCatalogs.clear();

    resetCatalogList();
    normalButtonStates();
}

void ManageDatabaseDialog::onUpdateAllButton_clicked()
{

}

