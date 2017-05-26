#ifndef DATABASESETTING_H
#define DATABASESETTING_H

#include <QtGui>
#include <QDialog>
#include "models/thumbnailmanager.h"

namespace Ui {
class DatabaseSettingDialog;
}


class DatabaseSettingDialog : public QDialog
{
    Q_OBJECT
public:
    DatabaseSettingDialog(QWidget* parent=nullptr);
    ~DatabaseSettingDialog();
    QString name() const { return m_name;}
    QString path() const { return m_path;}
    void setName(QString name) { m_name = name; }
    void setPath(QString path) { m_path = path; }
    void setForEditing(bool editing) { m_editing = editing; }

    int exec();
    void dragEnterEvent(QDragEnterEvent *e);
    void dropEvent(QDropEvent *e);
    void checkAcceptable();

public slots:
    void on_nameChanged(QString name);
    void on_pathChanged(QString path) {setPath(path);checkAcceptable();}
    void on_selectFolder_triggered();

private:
    Ui::DatabaseSettingDialog *ui;
    QString m_name;
    QString m_path;
    bool m_editing;
};

#endif // DATABASESETTING_H
