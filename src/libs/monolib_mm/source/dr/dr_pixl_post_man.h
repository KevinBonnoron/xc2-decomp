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
class DrPixlPostObj3dLut;
class DrPixlPostObjBloom;
class DrPixlPostObjCapture;
class DrPixlPostObjCubeMapIBL;
class DrPixlPostObjCubeMapMultiIBL;
class DrPixlPostObjDepthofField;
class DrPixlPostObjExpStencil;
class DrPixlPostObjFxAA;
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
    FLAG_UNKNOWN_22 = 0x400000, // Inferred role: color buffers released with the render mode 3; original name unknown.
  };

  void beginUpdate();
  void setDownDepth();
  void setReflection(f32 x, f32 y, f32 z, bool isHigh);
  void renderDeferred();
  void renderDeferredLast();
  void setupDepthBuff();
  void resetColorBuff();
  void releaseColorBuff();
  void render();
  bool debugDeferredRenderImpl(bool isRender);
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

  DrMan *m_drMan;                               // Inferred role: dr man; original member name unknown.
  DrPixlMan *m_drPixlMan;                       // Inferred role: pixl man; original member name unknown.
  DrPixlPostObj3dLut *m_drPixlPostObj3dLut;     // Inferred role: 3d lut (the destructor 0x710084dd20 inlines its destructor: two render volumes at +0x20 and +0x28); original member name unknown.
  DrPixlPostObjToneMap *m_drPixlPostObjToneMap; // Inferred role: tone map; original member name unknown.
  DrPixlPostObjBloom *m_drPixlPostObjBloom;     // Inferred role: bloom; original member name unknown.
  DrPixlPostObjVolume *m_drPixlPostObjVolume;   // Inferred role: volume; original member name unknown.
  DrPixlPostObjDepthofField *m_drPixlPostObjDepthofField;       // Inferred role: depthof field; original member name unknown.
  DrPixlPostObjFxAA *m_drPixlPostObjFxAA;                       // Inferred role: fx aa (releaseColorBuff 0x710083d614 releases its target at +0x18); original member name unknown.
  DrPixlPostObjCubeMapMultiIBL *m_drPixlPostObjCubeMapMultiIBL; // Inferred role: cube map multi ibl; original member name unknown.
  DrPixlPostObjCubeMapIBL *m_drPixlPostObjCubeMapIBL;           // Inferred role: cube map ibl; original member name unknown.
  DrPixlPostObjMotionBlur *m_drPixlPostObjMotionBlur;           // Inferred role: motion blur; original member name unknown.
  DrPixlPostObjMotionBlur2 *m_drPixlPostObjMotionBlur2;         // Inferred role: motion blur2; original member name unknown.
  DrPixlPostObjHistgram *m_drPixlPostObjHistgram;               // Inferred role: histgram; original member name unknown.
  DrPixlPostObjTMAA *m_drPixlPostObjTMAA;                       // Inferred role: tmaa; original member name unknown.
  DrPixlPostObjSSR *m_drPixlPostObjSSR;                         // Inferred role: ssr; original member name unknown.
  DrPixlPostObjTSSAO *m_drPixlPostObjTSSAO;                     // Inferred role: tssao; original member name unknown.
  DrPixlPostObjExpStencil *m_drPixlPostObjExpStencil;           // Inferred role: exp stencil; original member name unknown.
  DrPixlShadowRaytrace *m_drPixlShadowRaytrace;                 // Inferred role: shadow raytrace; original member name unknown.
  DrPixlSkyDome *m_drPixlSkyDome;                               // Inferred role: sky dome; original member name unknown.
  DrPixlToonGrad *m_drPixlToonGrad;                             // Inferred role: toon grad; original member name unknown.
  DrPixlPostObjRainDrop *m_drPixlPostObjRainDrop;               // Inferred role: rain drop; original member name unknown.
  DrPixlPostObjGlassBr *m_drPixlPostObjGlassBr;                 // Inferred role: glass br; original member name unknown.
  DrPixlPostObjCapture *m_drPixlPostObjCapture;                 // Inferred role: capture; original member name unknown.
  DrPixlPostObjUnbranchToDepth *m_drPixlPostObjUnbranchToDepth; // Inferred role: unbranch to depth; original member name unknown.
  DrPixlRenderTarget *unknownc0[2];                             // Inferred role: down depths; original member name unknown.
  DrPixlRenderTarget *unknownd0;                                // Inferred role: refraction map; original member name unknown.
  // Inferred role: render target released by the destructor 0x710084dd20 (the only other access known); original member name unknown. Evidence: receives a
  // new DrPixlRenderTarget in the DrPixlPostMan constructor (0x710084da38-0x710084da4c, the object's DrMan at +0x3c8).
  DrPixlRenderTarget *unknownd8;
  // Inferred role: quarter normal target shown by DrPixlPostObjTSSAO::debugRender; original member name unknown. Evidence: receives a new
  // DrPixlRenderTarget in the DrPixlPostMan constructor (0x710084d600-0x710084d618) and is read by DrPixlPostObjTSSAO::passQuaterNormal
  // (0x71008c1ee8).
  DrPixlRenderTarget *unknowne0;
  // Inferred role: depth target (the shader samples it as gTDepth); original member name unknown. Evidence: receives a new
  // DrPixlRenderTarget in the DrPixlPostMan constructor (0x710084d63c-0x710084d654, after unknowne0) and DrPixlPostObjTSSAO::
  // passTemporalFiltering (0x71008c2aa0) reads its width and height (offsets 0xbc, 0xc0) and its texture (offset 0x70).
  DrPixlRenderTarget *unknowne8;
  DrResUseQueryObj *m_drResUseQueryObj; // Inferred role: refraction query; original member name unknown.
  u32 unknownf8;                        // Inferred role: flags; original member name unknown.
  f32 unknownfc;
  f32 unknown100;
  f32 unknown104;
  f32 unknown108; // Inferred role: SSR strength; original member name unknown.
};

static_assert(offsetof(DrPixlPostMan, m_drPixlPostObj3dLut) == 0x010, "");
static_assert(offsetof(DrPixlPostMan, m_drPixlPostObjToneMap) == 0x018, "");
static_assert(offsetof(DrPixlPostMan, m_drPixlPostObjFxAA) == 0x038, "");
static_assert(offsetof(DrPixlPostMan, m_drPixlPostObjCubeMapMultiIBL) == 0x040, "");
static_assert(offsetof(DrPixlPostMan, m_drPixlPostObjMotionBlur) == 0x050, "");
static_assert(offsetof(DrPixlPostMan, m_drPixlPostObjTMAA) == 0x068, "");
static_assert(offsetof(DrPixlPostMan, m_drPixlPostObjTSSAO) == 0x078, "");
static_assert(offsetof(DrPixlPostMan, m_drPixlSkyDome) == 0x090, "");
static_assert(offsetof(DrPixlPostMan, m_drPixlPostObjRainDrop) == 0x0a0, "");
static_assert(offsetof(DrPixlPostMan, m_drPixlPostObjCapture) == 0x0b0, "");
static_assert(offsetof(DrPixlPostMan, unknownc0) == 0x0c0, "");
static_assert(offsetof(DrPixlPostMan, unknownd8) == 0x0d8, "");
static_assert(offsetof(DrPixlPostMan, unknowne0) == 0x0e0, "");
static_assert(offsetof(DrPixlPostMan, unknowne8) == 0x0e8, "");
static_assert(offsetof(DrPixlPostMan, m_drResUseQueryObj) == 0x0f0, "");
static_assert(offsetof(DrPixlPostMan, unknownf8) == 0x0f8, "");
static_assert(offsetof(DrPixlPostMan, unknownfc) == 0x0fc, "");
static_assert(offsetof(DrPixlPostMan, unknown104) == 0x104, "");
static_assert(offsetof(DrPixlPostMan, unknown108) == 0x108, "");

} // namespace ml
