#ifndef PAGESLIDER_H
#define PAGESLIDER_H

#include <QSlider>

class PageSlider : public QSlider
{
public:
    PageSlider(QWidget* parent);

protected:
  void mousePressEvent ( QMouseEvent * event );
};

#endif // PAGESLIDER_H
