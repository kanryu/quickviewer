#ifndef QMOUSESEQUENCE_H
#define QMOUSESEQUENCE_H

#include <QtGui>

#define Q_MOUSE_DELTA 120

/**
 * @brief The QMouseValue class
 *
 * QMouseValue is a unit that constitutes QMouseSequence,
 * and defines one combination of key input and mouse input.
 */
class QMouseValue
{
public:
    QMouseValue()
        : KeyboardModifier("")
        , Buttons(0)
        , Delta(0) {}

    QMouseValue(const QString key);

    QMouseValue(QKeySequence modifiers, Qt::MouseButtons buttons, int delta)
        : KeyboardModifier(modifiers)
        , Buttons(buttons)
        , Delta(delta) {toString();}

    QMouseValue(const QMouseValue& rhs)
        : KeyboardModifier(rhs.KeyboardModifier)
        , Buttons(rhs.Buttons)
        , Delta(rhs.Delta)
        , Key(rhs.Key){}

    inline QMouseValue& operator=(const QMouseValue &rhs)
    {
        KeyboardModifier = rhs.KeyboardModifier;
        Buttons = rhs.Buttons;
        Delta = rhs.Delta;
        Key = rhs.Key;
        return *this;
    }

    inline bool operator==(const QMouseValue &other) const
    {
        return KeyboardModifier == other.KeyboardModifier
                && Buttons == other.Buttons
                && Delta == other.Delta;
    }
    inline bool operator<(const QMouseValue &other) const
    {
        return Key < other.Key;
    }


    QString toString();

    QKeySequence KeyboardModifier;
    Qt::MouseButtons Buttons;
    int Delta;
    QString Key;
};



/**
 * @brief The QMouseSequence class
 *
 * QMouseSequence is a class created by mimicking QKeySequence
 * and holds mouse buttons, wheels, key codes as unique values.
 *
 * Instances of this class are values rather than objects,
 * are copyable and comparable, and do not have destructors.
 * Therefore, you can use this class as QMap's Key or Value.
 *
 * QMouseSequence is effectively a list of instances of QMouseValue.
 *
 * A QMouseValue instance can be serialized to a string,
 * and a QMouseSequence instance can be serialized with ',' separator in one string.
 */
class QMouseSequence
{
public:
    QMouseSequence() {}
    QMouseSequence(const QString seq);
    inline QString toString() const {return m_seq;}
    const QList<QMouseValue>& Values() const { return m_values; }
    QKeySequence::SequenceMatch matches(const QMouseSequence &seq) const;

    inline QMouseSequence& operator=(const QMouseSequence &rhs)
    {
        m_seq = rhs.m_seq;
        m_values = rhs.m_values;
        m_values.detach();
        return *this;
    }

    inline bool operator==(const QMouseSequence &rhs) const
    {
        return m_seq == rhs.m_seq;
    }
    inline bool operator<(const QMouseSequence &rhs) const
    {
        return m_seq < rhs.m_seq;
    }
    inline QString operator[](const int idx) { return m_values[idx].toString(); }
    inline int count() const { return m_values.count(); }

private:
    QString m_seq;
    QList<QMouseValue> m_values;
};

#endif // QMOUSESEQUENCE_H
