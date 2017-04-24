#-------------------------------------------------
#
# Project created by QtCreator 2016-05-24T17:06:01
#
#-------------------------------------------------

QT       += core gui opengl concurrent gui-private opengl-private

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

VERSION = 0.5.6

TARGET = QuickViewer
TEMPLATE = app
CONFIG += plugin

QMAKE_TARGET_COMPANY = KATO Kanryu(k.kanryu@gmail.com)
QMAKE_TARGET_PRODUCT = QuickViewer
QMAKE_TARGET_DESCRIPTION = A image viewer for folders/archives, it can show images very fast
QMAKE_TARGET_COPYRIGHT = (C) 2017 KATO Kanryu

DEFINES += \
  APP_VERSION=\\\"$$VERSION\\\" \
  APP_NAME=\\\"$$QMAKE_TARGET_PRODUCT\\\" \

CODECFORSRC = UTF-8


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

# win32 depoying, please add 'jom install' into build setting on qt-creator
win32 { !CONFIG(debug, debug|release) {
    MY_DEFAULT_INSTALL = ../../QuickViewer-$${VERSION}-$${TARGET_ARCH}

    target.path = $${MY_DEFAULT_INSTALL}
    target.files = $${DESTDIR}/QuickViewer.exe
    deploy_files.path = $${MY_DEFAULT_INSTALL}
    deploy_files.files = $${PWD}/../README.md $${PWD}/../LICENSE
    deploy_files.depends = install_target
    deploy_files.commands = $$[QT_INSTALL_BINS]/windeployqt  --release --compiler-runtime $${MY_DEFAULT_INSTALL}/QuickViewer.exe
    translations.path = $${MY_DEFAULT_INSTALL}/translations
    translations.files = $${PWD}/translations/quickviewer_ja.qm
    qrawspeed.path = $${MY_DEFAULT_INSTALL}/imageformats
    qrawspeed.files = ../../../qrawspeed/imageformats-$${TARGET_ARCH}/qrawspeed0.dll
    # dlls instead of vcredist_xxx.exe
    msvcrt.PATH = C:/Program Files (x86)/Microsoft Visual Studio 14.0/VC/redist/$${TARGET_ARCH}/Microsoft.VC140.CRT
    msvcrt.path = $${MY_DEFAULT_INSTALL}
    msvcrt.removefiles = $$shell_path($${MY_DEFAULT_INSTALL}/vcredist_$${TARGET_ARCH}.exe)
    msvcrt.commands = -$(DEL_FILE) "$${msvcrt.removefiles}"
    msvcrt.depends = install_deploy_files
    msvcrt.files = \
        "$${msvcrt.PATH}/concrt140.dll" \
        "$${msvcrt.PATH}/msvcp140.dll" \
        "$${msvcrt.PATH}/vccorlib140.dll" \
        "$${msvcrt.PATH}/vcruntime140.dll"

    INSTALLS += target deploy_files translations qrawspeed msvcrt
} }


INCLUDEPATH += ../Qt7z/Qt7z
INCLUDEPATH += ../ResizeHalf/ResizeHalf
INCLUDEPATH += ../easyexif/easyexif
#INCLUDEPATH += ../QtRAR/src
INCLUDEPATH += ../unrar

#LIBS += -L../lib  -leasyexif -lresizehalf -lQt7z -lunrar -lQtRAR
LIBS += -L../lib  -leasyexif -lresizehalf -lQt7z -lunrar

## qtrar
#DEFINES += QTRAR_STATIC RARDLL

DEFINES += UNRAR RARDLL
win32 {
    QMAKE_CXXFLAGS += /wd4819
    LIBS += -luser32 -ladvapi32 -lShlwapi
}
unix {
    DEFINES += _UNIX
    QMAKE_LFLAGS += -Wl,-rpath,../lib
}


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
    pagemanager.cpp \
    timeorderdcache.cpp \
    shadermanager.cpp


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
    pagemanager.h \
    timeorderdcache.h \
    shadermanager.h


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


DISTFILES += \
    translations/quickviewer_ja.qm

# Shaders will be installed into DIST_DIR/shaders
SHADERS += \
    shaders/bicubic.frag \
    shaders/lanczos.frag \

win32 { !CONFIG(debug, debug|release) {
    shaders_install.path = $${MY_DEFAULT_INSTALL}/shaders
    shaders_install.files = $$SHADERS
    INSTALLS += shaders_install
} }

SHADERDIR += shaders/

shader_dir.name = shaderpath
shader_dir.target = ${QMAKE_FILE_OUT}
shader_dir.output = $$DESTDIR/${QMAKE_FILE_BASE}
shader_dir.variable_out = DEPENDPATH
shader_dir.CONFIG = verify
shader_dir.commands = -$(MKDIR) ${QMAKE_FILE_OUT}
shader_dir.clean_commands = -$(DEL_DIR) ${QMAKE_FILE_OUT}
shader_dir.input = SHADERDIR

shaders.name  = ${QMAKE_FILE_OUT}
shaders.target = ${QMAKE_FILE_OUT}
shaders.output = $$DESTDIR/shaders/${QMAKE_FILE_BASE}.frag
shaders.variable_out = DEPENDPATH
shaders.CONFIG = verify target_predeps
shaders.commands = -$(COPY_FILE) ${QMAKE_FILE_IN} ${QMAKE_FILE_OUT}
shaderd.depends = shader_dir
shaders.input = SHADERS

QMAKE_EXTRA_COMPILERS += shader_dir shaders


OTHER_FILES += SHADERS

