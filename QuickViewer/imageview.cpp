#include "imageview.h"
#include "qvapplication.h"

#include <QMouseEvent>
#include <QtDebug>
#include <QPainter>
#include <QGLWidget>
#include <QGraphicsPixmapItem>

ImageView::ImageView(QWidget *parent)
    : QGraphicsView(parent)
    , m_renderer(Native)
    , m_fileVolume(nullptr)
    , m_hoverState(Qt::AnchorHorizontalCenter)
    , m_currentPage(0)
    , m_wideImage(false)
{
    viewSizeList << 25 << 33 << 50 << 75 << 100 << 150 << 200 << 300 << 400 << 800;
    viewSizeIdx = 4; // 100

    QGraphicsScene* scene = new QGraphicsScene(this);
//    scene->setForegroundBrush(QBrush(QColor("white")));
//    scene->setBackgroundBrush(QBrush(QColor("black")));
//    scene->setPalette(QPalette(Qt::white));
    setScene(scene);
//    setTransformationAnchor(AnchorUnderMouse);
//    setDragMode(ScrollHandDrag);
//    setViewportUpdateMode(FullViewportUpdate);
    setAcceptDrops(false);
//    setDragMode(DragDropMode::InternalMove);
//    setBackgroundBrush(QBrush(Qt::gray));
    setRenderer(OpenGL);

    setMouseTracking(true);


}


void ImageView::setImage(QPixmap pixmap)
{
    if(m_fileVolume == nullptr) return;
    clearImages();
    addImage(pixmap, true);
}

bool ImageView::addImage(QPixmap pixmap, bool pageNext)
{
    if(m_fileVolume == nullptr) return false;
    m_ptLeftTop.reset();
    QGraphicsScene *s = scene();


    QGraphicsItem* gitem;
    QSize size;
    if(pixmap.width() > 0) {
        QGraphicsPixmapItem* gpi = s->addPixmap(pixmap);
        // if we show the image with resizing more smooth, must be called
        gpi->setTransformationMode(Qt::SmoothTransformation);
        gitem = gpi;
        size = pixmap.size();
    } else {
        QGraphicsTextItem* gtext = s->addText(tr("NOT IMAGE"));
        gtext->setDefaultTextColor(Qt::white);
        qDebug() << gtext;
        gitem = gtext;
        size = QSize(100, 100);
    }
    if(pageNext)
        m_gpiImages.push_back(gitem);
    else
        m_gpiImages.push_front(gitem);
    if(pageNext)
        m_pagesizes.push_back(size);
    else
        m_pagesizes.push_front(size);
    if(pageNext)
        m_pageFilenames.push_back(m_fileVolume->currentImageName());
    else
        m_pageFilenames.push_front(m_fileVolume->currentImageName());

    return size.width() > size.height();
}

void ImageView::clearImages()
{
    if(m_fileVolume == nullptr) return;
    QGraphicsScene *s = scene();
    for(int i = 0; i < m_gpiImages.length(); i++) {
        s->removeItem((QGraphicsItem*)m_gpiImages[i]);
        delete m_gpiImages[i];
    }
    m_gpiImages.resize(0);
    m_pagesizes.resize(0);
    m_pageFilenames.resize(0);
}

void ImageView::nextPage()
{
    qDebug() << "ImageView::nextPage()";
    if(m_fileVolume == nullptr) return;
    bool result = (qApp->DualView() && m_fileVolume->pageCount() == m_fileVolume->size() - 2) ||  m_fileVolume->nextPage();
    if(!result) return;

    int pageIncr = qApp->DualView() ? 2 : 1;
    m_currentPage += pageIncr;
    if(m_currentPage >= m_fileVolume->size() - pageIncr)
        m_currentPage = m_fileVolume->size() - pageIncr;

    reloadCurrentPage();
    emit pageChanged();
}

void ImageView::reloadCurrentPage()
{
    qDebug() << "ImageView::reloadCurrentPage()";
    if(m_fileVolume == nullptr) return;
    clearImages();

    bool wide = addImage(m_fileVolume->currentImage(), true);
    m_wideImage = wide;
    if(qApp->DualView() && wideImageAsDualView()) {
        if(m_fileVolume->nextPage()) {
            if(addImage(m_fileVolume->currentImage(), true) && qApp->WideImageAsOnePageInDualView()) {
                // if 2nd page is wide, will be canceled
                m_fileVolume->prevPage();
                scene()->removeItem(m_gpiImages[1]);
                delete m_gpiImages[1];
                m_gpiImages.remove(1);
                m_pagesizes.remove(1);
                m_currentPage--;
            }
        }
    }
    readyForPaint();
}


void ImageView::prevPage()
{
    if(m_fileVolume == nullptr) return;
//    bool result = (qApp->DualView() && m_fileVolume->pageCount() == 1) || m_fileVolume->prevFile();
//    if(!result) return;
//    clearImages();
//    m_currentPage -= qApp->DualView() ? 2 : 1;
//    if(m_currentPage < 0)
//        m_currentPage = 0;


//    addImage(m_fileVolume->currentImage(), false);
//    if(qApp->DualView()) {
//        if(m_fileVolume->prevFile())
//            addImage(m_fileVolume->currentImage(), false);
//    }
//    emit pageChanged();
    if(m_fileVolume->pageCount() == (qApp->DualView() ? 1 : 0)) return;
    m_currentPage -= qApp->DualView() ? 2 : 1;
    if(m_currentPage < 0)
        m_currentPage = 0;
    setIndexedPage(m_currentPage);
}

void ImageView::setIndexedPage(int idx)
{
    qDebug() << "ImageView::setIndexedPage()" << idx;
    if(m_fileVolume == nullptr) return;
//    clearImages();
    bool result = m_fileVolume->findPageByIndex(idx);
    if(!result) return;
    m_currentPage = idx;

//    bool wide = addImage(m_fileVolume->currentImage(), true);
//    m_wideImage = wide;
//    if(qApp->DualView() && !m_wideImage) {
//        if(m_fileVolume->nextPage())
//            addImage(m_fileVolume->currentImage(), true);
//    }
//    emit pageChanged();
//    readyForPaint();
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
    if(qApp->DualView()) {
        return QString("%1-%2/%3").arg(m_currentPage+1).arg(m_currentPage+2).arg(m_fileVolume->size());
    } else {
        return QString("%1/%3").arg(m_currentPage+1).arg(m_fileVolume->size());
    }
}
void ImageView::readyForPaint() {
    qDebug() << "readyForPaint";
    if(!m_gpiImages.empty()) {
        bool dualview = qApp->DualView() && wideImageAsDualView();
        if(qApp->Fitting()) {
            for(int i = 0; i < m_gpiImages.size(); i++) {
                QSize size = viewport()->size();
                QSize imgsize = m_pagesizes[i];
                QSize sizeofview = dualview ? QSize(size.width()/2,size.height()) : size;

                QSize newsize = imgsize.scaled(sizeofview, Qt::KeepAspectRatio);
                m_gpiImages[i]->setScale(1.0*newsize.width()/imgsize.width());

                int offset = qApp->RightSideBook() ? -i : i-1;
                if(newsize.height() == size.height()) { // 上下に内接
                    m_gpiImages[i]->setPos(dualview ? sizeofview.width()+offset*newsize.width() : (size.width()-newsize.width())/2, 0);
                } else { // 左右に内接
                    m_gpiImages[i]->setPos(dualview ? sizeofview.width()+offset*newsize.width() : 0, (size.height()-newsize.height())/2);
                }
            }
        } else {
            for(int i = 0; i < m_gpiImages.size(); i++) {
                qreal scale = 1.0*currentViewSize()/100;
                m_gpiImages[i]->setScale(scale);
                QSize size = viewport()->size();
                QSize imgsize = m_pagesizes[i];
                imgsize *= scale;
                if(dualview)
                    m_gpiImages[i]->setPos(size.width()/2-i*imgsize.width(), 0);
                else
                    m_gpiImages[i]->setPos(size.width()/2-imgsize.width()/2, 0);
            }
        }
    }
    repaint();
}

//void ImageView::paintEvent( QPaintEvent *event )
//{
//    qDebug() << event;
//    QGraphicsView::paintEvent(event);
//}

void ImageView::resizeEvent(QResizeEvent *event)
{
    if(scene()) {
        scene()->setSceneRect(QRect(QPoint(), event->size()));
    }
    QGraphicsView::resizeEvent(event);
    readyForPaint();
}

#define HOVER_BORDER 20

void ImageView::mouseMoveEvent(QMouseEvent *e)
{
//    qDebug() << e;
    if(e->pos().x() < HOVER_BORDER) {
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
    if(e->pos().y() > height()-HOVER_BORDER) {
        if(m_hoverState != Qt::AnchorBottom)
           emit anchorHovered(Qt::AnchorBottom);
        m_hoverState = Qt::AnchorBottom;
        return;
    }
    if(m_hoverState != Qt::AnchorHorizontalCenter)
       emit anchorHovered(Qt::AnchorHorizontalCenter);
    m_hoverState = Qt::AnchorHorizontalCenter;
}

//void ImageView::mousePressEvent(QMouseEvent *e)
//{
//    if(e->button() && Qt::LeftButton) {
//        m_isMouseDown = true;
//        m_ptLeftTop.start(e->pos());
////        qDebug("mousePressEvent x:%d y:%d button:%x\n", e->x(), e->y(), e->button());
//    }
//}

//void ImageView::mouseReleaseEvent(QMouseEvent *)
//{
//    if(m_isMouseDown) {
//        m_isMouseDown = false;
////        qDebug("mouseReleaseEvent x:%d y:%d\n", e->x(), e->y());
//    }
//}

void ImageView::on_image_changing(QPixmap image)
{
    setImage(image);
    readyForPaint();
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

bool ImageView::wideImageAsDualView() const
{
    QVApplication* myapp = qApp;
    return !(m_wideImage && myapp->WideImageAsOnePageInDualView());
}

