#pragma once
#include <stddef.h>

#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace ml {
class DrCalcClipObj;
class DrCalcViewWork;

class DrResClip {
public:
  DrResClip();
  ~DrResClip();
  bool clipChkOccOff(DrCalcViewWork *viewWork, const mm::Vec3 &position, f32 radius);

  DrCalcClipObj *unknown00; // Inferred role: clip object; original member name unknown.
  u32 unknown08;            // Inferred role: clip state flags; original member name unknown.
  s32 unknown0c;            // Inferred role: state frame counter; original member name unknown.
  s32 unknown10;            // Inferred role: occlusion query pixel; original member name unknown.
};

static_assert(offsetof(DrResClip, unknown08) == 0x08, "");
static_assert(offsetof(DrResClip, unknown0c) == 0x0c, "");
static_assert(offsetof(DrResClip, unknown10) == 0x10, "");

} // namespace ml
