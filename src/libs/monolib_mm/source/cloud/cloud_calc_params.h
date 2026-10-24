#pragma once
#include <stddef.h>

#include "mm_math/mm_col3.h"
#include "types.h"

namespace cloud {

class CloudCalcParams {
public:
  u8 _000[0x194 - 0x000];
  f32 unknown194; // Inferred role: height; original member name unknown.
  u8 _198[0x19c - 0x198];
  u32 unknown19c; // Inferred role: cld num; original member name unknown.
  u8 _1a0[0x1b8 - 0x1a0];
  mm::Col3 unknown1b8[2]; // Inferred role: plane cols; original member name unknown.
};

static_assert(offsetof(CloudCalcParams, unknown194) == 0x194, "");
static_assert(offsetof(CloudCalcParams, unknown19c) == 0x19c, "");
static_assert(offsetof(CloudCalcParams, unknown1b8) == 0x1b8, "");

} // namespace cloud
