#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibSampler;
} // namespace grlib

namespace ml {

class DrResMdoSampler {
public:
  ~DrResMdoSampler();
  void samplerRelease();

  DrResMdoSampler *unknown00; // Inferred role: prev; original member name unknown.
  DrResMdoSampler *unknown08; // Inferred role: next; original member name unknown.
  const u8 *unknown10;        // Inferred role: resource key; original member name unknown.
  s32 unknown18;              // Inferred role: ref count; original member name unknown.
  u8 _1c[0x20 - 0x1c];
  void *unknown20; // Inferred role: allocation; original member name unknown.
  s32 unknown28;   // Inferred role: sampler count; original member name unknown.
  u8 _2c[0x30 - 0x2c];
  grlib::CGLibSampler *unknown30; // Inferred role: samplers; original member name unknown.
};

static_assert(offsetof(DrResMdoSampler, unknown18) == 0x18, "");
static_assert(offsetof(DrResMdoSampler, unknown20) == 0x20, "");
static_assert(offsetof(DrResMdoSampler, unknown28) == 0x28, "");
static_assert(offsetof(DrResMdoSampler, unknown30) == 0x30, "");

} // namespace ml
