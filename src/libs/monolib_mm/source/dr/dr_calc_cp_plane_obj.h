#pragma once
#include <stddef.h>

#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace ml {

class DrCalcCpPlaneObj {
public:
  ~DrCalcCpPlaneObj();
  void release();
  bool testClip(const mm::Vec3 &position, f32 radius);

  u8 _00[0x08 - 0x00];
  DrCalcCpPlaneObj *unknown08; // Inferred role: next; original member name unknown.
  u8 _10[0x30 - 0x10];
  void *unknown30; // Inferred role: plane work buffer; original member name unknown.
  u8 _38[0x3c - 0x38];
  s32 unknown3c; // Inferred role: plane count; original member name unknown.
  u32 unknown40; // Inferred role: state flags; original member name unknown.
};

static_assert(offsetof(DrCalcCpPlaneObj, unknown08) == 0x08, "");
static_assert(offsetof(DrCalcCpPlaneObj, unknown30) == 0x30, "");
static_assert(offsetof(DrCalcCpPlaneObj, unknown3c) == 0x3c, "");
static_assert(offsetof(DrCalcCpPlaneObj, unknown40) == 0x40, "");

} // namespace ml
