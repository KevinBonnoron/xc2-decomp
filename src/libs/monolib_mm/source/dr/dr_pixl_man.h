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
  DrPixlRenderTarget *pixlObjs[19][2];
  DrPixlRenderTarget *colorBuff;
  DrPixlRenderTarget *activeColorBuff;
  DrPixlRenderTarget *hdrBuff;
  DrPixlRenderTarget *backFaceDepthTexture;
  u8 _150[0x170 - 0x150];
  DrPixlDeferred *deferred;
  DrPixlShadowMan *shadowMan;
  DrPixlPostMan *postMan;
  u8 _188[0x194 - 0x188];
  f32 toneAveMin;
  f32 toneAveMax;
  u8 _19c[0x1a0 - 0x19c];
  grlib::CGLibDepthTarget *depthObjs[2];
  grlib::CGLibDepthTarget *separateTransDepthObj;
  u8 _1b8[0x1d0 - 0x1b8];
  grlib::CGLibRenderTarget *mainRenderTarget;
  u32 flags;
  u8 _1dc[0x1f8 - 0x1dc];
};

static_assert(offsetof(wkPixlManRes, colorBuff) == 0x130, "");
static_assert(offsetof(wkPixlManRes, backFaceDepthTexture) == 0x148, "");
static_assert(offsetof(wkPixlManRes, deferred) == 0x170, "");
static_assert(offsetof(wkPixlManRes, shadowMan) == 0x178, "");
static_assert(offsetof(wkPixlManRes, postMan) == 0x180, "");
static_assert(offsetof(wkPixlManRes, toneAveMin) == 0x194, "");
static_assert(offsetof(wkPixlManRes, depthObjs) == 0x1a0, "");
static_assert(offsetof(wkPixlManRes, separateTransDepthObj) == 0x1b0, "");
static_assert(offsetof(wkPixlManRes, mainRenderTarget) == 0x1d0, "");
static_assert(offsetof(wkPixlManRes, flags) == 0x1d8, "");
static_assert(sizeof(wkPixlManRes) == 0x1f8, "");

class DrPixlMan {
public:
  enum ResFlag {
    RES_FLAG_SHADOW_DISPLAY_LIST = 0x20,
  };

  void endDeferredRenderTarget();
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

  u8 _000[0x008 - 0x000];
  DrMan *m_drMan;
  wkPixlManRes m_resources[4];
  wkPixlManRes *m_res;
  DrPixlOccQuery *m_occQuery;
  DrPixlShadowCacheMan *m_shadowCacheMan;
  u8 _808[0x830 - 0x808];
  DrPixlRenderTarget *m_dammyTex;
  DrPixlRenderTarget *m_dammyWhiteTex;
  u8 _840[0x858 - 0x840];
  u32 m_renderTarget;
  u32 m_gbuffMask;
  s32 m_cate;
};

static_assert(offsetof(DrPixlMan, m_drMan) == 0x008, "");
static_assert(offsetof(DrPixlMan, m_resources) == 0x010, "");
static_assert(offsetof(DrPixlMan, m_res) == 0x7f0, "");
static_assert(offsetof(DrPixlMan, m_occQuery) == 0x7f8, "");
static_assert(offsetof(DrPixlMan, m_shadowCacheMan) == 0x800, "");
static_assert(offsetof(DrPixlMan, m_dammyTex) == 0x830, "");
static_assert(offsetof(DrPixlMan, m_renderTarget) == 0x858, "");
static_assert(offsetof(DrPixlMan, m_cate) == 0x860, "");

} // namespace ml
