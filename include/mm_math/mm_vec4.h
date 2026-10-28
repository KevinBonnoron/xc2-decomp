#pragma once
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace mm {

struct alignas(16) Vec4 {
  static const Vec4 zero;
  static const Vec4 unit;

  Vec4() {}
  Vec4(const Vec3 &vector, f32 w) : x(vector.x), y(vector.y), z(vector.z), w(w) {}
  // Assigns in the body: a mem-initializer list changes the address order of the Vector copy loops, which the game's code does not have.
  Vec4(const Vec4 &vector) {
    x = vector.x;
    y = vector.y;
    z = vector.z;
    w = vector.w;
  }

  Vec4 &operator=(const Vec4 &vector) {
    x = vector.x;
    y = vector.y;
    z = vector.z;
    w = vector.w;
    return *this;
  }

  f32 x;
  f32 y;
  f32 z;
  f32 w;
};

} // namespace mm
