#ifndef QVAPPLICATION_H
#define QVAPPLICATION_H

#include <QApplication>
#include <QSettings>
#include <QMap>
#include <QKeySequence>
#include "shadermanager.h"

#if defined(qApp)
#undef qApp
#endif
#define qApp (static_cast<QVApplication *>(QCoreApplication::instance()))


#define APP_INI "quickviewer.ini"

namespace Ui {
class MainWindow;
}

class QAction;
//typedef QList<QKeySequence> QKeySequenceList;


class QVApplication : public QApplication
{
    Q_OBJECT

    // File
    Q_PROPERTY(bool AutoLoaded READ AutoLoaded WRITE setAutoLoaded)
    Q_PROPERTY(int MaxHistoryCount READ MaxHistoryCount WRITE setMaxHistoryCount)
    // Bookmark
//    Q_PROPERTY(int MaxBookmarkCount READ MaxBookmarkCount WRITE setMaxBookmarkCount)

    // Fitting
    Q_PROPERTY(bool Fitting READ Fitting WRITE setFitting)

    // DuapView
    Q_PROPERTY(bool DualView READ DualView WRITE setDualView)
    Q_PROPERTY(bool RightSideBook READ RightSideBook WRITE setRightSideBook)
    Q_PROPERTY(bool WideImageAsOnePageInDualView READ WideImageAsOnePageInDualView WRITE setWideImageAsOnePageInDualView)
    Q_PROPERTY(bool FirstImageAsOnePageInDualView READ FirstImageAsOnePageInDualView WRITE setFirstImageAsOnePageInDualView)

    Q_PROPERTY(bool StayOnTop READ StayOnTop WRITE setStayOnTop)
    // ToolBars
    Q_PROPERTY(bool ShowToolBar READ ShowToolBar WRITE setShowToolBar)
    Q_PROPERTY(bool ShowSliderBar READ ShowSliderBar WRITE setShowSliderBar)
    Q_PROPERTY(bool ShowStatusBar READ ShowStatusBar WRITE setShowStatusBar)
    Q_PROPERTY(bool ShowMenuBar READ ShowMenuBar WRITE setShowMenuBar)

    // WindowStates
    Q_PROPERTY(bool RestoreWindowState READ RestoreWindowState WRITE setRestoreWindowState)
    Q_PROPERTY(QByteArray WindowGeometry READ WindowGeometry WRITE setWindowGeometry)
    Q_PROPERTY(QByteArray WindowState READ WindowState WRITE setWindowState)

    // Shaders
    Q_PROPERTY(ShaderManager::ShaderEffect Effect READ Effect WRITE setEffect)
    Q_PROPERTY(QString BicubicShaderPath READ BicubicShaderPath WRITE setBicubicShaderPath)
    Q_PROPERTY(QString LanczosShaderPath READ LanczosShaderPath WRITE setLanczosShaderPath)

    // Key Config
    Q_PROPERTY(QMap<QString, QKeySequence> KeyConfigMap READ KeyConfigMap)

public:
    explicit QVApplication(int &argc, char **argv);
    QString getApplicationFilePath(QString subFilePath);

    // View
    bool Fitting() { return m_fitting; }
    void setFitting (bool fitting) { m_fitting = fitting; }
    bool DualView() { return m_dualView; }
    void setStayOnTop (bool stayOnTop) { m_stayOnTop = stayOnTop; }
    bool StayOnTop() { return m_stayOnTop; }
    void setDualView (bool dualView) { m_dualView = dualView; }
    bool RightSideBook() { return m_rightSideBook; }
    void setRightSideBook (bool rightSideBook) { m_rightSideBook = rightSideBook; }
    bool WideImageAsOnePageInDualView() { return m_wideImageAsOnePageInDualView; }
    void setWideImageAsOnePageInDualView (bool wideImageAsOnePageInDualView) { m_wideImageAsOnePageInDualView = wideImageAsOnePageInDualView; }
    bool FirstImageAsOnePageInDualView() { return m_firstImageAsOnePageInDualView; }
    void setFirstImageAsOnePageInDualView (bool firstImageAsOnePageInDualView) { m_firstImageAsOnePageInDualView = firstImageAsOnePageInDualView; }

    // Show Bars
    bool ShowToolBar() { return m_showToolBar; }
    void setShowToolBar (bool showToolBar) { m_showToolBar = showToolBar; }
    bool ShowSliderBar() { return m_showSliderBar; }
    void setShowSliderBar (bool showSliderBar) { m_showSliderBar = showSliderBar; }
    bool ShowStatusBar() { return m_showStatusBar; }
    void setShowStatusBar (bool showStatusBar) { m_showStatusBar = showStatusBar; }
    bool ShowMenuBar() { return m_showMenuBar; }
    void setShowMenuBar (bool showMenuBar) { m_showMenuBar = showMenuBar; }

    // RestoreWindowState
    bool RestoreWindowState() { return m_restoreWindowState; }
    void setRestoreWindowState (bool restoreWindowState) { m_restoreWindowState = restoreWindowState; }
    QByteArray WindowGeometry() { return m_windowGeometry; }
    void setWindowGeometry (QByteArray windowGeometry) { m_windowGeometry = windowGeometry; }
    QByteArray WindowState() { return m_windowState; }
    void setWindowState (QByteArray windowState) { m_windowState = windowState; }

    // File
    void setMaxHistoryCount (int maxHistoryCount) { m_maxHistoryCount = maxHistoryCount; }
    bool AutoLoaded() { return m_autoLoaded; }
    void setAutoLoaded (bool autoLoaded) { m_autoLoaded = autoLoaded; }
    // History
    int MaxHistoryCount() { return m_maxHistoryCount; }
    const QStringList& History() const { return m_history; }
    void clearHistory() { m_history.clear(); }
    /**
     * @brief addHistory add a path int History. if it is already in History, it will be top of this.
     * @param path
     */
    void addHistory(QString path);

    // BookMark
    QStringList& Bookmarks() { return m_bookmarks; }
    void clearBookmarks() { m_bookmarks.clear(); }
    void addBookMark(QString path, bool canDumplication=false);

    // ShaderEffect
    ShaderManager::ShaderEffect Effect() { return m_effect; }
    void setEffect (ShaderManager::ShaderEffect shaderEffect) { m_effect = shaderEffect; }
    QString BicubicShaderPath() { return getApplicationFilePath(m_bicubicShaderPath); }
    void setBicubicShaderPath (QString bicubicShaderPath) { m_bicubicShaderPath = bicubicShaderPath; }
    QString LanczosShaderPath() { return getApplicationFilePath(m_lanczosShaderPath); }
    void setLanczosShaderPath (QString lanczosShaderPath) { m_lanczosShaderPath = lanczosShaderPath; }

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
    void registActions(Ui::MainWindow* ui);
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
    void onGLInitialized();
    int maxTextureSize() { return m_maxTextureSize; }

    /**
     * @brief load settings from "quickviewer.ini"
     */
    void loadSettings();
    /**
     * @brief save settings int "quickviewer.ini"
     */
    void saveSettings();

private:
    bool m_glInitialized;
    int m_maxTextureSize;
    bool m_fitting;
    bool m_dualView;
    bool m_stayOnTop;
    /**
     * @brief if true, it will be supported for 'bound on the left side books'(e.g. books in Japan)
     */
    bool m_rightSideBook;
    int m_maxHistoryCount;
    int m_maxBookmarkCount;
    bool m_autoLoaded;
    bool m_showToolBar;
    bool m_showSliderBar;
    bool m_showStatusBar;
    bool m_showMenuBar;

    // WindowStates
    bool m_restoreWindowState;
    QByteArray m_windowGeometry;
    QByteArray m_windowState;

    /**
     * @brief if true, a wide image must be one view whether dual view is enabled
     */
    bool m_wideImageAsOnePageInDualView;
    bool m_firstImageAsOnePageInDualView;
    // Shader Effect
    ShaderManager::ShaderEffect m_effect;
    QString m_bicubicShaderPath;
    QString m_lanczosShaderPath;

    QSettings m_settings;
    QStringList m_history;
    QStringList m_bookmarks;
    QMap<QString, QKeySequence> m_keyConfigs;
    QMap<QString, QKeySequence> m_keyConfigDefauls;
    QMap<QString, QAction*> m_actionsByName;
    QMap<QKeySequence, QString> m_keyConfigsReverse;
};

#endif // QVAPPLICATION_H
