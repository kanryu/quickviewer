#ifndef BOOKSHELFMANAGER_H
#define BOOKSHELFMANAGER_H

#include <QtGui>
#include <QtCore>
#include <QtConcurrent>

#include "qv_init.h"

/**
 * @brief The BookProgress class
 * the page progress of volume
 */
class BookProgress
{
public:
    QString Title;
    QString Path;
    QString CurrenPage;
    int Pages;
    int Current;
    bool Completed;
};

/**
 * @brief The BookshelfManager class
 * a manager contains the page progress of volumes, that saved into some local file(currently ./bookshelf.ini)
 */
class BookProgressManager : QObject
{
    Q_OBJECT
public:
    typedef QMap<QString, BookProgress> BookProgressMap;

    BookProgressManager(QObject* parent);
    void save();

    BookProgressMap initializeAsync();

    bool contains(QString path) { return m_books.contains(path); }
    BookProgress at(QString path) { return m_books[path]; }
    void insert(QString path, BookProgress& value) { m_books.insert(path, value); }

public slots:
    void on_Initialized_triggered();

private:
    BookProgressMap m_books;
    QFutureWatcher<BookProgressMap> m_initializeWatcher;
};

#endif // BOOKSHELFMANAGER_H
