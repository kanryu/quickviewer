#include <QtGui>
#include <QDebug>
#include "sidesplitter.h"

SideSplitter::SideSplitter(QWidget *parent)
    : QSplitter(parent)
{
//    setMouseTracking(true);

}

void SideSplitter::mouseMoveEvent(QMouseEvent *e)
{
    qDebug() << "SideSplitter:" << e;
    QCursor cur;
    cur.setShape(Qt::CrossCursor);
    setCursor(cur);
}
