#pragma once
#include <stddef.h>

#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace ml {

class DrCalcClipObj;
class DrCalcCpPlaneObj;

class DrCalcClipMan {
public:
  void update();
  bool testObjectClip(const mm::Vec3 &position, f32 radius);
  bool testPlaneClip(const mm::Vec3 &position, f32 radius);

  u8 _00[0x10 - 0x00];
  DrCalcClipObj *unknown10; // Inferred role: first clip object; original member name unknown.
  u8 _18[0x40 - 0x18];
  DrCalcCpPlaneObj *unknown40; // Inferred role: first clip plane object; original member name unknown.
  u8 _48[0x70 - 0x48];
  u32 *unknown70; // Inferred role: clip flags; original member name unknown.
};

static_assert(offsetof(DrCalcClipMan, unknown10) == 0x10, "");
static_assert(offsetof(DrCalcClipMan, unknown40) == 0x40, "");
static_assert(offsetof(DrCalcClipMan, unknown70) == 0x70, "");

} // namespace ml
