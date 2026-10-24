#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibDepthBuffer;

class CGLibDepthTarget {
public:
  void setRenderTarget();

  u8 _000[0x120 - 0x000];
  CGLibDepthBuffer *unknown120; // Inferred role: depth buffer; original member name unknown.
};

static_assert(offsetof(CGLibDepthTarget, unknown120) == 0x120, "");

} // namespace grlib
