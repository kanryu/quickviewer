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
    void on_currentItem_triggered();

public slots:
    void onHomeButton_clicked();
    void onPrevButton_clicked();
    void onNextButton_clicked();
    void onParentButton_clicked();
    void onReloadButton_clicked();
    void onPageManager_volumeChanged(QString);
    void on_itemSingleClicked(const QModelIndex & index);
    void on_itemDoubleClicked(const QModelIndex & index);
    void onActionSetAsHomeFolder_triggered();
    void onSortModeButton_clicked();
    void onActionOrderByName_triggered();
    void onActionOrderByUpdatedAt_triggered();

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
