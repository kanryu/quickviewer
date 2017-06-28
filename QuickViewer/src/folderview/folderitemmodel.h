#ifndef FOLDERITEMMODEL_H
#define FOLDERITEMMODEL_H

#include <QtWidgets>
#include <QtCore>

class FolderItem
{
public:
    enum FileType {
        Dir,
        Archive,
        Image,
        NoItems
    };

    QString name;
    FileType type; // 0:folder, 1:archive
    QDateTime updated_at;

    FolderItem():type(Dir){}
    FolderItem(QString n, FileType t, QDateTime u)
        : name(n), type(t), updated_at(u)
    {}
};



class FolderItemModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    FolderItemModel(QObject* parent);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &) const override;
    QModelIndex	index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex	parent(const QModelIndex &) const override;

    void setVolumes(QList<FolderItem>* volumes);
    void setColumns(int c) { m_columns=c; }

private:
    QList<FolderItem>* m_searchedVolumes;
    int m_columns;
};

#endif // FOLDERITEMMODEL_H
