#include "qvapplication.h"
#include "qv_init.h"
#include <QTextCodec>
#include <QLocale>

QVApplication::QVApplication(int &argc, char **argv)
    : QApplication(argc, argv)
    , m_settings(APP_INI, QSettings::IniFormat, this)
{
    setApplicationVersion(APP_VERSION);
    setApplicationName(APP_NAME);
    setOrganizationName(APP_ORGANIZATION);

    m_settings.setIniCodec(QTextCodec::codecForName("UTF-8"));

    loadSettings();
}

void QVApplication::addHistory(QString path)
{
    if(m_history.contains(path)) {
        m_history.removeOne(path);
    }
    m_history.push_front(path);
}

void QVApplication::loadSettings()
{
    bool bRightSideBookDefault = QLocale::system().language() == QLocale::Japanese;
    m_settings.beginGroup("View");
    m_fitting = m_settings.value("Fitting", false).toBool();
    m_dualView = m_settings.value("DualView", false).toBool();
    m_rightSideBook = m_settings.value("RightSideBook", bRightSideBookDefault).toBool();
    m_settings.endGroup();

    m_settings.beginGroup("File");
    m_autoLoaded  = m_settings.value("AutoLoaded", false).toBool();
    m_history = m_settings.value("History", QStringList()).value<QStringList>();
    m_maxHistoryCount = m_settings.value("MaxHistoryCount", 30).toInt();
    m_settings.endGroup();
}

void QVApplication::saveSettings()
{
    m_settings.beginGroup("View");
    m_settings.setValue("Fitting", m_fitting);
    m_settings.setValue("DualView", m_dualView);
    m_settings.setValue("RightSideBook", m_rightSideBook);
    m_settings.endGroup();

    m_settings.beginGroup("File");
    m_settings.setValue("AutoLoaded", m_autoLoaded);
    m_settings.setValue("MaxHistoryCount", m_maxHistoryCount);
    m_settings.setValue("History", QVariant::fromValue(m_history));

    m_settings.sync();
}
