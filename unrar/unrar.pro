#QT -= core gui

TARGET = unrar
TEMPLATE = lib
CONFIG += staticlib
CONFIG += warn_off

QMAKE_MAC_SDK = macosx10.9

DEFINES += _FILE_OFFSET_BITS=64 _LARGEFILE_SOURCE UNRAR RARDLL RAR_BUILD_LIB

include(unrar.pri)
#unix {
#    DEFINES += _UNIX
#}

DESTDIR = ../lib

HEADERS += \
    rarextractor.h

SOURCES += \
    rarextractor.cpp
