#include <QtGui>
#include <memory>

#include "qzimg.h"
#include "api/zimg++.hpp"
#include "aligned_malloc.h"

class QZimgPrivate
{

};
struct Callback {
    const zimgxx::zimage_buffer *rgb_buf;
    const zimgxx::zimage_buffer *alpha_buf;
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

void unpack_bgra_straight(const void *bgra, void * const planar[4], unsigned left, unsigned right)
{
    const uint8_t *packed_bgra = static_cast<const uint8_t *>(bgra);
    uint16_t *planar_r = static_cast<uint16_t *>(planar[0]);
    uint16_t *planar_g = static_cast<uint16_t *>(planar[1]);
    uint16_t *planar_b = static_cast<uint16_t *>(planar[2]);
    uint8_t *planar_a = static_cast<uint8_t *>(planar[3]);

    for (unsigned j = left; j < right; ++j) {
        uint16_t r, g, b;
        uint8_t a;

        r = packed_bgra[j * 4 + 2];
        g = packed_bgra[j * 4 + 1];
        b = packed_bgra[j * 4 + 0];
        a = packed_bgra[j * 4 + 3];

        r = static_cast<uint16_t>(static_cast<uint32_t>(r) * a * 65535 / (255 * 255));
        g = static_cast<uint16_t>(static_cast<uint32_t>(g) * a * 65535 / (255 * 255));
        b = static_cast<uint16_t>(static_cast<uint32_t>(b) * a * 65535 / (255 * 255));

        planar_r[j] = r;
        planar_g[j] = g;
        planar_b[j] = b;
        planar_a[j] = a;
    }
}

void pack_bgra_straight(const void * const planar[4], void *bgra, unsigned left, unsigned right)
{
    const uint16_t *planar_r = static_cast<const uint16_t *>(planar[0]);
    const uint16_t *planar_g = static_cast<const uint16_t *>(planar[1]);
    const uint16_t *planar_b = static_cast<const uint16_t *>(planar[2]);
    const uint8_t *planar_a = static_cast<const uint8_t *>(planar[3]);
    uint8_t *packed_bgra = static_cast<uint8_t *>(bgra);

    for (unsigned j = left; j < right; ++j) {
        uint16_t r, g, b;
        uint8_t a, a_eff;

        r = planar_r[j];
        g = planar_g[j];
        b = planar_b[j];
        a = planar_a[j];

        a_eff = std::max(a, static_cast<uint8_t>(1));

        r = static_cast<uint16_t>(static_cast<uint32_t>(r) * 255 * 255 / (static_cast<uint32_t>(65535) * a_eff));
        g = static_cast<uint16_t>(static_cast<uint32_t>(g) * 255 * 255 / (static_cast<uint32_t>(65535) * a_eff));
        b = static_cast<uint16_t>(static_cast<uint32_t>(b) * 255 * 255 / (static_cast<uint32_t>(65535) * a_eff));

        packed_bgra[j * 4 + 0] = static_cast<uint8_t>(b);
        packed_bgra[j * 4 + 1] = static_cast<uint8_t>(g);
        packed_bgra[j * 4 + 2] = static_cast<uint8_t>(r);
        packed_bgra[j * 4 + 3] = a;
    }
}


static int unpack_bgra(void *user, unsigned i, unsigned left, unsigned right)
{
    const Callback *cb = static_cast<Callback *>(user);
    const zimgxx::zimage_buffer &rgb_buf = *cb->rgb_buf;
    const zimgxx::zimage_buffer &alpha_buf = *cb->alpha_buf;
    const void *packed_data = cb->img->bits() + i * cb->img->bytesPerLine();
    void *planar_data[4];

    for (unsigned p = 0; p < 3; ++p) {
        planar_data[p] = static_cast<char *>(rgb_buf.line_at(i, p));
    }
    planar_data[3] = static_cast<char *>(alpha_buf.line_at(i));

//    if (cb->premultiply)
//        unpack_bgra_premul(packed_data, planar_data, left, right);
//    else
        unpack_bgra_straight(packed_data, planar_data, left, right);

    return 0;
}

static int pack_bgra(void *user, unsigned i, unsigned left, unsigned right)
{
    const Callback * cb = static_cast<Callback *>(user);
    const zimgxx::zimage_buffer &rgb_buf = *cb->rgb_buf;
    const zimgxx::zimage_buffer &alpha_buf = *cb->alpha_buf;
    void *packed_data = const_cast<uchar*>(cb->img->bits()) + i * cb->img->bytesPerLine();
    const void *planar_data[4];

    for (unsigned p = 0; p < 3; ++p) {
        planar_data[p] = static_cast<const char *>(rgb_buf.line_at(i, p));
    }
    planar_data[3] = static_cast<const char *>(alpha_buf.line_at(i));

//    if (cb->premultiply)
//        pack_bgra_premul(planar_data, packed_data, left, right);
//    else
        pack_bgra_straight(planar_data, packed_data, left, right);

    return 0;
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
    const zimgxx::zimage_buffer &buf = *cb->rgb_buf;
    void *buf_data[4];

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
    const zimgxx::zimage_buffer &buf = *cb->rgb_buf;
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
    QImage converted;
    // QImage processing sometimes fails
    for(int count = 1; ; count++) {
        switch(src.format()) {
        case QImage::Format_RGBA8888:
        case QImage::Format_RGB32:
            return src;
        case QImage::Format_RGB555:
        case QImage::Format_RGB666:
        case QImage::Format_RGB888:
        case QImage::Format_RGB444:
#if QT_VERSION_MAJOR >= 5
        case QImage::Format_RGB30:
        case QImage::Format_BGR30:
        case QImage::Format_RGBX8888:
        case QImage::Format_Grayscale8:
#endif
            converted = src.convertToFormat(QImage::Format_RGB32);
            break;
//        case QImage::Format_Indexed8:
//            converted = src.convertToFormat(QImage::Format_ARGB32);
//            break;
//        case QImage::Format_ARGB32_Premultiplied:
//        case QImage::Format_ARGB8565_Premultiplied:
//        case QImage::Format_ARGB6666_Premultiplied:
//        case QImage::Format_ARGB8555_Premultiplied:
//        case QImage::Format_ARGB4444_Premultiplied:
//        case QImage::Format_RGBA8888:
//        case QImage::Format_RGBA8888_Premultiplied:
//        case QImage::Format_A2BGR30_Premultiplied:
//        case QImage::Format_A2RGB30_Premultiplied:
        default:
            converted = src.convertToFormat(QImage::Format_RGBA8888);
            break;
        }
        if(!converted.isNull()) break;
        if(count >= 100) return QImage();
#if QT_VERSION_MAJOR >= 5
        QThread::currentThread()->usleep(40000);
#else
        QThread::currentThread()->wait(40);
#endif

    }
    return converted;
}

QImage scaledRGB(QImage img, zimgxx::zimage_format in_format, zimgxx::zimage_format out_format)
{
    QImage oimg;
    // QImage processing sometimes fails
    for(int count = 1; ; count++) {
        oimg = QImage(QSize(out_format.width, out_format.height), img.format());
        if(!oimg.isNull()) break;
        if(count >= 100) return QImage();
#if QT_VERSION_MAJOR >= 5
        QThread::currentThread()->usleep(40000);
#else
        QThread::currentThread()->wait(40);
#endif
    }
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


        Callback unpack_cb_data = { &in_buf.first, nullptr, &img };
        Callback pack_cb_data = { &out_buf.first, nullptr, &oimg };

//        qDebug() << "resize begin: ";
        QElapsedTimer et_qt;et_qt.start();
        graph.process(in_buf.first.as_const(), out_buf.first, tmp_buf.get(),
                      unpack_image, &unpack_cb_data, pack_image, &pack_cb_data);

        qint64 t_qt = et_qt.elapsed();
//        qDebug() << "resize end. time: " << t_qt;
    } catch(zimgxx::zerror e) {
        qDebug() << e.code;
        qDebug() << e.msg;
    }
    return oimg;

}

QImage scaledARGB(QImage img, zimgxx::zimage_format in_format, zimgxx::zimage_format out_format,
                  zimgxx::zimage_format in_format_alpha, zimgxx::zimage_format out_format_alpha)
{
    QImage oimg;
    // QImage processing sometimes fails
    for(int count = 1; ; count++) {
        oimg = QImage(QSize(out_format.width, out_format.height), img.format());
        if(!oimg.isNull()) break;
        if(count >= 100) return QImage();
#if QT_VERSION_MAJOR >= 5
        QThread::currentThread()->usleep(40000);
#else
        QThread::currentThread()->wait(40);
#endif
    }
    try {
        //        zimgxx::zfilter_graph_builder_params params;
        //        zimgxx::FilterGraph graph{ zimgxx::FilterGraph::build(ifmt, ofmt, &params) };
        zimgxx::FilterGraph graph{ zimgxx::FilterGraph::build(in_format, out_format) };
        zimgxx::FilterGraph graph_alpha{ zimgxx::FilterGraph::build(in_format_alpha, out_format_alpha) };

        unsigned input_buffering = std::max(graph.get_input_buffering(), graph_alpha.get_input_buffering());
        unsigned output_buffering = std::max(graph.get_output_buffering(), graph_alpha.get_output_buffering());
        size_t tmp_size = std::max(graph.get_tmp_size(), graph_alpha.get_tmp_size());

//        qDebug() << "input buffering:  " << input_buffering;
//        qDebug() << "output buffering: " << output_buffering;
//        qDebug() << "heap usage: " << tmp_size;
//        qDebug() << "img: " << img;
//        qDebug() << "oimg: " << oimg;
        uchar* obuff = oimg.bits();

        auto in_rgb_buf = allocate_buffer(in_format, input_buffering);
        auto in_alpha_plane_buf = allocate_buffer(in_format_alpha, ZIMG_BUFFER_MAX);

        auto out_rgb_plane_buf = allocate_buffer(out_format, ZIMG_BUFFER_MAX);
        auto out_alpha_buf = allocate_buffer(out_format_alpha, output_buffering);

        auto tmp_buf = allocate_buffer(tmp_size);


        Callback unpack_cb_data = { &in_rgb_buf.first, &in_alpha_plane_buf.first, &img };
        Callback pack_cb_data = { &out_rgb_plane_buf.first, &out_alpha_buf.first, &oimg };

//        qDebug() << "resize begin: ";
        QElapsedTimer et_qt;et_qt.start();
//        graph.process(in_buf.first.as_const(), out_buf.first, tmp_buf.get(),
//                      unpack_image, &unpack_cb_data, pack_image, &pack_cb_data);
        graph.process(in_rgb_buf.first.as_const(), out_rgb_plane_buf.first, tmp_buf.get(), unpack_bgra, &unpack_cb_data, nullptr, nullptr);
        graph_alpha.process(in_alpha_plane_buf.first.as_const(), out_alpha_buf.first, tmp_buf.get(), nullptr, nullptr, pack_bgra, &pack_cb_data);

        qint64 t_qt = et_qt.elapsed();
//        qDebug() << "resize end. time: " << t_qt;
    } catch(zimgxx::zerror e) {
        qDebug() << e.code;
        qDebug() << e.msg;
    }
    return oimg;

}

QImage QZimg::scaled(const QImage &src, const QSize &newsize, Qt::AspectRatioMode aspectMode, QZimg::FilterMode mode)
{
    QImage img = toPackedImage(src);
    zimgxx::zimage_format in_format;
    in_format.width = img.width();
    in_format.height = img.height();

    in_format.subsample_w = 0;
    in_format.subsample_h = 0;

    in_format.pixel_type = img.format() == QImage::Format_RGB32 ? ZIMG_PIXEL_BYTE : ZIMG_PIXEL_WORD;
    in_format.color_family = ZIMG_COLOR_RGB;
//    in_format.matrix_coefficients = ZIMG_MATRIX_RGB;
    in_format.pixel_range = ZIMG_RANGE_FULL;

    zimgxx::zimage_format out_format = in_format;
    out_format.height = newsize.height();
    out_format.width = aspectMode == Qt::IgnoreAspectRatio
            ? newsize.width()
            : in_format.width*out_format.height/in_format.height;
    QImage oimg;
    if(img.format() == QImage::Format_RGB32)
        oimg = scaledRGB(img, in_format, out_format);
    else {
        zimgxx::zimage_format in_format_alpha;
        in_format_alpha.width = img.width();
        in_format_alpha.height = img.height();
        in_format_alpha.pixel_type = ZIMG_PIXEL_BYTE;
//        in_format.matrix_coefficients = ZIMG_MATRIX_UNSPECIFIED;

        in_format_alpha.color_family = ZIMG_COLOR_GREY;
        in_format_alpha.pixel_range = ZIMG_RANGE_FULL;

        zimgxx::zimage_format out_format_alpha = in_format_alpha;
        out_format_alpha.height = out_format.height;
        out_format_alpha.width = out_format.width;

        oimg = scaledARGB(img, in_format, out_format, in_format_alpha, out_format_alpha);
    }

    return oimg;
}
