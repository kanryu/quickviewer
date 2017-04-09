#-------------------------------------------------
#
# Project created by QtCreator 2016-05-24T17:06:01
#
#-------------------------------------------------

QT       += core gui opengl concurrent gui-private

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

VERSION = 0.4.3

TARGET = QuickViewer
TEMPLATE = app
CONFIG += plugin

INCLUDEPATH += ../Qt7z/Qt7z
INCLUDEPATH += ../ResizeHalf/ResizeHalf
INCLUDEPATH += ../easyexif/easyexif
INCLUDEPATH += ../QtRAR/src

LIBS += -L../lib  -leasyexif -lresizehalf -lQt7z -lunrar -lQtRAR

# qtrar
DEFINES += QTRAR_STATIC RARDLL
win32 {
    QMAKE_CXXFLAGS += /wd4819
    LIBS += -luser32 -ladvapi32
}
unix {
    DEFINES += _UNIX
    QMAKE_LFLAGS += -Wl,-rpath,../lib
}

DESTDIR = ../bin

SOURCES += main.cpp \
    mainwindow.cpp \
    imageview.cpp \
    filevolume.cpp \
    qvapplication.cpp \
    pageslider.cpp \
    exifdialog.cpp \
    keyconfigdialog.cpp \
    fileloader.cpp \
    fileloader7zarchive.cpp \
    fileloaderdirectory.cpp \
    fileloaderziparchive.cpp \
    fileloaderrararchive.cpp \
    shortcutbutton.cpp \


HEADERS  += mainwindow.h \
    imageview.h \
    filevolume.h \
    qv_init.h \
    qvapplication.h \
    pageslider.h \
    exifdialog.h \
    keyconfigdialog.h \
    fileloader.h \
    fileloader7zarchive.h \
    fileloaderdirectory.h \
    fileloaderziparchive.h \
    fileloaderrararchive.h \
    shortcutbutton.h \


win32 {
    SOURCES += mainwindowforwindows.cpp
    HEADERS += mainwindowforwindows.h
}

FORMS    += mainwindow.ui \
    exifdialog.ui \
    keyconfigdialog.ui

RESOURCES += \
    toolbar.qrc

RC_ICONS = icons/appicon.ico


QMAKE_TARGET_COMPANY = KATO Kanryu(k.kanryu@gmail.com)
QMAKE_TARGET_PRODUCT = QuickViewer
QMAKE_TARGET_DESCRIPTION = A image viewer for folders/archives, it can show images very fast
QMAKE_TARGET_COPYRIGHT = (C) 2017 KATO Kanryu

DEFINES += \
  APP_VERSION=\\\"$$VERSION\\\" \
  APP_NAME=\\\"$$QMAKE_TARGET_PRODUCT\\\" \

CODECFORSRC = UTF-8

DISTFILES += \
    translations/quickviewer_ja.qm


quickviewer_dist.path = $$OUT_PWD/dist
quickviewer_dist.files = ./dist/*

INSTALLS += quickviewer_dist
