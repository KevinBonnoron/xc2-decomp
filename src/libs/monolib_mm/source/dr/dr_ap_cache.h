#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibDecShader;
class CGLibDecShdExtTbl;
class CGLibSampler;
class CGLibTextureBuffer;
} // namespace grlib

namespace ml {
class DrResFetch;

enum DrApCullType {
  DR_AP_CULL_TYPE_BACK,
  DR_AP_CULL_TYPE_FRONT,
  DR_AP_CULL_TYPE_OFF,
  DR_AP_CULL_TYPE_DISP_OFF,
};

class DrAPCache {
public:
  void begin();
  u16 getSamplerID();
  void depthBegin();
  void shadowBegin();
  void beginZRender();
  void endZRender();
  void beginThicknessRenderFirst();
  void endThicknessRenderFirst();
  void beginThicknessRenderSecond();
  void endThicknessRenderSecond();
  void beginMdlZRender();
  void endMdlZRender();
  void setGBuffRender(u32 mask);
  void endGBuffRender();
  void setRefractionRender();
  void endRefractionRender();
  void setupCulling(DrApCullType cullType);
  void beginTexSampling(int clamp, int filter);
  void begin3DTextureSampling();
  void begin3DTexturePointSampling();
  void begin3DTextureWarpSampling();
  void begin3DTextureWarpPointSampling();
  void beginCubeTextureSampling(bool isArray);
  void beginCubeTexturePointSampling(bool isArray);
  void beginDepthCompare();
  void beginBorderWhite();
  void beginBorderBlack();
  void beginBorderDepthMax();
  void beginBorderDepthMinusMax();
  void texSampClamping(int clampU, int clampV);
  void setMipMapOn(const grlib::CGLibTextureBuffer &texture);
  void setupShader(grlib::CGLibDecShader *shader, DrResFetch *fetch);
  void setupShader(grlib::CGLibDecShdExtTbl *shader, DrResFetch *fetch);
  void setTexture(const grlib::CGLibTextureBuffer &texture, u32 location);
  void setTexture(const grlib::CGLibTextureBuffer &texture, const grlib::CGLibSampler &sampler, u32 location);

  u8 _00[0x08 - 0x00];
  s32 m_alphaBlend;
  s32 m_mrtAlphaBlend;
  DrApCullType m_cullType;
  s32 m_stencilRef;
  s32 m_stencilType;
  s32 m_depthWrite;
  u32 m_gbuffMask;
  s32 m_depthTest;
  u8 _28[0x30 - 0x28];
  grlib::CGLibSampler *m_samplers;
  u16 m_clampU;
  u16 m_clampV;
  u16 m_filter;
  u16 m_mipMap;
  u16 m_samplerID;
  u16 m_samplerType;
};

static_assert(offsetof(DrAPCache, m_alphaBlend) == 0x08, "");
static_assert(offsetof(DrAPCache, m_cullType) == 0x10, "");
static_assert(offsetof(DrAPCache, m_gbuffMask) == 0x20, "");
static_assert(offsetof(DrAPCache, m_depthTest) == 0x24, "");
static_assert(offsetof(DrAPCache, m_samplers) == 0x30, "");
static_assert(offsetof(DrAPCache, m_clampU) == 0x38, "");
static_assert(offsetof(DrAPCache, m_samplerID) == 0x40, "");
static_assert(offsetof(DrAPCache, m_samplerType) == 0x42, "");

} // namespace ml
