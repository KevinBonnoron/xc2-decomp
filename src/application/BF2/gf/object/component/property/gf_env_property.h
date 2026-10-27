#pragma once
#include <stddef.h>

#include "mm_math/mm_col4.h"
#include "mm_math/mm_plane.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace gf {

// Evidence: layout read from the GfEnvProperty constructor (0x71005a30cc, 0x2e0 bytes allocated by GfObjFactory), the loop over eight samples of 0x50 bytes,
// the water sample initialised at 0x280, and the accesses of GfEffectGround (flags at 0x2d0: bit 0 water sample, bit n + 1 ground sample n).
struct GfEnvProperty {
  struct unknown001 {
    mm::Vec3 unknown00;  // Inferred role: sampled position; original member name unknown.
    mm::Plane unknown10; // Inferred role: sampled plane; original member name unknown.
  };

  struct unknown002 : unknown001 {
    s32 unknown30;      // Inferred role: zero-initialised; original member name unknown.
    s32 unknown34;      // Inferred role: ground material; original member name unknown.
    mm::Col4 unknown38; // Inferred role: ground color; original member name unknown.
    s32 unknown48;      // Inferred role: ground material kind; original member name unknown.
  };

  unknown002 unknown00[8]; // Inferred role: ground samples; original member name unknown.
  unknown001 unknown280;   // Inferred role: water sample, its x holds the surface height; original member name unknown.
  f32 unknown2b0;          // Inferred role: zero-initialised; original member name unknown.
  f32 unknown2b4;          // Inferred role: water depth; original member name unknown.
  s32 unknown2b8;          // Inferred role: water ground material; original member name unknown.
  s32 unknown2bc;          // Inferred role: water ground material kind; original member name unknown.
  u32 unknown2c0;          // Inferred role: damage id; original member name unknown.
  u8 _2c4[0x2d0 - 0x2c4];
  u32 unknown2d0;  // Inferred role: valid samples; original member name unknown.
  bool unknown2d4; // Inferred role: zero-initialised; original member name unknown.
};

static_assert(sizeof(GfEnvProperty::unknown001) == 0x30, "");
static_assert(sizeof(GfEnvProperty::unknown002) == 0x50, "");
static_assert(offsetof(GfEnvProperty, unknown280) == 0x280, "");
static_assert(offsetof(GfEnvProperty, unknown2b4) == 0x2b4, "");
static_assert(offsetof(GfEnvProperty, unknown2b8) == 0x2b8, "");
static_assert(offsetof(GfEnvProperty, unknown2bc) == 0x2bc, "");
static_assert(offsetof(GfEnvProperty, unknown2c0) == 0x2c0, "");
static_assert(offsetof(GfEnvProperty, unknown2d0) == 0x2d0, "");
static_assert(sizeof(GfEnvProperty) == 0x2e0, "");

} // namespace gf
