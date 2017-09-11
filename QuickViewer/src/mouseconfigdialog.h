#ifndef MOUSECONFIGDIALOG_H
#define MOUSECONFIGDIALOG_H

#include <QtCore>
#include <QtWidgets>

#include "qactionmanager.h"
#include "qmousesequence.h"

namespace Ui {
class KeyConfigDialog;
}


class MouseConfigDialog : public QDialog
{
    Q_OBJECT
public:
    typedef QActionManager<QMouseSequence, QMouseValue, QAction*> MouseActionManager;

    MouseConfigDialog(MouseActionManager& mouseActions, QWidget *parent);
    ~MouseConfigDialog();

    void setEditTextWithoutSignal(QString text);
//    void revertMouseChanges();
    void resetMouseCheckBox();
    void resetView();
    MouseActionManager& mouseActions() { return m_mouseActions; }

public slots:
    void onTreeWidget_currentItemChanged(QTreeWidgetItem* item, QTreeWidgetItem * previous);
    void onRecordButton_keySequenceChanged(QMouseSequence key);
    void onAddSequenceButton_clicked();
    void onResetButton_clicked();
    void onShortcutEdit_textChanged(QString text);
    void onCheckBox_toggled();
    void onStandardButton_clicked(QAbstractButton *button);

private:
    Ui::KeyConfigDialog *ui;
    bool m_keyCapturing;
    QString m_actionName;
//    QMap<QString, QMouseSequence> m_prevKeyConfigs;
    MouseActionManager m_mouseActions;
    bool m_ignoreEdited;
};

#endif // MOUSECONFIGDIALOG_H
