#include "volumeitemmodel.h"
#include "qvapplication.h"

VolumeItemModel::VolumeItemModel(QObject* parent)
    : QAbstractItemModel(parent)
    , m_volumeSearch(nullptr)
    , m_catalogViewMode(qvEnums::Icon)
{

}

QVariant VolumeItemModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(!m_volumeSearch)
        return QVariant();
    const VolumeThumbRecord* vtr = m_volumeSearch->at(row);
    switch(role) {
    case Qt::DisplayRole:
        if(m_catalogViewMode == qvEnums::IconNoText)
           return QVariant();
        return qApp->TitleWithoutOptions() ? vtr->name :  vtr->realname;
    case Qt::DecorationRole:
        return QIcon(QPixmap::fromImage(QImage::fromData(vtr->thumbnail)));
    case Qt::SizeHintRole:
        if(qApp->IconLongText())
            return m_catalogViewMode == qvEnums::List ? QSize(300, 100) :
                   m_catalogViewMode == qvEnums::Icon ? QSize(150, 170) : QSize(100, 100);
        else
            return m_catalogViewMode == qvEnums::List ? QSize(200, 100) :
                   m_catalogViewMode == qvEnums::Icon ? QSize(150, 120) : QSize(100, 100);
    }
    return QVariant();
}

int VolumeItemModel::rowCount(const QModelIndex &) const
{
    return !m_volumeSearch ? 0 : m_volumeSearch->size();
}

QModelIndex VolumeItemModel::index(int row, int column, const QModelIndex &) const
{
    if(column > 1 || !m_volumeSearch)
        return QModelIndex();
    return row < m_volumeSearch->size() ? createIndex(row, column, m_volumeSearch->at(row)) : QModelIndex();
}

void VolumeItemModel::setVolumes(QList<VolumeThumbRecord *> *volumes)
{
    emit beginResetModel();
    m_volumeSearch = volumes;
    emit endResetModel();
}

void VolumeItemModel::setViewMode(qvEnums::CatalogViewMode viewMode)
{
    m_catalogViewMode = viewMode;
    emit submit();
}
