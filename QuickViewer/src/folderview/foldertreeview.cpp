#include "foldertreeview.h"

FolderTreeView::FolderTreeView(QWidget *parent)
    : QTreeView(parent)
{

}

void FolderTreeView::selectionChanged(const QItemSelection &selection, const QItemSelection &)
{
    auto list = selection.indexes();
    if(list.size() > 0)
        emit selected(list.first());
}
