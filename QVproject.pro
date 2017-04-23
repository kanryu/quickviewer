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
    Qt7z/Qt7z/qt7z.pro \
    ResizeHalf/resizehalf.pro \
    easyexif \
#    QtRAR/qtrar.pro \
    unrar \
    QuickViewer

#Qt7z.subdir = Qt7z/Qt7z/qt7z.pro
#QtRAR.subdir = QtRAR/qtrar.pro
#ResizeHalf.subdir = ResizeHalf/resizehalf.pro


#QuickViewer.depends = Qt7z/Qt7z/qt7z.pro ResizeHalf/resizehalf.pro easyexif QtRAR/qtrar.pro
QuickViewer.depends = Qt7z/Qt7z/qt7z.pro ResizeHalf/resizehalf.pro easyexif unrar



CODECFORSRC = UTF-8

TRANSLATIONS = QuickViewer/translations/quickviewer_ja.ts

DISTFILES += \
    QuickViewer/translations/quickviewer_ja.qm
