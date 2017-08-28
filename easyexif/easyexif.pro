#-------------------------------------------------
#
# Project created by QtCreator 2014-02-08T18:57:16
#
#-------------------------------------------------

QT       -= core

TARGET = easyexif
TEMPLATE = lib
CONFIG += staticlib

*g++* {
    QMAKE_CXXFLAGS += -std=c++11
}

SOURCES += \
    $$PWD/easyexif/exif.cpp

HEADERS += \
    $$PWD/easyexif/exif.h

INCLUDEPATH += \
    $$PWD/easyexif

DESTDIR = ../lib
