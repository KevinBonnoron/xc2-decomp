#pragma once
#include "grlib/cglib_render_target_base.h"
#include "types.h"

namespace mm {
struct Col4;
} // namespace mm

enum GrlClaerMask {};

namespace grlib {
class CGLibDepthBuffer;

class CGLibRenderTarget : public CGLibRenderTargetBase {
public:
  void clearTexture(const mm::Col4 &color, GrlClaerMask mask);
  void setRenderTarget();
  void setRenderTarget(CGLibDepthBuffer &depthBuffer);

  u8 _c8[0x3c8 - 0xc8];
};

static_assert(sizeof(CGLibRenderTarget) == 0x3c8, "");

} // namespace grlib
