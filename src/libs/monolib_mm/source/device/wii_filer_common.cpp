#include "ml/wii_filer_common.h"

#include <string.h>

namespace ml {

void WiiFilerCommon::clear() {
  memset(this, 0, sizeof(*this));
  unknown00[0] = 'Q';
  unknown00[1] = 'f';
  unknown00[2] = '9';
  unknown00[3] = 'W';
}

void WiiFilerCommon::setLocation(const char *location) { __builtin_strcpy(unknown40, location); }

void WiiFilerCommon::setTimeStamp(const char *timeStamp) { __builtin_strcpy(unknown140, timeStamp); }

WiiFilerCommon::WiiFilerCommon() { clear(); }

WiiFilerCommon::~WiiFilerCommon() {}

bool WiiFilerCommon::isValid() const { return memcmp(unknown00, "Qf9W", sizeof(unknown00)) == 0; }

void WiiFilerCommon::setKeyword(const char *keyword) { __builtin_strcpy(unknown18, keyword); }

void WiiFilerCommon::setDataSize(unsigned long size) { m_dataSize = size; }

u32 WiiFilerCommon::getDataSize() const { return m_dataSize; }

void WiiFilerCommon::setCRC(u32 crc) { m_CRC = crc; }

u32 WiiFilerCommon::getCRC() const { return m_CRC; }

u16 WiiFilerCommon::getCRC16(const char *data, unsigned long size) {
  u32 crc = 0;
  for (unsigned long i = 0; i < size; i++) {
    crc |= static_cast<u8>(data[i]);
    for (int j = 0; j < 8; j++) {
      crc <<= 1;
      if (crc & 0x1000000) {
        crc ^= 0x1102100;
      }
    }
  }
  for (int j = 0; j < 16; j++) {
    crc <<= 1;
    if (crc & 0x1000000) {
      crc ^= 0x1102100;
    }
  }
  return crc >> 8;
}

u32 WiiFilerCommon::swp(u32 value) { return __builtin_bswap32(value); }

int WiiFilerCommon::swp(int value) { return __builtin_bswap32(value); }

short WiiFilerCommon::swp(short value) { return __builtin_bswap16(value); }

u16 WiiFilerCommon::swp(u16 value) { return __builtin_bswap16(value); }

char WiiFilerCommon::swp(char value) { return value; }

u8 WiiFilerCommon::swp(u8 value) { return value; }

} // namespace ml
