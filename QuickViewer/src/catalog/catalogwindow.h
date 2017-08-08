#ifndef CATALOGWINDOW_H
#define CATALOGWINDOW_H

#include <QtGui>
#include <QMenu>
#include <QMainWindow>
#include "models/thumbnailmanager.h"
#include "volumeitemmodel.h"

namespace Ui {
class CatalogWindow;
class MainWindow;
}

class SearchWords
{
public:
    bool isEmpty;
    QStringList matches;
    QStringList nomatches;
    SearchWords(const QString& searchNoCase);
    bool match(const QString& targetNoCase);
};


class CatalogWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CatalogWindow(QWidget *parent, Ui::MainWindow* uiMain);
    ~CatalogWindow();
    void setThumbnailManager(ThumbnailManager* manager);
    void resetViewMode();
    void setAsToplevelWindow();
    void setAsInnerWidget();
    void resetVolumes();
    void searchByWord(bool doForce=false);
    void dragEnterEvent(QDragEnterEvent *e);
    void dropEvent(QDropEvent *e);
    bool isCatalogSearching();
    void clearTagFrame();
    void initTagButtons();
    void resetTagButtons(QStringList buttons, QStringList checks);
    QStringList getTagWords();
    void on_showTagBar_triggered(bool enable);

public slots:
    void on_treeItemChanged(QString path);
    void onFolderViewButton_clicked();
    void onActionFolderViewList_triggered();
    void onActionFolderViewIcon_triggered();
    void onActionFolderViewNotext_triggered();
    void onManageCatalogButton_clicked();
    void onSearchCombo_editTextChanged(QString search);
    void onSearchCombo_currentIndexChanged(QString search);
    void onLineEdit_editingFinished();
    void on_itemDoubleClicked(const QModelIndex & index);
    void onActionSearchTitleWithOptions_triggered(bool enable);
    void onActionCatalogTitleWithoutOptions_triggered(bool enable);
    void on_tagButtonClicked(bool checked);

signals:
    void openVolume(QString path);
    void closed();

protected:
    void closeEvent(QCloseEvent *e);

private:
    Ui::CatalogWindow *ui;
    ThumbnailManager* m_thumbManager;
    QMap<int, CatalogRecord> m_catalogs;
    QList<int> m_enabledCatalogs;
    QList<VolumeThumbRecord> m_volumes;
    QList<VolumeThumbRecord*> m_volumeSearch;
    QMenu m_folderViewMenu;
    QString m_lastSearchWord;
    VolumeItemModel m_itemModel;
};

#endif // CATALOGWINDOW_H
