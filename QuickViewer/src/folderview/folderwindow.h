#ifndef FOLDERWINDOW_H
#define FOLDERWINDOW_H

#include <QtGui>
#include <QtWidgets>
#include "qv_init.h"
#include "folderitemmodel.h"
#include "folderitemdelegate.h"

namespace Ui {
class FolderWindow;
class MainWindow;
}

class FolderWindow : public QWidget
{
    Q_OBJECT
public:
    explicit FolderWindow(QWidget *parent, Ui::MainWindow* uiMain);
    ~FolderWindow();
    void setAsToplevelWindow();
    void setAsInnerWidget();
    bool eventFilter(QObject *obj, QEvent *event);
    void dragEnterEvent(QDragEnterEvent *e);
    void dropEvent(QDropEvent *e);
    void resizeEvent(QResizeEvent *event);
    void setFolderPath(QString path, bool showParent=true);
    void reset();
    void resetSortMode();
    void resetPathLabel(int maxWidth);
    QString currentPath() { return m_currentPath; }
    QString itemPath(const QModelIndex& index);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);

public slots:
    void on_home_triggered();
    void on_prev_triggered();
    void on_next_triggered();
    void on_parent_triggered();
    void on_reload_triggered();
    void on_volumeChanged_triggered(QString);
    void on_itemSingleClicked(const QModelIndex & index);
    void on_itemDoubleClicked(const QModelIndex & index);
    void on_currentItem_triggered();
    void on_setHome_triggered();
    void on_sortMode_triggered();
    void on_orderByName_triggered();
    void on_orderByUpdatedAt_triggered();

signals:
    void openVolume(QString path);
    void closed();

protected:
    void closeEvent(QCloseEvent *e);

private:
    Ui::FolderWindow *ui;
    QMenu* m_sortModeMenu;
    QMenu* m_itemContextMenu;
    QString m_currentPath;
    QList<QvFolderItem> m_volumes;
    QStringList m_historyPrev;
    QStringList m_historyNext;
    FolderItemModel m_itemModel;
    FolderItemDelegate m_itemDelegate;
};

#endif // FOLDERWINDOW_H
