#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class DrCalcStmListObj;

class DrCalcTexStreamMan {
public:
  DrCalcStmListObj *createTexStmListObj(const char *path);
  DrCalcStmListObj *createBufferListObj(u32 size);
  void entryJob();
  void jobWait();
  void callHlvTexOptimization();
  void callOptimization(u32 value);
  void callReadStopMode();

  enum Flag {
    FLAG_CACHER_CLEAR_MODE = 1 << 4,
  };

  u8 _0000[0x2068 - 0x0000];
  u32 unknown2068; // Inferred role: flags; original member name unknown.
  u8 _206c[0x2488 - 0x206c];
  u32 unknown2488; // Inferred role: optimization count; original member name unknown.
  u16 unknown248c; // Inferred role: read mode; original member name unknown.
  u16 unknown248e; // Inferred role: read mode flags; original member name unknown.
  u8 _2490[0x2498 - 0x2490];
  u32 unknown2498; // Inferred role: job cpu; original member name unknown.
};

static_assert(offsetof(DrCalcTexStreamMan, unknown2068) == 0x2068, "");
static_assert(offsetof(DrCalcTexStreamMan, unknown248c) == 0x248c, "");
static_assert(offsetof(DrCalcTexStreamMan, unknown248e) == 0x248e, "");
static_assert(offsetof(DrCalcTexStreamMan, unknown2498) == 0x2498, "");

} // namespace ml
