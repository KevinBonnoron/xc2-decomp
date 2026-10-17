#pragma once
#include <stddef.h>

#include "mm_math/mm_vec2.h"
#include "types.h"

namespace layer {

struct LayerResNode {
  mm::Vec2 pos;
  mm::Vec2 scl;
  mm::Vec2 rot;
  f32 mulColor[4];
  f32 addColor[3];
  u8 _34[0x36 - 0x34];
  u8 flags;
  u8 blend;
};

static_assert(offsetof(LayerResNode, mulColor) == 0x18, "");
static_assert(offsetof(LayerResNode, addColor) == 0x28, "");
static_assert(offsetof(LayerResNode, flags) == 0x36, "");
static_assert(sizeof(LayerResNode) == 0x38, "");

} // namespace layer
