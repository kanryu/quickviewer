#include "fileexplorer.h"
#include "fileexplorermodel.h"

void FileExplorer::setRootPath(const QString &path)
{
    m_treeModel = new FileExplorerModel;
    m_treeModel->setFilter(QDir::Dirs|QDir::NoDotAndDotDot);
    QModelIndex rootModelIndex = m_treeModel->setRootPath(path);

    this->m_rootPath = path;
        ///現在のルートパスを保存

//    setHeaderHidden(true);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setTextElideMode(Qt::ElideNone);
    setModel(m_treeModel);
    setRootIndex(rootModelIndex);
//    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
//    setFixedHeight(500);
    setColumnWidth(0, INT_MAX);
    setIndentation(20);
    setSortingEnabled(true);

//    connect(ui->folderTree, SIGNAL(activated(QModelIndex)), this, SLOT(on_treeItemChanged(QModelIndex)) );
}

//void FileExplorer::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
//{
//    QModelIndexList lst = selected.indexes();
////    if(!lst.empty())
////        emit itemChanged(lst[0].data().toString());
//}


void FileExplorer::currentChanged(const QModelIndex & current, const QModelIndex &)
{
    qDebug() << current;
    qDebug() << m_treeModel->filePath(current);
    emit itemChanged(m_treeModel->filePath(current));
}

