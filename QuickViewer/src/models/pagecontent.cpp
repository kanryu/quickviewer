#include <QtConcurrent>

#include "pagecontent.h"
#include "qvapplication.h"
#include "qzimg.h"

PageContent::PageContent(QObject* parent)
    : QObject(parent)
    , Ic()
    , GrItem(nullptr)
    , Rotate(0)
    , m_resizeGeneratingState(0)
{

}

PageContent::PageContent(QObject* parent, QGraphicsScene *s, ImageContent ic)
    : QObject(parent)
    , Scene(s)
    , Ic(ic)
    , GrItem(nullptr)
    , Rotate(0)
    , m_resizeGeneratingState(0)
{
    if(ic.Info.ImageWidth > 0 && ic.Info.Orientation != 1) {
        switch(ic.Info.Orientation) {
        case 6: // left 90 digree turned
            Rotate = 90;
            break;
        case 8: // right 90 digree turned
            Rotate = 270;
            break;
        }
    }
    initializePage();
}

PageContent::PageContent(const PageContent &rhs)
    : QObject(rhs.parent())
    , Scene(rhs.Scene)
    , Ic(rhs.Ic)
    , ResizedPage(rhs.ResizedPage)
    , GrItem(rhs.GrItem)
    , Rotate(rhs.Rotate)
    , m_resizeGeneratingState(0)
{

}

PageContent &PageContent::operator=(const PageContent &rhs) {
    Scene = rhs.Scene;
    Ic = rhs.Ic;
    ResizedPage = rhs.ResizedPage;
    GrItem = rhs.GrItem;
    Rotate = rhs.Rotate;
    m_resizeGeneratingState = 0;
    return *this;
}

QPoint PageContent::Offset(int rotateOffset) {
    int rot = (Rotate+rotateOffset) % 360;
    switch(rot) {
    case 90:  return QPoint(Ic.Image.height(), 0);
    case 180: return QPoint(Ic.Image.width(), Ic.Image.height());
    case 270: return QPoint(0, Ic.Image.width());
    default:  return QPoint();
    }
}

QSize PageContent::CurrentSize(int rotateOffset) {
    int rot = (Rotate+rotateOffset) % 360;
    return rot==90 || rot==270 ? QSize(Ic.Image.height(), Ic.Image.width()) : Ic.Image.size();
}

QRect PageContent::setPageLayoutFitting(QRect viewport, PageContent::Fitting fitting, int rotateOffset) {
    QSize currentSize = CurrentSize(rotateOffset);
    QSize newsize = currentSize.scaled(viewport.size(), Qt::KeepAspectRatio);
    qreal scale = 1.0*newsize.width()/currentSize.width();

    QPoint of = Offset(rotateOffset);
    of *= scale;

    QRect drawRect;
    if(newsize.height() == viewport.height()) { // fitting on upper and bottom
        int ofsinviewport = fitting==FitLeft ? 0 : fitting==FitCenter ? (viewport.width()-newsize.width())/2 : viewport.width()-newsize.width();
        drawRect = QRect(QPoint(of.x() + viewport.x() + ofsinviewport, of.y()), newsize);
    } else { // fitting on left and right
        drawRect = QRect(QPoint(of.x() + viewport.x(), of.y() + (viewport.height()-newsize.height())/2), newsize);
    }
//    GrItem->setScale(scale);
//    GrItem->setRotation(Rotate+rotateOffset);
//    GrItem->setPos(drawRect.topLeft());
    applyResize(scale, rotateOffset, drawRect.topLeft(), newsize);
    return drawRect;
}

QRect PageContent::setPageLayoutManual(QRect viewport, PageContent::Fitting fitting, qreal scale, int rotateOffset) {
    QSize currentSize = CurrentSize(rotateOffset);
    QSize newsize = currentSize * scale;

    QPoint of = Offset(rotateOffset);
    of *= scale;

    int ofsinviewport = fitting==FitLeft ? 0 : fitting==FitCenter ? (viewport.width()-newsize.width())/2 : viewport.width()-newsize.width();
    QRect drawRect(QPoint(of.x() + viewport.x() + ofsinviewport, of.y()), newsize);

    applyResize(scale, rotateOffset, drawRect.topLeft(), newsize);
    return drawRect;
}

void PageContent::applyResize(qreal scale, int rotateOffset, QPoint pos, QSize newsize)
{
    // need CPU resizing
    if(qApp->Effect() > qvEnums::UsingCpuResizer && qApp->Effect() < qvEnums::UsingSomeShader) {
        if(!ResizedPage.isNull() && ResizedPage.size() != newsize) {
            initializePage();
        }
        if(ResizedPage.isNull() && m_resizeGeneratingState==0) {
            m_resizeGeneratingState = 1;
            QFuture<QImage> future = QtConcurrent::run(QZimg::scaled, Ic.Image.toImage(), newsize, Qt::IgnoreAspectRatio, QZimg::ResizeBicubic);
            connect(&generateWatcher, SIGNAL(finished()), this, SLOT(on_resizeFinished_trigger()));
            generateWatcher.setFuture(future);
        }
        if(!ResizedPage.isNull() && m_resizeGeneratingState==2) {
            Scene->removeItem(GrItem);
            delete GrItem;
            GrItem = Scene->addPixmap(ResizedPage);
            GrItem->setRotation(Rotate);
        }
    }
    GrItem->setScale(ResizedPage.isNull() ? scale : 1.0);
    GrItem->setRotation(Rotate+rotateOffset);
    GrItem->setPos(pos);
}

void PageContent::initializePage()
{
    if(GrItem) {
        Scene->removeItem(GrItem);
        delete GrItem;
    }
    GrItem = Scene->addPixmap(Ic.Image);
    GrItem->setRotation(Rotate);
    ResizedPage = QPixmap();
    m_resizeGeneratingState = 0;
}

void PageContent::on_resizeFinished_trigger()
{
    ResizedPage = QPixmap::fromImage(generateWatcher.result());

    m_resizeGeneratingState = 2;
    disconnect(&generateWatcher, SIGNAL(finished()), this, SLOT(on_resizeFinished_trigger()));
    emit resizeFinished();
}
