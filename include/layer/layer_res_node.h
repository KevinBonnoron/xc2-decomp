#pragma once
#include <stddef.h>

#include "mm_math/mm_vec2.h"
#include "types.h"

namespace layer {

struct LayerResNode {
  mm::Vec2 unknown00; // Inferred role: pos; original member name unknown.
  mm::Vec2 unknown08; // Inferred role: scl; original member name unknown.
  mm::Vec2 unknown10; // Inferred role: rot; original member name unknown.
  f32 unknown18[4];   // Inferred role: mul color; original member name unknown.
  f32 unknown28[3];   // Inferred role: add color; original member name unknown.
  u8 _34[0x36 - 0x34];
  u8 unknown36; // Inferred role: flags; original member name unknown.
  u8 unknown37; // Inferred role: blend; original member name unknown.
};

static_assert(offsetof(LayerResNode, unknown18) == 0x18, "");
static_assert(offsetof(LayerResNode, unknown28) == 0x28, "");
static_assert(offsetof(LayerResNode, unknown36) == 0x36, "");
static_assert(sizeof(LayerResNode) == 0x38, "");

} // namespace layer
