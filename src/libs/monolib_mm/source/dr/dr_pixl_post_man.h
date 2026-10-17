#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace mm {
struct Vec3;
} // namespace mm

namespace ml {
class DrMan;
class DrPixlMan;
class DrPixlPostObjBloom;
class DrPixlPostObjCapture;
class DrPixlPostObjCubeMapIBL;
class DrPixlPostObjCubeMapMultiIBL;
class DrPixlPostObjDepthofField;
class DrPixlPostObjExpStencil;
class DrPixlPostObjGlassBr;
class DrPixlPostObjHistgram;
class DrPixlPostObjMotionBlur;
class DrPixlPostObjMotionBlur2;
class DrPixlPostObjRainDrop;
class DrPixlPostObjSSR;
class DrPixlPostObjTMAA;
class DrPixlPostObjTSSAO;
class DrPixlPostObjToneMap;
class DrPixlPostObjUnbranchToDepth;
class DrPixlPostObjVolume;
class DrPixlRenderTarget;
class DrPixlShadowRaytrace;
class DrPixlSkyDome;
class DrPixlToonGrad;
class DrResUseQueryObj;

class DrPixlPostMan {
public:
  enum Flag {
    FLAG_3D_LUT = 0x1,
    FLAG_TONE_MAPING = 0x2,
    FLAG_BLOOM = 0x4,
    FLAG_VOLUME = 0x8,
    FLAG_SSAO = 0x10,
    FLAG_DEPTH_FIELD = 0x20,
    FLAG_BLUR = 0x40,
    FLAG_REFLECTION = 0x80,
    FLAG_CHG_SHADER = 0x100,
    FLAG_SSS = 0x200,
    FLAG_CALC_BLOOM = 0x8000,
    FLAG_CALC_VOLUME = 0x10000,
    FLAG_DEPTH_DOWN = 0x80000,
    FLAG_REFRACTION_MAP = 0x200000,
  };

  void setDownDepth();
  void renderDeferred();
  void renderDeferredLast();
  DrPixlRenderTarget *getDownDepth();
  bool isCalcVolume();
  void setRefRactionMap();
  void renderRefractionMap(bool isRefractionMap, bool isHalfMap);
  bool renderRefractionBegin();
  void renderRefractionEnd();
  void renderSkyDome();
  void renderSkyGodRay();
  void renderRainDrop();
  void renderTMAA();
  void renderDeferredFast_AfterTemporal();
  void fastRender();
  void capRender();
  void setBloom(bool isBloom);
  void setSSAO(bool isSSAO);
  DrPixlRenderTarget *getOldDownDepth();
  void setToneMaping(bool isToneMaping);
  void setVolume(bool isVolume);
  void set3DLut(bool is3DLut);
  void setSSAOAv(bool isSSAO);
  void setVolumePos(const mm::Vec3 &pos);
  void setDepthFieldParm(f32 distance, f32 range, f32 strength);
  void setBlurParm(f32 strength, f32 sub);
  bool isToneMaping();
  bool isBloom();
  bool isCalcBloom();
  bool is3DLut();
  bool isVolume();
  bool isBluer();
  bool isDepthField();
  bool isSSAO();
  bool isSSS();
  bool isReflection();
  bool isChgShader();
  bool isDepthDown();
  const grlib::CGLibTextureBuffer *getToonGradTex() const;
  const grlib::CGLibTextureBuffer *getToonDarkGradTex() const;

  DrMan *m_drMan;
  DrPixlMan *m_pixlMan;
  u8 _010[0x018 - 0x010];
  DrPixlPostObjToneMap *m_toneMap;
  DrPixlPostObjBloom *m_bloom;
  DrPixlPostObjVolume *m_volume;
  DrPixlPostObjDepthofField *m_depthofField;
  u8 _038[0x040 - 0x038];
  DrPixlPostObjCubeMapMultiIBL *m_cubeMapMultiIBL;
  DrPixlPostObjCubeMapIBL *m_cubeMapIBL;
  DrPixlPostObjMotionBlur *m_motionBlur;
  DrPixlPostObjMotionBlur2 *m_motionBlur2;
  DrPixlPostObjHistgram *m_histgram;
  DrPixlPostObjTMAA *m_tmaa;
  DrPixlPostObjSSR *m_ssr;
  DrPixlPostObjTSSAO *m_tssao;
  DrPixlPostObjExpStencil *m_expStencil;
  DrPixlShadowRaytrace *m_shadowRaytrace;
  DrPixlSkyDome *m_skyDome;
  DrPixlToonGrad *m_toonGrad;
  DrPixlPostObjRainDrop *m_rainDrop;
  DrPixlPostObjGlassBr *m_glassBr;
  DrPixlPostObjCapture *m_capture;
  DrPixlPostObjUnbranchToDepth *m_unbranchToDepth;
  DrPixlRenderTarget *m_downDepths[2];
  DrPixlRenderTarget *m_refractionMap;
  u8 _0d8[0x0f0 - 0x0d8];
  DrResUseQueryObj *m_refractionQuery;
  u32 m_flags;
};

static_assert(offsetof(DrPixlPostMan, m_toneMap) == 0x018, "");
static_assert(offsetof(DrPixlPostMan, m_cubeMapMultiIBL) == 0x040, "");
static_assert(offsetof(DrPixlPostMan, m_motionBlur) == 0x050, "");
static_assert(offsetof(DrPixlPostMan, m_tmaa) == 0x068, "");
static_assert(offsetof(DrPixlPostMan, m_tssao) == 0x078, "");
static_assert(offsetof(DrPixlPostMan, m_skyDome) == 0x090, "");
static_assert(offsetof(DrPixlPostMan, m_rainDrop) == 0x0a0, "");
static_assert(offsetof(DrPixlPostMan, m_capture) == 0x0b0, "");
static_assert(offsetof(DrPixlPostMan, m_downDepths) == 0x0c0, "");
static_assert(offsetof(DrPixlPostMan, m_refractionQuery) == 0x0f0, "");
static_assert(offsetof(DrPixlPostMan, m_flags) == 0x0f8, "");

} // namespace ml
