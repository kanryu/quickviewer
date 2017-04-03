#ifndef QVAPPLICATION_H
#define QVAPPLICATION_H

#include <QApplication>
#include <QSettings>
#include <QMap>
#include <QKeySequence>


#if defined(qApp)
#undef qApp
#endif
#define qApp (static_cast<QVApplication *>(QCoreApplication::instance()))


#define APP_INI "quickviewer.ini"

class QAction;
//typedef QList<QKeySequence> QKeySequenceList;

class QVApplication : public QApplication
{
    Q_OBJECT
    Q_PROPERTY(bool Fitting READ Fitting WRITE setFitting)
    Q_PROPERTY(bool DualView READ DualView WRITE setDualView)
    Q_PROPERTY(bool RightSideBook READ RightSideBook WRITE setRightSideBook)
    Q_PROPERTY(int MaxHistoryCount READ MaxHistoryCount WRITE setMaxHistoryCount)
    Q_PROPERTY(bool AutoLoaded READ AutoLoaded WRITE setAutoLoaded)
    Q_PROPERTY(bool WideImageAsOnePageInDualView READ WideImageAsOnePageInDualView WRITE setWideImageAsOnePageInDualView)
    Q_PROPERTY(bool ShowSliderBar READ ShowSliderBar WRITE setShowSliderBar)
    Q_PROPERTY(bool ShowStatusBar READ ShowStatusBar WRITE setShowStatusBar)
    Q_PROPERTY(QMap<QString, QKeySequence> KeyConfigMap READ KeyConfigMap)

public:
    explicit QVApplication(int &argc, char **argv);
    // View
    bool Fitting() { return m_fitting; }
    void setFitting (bool fitting) { m_fitting = fitting; }
    bool DualView() { return m_dualView; }
    void setDualView (bool dualView) { m_dualView = dualView; }
    bool RightSideBook() { return m_rightSideBook; }
    void setRightSideBook (bool rightSideBook) { m_rightSideBook = rightSideBook; }
    bool WideImageAsOnePageInDualView() { return m_wideImageAsOnePageInDualView; }
    void setWideImageAsOnePageInDualView (bool wideImageAsOnePageInDualView) { m_wideImageAsOnePageInDualView = wideImageAsOnePageInDualView; }
    bool ShowSliderBar() { return m_showSliderBar; }
    void setShowSliderBar (bool showSliderBar) { m_showSliderBar = showSliderBar; }
    bool ShowStatusBar() { return m_showStatusBar; }
    void setShowStatusBar (bool showStatusBar) { m_showStatusBar = showStatusBar; }

    // File
    int MaxHistoryCount() { return m_maxHistoryCount; }
    void setMaxHistoryCount (int maxHistoryCount) { m_maxHistoryCount = maxHistoryCount; }
    bool AutoLoaded() { return m_autoLoaded; }
    void setAutoLoaded (bool autoLoaded) { m_autoLoaded = autoLoaded; }
    const QStringList& History() const { return m_history; }

    // Key Config
    QMap<QString, QKeySequence>& KeyConfigMap() { return m_keyConfigs; }
//    QString KeySequenceListToString(QKeySequenceList& list) const {
//        QStringList strs;
//        foreach(const QKeySequence& seq, list) {
//            strs << seq.toString();
//        }
//        return strs.join(", ");
//    }
    QString getKeySequenceSerialized(const QString& actionName) {
        if(!m_keyConfigs.contains(actionName))
            return "";
        QKeySequence seq = m_keyConfigs[actionName];
        return seq.toString();
    }

    QKeySequence getKey (const QString& actionName) { return m_keyConfigs.contains(actionName) ? m_keyConfigs[actionName] : QKeySequence(); }
    QKeySequence getKeyDefault (const QString& actionName) { return m_keyConfigDefauls.contains(actionName) ? m_keyConfigDefauls[actionName] : QKeySequence(); }
    QMap<QString, QAction*>& ActionMapByName() { return m_actionsByName; }
    QMap<QKeySequence, QString>& KeyConfigMapReverse() { return m_keyConfigsReverse; }
    void registAction(const QString& actionName, QAction* action) {
        m_actionsByName[actionName] = action;
        QKeySequence seq = m_keyConfigs[actionName];
        for(int i = 0; i < seq.count(); i++) {
            m_keyConfigsReverse[seq[i]] = actionName;
        }
    }
    void setKeySequence(const QString& actionName, const QKeySequence seq) {
        if(!m_actionsByName.contains(actionName))
            return;
        QKeySequence old = m_keyConfigs[actionName];
        for(int i = 0; i < old.count(); i++) {
            m_keyConfigsReverse.remove(QKeySequence(old[i]));
        }
        m_keyConfigs[actionName] = seq;
        for(int i = 0; i < seq.count(); i++) {
            m_keyConfigsReverse[seq[i]] = actionName;
        }
    }
    bool checkConflict(const QString& actionName, const QKeySequence seq) {
        if(!m_actionsByName.contains(actionName))
            return false;
        foreach(const QString& action, m_keyConfigs.keys()) {
            if(action == actionName)
                continue;
            QKeySequence current = m_keyConfigs[action];
            if(seq.matches(current) >= QKeySequence::PartialMatch)
                return false;
        }
        return true;
    }

    QAction* getAction(const QKeySequence seq) {
        if(!m_keyConfigsReverse.contains(seq))
            return nullptr;
        QString name = m_keyConfigsReverse[seq];
        return m_actionsByName[name];
    }

    void revertKeyMap(QMap<QString, QKeySequence> revertMap) {
        foreach(const QString& action, revertMap.keys()) {
            m_keyConfigs[action] = revertMap[action];
        }
        m_keyConfigsReverse.clear();
        foreach(const QString& action, m_keyConfigs.keys()) {
            QKeySequence seq = m_keyConfigs[action];
            for(int i = 0; i < seq.count(); i++) {
                m_keyConfigsReverse[seq[i]] = action;
            }
        }
    }

    /**
     * @brief addHistory add a path int History. if it is already in History, it will be top of this.
     * @param path
     */
    void addHistory(QString path);
    /**
     * @brief load settings from "quickviewer.ini"
     */
    void loadSettings();
    /**
     * @brief save settings int "quickviewer.ini"
     */
    void saveSettings();

private:
    bool m_fitting;
    bool m_dualView;
    /**
     * @brief if true, it will be supported for 'bound on the left side books'(e.g. books in Japan)
     */
    bool m_rightSideBook;
    int m_maxHistoryCount;
    bool m_autoLoaded;
    bool m_showSliderBar;
    bool m_showStatusBar;
    /**
     * @brief if true, a wide image must be one view whether dual view is enabled
     */
    bool m_wideImageAsOnePageInDualView;
    QSettings m_settings;
    QStringList m_history;
    QMap<QString, QKeySequence> m_keyConfigs;
    QMap<QString, QKeySequence> m_keyConfigDefauls;
    QMap<QString, QAction*> m_actionsByName;
    QMap<QKeySequence, QString> m_keyConfigsReverse;
};

#endif // QVAPPLICATION_H
