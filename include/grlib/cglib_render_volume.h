#pragma once
#include <stddef.h>

#include "grlib/cglib_render_target.h"
#include "grlib/cglib_texture_buffer.h"
#include "types.h"

namespace mm {
struct Col4;
} // namespace mm

namespace grlib {
class CGLibDepthBuffer;

class CGLibColorBuffer;

class CGLibRenderVolume : public CGLibTextureBuffer {
public:
  CGLibRenderVolume();
  ~CGLibRenderVolume();
  void releaseWork();
  void release();
  void releaseTexture();
  void clearTexture(u32 slice, const mm::Col4 &color, GrlClaerMask mask);
  void clearIntTexture(u32 slice, const int *color, GrlClaerMask mask);
  void setRenderTarget(u32 slice);
  void setRenderTarget(u32 slice, CGLibDepthBuffer &depthBuffer);
  void setRenderTarget(u32 slice, CGLibRenderVolume &target);
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
