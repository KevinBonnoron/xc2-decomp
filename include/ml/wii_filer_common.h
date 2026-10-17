#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class WiiFilerCommon {
public:
  void clear();
  void setLocation(const char *location);
  void setTimeStamp(const char *timeStamp);
  WiiFilerCommon();
  ~WiiFilerCommon();
  bool isValid() const;
  void setKeyword(const char *keyword);
  void setDataSize(unsigned long size);
  u32 getDataSize() const;
  void setCRC(u32 crc);
  u32 getCRC() const;
  static u32 swp(u32 value);
  static int swp(int value);
  static short swp(short value);
  static u16 swp(u16 value);
  static char swp(char value);
  static u8 swp(u8 value);

  u32 m_magic;
  u8 _04[0x18 - 0x04];
  char m_keyword[0x10];
  u32 m_dataSize;
  u8 _2c[0x30 - 0x2c];
  u32 m_crc;
  u8 _34[0x40 - 0x34];
  char m_location[0x100];
  char m_timeStamp[0x100];
};

static_assert(offsetof(WiiFilerCommon, m_keyword) == 0x18, "");
static_assert(offsetof(WiiFilerCommon, m_dataSize) == 0x28, "");
static_assert(offsetof(WiiFilerCommon, m_crc) == 0x30, "");
static_assert(offsetof(WiiFilerCommon, m_location) == 0x40, "");
static_assert(offsetof(WiiFilerCommon, m_timeStamp) == 0x140, "");
static_assert(sizeof(WiiFilerCommon) == 0x240, "");

} // namespace ml
