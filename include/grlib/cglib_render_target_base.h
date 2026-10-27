#pragma once
#include <stddef.h>

#include "grlib/cglib_color_buffer.h"
#include "grlib/cglib_texture_buffer.h"
#include "types.h"

namespace grlib {

class CGLibRenderTargetBase : public CGLibTextureBuffer {
public:
  ~CGLibRenderTargetBase() { unknown78.release(); }
  void setColorInvalidate();

  CGLibTextureBuffer *unknown70; // Inferred role: texture; original member name unknown.
  CGLibColorBuffer unknown78;    // Inferred role: color buffer; original member name unknown.
  bool unknownb8;                // Inferred role: res area; original member name unknown.
  u8 _b9[0xbc - 0xb9];
  u32 unknownbc; // Inferred role: width; original member name unknown.
  u32 unknownc0; // Inferred role: height; original member name unknown.
};

static_assert(offsetof(CGLibRenderTargetBase, unknown70) == 0x70, "");
static_assert(offsetof(CGLibRenderTargetBase, unknown78) == 0x78, "");
static_assert(offsetof(CGLibRenderTargetBase, unknownb8) == 0xb8, "");
static_assert(offsetof(CGLibRenderTargetBase, unknownbc) == 0xbc, "");
static_assert(offsetof(CGLibRenderTargetBase, unknownc0) == 0xc0, "");

} // namespace grlib
