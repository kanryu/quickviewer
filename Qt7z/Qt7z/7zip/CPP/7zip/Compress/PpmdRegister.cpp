// PpmdRegister.cpp

#include "StdAfx.h"

#include "../Common/RegisterCodec.h"

#include "PpmdDecoder.h"

#ifndef EXTRACT_ONLY
#include "PpmdEncoder.h"
#endif

namespace NCompress {
namespace NPpmd {

REGISTER_CODEC_E(PPMD,
    CDecoder(),
    CEncoder(),
    0x30401,
    "PPMD")

QT7Z_STATIC_LINK_FORCE_INCLUDE

}}
