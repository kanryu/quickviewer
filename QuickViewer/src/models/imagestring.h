#ifndef IMAGESTRING_H
#define IMAGESTRING_H

#include <QtCore>

#include "pagecontent.h"
#include "pagemanager.h"

/**
 * @brief The ImageString class
 * Return outline information of the currently displayed image as text.
 *
 * These information are input as PageManager and PageContent,
 *  and are outputted as a model format character string dedicated to them.
 */
class ImageString : QObject
{
    Q_OBJECT
public:
    ImageString();
    void initialize(PageManagerProtocol* pm, PageContentProtocol* view);

    QString getTitleBarText();
    QString getStatusBarText();
    QString getFormatUsage();
    QString formatString(QString fmt);

private:
    PageManagerProtocol* m_pageManager;
    QVector<PageContent>* m_pages;
};



#endif // IMAGESTRING_H
