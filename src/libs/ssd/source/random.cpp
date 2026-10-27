#include "ssd/ssd_random.h"
#include "types.h"

namespace ssd {

void XorShift128Random::SetSeed(u32 seed) {
  u32 value1 = 1812433253u * (seed ^ (seed >> 30)) + 1;
  u32 value2 = 1812433253u * (value1 ^ (value1 >> 30)) + 2;
  u32 value3 = 1812433253u * (value2 ^ (value2 >> 30)) + 3;
  u32 value4 = 1812433253u * (value3 ^ (value3 >> 30)) + 4;
  unknown08 = value1;
  unknown0c = value2;
  unknown10 = value3;
  unknown14 = value4;
}

u32 XorShift128Random::GetRandom() {
  u32 t = unknown08 ^ (unknown08 << 11);
  unknown08 = unknown0c;
  unknown0c = unknown10;
  unknown10 = unknown14;
  unknown14 = (unknown14 ^ (unknown14 >> 19)) ^ (t ^ (t >> 8));
  return unknown14;
}

f32 XorShift128Random::GetF32Random() { return static_cast<f32>(GetRandom() & 0x7fffffff) * 4.656613e-10f; }

f64 XorShift128Random::GetF64Random() { return static_cast<f64>(GetRandom() & 0x7fffffff) / 2147483647.0; }

f64 XorShift128Random::GetAfter() const { return static_cast<f32>(unknown14 & 0x7fffffff) * 4.656613e-10f; }

} // namespace ssd
