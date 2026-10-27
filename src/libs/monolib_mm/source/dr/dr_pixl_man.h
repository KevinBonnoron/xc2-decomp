#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibDepthTarget;
class CGLibRenderTarget;
class CGLibTextureBuffer;
} // namespace grlib

namespace ml {
class DrMan;
class DrPixlDeferred;
class DrPixlOccQuery;
class DrPixlPostMan;
class DrPixlRenderTarget;
class DrPixlShadowCacheMan;
class DrPixlShadowMan;

struct wkPixlManRes {
  DrPixlRenderTarget *unknown00[19][2]; // Inferred role: pixl objs; original member name unknown.
  DrPixlRenderTarget *unknown130;       // Inferred role: color buff; original member name unknown.
  DrPixlRenderTarget *unknown138;       // Inferred role: active color buff; original member name unknown.
  DrPixlRenderTarget *unknown140;       // Inferred role: hdr buff; original member name unknown.
  DrPixlRenderTarget *unknown148;       // Inferred role: back face depth texture; original member name unknown.
  u8 _150[0x170 - 0x150];
  DrPixlDeferred *unknown170;  // Inferred role: deferred; original member name unknown.
  DrPixlShadowMan *unknown178; // Inferred role: shadow man; original member name unknown.
  DrPixlPostMan *unknown180;   // Inferred role: post man; original member name unknown.
  u8 _188[0x194 - 0x188];
  f32 unknown194; // Inferred role: tone ave min; original member name unknown.
  f32 unknown198; // Inferred role: tone ave max; original member name unknown.
  u8 _19c[0x1a0 - 0x19c];
  grlib::CGLibDepthTarget *unknown1a0[2]; // Inferred role: depth objs; original member name unknown.
  grlib::CGLibDepthTarget *unknown1b0;    // Inferred role: separate trans depth object; original member name unknown.
  grlib::CGLibDepthTarget *unknown1b8;    // Inferred role: light depth object; original member name unknown.
  u8 _1c0[0x1d0 - 0x1c0];
  grlib::CGLibRenderTarget *unknown1d0; // Inferred role: main render target; original member name unknown.
  u32 unknown1d8;                       // Inferred role: flags; original member name unknown.
  u8 _1dc[0x1f8 - 0x1dc];
};

static_assert(offsetof(wkPixlManRes, unknown130) == 0x130, "");
static_assert(offsetof(wkPixlManRes, unknown148) == 0x148, "");
static_assert(offsetof(wkPixlManRes, unknown170) == 0x170, "");
static_assert(offsetof(wkPixlManRes, unknown178) == 0x178, "");
static_assert(offsetof(wkPixlManRes, unknown180) == 0x180, "");
static_assert(offsetof(wkPixlManRes, unknown194) == 0x194, "");
static_assert(offsetof(wkPixlManRes, unknown1a0) == 0x1a0, "");
static_assert(offsetof(wkPixlManRes, unknown1b0) == 0x1b0, "");
static_assert(offsetof(wkPixlManRes, unknown1b8) == 0x1b8, "");
static_assert(offsetof(wkPixlManRes, unknown1d0) == 0x1d0, "");
static_assert(offsetof(wkPixlManRes, unknown1d8) == 0x1d8, "");
static_assert(sizeof(wkPixlManRes) == 0x1f8, "");

class DrPixlShadowObj;

class DrPixlMan {
public:
  enum ResFlag {
    RES_FLAG_SHADOW_DISPLAY_LIST = 0x20,
  };

  void debugRender(const grlib::CGLibTextureBuffer &texture, int x, int y, int width, int height, bool isAlpha, bool isDepth, f32 scale, bool isFlip);
  void debugRenderCh(const grlib::CGLibTextureBuffer &texture, int x, int y, int width, int height, u32 channel);
  void endDeferredRenderTarget();
  void endSkyRenderTarget();
  void setMainViewPort();
  void resetRenderTarget();
  void endGBuffTexture();
  void setMainRenderTarget();
  void selectOpcaityBlmRenderTarget();
  void selectOpcaityRenderTarget();
  DrPixlRenderTarget *getPixlObj(int type);
  grlib::CGLibDepthTarget *getDepthObj();
  grlib::CGLibTextureBuffer *getDammyWhiteTexObj();
  static DrPixlMan *get();
  void setShadowObj(DrPixlShadowObj *shadowObj);
  void setShadowDirRenderTarget(int index);
  void setupShadowUnifrom(int index);
  ~DrPixlMan();
  void releaseColorBuffer();
  void resetLightBuffOnly();
  void createShadowParmDisplayList(wkPixlManRes *res);
  void setupCate(int cate);
  void updateShadowDisplayList();
  DrPixlRenderTarget *getResponsiveAAMask();
  grlib::CGLibDepthTarget *getSeparateTransDepthObj();
  void displayUpdate();
  void renderEnd(int loop);
  void renderBegin(int loop);
  void selectZprepassRenderTarget();
  void selectGBuffRenderTarget();
  bool selectGBuffRenderTarget(u32 mask);
  void refractionGBuffInvalidate();
  void endGBuffRenderTarget();
  void selectDeferredRenderTarget();
  void selectRefractRenderTarget();
  void selectPrePassWrkClearRenderTarget();
  void selectGlobalIBLIndexRenderTarget();
  void endGlobalIBLIndexRenderTarget();
  void alphaRenderTarget();
  void selectLightRenderTarget();
  void selectSubtractLightRenderTarget();
  void skyRenderTarget();
  void skyVisibilityRenderTarget();
  void skyGodRayRenderTarget();
  void renderRefractionMap(bool isRefractionMap, bool isHalfMap);
  bool renderRefractionBegin();
  void renderRefractionEnd();
  void renderSkyDome();
  void renderSkyGodRay();
  void renderRainDrop();
  void renderTMAA();
  bool isRefractionMap();
  void thicknessFirstBegin();
  DrPixlRenderTarget *getBackFaceDepthTexture();
  void thicknessFirstEnd();
  void lastDeferredRender();
  void occRenderEnd();
  void depCheckBegin(bool isDblDepth);
  void depCheckEnd();
  void shadowCallDirBegin();
  void shadowCallDirEnd();
  void shadowDirBegin();
  void shadowDirEnd();
  void callShadowCacheUpdate(bool isAll);
  void callShadowCacheVariance();
  void callFgShadowCacheUpdate();
  void fastRender();
  void lastCapRender();
  void setFinalViewPort();
  void setMainSRGBRenderTarget();
  void setMainSRGBAfterRenderTarget();
  void changeColorBuff();
  void changeHDRBuff(DrPixlRenderTarget *hdrBuff);
  void setTempColorBuff();
  DrPixlRenderTarget *getTempColorBuff();
  void pixelEndMode();
  void setToneAveRange(f32 min, f32 max);
  grlib::CGLibTextureBuffer *getDammyTexObj();
  void offScreenAlphaEnd();
  void debugDeferredRenderAlbedoAndFogRatio(int x, int y, int width, int height);
  DrPixlRenderTarget *getDeactivePixlObj(int type);
  DrPixlRenderTarget *getSpecIBLObj();
  DrPixlRenderTarget *getDiffIBLObj();
  grlib::CGLibDepthTarget *getDeactiveDepthObj();
  void swapPixlObj(int type);
  DrPixlRenderTarget *getBackFaceDepthTexture() const;

  f32 unknown00; // Inferred role: depth value; original member name unknown.
  u8 _004[0x008 - 0x004];
  DrMan *unknown08;                         // Inferred role: dr man; original member name unknown.
  wkPixlManRes unknown10[4];                // Inferred role: resources; original member name unknown.
  wkPixlManRes *unknown7f0;                 // Inferred role: res; original member name unknown.
  DrPixlOccQuery *unknown7f8;               // Inferred role: occ query; original member name unknown.
  DrPixlShadowCacheMan *unknown800;         // Inferred role: shadow cache man; original member name unknown.
  grlib::CGLibTextureBuffer *unknown808[4]; // Inferred role: movie textures; original member name unknown.
  u8 unknown828[4];                         // Inferred role: movie mip filters; original member name unknown.
  u8 _82c[0x830 - 0x82c];
  DrPixlRenderTarget *unknown830; // Inferred role: dammy tex; original member name unknown.
  DrPixlRenderTarget *unknown838; // Inferred role: dammy white tex; original member name unknown.
  u8 _840[0x848 - 0x840];
  DrPixlShadowObj *unknown848; // Inferred role: shadow obj; original member name unknown.
  void *unknown850;            // Inferred role: shadow uniform; original member name unknown.
  u32 unknown858;              // Inferred role: render target; original member name unknown.
  u32 unknown85c;              // Inferred role: gbuff mask; original member name unknown.
  s32 unknown860;              // Inferred role: cate; original member name unknown.
  u8 _864[0x9c0 - 0x864];
  grlib::CGLibRenderTarget *unknown9c0; // Inferred role: capture4 render target; original member name unknown.
};

static_assert(offsetof(DrPixlMan, unknown00) == 0x000, "");
static_assert(offsetof(DrPixlMan, unknown08) == 0x008, "");
static_assert(offsetof(DrPixlMan, unknown10) == 0x010, "");
static_assert(offsetof(DrPixlMan, unknown7f0) == 0x7f0, "");
static_assert(offsetof(DrPixlMan, unknown7f8) == 0x7f8, "");
static_assert(offsetof(DrPixlMan, unknown800) == 0x800, "");
static_assert(offsetof(DrPixlMan, unknown808) == 0x808, "");
static_assert(offsetof(DrPixlMan, unknown828) == 0x828, "");
static_assert(offsetof(DrPixlMan, unknown830) == 0x830, "");
static_assert(offsetof(DrPixlMan, unknown848) == 0x848, "");
static_assert(offsetof(DrPixlMan, unknown850) == 0x850, "");
static_assert(offsetof(DrPixlMan, unknown858) == 0x858, "");
static_assert(offsetof(DrPixlMan, unknown860) == 0x860, "");
static_assert(offsetof(DrPixlMan, unknown9c0) == 0x9c0, "");

} // namespace ml
