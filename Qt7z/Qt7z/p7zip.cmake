include_directories(
    "p7zip/CPP/myWindows"
    "p7zip/CPP"
    "p7zip/CPP/include_windows"
)

add_definitions(
    -DQT7Z_STATIC_LINK
    -D_FILE_OFFSET_BITS=64
    -D_LARGEFILE_SOURCE
    -D_REENTRANT
    -DENV_UNIX
    -DBREAK_HANDLER
    -DUNICODE
    -D_UNICODE
    -DUNIX_USE_WIN_FILE
)

if(APPLE)
    add_definitions(-DENV_MACOSX)
    find_library(COREFOUNDATION_LIBRARY CoreFoundation)
endif(APPLE)

set(7Z_SRCS
    # "p7zip/ASM/x86/7zAsm.asm"
    # "p7zip/ASM/x86/7zCrcOpt_asm.asm"
    # "p7zip/ASM/x86/AesOpt.asm"

    # C
    "p7zip/C/7zCrc.c"
    "p7zip/C/7zCrcOpt.c"
    "p7zip/C/7zStream.c"
    "p7zip/C/Aes.c"
    "p7zip/C/Alloc.c"
    "p7zip/C/Bcj2.c"
    "p7zip/C/Bcj2Enc.c"
    "p7zip/C/Bra.c"
    "p7zip/C/Bra86.c"
    "p7zip/C/BraIA64.c"
    "p7zip/C/CpuArch.c"
    "p7zip/C/Delta.c"
    "p7zip/C/LzFind.c"
    "p7zip/C/LzFindMt.c"
    "p7zip/C/Lzma2Dec.c"
    "p7zip/C/Lzma2Enc.c"
    "p7zip/C/LzmaDec.c"
    "p7zip/C/LzmaEnc.c"
    "p7zip/C/MtCoder.c"
    "p7zip/C/Ppmd7.c"
    "p7zip/C/Ppmd7Dec.c"
    "p7zip/C/Ppmd7Enc.c"
    "p7zip/C/Sha256.c"
    "p7zip/C/Sort.c"
    "p7zip/C/Threads.c"
    "p7zip/C/Xz.c"
    "p7zip/C/XzDec.c"
    "p7zip/C/XzEnc.c"
    "p7zip/C/XzIn.c"

    # Common
    "p7zip/CPP/Common/CommandLineParser.cpp"
    "p7zip/CPP/Common/CRC.cpp"
    "p7zip/CPP/Common/CrcReg.cpp"
    "p7zip/CPP/Common/IntToString.cpp"
    "p7zip/CPP/Common/ListFileUtils.cpp"
    "p7zip/CPP/Common/NewHandler.cpp"
    "p7zip/CPP/Common/StdInStream.cpp"
    "p7zip/CPP/Common/StdOutStream.cpp"
    "p7zip/CPP/Common/MyString.cpp"
    "p7zip/CPP/Common/StringConvert.cpp"
    "p7zip/CPP/Common/StringToInt.cpp"
    "p7zip/CPP/Common/UTFConvert.cpp"
    "p7zip/CPP/Common/MyVector.cpp"
    "p7zip/CPP/Common/MyWindows.cpp"
    "p7zip/CPP/Common/Wildcard.cpp"
    "p7zip/CPP/Common/XzCrc64Reg.cpp"
    "p7zip/CPP/Common/Sha256Reg.cpp"

    # Win
    "p7zip/CPP/Windows/DLL.cpp"
    "p7zip/CPP/Windows/ErrorMsg.cpp"
    "p7zip/CPP/Windows/FileDir.cpp"
    "p7zip/CPP/Windows/FileFind.cpp"
    "p7zip/CPP/Windows/FileIO.cpp"
    "p7zip/CPP/Windows/FileName.cpp"
    "p7zip/CPP/Windows/PropVariant.cpp"
    "p7zip/CPP/Windows/PropVariantConv.cpp"
    "p7zip/CPP/Windows/Synchronization.cpp"
    "p7zip/CPP/Windows/System.cpp"
    "p7zip/CPP/Windows/TimeUtils.cpp"
    "p7zip/CPP/myWindows/myAddExeFlag.cpp"
    "p7zip/CPP/myWindows/mySplitCommandLine.cpp"
    "p7zip/CPP/myWindows/wine_date_and_time.cpp"

    # 7zip common
    "p7zip/CPP/7zip/Common/CreateCoder.cpp"
    "p7zip/CPP/7zip/Common/CWrappers.cpp"
    "p7zip/CPP/7zip/Common/FilePathAutoRename.cpp"
    "p7zip/CPP/7zip/Common/FileStreams.cpp"
    "p7zip/CPP/7zip/Common/FilterCoder.cpp"
    "p7zip/CPP/7zip/Common/InBuffer.cpp"
    "p7zip/CPP/7zip/Common/InOutTempBuffer.cpp"
    "p7zip/CPP/7zip/Common/LimitedStreams.cpp"
    "p7zip/CPP/7zip/Common/MethodId.cpp"
    "p7zip/CPP/7zip/Common/MethodProps.cpp"
    "p7zip/CPP/7zip/Common/OffsetStream.cpp"
    "p7zip/CPP/7zip/Common/OutBuffer.cpp"
    "p7zip/CPP/7zip/Common/ProgressUtils.cpp"
    "p7zip/CPP/7zip/Common/PropId.cpp"
    "p7zip/CPP/7zip/Common/StreamBinder.cpp"
    "p7zip/CPP/7zip/Common/StreamObjects.cpp"
    "p7zip/CPP/7zip/Common/StreamUtils.cpp"
    "p7zip/CPP/7zip/Common/UniqBlocks.cpp"
    "p7zip/CPP/7zip/Common/VirtThread.cpp"

    "p7zip/CPP/7zip/Archive/LzmaHandler.cpp"
    "p7zip/CPP/7zip/Archive/SplitHandler.cpp"
    "p7zip/CPP/7zip/Archive/XzHandler.cpp"

    "p7zip/CPP/7zip/Archive/Common/CoderMixer2.cpp"
    "p7zip/CPP/7zip/Archive/Common/DummyOutStream.cpp"
    "p7zip/CPP/7zip/Archive/Common/HandlerOut.cpp"
    "p7zip/CPP/7zip/Archive/Common/InStreamWithCRC.cpp"
    "p7zip/CPP/7zip/Archive/Common/ItemNameUtils.cpp"
    "p7zip/CPP/7zip/Archive/Common/MultiStream.cpp"
    "p7zip/CPP/7zip/Archive/Common/OutStreamWithCRC.cpp"
    "p7zip/CPP/7zip/Archive/Common/ParseProperties.cpp"

    "p7zip/CPP/7zip/Archive/7z/7zCompressionMode.cpp"
    "p7zip/CPP/7zip/Archive/7z/7zDecode.cpp"
    "p7zip/CPP/7zip/Archive/7z/7zEncode.cpp"
    "p7zip/CPP/7zip/Archive/7z/7zExtract.cpp"
    "p7zip/CPP/7zip/Archive/7z/7zFolderInStream.cpp"
    "p7zip/CPP/7zip/Archive/7z/7zHandler.cpp"
    "p7zip/CPP/7zip/Archive/7z/7zHandlerOut.cpp"
    "p7zip/CPP/7zip/Archive/7z/7zHeader.cpp"
    "p7zip/CPP/7zip/Archive/7z/7zIn.cpp"
    "p7zip/CPP/7zip/Archive/7z/7zOut.cpp"
    "p7zip/CPP/7zip/Archive/7z/7zProperties.cpp"
    "p7zip/CPP/7zip/Archive/7z/7zSpecStream.cpp"
    "p7zip/CPP/7zip/Archive/7z/7zUpdate.cpp"
    "p7zip/CPP/7zip/Archive/7z/7zRegister.cpp"

    # Compress
    "p7zip/CPP/7zip/Compress/Bcj2Coder.cpp"
    "p7zip/CPP/7zip/Compress/Bcj2Register.cpp"
    "p7zip/CPP/7zip/Compress/BcjCoder.cpp"
    "p7zip/CPP/7zip/Compress/BcjRegister.cpp"
    "p7zip/CPP/7zip/Compress/BranchMisc.cpp"
    "p7zip/CPP/7zip/Compress/BranchRegister.cpp"
    "p7zip/CPP/7zip/Compress/ByteSwap.cpp"
    "p7zip/CPP/7zip/Compress/CopyCoder.cpp"
    "p7zip/CPP/7zip/Compress/CopyRegister.cpp"
    "p7zip/CPP/7zip/Compress/DeltaFilter.cpp"
    "p7zip/CPP/7zip/Compress/Lzma2Decoder.cpp"
    "p7zip/CPP/7zip/Compress/Lzma2Encoder.cpp"
    "p7zip/CPP/7zip/Compress/Lzma2Register.cpp"
    "p7zip/CPP/7zip/Compress/LzmaDecoder.cpp"
    "p7zip/CPP/7zip/Compress/LzmaEncoder.cpp"
    "p7zip/CPP/7zip/Compress/LzmaRegister.cpp"
    "p7zip/CPP/7zip/Compress/PpmdDecoder.cpp"
    "p7zip/CPP/7zip/Compress/PpmdEncoder.cpp"
    "p7zip/CPP/7zip/Compress/PpmdRegister.cpp"

    # Crypto
    "p7zip/CPP/7zip/Crypto/7zAes.cpp"
    "p7zip/CPP/7zip/Crypto/7zAesRegister.cpp"
    "p7zip/CPP/7zip/Crypto/MyAes.cpp"
    "p7zip/CPP/7zip/Crypto/MyAesReg.cpp"
    "p7zip/CPP/7zip/Crypto/RandGen.cpp"

    # UI
    "p7zip/CPP/7zip/UI/Common/ArchiveExtractCallback.cpp"
    "p7zip/CPP/7zip/UI/Common/ArchiveOpenCallback.cpp"
    "p7zip/CPP/7zip/UI/Common/DefaultName.cpp"
    "p7zip/CPP/7zip/UI/Common/Extract.cpp"
    "p7zip/CPP/7zip/UI/Common/ExtractingFilePath.cpp"
    "p7zip/CPP/7zip/UI/Common/LoadCodecs.cpp"
    "p7zip/CPP/7zip/UI/Common/OpenArchive.cpp"
    "p7zip/CPP/7zip/UI/Common/PropIDUtils.cpp"
    "p7zip/CPP/7zip/UI/Common/SetProperties.cpp"
)
