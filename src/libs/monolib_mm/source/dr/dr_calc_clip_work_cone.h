#pragma once
#include "dr/dr_calc_clip_work.h"
#include "types.h"

namespace ml {

class DrCalcClipWorkCone : public DrCalcClipWork {
public:
  DrCalcClipWorkCone();
  ~DrCalcClipWorkCone();
  bool clipTest(const mm::Vec3 &position, f32 radius) const override;
  int clipTypeTest(const mm::Vec3 &position, f32 radius) const override;
  void debugDraw() override;

  u8 _10[0x60 - 0x10];
};

static_assert(sizeof(DrCalcClipWorkCone) == 0x60, "");

} // namespace ml
