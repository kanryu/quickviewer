// Common/CRC.cpp

#include "StdAfx.h"

#include "../../C/7zCrc.h"

struct CCRCTableInit { CCRCTableInit() { CrcGenerateTable(); } } g_CRCTableInit;

#ifdef QT7Z_STATIC_LINK
bool g_forceLinkCRC;
#endif
