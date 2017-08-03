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

public slots:
//    void on_keySequenceItemSelected(QTree)
    void on_currentCommandChanged(QTreeWidgetItem* item, QTreeWidgetItem * previous);
    void on_keySequence_changed(QMouseSequence key);
    void on_addSequenc_triggered();
    void on_resetToDefault();
    void on_shortcutClearButton_triggered();
    void on_shortcutEdit_changed(QString text);
    void on_checkboxChanged_triggered();
    void resetMouseCheckBox();

private:
    Ui::KeyConfigDialog *ui;
    bool m_keyCapturing;
    QString m_actionName;
    QMouseSequence m_seqListEditing;
    QMap<QString, QMouseSequence> m_prevKeyConfigs;
    bool m_ignoreEdited;

    bool markCollisions(QMouseSequence key);
};

#endif // MOUSECONFIGDIALOG_H
