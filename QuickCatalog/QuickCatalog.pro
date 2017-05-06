#-------------------------------------------------
#
# Project created by QtCreator 2017-04-28T01:37:51
#
#-------------------------------------------------

QT       += core gui concurrent sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = catalog
TEMPLATE = lib
CONFIG += staticlib


SOURCES += \
#    main.cpp\
    catalogwindow.cpp \
    thumbnailmanager.cpp \
    fileexplorermodel.cpp \
    fileexplorer.cpp \
    databasesettingdialog.cpp \
    managedatabasedialog.cpp

HEADERS  += catalogwindow.h \
    thumbnailmanager.h \
    fileexplorermodel.h \
    fileexplorer.h \
    databasesettingdialog.h \
    managedatabasedialog.h \
    qc_init.h

FORMS    += catalogwindow.ui \
    createdb.ui \
    cataloglist.ui

RESOURCES += \
    ../QuickViewer/toolbar.qrc

win32 {
    QMAKE_CXXFLAGS += /wd4819
    LIBS += -lShlwapi
}

DESTDIR = ../lib

DBS += \
    database/schema.sql \

DBBIN += \
    database/thumbnail.sqlite3.db \

DBDIR += database/

win32 { !CONFIG(debug, debug|release) {
    db_install.path = $${MY_DEFAULT_INSTALL}/$$DBDIR
    db_install.files = $$DBS $$DBBIN
    INSTALLS += db_install
} }


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

QMAKE_EXTRA_COMPILERS += db_dir db

OTHER_FILES += $$DBS
