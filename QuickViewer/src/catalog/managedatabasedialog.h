#ifndef MANAGEDATABASEDIALOG_H
#define MANAGEDATABASEDIALOG_H

#include <QtGui>
#include <QDialog>
#include "models/thumbnailmanager.h"

namespace Ui {
class ManageDatabaseDialog;
}

class ManageDatabaseDialog : public QDialog
{
    Q_OBJECT
public:
    ManageDatabaseDialog(QWidget* parent=nullptr);
    ~ManageDatabaseDialog();
    void normalButtonStates();
    void progressButtonStates();
    void setThumbnailManager(ThumbnailManager* manager);
    void resetCatalogList();
    void dragEnterEvent(QDragEnterEvent *e);
    void dropEvent(QDropEvent *e);
    bool databaseSettingDialog(CatalogRecord& catalog, bool editing);
    void createCatalog();

protected:
    void closeEvent(QCloseEvent *e);

public slots:
    void on_addNew_triggered();
    void on_delete_triggered();
    void on_edit_triggered();
    void on_update_triggered();
    void on_deleteAll_triggered();
    void on_updateAll_triggered();
    void on_cancelWork_triggered();

private slots:
    void on_catalogCreated(const CatalogRecord cr);
    void on_catalogCreateFinished();

private:
    Ui::ManageDatabaseDialog *ui;
    QMap<int, CatalogRecord> m_catalogs;
    QList<CatalogRecord> m_makeCatalogs;
    ThumbnailManager* m_thumbManager;

    QFutureWatcher<QList<CatalogRecord>>* m_catalogWatcher;
};

#endif // MANAGEDATABASEDIALOG_H
