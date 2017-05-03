#include <QProcess>

#include "qc_init.h"
#include "catalogwindow.h"
#include "ui_catalogwindow.h"
#include "managedatabasedialog.h"

CatalogWindow::CatalogWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CatalogWindow)
    , m_folderViewMenu(this)
{
    ui->setupUi(this);

    ui->folderTree->setRootPath("C:/Program Files");

    m_folderViewMenu.addAction(ui->actionFolderViewList);
    m_folderViewMenu.addAction(ui->actionFolderViewIcon);
    m_folderViewMenu.addAction(ui->actionFolderViewIconNoText);
}

CatalogWindow::~CatalogWindow()
{
    delete ui;
}

void CatalogWindow::setThumbnailManager(ThumbnailManager *manager)
{
    m_thumbManager = manager;
    ui->folderTree->setVisible(false);
    m_volumes = m_thumbManager->volumes();

    on_folderViewIcon_triggered();
}

void CatalogWindow::resetVolumes(bool withText)
{
    ui->volumeList->clear();
    foreach(const VolumeThumbRecord& vtr, m_volumes) {
        if(vtr.thumbnail.isEmpty())
            continue;
        auto item = new QListWidgetItem;
        QIcon icon(QPixmap::fromImage(QImage::fromData(vtr.thumbnail)));
        item->setIcon(icon);
        item->setData(Qt::UserRole, vtr.path);
        if(withText)
            item->setText(vtr.realname);
        ui->volumeList->addItem(item);
    }
    ui->volumeList->setIconSize(QSize(96,96));
    ui->volumeList->setResizeMode(QListView::Adjust);
    if(ui->actionFolderViewList->isChecked()) {
        ui->volumeList->setWrapping(true);
        ui->volumeList->setWordWrap(true);
        ui->volumeList->setGridSize(QSize(150, 170));
        ui->volumeList->setDragEnabled(false);
        ui->volumeList->setTextElideMode(Qt::ElideRight);

        ui->volumeList->setViewMode(QListView::ListMode);
        ui->volumeList->setGridSize(QSize(300, 100));
        ui->volumeList->setFlow(QListView::TopToBottom);
        ui->volumeList->setUniformItemSizes(true);
    }
    if(ui->actionFolderViewIcon->isChecked()) {
        ui->volumeList->setWrapping(true);
        ui->volumeList->setWordWrap(true);
        ui->volumeList->setGridSize(QSize(150, 170));
        ui->volumeList->setDragEnabled(false);
        ui->volumeList->setTextElideMode(Qt::ElideRight);

        ui->volumeList->setViewMode(QListView::IconMode);
        ui->volumeList->setWordWrap(true);
        ui->volumeList->setGridSize(QSize(150, 170));
        ui->volumeList->setFlow(QListView::LeftToRight);
        ui->volumeList->setUniformItemSizes(false);
    }
    if(ui->actionFolderViewIconNoText->isChecked()) {
        ui->volumeList->setWrapping(true);
        ui->volumeList->setWordWrap(true);
        ui->volumeList->setGridSize(QSize(150, 170));
        ui->volumeList->setDragEnabled(false);
        ui->volumeList->setTextElideMode(Qt::ElideRight);

        ui->volumeList->setViewMode(QListView::IconMode);
        ui->volumeList->setGridSize(QSize(100, 100));
        ui->volumeList->setFlow(QListView::LeftToRight);
        ui->volumeList->setUniformItemSizes(true);
    }
}

void CatalogWindow::on_treeItemChanged(QString path)
{
    ui->pathCombo->setCurrentText(QDir::toNativeSeparators(path));
}

void CatalogWindow::on_folderViewSelect_triggered()
{
    QWidget* widget = ui->folderViewButton;

    QPoint p = widget->mapToGlobal(QPoint(0, widget->height()));
    m_folderViewMenu.exec(p);
}

void CatalogWindow::on_folderViewList_triggered()
{
    ui->actionFolderViewList->setChecked(true);
    ui->actionFolderViewIcon->setChecked(false);
    ui->actionFolderViewIconNoText->setChecked(false);
    resetVolumes(true);
}

void CatalogWindow::on_folderViewIcon_triggered()
{
    ui->actionFolderViewList->setChecked(false);
    ui->actionFolderViewIcon->setChecked(true);
    ui->actionFolderViewIconNoText->setChecked(false);
    resetVolumes(true);
}

void CatalogWindow::on_folderViewNotext_triggered()
{
    ui->actionFolderViewList->setChecked(false);
    ui->actionFolderViewIcon->setChecked(false);
    ui->actionFolderViewIconNoText->setChecked(true);
    resetVolumes(false);
}

void CatalogWindow::on_manageDatabase_triggered()
{
    ManageDatabaseDialog dialog(this);
    dialog.setThumbnailManager(m_thumbManager);
    dialog.exec();

    m_volumes = m_thumbManager->volumes();

    resetVolumes(!ui->actionFolderViewIconNoText->isChecked());
}

void CatalogWindow::on_searchTextChanged(QString search)
{
    qDebug() << search;
}

void CatalogWindow::on_itemDoubleClicked(QListWidgetItem *item)
{
    QString path = item->data(Qt::UserRole).toString();
    QStringList options;
    options << path;
    QProcess::startDetached(QUICKVIEWER, options);
}
