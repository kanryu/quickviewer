#-------------------------------------------------
#
# Project created by QtCreator 2014-02-08T18:57:16
#
#-------------------------------------------------

#QT       -= core
QT       += core gui

TARGET = zimg
TEMPLATE = lib
CONFIG += staticlib
CONFIG += warn_off
CONFIG += c++11

DEFINES += ZIMG_X86

win32-msvc* {
    QMAKE_CXXFLAGS += /wd4819 /wd4996
    !CONFIG(debug, debug|release) {
        QMAKE_CXXFLAGS += /GL /W3 /Gy /Gm- /Gd /Oi
    }
}

*g++* {
    QMAKE_CXXFLAGS += -O2 -MD -MP -std=c++11
    !CONFIG(debug, debug|release) {
    }
}

macos {
    QMAKE_CXXFLAGS += -O2 -MD -MP -std=c++11
    !CONFIG(debug, debug|release) {
    }
}

SOURCES += \
    $$PWD/zimg/src/zimg/api/zimg.cpp \
    $$PWD/zimg/src/zimg/colorspace/colorspace.cpp \
    $$PWD/zimg/src/zimg/colorspace/colorspace_param.cpp \
    $$PWD/zimg/src/zimg/colorspace/gamma.cpp \
    $$PWD/zimg/src/zimg/colorspace/graph.cpp \
    $$PWD/zimg/src/zimg/colorspace/matrix3.cpp \
    $$PWD/zimg/src/zimg/colorspace/operation.cpp \
    $$PWD/zimg/src/zimg/colorspace/operation_impl.cpp \
    $$PWD/zimg/src/zimg/colorspace/operation_impl_x86.cpp \
    $$PWD/zimg/src/zimg/common/cpuinfo.cpp \
    $$PWD/zimg/src/zimg/common/libm_wrapper.cpp \
    $$PWD/zimg/src/zimg/common/matrix.cpp \
    $$PWD/zimg/src/zimg/common/x86util.cpp \
    $$PWD/zimg/src/zimg/depth/depth.cpp \
    $$PWD/zimg/src/zimg/depth/depth_convert.cpp \
    $$PWD/zimg/src/zimg/depth/depth_convert_x86.cpp \
    $$PWD/zimg/src/zimg/depth/dither.cpp \
    $$PWD/zimg/src/zimg/depth/dither_x86.cpp \
    $$PWD/zimg/src/zimg/depth/quantize.cpp \
    $$PWD/zimg/src/zimg/graph/basic_filter.cpp \
    $$PWD/zimg/src/zimg/graph/filtergraph.cpp \
    $$PWD/zimg/src/zimg/graph/graphbuilder.cpp \
    $$PWD/zimg/src/zimg/resize/filter.cpp \
    $$PWD/zimg/src/zimg/resize/resize.cpp \
    $$PWD/zimg/src/zimg/resize/resize_impl.cpp \
    $$PWD/zimg/src/zimg/resize/resize_impl_x86.cpp \
    $$PWD/zimg/src/zimg/unresize/bilinear.cpp \
    $$PWD/zimg/src/zimg/unresize/unresize.cpp \
    $$PWD/zimg/src/zimg/unresize/unresize_impl.cpp \
    qzimg.cpp

HEADERS += \
    $$PWD/zimg/src/zimg/api/zimg.h \
    $$PWD/zimg/src/zimg/api/zimg++.hpp \
    $$PWD/zimg/src/zimg/colorspace/colorspace.h \
    $$PWD/zimg/src/zimg/colorspace/colorspace_param.h \
    $$PWD/zimg/src/zimg/colorspace/gamma.h \
    $$PWD/zimg/src/zimg/colorspace/graph.h \
    $$PWD/zimg/src/zimg/colorspace/matrix3.h \
    $$PWD/zimg/src/zimg/colorspace/operation.h \
    $$PWD/zimg/src/zimg/colorspace/operation_impl.h \
    $$PWD/zimg/src/zimg/colorspace/operation_impl_x86.h \
    $$PWD/zimg/src/zimg/common/align.h \
    $$PWD/zimg/src/zimg/common/alloc.h \
    $$PWD/zimg/src/zimg/common/builder.h \
    $$PWD/zimg/src/zimg/common/ccdep.h \
    $$PWD/zimg/src/zimg/common/checked_int.h \
    $$PWD/zimg/src/zimg/common/cpuinfo.h \
    $$PWD/zimg/src/zimg/common/except.h \
    $$PWD/zimg/src/zimg/common/libm_wrapper.h \
    $$PWD/zimg/src/zimg/common/make_unique.h \
    $$PWD/zimg/src/zimg/common/matrix.h \
    $$PWD/zimg/src/zimg/common/pixel.h \
    $$PWD/zimg/src/zimg/common/static_map.h \
    $$PWD/zimg/src/zimg/common/x86util.h \
    $$PWD/zimg/src/zimg/common/zassert.h \
    $$PWD/zimg/src/zimg/depth/depth.h \
    $$PWD/zimg/src/zimg/depth/depth_convert.h \
    $$PWD/zimg/src/zimg/depth/depth_convert_x86.h \
    $$PWD/zimg/src/zimg/depth/dither.h \
    $$PWD/zimg/src/zimg/depth/dither_x86.h \
    $$PWD/zimg/src/zimg/depth/f16c_x86.h \
    $$PWD/zimg/src/zimg/depth/hexfloat.h \
    $$PWD/zimg/src/zimg/depth/quantize.h \
    $$PWD/zimg/src/zimg/graph/basic_filter.h \
    $$PWD/zimg/src/zimg/graph/filtergraph.h \
    $$PWD/zimg/src/zimg/graph/graphbuilder.h \
    $$PWD/zimg/src/zimg/graph/image_buffer.h \
    $$PWD/zimg/src/zimg/graph/image_filter.h \
    $$PWD/zimg/src/zimg/resize/filter.h \
    $$PWD/zimg/src/zimg/resize/resize.h \
    $$PWD/zimg/src/zimg/resize/resize_impl.h \
    $$PWD/zimg/src/zimg/resize/resize_impl_x86.h \
    $$PWD/zimg/src/zimg/unresize/bilinear.h \
    $$PWD/zimg/src/zimg/unresize/unresize.h \
    $$PWD/zimg/src/zimg/unresize/unresize_impl.h \
    $$PWD/zimg/src/testcommon/aligned_malloc.h \
    qzimg.h

INCLUDEPATH += \
    $$PWD/zimg/src/zimg  $$PWD/zimg/src/testcommon

DESTDIR = ../lib

# CPU specialized codes

win32-msvc* {
    SOURCES += \
        $$PWD/zimg/src/zimg/colorspace/operation_impl_sse.cpp \
        $$PWD/zimg/src/zimg/resize/resize_impl_sse.cpp \

    SOURCES += \
        $$PWD/zimg/src/zimg/depth/dither_sse2.cpp \
        $$PWD/zimg/src/zimg/colorspace/operation_impl_sse2.cpp \
        $$PWD/zimg/src/zimg/depth/f16c_sse2.cpp \
        $$PWD/zimg/src/zimg/resize/resize_impl_sse2.cpp \
        $$PWD/zimg/src/zimg/depth/depth_convert_sse2.cpp \
        $$PWD/zimg/src/zimg/depth/error_diffusion_sse2.cpp \

    SOURCES += \
        $$PWD/zimg/src/zimg/resize/resize_impl_avx.cpp \
        $$PWD/zimg/src/zimg/colorspace/operation_impl_avx.cpp \
        $$PWD/zimg/src/zimg/depth/f16c_ivb.cpp \

    SOURCES += \
        $$PWD/zimg/src/zimg/colorspace/operation_impl_avx2.cpp \
        $$PWD/zimg/src/zimg/depth/depth_convert_avx2.cpp \
        $$PWD/zimg/src/zimg/depth/dither_avx2.cpp \
        $$PWD/zimg/src/zimg/depth/error_diffusion_avx2.cpp \
        $$PWD/zimg/src/zimg/resize/resize_impl_avx2.cpp \

}

*g++* {
    SOURCES_SSE = \
            $$PWD/zimg/src/zimg/colorspace/operation_impl_sse.cpp \
            $$PWD/zimg/src/zimg/resize/resize_impl_sse.cpp \

    sse.name = sse
    sse.input = SOURCES_SSE
    sse.dependency_type = TYPE_C
    sse.variable_out = OBJECTS
    sse.output = ${QMAKE_VAR_OBJECTS_DIR}${QMAKE_FILE_IN_BASE}$${first(QMAKE_EXT_OBJ)}
    sse.commands = $${QMAKE_CXX} $(CXXFLAGS) -msse $(INCPATH) -c ${QMAKE_FILE_IN} -o ${QMAKE_FILE_OUT}

    SOURCES_SSE2 = \
            $$PWD/zimg/src/zimg/depth/dither_sse2.cpp \
            $$PWD/zimg/src/zimg/colorspace/operation_impl_sse2.cpp \
            $$PWD/zimg/src/zimg/depth/f16c_sse2.cpp \
            $$PWD/zimg/src/zimg/resize/resize_impl_sse2.cpp \
            $$PWD/zimg/src/zimg/depth/depth_convert_sse2.cpp \
            $$PWD/zimg/src/zimg/depth/error_diffusion_sse2.cpp \

    sse2.name = sse2
    sse2.input = SOURCES_SSE2
    sse2.dependency_type = TYPE_C
    sse2.variable_out = OBJECTS
    sse2.output = ${QMAKE_VAR_OBJECTS_DIR}${QMAKE_FILE_IN_BASE}$${first(QMAKE_EXT_OBJ)}
    sse2.commands = $${QMAKE_CXX} $(CXXFLAGS) -msse2 $(INCPATH) -c ${QMAKE_FILE_IN} -o ${QMAKE_FILE_OUT}

    SOURCES_AVX = \
            $$PWD/zimg/src/zimg/resize/resize_impl_avx.cpp \
            $$PWD/zimg/src/zimg/colorspace/operation_impl_avx.cpp \
            $$PWD/zimg/src/zimg/depth/f16c_ivb.cpp \

    avx.name = avx
    avx.input = SOURCES_AVX
    avx.dependency_type = TYPE_C
    avx.variable_out = OBJECTS
    avx.output = ${QMAKE_VAR_OBJECTS_DIR}${QMAKE_FILE_IN_BASE}$${first(QMAKE_EXT_OBJ)}
    avx.commands = $${QMAKE_CXX} $(CXXFLAGS) -mavx -mf16c $(INCPATH) -c ${QMAKE_FILE_IN} -o ${QMAKE_FILE_OUT}

    SOURCES_AVX2 = \
            $$PWD/zimg/src/zimg/colorspace/operation_impl_avx2.cpp \
            $$PWD/zimg/src/zimg/depth/depth_convert_avx2.cpp \
            $$PWD/zimg/src/zimg/depth/dither_avx2.cpp \
            $$PWD/zimg/src/zimg/depth/error_diffusion_avx2.cpp \
            $$PWD/zimg/src/zimg/resize/resize_impl_avx2.cpp \

    avx2.name = avx2
    avx2.input = SOURCES_AVX2
    avx2.dependency_type = TYPE_C
    avx2.variable_out = OBJECTS
    avx2.output = ${QMAKE_VAR_OBJECTS_DIR}${QMAKE_FILE_IN_BASE}$${first(QMAKE_EXT_OBJ)}
    avx2.commands = $${QMAKE_CXX} $(CXXFLAGS)  -mavx2 -mf16c -mfma $(INCPATH) -c ${QMAKE_FILE_IN} -o ${QMAKE_FILE_OUT}

    QMAKE_EXTRA_COMPILERS += sse sse2 avx avx2
}

macos {
    SOURCES_SSE = \
            $$PWD/zimg/src/zimg/colorspace/operation_impl_sse.cpp \
            $$PWD/zimg/src/zimg/resize/resize_impl_sse.cpp \

    sse.name = sse
    sse.input = SOURCES_SSE
    sse.dependency_type = TYPE_C
    sse.variable_out = OBJECTS
    sse.output = ${QMAKE_VAR_OBJECTS_DIR}${QMAKE_FILE_IN_BASE}$${first(QMAKE_EXT_OBJ)}
    sse.commands = $${QMAKE_CXX} $(CXXFLAGS) -msse $(INCPATH) -c ${QMAKE_FILE_IN} -o ${QMAKE_FILE_OUT}

    SOURCES_SSE2 = \
            $$PWD/zimg/src/zimg/depth/dither_sse2.cpp \
            $$PWD/zimg/src/zimg/colorspace/operation_impl_sse2.cpp \
            $$PWD/zimg/src/zimg/depth/f16c_sse2.cpp \
            $$PWD/zimg/src/zimg/resize/resize_impl_sse2.cpp \
            $$PWD/zimg/src/zimg/depth/depth_convert_sse2.cpp \
            $$PWD/zimg/src/zimg/depth/error_diffusion_sse2.cpp \

    sse2.name = sse2
    sse2.input = SOURCES_SSE2
    sse2.dependency_type = TYPE_C
    sse2.variable_out = OBJECTS
    sse2.output = ${QMAKE_VAR_OBJECTS_DIR}${QMAKE_FILE_IN_BASE}$${first(QMAKE_EXT_OBJ)}
    sse2.commands = $${QMAKE_CXX} $(CXXFLAGS) -msse2 $(INCPATH) -c ${QMAKE_FILE_IN} -o ${QMAKE_FILE_OUT}

    SOURCES_AVX = \
            $$PWD/zimg/src/zimg/resize/resize_impl_avx.cpp \
            $$PWD/zimg/src/zimg/colorspace/operation_impl_avx.cpp \
            $$PWD/zimg/src/zimg/depth/f16c_ivb.cpp \

    avx.name = avx
    avx.input = SOURCES_AVX
    avx.dependency_type = TYPE_C
    avx.variable_out = OBJECTS
    avx.output = ${QMAKE_VAR_OBJECTS_DIR}${QMAKE_FILE_IN_BASE}$${first(QMAKE_EXT_OBJ)}
    avx.commands = $${QMAKE_CXX} $(CXXFLAGS) -mavx -mf16c $(INCPATH) -c ${QMAKE_FILE_IN} -o ${QMAKE_FILE_OUT}

    SOURCES_AVX2 = \
            $$PWD/zimg/src/zimg/colorspace/operation_impl_avx2.cpp \
            $$PWD/zimg/src/zimg/depth/depth_convert_avx2.cpp \
            $$PWD/zimg/src/zimg/depth/dither_avx2.cpp \
            $$PWD/zimg/src/zimg/depth/error_diffusion_avx2.cpp \
            $$PWD/zimg/src/zimg/resize/resize_impl_avx2.cpp \

    avx2.name = avx2
    avx2.input = SOURCES_AVX2
    avx2.dependency_type = TYPE_C
    avx2.variable_out = OBJECTS
    avx2.output = ${QMAKE_VAR_OBJECTS_DIR}${QMAKE_FILE_IN_BASE}$${first(QMAKE_EXT_OBJ)}
    avx2.commands = $${QMAKE_CXX} $(CXXFLAGS)  -mavx2 -mf16c -mfma $(INCPATH) -c ${QMAKE_FILE_IN} -o ${QMAKE_FILE_OUT}

    QMAKE_EXTRA_COMPILERS += sse sse2 avx avx2
}
