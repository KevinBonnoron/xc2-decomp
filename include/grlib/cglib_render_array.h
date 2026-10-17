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

  CGLibTextureBuffer *m_texture;
  CGLibColorBuffer *m_colorBuffers;
  bool m_isResArea;
  u32 m_arrayWidth;
  u32 m_arrayHeight;
  u32 m_sliceNum;
  u32 m_mipmapNum;
};

static_assert(offsetof(CGLibRenderArray, m_texture) == 0x70, "");
static_assert(offsetof(CGLibRenderArray, m_mipmapNum) == 0x90, "");

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

  u32 getFaceBufferNum() const { return m_sliceNum + m_mipmapNum * m_sliceNum; }

  CGLibTextureBuffer *m_texture;
  CGLibColorBuffer *m_colorBuffers;
  bool m_isResArea;
  u32 m_arrayWidth;
  u32 m_arrayHeight;
  u32 m_sliceNum;
  u32 m_mipmapNum;
};

static_assert(offsetof(CGLibRenderArrayCubeMap, m_texture) == 0x70, "");
static_assert(offsetof(CGLibRenderArrayCubeMap, m_mipmapNum) == 0x90, "");

} // namespace grlib
