#pragma once
#include "types.h"

namespace mm {

struct alignas(16) Vec3 {
  static const Vec3 zero;
  static const Vec3 unit;

  Vec3() {}
  Vec3(const Vec3 &vector) : x(vector.x), y(vector.y), z(vector.z) {}

  Vec3 &operator=(const Vec3 &vector) {
    x = vector.x;
    y = vector.y;
    z = vector.z;
    return *this;
  }

  Vec3 &operator+=(const Vec3 &vector) {
    x = x + vector.x;
    y = y + vector.y;
    z = z + vector.z;
    return *this;
  }

  Vec3 &operator*=(f32 scale) {
    x = x * scale;
    y = y * scale;
    z = z * scale;
    return *this;
  }

  f32 x;
  f32 y;
  f32 z;
};

} // namespace mm
