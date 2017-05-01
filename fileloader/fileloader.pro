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
INCLUDEPATH += ../unrar


DESTDIR = ../lib

DEFINES += UNRAR RARDLL


