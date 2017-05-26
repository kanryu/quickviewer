#include "folderitemmodel.h"


FolderItemModel::FolderItemModel(QObject *parent)
    : QAbstractItemModel(parent)
    , m_searchedVolumes(nullptr)
    , m_columns(1)
{

}

QVariant FolderItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch(role) {
    case Qt::DisplayRole:
        switch(section) {
        case 0: return tr("Name");
        case 1: return tr("ModifiedTime");
        }
        break;
//    case Qt::SizeHintRole:
//        switch(section) {
//        case 0: return QSize(300, 20);
//        case 1: return QSize(300, 20);
//        }
//        break;
    }
    return QVariant();
}

QVariant FolderItemModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int column = index.column();
    if(!m_searchedVolumes)
        return QVariant();
    const FolderItem& fi = m_searchedVolumes->at(row);
    switch(role) {
    case Qt::DisplayRole:
        switch(column) {
        case 0: return fi.name;
        case 1: return fi.updated_at;
        }
    case Qt::DecorationRole:
        if(column == 0 && fi.type == FolderItem::Dir) {
            QIcon icon(":/icons/24/checkbox_off_icon_24");
            return icon;
        }
        return QVariant();
//    case Qt::SizeHintRole:
//        if(qApp->IconLongText())
//            return m_catalogViewMode == qvEnums::List ? QSize(300, 100) :
//                   m_catalogViewMode == qvEnums::Icon ? QSize(150, 170) : QSize(100, 100);
//        else
//            return m_catalogViewMode == qvEnums::List ? QSize(200, 100) :
//                   m_catalogViewMode == qvEnums::Icon ? QSize(150, 120) : QSize(100, 100);
    }
    return QVariant();

}

int FolderItemModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return !m_searchedVolumes ? 0 : m_searchedVolumes->size();
}

int FolderItemModel::columnCount(const QModelIndex &) const
{
    return m_columns;
}

QModelIndex FolderItemModel::index(int row, int column, const QModelIndex &parent) const
{
//    if(column > 1 || !m_searchedVolumes)
//        return QModelIndex();
    if(!m_searchedVolumes)
        return QModelIndex();
    return row < m_searchedVolumes->size() ? createIndex(row, column, (void*)&m_searchedVolumes->at(row)) : QModelIndex();
}

QModelIndex FolderItemModel::parent(const QModelIndex &) const {return QModelIndex();}

void FolderItemModel::setVolumes(QList<FolderItem> *volumes)
{
    if(!volumes)
        return;
    emit beginResetModel();
    m_searchedVolumes = volumes;
    emit endResetModel();
}

