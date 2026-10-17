#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class DrGlobalIBLPack {
public:
  enum Flag {
    FLAG_DISP_OFF = 1 << 0,
  };

  u8 _00[0x50 - 0x00];
  u32 m_flags;
  u8 _54[0x58 - 0x54];
  u8 m_captureMode;
};

static_assert(offsetof(DrGlobalIBLPack, m_flags) == 0x50, "");
static_assert(offsetof(DrGlobalIBLPack, m_captureMode) == 0x58, "");

class DrGlobalIBLMan {
public:
  DrGlobalIBLPack *createObj(const void *data);
  void releaseObj(DrGlobalIBLPack *pack);
};

} // namespace ml
