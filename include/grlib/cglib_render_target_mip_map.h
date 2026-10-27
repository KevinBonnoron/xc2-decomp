#pragma once
#include <stddef.h>

#include "grlib/cglib_color_buffer.h"
#include "grlib/cglib_render_target.h"
#include "grlib/cglib_texture_buffer.h"
#include "types.h"

namespace mm {
struct Col4;
} // namespace mm

namespace grlib {
class CGLibDepthBuffer;

class CGLibRenderTargetMipMap : public CGLibTextureBuffer {
public:
  CGLibRenderTargetMipMap();
  ~CGLibRenderTargetMipMap();
  void releaseWork();
  void release();
  void releaseTexture();
  void clearTexture(u32 mipmap, const mm::Col4 &color, GrlClaerMask mask);
  void clearIntTexture(u32 mipmap, const int *color, GrlClaerMask mask);
  void setRenderTarget(u32 mipmap);
  void setRenderTarget(u32 mipmap, CGLibDepthBuffer &depthBuffer);

  CGLibTextureBuffer *unknown70;  // Inferred role: texture; original member name unknown.
  CGLibColorBuffer unknown78[16]; // Inferred role: mipmap color buffers; original member name unknown.
  bool unknown478;                // Inferred role: res area; original member name unknown.
  u32 unknown47c;                 // Inferred role: width; original member name unknown.
  u32 unknown480;                 // Inferred role: height; original member name unknown.
  u32 unknown484;                 // Inferred role: mipmap num; original member name unknown.
};

static_assert(offsetof(CGLibRenderTargetMipMap, unknown70) == 0x70, "");
static_assert(sizeof(CGLibRenderTargetMipMap) == 0x488, "");

} // namespace grlib
