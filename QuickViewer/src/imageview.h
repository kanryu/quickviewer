#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QtCore>
#include <QtWidgets>

#include "volumemanager.h"
#include "exifdialog.h"
#include "models/pagemanager.h"
#include "models/shadermanager.h"
#include "models/pagecontent.h"

class SavedPoint : public QPoint
{
public:
    void start(QPoint ptStart) {
        m_ptStart = ptStart;
        m_ptSaved = QPoint(x(),y());
    }
    void step(QPoint ptStep) {
//        qDebug("before: pt:(%d,%d) step:(%d,%d) start:(%d,%d)",
//               x(),y(),
//               ptStep.x(),ptStep.y(),
//               m_ptStart.x(),m_ptStart.y() );
        setX(m_ptSaved.x() + ptStep.x() - m_ptStart.x());
        setY(m_ptSaved.y() + ptStep.y() - m_ptStart.y());
//        qDebug("after:  pt:(%d,%d)", x(),y());
    }
    QPoint pt() const { return QPoint(x(), y()); }
    void reset() { setX(0);setY(0);}

private:
    QPoint m_ptStart;
    QPoint m_ptSaved;
};

/**
 * @brief The ImageView class
 * It provides to show 1 or 2 images once, using OpenGL.
 * It is made on QGraphicView, each images is used as QGraphicsItem
 */
class ImageView : public QGraphicsView
{
    Q_OBJECT
public:
    enum RendererType { Native, OpenGL, Image };
    explicit ImageView(QWidget *parent = Q_NULLPTR);
    void setRenderer(RendererType type = Native);
    void setPageManager(PageManager* manager);
    /**
     * @brief currentViewSize returns current manual resizing magnification value
     * @return
     */
    int currentViewSize() { return viewSizeList[viewSizeIdx]; }
    Qt::AnchorPoint hoverState() const { return m_hoverState; }
    void skipRisizeEvent(bool skipped) { m_skipResizeEvent = skipped; }
    bool isSlideShow() const { return m_slideshowTimer != nullptr; }
    void toggleSlideShow();
    void setWillFullscreen(bool fullscreen) { m_isFullScreen = fullscreen; }
    void resetBackgroundColor();
    void setSceneRectMode(bool scrolled, const QRect& sceneRect);
    bool isScrollMode() { return m_scrollMode; }

signals:
    /**
     * @brief anchorHovered a signal when the mouse moved to one of 4 edges on this widget
     */
    void anchorHovered(Qt::AnchorPoint anchor) const;
//    void pageChanged() const;

    void fittingChanged(bool fitting) const;
    void scrollModeChanged(bool scrolling) const;

protected:
//    void paintEvent( QPaintEvent *event );
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
//    void mousePressEvent(QMouseEvent *event);
//    void mouseReleaseEvent(QMouseEvent *event);
//    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
//    void dragEnterEvent(QDragEnterEvent *event) { event->accept(); qDebug() << "ImageView::dragEnterEvent"; }
//    void dropEvent( QDropEvent *e ) {qDebug() << "ImageView::dropEvent";}
//    void dragMoveEvent( QDragMoveEvent *e ) {qDebug() << "ImageView::dragMoveEvent";}
//    void dragLeaveEvent( QDragLeaveEvent * e ) {qDebug() << "ImageView::dragLeaveEvent";}

public slots:
    void on_volumeChanged_triggered(QString path);
    bool on_addImage_triggered(ImageContent image, bool pageNext);
    void on_clearImages_triggered();
    void readyForPaint();

    // Navigation
    void on_nextPage_triggered();
    void on_prevPage_triggered();
    void on_fastForwardPage_triggered();
    void on_fastBackwardPage_triggered();
    void on_firstPage_triggered();
    void on_lastPage_triggered();
    void on_nextOnlyOnePage_triggered();
    void on_prevOnlyOnePage_triggered();
    void on_rotatePage_triggered();
    void on_showSubfolders_triggered(bool enable);

    // SlideShow
    void on_slideShowChanging_triggered();

    // Volume
    void on_nextVolume_triggered();
    void on_prevVolume_triggered();

    // View
    void on_fitting_triggered(bool maximized);
    void on_dualView_triggered(bool viewdual);
    void on_rightSideBook_triggered(bool rightSideBook);
    void on_wideImageAsOneView_triggered(bool wideImage);
    void on_firstImageAsOneView_triggered(bool firstImage);
    void on_dontEnlargeSmallImagesOnFitting(bool enable);

    void on_scaleUp_triggered();
    void on_scaleDown_triggered();
    void on_openFiler_triggered();
    void on_copyPage_triggered();
    void on_copyFile_triggered();


private:

    RendererType m_renderer;
    QVector<PageContent> m_pages;

    SavedPoint m_ptLeftTop;
    QGraphicsScene* m_scene;
    Qt::AnchorPoint m_hoverState;
    /**
     * @brief for manual ZoomIn or ZoomOut
     */
    QList<int> viewSizeList;
    QVector<int> m_pageRotations;
    int viewSizeIdx;
    QFont m_font;

    PageManager* m_pageManager;
    ShaderManager m_effectManager;
    QTimer* m_slideshowTimer;

    bool m_isMouseDown;
    bool m_wideImage;
    bool m_skipResizeEvent;
    bool m_isFullScreen;
    bool m_scrollMode;
};



#endif // IMAGEVIEW_H
