#include <QtWidgets>
#ifdef Q_OS_WIN
#include <Windows.h>
#endif

#include "ui_catalogwindow.h"
#include "ui_mainwindow.h"

#include "qc_init.h"
#include "catalogwindow.h"
#include "managedatabasedialog.h"
#include "qvapplication.h"

CatalogWindow::CatalogWindow(QWidget *parent, Ui::MainWindow *uiMain)
    : QWidget(parent)
    , ui(new Ui::CatalogWindow)
    , m_folderViewMenu(this)
    , m_itemModel(this)
{
    ui->setupUi(this);

    // VolumeView
    m_itemModel.setViewMode(qApp->CatalogViewModeSetting());
    ui->volumeList->setModel(&m_itemModel);

    // SearchCombo
    connect(ui->searchCombo->lineEdit(), SIGNAL(editingFinished()), this, SLOT(on_searchTextFinished()));
    ui->searchCombo->lineEdit()->setPlaceholderText(tr("Input Search words and Press Enter-key"));

    // Status Bar
    ui->statusBar->addPermanentWidget(ui->statusLabel);
    ui->statusLabel->setText(tr("Drop image folders here and create Catalogs."));

    ui->menu_View->addAction(uiMain->actionCatalogTitleWithoutOptions);
    ui->menu_View->addAction(uiMain->actionSearchTitleWithOptions);

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
    m_volumes = m_thumbManager->volumes();

    switch(qApp->CatalogViewModeSetting()) {
    case qvEnums::List: on_folderViewList_triggered(); break;
    case qvEnums::Icon: on_folderViewIcon_triggered(); break;
    case qvEnums::IconNoText: on_folderViewNotext_triggered(); break;
    }
    searchByWord(true);
}

void CatalogWindow::setAsToplevelWindow()
{
    ui->menuBar->setVisible(true);
    ui->statusLabel->setWordWrap(false);
    setAttribute(Qt::WA_DropSiteRegistered, false);
    setAcceptDrops(true);
}

void CatalogWindow::setAsInnerWidget()
{
    ui->menuBar->setVisible(false);
    ui->statusLabel->setWordWrap(true);
    ui->searchCombo->setFocus();
}

bool CatalogWindow::isCatalogSearching()
{
    return ui->searchCombo->hasFocus();
}

void CatalogWindow::resetVolumes()
{
    m_itemModel.setVolumes(&m_volumeSearch);
    if(m_volumes.size() > 0) {
        QString volumestxt = QString(tr("(%1/%2) volumes listed."))
                .arg(m_volumeSearch.size()).arg(m_volumes.size());
        ui->statusLabel->setText(volumestxt);
    }
    return;

//    bool withText = !ui->actionFolderViewIconNoText->isChecked();
//    ui->volumeList->clear();
//    foreach(VolumeThumbRecord* vtr, m_volumeSearch) {
//        if(vtr->thumbnail.isEmpty())
//            continue;
//        auto item = new QListWidgetItem;
////        if(vtr->icon.isNull()) {
////            vtr->icon = QIcon(QPixmap::fromImage(QImage::fromData(vtr->thumbnail)));
////        }
//        item->setIcon(vtr->icon);
////        item->setIcon(QIcon(QPixmap::fromImage(QImage::fromData(vtr->thumbnail))));
//        item->setData(Qt::UserRole, vtr->path);
//        if(withText) {
//            if(qApp->TitleWithoutOptions())
//                item->setText(vtr->name);
//            else
//                item->setText(vtr->realname);
//        }
//        ui->volumeList->addItem(item);
//    }
//    if(m_volumes.size() > 0) {
//        QString volumestxt = QString(tr("(%1/%2) volumes listed."))
//                .arg(m_volumeSearch.size()).arg(m_volumes.size());
//        ui->statusLabel->setText(volumestxt);
//    }

//    ui->volumeList->setIconSize(QSize(96,96));
//    ui->volumeList->setResizeMode(QListView::Adjust);
//    switch(qApp->CatalogViewModeSetting()) {
//    case qvEnums::List:
//        ui->volumeList->setWrapping(true);
//        ui->volumeList->setWordWrap(true);
//        ui->volumeList->setGridSize(QSize(150, 170));
//        ui->volumeList->setDragEnabled(false);
//        ui->volumeList->setTextElideMode(Qt::ElideRight);

//        ui->volumeList->setViewMode(QListView::ListMode);
//        ui->volumeList->setGridSize(QSize(300, 100));
//        ui->volumeList->setFlow(QListView::TopToBottom);
//        ui->volumeList->setUniformItemSizes(false);
//        break;
//    case qvEnums::Icon:
//        ui->volumeList->setWrapping(true);
//        ui->volumeList->setWordWrap(true);
//        ui->volumeList->setGridSize(QSize(150, 170));
//        ui->volumeList->setDragEnabled(false);
//        ui->volumeList->setTextElideMode(Qt::ElideRight);

//        ui->volumeList->setViewMode(QListView::IconMode);
//        ui->volumeList->setWordWrap(true);
//        ui->volumeList->setGridSize(QSize(150, 170));
//        ui->volumeList->setFlow(QListView::LeftToRight);
//        ui->volumeList->setUniformItemSizes(false);
//        break;
//    case qvEnums::IconNoText:
//        ui->volumeList->setWrapping(true);
//        ui->volumeList->setWordWrap(true);
//        ui->volumeList->setDragEnabled(false);
//        ui->volumeList->setTextElideMode(Qt::ElideRight);

//        ui->volumeList->setViewMode(QListView::IconMode);
//        ui->volumeList->setGridSize(QSize(100, 100));
//        ui->volumeList->setFlow(QListView::LeftToRight);
//        ui->volumeList->setUniformItemSizes(false);
//    }
}

void CatalogWindow::searchByWord(bool doForce)
{
    QString search = ui->searchCombo->currentText();
    search = search.trimmed();
    if(!doForce && search == m_lastSearchWord)
        return;
    m_lastSearchWord = search;

    int cnt = 0;
    m_volumeSearch.clear();
    SearchWords searchwords(search.toLower());
    foreach(const VolumeThumbRecord& vtr , m_volumes) {
        if(vtr.thumbnail.isEmpty())
            continue;
        QString title = qApp->SearchTitleWithOptions() ? vtr.nameNoCase : vtr.realnameNoCase;
        if(!searchwords.match(title))
            continue;
//        if(qApp->MaxShowFrontpage() < ++cnt)
//            break;
        m_volumeSearch.append(const_cast<VolumeThumbRecord*>(&vtr));
    }
    resetVolumes();
}

void CatalogWindow::dragEnterEvent(QDragEnterEvent *e)
{
    if(e->mimeData()->hasFormat("text/uri-list"))
    {
        //視覚的にドロップを受付られることを
        //表示し、ドラッグ＆ドロップを受け付ける
        //これがないと受付られない。
        e->acceptProposedAction();
//        e->accept();
    }
}

void CatalogWindow::dropEvent(QDropEvent *e)
{
    ManageDatabaseDialog dialog(this);
    dialog.setThumbnailManager(m_thumbManager);
    dialog.dropEvent(e);
    dialog.exec();

    m_volumes = m_thumbManager->volumes();
    searchByWord(true);

    resetVolumes();
}

void CatalogWindow::on_treeItemChanged(QString path)
{
    //ui->pathCombo->setCurrentText(QDir::toNativeSeparators(path));
}

void CatalogWindow::on_folderViewSelect_triggered()
{
    QWidget* widget = ui->folderViewButton;

    QPoint p = widget->mapToGlobal(QPoint(0, widget->height()));
    m_folderViewMenu.exec(p);
}

void CatalogWindow::on_folderViewList_triggered()
{
    qApp->setCatalogViewModeSetting(qvEnums::List);
    ui->actionFolderViewList->setChecked(true);
    ui->actionFolderViewIcon->setChecked(false);
    ui->actionFolderViewIconNoText->setChecked(false);
    m_itemModel.setViewMode(qvEnums::List);
    ui->volumeList->setResizeMode(QListView::Adjust);
    ui->volumeList->setGridSize(QSize(300, 100));
    ui->volumeList->setViewMode(QListView::ListMode);
    ui->volumeList->setUniformItemSizes(true);

    resetVolumes();
}

void CatalogWindow::on_folderViewIcon_triggered()
{
    qApp->setCatalogViewModeSetting(qvEnums::Icon);
    ui->actionFolderViewList->setChecked(false);
    ui->actionFolderViewIcon->setChecked(true);
    ui->actionFolderViewIconNoText->setChecked(false);
    m_itemModel.setViewMode(qvEnums::Icon);
    ui->volumeList->setResizeMode(QListView::Adjust);
    ui->volumeList->setGridSize(QSize(150, 170));
    ui->volumeList->setViewMode(QListView::IconMode);
    ui->volumeList->setUniformItemSizes(true);

    resetVolumes();
}

void CatalogWindow::on_folderViewNotext_triggered()
{
    qApp->setCatalogViewModeSetting(qvEnums::IconNoText);
    ui->actionFolderViewList->setChecked(false);
    ui->actionFolderViewIcon->setChecked(false);
    ui->actionFolderViewIconNoText->setChecked(true);
    m_itemModel.setViewMode(qvEnums::IconNoText);
    ui->volumeList->setResizeMode(QListView::Adjust);
    ui->volumeList->setViewMode(QListView::IconMode);
    ui->volumeList->setGridSize(QSize(100, 100));
    ui->volumeList->setUniformItemSizes(true);

    resetVolumes();
}

void CatalogWindow::on_manageDatabase_triggered()
{
    ManageDatabaseDialog dialog(this);
    dialog.setThumbnailManager(m_thumbManager);
    dialog.exec();

    m_volumes = m_thumbManager->volumes();
    searchByWord(true);
}

void CatalogWindow::on_searchTextChanged(QString search)
{
    qDebug() << search;
//    if(m_volumes.size() < qApp->MaxSearchByCharChanged())
        searchByWord();
    return;
}

void CatalogWindow::on_searchTextIndexChanged(QString search)
{
    qDebug() << "on_searchTextIndexChanged: " << search;
    searchByWord();
}

void CatalogWindow::on_searchTextFinished()
{
    qDebug() << "on_searchTextFinished:";
    searchByWord();
}

void CatalogWindow::on_itemDoubleClicked(QListWidgetItem *item)
{
    QString path = item->data(Qt::UserRole).toString();
    emit openVolume(path);
}

void CatalogWindow::on_itemDoubleClicked(const QModelIndex &index)
{
    int row = index.row();
    if(row >= m_volumeSearch.size())
        return;
    emit openVolume(m_volumeSearch[row]->path);
}

void CatalogWindow::on_searchTitleWithOptions_triggered(bool enable)
{
    qApp->setSearchTitleWithOptions(enable);
    searchByWord(true);
}

void CatalogWindow::on_catalogTitleWithoutOptions_triggered(bool enable)
{
    qApp->setTitleWithoutOptions(enable);
    searchByWord(true);
}

void CatalogWindow::closeEvent(QCloseEvent *e)
{
    QWidget::closeEvent(e);
    emit closed();
}

SearchWords::SearchWords(const QString &searchNoCase)
{
    if(searchNoCase.isEmpty()) {
        isEmpty = true;
        return;
    }
    isEmpty = false;
    foreach(const QString& s, searchNoCase.trimmed().split(" ")) {
        if(s.isEmpty())
            continue;
        if(s[0] == '-')
            nomatches << s.mid(1);
        else
            matches << s;
    }
}

bool SearchWords::match(const QString &targetNoCase)
{
    if(isEmpty)
        return true;
    foreach(const QString& s, matches) {
        if(!targetNoCase.contains(s))
            return false;
    }
    foreach(const QString& s, nomatches) {
        if(targetNoCase.contains(s))
            return false;
    }
    return true;
}
