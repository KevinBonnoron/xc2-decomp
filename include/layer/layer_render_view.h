#pragma once
#include <stddef.h>

#include "types.h"

namespace layer {

struct LayerResViewPortInfo;

// Partial layout; the original member names and the size are unknown.
struct LayerRenderView {
  u8 _00[0x08];
  LayerResViewPortInfo *unknown08; // Inferred role: view port info; original member name unknown.
};

static_assert(offsetof(LayerRenderView, unknown08) == 0x08, "");

} // namespace layer
