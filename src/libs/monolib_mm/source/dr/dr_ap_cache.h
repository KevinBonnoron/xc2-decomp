#pragma once
#include <stddef.h>

#include "grlib/cglib_texture_buffer.h"
#include "types.h"

namespace grlib {
class CGLibDecShader;
class CGLibDecShdExtTbl;
class CGLibSampler;
} // namespace grlib

namespace ml {
class DrResFetch;

enum DrApCullType {
  DR_AP_CULL_TYPE_UNKNOWN_0, // Inferred role: back; original name unknown.
  DR_AP_CULL_TYPE_UNKNOWN_1, // Inferred role: front; original name unknown.
  DR_AP_CULL_TYPE_UNKNOWN_2, // Inferred role: off; original name unknown.
  DR_AP_CULL_TYPE_UNKNOWN_3, // Inferred role: disp off; original name unknown.
  DR_AP_CULL_TYPE_UNKNOWN_4,
};

class DrAPCache {
public:
  static DrAPCache *s_pIns;
  static GrlSurfaceFormat TEXTYPE_RGBA_8;
  static const GrlSurfaceFormat TEXTYPE_HALF_X1; // Read-only data in the game (0x7100f84614).

  DrAPCache();
  virtual ~DrAPCache() {}
  void createSampler();
  void begin();
  void releaseSampler();
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
  void setMrtGBuffRender(u32 mask, u32 layout);
  void endGBuffRender();
  void setRefractionRender();
  void endRefractionRender();
  void setupCulling(DrApCullType cullType);
  void setupDepthStencil(int ref, int stencil, int depthWrite, int depthTest);
  void setupAlphaBlend(int blend);
  void setupMrtAlphaBlend(int blend);
  void setupMrtAlphaBlend(int blend, int mrt);
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

  s32 unknown08;          // Inferred role: alpha blend; original member name unknown.
  s32 unknown0c;          // Inferred role: mrt alpha blend; original member name unknown.
  DrApCullType unknown10; // Inferred role: cull type; original member name unknown.
  s32 unknown14;          // Inferred role: stencil ref; original member name unknown.
  s32 unknown18;          // Inferred role: stencil type; original member name unknown.
  s32 unknown1c;          // Inferred role: depth write; original member name unknown.
  u32 unknown20;          // Inferred role: gbuff mask; original member name unknown.
  s32 unknown24;          // Inferred role: depth test; original member name unknown.
  s32 unknown28;          // Inferred role: depth compare; original member name unknown.
  u8 _2c[0x30 - 0x2c];
  grlib::CGLibSampler *unknown30; // Inferred role: samplers; original member name unknown.
  u16 unknown38;                  // Inferred role: clamp u; original member name unknown.
  u16 unknown3a;                  // Inferred role: clamp v; original member name unknown.
  u16 m_filter;
  u16 m_mipMapOn;
  u16 unknown40; // Inferred role: sampler id; original member name unknown.
  u16 unknown42; // Inferred role: sampler type; original member name unknown.
};

static_assert(offsetof(DrAPCache, unknown08) == 0x08, "");
static_assert(offsetof(DrAPCache, unknown10) == 0x10, "");
static_assert(offsetof(DrAPCache, unknown20) == 0x20, "");
static_assert(offsetof(DrAPCache, unknown24) == 0x24, "");
static_assert(offsetof(DrAPCache, unknown30) == 0x30, "");
static_assert(offsetof(DrAPCache, unknown38) == 0x38, "");
static_assert(offsetof(DrAPCache, unknown40) == 0x40, "");
static_assert(offsetof(DrAPCache, unknown42) == 0x42, "");

} // namespace ml
