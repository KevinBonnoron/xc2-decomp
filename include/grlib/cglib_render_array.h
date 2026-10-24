#pragma once
#include <stddef.h>

#include "grlib/cglib_render_target.h"
#include "grlib/cglib_texture_buffer.h"
#include "types.h"

namespace mm {
struct Col4;
} // namespace mm

namespace grlib {

class CGLibColorBuffer;
class CGLibDepthBuffer;

enum GrlCubeMapFace {
  GRL_CUBE_MAP_FACE_POSITIVE_X,
  GRL_CUBE_MAP_FACE_NEGATIVE_X,
  GRL_CUBE_MAP_FACE_POSITIVE_Y,
  GRL_CUBE_MAP_FACE_NEGATIVE_Y,
  GRL_CUBE_MAP_FACE_POSITIVE_Z,
  GRL_CUBE_MAP_FACE_NEGATIVE_Z,
  GRL_CUBE_MAP_FACE_NUM,
};

class CGLibRenderArray : public CGLibTextureBuffer {
public:
  CGLibRenderArray();
  ~CGLibRenderArray();
  void releaseWork();
  void release();
  void setTextureInfo(f32 width, f32 height, u32 slice, bool isMipmap, GrlSurfaceFormat format, bool isResArea, u32 resArea);
  void releaseTexture();
  void clearTexture(u32 slice, const mm::Col4 &color, GrlClaerMask mask);
  CGLibColorBuffer *getColorBuffer(u32 slice);
  void clearMipmapTexture(u32 slice, u32 mipmap, const mm::Col4 &color, GrlClaerMask mask);
  CGLibColorBuffer *getMipmapColorBuffer(u32 slice, u32 mipmap);
  void clearIntTexture(u32 slice, const int *color, GrlClaerMask mask);
  void clearIntMipmapTexture(u32 slice, u32 mipmap, const int *color, GrlClaerMask mask);
  void setRenderTarget(u32 slice);
  void setRenderTarget(u32 slice, CGLibColorBuffer &colorBuffer);
  void setRenderTarget(u32 slice, CGLibDepthBuffer &depthBuffer);
  void setMipmapRenderTarget(u32 slice, u32 mipmap);
  void setMipmapRenderTarget(u32 slice, u32 mipmap, CGLibColorBuffer &colorBuffer);
  void setMipmapRenderTarget(u32 slice, u32 mipmap, CGLibDepthBuffer &depthBuffer);
  const CGLibColorBuffer *getColorBuffer(u32 slice) const;
  const CGLibColorBuffer *getMipmapColorBuffer(u32 slice, u32 mipmap) const;

  CGLibTextureBuffer *unknown70; // Inferred role: texture; original member name unknown.
  CGLibColorBuffer *unknown78;   // Inferred role: color buffers; original member name unknown.
  bool unknown80;                // Inferred role: res area; original member name unknown.
  u32 unknown84;                 // Inferred role: array width; original member name unknown.
  u32 unknown88;                 // Inferred role: array height; original member name unknown.
  u32 unknown8c;                 // Inferred role: slice num; original member name unknown.
  u32 unknown90;                 // Inferred role: mipmap num; original member name unknown.
};

static_assert(offsetof(CGLibRenderArray, unknown70) == 0x70, "");
static_assert(offsetof(CGLibRenderArray, unknown90) == 0x90, "");

class CGLibRenderArrayCubeMap : public CGLibTextureBuffer {
public:
  CGLibRenderArrayCubeMap();
  ~CGLibRenderArrayCubeMap();
  void releaseWork();
  void release();
  void setTextureInfo(f32 width, f32 height, u32 slice, bool isMipmap, GrlSurfaceFormat format, bool isResArea, u32 resArea);
  void releaseTexture();
  void clearTexture(GrlCubeMapFace face, u32 slice, const mm::Col4 &color, GrlClaerMask mask);
  CGLibColorBuffer *getColorBuffer(GrlCubeMapFace face, u32 slice);
  void clearMipmapTexture(GrlCubeMapFace face, u32 slice, u32 mipmap, const mm::Col4 &color, GrlClaerMask mask);
  CGLibColorBuffer *getMipmapColorBuffer(GrlCubeMapFace face, u32 slice, u32 mipmap);
  void clearIntTexture(GrlCubeMapFace face, u32 slice, const int *color, GrlClaerMask mask);
  void clearIntMipmapTexture(GrlCubeMapFace face, u32 slice, u32 mipmap, const int *color, GrlClaerMask mask);
  void setRenderTarget(GrlCubeMapFace face, u32 slice);
  void setRenderTarget(GrlCubeMapFace face, u32 slice, CGLibColorBuffer &colorBuffer);
  void setRenderTarget(GrlCubeMapFace face, u32 slice, CGLibDepthBuffer &depthBuffer);
  void setMipmapRenderTarget(GrlCubeMapFace face, u32 slice, u32 mipmap);
  void setMipmapRenderTarget(GrlCubeMapFace face, u32 slice, u32 mipmap, CGLibColorBuffer &colorBuffer);
  void setMipmapRenderTarget(GrlCubeMapFace face, u32 slice, u32 mipmap, CGLibDepthBuffer &depthBuffer);
  const CGLibColorBuffer *getColorBuffer(GrlCubeMapFace face, u32 slice) const;
  const CGLibColorBuffer *getMipmapColorBuffer(GrlCubeMapFace face, u32 slice, u32 mipmap) const;

  u32 getFaceBufferNum() const { return unknown8c + unknown90 * unknown8c; }

  CGLibTextureBuffer *unknown70; // Inferred role: texture; original member name unknown.
  CGLibColorBuffer *unknown78;   // Inferred role: color buffers; original member name unknown.
  bool unknown80;                // Inferred role: res area; original member name unknown.
  u32 unknown84;                 // Inferred role: array width; original member name unknown.
  u32 unknown88;                 // Inferred role: array height; original member name unknown.
  u32 unknown8c;                 // Inferred role: slice num; original member name unknown.
  u32 unknown90;                 // Inferred role: mipmap num; original member name unknown.
};

static_assert(offsetof(CGLibRenderArrayCubeMap, unknown70) == 0x70, "");
static_assert(offsetof(CGLibRenderArrayCubeMap, unknown90) == 0x90, "");

} // namespace grlib
