#include "imageview.h"
#include "qvapplication.h"
#include "exifdialog.h"

#include <QMouseEvent>
#include <QtDebug>
#include <QPainter>
#include <QGLWidget>
#include <QGraphicsPixmapItem>
#include <QDesktopServices>
#include <QProcessEnvironment>
#include <QMessageBox>

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


void ImageView::setImage(ImageContent pixmap)
{
    if(m_fileVolume == nullptr) return;
    clearImages();
    addImage(pixmap, true);
}

bool ImageView::addImage(ImageContent ic, bool pageNext)
{
    if(m_fileVolume == nullptr) return false;
    m_ptLeftTop.reset();
    QGraphicsScene *s = scene();


    QGraphicsItem* gitem;
    QSize size;
    QPoint offset;
    if(ic.BaseSize.width() > 0) {
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
    if(pageNext)
        m_gpiImages.push_back(gitem);
    else
        m_gpiImages.push_front(gitem);
    if(pageNext)
        m_pagesizes.push_back(size);
    else
        m_pagesizes.push_front(size);
    if(pageNext)
        m_gpiOffsets.push_back(offset);
    else
        m_gpiOffsets.push_front(offset);

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
    m_gpiOffsets.resize(0);
//    m_pageFilenames.resize(0);
}

void ImageView::nextPage()
{
    qDebug() << "ImageView::nextPage()" << m_currentPage;
    if(m_fileVolume == nullptr) return;
    bool result = (m_fileVolume->pageCount() == m_fileVolume->size() -1) ||  m_fileVolume->nextPage();
    if(!result) return;

    int pageIncr = m_gpiImages.size();
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
    if(canDualView()) {
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

    if(m_fileVolume->pageCount() < m_gpiImages.size()) return;

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
    if(m_gpiImages.size() == 2) {
        return QString("%1-%2/%3").arg(m_currentPage+1).arg(m_currentPage+2).arg(m_fileVolume->size());
    } else {
        return QString("%1/%3").arg(m_currentPage+1).arg(m_fileVolume->size());
    }
}
void ImageView::readyForPaint() {
    qDebug() << "readyForPaint";
    if(!m_gpiImages.empty()) {
        bool dualview = qApp->DualView() && canDualView();
        if(qApp->Fitting()) {
            for(int i = 0; i < m_gpiImages.size(); i++) {
                QSize size = viewport()->size();
                QSize imgsize = m_pagesizes[i];
                QSize sizeofview = dualview ? QSize(size.width()/2,size.height()) : size;

                QSize newsize = imgsize.scaled(sizeofview, Qt::KeepAspectRatio);
                qreal scale = 1.0*newsize.width()/imgsize.width();
                QPoint of = QPoint(scale*m_gpiOffsets[i].x(), scale*m_gpiOffsets[i].y());
                m_gpiImages[i]->setScale(scale);

                int offset = qApp->RightSideBook() ? -i : i-1;
                if(newsize.height() == size.height()) { // 上下に内接
                    m_gpiImages[i]->setPos(of.x() + (dualview ? sizeofview.width()+offset*newsize.width() : (size.width()-newsize.width())/2), of.y());
                } else { // 左右に内接
                    m_gpiImages[i]->setPos(of.x() + (dualview ? sizeofview.width()+offset*newsize.width() : 0), of.y() + (size.height()-newsize.height())/2);
                }
            }
        } else {
            for(int i = 0; i < m_gpiImages.size(); i++) {
                qreal scale = 1.0*currentViewSize()/100;
                m_gpiImages[i]->setScale(scale);
                QSize size = viewport()->size();
                QSize imgsize = m_pagesizes[i];
                imgsize *= scale;
                QPoint of = QPoint(scale*m_gpiOffsets[i].x(), scale*m_gpiOffsets[i].y());
                if(dualview)
                    m_gpiImages[i]->setPos(of.x() + size.width()/2-i*imgsize.width(), of.y());
                else
                    m_gpiImages[i]->setPos(of.x() + size.width()/2-imgsize.width()/2, of.y());
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

#define HOVER_BORDER 20
#define NOT_HOVER_AREA 100

void ImageView::mouseMoveEvent(QMouseEvent *e)
{
//    qDebug() << e;
    if(e->pos().x() < HOVER_BORDER && e->pos().y() < height()-NOT_HOVER_AREA) {
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

void ImageView::on_openFiler_triggered()
{
    if(!m_fileVolume)
        return;
    QString path = m_fileVolume->volumePath();
    if(!m_fileVolume->isArchive()) {
        path = m_fileVolume->currentPath();
    }
#if defined(Q_OS_WIN)
    //const QString explorer = QProcessEnvironment::systemEnvironment().searchInPath(QLatin1String("explorer.exe"));
    const QString explorer = QLatin1String("explorer.exe");
    if (explorer.isEmpty()) {
        QMessageBox::warning(this,
                             tr("Launching Windows Explorer failed"),
                             tr("Could not find explorer.exe in path to launch Windows Explorer."));
        return;
    }
    QString param;
    if (!QFileInfo(path).isDir())
        param = QLatin1String("/select,");
    param += QDir::toNativeSeparators(path);
    QString command = explorer + " " + param;
    QProcess::startDetached(command);
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

bool ImageView::canDualView() const
{
    QVApplication* myapp = qApp;
    return qApp->DualView() && !(m_wideImage && myapp->WideImageAsOnePageInDualView());
}

