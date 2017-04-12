#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QWidget>
#include <QtDebug>
#include <QGraphicsView>
#include <QDragEnterEvent>
#include "filevolume.h"
#include "exifdialog.h"
#include "pagemanager.h"
#include <QGraphicsPixmapItem>

/**
 * @brief The SavedPoint class
 * マウスやキーボードによる画像の移動計算の補助を行う。マウスドラッグ開始時の座標を保存し、
 * ドラッグ時にマウスカーソルが相対的に移動した分だけ画像を移動させるための座標を算出する
 */
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

struct PageGraphicsItem
{
    QPixmap Image;
    /**
     * @brief GrItem
     * 表示画像をQGraphicsItem化したもの。これをsceneに登録することで画像を表示する
     */
    QGraphicsItem* GrItem;
    /**
     * @brief Offset if GrItem is rolling, Offset is not Point(0,0)
     */
    QSize PageSize;
    QPoint Offset;
    enum Fitting {
        FitCenter,
        FitLeft,
        FitRight
    };
    PageGraphicsItem()
     : Image(), GrItem(nullptr), PageSize(), Offset(){}
    PageGraphicsItem(QPixmap image, QGraphicsItem* item, QSize size, QPoint offset)
        : Image(image), GrItem(item), PageSize(size), Offset(offset){}

    /**
     * @brief setPageLayout set each image on the page
     * @param viewport: the image must be inscribed in the viewport area
     */
    void setPageLayoutFitting(QRect viewport, Fitting fitting) {
        QSize newsize = PageSize.scaled(viewport.size(), Qt::KeepAspectRatio);
        qreal scale = 1.0*newsize.width()/PageSize.width();
        GrItem->setScale(scale);
        QPoint of = QPoint(scale*Offset.x(), scale*Offset.y());
        if(newsize.height() == viewport.height()) { // fitting on upper and bottom
            int ofsinviewport = fitting==FitLeft ? 0 : fitting==FitCenter ? (viewport.width()-newsize.width())/2 : viewport.width()-newsize.width();
            GrItem->setPos(of.x() + viewport.x() + ofsinviewport, of.y());
        } else { // fitting on left and right
            GrItem->setPos(of.x() + viewport.x(), of.y() + (viewport.height()-newsize.height())/2);
        }
    }
    void setPageLayoutManual(QRect viewport, Fitting fitting, qreal scale) {
        GrItem->setScale(scale);
        QSize size = viewport.size();
        QSize newsize = PageSize;
        newsize *= scale;
        QPoint of = QPoint(scale*Offset.x(), scale*Offset.y());
        int ofsinviewport = fitting==FitLeft ? 0 : fitting==FitCenter ? (viewport.width()-newsize.width())/2 : viewport.width()-newsize.width();
        GrItem->setPos(of.x() + viewport.x() + ofsinviewport, of.y());
    }
};

/**
 * @brief The ImageView class
 * セットした画像を１枚表示できる。
 * 画像はマウスでドラッグできる。
 */
class ImageView : public QGraphicsView
{
    Q_OBJECT
public:
    enum RendererType { Native, OpenGL, Image };
    explicit ImageView(QWidget *parent = Q_NULLPTR);
    void setRenderer(RendererType type = Native);
    void reloadCurrentPage(bool pageNext=true);
    void setPageManager(PageManager* manager);
    /**
     * @brief currentViewSize returns current manual resizing magnification value
     * @return
     */
    int currentViewSize() { return viewSizeList[viewSizeIdx]; }
    Qt::AnchorPoint hoverState() const { return m_hoverState; }
    void skipRisizeEvent(bool skipped) { m_skipResizeEvent = skipped; }

signals:
    /**
     * @brief anchorHovered ImageViewのフレーム端にマウスカーソルが移動した場合に発生するシグナル
     */
    void anchorHovered(Qt::AnchorPoint anchor) const;
    void pageChanged() const;

protected:
//    void paintEvent( QPaintEvent *event );
    void mouseMoveEvent(QMouseEvent *event);
//    void mousePressEvent(QMouseEvent *event);
//    void mouseReleaseEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event) override;
//    void dragEnterEvent(QDragEnterEvent *event) { event->accept(); qDebug() << "ImageView::dragEnterEvent"; }
//    void dropEvent( QDropEvent *e ) {qDebug() << "ImageView::dropEvent";}
//    void dragMoveEvent( QDragMoveEvent *e ) {qDebug() << "ImageView::dragMoveEvent";}
//    void dragLeaveEvent( QDragLeaveEvent * e ) {qDebug() << "ImageView::dragLeaveEvent";}

public slots:
    bool addImage(ImageContent image, bool pageNext);
    void clearImages();
    void readyForPaint();

    void on_nextPage_triggered();
    void on_prevPage_triggered();
    void on_firstPage_triggered();
    void on_lastPage_triggered();
    void on_nextOnlyOnePage_triggered();
    void on_prevOnlyOnePage_triggered();

    void on_fitting_triggered(bool maximized);
    void on_dualView_triggered(bool viewdual);
    void on_rightSideBook_triggered(bool rightSideBook);
    void on_wideImageAsOneView_triggered(bool wideImage);
    void on_firstImageAsOneView_triggered(bool firstImage);

    void on_scaleUp_triggered();
    void on_scaleDown_triggered();
    void on_openFiler_triggered();
    void on_openExifDialog_triggered();
    void on_copyPage_triggered();

private:

    RendererType m_renderer;
    QVector<PageGraphicsItem> m_pages;

    SavedPoint m_ptLeftTop;
    QGraphicsScene* m_scene;
    bool m_isMouseDown;
    Qt::AnchorPoint m_hoverState;
    /**
     * @brief マニュアル拡大縮小するときの倍率を保持するリスト
     */
    QList<int> viewSizeList;
    int viewSizeIdx;
    QFont m_font;
    bool m_wideImage;
    bool m_skipResizeEvent;

    ExifDialog exifDialog;

    PageManager* m_pageManager;
};



#endif // IMAGEVIEW_H
