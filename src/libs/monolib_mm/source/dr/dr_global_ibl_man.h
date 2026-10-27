#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class DrGlobalIBLPack {
public:
  void setup();

  enum Flag {
    FLAG_DISP_OFF = 1 << 0,
    FLAG_UNKNOWN_30 = 1 << 30, // Inferred role: release per buffer; original name unknown.
  };

  u8 _00[0x50 - 0x00];
  u32 unknown50; // Inferred role: flags; original member name unknown.
  u8 _54[0x58 - 0x54];
  u8 unknown58; // Inferred role: capture mode; original member name unknown.
};

static_assert(offsetof(DrGlobalIBLPack, unknown50) == 0x50, "");
static_assert(offsetof(DrGlobalIBLPack, unknown58) == 0x58, "");

class DrGlobalIBLMan {
public:
  DrGlobalIBLPack *createObj(const void *data);
  void releaseObj(DrGlobalIBLPack *pack);
};

} // namespace ml
