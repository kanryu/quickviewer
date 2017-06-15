#ifndef FOLDERTREEVIEW_H
#define FOLDERTREEVIEW_H

#include <QtWidgets>

class FolderTreeView : public QTreeView
{
    Q_OBJECT
public:
    FolderTreeView(QWidget* parent);

signals:
    void selected(const QModelIndex & index);

protected:
    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) override;
};

#endif // FOLDERTREEVIEW_H
