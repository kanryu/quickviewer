#-------------------------------------------------
#
# Project created by QtCreator 2014-02-08T18:57:16
#
#-------------------------------------------------

QT       -= core

TARGET = resizehalf
TEMPLATE = lib
CONFIG += staticlib
CONFIG += warn_off

equals(QMAKE_CC,"cl") {
    QMAKE_CXXFLAGS += /wd4819
}

SOURCES += \
    $$PWD/ResizeHalf/ResizeHalf.cpp

HEADERS += \
    $$PWD/ResizeHalf/ResizeHalf.h \
    $$PWD/ResizeHalf/rh_common.h \
    $$PWD/ResizeHalf/reduceby2_functions.h \
    $$PWD/ResizeHalf/bilinear_functions.h \

INCLUDEPATH += \
    $$PWD/ResizeHalf

DESTDIR = ../lib

