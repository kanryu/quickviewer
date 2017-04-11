#include <QMouseEvent>
#include <QtDebug>
#include <QPainter>
#include <QGLWidget>
#include <QDesktopServices>
#include <QProcessEnvironment>
#include <QMessageBox>
#include <QClipboard>

#include "imageview.h"
#include "qvapplication.h"
#include "exifdialog.h"

ImageView::ImageView(QWidget *parent)
    : QGraphicsView(parent)
    , m_renderer(Native)
    , m_fileVolume(nullptr)
    , m_hoverState(Qt::AnchorHorizontalCenter)
    , m_currentPage(0)
    , m_wideImage(false)
    , exifDialog(this)
    , m_skipResizeEvent(false)
{
    viewSizeList << 25 << 33 << 50 << 75 << 100 << 150 << 200 << 300 << 400 << 800;
    viewSizeIdx = 4; // 100

    QGraphicsScene* scene = new QGraphicsScene(this);
    setScene(scene);
//    setTransformationAnchor(AnchorUnderMouse);
//    setDragMode(ScrollHandDrag);
//    setViewportUpdateMode(FullViewportUpdate);
    setAcceptDrops(false);
//    setDragMode(DragDropMode::InternalMove);
    setRenderer(OpenGL);

    setMouseTracking(true);


}


//void ImageView::setImage(ImageContent pixmap)
//{
//    if(m_fileVolume == nullptr) return;
//    clearImages();
//    addImage(pixmap, true);
//}

bool ImageView::addImage(ImageContent ic, bool pageNext)
{
    if(m_fileVolume == nullptr) return false;
    m_ptLeftTop.reset();
    QGraphicsScene *s = scene();


    QSize size;
    QPoint offset;
    QGraphicsItem* gitem = nullptr;
    if(ic.BaseSize.width() > 0) {
//        m_pageImages.append(ic.Image);
        QGraphicsPixmapItem* gpi = s->addPixmap(ic.Image);
        // if we show the image with resizing more smooth, must be called
        gpi->setTransformationMode(Qt::SmoothTransformation);
        gitem = gpi;
        size = ic.Image.size();
        if(ic.Info.ImageWidth > 0 && ic.Info.Orientation != 1) {
            switch(ic.Info.Orientation) {
            case 6: // left 90 digree turned
                gpi->setRotation(90);
                size = QSize(ic.Image.height(), ic.Image.width());
                offset = QPoint(size.width(), 0);
                break;
            case 8: // right 90 digree turned
                gpi->setRotation(270);
                size = QSize(ic.Image.height(), ic.Image.width());
                offset = QPoint(0, size.height());
                break;
            }
        }
    } else {
        QGraphicsTextItem* gtext = s->addText(tr("NOT IMAGE"));
        gtext->setDefaultTextColor(Qt::white);
        qDebug() << gtext;
        gitem = gtext;
        size = QSize(100, 100);
    }
    PageGraphicsItem pgi(ic.Image, gitem, size, offset);
    if(pageNext)
        m_pages.push_back(pgi);
    else
        m_pages.push_front(pgi);

    return size.width() > size.height();
}

void ImageView::clearImages()
{
    if(m_fileVolume == nullptr) return;
    QGraphicsScene *s = scene();
    for(int i = 0; i < m_pages.length(); i++) {
        s->removeItem(m_pages[i].GrItem);
        delete m_pages[i].GrItem;
    }

    m_pages.resize(0);
}

void ImageView::nextPage()
{
    qDebug() << "ImageView::nextPage()" << m_currentPage;
    if(m_fileVolume == nullptr) return;
    bool result = (m_fileVolume->pageCount() == m_fileVolume->size() -1) ||  m_fileVolume->nextPage();
    if(!result) return;

    int pageIncr = m_pages.size();
    m_currentPage += pageIncr;
    if(m_currentPage >= m_fileVolume->size() - pageIncr)
        m_currentPage = m_fileVolume->size() - pageIncr;

    reloadCurrentPage();
    emit pageChanged();
}

void ImageView::reloadCurrentPage(bool pageNext)
{
    qDebug() << "ImageView::reloadCurrentPage()";
    if(m_fileVolume == nullptr) return;
    clearImages();

    bool wide = addImage(m_fileVolume->currentImage(), true);
    m_wideImage = wide;
    if(!(m_currentPage==0 && qApp->FirstImageAsOnePageInDualView()) && canDualView()) {
        if(m_fileVolume->pageCount() < m_fileVolume->size()-1) {
            const ImageContent ic0 = m_fileVolume->getIndexedImageContent(m_currentPage);
            const ImageContent ic1 = m_fileVolume->getIndexedImageContent(m_currentPage+1);
            if(!qApp->WideImageAsOnePageInDualView() || (!ic0.wideImage() && !ic1.wideImage())) {
                    m_fileVolume->nextPage();
                    addImage(m_fileVolume->currentImage(), pageNext);
            }
        }
    }
    readyForPaint();
}


void ImageView::prevPage()
{
    if(m_fileVolume == nullptr) return;

    if(m_fileVolume->pageCount() < m_pages.size()) return;

    //QVApplication* app = qApp;
    m_currentPage--;
    if(qApp->DualView() && m_currentPage >= 1) {
        const ImageContent ic0 = m_fileVolume->getIndexedImageContent(m_currentPage);
        const ImageContent ic1 = m_fileVolume->getIndexedImageContent(m_currentPage-1);
        if(!qApp->WideImageAsOnePageInDualView() || (!ic0.wideImage() && !ic1.wideImage()))
            m_currentPage--;
    }
    if(m_currentPage < 0)
        m_currentPage = 0;
    setIndexedPage(m_currentPage);
}

void ImageView::setIndexedPage(int idx)
{
    qDebug() << "ImageView::setIndexedPage()" << idx;
    if(m_fileVolume == nullptr) return;
    bool result = m_fileVolume->findPageByIndex(idx);
    if(!result) return;
    m_currentPage = idx;

    reloadCurrentPage();
    emit pageChanged();
}

void ImageView::setRenderer(RendererType type)
{
    m_renderer = type;

    if (m_renderer == OpenGL) {
#ifndef QT_NO_OPENGL
        QGLWidget* w = new QGLWidget(QGLFormat(QGL::SampleBuffers));
        setViewport(w);
#endif
    } else {
        setViewport(new QWidget);
    }
}

QString ImageView::currentPageAsString() const
{
    if(m_pages.size() == 2) {
        return QString("%1-%2/%3").arg(m_currentPage+1).arg(m_currentPage+2).arg(m_fileVolume->size());
    } else {
        return QString("%1/%3").arg(m_currentPage+1).arg(m_fileVolume->size());
    }
}
void ImageView::readyForPaint() {
    qDebug() << "readyForPaint";
    if(!m_pages.empty()) {
        bool dualview = qApp->DualView() && canDualView();
        for(int i = 0; i < m_pages.size(); i++) {
            PageGraphicsItem::Fitting fitting = PageGraphicsItem::FitCenter;
            QRect pageRect = QRect(QPoint(), viewport()->size());
            if(dualview) {
                fitting = ((i==0 && !qApp->RightSideBook()) || (i==1 && qApp->RightSideBook()))
                            ? PageGraphicsItem::FitRight : PageGraphicsItem::FitLeft;
                pageRect = QRect(QPoint(fitting==PageGraphicsItem::FitRight ? 0 : pageRect.width()/2, 0), QSize(pageRect.width()/2,pageRect.height()));
            }
            if(qApp->Fitting()) {
                m_pages[i].setPageLayoutFitting(pageRect, fitting);
            } else {
                qreal scale = 1.0*currentViewSize()/100;
                m_pages[i].setPageLayoutManual(pageRect, fitting, scale);
            }
        }
    }
    repaint();
}

void ImageView::resizeEvent(QResizeEvent *event)
{
    if(scene()) {
        scene()->setSceneRect(QRect(QPoint(), event->size()));
    }
    QGraphicsView::resizeEvent(event);
    if(m_skipResizeEvent)
        return;
    readyForPaint();
}

void ImageView::on_nextPage_triggered()
{
    nextPage();
}

void ImageView::on_prevPage_triggered()
{
    prevPage();
}

void ImageView::on_firstPage_triggered()
{
    setIndexedPage(0);
}

void ImageView::on_lastPage_triggered()
{
    if(m_fileVolume && m_fileVolume->size() > 0)
        setIndexedPage(m_fileVolume->size()-1);

}

void ImageView::on_nextOnlyOnePage_triggered()
{
    if(m_fileVolume == nullptr || m_fileVolume->pageCount() == m_fileVolume->size() -1) return;
    if(m_pages.size() == 1) {
        m_fileVolume->nextPage();
    }
    m_currentPage++;
    if(m_currentPage >= m_fileVolume->size() - 1)
        m_currentPage = m_fileVolume->size() - 1;
    reloadCurrentPage();
    emit pageChanged();
}

void ImageView::on_prevOnlyOnePage_triggered()
{
    if(m_fileVolume == nullptr) return;

    if(m_fileVolume->pageCount() < m_pages.size()) return;

    //QVApplication* app = qApp;
    m_currentPage--;
    if(m_currentPage < 0)
        m_currentPage = 0;
    setIndexedPage(m_currentPage);
}

#define HOVER_BORDER 20
//#define NOT_HOVER_AREA 100

void ImageView::mouseMoveEvent(QMouseEvent *e)
{
//    qDebug() << e;
    int NOT_HOVER_AREA = width() / 3;
    if(e->pos().x() < HOVER_BORDER && e->pos().y() < height()-HOVER_BORDER) {
        if(m_hoverState != Qt::AnchorLeft)
            emit anchorHovered(Qt::AnchorLeft);
        m_hoverState = Qt::AnchorLeft;
        QApplication::setOverrideCursor(Qt::PointingHandCursor);
        return;
    }
    if(e->pos().x() > width()-HOVER_BORDER) {
        if(m_hoverState != Qt::AnchorRight)
            emit anchorHovered(Qt::AnchorRight);
        m_hoverState = Qt::AnchorRight;
        QApplication::setOverrideCursor(Qt::PointingHandCursor);
        return;
    }
    QApplication::setOverrideCursor(Qt::ArrowCursor);
    if(e->pos().y() < HOVER_BORDER) {
        if(m_hoverState != Qt::AnchorTop)
           emit anchorHovered(Qt::AnchorTop);
        m_hoverState = Qt::AnchorTop;
        return;
    }
    if(e->pos().y() > height()-HOVER_BORDER && e->pos().x() > NOT_HOVER_AREA) {
        if(m_hoverState != Qt::AnchorBottom)
           emit anchorHovered(Qt::AnchorBottom);
        m_hoverState = Qt::AnchorBottom;
        return;
    }
    if(m_hoverState != Qt::AnchorHorizontalCenter)
       emit anchorHovered(Qt::AnchorHorizontalCenter);
    m_hoverState = Qt::AnchorHorizontalCenter;
}

void ImageView::on_fitting_triggered(bool maximized)
{
    qApp->setFitting(maximized);
    readyForPaint();
}

void ImageView::on_dualView_triggered(bool viewdual)
{
    qApp->setDualView(viewdual);

    if(!viewdual && m_fileVolume)
        m_fileVolume->prevPage();
    reloadCurrentPage();
    readyForPaint();
}

void ImageView::on_rightSideBook_triggered(bool rightSideBook)
{
    qApp->setRightSideBook(rightSideBook);
    readyForPaint();
}

void ImageView::on_scaleUp_triggered()
{
    if(viewSizeIdx < viewSizeList.size() -1)
        viewSizeIdx++;
    readyForPaint();
}

void ImageView::on_scaleDown_triggered()
{
    if(viewSizeIdx > 0)
        viewSizeIdx--;
    readyForPaint();
}

void ImageView::on_wideImageAsOneView_triggered(bool wideImage)
{
    qApp->setWideImageAsOnePageInDualView(wideImage);
    reloadCurrentPage();
    readyForPaint();
}

void ImageView::on_firstImageAsOneView_triggered(bool firstImage)
{
    qApp->setFirstImageAsOnePageInDualView(firstImage);
    reloadCurrentPage();
    readyForPaint();
}

void ImageView::on_openFiler_triggered()
{
    if(!m_fileVolume)
        return;
    QString path = m_fileVolume->volumePath();
    if(!m_fileVolume->isArchive()) {
        path = m_fileVolume->currentPath();
    }
#if defined(Q_OS_WIN)
    const QString explorer = QLatin1String("explorer.exe ");
    QFileInfo fi(path);

    // canonicalFilePath returns empty if the file does not exist
    if( !fi.canonicalFilePath().isEmpty() ) {
        QString nativeArgs;
        if (!fi.isDir()) {
            nativeArgs += QLatin1String("/select,");
        }
        nativeArgs += QLatin1Char('"');
        nativeArgs += QDir::toNativeSeparators(fi.canonicalFilePath());
        nativeArgs += QLatin1Char('"');

        qDebug() << "OO Open explorer commandline:" << explorer << nativeArgs;
        QProcess p;
        // QProcess on Windows tries to wrap the whole argument/program string
        // with quotes if it detects a space in it, but explorer wants the quotes
        // only around the path. Use setNativeArguments to bypass this logic.
        p.setNativeArguments(nativeArgs);
        p.start(explorer);
        p.waitForFinished(5000);
    }
#else
    if(!QFileInfo(path).isDir()) {
        QDir dir(path);
        dir.cdUp();
        path = dir.path();
    }
    QUrl url = QString("file:///%1").arg(path);
    QDesktopServices::openUrl(url);
#endif
}

void ImageView::on_openExifDialog_triggered()
{
    if(!m_fileVolume)
        return;
    const easyexif::EXIFInfo& info = m_fileVolume->currentImage().Info;
    if(info.ImageWidth == 0)
        return;
    exifDialog.setExif(info);
    exifDialog.open();
}

void ImageView::on_copyPage_triggered()
{
    if(m_pages.empty())
        return;
    QClipboard* clip = qApp->clipboard();
    clip->setImage(m_pages[0].Image.toImage());
}


bool ImageView::canDualView() const
{
    QVApplication* myapp = qApp;
    return qApp->DualView() && !(m_wideImage && myapp->WideImageAsOnePageInDualView());
}

