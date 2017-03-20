#-------------------------------------------------
#
# Project created by QtCreator 2014-02-08T18:57:16
#
#-------------------------------------------------

QT       -= gui

TARGET = Qt7z
TEMPLATE = lib
CONFIG += staticlib

include("Qt7z.pri")

unix {
    target.path = /usr/lib
    INSTALLS += target
}
