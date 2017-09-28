#ifndef IMAGESTRING_H
#define IMAGESTRING_H

#include <QtCore>

class ImageView;
class PageManager;

/**
 * @brief The ImageString class
 * Return outline information of the currently displayed image as text.
 *
 * These information are input as PageManager and PageContent,
 *  and are outputted as a model format character string dedicated to them.
 */
class ImageString
{
public:
    ImageString();
    void initialize(PageManager* pm, ImageView* view);

    QString getTitleBarText();
    QString getStatusBarText();
    QString formatString(QString fmt);

private:
    PageManager* m_pageManager;
    const QVector<PageContent>* m_pages;
};

#endif // IMAGESTRING_H
