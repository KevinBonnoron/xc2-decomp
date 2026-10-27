#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class DrCalcStmListObj;

// Inferred layout from DrCalcTexStreamMan list walks; the original member names are unknown.
class DrCalcTexStmObj {
public:
  u8 _00[0x10];
  DrCalcTexStmObj *unknown10; // Inferred role: next object; original member name unknown.
  void *unknown18;            // Inferred role: address; original member name unknown.
  s32 unknown20;              // Inferred role: size; original member name unknown.
  u32 unknown24;              // Inferred role: flags, bit 0 is in use; original member name unknown.
};

static_assert(offsetof(DrCalcTexStmObj, unknown10) == 0x10, "");
static_assert(offsetof(DrCalcTexStmObj, unknown18) == 0x18, "");
static_assert(offsetof(DrCalcTexStmObj, unknown20) == 0x20, "");
static_assert(offsetof(DrCalcTexStmObj, unknown24) == 0x24, "");

class DrCalcTexStreamMan {
public:
  int getUseMax() const;
  int getFreeMax() const;
  int getAllFreeSize() const;
  int getAllUseSize() const;
  DrCalcTexStmObj *getTopAheadFreeObj();

  DrCalcStmListObj *createTexStmListObj(const char *path);
  DrCalcStmListObj *createBufferListObj(u32 size);
  void entryJob();
  void update();
  static u32 jobUpdate(void *argument, void *userData);
  void clearMemObj(DrCalcTexStmObj *object);
  void releaseFreeObj(DrCalcTexStmObj *&object);
  void jobWait();
  void callHlvTexOptimization();
  void callOptimization(u32 value);
  void callReadStopMode();

  enum Flag {
    FLAG_CACHER_CLEAR_MODE = 1 << 4,
  };

  u8 _0000[0x08 - 0x00];
  DrCalcTexStmObj *unknown08; // Inferred role: first object of the list; original member name unknown.
  u8 _0010[0x2068 - 0x0010];
  u32 unknown2068; // Inferred role: flags; original member name unknown.
  u8 _206c[0x2488 - 0x206c];
  u32 unknown2488; // Inferred role: optimization count; original member name unknown.
  u16 unknown248c; // Inferred role: read mode; original member name unknown.
  u16 unknown248e; // Inferred role: read mode flags; original member name unknown.
  u8 _2490[0x2498 - 0x2490];
  u32 unknown2498; // Inferred role: job cpu; original member name unknown.
};

static_assert(offsetof(DrCalcTexStreamMan, unknown08) == 0x08, "");
static_assert(offsetof(DrCalcTexStreamMan, unknown2068) == 0x2068, "");
static_assert(offsetof(DrCalcTexStreamMan, unknown248c) == 0x248c, "");
static_assert(offsetof(DrCalcTexStreamMan, unknown248e) == 0x248e, "");
static_assert(offsetof(DrCalcTexStreamMan, unknown2498) == 0x2498, "");

} // namespace ml
