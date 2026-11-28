#pragma once
#include <math.h>

#include "mm_math/mm_vec3.h"
#include "types.h"

namespace mm {

struct Line2 {
  // Nearest points of two lines (the segments' directions are unit vectors, the lines pass through `end`): the distance goes to length, the
  // points to position and otherPosition when they are not null. Returns 2 for parallel lines, 1 when a nearest point lies outside its
  // segment, else 0. Evidence: mm::Line2::getNearest (1.0.0: 0x71009b270c).
  static u32 getNearest(const Line2 &line, const Line2 &other, f32 &length, Vec3 *position, Vec3 *otherPosition);
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
