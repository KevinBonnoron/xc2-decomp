#pragma once
#include <stddef.h>

#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace ml {

class DrCalcCpPlaneObj {
public:
  void release();
  bool testClip(const mm::Vec3 &position, f32 radius);

  u8 _00[0x08 - 0x00];
  DrCalcCpPlaneObj *unknown08; // Inferred role: next; original member name unknown.
};

static_assert(offsetof(DrCalcCpPlaneObj, unknown08) == 0x08, "");

} // namespace ml
