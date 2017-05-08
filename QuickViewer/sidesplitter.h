#ifndef SIDESPLITTER_H
#define SIDESPLITTER_H

#include <QtWidgets>

class SideSplitter : public QSplitter
{
public:
    SideSplitter(QWidget* parent);
    virtual void mouseMoveEvent(QMouseEvent* e) override;
};

#endif // SIDESPLITTER_H
