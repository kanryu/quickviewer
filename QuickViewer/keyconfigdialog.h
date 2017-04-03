#ifndef KEYCONFIGDIALOG_H
#define KEYCONFIGDIALOG_H

#include <QDialog>
#include <QTreeWidget>
#include <QPushButton>
#include <QMap>
#include <QKeySequence>

#include "qvapplication.h"

namespace Ui {
class KeyConfigDialog;
}



class KeyConfigDialog : public QDialog
{
    Q_OBJECT
public:
    explicit KeyConfigDialog(QWidget *parent);
    ~KeyConfigDialog();

    bool eventFilter(QObject *obj, QEvent *event);
    void setEditTextWithoutSignal(QString text);
    void revertKeyChanges();

signals:

public slots:
//    void on_keySequenceItemSelected(QTree)
    void on_currentCommandChanged(QTreeWidgetItem* item, QTreeWidgetItem * previous);
    void on_keySequence_changed(QKeySequence &key);
    void on_resetToDefault();
    void on_shortcutClearButton_triggered();
    void on_shortcutEdit_changed(QString text);


private:
    Ui::KeyConfigDialog *ui;
    bool m_keyCapturing;
    QString m_actionName;
    QKeySequence m_seqListEditing;
    QMap<QString, QKeySequence> m_prevKeyConfigs;
    bool m_ignoreEdited;

    bool markCollisions(QKeySequence key);
};


#endif // KEYCONFIGDIALOG_H
