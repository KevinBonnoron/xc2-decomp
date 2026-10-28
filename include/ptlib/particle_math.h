#pragma once
#include <string.h>

#include "types.h"

namespace ptlib {

namespace math {

// Inferred role: value and random range of each of the three components; the name comes from the mangled game symbols of ptlib::emitter::EmitterObj.
struct Vec3r {
  f32 unknown00; // Inferred role: value x; original member name unknown.
  f32 unknown04; // Inferred role: value y; original member name unknown.
  f32 unknown08; // Inferred role: value z; original member name unknown.
  f32 unknown0c; // Inferred role: random range x; original member name unknown.
  f32 unknown10; // Inferred role: random range y; original member name unknown.
  f32 unknown14; // Inferred role: random range z; original member name unknown.
};

static_assert(sizeof(Vec3r) == 0x18, "");

// Inferred role: advances a linear congruential seed and returns a value in [-1, 1); original name unknown.
inline f32 unknown001(u32 &seed) {
  seed = seed * 0x41c64e6d + 0x3039;
  u32 bits = seed & 0x7fffff | 0x40000000;
  f32 value;
  memcpy(&value, &bits, sizeof(value));
  return value - 3.0f;
}

f32 fxMath_rsqrt(f32 value);
u32 fxMath_RandI();
f32 randf2();

} // namespace math

} // namespace ptlib
