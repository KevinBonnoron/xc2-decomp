#pragma once
#include <stddef.h>

#include "mm_math/mm_mat44.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace ml {

class AttrTransform {
public:
  enum Flag {
    FLAG_MATRIX = 1 << 0,
    FLAG_QUAT = 1 << 1,
    FLAG_ROTATION_ZXY = 1 << 3,
  };

  AttrTransform() : unknown130(0) {}
  void update();
  void clear();

  mm::Vec3 unknown00; // Inferred role: pos; original member name unknown.
  mm::Vec3 _10;
  mm::Vec3 unknown20;  // Inferred role: scl; original member name unknown.
  mm::Mat44 unknown30; // Inferred role: matrix; original member name unknown.
  mm::Mat44 unknown70; // Inferred role: world matrix; original member name unknown.
  mm::Mat44 _b0;
  mm::Vec3 unknownf0; // Inferred role: rot; original member name unknown.
  mm::Vec3 _100;
  mm::Quat unknown110; // Inferred role: quat; original member name unknown.
  mm::Quat _120;
  u32 unknown130; // Inferred role: flags; original member name unknown.
};

static_assert(offsetof(AttrTransform, unknown20) == 0x20, "");
static_assert(offsetof(AttrTransform, unknown30) == 0x30, "");
static_assert(offsetof(AttrTransform, unknown70) == 0x70, "");
static_assert(offsetof(AttrTransform, unknownf0) == 0xf0, "");
static_assert(offsetof(AttrTransform, unknown110) == 0x110, "");
static_assert(offsetof(AttrTransform, unknown130) == 0x130, "");
static_assert(sizeof(AttrTransform) == 0x140, "");

} // namespace ml
