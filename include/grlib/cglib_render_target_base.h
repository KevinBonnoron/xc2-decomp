#pragma once
#include <stddef.h>

#include "nvn/nvn.h"
#include "types.h"

struct NVNtexture;

namespace grlib {
class CGLibTextureBuffer;

class CGLibRenderTargetBase {
public:
  void setColorInvalidate();

  u8 _00[0x70 - 0x00];
  CGLibTextureBuffer *m_texture;
  u8 _78[0x88 - 0x78];
  NVNtextureView m_textureView;
  NVNtexture *m_nvnTexture;
  u8 _b8[0xbc - 0xb8];
  u32 m_width;
  u32 m_height;
};

static_assert(offsetof(CGLibRenderTargetBase, m_texture) == 0x70, "");
static_assert(offsetof(CGLibRenderTargetBase, m_textureView) == 0x88, "");
static_assert(offsetof(CGLibRenderTargetBase, m_nvnTexture) == 0xb0, "");
static_assert(offsetof(CGLibRenderTargetBase, m_width) == 0xbc, "");
static_assert(offsetof(CGLibRenderTargetBase, m_height) == 0xc0, "");

} // namespace grlib
