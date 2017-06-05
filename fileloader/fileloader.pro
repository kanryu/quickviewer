#-------------------------------------------------
#
# Project created by QtCreator 2014-02-08T18:57:16
#
#-------------------------------------------------

QT       += core gui gui-private

TARGET = fileloader
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    $$PWD/*.cpp

HEADERS += \
    $$PWD/*.h

INCLUDEPATH += ../Qt7z/Qt7z


DESTDIR = ../lib

DEFINES += UNRAR RARDLL
INCLUDEPATH += ../unrar

DEFINES += QUAZIP_STATIC
INCLUDEPATH += $$PWD/../quazip/quazip/quazip $$PWD/../zlib/zlib



