#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace ml {

class DrResMdoVertex;

class DrCalcStmWork {
public:
  DrCalcStmWork();
  static int getWorkSize(u32 count);
  grlib::CGLibTextureBuffer *getTexObj(u32 index);
  void texRelease();

  grlib::CGLibTextureBuffer *unknown00; // Inferred role: textures; original member name unknown.
  s32 unknown08;                        // Inferred role: texture count; original member name unknown.
  DrResMdoVertex *unknown10;            // Inferred role: vertex object; original member name unknown.
};

static_assert(offsetof(DrCalcStmWork, unknown08) == 0x08, "");
static_assert(offsetof(DrCalcStmWork, unknown10) == 0x10, "");

} // namespace ml
