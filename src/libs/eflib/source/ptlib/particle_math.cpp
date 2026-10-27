#include "ptlib/particle_math.h"

#include <string.h>

namespace ptlib {

namespace {
u32 s_randSeed;
} // namespace

namespace math {

f32 fxMath_rsqrt(f32 value) {
  u32 bits;
  memcpy(&bits, &value, sizeof(bits));
  bits = 0x5f3759df - (bits >> 1);
  f32 estimate;
  memcpy(&estimate, &bits, sizeof(estimate));
  return estimate * (value * -0.5f * estimate * estimate + 1.5f);
}

u32 fxMath_RandI() { return s_randSeed = s_randSeed * 0x41c64e6d + 0x3039; }

f32 randf2() {
  s_randSeed = s_randSeed * 0x41c64e6d + 0x3039;
  u32 bits = s_randSeed & 0x7fffff | 0x40000000;
  f32 value;
  memcpy(&value, &bits, sizeof(value));
  return value - 3.0f;
}

} // namespace math

} // namespace ptlib
