include("QVproject.pri")

TEMPLATE = subdirs
SUBDIRS = \
    Qt7z/Qt7z \
    ResizeHalf \
    easyexif \
    unrar \
    fileloader \
    zimg \
    qsvgrenderer \
    QuickViewer \

#   qvtest


fileloader.depends = Qt7z/Qt7z unrar
QuickViewer.depends = ResizeHalf easyexif fileloader zimg qsvgrenderer
qvtest.depends = fileloader

contains(DEFINES, QV_WITH_LUMINOR) {
    SUBDIRS += luminor
    QuickViewer.depends += luminor
}

win32 {
    SUBDIRS += AssociateFilesWithQuickViewer
}

unix {
#    SUBDIRS += zlib quazip Qt7z/lib7z/lib7z.pro
#    quazip.depends = zlib
#    fileloader.depends += quazip zlib
#    SUBDIRS += Qt7z/lib7z/lib7z.pro
#    fileloader.depends += Qt7z/lib7z/lib7z.pro
}


CODECFORSRC = UTF-8

TRANSLATIONS = \
    QuickViewer/translations/quickviewer_en.ts \
    QuickViewer/translations/quickviewer_ja.ts \
    QuickViewer/translations/quickviewer_es.ts \
    QuickViewer/translations/quickviewer_zh.ts \
    QuickViewer/translations/quickviewer_el.ts \
    QuickViewer/translations/quickviewer_fr.ts \
    QuickViewer/translations/quickviewer_ru.ts \
    QuickViewer/translations/quickviewer_ar.ts \

DISTFILES += \
    QuickViewer/translations/quickviewer_ja.qm \
