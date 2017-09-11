#ifndef KEYCONFIGDIALOG_H
#define KEYCONFIGDIALOG_H

#include <QtCore>
#include <QtWidgets>

#include "qactionmanager.h"

namespace Ui {
class KeyConfigDialog;
}

class KeyConfigDialog : public QDialog
{
    Q_OBJECT
public:
    typedef QActionManager<QKeySequence, QKeySequence, QAction*> KeyActionManager;

    explicit KeyConfigDialog(KeyActionManager& keyActions, QWidget *parent);
    ~KeyConfigDialog();

    bool eventFilter(QObject *obj, QEvent *event);
    void setEditTextWithoutSignal(QString text);
    void resetView();
    KeyActionManager& keyActions() { return m_keyActions; }

signals:

public slots:
    void onTreeWidget_currentItemChanged(QTreeWidgetItem* item, QTreeWidgetItem * previous);
    void onRecordButton_keySequenceChanged(QKeySequence key);
    void onResetButton_clicked();
    void onShortcutEdit_textChanged(QString text);
    void onStandardButton_clicked(QAbstractButton *button);


private:
    Ui::KeyConfigDialog *ui;
    QString m_actionName;
    KeyActionManager m_keyActions;
    bool m_ignoreEdited;
    bool m_keyCapturing;
};


#endif // KEYCONFIGDIALOG_H
