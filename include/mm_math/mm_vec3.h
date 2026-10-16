#pragma once
#include "types.h"

namespace mm {

struct alignas(16) Vec3 {
  static const Vec3 zero;
  static const Vec3 unit;
  static const Vec3 unitX;
  static const Vec3 unitY;
  static const Vec3 unitZ;

  Vec3() {}
  Vec3(f32 x, f32 y, f32 z) : x(x), y(y), z(z) {}
  Vec3(const Vec3 &vector) : x(vector.x), y(vector.y), z(vector.z) {}

  Vec3 &operator=(const Vec3 &vector) {
    x = vector.x;
    y = vector.y;
    z = vector.z;
    return *this;
  }

  Vec3 &operator=(Vec3 &&vector) {
    if (this != &vector) {
      x = vector.x;
      y = vector.y;
      z = vector.z;
    }
    return *this;
  }

  Vec3 operator+(const Vec3 &vector) const { return Vec3(x + vector.x, y + vector.y, z + vector.z); }

  Vec3 &operator+=(const Vec3 &vector) {
    x = x + vector.x;
    y = y + vector.y;
    z = z + vector.z;
    return *this;
  }

  Vec3 &operator-=(const Vec3 &vector) {
    x = x - vector.x;
    y = y - vector.y;
    z = z - vector.z;
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
