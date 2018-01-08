#include <vector>
#include "qluminor.h"
#include "luminor.h"
#include "luminor_rgba.h"
#include "HalideBuffer.h"

using namespace Halide::Runtime;

template<typename ElemType>
ElemType read_big_endian(const uint8_t *src);

template<>
inline uint8_t read_big_endian(const uint8_t *src) {
    return *src;
}

template<>
inline uint16_t read_big_endian(const uint8_t *src) {
    return (((uint16_t) src[0]) << 8) | ((uint16_t) src[1]);
}

template<typename ElemType>
void write_big_endian(const ElemType &src, uint8_t *dst);

template<>
inline void write_big_endian(const uint8_t &src, uint8_t *dst) {
    *dst = src;
}

template<>
inline void write_big_endian(const uint16_t &src, uint8_t *dst) {
    dst[0] = src >> 8;
    dst[1] = src & 0xff;
}

// Read a row of ElemTypes from a byte buffer and copy them into a specific image row.
// Multibyte elements are assumed to be big-endian.
template<typename ElemType, typename ImageType>
void read_big_endian_row(const uint8_t *src, int y, ImageType *im) {
    auto im_typed = im->template as<ElemType>();
    const int xmin = im_typed.dim(0).min();
    const int xmax = im_typed.dim(0).max();
    if (im_typed.dimensions() > 2) {
        const int cmin = im_typed.dim(2).min();
        const int cmax = im_typed.dim(2).max();
        for (int x = xmin; x <= xmax; x++) {
            for (int c = cmin; c <= cmax; c++) {
                im_typed(x, y, c+cmin) = read_big_endian<ElemType>(src);
                src += sizeof(ElemType);
            }
        }
    } else {
        for (int x = xmin; x <= xmax; x++) {
            im_typed(x, y) = read_big_endian<ElemType>(src);
            src += sizeof(ElemType);
        }
    }
}

// Copy a row from an image into a byte buffer.
// Multibyte elements are written in big-endian layout.
template<typename ElemType, typename ImageType>
void write_big_endian_row(const ImageType &im, int y, uint8_t *dst) {
    auto im_typed = im.template as<ElemType>();
    const int xmin = im_typed.dim(0).min();
    const int xmax = im_typed.dim(0).max();
    if (im_typed.dimensions() > 2) {
        const int cmin = im_typed.dim(2).min();
        const int cmax = im_typed.dim(2).max();
        for (int x = xmin; x <= xmax; x++) {
            for (int c = cmin; c <= cmax; c++) {
                write_big_endian<ElemType>(im_typed(x, y, c), dst);
                dst += sizeof(ElemType);
            }
        }
    } else {
        for (int x = xmin; x <= xmax; x++) {
            write_big_endian<ElemType>(im_typed(x, y), dst);
            dst += sizeof(ElemType);
        }
    }
}

QLuminor::QLuminor(QObject *parent) : QObject(parent)
{

}

QImage QLuminor::toLuminor(const QImage &src, float brightness, float contrast, float gamma)
{
    if(src.format() == QImage::Format_ARGB32 || src.format() == QImage::Format_RGBA8888) {
        return toLuminorRGBA(src, brightness, contrast, gamma);
    }
    std::vector<int> sizes(3);
    sizes[0] = src.width();
    sizes[1] = src.height();
    sizes[2] = src.depth()/8;
    qDebug() << src.width() << src.height() << (src.depth()/8);

    Buffer<uint8_t> input(const_cast<uint8_t*>(src.bits()), sizes);
    QImage dest(src.size(), src.format());
    Buffer<uint8_t> output(dest.bits(), sizes);

    luminor(input, brightness, contrast, gamma, output);
    return dest;
}

QImage QLuminor::toLuminorRGBA(const QImage &src, float brightness, float contrast, float gamma)
{
    QImage img2(src.size(),src.format());
    std::vector<int> sizes(3);
    sizes[0] = src.width();
    sizes[1] = src.height();
    sizes[2] = src.depth()/8;
    Buffer<uint8_t> buff1(img2.bits(), sizes);
    Buffer<uint8_t> buff2(src.width(), src.height(), src.depth()/8);

    // Halide 's Buffer needs to be rearranged because ordinary bitmap and byte order are different.
    for(int y=0; y<src.height(); y++) {
        read_big_endian_row<uint8_t, Buffer<uint8_t>>(src.bits()+y*src.bytesPerLine(), y, &buff1);
    }

    int result = 0;
    result = luminor_rgba(buff1, brightness, contrast, gamma, buff2);

    for(int y=0; y<img2.height(); y++) {
        write_big_endian_row<uint8_t, Buffer<uint8_t>>(buff2, y, img2.bits()+y*img2.bytesPerLine());
    }
    return img2;
}
