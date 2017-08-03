#include "qmousesequence.h"

QMouseValue::QMouseValue(const QString key)
    : KeyboardModifier()
    , Buttons(0)
    , Delta(0)
{
    auto rkey = key.trimmed();
    Key = rkey;

    // The separator must be included in the string,
    // it must be separated from QKeySequence.
    int sep = rkey.indexOf("+::");
    KeyboardModifier = QKeySequence(rkey.left(sep));
    QString mouse = rkey.mid(sep+3);
    if(mouse.isEmpty())
        return;
    foreach(const QString& mkey, mouse.split("+")) {
        if(mkey == "LeftButton")         Buttons |= Qt::LeftButton;
        else if(mkey == "RightButton")   Buttons |= Qt::RightButton;
        else if(mkey == "MiddleButton")  Buttons |= Qt::MiddleButton;
        else if(mkey == "BackButton")    Buttons |= Qt::BackButton;
        else if(mkey == "ForwardButton") Buttons |= Qt::ForwardButton;
        else if(mkey == "TaskButton")    Buttons |= Qt::TaskButton;
        else if(mkey == "ExtraButton4")  Buttons |= Qt::ExtraButton4;
        else if(mkey == "WheelUp")       Delta = Q_MOUSE_DELTA;
        else if(mkey == "WheelDown")     Delta = -Q_MOUSE_DELTA;
    }
}

QString QMouseValue::toString()
{
    if(!Key.isEmpty())
        return Key;
    QStringList out;
    if(Buttons & Qt::LeftButton)    out << "LeftButton";
    if(Buttons & Qt::RightButton)   out << "RightButton";
    if(Buttons & Qt::MiddleButton)  out << "MiddleButton";
    if(Buttons & Qt::BackButton)    out << "BackButton";
    if(Buttons & Qt::ForwardButton) out << "ForwardButton";
    if(Buttons & Qt::ExtraButton4)  out << "ExtraButton4";
    if(Delta > 0) out << "WheelUp";
    if(Delta < 0) out << "WheelDown";
    QString keymod = KeyboardModifier.toString();
//    qDebug() << keymod.mid(keymod.length()-2);
    if(!keymod.isEmpty() && keymod.mid(keymod.length()-2) != "++" && keymod.mid(keymod.length()-1) == "+")
        keymod = keymod.left(keymod.length()-1);
    Key = keymod + "+::" + out.join("+");
    return Key;
}

QMouseSequence::QMouseSequence(const QString seq)
{
    QStringList seqs = seq.split(", ");
    qSort(seqs);
    m_seq = seqs.join(", ");
    foreach(const QString& s, seqs) {
        m_values.append(QMouseValue(s));
    }
}

QKeySequence::SequenceMatch QMouseSequence::matches(const QMouseSequence &seq) const
{
    int cnt = 0;
    foreach(const QMouseValue& v1, m_values) {
        foreach(const QMouseValue& v2, seq.m_values) {
            if(v1 == v2) cnt++;
        }
    }
    if(cnt == 0) return QKeySequence::NoMatch;
    if(m_values.length() == seq.m_values.length() && cnt == m_values.length())
        return QKeySequence::ExactMatch;
    return QKeySequence::PartialMatch;
}
