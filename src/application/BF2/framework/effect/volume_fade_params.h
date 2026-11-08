#pragma once
#include <stddef.h>

#include "mm_math/mm_col3.h"
#include "mm_math/mm_vec3_na.h"
#include "types.h"

namespace fw {

// Layout evidence: gf::GfVolumeFade::copyVolumeFadeParams (0x7104f74a4) reads 0x00..0x98 and gf::GfVolumeFade::setupKeyFrame (0x7104f75a8)
// reads the key times at 0x9c and the key values at 0xac.
struct VolumeFadeParams {
  mm::Col3 unknown00[5]; // Inferred role: colors; original member name unknown.
  mm::Vec3NA unknown3c;  // Inferred role: position; original member name unknown.
  mm::Vec3NA unknown48;  // Inferred role: scale; original member name unknown.
  f32 unknown54[5];      // Inferred role: first group of five floats; original member name unknown.
  f32 unknown68[5];      // Inferred role: second group of five floats; original member name unknown.
  f32 unknown7c[5];      // Inferred role: third group of five floats; original member name unknown.
  f32 unknown90;         // Inferred role: frame; original member name unknown.
  f32 unknown94;         // Inferred role: rate; original member name unknown.
  f32 unknown98;         // Role and original member name unknown.
  f32 unknown9c[4];      // Inferred role: key times in frames, the unused keys are zero; original member name unknown.
  f32 unknownac[4];      // Inferred role: key values; original member name unknown.
};

static_assert(offsetof(VolumeFadeParams, unknown3c) == 0x3c, "");
static_assert(offsetof(VolumeFadeParams, unknown48) == 0x48, "");
static_assert(offsetof(VolumeFadeParams, unknown54) == 0x54, "");
static_assert(offsetof(VolumeFadeParams, unknown68) == 0x68, "");
static_assert(offsetof(VolumeFadeParams, unknown7c) == 0x7c, "");
static_assert(offsetof(VolumeFadeParams, unknown90) == 0x90, "");
static_assert(offsetof(VolumeFadeParams, unknown9c) == 0x9c, "");
static_assert(offsetof(VolumeFadeParams, unknownac) == 0xac, "");
static_assert(sizeof(VolumeFadeParams) == 0xbc, "");

} // namespace fw
