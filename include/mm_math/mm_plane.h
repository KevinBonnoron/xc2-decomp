#pragma once
#include <math.h>

#include "mm_math/mm_vec3.h"
#include "types.h"

namespace mm {

struct Plane {
  Plane() {}

  void set(const Vec3 &direction, const Vec3 &position) {
    normal = direction;
    f32 length = sqrtf(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
    if (length <= 0.000001f) {
      normal = Vec3::zero;
    } else {
      f32 scale = 1.0f / length;
      normal.x = normal.x * scale;
      normal.y = normal.y * scale;
      normal.z = normal.z * scale;
    }
    distance = -(normal.x * position.x + normal.y * position.y + normal.z * position.z);
  }

  Vec3 normal;
  f32 distance;
};

static_assert(sizeof(Plane) == 0x20, "");

} // namespace mm
