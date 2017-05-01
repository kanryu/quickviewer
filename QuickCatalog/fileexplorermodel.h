#ifndef FILEEXPLORERMODEL_H
#define FILEEXPLORERMODEL_H

#include <QtGui>
#include <QtWidgets>

class FileExplorerModel : public QFileSystemModel
{
public:
    FileExplorerModel(QObject* parent=nullptr)
     : QFileSystemModel(parent) {}

    int columnCount(const QModelIndex &) const { return 1; }
    bool hasChildren(const QModelIndex &parent) const;
};

#endif // FILEEXPLORERMODEL_H
