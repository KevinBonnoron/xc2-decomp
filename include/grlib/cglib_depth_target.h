#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibDepthBuffer;

class CGLibDepthTarget {
public:
  void setRenderTarget();

  u8 _000[0x120 - 0x000];
  CGLibDepthBuffer *m_depthBuffer;
};

static_assert(offsetof(CGLibDepthTarget, m_depthBuffer) == 0x120, "");

} // namespace grlib
