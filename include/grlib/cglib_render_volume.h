#pragma once
#include <stddef.h>

#include "grlib/cglib_texture_buffer.h"
#include "types.h"

namespace grlib {
class CGLibColorBuffer;

class CGLibRenderVolume : public CGLibTextureBuffer {
public:
  CGLibRenderVolume();
  ~CGLibRenderVolume();
  void releaseWork();
  void setTextureInfo(f32 width, f32 height, f32 depth, GrlSurfaceFormat format, bool isResArea, u32 resArea);

  CGLibTextureBuffer *unknown70; // Inferred role: texture; original member name unknown.
  CGLibColorBuffer *unknown78;   // Inferred role: color buffers; original member name unknown.
  bool unknown80;                // Inferred role: res area; original member name unknown.
  u32 unknown84;                 // Inferred role: width; original member name unknown.
  u32 unknown88;                 // Inferred role: height; original member name unknown.
  u32 unknown8c;                 // Inferred role: depth; original member name unknown.
};

static_assert(offsetof(CGLibRenderVolume, unknown70) == 0x70, "");
static_assert(sizeof(CGLibRenderVolume) == 0x90, "");

} // namespace grlib
