#include "mouseconfigdialog.h"
#include "ui_keyconfigdialog.h"


MouseConfigDialog::MouseConfigDialog(MouseConfigDialog::MouseActionManager &mouseActions, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::KeyConfigDialog)
    , m_mouseActions(mouseActions)
    , m_keyCapturing(false)
    , m_ignoreEdited(false)
{
    ui->setupUi(this);
    ui->frameMouseOptions->setEnabled(false);
    ui->recordButton->setVisible(false);
    setWindowTitle(tr("Mouse Config", "Title of the dialog to customize the mouse sequences"));
    ui->label->setText(tr("Mouse Sequence:", "Title of LineEdit label to which mouse sequence is input"));
    ui->shortcutEdit->setPlaceholderText(tr("Select the combination of the checks below, press the 'Add Sequence' button", "Placeholder text urging the mouse input setting procedure"));

#ifdef Q_OS_WIN
    ui->checkBoxMeta->setVisible(false);
#endif
#ifdef Q_OS_MAC
    ui->checkBoxMeta->setText(tr("Command", "caption of Command key"));
    ui->checkBoxAlt->setText(tr("Option", "caption of Option key"));
#endif


    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    connect(ui->buttonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(onStandardButton_clicked(QAbstractButton*)));
    connect(ui->treeWidget, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)), this, SLOT(onTreeWidget_currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)));
    connect(ui->resetButton, SIGNAL(clicked()), this, SLOT(onResetButton_clicked()));
    connect(ui->addSequenceButton, SIGNAL(clicked()), this, SLOT(onAddSequenceButton_clicked()));
    connect(ui->shortcutEdit, SIGNAL(textChanged(QString)), this, SLOT(onShortcutEdit_textChanged(QString)));

    connect(ui->checkBoxLeft, SIGNAL(toggled(bool)), this, SLOT(onCheckBox_toggled()));
    connect(ui->checkBoxRight, SIGNAL(toggled(bool)), this, SLOT(onCheckBox_toggled()));
    connect(ui->checkBoxWheel, SIGNAL(toggled(bool)), this, SLOT(onCheckBox_toggled()));
    connect(ui->checkBoxForward, SIGNAL(toggled(bool)), this, SLOT(onCheckBox_toggled()));
    connect(ui->checkBoxBackward, SIGNAL(toggled(bool)), this, SLOT(onCheckBox_toggled()));
    connect(ui->radioButtonDown, SIGNAL(toggled(bool)), this, SLOT(onCheckBox_toggled()));
    connect(ui->radioButtonNone, SIGNAL(toggled(bool)), this, SLOT(onCheckBox_toggled()));
    connect(ui->radioButtonUp, SIGNAL(toggled(bool)), this, SLOT(onCheckBox_toggled()));

//    connect(ui->recordButton, &ShortcutButton::keySequenceChanged,
//            this, &MouseConfigDialog::on_keySequence_changed);

    ui->treeWidget->sortByColumn(0, Qt::AscendingOrder);
    QTreeWidgetItem *header = ui->treeWidget->headerItem();
    header->setText(0, tr("Motions", "Title of the column of Action to be registered with the mouse sequence"));
    header->setText(1, tr("Description", "Title of the column that displays the meaning of the action to be registered with the mouse sequence"));
    header->setText(2, tr("Current Mouse Sequence", "Title of the column of the content of the mouse sequence registered for Action"));

    resetView();
}

void MouseConfigDialog::resetView()
{
    ui->treeWidget->clear();
    QMap<QString, QAction*>& actions = m_mouseActions.actions();
    QMap<QString, QMouseSequence>& mouseconfigs = m_mouseActions.keyMaps();
    foreach(const QString& key, actions.keys()) {
        QAction* action = actions[key];
        if(!action) continue;
        QTreeWidgetItem* item = new QTreeWidgetItem;
        item->setText(0, key);
        item->setText(1, action->iconText());
        item->setText(2, mouseconfigs.contains(key) ? mouseconfigs[key].toString() : "");
//        item->setSizeHint(0, QSize(240, 20));
//        item->setSizeHint(1, QSize(240, 20));
        ui->treeWidget->addTopLevelItem(item);
    }

}

MouseConfigDialog::~MouseConfigDialog()
{
    delete ui;
}

void MouseConfigDialog::setEditTextWithoutSignal(QString text)
{
    m_ignoreEdited = true;
    ui->shortcutEdit->setText(text);
    m_ignoreEdited = false;
}

void MouseConfigDialog::onTreeWidget_currentItemChanged(QTreeWidgetItem *item, QTreeWidgetItem *)
{
    if(item) {
        m_actionName = item->text(0);
        ui->shortcutGroupBox->setEnabled(true);
        QString shortcut = item->text(2);
        ui->shortcutEdit->setText(shortcut);
        ui->frameMouseOptions->setEnabled(true);
        resetMouseCheckBox();
        onCheckBox_toggled();
    }
}

void MouseConfigDialog::onRecordButton_keySequenceChanged(QMouseSequence key)
{
    QString shortcutText = key.toString();
    setEditTextWithoutSignal(shortcutText);
    if(!shortcutText.isEmpty() && m_mouseActions.markCollisions(m_actionName, key)) {
        ui->warningLabel->setText(tr("Mouse sequence has potential conflicts.", "Text to be displayed when the entered mouse sequence conflicts with another mouse sequence"));
        return;
    }
    ui->warningLabel->clear();
    resetMouseCheckBox();


    QTreeWidgetItem *current = ui->treeWidget->currentItem();
    current->setText(2, shortcutText);
    m_mouseActions.updateKey(m_actionName, key);
}

void MouseConfigDialog::onAddSequenceButton_clicked()
{
    Qt::KeyboardModifiers keys;
    if(ui->checkBoxCtrl->isChecked())  keys |= Qt::ControlModifier;
    if(ui->checkBoxAlt->isChecked())   keys |= Qt::AltModifier;
    if(ui->checkBoxShift->isChecked()) keys |= Qt::ShiftModifier;
    if(ui->checkBoxMeta->isChecked()) keys |= Qt::MetaModifier;

    Qt::MouseButtons buttons = 0;
    if(ui->checkBoxLeft->isChecked())     buttons |= Qt::LeftButton;
    if(ui->checkBoxRight->isChecked())    buttons |= Qt::RightButton;
    if(ui->checkBoxWheel->isChecked())    buttons |= Qt::MiddleButton;
    if(ui->checkBoxForward->isChecked())  buttons |= Qt::ForwardButton;
    if(ui->checkBoxBackward->isChecked()) buttons |= Qt::BackButton;
    QKeySequence keyseq(keys);
    qDebug() << keyseq;
    keyseq = QKeySequence();
    QMouseValue newval(QKeySequence(keys), buttons,
                       ui->radioButtonUp->isChecked()   ?  Q_MOUSE_DELTA
                     : ui->radioButtonDown->isChecked() ? -Q_MOUSE_DELTA
                     : 0);
    QString seqtext = ui->shortcutEdit->text();
    seqtext += seqtext.isEmpty() ? newval.Key : ", "+newval.Key;
    onRecordButton_keySequenceChanged(QMouseSequence(seqtext));
}

void MouseConfigDialog::onResetButton_clicked()
{
    QMouseSequence key = m_mouseActions.getKeyDefault(m_actionName);
//    QString shortcutText = keySequenceToEditString(key);
    QString shortcutText = key.toString();
    setEditTextWithoutSignal(shortcutText);
    if(m_mouseActions.markCollisions(m_actionName, key)) {
        ui->warningLabel->setText(tr("Mouse sequence has potential conflicts.", "Text to be displayed when the entered mouse sequence conflicts with another mouse sequence"));
        return;
    }
    ui->warningLabel->clear();

    QTreeWidgetItem *current = ui->treeWidget->currentItem();
    current->setText(2, shortcutText);
    m_mouseActions.updateKey(m_actionName, key);
}

void MouseConfigDialog::onShortcutEdit_textChanged(QString text)
{
    if(!m_ignoreEdited) {
        QMouseSequence key(text);
//        if(!keySequenceIsValid(key)) {
//            ui->warningLabel->setText(tr("Invalid mouse sequence.", "Message when rejecting input contents of inappropriate mouse sequence"));
//            return;
//        }
        onRecordButton_keySequenceChanged(key);
    }
}

void MouseConfigDialog::onCheckBox_toggled()
{
    bool enabled = ui->checkBoxLeft->isChecked()
            || ui->checkBoxRight->isChecked()
            || ui->checkBoxWheel->isChecked()
            || ui->checkBoxForward->isChecked()
            || ui->checkBoxBackward->isChecked()
            || ui->radioButtonDown->isChecked()
            || ui->radioButtonUp->isChecked();
    ui->addSequenceButton->setEnabled(enabled);
}

void MouseConfigDialog::onStandardButton_clicked(QAbstractButton *button)
{
    switch(ui->buttonBox->standardButton(button)) {
    case QDialogButtonBox::RestoreDefaults:
        m_mouseActions.resetByDefault();
        resetView();
        break;
    }
}

void MouseConfigDialog::resetMouseCheckBox()
{
    ui->checkBoxCtrl->setChecked(false);
    ui->checkBoxShift->setChecked(false);
    ui->checkBoxAlt->setChecked(false);
    ui->checkBoxMeta->setChecked(false);

    ui->checkBoxLeft->setChecked(false);
    ui->checkBoxRight->setChecked(false);
    ui->checkBoxWheel->setChecked(false);
    ui->checkBoxForward->setChecked(false);
    ui->checkBoxBackward->setChecked(false);

    ui->radioButtonNone->setChecked(true);
}
