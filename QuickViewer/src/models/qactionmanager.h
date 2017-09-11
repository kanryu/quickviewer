#ifndef QACTIONMANAGER_H
#define QACTIONMANAGER_H

#include <QtCore>

template<typename Key, typename Value, typename Action>
class QActionManager
{
public:
    explicit QActionManager()
    {

    }
    explicit QActionManager(QActionManager& rhs)
        : m_actionByName(rhs.m_actionByName)
        , m_keyByName(rhs.m_keyByName)
        , m_keyByNameDefaults(rhs.m_keyByNameDefaults)
        , m_nameByValue(rhs.m_nameByValue)
    {
        m_actionByName.detach();
        m_keyByName.detach();
        m_keyByNameDefaults.detach();
        m_nameByValue.detach();
    }

    void operator=(QActionManager& rhs)
    {
        m_actionByName = rhs.m_actionByName;
        m_keyByName = rhs.m_keyByName;
        m_keyByNameDefaults = rhs.m_keyByNameDefaults;
        m_nameByValue = rhs.m_nameByValue;
    }
    void registAction(QString name, Action& action, QString group)
    {
        m_actionByName[name] = action;
        m_nameByGroup.insert(group, name);
    }
    void copyActions(QMap<QString, Action>& rhs)
    {
        m_actionByName = rhs;
    }

    void addDefaultKey(QString name, Key key)
    {
        m_keyByNameDefaults[name] = key;
        m_keyByName[name] = key;
        for(int i = 0; i < key.count(); i++) {
            m_nameByValue[Value(key[i])] = name;
        }
    }

    QMap<QString, Action>& actions() { return m_actionByName; }
    QMap<QString, Key>& keyMaps() { return m_keyByName; }
    Key getKey(const QString& name) { return m_keyByName.contains(name) ? m_keyByName[name] : Key(); }
    Key getKeyDefault(const QString& name) { return m_keyByNameDefaults.contains(name) ? m_keyByNameDefaults[name] : Key(); }
    Action getActionByKey(const Value& value) {
        if(!m_nameByValue.contains(value))
            return Action();
        QString name = m_nameByValue[value];
        return m_actionByName[name];
    }
    bool markCollisions(const QString& name, Key key)
    {
        if(!m_actionByName.contains(name))
            return true;
        for(int i = 0; i < key.count(); i++) {
            if(!m_nameByValue.contains(key[i]))
                continue;
            QString nm = m_nameByValue[key[i]];
            if(nm != name)
                return true;
        }
        return false;
    }

    void updateKey(const QString& name, Key key, bool force=false) {
        if(!force && !m_actionByName.contains(name))
            return;
        Key old = m_keyByName[name];
        for(int i = 0; i < old.count(); i++) {
            m_nameByValue.remove(Value(old[i]));
        }
        m_keyByName[name] = key;
        for(int i = 0; i < key.count(); i++) {
            m_nameByValue[Value(key[i])] = name;
        }
    }
    void resetByDefault() {
        m_keyByName.clear();
        m_nameByValue.clear();
        foreach(const QString& name, m_keyByNameDefaults.keys()) {
            Key key = m_keyByNameDefaults[name];
            m_keyByName[name] = key;
            for(int i = 0; i < key.count(); i++) {
                m_nameByValue[Value(key[i])] = name;
            }
        }
    }

private:
    QMap<QString, Action> m_actionByName;
    QMultiMap<QString, QString> m_nameByGroup;
    QMap<QString, Key> m_keyByName;
    QMap<QString, Key> m_keyByNameDefaults;
    QMap<Value, QString> m_nameByValue;
};

#endif // QACTIONMANAGER_H
