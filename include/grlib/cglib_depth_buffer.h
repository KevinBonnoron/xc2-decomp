#pragma once
#include <stddef.h>

#include "grlib/cglib_texture_buffer.h"
#include "types.h"

struct NVNtexture;

namespace grlib {

class CGLibDepthBuffer {
public:
  enum Flag {
    FLAG_INITIALIZED = 1 << 0,
    FLAG_OWN_BUFFER = 1 << 1,
  };

  void delayRelease();
  CGLibDepthBuffer();
  ~CGLibDepthBuffer();
  void release();
  u16 getWidth() const;
  u16 getHeight() const;
  GrlSurfaceFormat getFormat() const;
  u32 getImageSize() const;
  u32 get1PixelImageSize() const;
  void invalidate();
  bool isInitialized() const;

  GrlSurfaceFormat m_format;
  u16 m_width;
  u16 m_height;
  u32 m_flags;
  NVNtexture *m_nvnTexture;
  u64 m_gpuAddress;
  void *m_buffer;
  u32 m_bufferSize;
};

static_assert(offsetof(CGLibDepthBuffer, m_flags) == 0x08, "");
static_assert(offsetof(CGLibDepthBuffer, m_nvnTexture) == 0x10, "");
static_assert(offsetof(CGLibDepthBuffer, m_buffer) == 0x20, "");
static_assert(offsetof(CGLibDepthBuffer, m_bufferSize) == 0x28, "");

} // namespace grlib
