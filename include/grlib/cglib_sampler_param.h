#pragma once
#include <stddef.h>

#include "nvn/nvn.h"
#include "types.h"

namespace grlib {

struct CGLibWkrSamplerParams;

// Layout evidence: setupResource 0x710079e59c (NVN sampler at 0x0, initialised flag at 0x60, sampler id at 0x64),
// releaseParams 0x710079e790 and the CGLibBuffResSamObj constructor 0x71007b083c (flag cleared, id set to -1).
class CGLibSamplerParam {
public:
  CGLibSamplerParam() : unknown60(false), unknown64(-1) {}
  void setupResource(const CGLibWkrSamplerParams &params);
  void releaseParams();

  NVNsampler unknown00; // Inferred role: sampler; original member name unknown.
  u8 _30[0x60 - 0x30];
  bool unknown60; // Inferred role: sampler initialised; original member name unknown.
  s32 unknown64;  // Inferred role: sampler id in the sampler pool, -1 when none; original member name unknown.
};

static_assert(offsetof(CGLibSamplerParam, unknown60) == 0x60, "");
static_assert(offsetof(CGLibSamplerParam, unknown64) == 0x64, "");
static_assert(sizeof(CGLibSamplerParam) == 0x68, "");

} // namespace grlib
