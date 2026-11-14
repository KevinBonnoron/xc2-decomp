#pragma once
#include <stddef.h>

#include "dr/dr_calc_clip_work.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace ml {

class DrCalcClipWorkCone : public DrCalcClipWork {
public:
  DrCalcClipWorkCone();
  ~DrCalcClipWorkCone();
  bool clipTest(const mm::Vec3 &position, f32 radius) const override;
  int clipTypeTest(const mm::Vec3 &position, f32 radius) const override;
  void debugDraw() override;

  void setConeWork(const mm::Vec3 &position, const mm::Vec3 &direction, f32 angle, f32 length);

  mm::Vec3 unknown10; // Inferred role: cone apex position; original member name unknown.
  mm::Vec3 unknown20; // Inferred role: cone axis direction; original member name unknown.
  mm::Vec3 unknown30; // Inferred role: axis direction scaled by the length; original member name unknown.
  f32 unknown40;      // Inferred role: cone length; original member name unknown.
  f32 unknown44;      // Inferred role: cone angle; original member name unknown.
  f32 unknown48;      // Inferred role: function of half the angle; original member name unknown.
  f32 unknown4c;      // Inferred role: function of the angle; original member name unknown.
  f32 unknown50;      // Inferred role: dot product of the axis and the apex position; original member name unknown.
};

static_assert(offsetof(DrCalcClipWorkCone, unknown10) == 0x10, "");
static_assert(offsetof(DrCalcClipWorkCone, unknown20) == 0x20, "");
static_assert(offsetof(DrCalcClipWorkCone, unknown30) == 0x30, "");
static_assert(offsetof(DrCalcClipWorkCone, unknown40) == 0x40, "");
static_assert(offsetof(DrCalcClipWorkCone, unknown44) == 0x44, "");
static_assert(offsetof(DrCalcClipWorkCone, unknown48) == 0x48, "");
static_assert(offsetof(DrCalcClipWorkCone, unknown4c) == 0x4c, "");
static_assert(offsetof(DrCalcClipWorkCone, unknown50) == 0x50, "");

static_assert(sizeof(DrCalcClipWorkCone) == 0x60, "");

} // namespace ml
