#ifndef MOUSECONFIGDIALOG_H
#define MOUSECONFIGDIALOG_H

#include <QtCore>
#include <QtWidgets>

#include "models/qvapplication.h"

namespace Ui {
class KeyConfigDialog;
}


class MouseConfigDialog : public QDialog
{
    Q_OBJECT
public:
    MouseConfigDialog(QWidget *parent);
    ~MouseConfigDialog();

    void setEditTextWithoutSignal(QString text);
    void revertMouseChanges();
    void resetMouseCheckBox();

public slots:
    void onTreeWidget_currentItemChanged(QTreeWidgetItem* item, QTreeWidgetItem * previous);
    void onRecordButton_keySequenceChanged(QMouseSequence key);
    void onAddSequenceButton_clicked();
    void onResetButton_clicked();
    void onShortcutEdit_textChanged(QString text);
    void onCheckBox_toggled();

private:
    Ui::KeyConfigDialog *ui;
    bool m_keyCapturing;
    QString m_actionName;
    QMap<QString, QMouseSequence> m_prevKeyConfigs;
    bool m_ignoreEdited;

    bool markCollisions(QMouseSequence key);
};

#endif // MOUSECONFIGDIALOG_H
