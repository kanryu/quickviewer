#-------------------------------------------------
#
# Project created by QtCreator 2016-05-24T17:06:01
#
#-------------------------------------------------

QT       += core gui opengl concurrent opengl-private sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

VERSION = 0.8.0

TARGET = QuickViewer
TEMPLATE = app
CONFIG += plugin

QMAKE_TARGET_COMPANY = KATO Kanryu(k.kanryu@gmail.com)
QMAKE_TARGET_PRODUCT = QuickViewer
QMAKE_TARGET_DESCRIPTION = QuickViewer for folders/archives
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


INCLUDEPATH += ../ResizeHalf/ResizeHalf
INCLUDEPATH += ../easyexif/easyexif
INCLUDEPATH += ../fileloader
INCLUDEPATH += ../zimg
INCLUDEPATH += ./src ./src/catalog ./src/widgets ./src/models ./src/folderview

LIBS += -L../lib  -leasyexif -lresizehalf -lfileloader -lQt7z -lunrar -lzimg -lzlib -lquazip

win32 {
    equals(QMAKE_CC,"cl") {
        QMAKE_CXXFLAGS += /wd4819
    }
    LIBS += -luser32 -ladvapi32 -lShlwapi
}
unix {
    DEFINES += _UNIX
    QMAKE_LFLAGS += -Wl,-rpath,../lib
}


SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/imageview.cpp \
    src/exifdialog.cpp \
    src/keyconfigdialog.cpp \
    src/catalog/catalogwindow.cpp \
    src/catalog/databasesettingdialog.cpp \
    src/catalog/managedatabasedialog.cpp \
    src/catalog/volumeitemmodel.cpp \
    src/models/qvapplication.cpp \
    src/models/thumbnailmanager.cpp \
    src/models/filevolume.cpp \
    src/models/pagemanager.cpp \
    src/models/timeorderdcache.cpp \
    src/models/shadermanager.cpp \
    src/widgets/flowlayout.cpp \
    src/widgets/pageslider.cpp \
    src/widgets/shortcutbutton.cpp \
    src/folderview/folderitemmodel.cpp \
    src/folderview/folderwindow.cpp \
    src/models/pagecontent.cpp \
    src/folderview/folderitemdelegate.cpp \
    src/models/bookprogressmanager.cpp \
    src/folderview/foldertreeview.cpp \
    src/catalog/catalogwindow.cpp \
    src/catalog/databasesettingdialog.cpp \
    src/catalog/managedatabasedialog.cpp \
    src/catalog/volumeitemmodel.cpp \
    src/folderview/folderitemdelegate.cpp \
    src/folderview/folderitemmodel.cpp \
    src/folderview/foldertreeview.cpp \
    src/folderview/folderwindow.cpp \
    src/models/bookprogressmanager.cpp \
    src/models/filevolume.cpp \
    src/models/pagecontent.cpp \
    src/models/pagemanager.cpp \
    src/models/qvapplication.cpp \
    src/models/shadermanager.cpp \
    src/models/thumbnailmanager.cpp \
    src/models/timeorderdcache.cpp \
    src/widgets/flowlayout.cpp \
    src/widgets/pageslider.cpp \
    src/widgets/shortcutbutton.cpp \
    src/exifdialog.cpp \
    src/imageview.cpp \
    src/keyconfigdialog.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/mainwindowforwindows.cpp \
    src/optionsdialog.cpp \
    src/renamedialog.cpp \
    src/models/movie.cpp

HEADERS  += \
    src/qv_init.h \
    src/exifdialog.h \
    src/mainwindow.h \
    src/stdafx.h \
    src/keyconfigdialog.h \
    src/imageview.h \
    src/catalog/catalogwindow.h \
    src/catalog/databasesettingdialog.h \
    src/catalog/managedatabasedialog.h \
    src/catalog/qc_init.h \
    src/catalog/volumeitemmodel.h \
    src/models/filevolume.h \
    src/models/qvapplication.h \
    src/models/pagemanager.h \
    src/models/timeorderdcache.h \
    src/models/shadermanager.h \
    src/models/thumbnailmanager.h \
    src/widgets/flowlayout.h \
    src/widgets/pageslider.h \
    src/widgets/shortcutbutton.h \
    src/folderview/folderitemmodel.h \
    src/folderview/folderwindow.h \
    src/models/pagecontent.h \
    src/folderview/folderitemdelegate.h \
    src/models/bookprogressmanager.h \
    src/folderview/foldertreeview.h \
    src/catalog/catalogwindow.h \
    src/catalog/databasesettingdialog.h \
    src/catalog/managedatabasedialog.h \
    src/catalog/qc_init.h \
    src/catalog/volumeitemmodel.h \
    src/folderview/folderitemdelegate.h \
    src/folderview/folderitemmodel.h \
    src/folderview/foldertreeview.h \
    src/folderview/folderwindow.h \
    src/models/bookprogressmanager.h \
    src/models/filevolume.h \
    src/models/pagecontent.h \
    src/models/pagemanager.h \
    src/models/qvapplication.h \
    src/models/shadermanager.h \
    src/models/thumbnailmanager.h \
    src/models/timeorderdcache.h \
    src/widgets/flowlayout.h \
    src/widgets/pageslider.h \
    src/widgets/shortcutbutton.h \
    src/exifdialog.h \
    src/imageview.h \
    src/keyconfigdialog.h \
    src/mainwindow.h \
    src/mainwindowforwindows.h \
    src/qv_init.h \
    src/stdafx.h \
    src/optionsdialog.h \
    src/renamedialog.h \
    src/models/movie.h

win32 {
    SOURCES += src/mainwindowforwindows.cpp
    HEADERS += src/mainwindowforwindows.h
    PRECOMPILED_HEADER += src/stdafx.h
}

precompile_header:!isEmpty(PRECOMPILED_HEADER) {
    DEFINES += USING_PCH
}

FORMS    += \
    src/mainwindow.ui \
    src/exifdialog.ui \
    src/keyconfigdialog.ui \
    src/catalog/cataloglist.ui \
    src/catalog/catalogwindow.ui \
    src/catalog/createdb.ui \
    src/folderview/folderwindow.ui \
    src/optionsdialog.ui \
    src/renamedialog.ui

RESOURCES += \
    toolbar.qrc

RC_ICONS = icons/appicon.ico


DISTFILES += \
    translations/quickviewer_ja.qm \
    translations/quickviewer_es.qm \

# Shaders will be installed into DIST_DIR/shaders
SHADERS += \
    shaders/bicubic.frag \
    shaders/lanczos.frag \

DBS += \
    database/schema.sql \

OTHER_FILES += $$DBS

DBBIN += \
    database/thumbnail.sqlite3.db \

DBDIR += database/

win32 { !CONFIG(debug, debug|release) {
    shaders_install.path = $${MY_DEFAULT_INSTALL}/shaders
    shaders_install.files = $$SHADERS
    db_install.path = $${MY_DEFAULT_INSTALL}/database
    db_install.files = $$DBS $$DBBIN
    INSTALLS += shaders_install db_install
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
#shaderd.depends = shader_dir
shaders.input = SHADERS


db_dir.name = dbpath
db_dir.target = ${QMAKE_FILE_OUT}
db_dir.output = $$DESTDIR/${QMAKE_FILE_BASE}
db_dir.variable_out = DEPENDPATH
db_dir.CONFIG = verify
db_dir.commands = -$(MKDIR) ${QMAKE_FILE_OUT}
db_dir.clean_commands = -$(DEL_DIR) ${QMAKE_FILE_OUT}
db_dir.input = DBDIR

db.name  = ${QMAKE_FILE_OUT}
db.target = ${QMAKE_FILE_OUT}
db.output = $$DESTDIR/database/${QMAKE_FILE_BASE}.db
db.variable_out = DEPENDPATH
db.CONFIG = verify target_predeps
db.commands = -$(COPY_FILE) ${QMAKE_FILE_IN} ${QMAKE_FILE_OUT}
#db.depends = db_dir
db.input = DBBIN

QMAKE_EXTRA_COMPILERS += shader_dir shaders db_dir db


OTHER_FILES += SHADERS

