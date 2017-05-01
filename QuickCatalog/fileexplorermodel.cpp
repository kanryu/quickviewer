#include "fileexplorermodel.h"


bool FileExplorerModel::hasChildren(const QModelIndex &parent) const
{
//    qDebug() << "hasChildren:" << parent.data();
    return QFileSystemModel::hasChildren(parent);
}
