#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class DrFogObjGbl {
public:
  u8 _00[0x44 - 0x00];
  f32 unknown44; // Inferred role: near; original member name unknown.
  f32 unknown48; // Inferred role: far; original member name unknown.
  f32 unknown4c; // Inferred role: str; original member name unknown.
  u8 _50[0x54 - 0x50];
  f32 unknown54; // Inferred role: pow; original member name unknown.
};

static_assert(offsetof(DrFogObjGbl, unknown44) == 0x44, "");
static_assert(offsetof(DrFogObjGbl, unknown54) == 0x54, "");

} // namespace ml
