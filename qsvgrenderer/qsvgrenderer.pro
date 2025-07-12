QT = core gui widgets

TEMPLATE = lib
TARGET = QSVGNative
DESTDIR = ../lib
CONFIG += dll
VERSION = 0.9.0

SVGNATIVE = $$PWD/svg-native-viewer/svgnative

DEFINES += BUILDING_DLL

win32-msvc* {
    QMAKE_CXXFLAGS += /Zp8 /we4302 /we4189 /wd4290 /wd4335 /wd4355 /wd4814 /wd4091 /TP /Zc:sizedDealloc- 
}

INCLUDEPATH += \
  $$SVGNATIVE/include \

HEADERS  += \
  $$SVGNATIVE/include/svgnative/SVGDocument.h \
  $$SVGNATIVE/include/svgnative/SVGNativeCWrapper.h \
  $$SVGNATIVE/include/svgnative/SVGRenderer.h \
  $$SVGNATIVE/include/svgnative/Config.h \
  $$SVGNATIVE/include/svgnative/Rect.h \
  $$SVGNATIVE/include/svgnative/ports/qt/QSVGRenderer.h \

SOURCES +=  \
  $$SVGNATIVE/src/Constants.h \
  $$SVGNATIVE/src/SVGDocumentImpl.h \
  $$SVGNATIVE/src/SVGDocumentImpl.cpp \
  $$SVGNATIVE/src/SVGDocument.cpp \
  $$SVGNATIVE/src/Rect.cpp \
  $$SVGNATIVE/src/Interval.h \
  $$SVGNATIVE/src/Interval.cpp \
  $$SVGNATIVE/src/SVGNativeCWrapper.cpp \
  $$SVGNATIVE/src/SVGParserArcToCurve.cpp \
  $$SVGNATIVE/src/SVGStringParser.h \
  $$SVGNATIVE/src/SVGStringParser.cpp \
  $$SVGNATIVE/src/xml/XMLParser.h \
  $$SVGNATIVE/src/ports/qt/QSVGRenderer.cpp \
  $$SVGNATIVE/src/ports/qt/QXMLParser.cpp \

QMAKE_TARGET_COMPANY = Adobe
QMAKE_TARGET_PRODUCT = QSVGNative
QMAKE_TARGET_DESCRIPTION = svg-native-viewer
QMAKE_TARGET_COPYRIGHT = (C) 2025 Adobe
