#ifndef PAGECONTENT_H
#define PAGECONTENT_H

#include <QtCore>
#include <QtWidgets>

#include "exif.h"
#include "qvmovie.h"

/**
 * @brief The ImageContent struct
 * actual Image data and metadata
 */
struct ImageContent
{
public:
    /**
     * @brief Image is a pixmap of the image for viewing
     */
    QImage Image;
    /**
     * @brief ResizedImage is resized to actual view size from Image
     */
    QImage ResizedImage;
    /**
     * @brief Movie will be initialized when imageReader.supportsAnimation() == true
     */
    QvMovie Movie;
    /**
     * @brief BaseSize is original size of the image
     */
    QSize BaseSize;
    /**
     * @brief ImportSize is actual size of image for viewing
     */
    QSize ImportSize;
    /**
     * @brief Path is path of the image
     */
    QString Path;
    /**
     * @brief Info is Exif Information of the image(JPEG only)
     */
    easyexif::EXIFInfo Info;
    size_t FileLength;

    ImageContent():FileLength(0){}
    ImageContent(QString path, size_t length):Path(path),FileLength(length){}
    ImageContent(QImage image, QString path, QSize size, easyexif::EXIFInfo info, size_t length)
        : Image(image), BaseSize(size), ImportSize(image.size()), Path(path), Info(info), FileLength(length) {}
    ImageContent(const ImageContent& rhs)
        : Image(rhs.Image)
        , ResizedImage(rhs.ResizedImage)
        , Movie(rhs.Movie)
        , BaseSize(rhs.BaseSize)
        , ImportSize(rhs.ImportSize)
        , Path(rhs.Path)
        , Info(rhs.Info)
        , FileLength(rhs.FileLength)
    {}
    inline ImageContent& operator=(const ImageContent &rhs)
    {
        Image = rhs.Image;
        ResizedImage = rhs.ResizedImage;
        Movie = rhs.Movie;
        Path = rhs.Path;
        BaseSize = rhs.BaseSize;
        ImportSize = rhs.ImportSize;
        Info = rhs.Info;
        FileLength = rhs.FileLength;
        return *this;
    }
    bool wideImage() const {return BaseSize.width() > BaseSize.height(); }
    void initialize();
};

/**
 * @brief PageContent
 * contains the informations of a Page
 */
class PageContent : public QObject
{
    Q_OBJECT
public:
    enum Fitting {
        FitCenter,
        FitLeft,
        FitRight
    };
    enum SeparationState {
        NoSeparated,
        FirstSeparated,
        SecondSeparated
    };

    QGraphicsScene *Scene;
    ImageContent Ic;
    /**
     * @brief GrItem
     * Page image is used as a QGraphicsItem. it will be registed to the scene
     */
    QGraphicsItem* GrItem;
//    /**
//     * @brief Resized
//     * Store the image changed to the specified size (newsize)
//     */
//    QPixmap ResizedPage;
    QFutureWatcher<QImage> generateWatcher;
    /**
     * @brief Rotate: rotation as digrees
     */
    int Rotate;
    /**
     * @brief GText is information as a text on fullscreen
     */
    QString Text;
    QGraphicsTextItem* GText;
    QGraphicsRectItem* GTextSurface;
    qreal DrawScale;
    SeparationState Separation;

    PageContent(QObject* parent=nullptr);
    PageContent(QObject* parent, QGraphicsScene *s, ImageContent ic);
    PageContent(const PageContent& rhs);
    PageContent& operator=(const PageContent& rhs);

    QPoint Offset(int rotateOffset=0);
    QSize CurrentSize(int rotateOffset=0);

    /**
     * @brief setPageLayout set each image on the page
     * @param viewport: the image must be inscribed in the viewport area
     */
    QRect setPageLayoutFitting(QRect viewport, Fitting fitting, qreal loupe, int rotateOffset=0);
    QRect setPageLayoutManual(QRect viewport, Fitting fitting, qreal scale, int rotateOffset=0, bool loupe=false);

    void applyResize(qreal scale, int rotateOffset, QPoint pos, QSize newsize, bool loupe=false);
    void initializePage(bool resetResized=false);
    void resetSignage(QRect viewport, PageContent::Fitting fitting);
    void resetScene(QGraphicsScene* scene);
    void checkInitialize();
    void dispose();
signals:
    void resizeFinished();
public slots:
    void on_resizeFinished_trigger();
    void on_animateFrameChanged_trigger(int frameNumber);
    void on_animateFinished_trigger();

private:
    int m_resizeGeneratingState;
    bool initialized;
};


class PageContentProtocol
{
public:
    virtual QVector<PageContent>* pages()=0;
};


#endif // PAGECONTENT_H
