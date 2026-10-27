#pragma once
#include <stddef.h>

#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace ml {

class DrCalcClipObj {
public:
  void release();
  bool clipcoli_sphere(const u8 *data, const mm::Vec3 &pos);
  bool clipcoli_notrot_cylinder(const u8 *data, const mm::Vec3 &pos);
  bool clipcoli_notrot_box(const u8 *data, const mm::Vec3 &pos);
  bool clipcoli_cylinder(const u8 *data, const mm::Vec3 &pos);
  bool clipcoli_box(const u8 *data, const mm::Vec3 &pos);

  u8 _00[0x3c - 0x00];
  u32 unknown3c; // Inferred role: state flags; original member name unknown.
};

static_assert(offsetof(DrCalcClipObj, unknown3c) == 0x3c, "");

} // namespace ml
