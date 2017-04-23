HEADERS += $$PWD/unrar/*.hpp

SOURCES += \
    $$PWD/unrar/rar.cpp \
    $$PWD/unrar/strlist.cpp \
    $$PWD/unrar/strfn.cpp \
    $$PWD/unrar/pathfn.cpp \
    $$PWD/unrar/smallfn.cpp \
    $$PWD/unrar/global.cpp \
    $$PWD/unrar/file.cpp \
    $$PWD/unrar/filefn.cpp \
    $$PWD/unrar/filcreat.cpp \
    $$PWD/unrar/archive.cpp \
    $$PWD/unrar/arcread.cpp \
    $$PWD/unrar/unicode.cpp \
    $$PWD/unrar/system.cpp \
    $$PWD/unrar/isnt.cpp \
    $$PWD/unrar/crypt.cpp \
    $$PWD/unrar/crc.cpp \
    $$PWD/unrar/rawread.cpp \
    $$PWD/unrar/encname.cpp \
    $$PWD/unrar/resource.cpp \
    $$PWD/unrar/match.cpp \
    $$PWD/unrar/timefn.cpp \
    $$PWD/unrar/rdwrfn.cpp \
    $$PWD/unrar/consio.cpp \
    $$PWD/unrar/options.cpp \
    $$PWD/unrar/errhnd.cpp \
    $$PWD/unrar/rarvm.cpp \
    $$PWD/unrar/secpassword.cpp \
    $$PWD/unrar/rijndael.cpp \
    $$PWD/unrar/getbits.cpp \
    $$PWD/unrar/sha1.cpp \
    $$PWD/unrar/sha256.cpp \
    $$PWD/unrar/blake2s.cpp \
    $$PWD/unrar/hash.cpp \
    $$PWD/unrar/extinfo.cpp \
    $$PWD/unrar/extract.cpp \
    $$PWD/unrar/volume.cpp \
    $$PWD/unrar/list.cpp \
    $$PWD/unrar/find.cpp \
    $$PWD/unrar/unpack.cpp \
    $$PWD/unrar/headers.cpp \
    $$PWD/unrar/threadpool.cpp \
    $$PWD/unrar/rs16.cpp \
    $$PWD/unrar/cmddata.cpp \
    $$PWD/unrar/ui.cpp \

contains(DEFINES, RAR_BUILD_UNRAR) {
    SOURCES += \
        $$PWD/unrar/filestr.cpp \
        $$PWD/unrar/recvol.cpp \
        $$PWD/unrar/rs.cpp \
        $$PWD/unrar/scantree.cpp \
        $$PWD/unrar/qopen.cpp \

}

contains(DEFINES, RAR_BUILD_LIB) {
    SOURCES += \
        $$PWD/unrar/filestr.cpp \
        $$PWD/unrar/scantree.cpp \
        $$PWD/unrar/dll.cpp \
        $$PWD/unrar/qopen.cpp \

}

