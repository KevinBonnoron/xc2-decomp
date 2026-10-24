#include "ml/wii_filer_common.h"

namespace ml {

void WiiFilerCommon::setLocation(const char *location) { __builtin_strcpy(unknown40, location); }

void WiiFilerCommon::setTimeStamp(const char *timeStamp) { __builtin_strcpy(unknown140, timeStamp); }

WiiFilerCommon::~WiiFilerCommon() {}

bool WiiFilerCommon::isValid() const { return unknown00 == 0x57396651; }

void WiiFilerCommon::setKeyword(const char *keyword) { __builtin_strcpy(unknown18, keyword); }

void WiiFilerCommon::setDataSize(unsigned long size) { m_dataSize = size; }

u32 WiiFilerCommon::getDataSize() const { return m_dataSize; }

void WiiFilerCommon::setCRC(u32 crc) { m_CRC = crc; }

u32 WiiFilerCommon::getCRC() const { return m_CRC; }

u32 WiiFilerCommon::swp(u32 value) { return __builtin_bswap32(value); }

int WiiFilerCommon::swp(int value) { return __builtin_bswap32(value); }

short WiiFilerCommon::swp(short value) { return __builtin_bswap16(value); }

u16 WiiFilerCommon::swp(u16 value) { return __builtin_bswap16(value); }

char WiiFilerCommon::swp(char value) { return value; }

u8 WiiFilerCommon::swp(u8 value) { return value; }

} // namespace ml
