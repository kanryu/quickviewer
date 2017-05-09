#ifndef SHORTCUTBUTTON_H
#define SHORTCUTBUTTON_H

#include <array>
#include <QtWidgets>

struct ShortcutItem
{
    QAction *m_action;
    QKeySequence m_key;
    QTreeWidgetItem *m_item;
};


class ShortcutButton : public QPushButton
{
    Q_OBJECT
public:
    ShortcutButton(QWidget *parent = 0);

    QSize sizeHint() const;

signals:
    void keySequenceChanged(QKeySequence sequence);

protected:
    bool eventFilter(QObject *obj, QEvent *evt);

private:
    void updateText();
    void handleToggleChange(bool toggleState);

    QString m_checkedText;
    QString m_uncheckedText;
    mutable int m_preferredWidth = -1;
    std::array<int, 4> m_key;
    int m_keyNum = 0;
};


#endif // SHORTCUTBUTTON_H
