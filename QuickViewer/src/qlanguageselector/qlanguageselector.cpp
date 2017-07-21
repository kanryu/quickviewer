#include "qlanguageselector.h"

QLanguageSelector::QLanguageSelector(QString prefix, QString path)
    : QObject(nullptr)
    , m_prefix(prefix)
    , m_path(path)
    , m_translator(nullptr)
{
    initialize();
}


LanguageInfo QLanguageSelector::getLanguageInfo(QString languageId)
{
    if(m_languages.contains(languageId))
        return m_languages[languageId];
    return getSystemLanguageInfo();
}

LanguageInfo QLanguageSelector::getSystemLanguageInfo()
{
    auto systemLocale = QLocale::system();
    foreach(const QString& lang, m_languageList) {
        LanguageInfo info = m_languages[lang];
        auto locale = QLocale(info.Code);
        if(locale.name() == systemLocale.name())
            return info;
    }
    return m_languages[LANGUAGE_DEFUALT];
}

void QLanguageSelector::resetTranslator(QString languageId)
{
    LanguageInfo info = getLanguageInfo(languageId);
    m_uiLanguage = info.Caption;
    if(m_translator) {
        qApp->removeTranslator(m_translator);
        delete m_translator;
    }
    m_translator = new QTranslator;
    bool exist = m_translator->load(QLocale(info.Code),
                                 m_path, m_prefix, qApp->applicationDirPath());
    if(exist) {
        qApp->installTranslator(m_translator);
    } else {
        delete m_translator;
        m_translator = nullptr;
    }
    emit languageChanged(info.Caption);
}

QString QLanguageSelector::getApplicationFilePath(QString subFilePath)
{
    return QDir::toNativeSeparators(QString("%1/%2").arg(qApp->applicationDirPath()).arg(subFilePath));
}

void QLanguageSelector::initialize()
{
    QString inipath = getLanguageIniPath();
    QSettings settings(getLanguageIniPath(), QSettings::IniFormat, this);
    settings.setIniCodec(QTextCodec::codecForName("UTF-8"));

    QStringList groups = settings.childGroups();
    foreach(const QString g, groups) {
        settings.beginGroup(g);
        LanguageInfo info = {
            settings.value("code", "").toString(),
            settings.value("caption", "").toString(),
            settings.value("qm", "").toString(),
        };
        m_languages[info.Caption] = info;
        m_languageList << info.Caption;
        settings.endGroup();
    }
}

QString QLanguageSelector::getLanguageIniPath()
{
    return getApplicationFilePath(m_path + LANGUAGES_INI);
}

void QLanguageSelector::clearLanguageMenus()
{
    foreach(QAction *action, m_actions) {
        action->setChecked(false);
    }
}

void QLanguageSelector::initializeMenu(QMenu* parent)
{
    auto self = this;
    foreach(const QString& lang, m_languageList) {
        LanguageInfo info = m_languages[lang];
        QAction* action = parent->addAction(info.Caption);
        action->setCheckable(true);
        if(m_uiLanguage == info.Caption) {
            action->setChecked(true);
        }
        connect(action, &QAction::triggered, this, [=]() {
            clearLanguageMenus();
            action->setChecked(true);
            self->resetTranslator(info.Caption);
        });
        m_actions << action;
    }
}
