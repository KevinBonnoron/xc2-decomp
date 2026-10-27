#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class DrPixlMdlSampler {
public:
  DrPixlMdlSampler();
  bool update();

  s32 unknown00;  // Inferred role: applied sampler setting; original member name unknown.
  s32 unknown04;  // Inferred role: applied sampler setting; original member name unknown.
  bool unknown08; // Inferred role: applied sampler setting; original member name unknown.
  s32 unknown0c;  // Inferred role: requested sampler setting; original member name unknown.
  s32 unknown10;  // Inferred role: requested sampler setting; original member name unknown.
  bool unknown14; // Inferred role: requested sampler setting; original member name unknown.
};

static_assert(offsetof(DrPixlMdlSampler, unknown04) == 0x04, "");
static_assert(offsetof(DrPixlMdlSampler, unknown08) == 0x08, "");
static_assert(offsetof(DrPixlMdlSampler, unknown0c) == 0x0c, "");
static_assert(offsetof(DrPixlMdlSampler, unknown10) == 0x10, "");
static_assert(offsetof(DrPixlMdlSampler, unknown14) == 0x14, "");

} // namespace ml
