#pragma once
#include <stddef.h>

#include "grlib/cglib_color_buffer.h"
#include "grlib/cglib_texture_buffer.h"
#include "types.h"

namespace grlib {

class CGLibRenderTarget1D : public CGLibTextureBuffer {
public:
  CGLibRenderTarget1D();
  ~CGLibRenderTarget1D();
  void releaseWork();

  CGLibTextureBuffer *unknown70; // Inferred role: texture; original member name unknown.
  CGLibColorBuffer unknown78;    // Inferred role: color buffer; original member name unknown.
  u32 unknownb8;                 // Inferred role: width; original member name unknown.
  bool unknownbc;                // Inferred role: res area; original member name unknown.
};

static_assert(offsetof(CGLibRenderTarget1D, unknown70) == 0x70, "");
static_assert(sizeof(CGLibRenderTarget1D) == 0xc0, "");

} // namespace grlib
