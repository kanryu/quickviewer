TEMPLATE = subdirs
SUBDIRS = \
    Qt7z \
    ResizeHalf \
    easyexif \
    QuickViewer

Qt7z.subdir = Qt7z/Qt7z


QuickViewer.depends = Qt7z ResizeHalf easyexif

CODECFORSRC = UTF-8

TRANSLATIONS = QuickViewer/translations/quickviewer_ja.ts

DISTFILES += \
    QuickViewer/translations/quickviewer_ja.qm
