#include "imagestring.h"
#include "pagecontent.h"
#include "pagemanager.h"

#include "qvapplication.h"

ImageString::ImageString()
    : m_pageManager(nullptr)
    , m_pages(nullptr)
{

}

void ImageString::initialize(PageManager *pm, ImageView *view)
{
    m_pageManager = pm;
    m_pages = view->pages();
}

QString ImageString::getTitleBarText()
{
    if(m_pages->empty())
        return QString("%1 v%2").arg(qApp->applicationName()).arg(qApp->applicationVersion());
    return QString("%1 - %2")
            .arg(formatString(qApp->ShowStatusBar() ? qApp->TitleTextFormat() : qApp->StatusTextFormat()))
            .arg(qApp->applicationName());
}

QString ImageString::getStatusBarText()
{
    return m_pages->isEmpty() ? "" : formatString(qApp->StatusTextFormat());
}

QString ImageString::formatString(QString fmt)
{
    QList<int> pages = qApp->RightSideBook() ? QList<int>{1,0} : QList<int>{0,1};
    const QStringList tags = {
        "%v", // volume name (only folder/archive name), e.g. "Sample Book"
        "%V", // volume full path, e.g. "C:/Users/qv/Desktop/Sample Book"
        "%p", // image file name (only file name), e.g. "page01.jpg"
        "%P", // image file path in volume, e.g. "subpath/page01.jpg"
        "%s", // image size, e.g. "1920x1080"
        "%m", // Display magnification of image, e.g. "25%"
        "%f", // image file size with usefull, e.g. "63.23 KB"
        "%F", // image file size as correct number of bytes, e.g. "1,154,340 Bytes"
        "%b", // image bitmap size with useful, e.g. "1.59 MB"
        "%n", // current page number of the volume e.g. "33/100" or "33-34/100"
        "%2", // second image format string(when 2 page spread viewing is valid)
    };
    QStringList result;
    int p = 0;
    for (int i = 0; i < fmt.length(); i++) {
        QChar c = fmt.at(i);
        if(c != '%' || i+1==fmt.length()) {
            result << c;
            continue;
        }
        c = fmt.at(++i);
        const PageContent& page = m_pages->at(m_pages->size() == 2 ? pages[p] : 0);
        switch(c.toLatin1()) {
        case 'v':
        {
            QFileInfo info(m_pageManager->volumePath());
            result << info.fileName();
            break;
        }
        case 'V': result << m_pageManager->volumePath(); break;
        case 'p':
        {
            QFileInfo info(page.Ic.Path);
            result << info.fileName();
            break;
        }
        case 'P': result << page.Ic.Path; break;
        case 's': result << QString("%1x%2").arg(page.Ic.BaseSize.width()).arg(page.Ic.BaseSize.height()); break;
        case 'm': result << QString("%1%").arg((int)(100*page.DrawScale)); break;
        case 'f': {
            double filelength = page.Ic.FileLength;
            if(filelength < 1024)
                result << QString("%1 Bytes").arg(filelength);
            else if(filelength < 1024*1024)
                result << QString("%1 KB").arg(filelength/1024, 0, 'f', 2);
            else
                result << QString("%1 MB").arg(filelength/1024/1024, 0, 'f', 2);
            break;
        }
        case 'F': result << QString("%L1 Bytes").arg(page.Ic.FileLength); break;
        case 'b': {
            double filelength = page.Ic.Image.byteCount();
            if(filelength < 1024)
                result << QString("%1 Bytes").arg(filelength);
            else if(filelength < 1024*1024)
                result << QString("%1 KB").arg(filelength/1024, 0, 'f', 2);
            else
                result << QString("%1 MB").arg(filelength/1024/1024, 0, 'f', 2);
            break;
        }
        case 'n': {
            if(m_pages->size()==2)
                result << QString("%1-%2/%3").arg(m_pageManager->currentPage()+1).arg(m_pageManager->currentPage()+2).arg(m_pageManager->size());
            else
                result << QString("%1/%2").arg(m_pageManager->currentPage()+1).arg(m_pageManager->size());
            break;
        }
        case '2': {
            if(m_pages->size() < 2)
                i = fmt.length();
            p++;
            break;
        }
        default: result << "%" << c; break;
        }
    }
    return result.join("");
}
