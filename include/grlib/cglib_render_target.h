#pragma once
#include <stddef.h>

#include "grlib/cglib_color_buffer.h"
#include "grlib/cglib_render_target_base.h"
#include "grlib/cglib_texture_buffer.h"
#include "types.h"

namespace mm {
struct Col4;
} // namespace mm

enum GrlClaerMask {};

namespace grlib {
class CGLibDepthBuffer;

class CGLibRenderTarget : public CGLibRenderTargetBase {
public:
  CGLibRenderTarget();
  ~CGLibRenderTarget();
  void release();
  void releaseWork();
  void clearTexture(const mm::Col4 &color, GrlClaerMask mask);
  void clearIntTexture(const int *color, GrlClaerMask mask);
  void setTextureInfo(f32 width, f32 height, GrlSurfaceFormat format, bool isResArea, u32 resArea);
  void setTextureInfo(CGLibTextureBuffer &texture);
  void setRenderTarget();
  void setRenderTarget(CGLibDepthBuffer &depthBuffer);
  void setRenderTarget(CGLibColorBuffer &colorBuffer);
  void setRenderTarget(CGLibRenderTarget &target1);
  void setRenderTarget(CGLibRenderTarget &target1, CGLibRenderTarget &target2);
  void setRenderTarget(CGLibRenderTarget &target1, CGLibRenderTarget &target2, CGLibRenderTarget &target3);
  void setRenderTarget(CGLibRenderTarget &target1, CGLibRenderTarget &target2, CGLibRenderTarget &target3, CGLibRenderTarget &target4);
  void setRenderTarget(CGLibDepthBuffer &depthBuffer, CGLibRenderTarget &target1);
  void setRenderTarget(CGLibDepthBuffer &depthBuffer, CGLibRenderTarget &target1, CGLibRenderTarget &target2);
  void setRenderTargetImpl(CGLibRenderTarget **targets, u64 count, CGLibDepthBuffer *depthBuffer);
  void releaseTexture();

  // Inferred role: key of a cached resident-area texture; original type name unknown.
  struct unknown001 {
    u16 unknown00; // Inferred role: width; original member name unknown.
    u16 unknown02; // Inferred role: height; original member name unknown.
    s16 unknown04; // Inferred role: age since last use; original member name unknown.
    u8 _06[0x08 - 0x06];
    u32 unknown08;              // Inferred role: res area; original member name unknown.
    GrlSurfaceFormat unknown0c; // Inferred role: format; original member name unknown.
  };

  CGLibColorBuffer unknown78; // Inferred role: color buffer; original member name unknown.
  bool unknownb8;             // Inferred role: res area; original member name unknown.
  u8 _b9[0xbc - 0xb9];
  u32 unknownbc;                    // Inferred role: width; original member name unknown.
  u32 unknownc0;                    // Inferred role: height; original member name unknown.
  u16 unknownc4;                    // Inferred role: mrt state; original member name unknown.
  unknown001 unknownc8[6];          // Inferred role: cached texture keys; original member name unknown.
  CGLibTextureBuffer unknown128[6]; // Inferred role: mrt textures; original member name unknown.
};

static_assert(sizeof(CGLibRenderTarget::unknown001) == 0x10, "");
static_assert(offsetof(CGLibRenderTarget, unknown78) == 0x78, "");
static_assert(offsetof(CGLibRenderTarget, unknownb8) == 0xb8, "");
static_assert(offsetof(CGLibRenderTarget, unknownbc) == 0xbc, "");
static_assert(offsetof(CGLibRenderTarget, unknownc0) == 0xc0, "");
static_assert(offsetof(CGLibRenderTarget, unknownc4) == 0xc4, "");
static_assert(offsetof(CGLibRenderTarget, unknownc8) == 0xc8, "");
static_assert(offsetof(CGLibRenderTarget, unknown128) == 0x128, "");
static_assert(sizeof(CGLibRenderTarget) == 0x3c8, "");

} // namespace grlib
