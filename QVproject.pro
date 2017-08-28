TEMPLATE = subdirs
SUBDIRS = \
    Qt7z/Qt7z/qt7z.pro \
    ResizeHalf/resizehalf.pro \
    easyexif \
    unrar \
    fileloader \
    zimg \
    QuickViewer \

#    zlib \
#    quazip \



#quazip.depends = zlib
#fileloader.depends = Qt7z/Qt7z/qt7z.pro unrar quazip zlib
fileloader.depends = Qt7z/Qt7z/qt7z.pro unrar
QuickViewer.depends = ResizeHalf/resizehalf.pro easyexif fileloader zimg

win32 {
    SUBDIRS += AssociateFilesWithQuickViewer
    QuickViewer.depends += AssociateFilesWithQuickViewer
}


CODECFORSRC = UTF-8

TRANSLATIONS = \
    QuickViewer/translations/quickviewer_ja.ts \
    QuickViewer/translations/quickviewer_es.ts \
    QuickViewer/translations/quickviewer_zh.ts \
    QuickViewer/translations/quickviewer_el.ts \

DISTFILES += \
    QuickViewer/translations/quickviewer_ja.qm \
