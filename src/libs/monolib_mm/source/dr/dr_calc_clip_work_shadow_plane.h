#pragma once
#include <stddef.h>

#include "dr/dr_calc_clip_work.h"
#include "types.h"

namespace ml {

class DrCalcClipWorkShadowPlane : public DrCalcClipWork {
public:
  DrCalcClipWorkShadowPlane();
  ~DrCalcClipWorkShadowPlane();
  bool clipTest(const mm::Vec3 &position, f32 radius) const override;

  unknown001 unknown10[4]; // Inferred role: clip planes; original member name unknown.
};

static_assert(offsetof(DrCalcClipWorkShadowPlane, unknown10) == 0x10, "");
static_assert(sizeof(DrCalcClipWorkShadowPlane) == 0x90, "");

} // namespace ml
