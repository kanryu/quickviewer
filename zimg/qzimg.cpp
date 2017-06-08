#include <QtGui>
#include <memory>

#include "qzimg.h"
#include "api/zimg++.hpp"
#include "aligned_malloc.h"

class QZimgPrivate
{

};
struct Callback {
    const zimgxx::zimage_buffer *buffer;
    const QImage *img;
};

static std::pair<zimgxx::zimage_buffer, std::shared_ptr<void>> allocate_buffer(const zimgxx::zimage_format &format, unsigned count)
{
    zimgxx::zimage_buffer buffer;
    std::shared_ptr<void> handle;
    unsigned char *ptr;

    unsigned mask = zimg_select_buffer_mask(count);
    size_t channel_size[3] = { 0 };
    size_t pixel_size;

    count = (mask == ZIMG_BUFFER_MAX) ? format.height : mask + 1;

    if (format.pixel_type == ZIMG_PIXEL_FLOAT)
        pixel_size = sizeof(float);
    else if (format.pixel_type == ZIMG_PIXEL_WORD || format.pixel_type == ZIMG_PIXEL_HALF)
        pixel_size = sizeof(uint16_t);
    else
        pixel_size = sizeof(uint8_t);

    for (unsigned p = 0; p < (format.color_family == ZIMG_COLOR_GREY ? 1U : 3U); ++p) {
        unsigned count_plane = p ? count : count >> format.subsample_h;
        unsigned mask_plane = (mask == ZIMG_BUFFER_MAX) ? mask : mask >> format.subsample_h;
        size_t row_size = format.width * pixel_size;
        ptrdiff_t stride = row_size % 64 ? row_size - row_size % 64 + 64 : row_size;

        buffer.mask(p) = mask_plane;
        buffer.stride(p) = stride;
        channel_size[p] = static_cast<size_t>(stride) * count_plane;
    }

    handle.reset(aligned_malloc(channel_size[0] + channel_size[1] + channel_size[2], 64), &aligned_free);
    ptr = static_cast<unsigned char *>(handle.get());

    for (unsigned p = 0; p < (format.color_family == ZIMG_COLOR_GREY ? 1U : 3U); ++p) {
        buffer.data(p) = ptr;
        ptr += channel_size[p];
    }

    return{ buffer, handle };
}

static std::shared_ptr<void> allocate_buffer(size_t size)
{
    return{ aligned_malloc(size, 64), &aligned_free };
}


static void unpack_bgr(const void *bgr, void * const planar[3], unsigned bit_depth, unsigned left, unsigned right)
{
    const uint8_t *packed_bgr = static_cast<const uint8_t *>(bgr);
    uint8_t *planar_r = static_cast<uint8_t *>(planar[0]);
    uint8_t *planar_g = static_cast<uint8_t *>(planar[1]);
    uint8_t *planar_b = static_cast<uint8_t *>(planar[2]);
    unsigned step = bit_depth / 8;
    if(step == 1) {
        ::memcpy(&planar_r[left], &packed_bgr[left], right-left);
        return;
    }

    for (unsigned j = left; j < right; ++j) {
        uint8_t r, g, b;

        b = packed_bgr[j * step + 0];
        g = packed_bgr[j * step + 1];
        r = packed_bgr[j * step + 2];

        planar_r[j] = r;
        planar_g[j] = g;
        planar_b[j] = b;
    }
}

static void pack_bgr(const void * const planar[3], void *bgr, unsigned bit_depth, unsigned left, unsigned right)
{
    const uint8_t *planar_r = static_cast<const uint8_t *>(planar[0]);
    const uint8_t *planar_g = static_cast<const uint8_t *>(planar[1]);
    const uint8_t *planar_b = static_cast<const uint8_t *>(planar[2]);
    uint8_t *packed_bgr = static_cast<uint8_t *>(bgr);
    unsigned step = bit_depth / 8;
    if(step == 1) {
        ::memcpy(&packed_bgr[left], &planar_r[left], right-left);
        return;
    }

    for (unsigned j = left; j < right; ++j) {
        uint8_t r, g, b;

        r = planar_r[j];
        g = planar_g[j];
        b = planar_b[j];

        packed_bgr[j * step + 0] = b;
        packed_bgr[j * step + 1] = g;
        packed_bgr[j * step + 2] = r;
    }
}

static int unpack_image(void *user, unsigned i, unsigned left, unsigned right)
{
    const Callback *cb = static_cast<Callback *>(user);
    const void *img = cb->img->bits() + i * cb->img->bytesPerLine();
    const zimgxx::zimage_buffer &buf = *cb->buffer;
    void *buf_data[3];

    for (unsigned p = 0; p < 3; ++p) {
        buf_data[p] = static_cast<char *>(buf.line_at(i, p));
    }

    unpack_bgr(img, buf_data, cb->img->depth(), left, right);
    return 0;
}

static int pack_image(void *user, unsigned i, unsigned left, unsigned right)
{
    const Callback *cb = static_cast<Callback *>(user);
    void *img = const_cast<uchar*>(cb->img->bits()) + i * cb->img->bytesPerLine();
    const zimgxx::zimage_buffer &buf = *cb->buffer;
    const void *buf_data[3];

    for (unsigned p = 0; p < 3; ++p) {
        buf_data[p] = static_cast<const char *>(buf.line_at(i, p));
    }

    pack_bgr(buf_data, img, cb->img->depth(), left, right);
    return 0;
}

QZimg::QZimg(QObject *parent)
    : QObject(parent)
    , d(new QZimgPrivate)
{

}

QZimg::~QZimg()
{
    delete d;
}

static void releaseBuff(void* pt)
{
    aligned_free(pt);
}

QImage QZimg::createPackedImage(QSize size, QImage::Format fmt, int stridePack)
{
    return QImage(size, fmt);
}

QImage QZimg::toPackedImage(const QImage &src, int stridePack)
{
    switch(src.format()) {
    case QImage::Format_Indexed8:
        return src.convertToFormat(QImage::Format_ARGB32);
    case QImage::Format_ARGB32_Premultiplied:
    case QImage::Format_ARGB8565_Premultiplied:
    case QImage::Format_ARGB6666_Premultiplied:
    case QImage::Format_ARGB8555_Premultiplied:
    case QImage::Format_ARGB4444_Premultiplied:
    case QImage::Format_RGBA8888:
    case QImage::Format_RGBA8888_Premultiplied:
    case QImage::Format_A2BGR30_Premultiplied:
    case QImage::Format_A2RGB30_Premultiplied:
        return src.convertToFormat(QImage::Format_ARGB32);
    case QImage::Format_RGB555:
    case QImage::Format_RGB666:
    case QImage::Format_RGB30:
    case QImage::Format_BGR30:
    case QImage::Format_RGBX8888:
    case QImage::Format_RGB888:
    case QImage::Format_RGB444:
        return src.convertToFormat(QImage::Format_RGB32);
    }
    return src;
}

QImage QZimg::scaled(const QImage &src, const QSize &newsize, Qt::AspectRatioMode aspectMode, QZimg::FilterMode mode)
{
    QImage img = toPackedImage(src);
    zimgxx::zimage_format in_format;
    in_format.width = img.width();
    in_format.height = img.height();

    in_format.subsample_w = 0;
    in_format.subsample_h = 0;

    in_format.pixel_type = ZIMG_PIXEL_BYTE;
    in_format.color_family = img.format() == QImage::Format_Grayscale8
            ? ZIMG_COLOR_GREY
            : ZIMG_COLOR_RGB;
    in_format.matrix_coefficients = in_format.color_family == ZIMG_COLOR_RGB ? ZIMG_MATRIX_RGB : ZIMG_MATRIX_UNSPECIFIED;
    in_format.pixel_range = ZIMG_RANGE_FULL;

    zimgxx::zimage_format out_format = in_format;
    out_format.height = newsize.height();
    out_format.width = aspectMode == Qt::IgnoreAspectRatio
            ? newsize.width()
            : in_format.width*out_format.height/in_format.height;
    QImage oimg = createPackedImage(QSize(out_format.width, out_format.height), img.format());

    try {
        //        zimgxx::zfilter_graph_builder_params params;
        //        zimgxx::FilterGraph graph{ zimgxx::FilterGraph::build(ifmt, ofmt, &params) };
        zimgxx::FilterGraph graph{ zimgxx::FilterGraph::build(in_format, out_format) };
        unsigned input_buffering = graph.get_input_buffering();
        unsigned output_buffering = graph.get_output_buffering();
        size_t tmp_size = graph.get_tmp_size();

//        qDebug() << "input buffering:  " << input_buffering;
//        qDebug() << "output buffering: " << output_buffering;
//        qDebug() << "heap usage: " << tmp_size;
//        qDebug() << "img: " << img;
//        qDebug() << "oimg: " << oimg;
        uchar* obuff = oimg.bits();

        auto in_buf = allocate_buffer(in_format, input_buffering);
        auto out_buf = allocate_buffer(out_format, output_buffering);
        auto tmp_buf = allocate_buffer(tmp_size);


        Callback unpack_cb_data = { &in_buf.first, &img };
        Callback pack_cb_data = { &out_buf.first, &oimg };

//        qDebug() << "resize begin: ";
//        QElapsedTimer et_qt;et_qt.start();
        graph.process(in_buf.first.as_const(), out_buf.first, tmp_buf.get(),
                      unpack_image, &unpack_cb_data, pack_image, &pack_cb_data);

//        qint64 t_qt = et_qt.elapsed();
//        qDebug() << "resize end. time: " << t_qt;
    } catch(zimgxx::zerror e) {
        qDebug() << e.code;
        qDebug() << e.msg;
    }

    return oimg;
}
