#pragma once
#include "grlib/cglib_color_ctl.h"
#include "types.h"

namespace grlib {
class CGLibColorBuffer;
class CGLibDepthBuffer;
class CGLibDepthTarget;
class CGLibRenderTarget;

struct LibMainStateViewPort {
  LibMainStateViewPort(f32 x, f32 y, f32 width, f32 height, f32 minDepth, f32 maxDepth) : unknown00(x), unknown04(y), unknown08(width), unknown0c(height), unknown10(minDepth), unknown14(maxDepth) {}

  f32 unknown00; // Inferred role: x; original member name unknown.
  f32 unknown04; // Inferred role: y; original member name unknown.
  f32 unknown08; // Inferred role: width; original member name unknown.
  f32 unknown0c; // Inferred role: height; original member name unknown.
  f32 unknown10; // Inferred role: min depth; original member name unknown.
  f32 unknown14; // Inferred role: max depth; original member name unknown.
};

class CGLibState {
public:
  static void setMainFrameBuffer();
  static void setupInitialize();
  static void setViewport(const LibMainStateViewPort &viewPort);
  static void setOnlyViewport(const LibMainStateViewPort &viewPort);
  static void setOnlyScissor(const LibMainStateViewPort &viewPort);
  static void beginRegisterRenderTarget();
  static void setRegisterRenderTarget(CGLibColorBuffer &colorBuffer, GrlMrtType mrt);
  static void setRegisterRenderTarget(CGLibRenderTarget &renderTarget, GrlMrtType mrt);
  static void setRegisterDepthTarget(CGLibDepthBuffer &depthBuffer);
  static void endRegisterRenderTarget();
  static CGLibRenderTarget *getMainRenderTarget();
  static CGLibDepthTarget *getMainDepthTarget();
  static LibMainStateViewPort *getDefViewPort();
};

} // namespace grlib
