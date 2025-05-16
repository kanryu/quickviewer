

#DEFINES += QT7Z_LIBRARY QT7Z_STATIC EXTERNAL_CODECS
DEFINES += QT_DEPRECATED_WARNINGS

win32 {
#    DEFINES += QT7Z_STATIC_LINK
#    DEFINES += UNICODE
#    DEFINES += _UNICODE
#    DEFINES += WIN_LONG_PATH
#    DEFINES += _7ZIP_LARGE_PAGES
#    DEFINES += SUPPORT_DEVICE_FILE
    !CONFIG(debug, debug|release): DEFINES += NDEBUG
#    *g++*: DEFINES += NTDDI_VERSION=NTDDI_VISTA

    INCLUDEPATH += \
        $$PWD/7zip \
        $$PWD/7zip/CPP \
        $$PWD/lib7zip/src \

    HEADERS += \
        $$PWD/7zip/CPP/Common/AutoPtr.h \
        $$PWD/7zip/CPP/Common/C_FileIO.h \
        $$PWD/7zip/CPP/Common/ComTry.h \
        $$PWD/7zip/CPP/Common/CommandLineParser.h \
        $$PWD/7zip/CPP/Common/Common.h \
        $$PWD/7zip/CPP/Common/Defs.h \
        $$PWD/7zip/CPP/Common/DynLimBuf.h \
        $$PWD/7zip/CPP/Common/DynamicBuffer.h \
        $$PWD/7zip/CPP/Common/IntToString.h \
        $$PWD/7zip/CPP/Common/Lang.h \
        $$PWD/7zip/CPP/Common/ListFileUtils.h \
        $$PWD/7zip/CPP/Common/MyBuffer.h \
        $$PWD/7zip/CPP/Common/MyBuffer2.h \
        $$PWD/7zip/CPP/Common/MyCom.h \
        $$PWD/7zip/CPP/Common/MyException.h \
        $$PWD/7zip/CPP/Common/MyGuidDef.h \
        $$PWD/7zip/CPP/Common/MyInitGuid.h \
        $$PWD/7zip/CPP/Common/MyLinux.h \
        $$PWD/7zip/CPP/Common/MyMap.h \
        $$PWD/7zip/CPP/Common/MyString.h \
        $$PWD/7zip/CPP/Common/MyTypes.h \
        $$PWD/7zip/CPP/Common/MyUnknown.h \
        $$PWD/7zip/CPP/Common/MyVector.h \
        $$PWD/7zip/CPP/Common/MyWindows.h \
        $$PWD/7zip/CPP/Common/MyXml.h \
        $$PWD/7zip/CPP/Common/NewHandler.h \
        $$PWD/7zip/CPP/Common/Random.h \
        $$PWD/7zip/CPP/Common/StdAfx.h \
        $$PWD/7zip/CPP/Common/StdInStream.h \
        $$PWD/7zip/CPP/Common/StdOutStream.h \
        $$PWD/7zip/CPP/Common/StringConvert.h \
        $$PWD/7zip/CPP/Common/StringToInt.h \
        $$PWD/7zip/CPP/Common/TextConfig.h \
        $$PWD/7zip/CPP/Common/UTFConvert.h \
        $$PWD/7zip/CPP/Common/Wildcard.h \

    SOURCES += \
        $$PWD/lib7zip/src/7ZipArchive.cpp \
        $$PWD/lib7zip/src/7ZipArchiveItem.cpp \
        $$PWD/lib7zip/src/7ZipArchiveOpenCallback.cpp \
        $$PWD/lib7zip/src/7ZipCodecInfo.cpp \
        $$PWD/lib7zip/src/7ZipCompressCodecsInfo.cpp \
        $$PWD/lib7zip/src/7ZipDllHandler.cpp \
        $$PWD/lib7zip/src/7ZipFormatInfo.cpp \
        $$PWD/lib7zip/src/7ZipInStreamWrapper.cpp \
        $$PWD/lib7zip/src/7zipLibrary.cpp \
        $$PWD/lib7zip/src/7ZipObjectPtrArray.cpp \
        $$PWD/lib7zip/src/7ZipOpenArchive.cpp \
        $$PWD/lib7zip/src/GUIDs.cpp \
        $$PWD/lib7zip/src/HelperFuncs.cpp \
        $$PWD/lib7zip/src/OSFunctions_OS2.cpp \
        $$PWD/lib7zip/src/OSFunctions_UnixLike.cpp \
        $$PWD/lib7zip/src/OSFunctions_Win32.cpp \
        $$PWD/7zip/CPP/Common/MyWindows.cpp \
        $$PWD/7zip/CPP/Windows/PropVariant.cpp \

    PRECOMPILED_HEADER += $$PWD/7zip/CPP/Common/StdAfx.h
    precompile_header:!isEmpty(PRECOMPILED_HEADER) {
        DEFINES += USING_PCH
    }
}

unix {
#    DEFINES += QT7Z_STATIC_LINK
    DEFINES += EXTERNAL_CODECS
    DEFINES += _FILE_OFFSET_BITS=64
    DEFINES += _LARGEFILE_SOURCE
    DEFINES += _REENTRANT
    DEFINES += ENV_UNIX
    DEFINES += BREAK_HANDLER
    DEFINES += UNICODE
    DEFINES += _UNICODE
    DEFINES += UNIX_USE_WIN_FILE
#    DEFINES += LOCALE_IS_UTF8
    DEFINES+=USE_LIB7Z_DLL

LIBS += -ldl


   INCLUDEPATH += \
       $$PWD/p7zip \
       $$PWD/p7zip/CPP \
       $$PWD/p7zip/CPP/include_windows \
       $$PWD/p7zip/CPP/7zip/Archive/Common \
       $$PWD/p7zip/CPP/Common \
       $$PWD/lib7zip/src \

    HEADERS += \
        $$PWD/p7zip/CPP/Common/AutoPtr.h \
        $$PWD/p7zip/CPP/Common/C_FileIO.h \
        $$PWD/p7zip/CPP/Common/ComTry.h \
        $$PWD/p7zip/CPP/Common/CommandLineParser.h \
        $$PWD/p7zip/CPP/Common/Common.h \
        $$PWD/p7zip/CPP/Common/Defs.h \
        $$PWD/p7zip/CPP/Common/DynLimBuf.h \
        $$PWD/p7zip/CPP/Common/DynamicBuffer.h \
        $$PWD/p7zip/CPP/Common/IntToString.h \
        $$PWD/p7zip/CPP/Common/Lang.h \
        $$PWD/p7zip/CPP/Common/ListFileUtils.h \
        $$PWD/p7zip/CPP/Common/MyBuffer.h \
        $$PWD/p7zip/CPP/Common/MyBuffer2.h \
        $$PWD/p7zip/CPP/Common/MyCom.h \
        $$PWD/p7zip/CPP/Common/MyException.h \
        $$PWD/p7zip/CPP/Common/MyGuidDef.h \
        $$PWD/p7zip/CPP/Common/MyInitGuid.h \
        $$PWD/p7zip/CPP/Common/MyLinux.h \
        $$PWD/p7zip/CPP/Common/MyMap.h \
        $$PWD/p7zip/CPP/Common/MyString.h \
        $$PWD/p7zip/CPP/Common/MyTypes.h \
        $$PWD/p7zip/CPP/Common/MyUnknown.h \
        $$PWD/p7zip/CPP/Common/MyVector.h \
        $$PWD/p7zip/CPP/Common/MyWindows.h \
        $$PWD/p7zip/CPP/Common/MyXml.h \
        $$PWD/p7zip/CPP/Common/NewHandler.h \
        $$PWD/p7zip/CPP/Common/Random.h \
        $$PWD/p7zip/CPP/Common/StdAfx.h \
        $$PWD/p7zip/CPP/Common/StdInStream.h \
        $$PWD/p7zip/CPP/Common/StdOutStream.h \
        $$PWD/p7zip/CPP/Common/StringConvert.h \
        $$PWD/p7zip/CPP/Common/StringToInt.h \
        $$PWD/p7zip/CPP/Common/TextConfig.h \
        $$PWD/p7zip/CPP/Common/UTFConvert.h \
        $$PWD/p7zip/CPP/Common/Wildcard.h \
        $$PWD/p7zip/CPP/myWindows/StdAfx.h \

    SOURCES += \
        $$PWD/lib7zip/src/7ZipArchive.cpp \
        $$PWD/lib7zip/src/7ZipArchiveItem.cpp \
        $$PWD/lib7zip/src/7ZipArchiveOpenCallback.cpp \
        $$PWD/lib7zip/src/7ZipCodecInfo.cpp \
        $$PWD/lib7zip/src/7ZipCompressCodecsInfo.cpp \
        $$PWD/lib7zip/src/7ZipDllHandler.cpp \
        $$PWD/lib7zip/src/7ZipFormatInfo.cpp \
        $$PWD/lib7zip/src/7ZipInStreamWrapper.cpp \
        $$PWD/lib7zip/src/7zipLibrary.cpp \
        $$PWD/lib7zip/src/7ZipObjectPtrArray.cpp \
        $$PWD/lib7zip/src/7ZipOpenArchive.cpp \
        $$PWD/lib7zip/src/HelperFuncs.cpp \
        $$PWD/lib7zip/src/OSFunctions_OS2.cpp \
        $$PWD/lib7zip/src/OSFunctions_UnixLike.cpp \
        $$PWD/lib7zip/src/OSFunctions_Win32.cpp \
        $$PWD/p7zip/CPP/Common/MyWindows.cpp \
        $$PWD/p7zip/CPP/Windows/PropVariant.cpp \

    PRECOMPILED_HEADER += $$PWD/p7zip/CPP/myWindows/StdAfx.h
    precompile_header:!isEmpty(PRECOMPILED_HEADER) {
        DEFINES += USING_PCH
    }
}
