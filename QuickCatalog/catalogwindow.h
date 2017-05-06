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

class SearchWords
{
public:
    bool isEmpty;
    QStringList matches;
    QStringList nomatches;
    SearchWords(const QString& searchNoCase);
    bool match(const QString& targetNoCase);
};


class CatalogWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CatalogWindow(QWidget *parent = 0);
    ~CatalogWindow();
    void setThumbnailManager(ThumbnailManager* manager);
    void resetVolumes();
    void searchByWord(bool doForce=false);

public slots:
    void on_treeItemChanged(QString path);
    void on_folderViewSelect_triggered();
    void on_folderViewList_triggered();
    void on_folderViewIcon_triggered();
    void on_folderViewNotext_triggered();
    void on_manageDatabase_triggered();
    void on_searchTextChanged(QString search);
    void on_searchTextIndexChanged(QString search);
    void on_searchTextFinished();
    void on_itemDoubleClicked(QListWidgetItem * item);

private:
    Ui::CatalogWindow *ui;
    ThumbnailManager* m_thumbManager;
    QMap<int, CatalogRecord> m_catalogs;
    QList<int> m_enabledCatalogs;
    QList<VolumeThumbRecord> m_volumes;
    QList<VolumeThumbRecord*> m_volumeSearch;
    QMenu m_folderViewMenu;
    QString m_lastSearchWord;
    int m_maxVolumeViewing;
};

#endif // CATALOGWINDOW_H
