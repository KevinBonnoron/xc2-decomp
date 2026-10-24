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

  u32 unknown00; // Inferred role: magic; original member name unknown.
  u8 _04[0x18 - 0x04];
  char unknown18[0x10]; // Inferred role: keyword; original member name unknown.
  u32 m_dataSize;
  u8 _2c[0x30 - 0x2c];
  u32 m_CRC;
  u8 _34[0x40 - 0x34];
  char unknown40[0x100];  // Inferred role: location; original member name unknown.
  char unknown140[0x100]; // Inferred role: time stamp; original member name unknown.
};

static_assert(offsetof(WiiFilerCommon, unknown18) == 0x18, "");
static_assert(offsetof(WiiFilerCommon, m_dataSize) == 0x28, "");
static_assert(offsetof(WiiFilerCommon, m_CRC) == 0x30, "");
static_assert(offsetof(WiiFilerCommon, unknown40) == 0x40, "");
static_assert(offsetof(WiiFilerCommon, unknown140) == 0x140, "");
static_assert(sizeof(WiiFilerCommon) == 0x240, "");

} // namespace ml
