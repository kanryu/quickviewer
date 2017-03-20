TEMPLATE = subdirs
SUBDIRS = \
    Qt7z\
    QuickViewer

Qt7z.subdir = Qt7z/Qt7z

QuickViewer.depends = Qt7z
