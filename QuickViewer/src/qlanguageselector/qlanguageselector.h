#ifndef QLANGUAGESELECTOR_H
#define QLANGUAGESELECTOR_H

#include <QtGui>
#include <QtWidgets>

#ifndef LANGUAGES_INI
  #define LANGUAGES_INI "languages.ini"
#endif
#ifndef LANGUAGE_DEFUALT
  #define LANGUAGE_DEFUALT "English"
#endif

struct LanguageInfo
{
    QString Code;
    QString Caption;
    QString Qm;
};


/**
 * @brief The QLanguageSelector class
 *
 * This object provides a mechanism for applications to make language changes by users.
 * Each language is registered as a child QAction menu of QMenu specified.
 * Each language is described in the ini file (usually "translations/languages.ini").
 * Allow users of the application to add new languages without changing the source code.
 * When the application user selects the Language Menu,
 *  the QLanguageSelector automatically sets the new QTranslator
 *  to qApp and replaces the language resources of the application.
 * Eventually the languageChanged signal is emitted and you can handle additional change events.
 */
class QLanguageSelector : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief QLanguageSelector
     * @param prefix: prefix of *.qm files  e.g. [prefix][langageId].qm
     * @param path: The path of the directory where the qm file is stored
     */
    QLanguageSelector(QString prefix, QString path="translations/");
    /**
     * @brief resetTranslator
     * @param languageId: language name in English
     *
     * Replace the language resources of the application.
     */
    void resetTranslator(QString languageId);
    QString language() { return m_uiLanguage; }
    QString getApplicationFilePath(QString subFilePath);

    /**
     * @brief initializeMenu
     * @param parent
     *
     * Create a menu that allows you to change the display language.
     * For each specified parent menu, add each language registered in language.ini as a submenu.
     * Each menu is checkable, and the currently selected menu is checked.
     * When the user selects a menu, the display language of the application is changed.
     */
    void initializeMenu(QMenu* parent);

    /**
     * @brief getLanguageInfo
     * @param languageId
     *
     * Returns an instance of the language information specified by languageId.
     * This is the information set in languages.ini.
     */
    LanguageInfo getLanguageInfo(QString languageId);

    /**
     * @brief getSystemLanguageInfo
     *
     * Returns language information that matches the language resource
     *  of the environment in which the application is executed.
     * If it does not match, it returns the language information specified by LANGUAGE_DEFUALT.
     */
    LanguageInfo getSystemLanguageInfo();

signals:
    /**
     * @brief languageChanged
     * @param language
     *
     * Called after the language resource of the application has been replaced.
     * To change the language of Widgets other than QMainWindow
     *  you should receive this signal in your slot.
     */
    void languageChanged(QString language);

private:
    QString m_uiLanguage;
    QTranslator *m_translator;
    QString m_path;
    QString m_prefix;
    QMap<QString, LanguageInfo> m_languages;
    QList<QAction*> m_actions;
    QStringList m_languageList;

    void initialize();
    QString getLanguageIniPath();
    void clearLanguageMenus();
};

#endif // QLANGUAGESELECTOR_H
