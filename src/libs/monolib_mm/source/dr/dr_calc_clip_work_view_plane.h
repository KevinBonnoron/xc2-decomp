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
  bool clipTest(const f32 *min, const f32 *max) const override;
  bool clipTest(const mm::Vec3 *points, int count) const override;
  int clipTypeTest(const mm::Vec3 &position, f32 radius) const override;

  unknown001 unknown10[5]; // Inferred role: clip planes; original member name unknown.
};

static_assert(offsetof(DrCalcClipWorkViewPlane, unknown10) == 0x10, "");
static_assert(sizeof(DrCalcClipWorkViewPlane) == 0xb0, "");

} // namespace ml
