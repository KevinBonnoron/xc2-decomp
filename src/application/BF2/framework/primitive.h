#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "types.h"

namespace mm {
struct Mat44;
} // namespace mm

namespace fw {

class PrimCapsule {
public:
  f32 getHeight() const;
  void getMat(mm::Mat44 &matrix) const;

  mm::Vec3 direction;
  mm::Vec3 start;
  mm::Vec3 end;
  f32 radius;
};

static_assert(offsetof(PrimCapsule, radius) == 0x30, "");

class PrimSphere {
public:
  mm::Vec3 center;
  f32 radius;
};

static_assert(offsetof(PrimSphere, radius) == 0x10, "");

} // namespace fw
