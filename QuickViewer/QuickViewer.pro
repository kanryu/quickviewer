#-------------------------------------------------
#
# Project created by QtCreator 2016-05-24T17:06:01
#
#-------------------------------------------------

QT       += core gui opengl concurrent gui-private

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

VERSION = 0.3.0

TARGET = QuickViewer
TEMPLATE = app
CONFIG += plugin

INCLUDEPATH += ../Qt7z/Qt7z
INCLUDEPATH += ../ResizeHalf/ResizeHalf
INCLUDEPATH += ../easyexif/easyexif


CONFIG(debug,debug|release) {
LIBS += -L../Qt7z/Qt7z/debug -lQt7z
LIBS += -L../ResizeHalf/debug -lresizehalf
LIBS += -L../easyexif/debug -leasyexif
} else {
LIBS += -L../Qt7z/Qt7z/release -lQt7z
LIBS += -L../ResizeHalf/release -lresizehalf
LIBS += -L../easyexif/release -leasyexif
}

SOURCES += main.cpp\
        mainwindow.cpp \
    imageview.cpp \
    filevolume.cpp \
    qvapplication.cpp \
    pageslider.cpp \
    exifdialog.cpp \
    keyconfigdialog.cpp \
    fileloader.cpp \
    fileloader7zarchive.h.cpp \
    fileloaderdirectory.cpp \
    fileloaderziparchive.cpp

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
    fileloaderziparchive.h

FORMS    += mainwindow.ui \
    exifdialog.ui

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
#TRANSLATIONS = translations/quickviewer_ja.ts

lupdate_only {
    SOURCES += mainwindow.ui
    SOURCES += exifdialog.ui
}
DISTFILES += \
    translations/quickviewer_ja.qm

#transfiles.target = translations/quickviewer_jaaa.qm
#transfiles.command = $(COPY) $$transfiles.depends $$transfiles.target
#transfiles.depends = $$PWD/translations/quickviewer_ja.qm

#QMAKE_EXTRA_TARGETS += transfiles
#POST_TARGETDEPS += $$transfiles.target

quickviewer_dist.path = $$OUT_PWD/dist
quickviewer_dist.files = ./dist/*

INSTALLS += quickviewer_dist
