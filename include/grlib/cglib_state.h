#pragma once
#include "grlib/cglib_color_ctl.h"
#include "types.h"

namespace grlib {
class CGLibDepthBuffer;
class CGLibRenderTarget;

struct LibMainStateViewPort {
  LibMainStateViewPort(f32 x, f32 y, f32 width, f32 height, f32 minDepth, f32 maxDepth)
      : x(x), y(y), width(width), height(height), minDepth(minDepth), maxDepth(maxDepth) {}

  f32 x;
  f32 y;
  f32 width;
  f32 height;
  f32 minDepth;
  f32 maxDepth;
};

class CGLibState {
public:
  static void setMainFrameBuffer();
  static void setViewport(const LibMainStateViewPort &viewPort);
  static void beginRegisterRenderTarget();
  static void setRegisterRenderTarget(CGLibRenderTarget &renderTarget, GrlMrtType mrt);
  static void setRegisterDepthTarget(CGLibDepthBuffer &depthBuffer);
  static void endRegisterRenderTarget();
};

} // namespace grlib
