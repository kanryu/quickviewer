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
    std::vector<int> sizes(3);
    sizes[0] = src.width();
    sizes[1] = src.height();
    sizes[2] = src.depth()/8;

    Buffer<uint8_t> input(const_cast<uint8_t*>(src.bits()), sizes);
    QImage dest(src.size(), src.format());
    Buffer<uint8_t> output(dest.bits(), sizes);

    if(src.format() == QImage::Format_RGBA8888) {
        luminor_rgba(input.raw_buffer(), brightness, contrast, gamma, output.raw_buffer());
    } else {
        luminor(input.raw_buffer(), brightness, contrast, gamma, output.raw_buffer());
    }
    return dest;
}
