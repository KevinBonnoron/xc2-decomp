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
  u32 unknown08;         // Inferred role: flags; original member name unknown.
  NVNtexture *unknown10; // Inferred role: nvn texture; original member name unknown.
  u64 unknown18;         // Inferred role: gpu address; original member name unknown.
  void *m_buffer;
  u32 unknown28; // Inferred role: buffer size; original member name unknown.
};

static_assert(offsetof(CGLibDepthBuffer, unknown08) == 0x08, "");
static_assert(offsetof(CGLibDepthBuffer, unknown10) == 0x10, "");
static_assert(offsetof(CGLibDepthBuffer, m_buffer) == 0x20, "");
static_assert(offsetof(CGLibDepthBuffer, unknown28) == 0x28, "");

} // namespace grlib
