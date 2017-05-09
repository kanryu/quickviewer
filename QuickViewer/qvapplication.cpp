#include <QtGui>
#include <QtOpenGL>

#include "qvapplication.h"
#include "qv_init.h"
#include "ui_mainwindow.h"

QVApplication::QVApplication(int &argc, char **argv)
    : QApplication(argc, argv)
    , m_settings(getApplicationFilePath(APP_INI), QSettings::IniFormat, this)
    , m_effect(ShaderManager::Bilinear)
    , m_glInitialized(false)
    , m_maxTextureSize(4096)
{
    setApplicationVersion(APP_VERSION);
    setApplicationName(APP_NAME);
    setOrganizationName(APP_ORGANIZATION);

    // Default key configs
    m_keyConfigDefauls["actionExitApplicationOrFullscreen"] = QKeySequence("Esc");
    m_keyConfigDefauls["actionNextPage"] = QKeySequence("L, Right, Space");
    m_keyConfigDefauls["actionPrevPage"] = QKeySequence("H, Left, Backspace");
    m_keyConfigDefauls["actionScaleUp"] = QKeySequence("K, Num++");
    m_keyConfigDefauls["actionScaleDown"] = QKeySequence("J, Num+-");
    m_keyConfigDefauls["actionManageCatalog"] = QKeySequence("F6");
    m_keyConfigDefauls["actionSlideShow"] = QKeySequence("F7");
    m_keyConfigDefauls["actionStayOnTop"] = QKeySequence("F8");
    m_keyConfigDefauls["actionShowMenuBar"] = QKeySequence("F9");
    m_keyConfigDefauls["actionDualView"] = QKeySequence("Y, F10");
    m_keyConfigDefauls["actionFullscreen"] = QKeySequence("F11");
    m_keyConfigDefauls["actionFitting"] = QKeySequence("M, F12, Num+*");
    m_keyConfigDefauls["actionRotate"] = QKeySequence("R");
    m_keyConfigDefauls["actionLastPage"] = QKeySequence("Ctrl+L, End");
    m_keyConfigDefauls["actionFirstPage"] = QKeySequence("Ctrl+H, Home");
    m_keyConfigDefauls["actionNextVolume"] = QKeySequence("PgDown");
    m_keyConfigDefauls["actionPrevVolume"] = QKeySequence("PgUp");
    m_keyConfigDefauls["actionDeletePage"] = QKeySequence("Del");

    m_keyConfigDefauls["actionCopyPage"] = QKeySequence("Ctrl+C");
    m_keyConfigDefauls["actionCopyFile"] = QKeySequence("Ctrl+Shift+C");

    m_keyConfigDefauls["actionLoadBookmark"] = QKeySequence("Q");
    m_keyConfigDefauls["actionSaveBookmark"] = QKeySequence("W");

    m_keyConfigDefauls["actionMaximizeOrNormal"] = QKeySequence("Return, Num+Enter");

    m_keyConfigDefauls["actionFastForward"] = QKeySequence("Shift+L, Num+3");
    m_keyConfigDefauls["actionFastBackward"] = QKeySequence("Shift+H, Num+1");

    m_keyConfigs = m_keyConfigDefauls;
    m_keyConfigs.detach();

    //qDebug() << m_keyConfigs;

    m_settings.setIniCodec(QTextCodec::codecForName("UTF-8"));

    loadSettings();
    //qDebug() << m_keyConfigs;
}

QString QVApplication::getApplicationFilePath(QString subFilePath)
{
    return QDir::toNativeSeparators(QString("%1/%2").arg(applicationDirPath()).arg(subFilePath));
}

void QVApplication::registActions(Ui::MainWindow *ui)
{
    // File
    registAction("actionOpenFolder", ui->actionOpenFolder);
    registAction("actionClearHistory", ui->actionClearHistory);
    registAction("actionAutoLoaded", ui->actionAutoLoaded);
    registAction("actionExit", ui->actionExit);
    registAction("actionManageCatalog", ui->actionManageCatalog);


    // Bookmark
    registAction("actionClearBookmarks", ui->actionClearBookmarks);
    registAction("actionLoadBookmark", ui->actionLoadBookmark);
    registAction("actionSaveBookmark", ui->actionSaveBookmark);

    // Navigation
    registAction("actionNextPage", ui->actionNextPage);
    registAction("actionPrevPage", ui->actionPrevPage);
    registAction("actionFastForward", ui->actionFastForward);
    registAction("actionFastBackward", ui->actionFastBackward);
    registAction("actionLastPage", ui->actionLastPage);
    registAction("actionFirstPage", ui->actionFirstPage);
    registAction("actionNextVolume", ui->actionNextVolume);
    registAction("actionPrevVolume", ui->actionPrevVolume);
    registAction("actionNextOnePage", ui->actionNextOnePage);
    registAction("actionPrevOnePage", ui->actionPrevOnePage);
    registAction("actionSlideShow", ui->actionSlideShow);

    // View
    registAction("actionRotate", ui->actionRotate);
    registAction("actionFitting", ui->actionFitting);
    registAction("actionScaleUp", ui->actionScaleUp);
    registAction("actionScaleDown", ui->actionScaleDown);
    registAction("actionStayOnTop", ui->actionStayOnTop);

    registAction("actionDualView", ui->actionDualView);
    registAction("actionRightSideBook", ui->actionRightSideBook);
    registAction("actionWideImageAsOneView", ui->actionWideImageAsOneView);
    registAction("actionFirstImageAsOneView", ui->actionFirstImageAsOneView);

    registAction("actionFullscreen", ui->actionFullscreen);
    registAction("actionExitApplicationOrFullscreen", ui->actionExitApplicationOrFullscreen);
    registAction("actionMaximizeOrNormal", ui->actionMaximizeOrNormal);
    registAction("actionRestoreWindowState", ui->actionRestoreWindowState);

    // Toolbar
    registAction("actionShowToolBar", ui->actionShowToolBar);
    registAction("actionShowStatusBar", ui->actionShowStatusBar);
    registAction("actionShowPageBar", ui->actionShowPageBar);
    registAction("actionShowMenuBar", ui->actionShowMenuBar);

    // ContextMenu
    registAction("actionOpenFiler", ui->actionOpenFiler);
    registAction("actionOpenExif", ui->actionOpenExif);
    registAction("actionCopyPage", ui->actionCopyPage);
    registAction("actionCopyFile", ui->actionCopyFile);
    registAction("actionDeletePage", ui->actionDeletePage);

    registAction("actionOpenKeyConfig", ui->actionOpenKeyConfig);
    registAction("actionCheckVersion", ui->actionCheckVersion);
    registAction("actionAppVersion", ui->actionAppVersion);

    // Shader
    registAction("actionShaderNearestNeighbor", ui->actionShaderNearestNeighbor);
    registAction("actionShaderBilinear", ui->actionShaderBilinear);
    registAction("actionShaderBicubic", ui->actionShaderBicubic);
    registAction("actionShaderLanczos", ui->actionShaderLanczos);
}

void QVApplication::onGLInitialized()
{
    const QGLContext* c0 = QGLContext::currentContext();
    if(c0) {
        QOpenGLContext* c1 = QOpenGLContext::currentContext();
        //QOpenGLContext* c2 = c0->contextHandle();
        if(c1 && c1->isValid()) {
            c1->functions()->glGetIntegerv(GL_MAX_TEXTURE_SIZE, &m_maxTextureSize);
            qDebug() << m_maxTextureSize;
        }
    }
}

void QVApplication::addHistory(QString path)
{
    const QString unixpath = QDir::fromNativeSeparators(path);
    if(m_history.contains(unixpath)) {
        m_history.removeOne(unixpath);
    }
    m_history.push_front(unixpath);
    while(m_history.size() > m_maxHistoryCount)
        m_history.pop_back();
}

void QVApplication::addBookMark(QString path, bool canDumplication)
{
    const QString unixpath = QDir::fromNativeSeparators(path);
    if(canDumplication) {
        m_bookmarks.push_front(unixpath);
        return;
    }
    if(m_bookmarks.contains(unixpath)) {
        m_bookmarks.removeOne(unixpath);
    }
    m_bookmarks.push_front(unixpath);
    while(m_bookmarks.size() > m_maxBookmarkCount)
        m_bookmarks.pop_back();
}

void QVApplication::loadSettings()
{
    bool bRightSideBookDefault = QLocale::system().language() == QLocale::Japanese;
    m_settings.beginGroup("View");
    m_fitting = m_settings.value("Fitting", true).toBool();
    m_dualView = m_settings.value("DualView", false).toBool();
    m_stayOnTop = m_settings.value("StayOnTop", false).toBool();

    m_rightSideBook = m_settings.value("RightSideBook", bRightSideBookDefault).toBool();
    m_wideImageAsOnePageInDualView = m_settings.value("WideImageAsOnePageInDualView", true).toBool();
    m_firstImageAsOnePageInDualView = m_settings.value("FirstImageAsOnePageInDualView", false).toBool();

    m_showToolBar = m_settings.value("ShowToolBar", true).toBool();
    m_showSliderBar = m_settings.value("ShowSliderBar", true).toBool();
    m_showStatusBar = m_settings.value("ShowStatusBar", true).toBool();
    m_showMenuBar = m_settings.value("ShowMenuBar", true).toBool();
    m_settings.endGroup();

    m_settings.beginGroup("WindowState");
    m_restoreWindowState  = m_settings.value("RestoreWindowState", false).toBool();
    m_windowGeometry  = m_settings.value("WindowGeometry", "").toByteArray();
    m_windowState  = m_settings.value("WindowState", "").toByteArray();
    m_settings.endGroup();

    m_settings.beginGroup("File");
    m_autoLoaded  = m_settings.value("AutoLoaded", true).toBool();
    m_history = m_settings.value("History", QStringList()).value<QStringList>();
    m_maxHistoryCount = m_settings.value("MaxHistoryCount", 36).toInt();
    m_bookmarks = m_settings.value("Bookmarks", QStringList()).value<QStringList>();
    m_maxBookmarkCount = m_settings.value("MaxBookmarkCount", 20).toInt();
    m_settings.endGroup();

    m_settings.beginGroup("KeyConfig");
    foreach(const QString& action, m_settings.childKeys()) {
        QString str = m_settings.value(action, "").toString();
        m_keyConfigs[action] = QKeySequence(str);
    }
    m_settings.endGroup();

    m_settings.beginGroup("Shader");
    QString effectstring = m_settings.value("Effect", "Bilinear").toString();
    m_effect = ShaderManager::stringToShaderEffect(effectstring);
    m_bicubicShaderPath = m_settings.value("BicubicShaderPath", "shaders/bicubic.frag").toString();
    m_lanczosShaderPath = m_settings.value("LanczosShaderPath", "shaders/lanczos.frag").toString();
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

    m_settings.beginGroup("WindowState");
    m_settings.setValue("RestoreWindowState", m_restoreWindowState);
    m_settings.setValue("WindowGeometry", m_windowGeometry);
    m_settings.setValue("WindowState", m_windowState);

    m_settings.endGroup();

    m_settings.beginGroup("File");
    m_settings.setValue("AutoLoaded", m_autoLoaded);
    m_settings.setValue("MaxHistoryCount", m_maxHistoryCount);
    m_settings.setValue("History", QVariant::fromValue(m_history));
    m_settings.setValue("MaxBookmarkCount", m_maxBookmarkCount);
    m_settings.setValue("Bookmarks", QVariant::fromValue(m_bookmarks));
    m_settings.endGroup();

    m_settings.beginGroup("KeyConfig");
    foreach(const QString& action, m_keyConfigs.keys()) {
        QKeySequence seqs = m_keyConfigs[action];
        m_settings.setValue(action, seqs.toString());
    }
    m_settings.endGroup();

    m_settings.beginGroup("Shader");
    m_settings.setValue("Effect", ShaderManager::shaderEffectToString(m_effect));
    m_settings.setValue("BicubicShaderPath", m_bicubicShaderPath);
    m_settings.setValue("LanczosShaderPath", m_lanczosShaderPath);
    m_settings.endGroup();


    m_settings.sync();
}
