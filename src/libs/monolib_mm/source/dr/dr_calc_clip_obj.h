#pragma once
#include <stddef.h>

#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace ml {

class DrResClip;

class DrCalcClipObj {
public:
  void release();
  bool clipcoli_sphere(const u8 *data, const mm::Vec3 &pos);
  bool clipcoli_notrot_cylinder(const u8 *data, const mm::Vec3 &pos);
  bool clipcoli_notrot_box(const u8 *data, const mm::Vec3 &pos);
  bool clipcoli_cylinder(const u8 *data, const mm::Vec3 &pos);
  bool clipcoli_box(const u8 *data, const mm::Vec3 &pos);

  bool testObjectClip(const mm::Vec3 &position, f32 radius, u32 *flags);

  u8 _00[0x08 - 0x00];
  DrCalcClipObj *unknown08; // Inferred role: next; original member name unknown.
  u8 _10[0x28 - 0x10];
  DrResClip *unknown28; // Inferred role: owner clip; original member name unknown.
  u8 _30[0x3c - 0x30];
  u32 unknown3c; // Inferred role: state flags; original member name unknown.
};

static_assert(offsetof(DrCalcClipObj, unknown08) == 0x08, "");
static_assert(offsetof(DrCalcClipObj, unknown28) == 0x28, "");
static_assert(offsetof(DrCalcClipObj, unknown3c) == 0x3c, "");

} // namespace ml
