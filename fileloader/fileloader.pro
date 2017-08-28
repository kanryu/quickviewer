#-------------------------------------------------
#
# Project created by QtCreator 2014-02-08T18:57:16
#
#-------------------------------------------------

QT       += core gui concurrent

TARGET = fileloader
TEMPLATE = lib

win32-msvc* {
    CONFIG += staticlib
    QMAKE_CXXFLAGS += /wd4819
}

*g++* {
    QMAKE_LFLAGS += -Wl,-rpath,../lib
    QMAKE_CXXFLAGS += -std=c++11
}

win32 {
    LIBS += -luser32 -ladvapi32 -lShlwapi
}
unix {
    DEFINES += _UNIX
}

SOURCES += \
    $$PWD/fileloader.cpp \
    $$PWD/fileloader7zarchive.cpp \
    $$PWD/fileloaderdirectory.cpp \
    $$PWD/fileloaderrararchive.cpp \
    $$PWD/fileloadersubdirectory.cpp \

#    $$PWD/fileloaderziparchive.cpp \

HEADERS += \
    $$PWD/fileloader.h \
    $$PWD/fileloader7zarchive.h \
    $$PWD/fileloaderdirectory.h \
    $$PWD/fileloaderrararchive.h \
    $$PWD/fileloadersubdirectory.h \

#    $$PWD/fileloaderziparchive.h \


DESTDIR = ../lib
LIBS += -L../lib

DEFINES += UNRAR RARDLL
INCLUDEPATH += ../unrar
LIBS += -lunrar

#DEFINES += QUAZIP_STATIC
#INCLUDEPATH += $$PWD/../quazip/quazip/quazip $$PWD/../zlib/zlib
#LIBS += -lquazip -lzlib

DEFINES += QT7Z_STATIC
INCLUDEPATH += ../Qt7z/Qt7z
LIBS += -lQt7z

