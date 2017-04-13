#include <QMap>
#include <QAction>
#include <QKeySequence>
#include <QTreeWidgetItem>
#include <QDebug>
#include <QKeyEvent>

#include "keyconfigdialog.h"
#include "shortcutbutton.h"
#include "ui_keyconfigdialog.h"

static int translateModifiers(Qt::KeyboardModifiers state,
                                         const QString &text)
{
    int result = 0;
    // The shift modifier only counts when it is not used to type a symbol
    // that is only reachable using the shift key anyway
    if ((state & Qt::ShiftModifier) && (text.size() == 0
                                        || !text.at(0).isPrint()
                                        || text.at(0).isLetterOrNumber()
                                        || text.at(0).isSpace()))
        result |= Qt::SHIFT;
    if (state & Qt::ControlModifier)
        result |= Qt::CTRL;
    if (state & Qt::MetaModifier)
        result |= Qt::META;
    if (state & Qt::AltModifier)
        result |= Qt::ALT;
    if (state & Qt::KeypadModifier)
        result |= Qt::KeypadModifier;
    return result;
}

static QString keySequenceToEditString(const QKeySequence &sequence)
{
    QString text = sequence.toString(QKeySequence::PortableText);
//    if (Utils::HostOsInfo::isMacHost()) {
//        // adapt the modifier names
//        text.replace(QLatin1String("Ctrl"), QLatin1String("Cmd"), Qt::CaseInsensitive);
//        text.replace(QLatin1String("Alt"), QLatin1String("Opt"), Qt::CaseInsensitive);
//        text.replace(QLatin1String("Meta"), QLatin1String("Ctrl"), Qt::CaseInsensitive);
//    }
    return text;
}

static QKeySequence keySequenceFromEditString(const QString &editString)
{
    QString text = editString;
//    if (Utils::HostOsInfo::isMacHost()) {
//        // adapt the modifier names
//        text.replace(QLatin1String("Opt"), QLatin1String("Alt"), Qt::CaseInsensitive);
//        text.replace(QLatin1String("Ctrl"), QLatin1String("Meta"), Qt::CaseInsensitive);
//        text.replace(QLatin1String("Cmd"), QLatin1String("Ctrl"), Qt::CaseInsensitive);
//    }
    return QKeySequence::fromString(text, QKeySequence::PortableText);
}

static bool keySequenceIsValid(const QKeySequence &sequence)
{
    if (sequence.isEmpty())
        return true;
    for (int i = 0; i < sequence.count(); ++i) {
        if (sequence[i] == Qt::Key_unknown)
            return false;
    }
    return true;
}

ShortcutButton::ShortcutButton(QWidget *parent)
    : QPushButton(parent)
    , m_key({{0, 0, 0, 0}})
{
    // Using ShortcutButton::tr() as workaround for QTBUG-34128
    setToolTip(ShortcutButton::tr("Click and type the new key sequence."));
    setCheckable(true);
    m_checkedText = ShortcutButton::tr("Stop Recording");
    m_uncheckedText = ShortcutButton::tr("Record");
    updateText();
    connect(this, &ShortcutButton::toggled, this, &ShortcutButton::handleToggleChange);
}

QSize ShortcutButton::sizeHint() const
{
    if (m_preferredWidth < 0) { // initialize size hint
        const QString originalText = text();
        ShortcutButton *that = const_cast<ShortcutButton *>(this);
        that->setText(m_checkedText);
        m_preferredWidth = QPushButton::sizeHint().width();
        that->setText(m_uncheckedText);
        int otherWidth = QPushButton::sizeHint().width();
        if (otherWidth > m_preferredWidth)
            m_preferredWidth = otherWidth;
        that->setText(originalText);
    }
    return QSize(m_preferredWidth, QPushButton::sizeHint().height());
}

bool ShortcutButton::eventFilter(QObject *obj, QEvent *evt)
{
    if (evt->type() == QEvent::ShortcutOverride) {
        evt->accept();
        return true;
    }
    if (evt->type() == QEvent::KeyRelease
               || evt->type() == QEvent::Shortcut
               || evt->type() == QEvent::Close/*Escape tries to close dialog*/) {
        return true;
    }
    if (evt->type() == QEvent::MouseButtonPress && isChecked()) {
        setChecked(false);
        return true;
    }
    if (evt->type() == QEvent::KeyPress) {
        QKeyEvent *k = static_cast<QKeyEvent*>(evt);
        int nextKey = k->key();
        if (m_keyNum > 3
                || nextKey == Qt::Key_Control
                || nextKey == Qt::Key_Shift
                || nextKey == Qt::Key_Meta
                || nextKey == Qt::Key_Alt) {
             return false;
        }

        nextKey |= translateModifiers(k->modifiers(), k->text());
        switch (m_keyNum) {
        case 0:
            m_key[0] = nextKey;
            break;
        case 1:
            m_key[1] = nextKey;
            break;
        case 2:
            m_key[2] = nextKey;
            break;
        case 3:
            m_key[3] = nextKey;
            break;
        default:
            break;
        }
        m_keyNum++;
        k->accept();
        emit keySequenceChanged(QKeySequence(m_key[0], m_key[1], m_key[2], m_key[3]));
        if (m_keyNum > 3)
            setChecked(false);
        return true;
    }
    return QPushButton::eventFilter(obj, evt);
}

void ShortcutButton::updateText()
{
    setText(isChecked() ? m_checkedText : m_uncheckedText);
}

void ShortcutButton::handleToggleChange(bool toogleState)
{
    updateText();
    m_keyNum = m_key[0] = m_key[1] = m_key[2] = m_key[3] = 0;
    if (toogleState) {
        if (qApp->focusWidget())
            qApp->focusWidget()->clearFocus(); // funny things happen otherwise
        qApp->installEventFilter(this);
    } else {
        qApp->removeEventFilter(this);
    }
}


KeyConfigDialog::KeyConfigDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::KeyConfigDialog)
    , m_keyCapturing(false)
    , m_ignoreEdited(false)
{
    ui->setupUi(this);
    connect(ui->recordButton, &ShortcutButton::keySequenceChanged,
            this, &KeyConfigDialog::on_keySequence_changed);

    ui->treeWidget->sortByColumn(0, Qt::AscendingOrder);
    QTreeWidgetItem *header = ui->treeWidget->headerItem();
    header->setText(0, tr("Command"));
    header->setText(1, tr("Label"));
    header->setText(2, tr("Target"));

    QVApplication* app = qApp;
    QMap<QString, QAction*>& actions = qApp->ActionMapByName();
    QMap<QString, QKeySequence>& keyconfigs = qApp->KeyConfigMap();
    foreach(const QString& key, actions.keys()) {
        QAction* action = actions[key];
        if(!action) continue;
        QTreeWidgetItem* item = new QTreeWidgetItem;
        item->setText(0, key);
        item->setText(1, action->iconText());
        item->setText(2, keyconfigs.contains(key) ? keyconfigs[key].toString() : "");
//        item->setSizeHint(0, QSize(240, 20));
//        item->setSizeHint(1, QSize(240, 20));
        ui->treeWidget->addTopLevelItem(item);
    }


}
KeyConfigDialog::~KeyConfigDialog()
{
    delete ui;
}

bool KeyConfigDialog::eventFilter(QObject *obj, QEvent *event)
{
    return QObject::eventFilter(obj, event);

}

void KeyConfigDialog::setEditTextWithoutSignal(QString text)
{
    m_ignoreEdited = true;
    ui->shortcutEdit->setText(text);
    m_ignoreEdited = false;
}

void KeyConfigDialog::revertKeyChanges()
{
    qApp->revertKeyMap(m_prevKeyConfigs);
}

void KeyConfigDialog::on_currentCommandChanged(QTreeWidgetItem *item, QTreeWidgetItem *)
{
    //qDebug() << "on_currentCommandChanged: " << (item ? item->text(0):"nullptr") << (previous ? previous->text(0) :"nullptr");
    if(item) {
        m_actionName = item->text(0);
        ui->shortcutGroupBox->setEnabled(true);
        ui->shortcutEdit->setText(item->text(2));
    }
}

void KeyConfigDialog::on_keySequence_changed(QKeySequence key)
{
    //qDebug() << "on_keySequence_changed:" << key;
    if(!m_prevKeyConfigs.contains(m_actionName))
        m_prevKeyConfigs[m_actionName] = qApp->getKey(m_actionName);

    QString shortcutText = keySequenceToEditString(key);
    setEditTextWithoutSignal(shortcutText);
    if(!keySequenceIsValid(key)) {
        ui->warningLabel->setText(tr("Invalid key sequence."));
        return;
    }
    if(markCollisions(key)) {
        ui->warningLabel->setText(tr("Key sequence has potential conflicts."));
        return;
    }
    ui->warningLabel->clear();


    QTreeWidgetItem *current = ui->treeWidget->currentItem();
    current->setText(2, shortcutText);
    qApp->setKeySequence(m_actionName, key);

}

void KeyConfigDialog::on_resetToDefault()
{
    QKeySequence key = qApp->getKeyDefault(m_actionName);
    QString shortcutText = keySequenceToEditString(key);
    setEditTextWithoutSignal(shortcutText);
    if(markCollisions(key)) {
        ui->warningLabel->setText(tr("Key sequence has potential conflicts."));
        return;
    }
    ui->warningLabel->clear();

    QTreeWidgetItem *current = ui->treeWidget->currentItem();
    current->setText(2, shortcutText);
    qApp->setKeySequence(m_actionName, key);
}

void KeyConfigDialog::on_shortcutClearButton_triggered()
{

}

void KeyConfigDialog::on_shortcutEdit_changed(QString text)
{
    if(!m_ignoreEdited) {
        QKeySequence key(text);
        if(!keySequenceIsValid(key)) {
            ui->warningLabel->setText(tr("Invalid key sequence."));
            return;
        }
        on_keySequence_changed(key);
    }
}

bool KeyConfigDialog::markCollisions(QKeySequence key)
{
    QMap<QKeySequence, QString>& keymap = qApp->KeyConfigMapReverse();
    for(int i = 0; i < key.count(); i++) {
        QKeySequence k(key[i]);
        if(keymap.contains(k) && keymap[k] != m_actionName) {
            return true;
        }
    }
    return false;
}
