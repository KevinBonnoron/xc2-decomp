#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class DrCalcStmListObj;

class DrCalcTexStreamMan {
public:
  DrCalcStmListObj *createTexStmListObj(const char *path);
  DrCalcStmListObj *createBufferListObj(u32 size);

  enum Flag {
    FLAG_CACHER_CLEAR_MODE = 1 << 4,
  };

  u8 _0000[0x2068 - 0x0000];
  u32 unknown2068; // Inferred role: flags; original member name unknown.
};

static_assert(offsetof(DrCalcTexStreamMan, unknown2068) == 0x2068, "");

} // namespace ml
