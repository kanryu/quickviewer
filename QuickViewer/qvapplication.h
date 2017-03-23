#ifndef QVAPPLICATION_H
#define QVAPPLICATION_H

#include <QApplication>
#include <QSettings>


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

public:
    explicit QVApplication(int &argc, char **argv);
    bool Fitting() { return m_fitting; }
    void setFitting (bool fitting) { m_fitting = fitting; }
    bool DualView() { return m_dualView; }
    void setDualView (bool dualView) { m_dualView = dualView; }
    bool RightSideBook() { return m_rightSideBook; }
    void setRightSideBook (bool rightSideBook) { m_rightSideBook = rightSideBook; }
    bool WideImageAsOnePageInDualView() { return m_wideImageAsOnePageInDualView; }
    void setWideImageAsOnePageInDualView (bool wideImageAsOnePageInDualView) { m_wideImageAsOnePageInDualView = wideImageAsOnePageInDualView; }

    int MaxHistoryCount() { return m_maxHistoryCount; }
    void setMaxHistoryCount (int maxHistoryCount) { m_maxHistoryCount = maxHistoryCount; }
    bool AutoLoaded() { return m_autoLoaded; }
    void setAutoLoaded (bool autoLoaded) { m_autoLoaded = autoLoaded; }
    QStringList History() const { return m_history; }

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
    /**
     * @brief if true, a wide image must be one view whether dual view is enabled
     */
    bool m_wideImageAsOnePageInDualView;
    QSettings m_settings;
    QStringList m_history;
};

#endif // QVAPPLICATION_H
