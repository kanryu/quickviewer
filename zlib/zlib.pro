#-------------------------------------------------
#
# Project created by QtCreator 2014-02-08T18:57:16
#
#-------------------------------------------------

QT       -= core
#QT       += core gui

TARGET = zlib
TEMPLATE = lib
CONFIG += warn_off

DEFINES += ASMV ASMINF

CONFIG += staticlib
#DEFINES += ZLIB_DLL


CONFIG(debug,debug|release) {
    BUILD = debug
} else {
    BUILD = release
}


greaterThan(QT_MAJOR_VERSION, 4) {
    TARGET_ARCH=$${QT_ARCH}
} else {
    TARGET_ARCH=$${QMAKE_HOST.arch}
}
contains(TARGET_ARCH, x86_64) {
    TARGET_ARCH = x64
} else {
    TARGET_ARCH = x86
}

INCLUDEPATH += $$PWD/zlib


SOURCES += \
    $$PWD/zlib/adler32.c \
    $$PWD/zlib/compress.c \
    $$PWD/zlib/crc32.c \
    $$PWD/zlib/deflate.c \
    $$PWD/zlib/gzclose.c \
    $$PWD/zlib/gzlib.c \
    $$PWD/zlib/gzread.c \
    $$PWD/zlib/gzwrite.c \
    $$PWD/zlib/infback.c \
    $$PWD/zlib/inflate.c \
    $$PWD/zlib/inftrees.c \
    $$PWD/zlib/trees.c \
    $$PWD/zlib/uncompr.c \
    $$PWD/zlib/zutil.c \

#    $$PWD/zlib/inffast.c \

HEADERS += \
    $$PWD/zlib/crc32.h \
    $$PWD/zlib/deflate.h \
    $$PWD/zlib/gzguts.h \
    $$PWD/zlib/inffast.h \
    $$PWD/zlib/inffixed.h \
    $$PWD/zlib/inflate.h \
    $$PWD/zlib/inftrees.h \
    $$PWD/zlib/trees.h \
    $$PWD/zlib/zconf.h \
    $$PWD/zlib/zlib.h \
    $$PWD/zlib/zutil.h \

DESTDIR = ../lib

win32-msvc* {
    QMAKE_CFLAGS += -MD -W3 -O2 -Oy- -Zi
    equals(TARGET_ARCH, x64) {
        message("zlib: Host is x64")
        ARCHITECTURE = x64
        SOURCES += $$PWD/zlib/contrib/masmx64/inffas8664.c
        NASM = ml64.exe /c /Zi
        NASM_SOURCES = \
            $$PWD/zlib/contrib/masmx64/gvmat64.asm \
            $$PWD/zlib/contrib/masmx64/inffasx64.asm \

    }
    equals(TARGET_ARCH, x86) {
        message("zlib: Host is x86")
        message("x86 asms of 1.2.11 has a bug. to see https://github.com/madler/zlib/issues/200")
        ARCHITECTURE = x86
    #    SOURCES += $$PWD/zlib/contrib/masmx86/inffas8664.c
        NASM = ml.exe /c /Zi
#        NASM_SOURCES = \
#            $$PWD/zlib/contrib/masmx86/match686.asm \
#            $$PWD/zlib/contrib/masmx86/inffas32.asm \

        DEFINES -= ASMV ASMINF
        SOURCES += \
            $$PWD/zlib/inffast.c \
    }
    OTHER_FILES += $$NASM_SOURCES
    nasm_build.name  = ${QMAKE_FILE_BASE}
    nasm_build.target = ${QMAKE_FILE_OUT}
    nasm_build.output = $${BUILD}/${QMAKE_FILE_BASE}.obj
    nasm_build.variable_out = OBJECTS
    nasm_build.CONFIG = verify
    #nasm_build.commands = $$NASM /F${QMAKE_FILE_BASE} ${QMAKE_FILE_IN}
    nasm_build.commands = $$NASM /Fo${QMAKE_FILE_OUT} ${QMAKE_FILE_IN}
    nasm_build.input = NASM_SOURCES
    QMAKE_EXTRA_COMPILERS += nasm_build
}

*g++* {
    message("for g++")
#    equals(TARGET_ARCH, x86) {
#        message("zlib: Host is g++ x86")
#        CPP_ASM_SORUCES += $$PWD/zlib/contrib/amd64/amd64-match.S
#    }
#    equals(TARGET_ARCH, x64) {
#        message("zlib: Host is g++ x64")
#        CPP_ASM_SORUCES += $$PWD/zlib/contrib/asm686/match.S
#    }
#    OTHER_FILES += $$CPP_ASM_SORUCES
#    cpp_asm.name  = ${QMAKE_FILE_BASE}
#    cpp_asm.target = ${QMAKE_FILE_OUT}
#    cpp_asm.output = $${BUILD}/${QMAKE_FILE_BASE}.s
#    cpp_asm.variable_out = OBJECTS
#    cpp_asm.CONFIG = verify
#    cpp_asm.commands = $${QMAKE_CC} -E ${QMAKE_FILE_IN} > ${QMAKE_FILE_OUT}
#    cpp_asm.input = CPP_ASM_SORUCES
#    QMAKE_EXTRA_COMPILERS += cpp_asm
    DEFINES -= ASMV ASMINF
    SOURCES += \
        $$PWD/zlib/inffast.c \

}







