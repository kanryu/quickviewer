#include <QTextCodec>
#include <QLocale>
#include <QKeySequence>
#include <QDebug>

#include "qvapplication.h"
#include "qv_init.h"
#include "ui_mainwindow.h"

QVApplication::QVApplication(int &argc, char **argv)
    : QApplication(argc, argv)
    , m_settings(APP_INI, QSettings::IniFormat, this)
{
    setApplicationVersion(APP_VERSION);
    setApplicationName(APP_NAME);
    setOrganizationName(APP_ORGANIZATION);

    // Default key configs
    m_keyConfigDefauls["actionExitApplicationOrFullscreen"] = QKeySequence("Esc");
    m_keyConfigDefauls["actionNextPage"] = QKeySequence("Right, Space");
    m_keyConfigDefauls["actionPrevPage"] = QKeySequence("Left, Backspace");
    m_keyConfigDefauls["actionScaleUp"] = QKeySequence("+");
    m_keyConfigDefauls["actionScaleDown"] = QKeySequence("-");
    m_keyConfigDefauls["actionFitting"] = QKeySequence("F12, *");
    m_keyConfigDefauls["actionFullscreen"] = QKeySequence("F11");
    m_keyConfigDefauls["actionStayOnTop"] = QKeySequence("F8");
    m_keyConfigDefauls["actionShowMenuBar"] = QKeySequence("F9");
    m_keyConfigDefauls["actionLastPage"] = QKeySequence("End");
    m_keyConfigDefauls["actionFirstPage"] = QKeySequence("Home");
    m_keyConfigDefauls["actionNextVolume"] = QKeySequence("PgDown");
    m_keyConfigDefauls["actionPrevVolume"] = QKeySequence("PgUp");
    m_keyConfigDefauls["actionDeletePage"] = QKeySequence("Del");
    m_keyConfigDefauls["actionCopyPage"] = QKeySequence("Ctrl+C");

    m_keyConfigs = m_keyConfigDefauls;
    m_keyConfigs.detach();

    //qDebug() << m_keyConfigs;

    m_settings.setIniCodec(QTextCodec::codecForName("UTF-8"));

    loadSettings();
    //qDebug() << m_keyConfigs;
}

void QVApplication::registActions(Ui::MainWindow *ui)
{
    registAction("actionExit", ui->actionExit);
    registAction("actionClearHistory", ui->actionClearHistory);
    registAction("actionExitApplicationOrFullscreen", ui->actionExitApplicationOrFullscreen);
    registAction("actionNextPage", ui->actionNextPage);
    registAction("actionPrevPage", ui->actionPrevPage);
    registAction("actionScaleUp", ui->actionScaleUp);
    registAction("actionScaleDown", ui->actionScaleDown);
    registAction("actionFitting", ui->actionFitting);
    registAction("actionDualView", ui->actionDualView);
    registAction("actionFullscreen", ui->actionFullscreen);
    registAction("actionStayOnTop", ui->actionStayOnTop);
    registAction("actionAppVersion", ui->actionAppVersion);
    registAction("actionAutoLoaded", ui->actionAutoLoaded);
    registAction("actionRightSideBook", ui->actionRightSideBook);
    registAction("actionOpenFolder", ui->actionOpenFolder);
    registAction("actionWideImageAsOneView", ui->actionWideImageAsOneView);
    registAction("actionFirstImageAsOneView", ui->actionFirstImageAsOneView);
    registAction("actionLastPage", ui->actionLastPage);
    registAction("actionFirstPage", ui->actionFirstPage);
    registAction("actionShowToolBar", ui->actionShowToolBar);
    registAction("actionShowStatusBar", ui->actionShowStatusBar);
    registAction("actionShowPageBar", ui->actionShowPageBar);
    registAction("actionShowMenuBar", ui->actionShowMenuBar);
    registAction("actionOpenFiler", ui->actionOpenFiler);
    registAction("actionOpenExif", ui->actionOpenExif);
    registAction("actionOpenKeyConfig", ui->actionOpenKeyConfig);
    registAction("actionCheckVersion", ui->actionCheckVersion);
    registAction("actionNextVolume", ui->actionNextVolume);
    registAction("actionPrevVolume", ui->actionPrevVolume);
    registAction("actionNextOnePage", ui->actionNextOnePage);
    registAction("actionPrevOnePage", ui->actionPrevOnePage);
    registAction("actionCopyPage", ui->actionCopyPage);
    registAction("actionDeletePage", ui->actionDeletePage);
}

void QVApplication::addHistory(QString path)
{
    if(m_history.contains(path)) {
        m_history.removeOne(path);
    }
    m_history.push_front(path);
    while(m_history.size() > m_maxHistoryCount)
        m_history.pop_back();
}

void QVApplication::loadSettings()
{
    bool bRightSideBookDefault = QLocale::system().language() == QLocale::Japanese;
    m_settings.beginGroup("View");
    m_fitting = m_settings.value("Fitting", true).toBool();
    m_dualView = m_settings.value("DualView", false).toBool();
    m_stayOnTop = m_settings.value("StayOnTop", false).toBool();

    m_rightSideBook = m_settings.value("RightSideBook", bRightSideBookDefault).toBool();
    m_wideImageAsOnePageInDualView = m_settings.value("WideImageAsOnePageInDualView", false).toBool();
    m_firstImageAsOnePageInDualView = m_settings.value("FirstImageAsOnePageInDualView", false).toBool();

    m_showToolBar = m_settings.value("ShowToolBar", true).toBool();
    m_showSliderBar = m_settings.value("ShowSliderBar", true).toBool();
    m_showStatusBar = m_settings.value("ShowStatusBar", true).toBool();
    m_showMenuBar = m_settings.value("ShowMenuBar", true).toBool();
    m_settings.endGroup();

    m_settings.beginGroup("File");
    m_autoLoaded  = m_settings.value("AutoLoaded", false).toBool();
    m_history = m_settings.value("History", QStringList()).value<QStringList>();
    m_maxHistoryCount = m_settings.value("MaxHistoryCount", 36).toInt();
    m_settings.endGroup();

    m_settings.beginGroup("KeyConfig");
    foreach(const QString& action, m_settings.childKeys()) {
        QString str = m_settings.value(action, "").toString();
        m_keyConfigs[action] = QKeySequence(str);
    }
    m_settings.endGroup();
}

void QVApplication::saveSettings()
{
    m_settings.beginGroup("View");
    m_settings.setValue("Fitting", m_fitting);
    m_settings.setValue("DualView", m_dualView);
    m_settings.setValue("StayOnTop", m_stayOnTop);

    m_settings.setValue("RightSideBook", m_rightSideBook);
    m_settings.setValue("WideImageAsOnePageInDualView", m_wideImageAsOnePageInDualView);
    m_settings.setValue("FirstImageAsOnePageInDualView", m_firstImageAsOnePageInDualView);

    m_settings.setValue("ShowToolBar", m_showToolBar);
    m_settings.setValue("ShowSliderBar", m_showSliderBar);
    m_settings.setValue("ShowStatusBar", m_showStatusBar);
    m_settings.setValue("ShowMenuBar", m_showMenuBar);
    m_settings.endGroup();

    m_settings.beginGroup("File");
    m_settings.setValue("AutoLoaded", m_autoLoaded);
    m_settings.setValue("MaxHistoryCount", m_maxHistoryCount);
    m_settings.setValue("History", QVariant::fromValue(m_history));
    m_settings.endGroup();

    m_settings.beginGroup("KeyConfig");
    foreach(const QString& action, m_keyConfigs.keys()) {
        QKeySequence seqs = m_keyConfigs[action];
        m_settings.setValue(action, seqs.toString());
    }
    m_settings.endGroup();



    m_settings.sync();
}
