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
  CGLibTextureBuffer *unknown70; // Inferred role: texture; original member name unknown.
  u8 _78[0x88 - 0x78];
  NVNtextureView unknown88; // Inferred role: texture view; original member name unknown.
  NVNtexture *unknownb0;    // Inferred role: nvn texture; original member name unknown.
  u8 _b8[0xbc - 0xb8];
  u32 unknownbc; // Inferred role: width; original member name unknown.
  u32 unknownc0; // Inferred role: height; original member name unknown.
};

static_assert(offsetof(CGLibRenderTargetBase, unknown70) == 0x70, "");
static_assert(offsetof(CGLibRenderTargetBase, unknown88) == 0x88, "");
static_assert(offsetof(CGLibRenderTargetBase, unknownb0) == 0xb0, "");
static_assert(offsetof(CGLibRenderTargetBase, unknownbc) == 0xbc, "");
static_assert(offsetof(CGLibRenderTargetBase, unknownc0) == 0xc0, "");

} // namespace grlib
