#pragma once
#include <stddef.h>

#include "types.h"

namespace ssd {

class XorShift128Random {
public:
  virtual void SetSeed(u32 seed);
  virtual u32 GetRandom();
  virtual f32 GetF32Random();
  virtual f64 GetF64Random();
  virtual f64 GetAfter() const;

  u32 unknown08; // Inferred role: state; original member name unknown.
  u32 unknown0c; // Inferred role: state; original member name unknown.
  u32 unknown10; // Inferred role: state; original member name unknown.
  u32 unknown14; // Inferred role: state and last random value; original member name unknown.
};

static_assert(offsetof(XorShift128Random, unknown08) == 0x8, "");
static_assert(offsetof(XorShift128Random, unknown14) == 0x14, "");
static_assert(sizeof(XorShift128Random) == 0x18, "");

} // namespace ssd
