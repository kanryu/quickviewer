#-------------------------------------------------
#
# Project created by QtCreator 2017-07-21T04:47:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AssociateFilesWithQuickViewer
TEMPLATE = app
#CONFIG += console

QMAKE_TARGET_COMPANY = KATO Kanryu(k.kanryu@gmail.com)
QMAKE_TARGET_PRODUCT = AssociateFilesWithQuickViewer
QMAKE_TARGET_DESCRIPTION = Associate Files Tool for QuickViewer
QMAKE_TARGET_COPYRIGHT = (C) 2017 KATO Kanryu

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

*g++* {
    DEFINES += NTDDI_VERSION=NTDDI_VISTA
}

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

LIBS += -lole32

INCLUDEPATH += ../QuickViewer/src/qlanguageselector

SOURCES += \
        main.cpp \
        fileassocdialog.cpp \
    ../QuickViewer/src/qlanguageselector/qlanguageselector.cpp

HEADERS += \
        fileassocdialog.h \
    ../QuickViewer/src/qlanguageselector/qlanguageselector.h

FORMS += \
        fileassocdialog.ui

RC_ICONS = app_icon2.ico
!CONFIG(debug, debug|release) {
    CONFIG += embed_manifest_exe
    QMAKE_LFLAGS += /MANIFESTUAC:$$quote(\"level=\'requireAdministrator\' uiAccess=\'false\'\")
}

greaterThan(QT_MAJOR_VERSION, 4) {
    TARGET_ARCH=$${QT_ARCH}
} else {
    TARGET_ARCH=$${QMAKE_HOST.arch}
}
contains(TARGET_ARCH, x86_64) {
    TARGET_ARCH = x64
} else {
    TARGET_ARCH = x86
}

DESTDIR = ../bin

DISTFILES += \
    ../QuickViewer/translations/quickviewer_ja.qm \
    ../QuickViewer/translations/quickviewer_es.qm \
    ../QuickViewer/translations/quickviewer_zh.qm \

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    icons/qv_apng.ico \
    icons/qv_bmp.ico \
    icons/qv_dds.ico \
    icons/qv_gif.ico \
    icons/qv_icon.ico \
    icons/qv_jpeg.ico \
    icons/qv_png.ico \
    icons/qv_raw.ico \
    icons/qv_tga.ico \
    icons/qv_tiff.ico \
    icons/qv_webp.ico \
