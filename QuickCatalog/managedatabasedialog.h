#ifndef MANAGEDATABASEDIALOG_H
#define MANAGEDATABASEDIALOG_H

#include <QtGui>
#include <QDialog>
#include "thumbnailmanager.h"

namespace Ui {
class ManageDatabaseDialog;
}

class ManageDatabaseDialog : public QDialog
{
    Q_OBJECT
public:
    ManageDatabaseDialog(QWidget* parent=nullptr);
    ~ManageDatabaseDialog();
    void resetButtonStates();
    void setThumbnailManager(ThumbnailManager* manager) {m_thumbManager = manager;}
    void resetCatalogList();

public slots:
    void on_addNew_triggered();
    void on_delete_triggered();
    void on_edit_triggered();
    void on_update_triggered();
    void on_deleteAll_triggered();
    void on_updateAll_triggered();


private:
    Ui::ManageDatabaseDialog *ui;
    QMap<int, CatalogRecord> m_catalogs;
    ThumbnailManager* m_thumbManager;
};

#endif // MANAGEDATABASEDIALOG_H
