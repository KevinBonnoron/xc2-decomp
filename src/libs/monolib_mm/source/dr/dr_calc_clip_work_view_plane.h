#pragma once
#include <stddef.h>

#include "dr/dr_calc_clip_work.h"
#include "types.h"

namespace ml {

class DrCalcClipWorkViewPlane : public DrCalcClipWork {
public:
  DrCalcClipWorkViewPlane();
  ~DrCalcClipWorkViewPlane();
  bool clipTest(const mm::Vec3 &position, f32 radius) const override;

  unknown001 unknown10[5]; // Inferred role: clip planes; original member name unknown.
};

static_assert(offsetof(DrCalcClipWorkViewPlane, unknown10) == 0x10, "");
static_assert(sizeof(DrCalcClipWorkViewPlane) == 0xb0, "");

} // namespace ml
