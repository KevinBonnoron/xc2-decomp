#pragma once
#include <stddef.h>

#include "grlib/cglib_texture_buffer.h"
#include "nvn/nvn.h"
#include "types.h"

struct NVNtexture;

namespace grlib {

class CGLibColorBuffer {
public:
  enum Flag {
    FLAG_INITIALIZED = 1 << 0,
  };

  void release();
  u16 getWidth() const;
  u16 getHeight() const;
  CGLibColorBuffer();
  ~CGLibColorBuffer();
  u16 getSlice() const;
  GrlSurfaceFormat getFormat() const;
  u16 getMipmap() const;
  u32 getImageSize() const;
  u32 get1PixelImageSize() const;
  bool isInitialized() const;

  GrlSurfaceFormat m_format;
  u16 m_width;
  u16 m_height;
  u16 m_mipmap;
  u16 m_slice;
  u32 m_flags;
  NVNtextureView m_textureView;
  NVNtexture *m_nvnTexture;
};

static_assert(offsetof(CGLibColorBuffer, m_mipmap) == 0x08, "");
static_assert(offsetof(CGLibColorBuffer, m_flags) == 0x0c, "");
static_assert(offsetof(CGLibColorBuffer, m_textureView) == 0x10, "");
static_assert(offsetof(CGLibColorBuffer, m_nvnTexture) == 0x38, "");

} // namespace grlib
