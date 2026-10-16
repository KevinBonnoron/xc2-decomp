#pragma once
#include <math.h>
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "types.h"

namespace mm {
struct Mat44;

struct Line2 {
  static f32 getNearestLength(const Line2 &line, const Line2 &other);
  static f32 getNearestLength(const Line2 &line, const Vec3 &position);

  void set(const Vec3 &start, const Vec3 &end) {
    direction.x = start.x - end.x;
    direction.y = start.y - end.y;
    direction.z = start.z - end.z;
    f32 length = sqrtf(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);
    if (length <= 0.000001f) {
      direction = Vec3::zero;
    } else {
      f32 scale = 1.0f / length;
      direction.x = scale * direction.x;
      direction.y = scale * direction.y;
      direction.z = scale * direction.z;
    }

    this->start = start;
    this->end = end;
  }

  Vec3 direction;
  Vec3 start;
  Vec3 end;
};

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
