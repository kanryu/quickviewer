#ifndef QLUMINOR_H
#define QLUMINOR_H

#include <QtGui>

class QLuminor : public QObject
{
    Q_OBJECT
public:
    explicit QLuminor(QObject *parent = nullptr);

    static QImage toLuminor(const QImage& src, float brightness, float contrast, float gamma);
    static QImage toLuminorRGBA(const QImage& src, float brightness, float contrast, float gamma);
};

#endif // QLUMINOR_H
