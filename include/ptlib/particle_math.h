#pragma once
#include <string.h>

#include "types.h"

namespace ptlib {

namespace math {

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
