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
class ImageView : public QGraphicsView, public PageContentProtocol
{
    Q_OBJECT
public:
    enum RendererType { Native, OpenGL, Image };
    typedef QPair<uint, uint> ZoomFraction;
    explicit ImageView(QWidget *parent = Q_NULLPTR);
    void setRenderer(RendererType type = Native);
    void setPageManager(PageManager* manager);
    Qt::AnchorPoint hoverState() const { return m_hoverState; }
    void skipRisizeEvent(bool skipped) { m_skipResizeEvent = skipped; }
    bool isSlideShow() const { return m_slideshowTimer != nullptr; }
    void toggleSlideShow();
    void setWillFullscreen(bool fullscreen) { m_isFullScreen = fullscreen; }
    void resetBackgroundColor();
    void setSceneRectMode(bool scrolled, const QRect& sceneRect);
    void scrollOnLoupeMode();
    void scrollOnZoomMode();
    bool isScrollMode() { return m_scrollMode; }
    QVector<PageContent>* pages() override {return &m_pages; }
    void updateViewportOffset(QPointF moved);
    void updateViewportFactors(qreal currentScale, qreal currentRotate);
    void commitViewportFactors();
    void resetViewportFactors();

signals:
    /**
     * @brief anchorHovered a signal when the mouse moved to one of 4 edges on this widget
     */
    void anchorHovered(Qt::AnchorPoint anchor) const;
//    void pageChanged() const;

    void fittingChanged(bool fitting) const;
    void scrollModeChanged(bool scrolling) const;
    void zoomingChanged() const;

protected:
//    void paintEvent( QPaintEvent *event );
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
//    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

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
    void onActionSeparatePagesWhenWideImage_triggered(bool enable);
    void onActionLoupe_triggered(bool enable);
    void onActionScrollWithCursorWhenZooming_triggered(bool enable);
    void onActionShowFullscreenSignage_triggered(bool enable);

    void on_scaleUp_triggered();
    void on_scaleDown_triggered();
    void on_openFiler_triggered();
    void on_copyPage_triggered();
    void on_copyFile_triggered();


private:
    qreal getZoomScale() {return 1.0*viewSizeList[viewSizeIdx].first/viewSizeList[viewSizeIdx].second;}

    RendererType m_renderer;
    QVector<PageContent> m_pages;

    SavedPoint m_ptLeftTop;
    QGraphicsScene* m_scene;
    Qt::AnchorPoint m_hoverState;
    /**
     * @brief for manual ZoomIn or ZoomOut
     */
    QList<ZoomFraction> viewSizeList;
    QVector<int> m_pageRotations;
    int viewSizeIdx;
    QFont m_font;
    QCursor m_loupeCursor;

    PageManager* m_pageManager;
    ShaderManager m_effectManager;
    QTimer* m_slideshowTimer;

    // rotate or scale with touchEvents
    qreal m_beginScaleFactor;
    qreal m_beginRotateFactor;
    qreal m_loupeFactor;

    bool m_isMouseDown;
    bool m_wideImage;
    bool m_skipResizeEvent;
    bool m_isFullScreen;
    bool m_scrollMode;
    bool m_pageBacking;
    bool m_loupeEnable;

    // Loupe
    QPoint m_loupeBasePos;
    QRect m_sceneRect;
    QPoint m_scrollBaseValues;
};



#endif // IMAGEVIEW_H
