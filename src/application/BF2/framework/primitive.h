#pragma once
#include <stddef.h>

#include "mm_math/mm_line2.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace mm {
struct Mat44;
} // namespace mm

namespace fw {

class PrimSphere;

class PrimCapsule : public mm::Line2 {
public:
  void setup(const mm::Vec3 &start, const mm::Vec3 &end, f32 radius);
  f32 getHeight() const;
  void getCenter(mm::Vec3 &center) const;
  void getMat(mm::Mat44 &matrix) const;
  bool isCollide(const PrimCapsule &capsule) const;
  bool isCollide(const PrimSphere &sphere) const;
  PrimCapsule &add(const mm::Vec3 &offset);

  f32 radius;
};

static_assert(offsetof(PrimCapsule, radius) == 0x30, "");

class PrimSphere {
public:
  void setup(const mm::Vec3 &center, f32 radius);
  void getCenter(mm::Vec3 &center) const;
  bool isCollide(const PrimSphere &sphere) const;
  bool isCollide(const PrimCapsule &capsule) const;
  PrimSphere &add(const mm::Vec3 &offset);

  mm::Vec3 center;
  f32 radius;
};

static_assert(offsetof(PrimSphere, radius) == 0x10, "");

} // namespace fw
