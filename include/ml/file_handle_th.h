#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class FileHandleTh {
public:
  bool addCurrentPtr(int offset);
  bool setCurrentPtr(int offset);
  void setReadAdr(int size, void *buffer, int alignedSize);
  void setTime(u64 time);

  u8 _00[0x08];
  void *unknown08; // Inferred role: read buffer; original member name unknown.
  s32 unknown10;   // Inferred role: allocated size; original member name unknown.
  u8 _14[0x18 - 0x14];
  s32 unknown18; // Inferred role: read size; original member name unknown.
  u8 _1c[0x28 - 0x1c];
  s32 m_currentPtr;
  u8 _2c[0x1c0 - 0x2c];
  u64 m_time;
};

static_assert(offsetof(FileHandleTh, unknown08) == 0x08, "");
static_assert(offsetof(FileHandleTh, unknown10) == 0x10, "");
static_assert(offsetof(FileHandleTh, unknown18) == 0x18, "");
static_assert(offsetof(FileHandleTh, m_currentPtr) == 0x28, "");
static_assert(offsetof(FileHandleTh, m_time) == 0x1c0, "");

} // namespace ml
