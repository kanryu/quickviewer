#ifndef QVAPPLICATION_H
#define QVAPPLICATION_H

#include <QApplication>
#include <QSettings>
#include <QMap>


#if defined(qApp)
#undef qApp
#endif
#define qApp (static_cast<QVApplication *>(QCoreApplication::instance()))


#define APP_INI "quickviewer.ini"

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
    Q_PROPERTY(QMap<QString, QStringList> KeyConfigMap READ KeyConfigMap)

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
    QMap<QString, QStringList>& KeyConfigMap() { return m_keyConfigs; }
    void setKey (const QString& action, QStringList& keymap) { m_keyConfigs[action] = keymap; }
    QStringList getKey (const QString& action) { return m_keyConfigs.contains(action) ? m_keyConfigs[action] : QStringList(); }

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
    QMap<QString, QStringList> m_keyConfigs;
};

#endif // QVAPPLICATION_H
