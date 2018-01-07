#ifndef QZIMG_H
#define QZIMG_H

#include <QtGui>

class QZimgPrivate;

class QZimg : public QObject
{
    Q_OBJECT
public:
    enum FilterMode {
        ResizePoint,
        ResizeBicubic,
        ResizeSpline16,
        ResizeSpline36,
        ResizeLanczos,
    };
#if QT_VERSION_MAJOR >= 5
    Q_ENUM(FilterMode)
#endif


    explicit QZimg(QObject *parent = 0);
    ~QZimg();

    /**
     * @brief createPackedImage zimg must require 64bit packed memory bitmap
     * @param size of new image
     * @param fmt of new image(only Format_Grayscale8, Format_RGB888, Format_RGBA8888)
     * @param stridePack packed byte size for each line(64 bytes aligned, or 64x4 bytes aligned for Format_RGBA8888)
     * @return a image which have 64byte aligned stride bytes for each line
     */
    static QImage createPackedImage(QSize size, QImage::Format fmt, int stridePack=64);

    /**
     * @brief stridePackedImage
     * @param src
     * @param stridePack
     * @return a image which have 64byte aligned stride bytes for each line
     */
    static QImage toPackedImage(const QImage& src, int stridePack=64);

    static QImage scaled(const QImage& src, const QSize& s, Qt::AspectRatioMode aspectMode = Qt::IgnoreAspectRatio,
                         FilterMode mode = ResizeBicubic);

signals:

public slots:
private:
    QZimgPrivate* d;
};

#endif // QZIMG_H
