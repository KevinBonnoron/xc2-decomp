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

  DrMan *unknown00;     // Inferred role: dr man; original member name unknown.
  DrPixlMan *unknown08; // Inferred role: pixl man; original member name unknown.
  u8 _010[0x018 - 0x010];
  DrPixlPostObjToneMap *unknown18;      // Inferred role: tone map; original member name unknown.
  DrPixlPostObjBloom *unknown20;        // Inferred role: bloom; original member name unknown.
  DrPixlPostObjVolume *unknown28;       // Inferred role: volume; original member name unknown.
  DrPixlPostObjDepthofField *unknown30; // Inferred role: depthof field; original member name unknown.
  u8 _038[0x040 - 0x038];
  DrPixlPostObjCubeMapMultiIBL *unknown40; // Inferred role: cube map multi ibl; original member name unknown.
  DrPixlPostObjCubeMapIBL *unknown48;      // Inferred role: cube map ibl; original member name unknown.
  DrPixlPostObjMotionBlur *unknown50;      // Inferred role: motion blur; original member name unknown.
  DrPixlPostObjMotionBlur2 *unknown58;     // Inferred role: motion blur2; original member name unknown.
  DrPixlPostObjHistgram *unknown60;        // Inferred role: histgram; original member name unknown.
  DrPixlPostObjTMAA *unknown68;            // Inferred role: tmaa; original member name unknown.
  DrPixlPostObjSSR *unknown70;             // Inferred role: ssr; original member name unknown.
  DrPixlPostObjTSSAO *unknown78;           // Inferred role: tssao; original member name unknown.
  DrPixlPostObjExpStencil *unknown80;      // Inferred role: exp stencil; original member name unknown.
  DrPixlShadowRaytrace *unknown88;         // Inferred role: shadow raytrace; original member name unknown.
  DrPixlSkyDome *unknown90;                // Inferred role: sky dome; original member name unknown.
  DrPixlToonGrad *unknown98;               // Inferred role: toon grad; original member name unknown.
  DrPixlPostObjRainDrop *unknowna0;        // Inferred role: rain drop; original member name unknown.
  DrPixlPostObjGlassBr *unknowna8;         // Inferred role: glass br; original member name unknown.
  DrPixlPostObjCapture *unknownb0;         // Inferred role: capture; original member name unknown.
  DrPixlPostObjUnbranchToDepth *unknownb8; // Inferred role: unbranch to depth; original member name unknown.
  DrPixlRenderTarget *unknownc0[2];        // Inferred role: down depths; original member name unknown.
  DrPixlRenderTarget *unknownd0;           // Inferred role: refraction map; original member name unknown.
  u8 _0d8[0x0f0 - 0x0d8];
  DrResUseQueryObj *unknownf0; // Inferred role: refraction query; original member name unknown.
  u32 unknownf8;               // Inferred role: flags; original member name unknown.
};

static_assert(offsetof(DrPixlPostMan, unknown18) == 0x018, "");
static_assert(offsetof(DrPixlPostMan, unknown40) == 0x040, "");
static_assert(offsetof(DrPixlPostMan, unknown50) == 0x050, "");
static_assert(offsetof(DrPixlPostMan, unknown68) == 0x068, "");
static_assert(offsetof(DrPixlPostMan, unknown78) == 0x078, "");
static_assert(offsetof(DrPixlPostMan, unknown90) == 0x090, "");
static_assert(offsetof(DrPixlPostMan, unknowna0) == 0x0a0, "");
static_assert(offsetof(DrPixlPostMan, unknownb0) == 0x0b0, "");
static_assert(offsetof(DrPixlPostMan, unknownc0) == 0x0c0, "");
static_assert(offsetof(DrPixlPostMan, unknownf0) == 0x0f0, "");
static_assert(offsetof(DrPixlPostMan, unknownf8) == 0x0f8, "");

} // namespace ml
