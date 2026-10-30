#pragma once
#include <stddef.h>

#include "grlib/cglib_color_buffer.h"
#include "grlib/cglib_color_ctl.h"
#include "grlib/cglib_render_array.h"
#include "grlib/cglib_render_target.h"
#include "grlib/cglib_texture_buffer.h"
#include "types.h"

namespace mm {
struct Col4;
} // namespace mm

namespace grlib {
class CGLibDepthBuffer;

class CGLibRenderCubeMap : public CGLibTextureBuffer {
public:
  CGLibRenderCubeMap();
  ~CGLibRenderCubeMap();
  void releaseWork();
  void release();
  void releaseTexture();
  void clearTexture(GrlCubeMapFace face, const mm::Col4 &color, GrlClaerMask mask);
  void clearIntTexture(GrlCubeMapFace face, const int *color, GrlClaerMask mask);
  void setTextureInfo(f32 width, f32 height, GrlSurfaceFormat format, bool isResArea, u32 resArea);
  void setRegisterRenderTarget(GrlCubeMapFace face, GrlMrtType mrt);
  void setRenderTarget(GrlCubeMapFace face);
  void setRenderTarget(GrlCubeMapFace face, CGLibDepthBuffer &depthBuffer);

  CGLibTextureBuffer *unknown70; // Inferred role: texture; original member name unknown.
  CGLibColorBuffer unknown78[6]; // Inferred role: face color buffers; original member name unknown.
  bool unknown1f8;               // Inferred role: res area; original member name unknown.
  f32 unknown1fc;                // Inferred role: width; original member name unknown.
  f32 unknown200;                // Inferred role: height; original member name unknown.
};

static_assert(offsetof(CGLibRenderCubeMap, unknown70) == 0x70, "");
static_assert(sizeof(CGLibRenderCubeMap) == 0x208, "");

class CGLibRenderCubeMapMipMap : public CGLibTextureBuffer {
public:
  CGLibRenderCubeMapMipMap();
  ~CGLibRenderCubeMapMipMap();
  void releaseWork();
  void release();
  void releaseTexture();
  void clearTexture(GrlCubeMapFace face, u32 mipmap, const mm::Col4 &color, GrlClaerMask mask);
  void clearIntTexture(GrlCubeMapFace face, u32 mipmap, const int *color, GrlClaerMask mask);
  CGLibColorBuffer *getColorBuffer(GrlCubeMapFace face, u32 mipmap);
  const CGLibColorBuffer *getColorBuffer(GrlCubeMapFace face, u32 mipmap) const;
  void setRegisterRenderTarget(GrlCubeMapFace face, u32 mipmap, GrlMrtType mrt);
  void setRenderTarget(GrlCubeMapFace face, u32 mipmap);
  void setRenderTarget(GrlCubeMapFace face, u32 mipmap, CGLibDepthBuffer &depthBuffer);

  CGLibTextureBuffer *unknown70;     // Inferred role: texture; original member name unknown.
  CGLibColorBuffer unknown78[6][16]; // Inferred role: face mipmap color buffers; original member name unknown.
  bool unknown1878;                  // Inferred role: res area; original member name unknown.
  u32 unknown187c;                   // Inferred role: width; original member name unknown.
  u32 unknown1880;                   // Inferred role: height; original member name unknown.
  u32 unknown1884;                   // Inferred role: mipmap num; original member name unknown.
};

static_assert(offsetof(CGLibRenderCubeMapMipMap, unknown70) == 0x70, "");
static_assert(sizeof(CGLibRenderCubeMapMipMap) == 0x1888, "");

} // namespace grlib
