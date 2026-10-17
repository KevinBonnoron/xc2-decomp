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
  u8 _78[0xbc - 0x78];
  u32 m_width;
  u32 m_height;
};

static_assert(offsetof(CGLibRenderTargetBase, m_texture) == 0x70, "");
static_assert(offsetof(CGLibRenderTargetBase, m_width) == 0xbc, "");
static_assert(offsetof(CGLibRenderTargetBase, m_height) == 0xc0, "");

} // namespace grlib
