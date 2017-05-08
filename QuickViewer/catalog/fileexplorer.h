#ifndef FILEEXPLORER_H
#define FILEEXPLORER_H

#include <QtWidgets>

class FileExplorerModel;

class FileExplorer : public QTreeView
{
    Q_OBJECT
public:
    FileExplorer(QWidget* parent=nullptr)
        : QTreeView(parent) {}

    void setRootPath(const QString& path);
    QString currentRootPath(){return m_rootPath; }

signals:
    void itemChanged(QString path);

protected:
    void currentChanged(const QModelIndex & current, const QModelIndex & previous);

private:
    QString m_rootPath;
    FileExplorerModel * m_treeModel;
};

#endif // FILEEXPLORER_H
