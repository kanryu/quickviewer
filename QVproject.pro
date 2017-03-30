TEMPLATE = subdirs
#SUBDIRS = \
#    Qt7z \
#    ResizeHalf \
#    easyexif \
#    unrar src \
#    QuickViewer
#
#Qt7z.subdir = Qt7z/Qt7z
#
#src.subdir = qtrar/src
#unrar.subdir = qtrar/src/unrar
#
#
#QuickViewer.depends = Qt7z ResizeHalf easyexif unrar src

SUBDIRS = \
    Qt7z \
    ResizeHalf \
    easyexif \
    QtRAR \
    QuickViewer

Qt7z.subdir = Qt7z/Qt7z



QuickViewer.depends = Qt7z ResizeHalf easyexif QtRAR



CODECFORSRC = UTF-8

TRANSLATIONS = QuickViewer/translations/quickviewer_ja.ts

DISTFILES += \
    QuickViewer/translations/quickviewer_ja.qm
