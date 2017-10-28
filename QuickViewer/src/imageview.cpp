#include <QtWidgets>

#include "imageview.h"
#include "qvapplication.h"

ImageView::ImageView(QWidget *parent)
    : QGraphicsView(parent)
    , m_renderer(Native)
    , m_hoverState(Qt::AnchorHorizontalCenter)
    , m_loupeCursor(QCursor(QPixmap(":/icons/loupe_cursor"), 20, 23))
    , m_pageManager(nullptr)
    , m_effectManager(this)
    , m_slideshowTimer(nullptr)
    , m_beginScaleFactor(1.0)
    , m_beginRotateFactor(0.0)
    , m_loupeFactor(3.0)
    , m_isMouseDown(false)
    , m_wideImage(false)
    , m_skipResizeEvent(false)
    , m_isFullScreen(false)
    , m_scrollMode(false)
    , m_pageBacking(false)
    , m_loupeEnable(false)
{
    viewSizeList << 16 << 20 << 25 << 33 << 50 << 75 << 100 << 150 << 200 << 300 << 400 << 800;
    viewSizeIdx = 6; // 100

    QGraphicsScene* scene = new QGraphicsScene(this);
    setScene(scene);
//    setTransformationAnchor(AnchorUnderMouse);
//    setDragMode(ScrollHandDrag);
//    setViewportUpdateMode(FullViewportUpdate);
    setAcceptDrops(false);
//    setDragMode(DragDropMode::InternalMove);
#ifdef QV_WITHOUT_OPENGL
    setRenderer(Native);
#else
    if(qApp->Effect() > qvEnums::UsingFixedShader)
        setRenderer(OpenGL);
#endif

    setMouseTracking(true);
    resetBackgroundColor();
	setAttribute(Qt::WA_AcceptTouchEvents);

}

#ifdef QV_WITHOUT_OPENGL
QWidget* widgetEngine = nullptr;
#else
QGLWidget* widgetEngine = nullptr;
#endif

void ImageView::setRenderer(RendererType type)
{
    m_renderer = type;
    if(widgetEngine)
        return;
#ifdef QV_WITHOUT_OPENGL
    type = RendererType::Native;
    QWidget* w = new QWidget;
    widgetEngine = w;
    setViewport(w);
#else
    if (m_renderer == OpenGL) {
        QGLWidget* w = new QGLWidget(QGLFormat(QGL::SampleBuffers));
        widgetEngine = w;
        setViewport(w);
    } else {
        setViewport(new QWidget);
    }
#endif
}


void ImageView::setPageManager(PageManager *manager)
{
    m_pageManager = manager;
    m_pageManager->setImageView(this);
    connect(manager, SIGNAL(pagesNolongerNeeded()), this, SLOT(on_clearImages_triggered()));
    connect(manager, SIGNAL(readyForPaint()), this, SLOT(readyForPaint()));
    connect(manager, SIGNAL(volumeChanged(QString)), this, SLOT(on_volumeChanged_triggered(QString)));
    connect(manager, SIGNAL(pageAdded(ImageContent, bool)), this, SLOT(on_addImage_triggered(ImageContent, bool)));
}

void ImageView::toggleSlideShow()
{
    if(!m_pageManager)
        return;
    if(m_slideshowTimer) {
        delete m_slideshowTimer;
        m_slideshowTimer = nullptr;
        return;
    }
    m_slideshowTimer = new QTimer();
    connect(m_slideshowTimer, SIGNAL(timeout()), this, SLOT(on_slideShowChanging_triggered()));
    m_slideshowTimer->start(qApp->SlideShowWait());
}

void ImageView::resetBackgroundColor()
{
//    QColor bg = qApp->BackgroundColor();
//    setStyleSheet(QString("background-color:") + bg.name(QColor::HexArgb));
    if(!qApp->UseCheckeredPattern()) {
        setBackgroundBrush(QBrush(qApp->BackgroundColor(), Qt::SolidPattern));
        return;
    }
    QPixmap pix(16, 16);
    pix.fill(qApp->BackgroundColor());
    QPainter paint(&pix);
    QBrush brush2(qApp->BackgroundColor2(), Qt::SolidPattern);
    paint.fillRect(QRect(0, 0, 8, 8), brush2);
    paint.fillRect(QRect(8, 8, 8, 8), brush2);
    QBrush brush(pix);
    setBackgroundBrush(brush);
}


void ImageView::on_volumeChanged_triggered(QString )
{
    m_pageRotations = QVector<int>(m_pageManager->size());
}

bool ImageView::on_addImage_triggered(ImageContent ic, bool pageNext)
{
    if(m_pageManager == nullptr) return false;
    m_ptLeftTop.reset();
    QGraphicsScene *s = scene();
    QSize size = ic.Image.size();
    PageContent pgi(this, s, ic);
    if(m_pageBacking && pgi.Separation == PageContent::FirstSeparated)
        pgi.Separation = PageContent::SecondSeparated;

    if(pageNext) {
        m_pages.push_back(pgi);
        connect(&(m_pages.last()), SIGNAL(resizeFinished()), this, SLOT(readyForPaint()));
    } else {
        m_pages.push_front(pgi);
        connect(&(m_pages.first()), SIGNAL(resizeFinished()), this, SLOT(readyForPaint()));
    }

    m_effectManager.prepareInitialize();

    return size.width() > size.height();
}

void ImageView::on_clearImages_triggered()
{
    if(m_pageManager == nullptr) return;
//    QGraphicsScene *s = scene();
    for(int i = 0; i < m_pages.length(); i++) {
        m_pages[i].dispose();
    }

    m_pages.resize(0);
    horizontalScrollBar()->setValue(0);
    verticalScrollBar()->setValue(0);
}
//static int paintCnt=0;
void ImageView::readyForPaint() {
//    qDebug() << "readyForPaint " << paintCnt++;
    if(qApp->Effect() > qvEnums::UsingFixedShader)
        setRenderer(OpenGL);
    if(!m_pages.empty()) {
        int pageCount = m_pageManager->currentPage();
        QRect sceneRect;
        for(int i = 0; i < m_pages.size(); i++) {
            if(qApp->SeparatePagesWhenWideImage() && m_pages[i].Ic.wideImage()) {
                if(m_pages[i].Separation == PageContent::NoSeparated && viewport()->width() < viewport()->height())
                    m_pages[i].Separation = PageContent::FirstSeparated;
                if(m_pages[i].Separation != PageContent::NoSeparated && viewport()->width() > viewport()->height())
                    m_pages[i].Separation = PageContent::NoSeparated;
            }
            PageContent::Fitting fitting = PageContent::FitCenter;
            QRect pageRect = QRect(QPoint(), viewport()->size());
            if(m_pages.size() == 2) {
                fitting = ((i==0 && !qApp->RightSideBook()) || (i==1 && qApp->RightSideBook()))
                            ? PageContent::FitLeft : PageContent::FitRight;
                pageRect = QRect(QPoint(fitting==PageContent::FitRight ? pageRect.width()/2 : 0 , 0), QSize(pageRect.width()/2,pageRect.height()));
            }
            QRect drawRect;
            qreal scalefactor = m_loupeEnable ? m_loupeFactor : 1.0;
            if(qApp->Fitting()) {
                qreal scale = m_loupeEnable ? m_loupeFactor : 1.0;
                drawRect = m_pages[i].setPageLayoutFitting(pageRect, fitting, scalefactor, m_pageRotations.isEmpty() ? 0 : m_pageRotations[pageCount+i]);
            } else {
                qreal scale = 1.0*currentViewSize()/100 * scalefactor;
                drawRect = m_pages[i].setPageLayoutManual(pageRect, fitting, scale, m_pageRotations.isEmpty() ? 0 : m_pageRotations[pageCount+i]);
            }
            m_pages[i].Text = qApp->ShowFullscreenSignage() && m_isFullScreen ? m_pageManager->pageSignage(i) : "";
            m_pages[i].resetSignage(QRect(QPoint(), viewport()->size()), fitting);
            m_effectManager.prepare(dynamic_cast<QGraphicsPixmapItem*>(m_pages[i].GrItem), m_pages[i].Ic, drawRect.size());
            sceneRect = sceneRect.united(drawRect);
        }
        // if Size of Image overs Size of View, use Image's size
//        setSceneRectMode(!qApp->Fitting() && !m_isFullScreen, sceneRect);
        setSceneRectMode(!qApp->Fitting() || m_loupeEnable, sceneRect);
    }
    m_effectManager.prepareFinished();
}

static bool s_lastLoupeMode;

void ImageView::setSceneRectMode(bool scrolled, const QRect &sceneRect)
{
    if(!m_loupeEnable) {
        m_sceneRect = sceneRect;
    }
    if(m_loupeEnable && !s_lastLoupeMode) {
        m_scrollBaseValues = QPoint(horizontalScrollBar()->value(), verticalScrollBar()->value());
    }
    s_lastLoupeMode = m_loupeEnable;
    // if Size of Image overs Size of View, use Image's size
    bool newMode = scrolled && (size().width() < sceneRect.width() || size().height() < sceneRect.height());
    if(newMode) {
        scene()->setSceneRect(QRect(QPoint(qMin(0, sceneRect.left()), 0), QSize(qMax(size().width(), sceneRect.width()), qMax(size().height(), sceneRect.height()))));
        if(m_loupeEnable) {
            m_loupeBasePos = mapFromGlobal(QCursor::pos());
            setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            setDragMode(QGraphicsView::NoDrag);
            scrollOnLoupeMode();
        } else if(qApp->ScrollWithCursorWhenZooming()) {
            setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            setDragMode(QGraphicsView::NoDrag);
            scrollOnZoomMode();
        } else {
            // Since Qt :: ScrollBarAsNeeded does not work correctly, judge the display state on its own and switch.
            bool willBeHide = m_isFullScreen && qApp->HideScrollBarInFullscreen();
            setHorizontalScrollBarPolicy(!willBeHide && size().width() < sceneRect.width()+verticalScrollBar()->width() ? Qt::ScrollBarAsNeeded : Qt::ScrollBarAlwaysOff );
            setVerticalScrollBarPolicy(!willBeHide && size().height() < sceneRect.height()+horizontalScrollBar()->height() ? Qt::ScrollBarAsNeeded : Qt::ScrollBarAlwaysOff );
            setDragMode(QGraphicsView::ScrollHandDrag);
        }
    } else {
        scene()->setSceneRect(QRect(QPoint(), size()));
        setDragMode(QGraphicsView::NoDrag);
    }
    if(m_scrollMode != newMode)
        emit scrollModeChanged(m_scrollMode = newMode);
}

void ImageView::scrollOnLoupeMode()
{
    QPoint cursorPos = QCursor::pos();
//    QPoint cursorPos0 = QCursor::pos();
    cursorPos = mapFromGlobal(cursorPos);
    const QRectF sceneRect = scene()->sceneRect();

    // The scrolling of the enlarged image is completed by moving the cursor
    // at a distance of half the distance from the first clicked coordinate to the edge of the window
    QRectF L = sceneRect;
    QRect  K = m_sceneRect;
    QPoint V = m_scrollBaseValues;
    K.moveTo(K.left()-V.x(), K.top()-V.y());
    QPoint S = m_loupeBasePos;
    QPoint R((S.x()-K.left())*L.width()/K.width()+L.left(),
             (S.y()-K.top())*L.height()/K.height()+L.top());
    QPoint Q = R-S;

    horizontalScrollBar()->setValue(cursorPos.x() < S.x()
        ? L.left() + (Q.x() - L.left()) * (2*cursorPos.x() - S.x()) / S.x()
        : L.right() - (L.right() - Q.x()) * (S.x() + width() - 2*cursorPos.x()) / (width() - S.x())
    );
    verticalScrollBar()->setValue(cursorPos.y() < S.y()
        ? L.top() + (Q.y() - L.top()) * (2*cursorPos.y() - S.y()) / S.y()
        : L.bottom() - (L.bottom() - Q.y()) * (S.y() + height() - 2*cursorPos.y()) / (height() - S.y())
    );
//    qDebug() << "S" << S << "K" << K << "L" << L << "R" << R << "scroolBase" << m_scrollBaseValues;
}

void ImageView::scrollOnZoomMode()
{
    QPoint cursorPos = QCursor::pos();
//    QPoint cursorPos0 = QCursor::pos();
    cursorPos = mapFromGlobal(cursorPos);
    cursorPos = QPoint(cursorPos.x() < width()/4 ? 0 : (cursorPos.x()- width()/4)*4/2,
                       cursorPos.y() < height()/4 ? 0 : (cursorPos.y()- height()/4)*4/2);
    const QRectF sceneRect = scene()->sceneRect();
//    qDebug() << cursorPos0 << cursorPos << QPoint(cursorPos.x()*horizontalScrollBar()->maximum()/width(), cursorPos.y()*verticalScrollBar()->maximum()/height());
//    qDebug() << horizontalScrollBar()->maximum() << verticalScrollBar()->maximum();
    horizontalScrollBar()->setValue(horizontalScrollBar()->minimum()+cursorPos.x()*(horizontalScrollBar()->maximum()-horizontalScrollBar()->minimum())/width());
    verticalScrollBar()->setValue(horizontalScrollBar()->minimum()+cursorPos.y()*(verticalScrollBar()->maximum()-horizontalScrollBar()->minimum())/height());
}

void ImageView::updateViewportOffset(QPointF moved)
{
    setTransform(
        QTransform()
                .scale(m_beginScaleFactor,m_beginScaleFactor)
                .rotate(m_beginRotateFactor)
                .translate(moved.x(), moved.y())
    );
}
static qreal s_lastScale;
static qreal s_lastRotate;

void ImageView::updateViewportFactors(qreal currentScale, qreal currentRotate)
{
    s_lastScale = currentScale;
    s_lastRotate = currentRotate;
    setTransform(
        QTransform()
           .scale(m_beginScaleFactor*currentScale,m_beginScaleFactor*currentScale)
           .rotate(m_beginRotateFactor+currentRotate)
    );
}

void ImageView::commitViewportFactors()
{
    m_beginScaleFactor *= s_lastScale;
    m_beginRotateFactor += s_lastRotate;
}

void ImageView::resetViewportFactors()
{
    m_beginScaleFactor = 1.0;
    m_beginRotateFactor = 0.0;
    setTransform(QTransform());
}

//void ImageView::paintEvent(QPaintEvent *event)
//{
////    readyForPaint();
//    QGraphicsView::paintEvent(event);
//}

void ImageView::resizeEvent(QResizeEvent *event)
{
    if(scene() && !m_isFullScreen) {
        scene()->setSceneRect(QRect(QPoint(), event->size()));
    }
    QGraphicsView::resizeEvent(event);
    if(m_skipResizeEvent)
        return;
    readyForPaint();
}

void ImageView::on_nextPage_triggered()
{
    if(qApp->SeparatePagesWhenWideImage() && m_pages[0].Separation == PageContent::FirstSeparated) {
        m_pages[0].Separation = PageContent::SecondSeparated;
        readyForPaint();
        return;
    }
    if(m_pageManager)
        m_pageManager->nextPage();
    if(isSlideShow())
        toggleSlideShow();
}

void ImageView::on_prevPage_triggered()
{
    if(qApp->SeparatePagesWhenWideImage() && m_pages[0].Separation == PageContent::SecondSeparated) {
        m_pages[0].Separation = PageContent::FirstSeparated;
        readyForPaint();
        return;
    }
    m_pageBacking = true;
    if(m_pageManager)
        m_pageManager->prevPage();
    if(isSlideShow())
        toggleSlideShow();
    m_pageBacking = false;
}

void ImageView::on_fastForwardPage_triggered()
{
    if(m_pageManager)
        m_pageManager->fastForwardPage();
    if(isSlideShow())
        toggleSlideShow();
}

void ImageView::on_fastBackwardPage_triggered()
{
    if(m_pageManager)
        m_pageManager->fastBackwardPage();
    if(isSlideShow())
        toggleSlideShow();
}

void ImageView::on_firstPage_triggered()
{
    if(m_pageManager)
        m_pageManager->firstPage();
    if(isSlideShow())
        toggleSlideShow();
}

void ImageView::on_lastPage_triggered()
{
    if(m_pageManager)
        m_pageManager->lastPage();
    if(isSlideShow())
        toggleSlideShow();
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

void ImageView::on_rotatePage_triggered()
{
    if(!m_pageManager)
        return;
    m_pageRotations[m_pageManager->currentPage()] += 90;
    readyForPaint();
}

void ImageView::on_showSubfolders_triggered(bool enable)
{
    qApp->setShowSubfolders(enable);
    if(m_pageManager->isFolder())
        m_pageManager->loadVolume(m_pageManager->volumePath());
}

void ImageView::on_slideShowChanging_triggered()
{
    int page = m_pageManager->currentPage();
    m_pageManager->nextPage();
    if(page == m_pageManager->currentPage())
        m_pageManager->firstPage();
}


void ImageView::on_nextVolume_triggered()
{
    if(m_pageManager)
        m_pageManager->nextVolume();
}

void ImageView::on_prevVolume_triggered()
{
    if(m_pageManager)
        m_pageManager->prevVolume();
}

#define HOVER_BORDER 20
//#define NOT_HOVER_AREA 100

void ImageView::mouseMoveEvent(QMouseEvent *e)
{
    QGraphicsView::mouseMoveEvent(e);
//    qDebug() << e;
    int NOT_HOVER_AREA = width() / 3;
	int hover_border = qApp->LargeToolbarIcons() ? 3 * HOVER_BORDER : HOVER_BORDER;
    if(e->pos().x() < hover_border && e->pos().y() < height()- hover_border) {
        if(m_hoverState != Qt::AnchorLeft)
            emit anchorHovered(Qt::AnchorLeft);
        m_hoverState = Qt::AnchorLeft;
//        QApplication::setOverrideCursor(Qt::PointingHandCursor);
        setCursor(QCursor(Qt::PointingHandCursor));
        return;
    }
    if(e->pos().x() > width()- hover_border) {
        if(m_hoverState != Qt::AnchorRight)
            emit anchorHovered(Qt::AnchorRight);
        m_hoverState = Qt::AnchorRight;
//        QApplication::setOverrideCursor(Qt::PointingHandCursor);
        setCursor(QCursor(Qt::PointingHandCursor));

        return;
    }
    if(qApp->LoupeTool()) {
        setCursor(m_loupeCursor);
    } else {
        setCursor(QCursor(Qt::ArrowCursor));
    }
    if(m_loupeEnable)
        scrollOnLoupeMode();
    else if(qApp->ScrollWithCursorWhenZooming() && (scene()->sceneRect().width() > width() || scene()->sceneRect().height() > height())) {
        scrollOnZoomMode();
    }

//    QApplication::setOverrideCursor(Qt::ArrowCursor);
    if(e->pos().y() < hover_border) {
        if(m_hoverState != Qt::AnchorTop)
           emit anchorHovered(Qt::AnchorTop);
        m_hoverState = Qt::AnchorTop;
        return;
    }
    if(e->pos().y() > height()- hover_border && e->pos().x() > NOT_HOVER_AREA) {
        if(m_hoverState != Qt::AnchorBottom)
           emit anchorHovered(Qt::AnchorBottom);
        m_hoverState = Qt::AnchorBottom;
        return;
    }
    if(m_hoverState != Qt::AnchorHorizontalCenter)
       emit anchorHovered(Qt::AnchorHorizontalCenter);
    m_hoverState = Qt::AnchorHorizontalCenter;
}

void ImageView::wheelEvent(QWheelEvent *event)
{
    if(event->buttons() & Qt::RightButton
       || qApp->keyboardModifiers() & Qt::ControlModifier)
        return;
    if(m_loupeEnable) {
        if(event->delta() < 0)
            m_loupeFactor = qMax(1.5, m_loupeFactor-0.5);
        if(event->delta() > 0)
            m_loupeFactor += 0.5;
        readyForPaint();
        return;
    }
    if(qApp->ScrollWithCursorWhenZooming())
        return;
    QGraphicsView::wheelEvent(event);
}

void ImageView::mousePressEvent(QMouseEvent *event)
{
    if(!qApp->LoupeTool() || (event->buttons() != Qt::LeftButton)) {
        QGraphicsView::mousePressEvent(event);
        return;
    }
    m_loupeEnable = true;
    readyForPaint();
}

void ImageView::mouseReleaseEvent(QMouseEvent *event)
{
    if(!qApp->LoupeTool() || (event->buttons() & Qt::LeftButton)) {
        QGraphicsView::mouseReleaseEvent(event);
        return;
    }
    m_loupeEnable = false;
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
    if(!m_pages.size())
        return;
    if(qApp->Fitting()) {
        qApp->setFitting(false);
        emit fittingChanged(false);
        int scale = m_pages[0].GrItem->scale()*100;
        viewSizeIdx = 0;
        qDebug() << viewSizeIdx << (viewSizeList.size()-1) << scale <<  viewSizeList[viewSizeIdx];
        while(viewSizeIdx < viewSizeList.size()-1 && viewSizeList[viewSizeIdx] < scale)
            viewSizeIdx++;
        readyForPaint();
        return;
    }
    if(viewSizeIdx < viewSizeList.size() -1)
        viewSizeIdx++;
    readyForPaint();
}

void ImageView::on_scaleDown_triggered()
{
    if(!m_pages.size())
        return;
    if(qApp->Fitting()) {
        qApp->setFitting(false);
        emit fittingChanged(false);
        int scale = m_pages[0].GrItem->scale()*100;
        viewSizeIdx = viewSizeList.size()-1;
        while(viewSizeIdx > 0 && viewSizeList[viewSizeIdx] > scale)
            viewSizeIdx--;
        readyForPaint();
        return;
    }
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

void ImageView::on_dontEnlargeSmallImagesOnFitting(bool enable)
{
    qApp->setDontEnlargeSmallImagesOnFitting(enable);
    readyForPaint();
}

void ImageView::onActionSeparatePagesWhenWideImage_triggered(bool enable)
{
    qApp->setSeparatePagesWhenWideImage(enable);
    readyForPaint();
}

void ImageView::onActionLoupe_triggered(bool enable)
{
    qApp->setLoupeTool(enable);
    if(!enable) {
        m_loupeEnable = false;
        readyForPaint();
    }
}

void ImageView::onActionScrollWithCursorWhenZooming_triggered(bool enable)
{
    qApp->setScrollWithCursorWhenZooming(enable);
    readyForPaint();
}

void ImageView::on_openFiler_triggered()
{
    if(!m_pageManager)
        return;
    QString path = m_pageManager->volumePath();
    if(m_pageManager->isFolder()) {
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

void ImageView::on_copyPage_triggered()
{
    if(m_pages.empty())
        return;
    QClipboard* clipboard = qApp->clipboard();
    clipboard->setImage(m_pages[0].Ic.Image);
}

void ImageView::on_copyFile_triggered()
{
    QClipboard* clipboard = qApp->clipboard();
    QMimeData* mimeData = new QMimeData();
    QString path = QString("file:///%1").arg(m_pageManager->currentPagePath());
    mimeData->setData("text/uri-list", path.toUtf8());
    clipboard->setMimeData(mimeData);
}

