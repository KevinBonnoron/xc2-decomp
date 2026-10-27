#pragma once
#include <stddef.h>

#include "grlib/cglib_color_buffer.h"
#include "grlib/cglib_texture_buffer.h"
#include "nvn/nvn.h"
#include "types.h"

struct NVNtexture;

namespace grlib {

class CGLibRenderTargetBase : public CGLibTextureBuffer {
public:
  ~CGLibRenderTargetBase() { unknown84 &= ~CGLibColorBuffer::FLAG_INITIALIZED; }
  void setColorInvalidate();

  CGLibTextureBuffer *unknown70; // Inferred role: texture; original member name unknown.
  u8 _78[0x84 - 0x78];
  u32 unknown84;            // Inferred role: color buffer flags; original member name unknown.
  NVNtextureView unknown88; // Inferred role: texture view; original member name unknown.
  NVNtexture *unknownb0;    // Inferred role: nvn texture; original member name unknown.
  bool unknownb8;           // Inferred role: res area; original member name unknown.
  u8 _b9[0xbc - 0xb9];
  u32 unknownbc; // Inferred role: width; original member name unknown.
  u32 unknownc0; // Inferred role: height; original member name unknown.
};

static_assert(offsetof(CGLibRenderTargetBase, unknown70) == 0x70, "");
static_assert(offsetof(CGLibRenderTargetBase, unknown88) == 0x88, "");
static_assert(offsetof(CGLibRenderTargetBase, unknownb0) == 0xb0, "");
static_assert(offsetof(CGLibRenderTargetBase, unknownbc) == 0xbc, "");
static_assert(offsetof(CGLibRenderTargetBase, unknownc0) == 0xc0, "");

} // namespace grlib
