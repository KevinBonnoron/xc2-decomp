#pragma once
#include <stddef.h>

#include "dr/dr_calc_clip_work.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace ml {

class DrCalcClipWorkSphere : public DrCalcClipWork {
public:
  DrCalcClipWorkSphere();
  ~DrCalcClipWorkSphere();
  void setSphereWork(const mm::Vec3 &position, f32 radius, int sign);
  bool clipTest(const mm::Vec3 &position, f32 radius) const override;
  int clipTypeTest(const mm::Vec3 &position, f32 radius) const override;
  void debugDraw() override;

  mm::Vec3 unknown10; // Inferred role: sphere position; original member name unknown.
  mm::Vec3 unknown20; // Inferred role: direction (0, 0, +-1); original member name unknown.
  f32 unknown30;      // Inferred role: sphere radius; original member name unknown.
};

static_assert(offsetof(DrCalcClipWorkSphere, unknown10) == 0x10, "");
static_assert(offsetof(DrCalcClipWorkSphere, unknown20) == 0x20, "");
static_assert(offsetof(DrCalcClipWorkSphere, unknown30) == 0x30, "");

} // namespace ml
