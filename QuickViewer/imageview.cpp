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
    , m_pageManager(nullptr)
    , m_hoverState(Qt::AnchorHorizontalCenter)
//    , m_currentPage(0)
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

bool ImageView::addImage(ImageContent ic, bool pageNext)
{
    if(m_pageManager == nullptr) return false;
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
        //qDebug() << gtext;
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
    if(m_pageManager == nullptr) return;
    QGraphicsScene *s = scene();
    for(int i = 0; i < m_pages.length(); i++) {
        s->removeItem(m_pages[i].GrItem);
        delete m_pages[i].GrItem;
    }

    m_pages.resize(0);
}

void ImageView::setPageManager(PageManager *manager)
{
    m_pageManager = manager;
    connect(manager, SIGNAL(pagesNolongerNeeded()), this, SLOT(clearImages()));
    connect(manager, SIGNAL(readyForPaint()), this, SLOT(readyForPaint()));
    connect(manager, SIGNAL(pageAdded(ImageContent, bool)), this, SLOT(addImage(ImageContent, bool)));
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

void ImageView::readyForPaint() {
    //qDebug() << "readyForPaint";
    if(!m_pages.empty()) {
        bool dualview = qApp->DualView() && m_pageManager->canDualView();
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
    if(m_pageManager)
        m_pageManager->nextPage();
}

void ImageView::on_prevPage_triggered()
{
    if(m_pageManager)
        m_pageManager->prevPage();
}

void ImageView::on_firstPage_triggered()
{
    if(m_pageManager)
        m_pageManager->firstPage();
}

void ImageView::on_lastPage_triggered()
{
    if(m_pageManager)
        m_pageManager->lastPage();
}

void ImageView::on_nextOnlyOnePage_triggered()
{
    if(m_pageManager)
        m_pageManager->nextOnlyOnePage();
}

void ImageView::on_prevOnlyOnePage_triggered()
{
    if(m_pageManager)
        m_pageManager->prevOnlyOnePage();
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

    if(!viewdual && m_pageManager)
        m_pageManager->prevPage();
    m_pageManager->reloadCurrentPage();
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
    m_pageManager->reloadCurrentPage();
    readyForPaint();
}

void ImageView::on_firstImageAsOneView_triggered(bool firstImage)
{
    qApp->setFirstImageAsOnePageInDualView(firstImage);
    m_pageManager->reloadCurrentPage();
    readyForPaint();
}

void ImageView::on_openFiler_triggered()
{
    if(!m_pageManager)
        return;
    QString path = m_pageManager->volumePath();
    if(!m_pageManager->isArchive()) {
        path = m_pageManager->currentPagePath();
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
    if(!m_pageManager || m_pages.size()==0)
        return;
    const easyexif::EXIFInfo& info = m_pageManager->currentPageContent()[0].Info;
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

