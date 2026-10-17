#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibTextureBuffer;

class CGLibRenderTargetBase {
public:
  void setColorInvalidate();

  u8 _00[0x70 - 0x00];
  CGLibTextureBuffer *m_texture;
};

static_assert(offsetof(CGLibRenderTargetBase, m_texture) == 0x70, "");

} // namespace grlib
