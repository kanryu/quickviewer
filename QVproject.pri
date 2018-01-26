## Comment out if you don't need to change brightness/contrast/gamma support
DEFINES += QV_WITH_LUMINOR

## Comment out if you need OpenGL support
DEFINES += QV_WITHOUT_OPENGL

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
}

win32 {
LUMINOR_BIN_PATH = luminor-msvc2015-$${TARGET_ARCH}
}

unix {
LUMINOR_BIN_PATH = luminor-linux-$${TARGET_ARCH}
}
