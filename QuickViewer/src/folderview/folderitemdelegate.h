#ifndef FOLDERITEMDELEGATE_H
#define FOLDERITEMDELEGATE_H

#include <QtWidgets>
#include <QtCore>

class FolderWindow;

class FolderItemDelegate : public QStyledItemDelegate
{
public:
    FolderItemDelegate(QWidget *parent, FolderWindow* folderWindow);
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
                             const QModelIndex &index) const override;
private:
    FolderWindow* m_folderWindow;
};

#endif // FOLDERITEMDELEGATE_H
