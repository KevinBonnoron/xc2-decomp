#pragma once
#include <stddef.h>

#include "types.h"

struct NVNtexture;

namespace grlib {

class CGLibDepthBuffer {
public:
  void invalidate();

  u8 _00[0x10 - 0x00];
  NVNtexture *m_nvnTexture;
};

static_assert(offsetof(CGLibDepthBuffer, m_nvnTexture) == 0x10, "");

} // namespace grlib
