#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace ml {

struct DrCalcStmRes {
  const u8 *unknown00; // Inferred role: data; original member name unknown.
  u8 _08[0x10 - 0x08];
  u8 unknown10; // Inferred role: flags; original member name unknown.
  u8 _11[0x18 - 0x11];
};

static_assert(offsetof(DrCalcStmRes, unknown10) == 0x10, "");
static_assert(sizeof(DrCalcStmRes) == 0x18, "");

class DrCalcStmListObj {
public:
  enum DrTexUseMode {
    DR_TEX_USE_MODE_NONE,
    DR_TEX_USE_MODE_LOW,
    DR_TEX_USE_MODE_MIDDLE,
  };

  void release();
  bool isResSafe() const;
  DrCalcStmRes *getResVertexObj();
  void setUseMode(DrTexUseMode mode);
  grlib::CGLibTextureBuffer *getTexObj(u32 index);
  u32 getAdder();
};

} // namespace ml
