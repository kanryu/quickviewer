#-------------------------------------------------
#
# Project created by QtCreator 2014-02-08T18:57:16
#
#-------------------------------------------------

QT       += core gui

TARGET = fileloader
TEMPLATE = lib

win32-msvc* {
    CONFIG += staticlib
    QMAKE_CXXFLAGS += /wd4819
}

*g++* {
    QMAKE_LFLAGS += -Wl,-rpath,../lib
}

win32 {
    LIBS += -luser32 -ladvapi32 -lShlwapi
}
unix {
    DEFINES += _UNIX
}

SOURCES += \
    $$PWD/*.cpp \

HEADERS += \
    $$PWD/*.h \

INCLUDEPATH += ../Qt7z/Qt7z


DESTDIR = ../lib

DEFINES += UNRAR RARDLL
INCLUDEPATH += ../unrar

DEFINES += QUAZIP_STATIC
INCLUDEPATH += $$PWD/../quazip/quazip/quazip $$PWD/../zlib/zlib


LIBS += -L../lib -lquazip -lzlib -lunrar -lQt7z

