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
  ~DrPixlPostMan();
  enum Flag {
    FLAG_UNKNOWN_0 = 0x1,       // Inferred role: 3d lut; original name unknown.
    FLAG_UNKNOWN_1 = 0x2,       // Inferred role: tone maping; original name unknown.
    FLAG_UNKNOWN_2 = 0x4,       // Inferred role: bloom; original name unknown.
    FLAG_UNKNOWN_3 = 0x8,       // Inferred role: volume; original name unknown.
    FLAG_UNKNOWN_4 = 0x10,      // Inferred role: ssao; original name unknown.
    FLAG_UNKNOWN_5 = 0x20,      // Inferred role: depth field; original name unknown.
    FLAG_UNKNOWN_6 = 0x40,      // Inferred role: blur; original name unknown.
    FLAG_UNKNOWN_7 = 0x80,      // Inferred role: reflection; original name unknown.
    FLAG_UNKNOWN_8 = 0x100,     // Inferred role: chg shader; original name unknown.
    FLAG_UNKNOWN_9 = 0x200,     // Inferred role: sss; original name unknown.
    FLAG_UNKNOWN_15 = 0x8000,   // Inferred role: calc bloom; original name unknown.
    FLAG_UNKNOWN_16 = 0x10000,  // Inferred role: calc volume; original name unknown.
    FLAG_UNKNOWN_17 = 0x20000,  // Inferred role: reflection; original name unknown.
    FLAG_UNKNOWN_18 = 0x40000,  // Inferred role: high reflection; original name unknown.
    FLAG_UNKNOWN_19 = 0x80000,  // Inferred role: depth down; original name unknown.
    FLAG_UNKNOWN_21 = 0x200000, // Inferred role: refraction map; original name unknown.
  };

  void setDownDepth();
  void setReflection(f32 x, f32 y, f32 z, bool isHigh);
  void renderDeferred();
  void renderDeferredLast();
  void render();
  void renderDeferredTemporal();
  DrPixlRenderTarget *getDownDepth();
  bool isCalcVolume();
  void update();
  void setRefRactionMap();
  void renderRefractionMap(bool isRefractionMap, bool isHalfMap);
  bool renderRefractionBegin();
  void renderRefractionEnd();
  void renderSkyLuminance();
  void renderSkyDome();
  void renderSkyGodRay();
  void renderRainDrop();
  void renderTMAA();
  void renderDeferredFast_AfterTemporal();
  void renderDeferredFast();
  void renderDownDepth(bool isDepth, bool isTemporal, bool isEtc);
  void fastRender();
  void capRender();
  void setGlassBreak(bool isGlassBreak);
  void setCaputureMode(bool isCapture);
  void setBloom(bool isBloom);
  void setSSAO(bool isSSAO);
  void setBlur(bool isBlur);
  void setDepthField(bool isDepthField);
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
  u8 _0d8[0x0e0 - 0x0d8];
  // Inferred role: quarter normal target shown by DrPixlPostObjTSSAO::debugRender; original member name unknown. Evidence: receives a new
  // DrPixlRenderTarget in the DrPixlPostMan constructor (0x710084d600-0x710084d618) and is read by DrPixlPostObjTSSAO::passQuaterNormal
  // (0x71008c1ee8).
  DrPixlRenderTarget *unknowne0;
  u8 _0e8[0x0f0 - 0x0e8];
  DrResUseQueryObj *unknownf0; // Inferred role: refraction query; original member name unknown.
  u32 unknownf8;               // Inferred role: flags; original member name unknown.
  f32 unknownfc;
  f32 unknown100;
  f32 unknown104;
  f32 unknown108; // Inferred role: SSR strength; original member name unknown.
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
static_assert(offsetof(DrPixlPostMan, unknowne0) == 0x0e0, "");
static_assert(offsetof(DrPixlPostMan, unknownf0) == 0x0f0, "");
static_assert(offsetof(DrPixlPostMan, unknownf8) == 0x0f8, "");
static_assert(offsetof(DrPixlPostMan, unknownfc) == 0x0fc, "");
static_assert(offsetof(DrPixlPostMan, unknown104) == 0x104, "");
static_assert(offsetof(DrPixlPostMan, unknown108) == 0x108, "");

} // namespace ml
