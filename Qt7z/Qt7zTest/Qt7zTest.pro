#-------------------------------------------------
#
# Project created by QtCreator 2014-02-08T20:25:29
#
#-------------------------------------------------

QT       += testlib

TARGET = Qt7zTest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

include("../Qt7z/Qt7z.pri")

SOURCES += \
    TestQt7zPackage.cpp \
    Qt7zTestMain.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    TestQt7zPackage.h

assets.files = $$PWD/assets/*
assets.path = $$OUT_PWD/assets

INSTALLS += assets
