#pragma once
#include "grlib/cglib_render_target_base.h"
#include "grlib/cglib_texture_buffer.h"
#include "types.h"

namespace mm {
struct Col4;
} // namespace mm

enum GrlClaerMask {};

namespace grlib {
class CGLibColorBuffer;
class CGLibDepthBuffer;

class CGLibRenderTarget : public CGLibRenderTargetBase {
public:
  CGLibRenderTarget();
  ~CGLibRenderTarget();
  void release();
  void releaseWork();
  void clearTexture(const mm::Col4 &color, GrlClaerMask mask);
  void clearIntTexture(const int *color, GrlClaerMask mask);
  void setRenderTarget();
  void setRenderTarget(CGLibDepthBuffer &depthBuffer);
  void setRenderTarget(CGLibColorBuffer &colorBuffer);
  void setRenderTarget(CGLibRenderTarget &target1);
  void setRenderTarget(CGLibRenderTarget &target1, CGLibRenderTarget &target2);
  void setRenderTarget(CGLibRenderTarget &target1, CGLibRenderTarget &target2, CGLibRenderTarget &target3);
  void setRenderTarget(CGLibRenderTarget &target1, CGLibRenderTarget &target2, CGLibRenderTarget &target3, CGLibRenderTarget &target4);
  void setRenderTarget(CGLibDepthBuffer &depthBuffer, CGLibRenderTarget &target1);
  void setRenderTarget(CGLibDepthBuffer &depthBuffer, CGLibRenderTarget &target1, CGLibRenderTarget &target2);
  void releaseTexture();

  u16 unknownc4; // Inferred role: mrt state; original member name unknown.
  u8 _c6[0x128 - 0xc6];
  CGLibTextureBuffer unknown128[6]; // Inferred role: mrt textures; original member name unknown.
};

static_assert(sizeof(CGLibRenderTarget) == 0x3c8, "");

} // namespace grlib
