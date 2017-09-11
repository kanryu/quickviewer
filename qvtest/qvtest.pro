#-------------------------------------------------
#
# Project created by QtCreator 2017-09-10T02:57:37
#
#-------------------------------------------------

QT       += testlib core gui concurrent

TARGET = tst_fileloadertest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        tst_fileloadertest.cpp 

DEFINES += SRCDIR=\\\"$$PWD/\\\"

win32 {
    LIBS += -luser32 -ladvapi32 -lShlwapi -loleaut32 -lole32
}
unix {
    DEFINES += _UNIX
}


DESTDIR = ../lib
LIBS += -L../lib -lunrar -lQt7z -lfileloader
INCLUDEPATH += ../fileloader

OTHER_FILES += \
    data/deflate-mbcs.zip \
    data/deflate-utf8.zip \
    data/deflate64-mbcs.zip \
    data/deflate64-utf8.zip
