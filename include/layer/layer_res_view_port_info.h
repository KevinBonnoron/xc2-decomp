#pragma once
#include <stddef.h>

#include "mm_math/mm_col4.h"
#include "mm_math/mm_rect.h"
#include "types.h"

namespace grlib {
class CGLibDblUniformBlock;
class CGLibRenderTarget;
} // namespace grlib

namespace layer {

struct LayerResViewPortInfo {
  mm::Rect<f32> unknown00;                // Inferred role: view port; original member name unknown.
  grlib::CGLibRenderTarget *unknown10;    // Inferred role: render target; original member name unknown.
  grlib::CGLibDblUniformBlock *unknown18; // Inferred role: view port uniform; original member name unknown.
  mm::Col4 unknown20;                     // Inferred role: clear color; original member name unknown.
  u32 unknown30;                          // Inferred role: state flags; original member name unknown.
};

static_assert(offsetof(LayerResViewPortInfo, unknown10) == 0x10, "");
static_assert(offsetof(LayerResViewPortInfo, unknown18) == 0x18, "");
static_assert(offsetof(LayerResViewPortInfo, unknown20) == 0x20, "");
static_assert(offsetof(LayerResViewPortInfo, unknown30) == 0x30, "");

} // namespace layer
