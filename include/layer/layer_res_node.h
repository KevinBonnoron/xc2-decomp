#pragma once
#include <stddef.h>

#include "mm_math/mm_pnt.h"
#include "types.h"

namespace layer {

struct LayerResNode {
  mm::Pnt<f32> unknown00; // Inferred role: pos; original member name unknown.
  mm::Pnt<f32> unknown08; // Inferred role: scl; original member name unknown.
  mm::Pnt<f32> unknown10; // Inferred role: rot; original member name unknown.
  f32 unknown18[4];       // Inferred role: mul color; original member name unknown.
  f32 unknown28[3];       // Inferred role: add color; original member name unknown.
  u16 unknown34;          // Inferred role: key index, set by LayerObjPlace::calcNodePos; original member name unknown.
  u8 unknown36;           // Inferred role: flags; original member name unknown.
  u8 unknown37;           // Inferred role: blend; original member name unknown.
};

static_assert(offsetof(LayerResNode, unknown18) == 0x18, "");
static_assert(offsetof(LayerResNode, unknown28) == 0x28, "");
static_assert(offsetof(LayerResNode, unknown34) == 0x34, "");
static_assert(offsetof(LayerResNode, unknown36) == 0x36, "");
static_assert(sizeof(LayerResNode) == 0x38, "");

} // namespace layer
