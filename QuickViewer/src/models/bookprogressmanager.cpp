
#include "bookprogressmanager.h"
#include "qvapplication.h"

BookProgressManager::BookProgressManager(QObject *parent)
    : QObject(parent)
{
    connect(&m_initializeWatcher, SIGNAL(finished()), SLOT(on_Initialized_triggered()));
    QFuture<BookProgressMap> future = QtConcurrent::run(&BookProgressManager::initializeAsync);
    m_initializeWatcher.setFuture(future);
}

static QString getProgressIniPath()
{
    return qApp->getFilePathOfApplicationSetting(PROGRESS_INI);
}


void BookProgressManager::save()
{
    QSettings settings(getProgressIniPath(), QSettings::IniFormat, this);
    //settings.setIniCodec(QTextCodec::codecForName("UTF-8"));

    QStringList titles;
    foreach(const BookProgress& book, m_books.values()) {
        QString group = QString("Volume_%1").arg(titles.size()+1,4,10,QChar('0'));
        settings.beginGroup(group);
        settings.setValue("Title", book.Title);
        settings.setValue("Path", book.Path);
        settings.setValue("CurrenPage", book.CurrenPage);
        settings.setValue("Pages", book.Pages);
        settings.setValue("Current", book.Current);
        settings.setValue("Completed", book.Completed);
        settings.endGroup();
        titles << group;
    }
    settings.sync();
}

BookProgressManager::BookProgressMap BookProgressManager::initializeAsync()
{
    QSettings settings(getProgressIniPath(), QSettings::IniFormat);
    //settings.setIniCodec(QTextCodec::codecForName("UTF-8"));

    BookProgressMap result;
    QStringList groups = settings.childGroups();
    foreach(const QString g, groups) {
        settings.beginGroup(g);
        QString path = settings.value("Path", "").toString();
        if(path.isEmpty())
            continue;
        QString title = settings.value("Title", "").toString();
        QString currentPage = settings.value("CurrenPage", "").toString();
        int pages = settings.value("Pages", 0).toInt();
        int current = settings.value("Current", 0).toInt();
        bool completed = settings.value("Completed", false).toBool();
        BookProgress book = {
          title, path, currentPage, pages, current, completed
        };
        result[path] = book;
        settings.endGroup();
    }
    return result;
}

void BookProgressManager::on_Initialized_triggered()
{
    m_books = m_initializeWatcher.result();
}

