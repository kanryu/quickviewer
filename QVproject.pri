## Comment out if you don't need to change brightness/contrast/gamma support
DEFINES += QV_WITH_LUMINOR

## Comment out if you need OpenGL support
DEFINES += QV_WITHOUT_OPENGL

## Define when asking for portable operation.
## When off, the installation will be done by OS standard method
## Installation destination when not portable:
##   Windows: "C:\Program Files" or "C:\Users\[user]\Appdata\Roaming"
##   Linux:   "/usr/local"
DEFINES += QV_PORTABLE

!contains(DEFINES, QV_PORTABLE) {
    QV_BIN_PATH = /usr/local/bin
    QV_LIB_PATH = /usr/local/lib
    QV_SHARED_PATH = /usr/local/shared
}

greaterThan(QT_MAJOR_VERSION, 4) {
    TARGET_ARCH=$${QT_ARCH}
} else {
    TARGET_ARCH=$${QMAKE_HOST.arch}
}

win32 {
    contains(TARGET_ARCH, x86_64) {
        TARGET_ARCH = x64
    } else {
        TARGET_ARCH = x86
    }
    LUMINOR_BIN_PATH = luminor-msvc2015-$${TARGET_ARCH}
}
unix {
    contains(TARGET_ARCH, x86_64) {
        TARGET_ARCH = x64
    } else {
        TARGET_ARCH = x86
    }
    LUMINOR_BIN_PATH = luminor-linux-$${TARGET_ARCH}
}
macos {
    LUMINOR_BIN_PATH = luminor-macos-$${TARGET_ARCH}
}
