#include "pageslider.h"
#include <QMouseEvent>

PageSlider::PageSlider(QWidget* parent)
    : QSlider(parent)
{

}

void PageSlider::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        int newValue = 0;
        if (orientation() == Qt::Vertical)
            newValue = minimum() + ((maximum()-minimum()) * (height()-event->y())) / height() ;
        else
            newValue = minimum() + ((maximum()-minimum()+1) * event->x()) / width();

        if(newValue != value()) {
            setValue(newValue);
            event->accept();
            return;
        }
    }
    QSlider::mousePressEvent(event);
}
