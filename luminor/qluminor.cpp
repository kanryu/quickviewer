#include <vector>
#include "qluminor.h"
#include "luminor.h"
#include "luminor_rgba.h"
#include "HalideBuffer.h"

using namespace Halide::Runtime;

QLuminor::QLuminor(QObject *parent) : QObject(parent)
{

}

QImage QLuminor::toLuminor(const QImage &src, float brightness, float contrast, float gamma)
{
    if(src.format() == QImage::Format_ARGB32 || src.format() == QImage::Format_RGBA8888)
        return toLuminorRGBA(src, brightness, contrast, gamma);

    std::vector<int> sizes(3);
    sizes[0] = src.width();
    sizes[1] = src.height();
    sizes[2] = src.depth()/8;
    Buffer<uint8_t> input(const_cast<uint8_t*>(src.bits()), sizes);
    QImage dest(src.size(),src.format());
    Buffer<uint8_t> output(const_cast<uint8_t*>(dest.bits()), sizes);

    int result = 0;
        result = luminor(input, brightness, contrast, gamma, output);

    return dest;
}

QImage QLuminor::toLuminorRGBA(const QImage &src, float brightness, float contrast, float gamma)
{
    QImage dest(src.size(),src.format());
    auto input = Buffer<uint8_t>::make_interleaved(const_cast<uint8_t*>(src.bits()), src.width(), src.height(), src.depth()/8);
    auto output = Buffer<uint8_t>::make_interleaved(const_cast<uint8_t*>(dest.bits()), dest.width(), dest.height(), dest.depth()/8);

    int result = 0;
        result = luminor_rgba(input, brightness, contrast, gamma, output);
    return dest;
}

