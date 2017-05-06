#include <QProcess>

#include "qc_init.h"
#include "catalogwindow.h"
#include "ui_catalogwindow.h"
#include "managedatabasedialog.h"

CatalogWindow::CatalogWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CatalogWindow)
    , m_folderViewMenu(this)
    , m_maxVolumeViewing(500)
{
    ui->setupUi(this);

    // SearchCombo
    connect(ui->searchCombo->lineEdit(), SIGNAL(editingFinished()), this, SLOT(on_searchTextFinished()));
    ui->searchCombo->lineEdit()->setPlaceholderText(tr("Input Search words and Press Enter-key"));

    // Status Bar
    ui->statusBar->addPermanentWidget(ui->statusLabel);
    ui->statusLabel->setText(tr("any database is not loaded."));

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
    searchByWord(true);

    on_folderViewIcon_triggered();
}

void CatalogWindow::resetVolumes()
{
    bool withText = !ui->actionFolderViewIconNoText->isChecked();
    ui->volumeList->clear();
    foreach(VolumeThumbRecord* vtr, m_volumeSearch) {
        if(vtr->thumbnail.isEmpty())
            continue;
        auto item = new QListWidgetItem;
        QIcon icon(QPixmap::fromImage(QImage::fromData(vtr->thumbnail)));
        item->setIcon(icon);
        item->setData(Qt::UserRole, vtr->path);
        if(withText)
            item->setText(vtr->realname);
        ui->volumeList->addItem(item);
    }
    QString volumestxt = QString(tr("(%1/%2) volumes listed."))
            .arg(m_volumeSearch.size()).arg(m_volumes.size());
    ui->statusLabel->setText(volumestxt);
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
        if(!searchwords.match(vtr.realnameNoCase))
            continue;
        if(m_maxVolumeViewing < ++cnt)
            break;
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
    ui->actionFolderViewList->setChecked(true);
    ui->actionFolderViewIcon->setChecked(false);
    ui->actionFolderViewIconNoText->setChecked(false);
    resetVolumes();
}

void CatalogWindow::on_folderViewIcon_triggered()
{
    ui->actionFolderViewList->setChecked(false);
    ui->actionFolderViewIcon->setChecked(true);
    ui->actionFolderViewIconNoText->setChecked(false);
    resetVolumes();
}

void CatalogWindow::on_folderViewNotext_triggered()
{
    ui->actionFolderViewList->setChecked(false);
    ui->actionFolderViewIcon->setChecked(false);
    ui->actionFolderViewIconNoText->setChecked(true);
    resetVolumes();
}

void CatalogWindow::on_manageDatabase_triggered()
{
    ManageDatabaseDialog dialog(this);
    dialog.setThumbnailManager(m_thumbManager);
    dialog.exec();

    m_volumes = m_thumbManager->volumes();
    searchByWord(true);

    resetVolumes();
}

void CatalogWindow::on_searchTextChanged(QString search)
{
    qDebug() << search;
    if(m_volumes.size() < 100)
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
//    QStringList options;
//    options << path;
//    QProcess::startDetached(QUICKVIEWER, options);

    emit openVolume(path);
}

SearchWords::SearchWords(const QString &searchNoCase)
{
    if(searchNoCase.isEmpty()) {
        isEmpty = true;
        return;
    }
    isEmpty = false;
    foreach(const QString& s, searchNoCase.trimmed().split(" ")) {
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
