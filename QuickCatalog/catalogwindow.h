#ifndef CATALOGWINDOW_H
#define CATALOGWINDOW_H

#include <QtGui>
#include <QMenu>
#include <QMainWindow>
#include <QListWidget>
#include "thumbnailmanager.h"

namespace Ui {
class CatalogWindow;
}

class CatalogWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CatalogWindow(QWidget *parent = 0);
    ~CatalogWindow();
    void setThumbnailManager(ThumbnailManager* manager);
    void resetVolumes(bool withText);

public slots:
    void on_treeItemChanged(QString path);
    void on_folderViewSelect_triggered();
    void on_folderViewList_triggered();
    void on_folderViewIcon_triggered();
    void on_folderViewNotext_triggered();
    void on_manageDatabase_triggered();
    void on_searchTextChanged(QString search);
    void on_itemDoubleClicked(QListWidgetItem * item);

private:
    Ui::CatalogWindow *ui;
    ThumbnailManager* m_thumbManager;
    QMap<int, CatalogRecord> m_catalogs;
    QList<int> m_enabledCatalogs;
    QList<VolumeThumbRecord> m_volumes;
    QMenu m_folderViewMenu;
};

#endif // CATALOGWINDOW_H
