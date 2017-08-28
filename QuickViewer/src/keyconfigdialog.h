#ifndef KEYCONFIGDIALOG_H
#define KEYCONFIGDIALOG_H

#include <QtCore>
#include <QtWidgets>

#include "models/qvapplication.h"

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
    void onTreeWidget_currentItemChanged(QTreeWidgetItem* item, QTreeWidgetItem * previous);
    void onRecordButton_keySequenceChanged(QKeySequence key);
    void onResetButton_clicked();
    void onShortcutEdit_textChanged(QString text);


private:
    Ui::KeyConfigDialog *ui;
    bool m_keyCapturing;
    QString m_actionName;
    QMap<QString, QKeySequence> m_prevKeyConfigs;
    bool m_ignoreEdited;

    bool markCollisions(QKeySequence key);
};


#endif // KEYCONFIGDIALOG_H
