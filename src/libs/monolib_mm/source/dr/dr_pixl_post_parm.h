#pragma once
#include "mm_math/mm_vec3.h"
#include "types.h"
#include <stddef.h>

namespace ml {

// Inferred role: g buff debug range; original type name unknown.
// Evidence: DrPixlMan::debugGBuffRender reads the two values of an entry through one loop index, the scene accessor writes them as min and max.
struct unknown038 {
  f32 unknown00[2]; // Inferred role: min and max; original member name unknown.
};

static_assert(sizeof(unknown038) == 0x8, "");

// Inferred role: pixl post dbl parm; original type name unknown.
// Evidence: the DrPixlPostParm constructor clears the two entries with one memset of 0xa40 bytes from 0x514.
struct unknown039 {
  bool unknown00; // Inferred role: tone map parameters are restored from this entry; original member name unknown. Evidence: DrEnvColiParameter::calcParams (0x71007d4be4, 0x71007d5204).
  u8 _001[0x004 - 0x001];
  bool unknown04; // Inferred role: override tone map; original member name unknown.
  u8 _005[0x008 - 0x005];
  f32 unknown08;     // Inferred role: tone map; original member name unknown.
  f32 unknown0c[11]; // Inferred role: tone map parameters saved from DrPixlPostParm 0x08 to 0x30 by DrEnvColiParameter::calcParams; original member name unknown.
  u8 _038[0x040 - 0x038];
  bool unknown40; // Inferred role: bloom parameters are restored from this entry (0x71007d4c54, 0x71007d5208); original member name unknown.
  u8 _041[0x048 - 0x041];
  f32 unknown48[30]; // Inferred role: bloom parameters saved from DrPixlPostParm 0x40 to 0xb4; original member name unknown.
  u8 _0c0[0x0c8 - 0x0c0];
  f32 unknownc8;    // Inferred role: bloom parameter saved from DrPixlPostParm::unknownc0; original member name unknown.
  u32 unknowncc;    // Inferred role: bloom parameter saved from DrPixlPostParm::unknownc4; original member name unknown.
  f32 unknownd0[2]; // Inferred role: blm lens sub and mul saved from DrPixlPostParm 0xc8; original member name unknown.
  s32 unknownd8;    // Inferred role: blm lens max saved from DrPixlPostParm 0xd0; original member name unknown.
  f32 unknowndc[6]; // Inferred role: blm lens parameters saved from DrPixlPostParm 0xd4 to 0xe8; original member name unknown.
  u8 _0f4[0x0f8 - 0x0f4];
  f32 unknownf8[3]; // Inferred role: god ray parameters saved from DrPixlPostParm 0xf0 to 0xf8; original member name unknown.
  bool unknown104;  // Inferred role: flag cleared by DrEnvColiParameter::calcParams (0x71007d5278); original member name unknown.
  u8 _105[0x118 - 0x105];
  bool unknown118; // Inferred role: flag cleared by DrEnvColiParameter::calcParams (0x71007d53f0); original member name unknown.
  u8 _119[0x17c - 0x119];
  bool unknown17c; // Inferred role: tssao parameters are restored from this entry (0x71007d4dcc, 0x71007d540c); original member name unknown.
  u8 _17d[0x180 - 0x17d];
  f32 unknown180[6]; // Inferred role: tssao parameters saved from DrPixlPostParm 0x178 to 0x18c; original member name unknown.
  u8 _198[0x19c - 0x198];
  bool unknown19c; // Inferred role: flag cleared by DrEnvColiParameter::calcParams (0x71007d5454); original member name unknown.
  u8 _19d[0x1d2 - 0x19d];
  bool unknown1d2; // Inferred role: flag cleared by DrEnvColiParameter::calcParams (0x71007d5464); original member name unknown.
  u8 _1d3[0x204 - 0x1d3];
  bool m_overrideMotBlur; // Inferred role: override mot blur; named after the game accessor ml::DrPixlPostParm::setOverrideMotBlur.
  bool m_motBlur2;        // Inferred role: mot blur2; named after the game accessor ml::DrPixlPostParm::setMotBlur2.
  u8 _206[0x220 - 0x206];
  bool m_overrideDOF; // Inferred role: override dof; named after the game accessor ml::DrPixlPostParm::isOverrideDOF.
  bool m_dOF;         // Inferred role: dof; named after the game accessor ml::DrPixlPostParm::setDOF.
  u8 _222[0x223 - 0x222];
  bool m_dOFHlv;       // Inferred role: dof hlv; named after the game accessor ml::DrPixlPostParm::setDOFHlv.
  bool m_dOFDownSec;   // Inferred role: dof down sec; named after the game accessor ml::DrPixlPostParm::setDOFDownSec.
  bool m_dOFAutoFocus; // Inferred role: dof auto focus; named after the game accessor ml::DrPixlPostParm::setDOFAutoFocus.
  u8 _226[0x228 - 0x226];
  f32 m_doFPixlRatio;   // Inferred role: dof pixl ratio; named after the game accessor ml::DrPixlPostParm::setDoFPixlRatio.
  f32 m_doFDistance;    // Inferred role: dof distance; named after the game accessor ml::DrPixlPostParm::setDoFDistance.
  f32 m_doFRange;       // Inferred role: dof range; named after the game accessor ml::DrPixlPostParm::setDoFRange.
  f32 m_doFStrength;    // Inferred role: dof strength; named after the game accessor ml::DrPixlPostParm::setDoFStrength.
  f32 m_doFLens;        // Inferred role: dof lens; named after the game accessor ml::DrPixlPostParm::setDoFLens.
  f32 m_doFBlend;       // Inferred role: dof blend; named after the game accessor ml::DrPixlPostParm::setDoFBlend.
  s32 m_doFPixlLv;      // Inferred role: dof pixl lv; named after the game accessor ml::DrPixlPostParm::setDoFPixlLv.
  s32 m_doFocusNum;     // Inferred role: dof focus num; named after the game accessor ml::DrPixlPostParm::setDoFocusNum.
  f32 m_doFDofFocusRat; // Inferred role: dof focus ratio; named after the game accessor ml::DrPixlPostParm::setDoFDofFocusRat.
  f32 m_dofFocusMin;    // Inferred role: dof focus min; named after the game accessor ml::DrPixlPostParm::setDofFocusMin.
  bool unknown250;      // Inferred role: flag cleared by DrEnvColiParameter::calcParams (0x71007d5504); original member name unknown.
  u8 _251[0x272 - 0x251];
  bool m_overrideColorFilter; // Inferred role: override color filter; named after the game accessor ml::DrPixlPostParm::isOverrideColorFilter.
  u8 _273[0x274 - 0x273];
  s32 m_colorFilterNum; // Inferred role: color filter num; named after the game accessor ml::DrPixlPostParm::setColorFilterNum.
  f32 m_colorFilterFrm; // Inferred role: color filter frm; named after the game accessor ml::DrPixlPostParm::setColorFilterFrm.
  u8 _27c[0x280 - 0x27c];
  s32 m_colorFilterFarNum; // Inferred role: color filter far num; named after the game accessor ml::DrPixlPostParm::setColorFilterFarNum.
  f32 unknown284[4];       // Inferred role: color filter parameters saved from DrPixlPostParm 0x27c to 0x288; original member name unknown.
  u8 _294[0x2a6 - 0x294];
  bool unknown2a6; // Inferred role: flag cleared by DrEnvColiParameter::calcParams (0x71007d5548); original member name unknown.
  u8 _2a7[0x30c - 0x2a7];
  bool unknown30c; // Inferred role: flag cleared by DrEnvColiParameter::calcParams (0x71007d5558); original member name unknown.
  u8 _30d[0x368 - 0x30d];
  bool unknown368; // Inferred role: shadow parameters are restored from this entry (0x71007d4ecc, 0x71007d5568); original member name unknown.
  u8 _369[0x388 - 0x369];
  f32 unknown388[10]; // Inferred role: shadow parameters saved from DrPixlPostParm 0x37c to 0x3a0; original member name unknown.
  u8 _3b0[0x3b1 - 0x3b0];
  bool unknown3b1; // Inferred role: flag cleared by DrEnvColiParameter::calcParams (0x71007d55d4); original member name unknown.
  u8 _3b2[0x3c4 - 0x3b2];
  bool unknown3c4; // Inferred role: rain drop parameters are restored from this entry (0x71007d4f34, 0x71007d55e8); original member name unknown.
  u8 _3c5[0x3d0 - 0x3c5];
  f32 unknown3d0[5]; // Inferred role: rain drop parameters saved from DrPixlPostParm 0x3c4 to 0x3d4; original member name unknown.
  u8 _3e4[0x3e8 - 0x3e4];
  f32 unknown3e8[27]; // Inferred role: rain drop values saved from DrPixlPostParm 0x3dc to 0x444; original member name unknown.
  u8 _454[0x468 - 0x454];
  f32 unknown468;  // Inferred role: rain drop parameter saved from DrPixlPostParm 0x45c; original member name unknown.
  bool unknown46c; // Inferred role: the ray traced shadow flag is not forced by this entry (0x71007d5180); original member name unknown.
  u8 _46d[0x46e - 0x46d];
  bool unknown46e; // Inferred role: flag cleared by DrEnvColiParameter::calcParams (0x71007d55e8); original member name unknown.
  u8 _46f[0x520 - 0x46f];
};

static_assert(offsetof(unknown039, unknown08) == 0x008, "");
static_assert(offsetof(unknown039, m_overrideMotBlur) == 0x204, "");
static_assert(offsetof(unknown039, m_overrideDOF) == 0x220, "");
static_assert(offsetof(unknown039, m_dOFHlv) == 0x223, "");
static_assert(offsetof(unknown039, m_doFPixlRatio) == 0x228, "");
static_assert(offsetof(unknown039, m_dofFocusMin) == 0x24c, "");
static_assert(offsetof(unknown039, m_overrideColorFilter) == 0x272, "");
static_assert(offsetof(unknown039, m_colorFilterNum) == 0x274, "");
static_assert(offsetof(unknown039, m_colorFilterFarNum) == 0x280, "");
static_assert(offsetof(unknown039, unknown0c) == 0x00c, "");
static_assert(offsetof(unknown039, unknown40) == 0x040, "");
static_assert(offsetof(unknown039, unknown48) == 0x048, "");
static_assert(offsetof(unknown039, unknowncc) == 0x0cc, "");
static_assert(offsetof(unknown039, unknownd0) == 0x0d0, "");
static_assert(offsetof(unknown039, unknownd8) == 0x0d8, "");
static_assert(offsetof(unknown039, unknowndc) == 0x0dc, "");
static_assert(offsetof(unknown039, unknown19c) == 0x19c, "");
static_assert(offsetof(unknown039, unknown1d2) == 0x1d2, "");
static_assert(offsetof(unknown039, unknownf8) == 0x0f8, "");
static_assert(offsetof(unknown039, unknown104) == 0x104, "");
static_assert(offsetof(unknown039, unknown118) == 0x118, "");
static_assert(offsetof(unknown039, unknown17c) == 0x17c, "");
static_assert(offsetof(unknown039, unknown180) == 0x180, "");
static_assert(offsetof(unknown039, unknown250) == 0x250, "");
static_assert(offsetof(unknown039, unknown284) == 0x284, "");
static_assert(offsetof(unknown039, unknown2a6) == 0x2a6, "");
static_assert(offsetof(unknown039, unknown30c) == 0x30c, "");
static_assert(offsetof(unknown039, unknown368) == 0x368, "");
static_assert(offsetof(unknown039, unknown388) == 0x388, "");
static_assert(offsetof(unknown039, unknown3b1) == 0x3b1, "");
static_assert(offsetof(unknown039, unknown3c4) == 0x3c4, "");
static_assert(offsetof(unknown039, unknown3d0) == 0x3d0, "");
static_assert(offsetof(unknown039, unknown3e8) == 0x3e8, "");
static_assert(offsetof(unknown039, unknown468) == 0x468, "");
static_assert(offsetof(unknown039, unknown46c) == 0x46c, "");
static_assert(offsetof(unknown039, unknown46e) == 0x46e, "");
static_assert(sizeof(unknown039) == 0x520, "");

class DrPixlPostParm {
public:
  struct stRainDropLayerInfo {
    f32 unknown00; // Role and original member name unknown.
    f32 unknown04; // Role and original member name unknown.
    f32 unknown08; // Role and original member name unknown.
    f32 unknown0c; // Role and original member name unknown.
    f32 unknown10; // Role and original member name unknown.
  };

  bool isShwRaytrace() const;
  void calcReductionTransBuffer(int &width, int &height) const;
  void setDOF(bool dof);
  bool getTMAAOn() const;
  f32 getTMAASharpness(u32 index) const;
  bool isMotBlur2() const;
  bool getBloomOn() const;
  bool getToneMapOn() const;
  bool isMotBlur() const;
  bool isBlm2PassExtract() const;
  bool isShwRaytraceTemporalWithOthers() const;
  void update();
  bool getAAOn() const;
  bool getColTblOn() const;
  f32 getBorderBlmMul() const;
  static DrPixlPostParm *get();
  void setInst();
  DrPixlPostParm();
  void reset();
  ~DrPixlPostParm();
  DrPixlPostParm &operator=(const DrPixlPostParm &parm);
  void calcOfsRenderCheck(f32 x, f32 y);
  void calcReductionBuffer(int &width, int &height);
  void setOverrideToneMap(f32 overrideToneMap);
  f32 getToonDirLightScale() const;
  void OnCloseAttriMenu();
  void resetScene();
  void setWeatherFrame(f32 weatherFrame);
  f32 getWeatherFrame() const;
  void resetWeatherFrame();
  void writeParameter(const char *path, const char *name);
  void readParameter(const char *path, bool isCreate, const char *name);
  void updateParameter(const char *name);
  void setOverrideMotBlur(bool overrideMotBlur);
  void setMotBlur2(bool motBlur2);
  void setOverrideDOF(bool overrideDOF);
  void setDOFHlv(bool dofHlv);
  void setDOFDownSec(bool dofDownSec);
  void setDOFAutoFocus(bool dofAutoFocus);
  void setDOFAutoFocusDebug(bool dofAutoFocusDebug);
  void setDoFPixlRatio(f32 dofPixlRatio);
  void setDoFDistance(f32 dofDistance);
  void setDoFRange(f32 dofRange);
  void setDoFStrength(f32 dofStrength);
  void setDoFLens(f32 dofLens);
  void setDoFBlend(f32 dofBlend);
  void setDoFPixlLv(s32 dofPixlLv);
  void setDoFocusNum(s32 dofFocusNum);
  void setDoFDofFocusRat(f32 dofFocusRatio);
  void setDofFocusMin(f32 dofFocusMin);
  bool isOverrideDOF() const;
  bool isOverrideColorFilter() const;
  void setOverrideColorFilter(bool overrideColorFilter);
  void setColorFilterNum(s32 colorFilterNum);
  void setColorFilterFrm(f32 colorFilterFrm);
  void setColorFilterTransZ(bool colorFilterTransZ);
  void setColorFilterFarNum(s32 colorFilterFarNum);
  bool getRainDropOn() const;
  bool getSSRWithTrans() const;
  bool getSSROn() const;
  void setGlassBrk(bool glassBrk, u32 type);
  void getRanDropLayerInfo(u32 layer, stRainDropLayerInfo &info) const;

  static DrPixlPostParm *s_pIns;

  bool m_toneMapOn;
  u8 _0001[0x0003 - 0x0001];
  bool unknown03;         // Inferred role: tone map override flag, set by DrEnvColiParameter::calcParams from the double buffered parameters (0x71007d4bbc); original member name unknown.
  f32 unknown04;          // Inferred role: tone map override value, 1 without the override (0x71007d4bd8); original member name unknown.
  f32 m_toneMax;          // Inferred role: tone max; named after the game accessor ml::ScnRenderDrSysParmAcc::setToneMax.
  f32 m_toneMin;          // Inferred role: tone min; named after the game accessor ml::ScnRenderDrSysParmAcc::setToneMin.
  f32 m_toneRatio;        // Inferred role: tone ratio; named after the game accessor ml::ScnRenderDrSysParmAcc::setToneRatio.
  f32 m_toneRatioLast;    // Inferred role: tone ratio last; named after the game accessor ml::ScnRenderDrSysParmAcc::setToneRatioLast.
  f32 m_toneBlmMax;       // Inferred role: tone blm max; named after the game accessor ml::ScnRenderDrSysParmAcc::setToneBlmMax.
  f32 m_toneBlmMin;       // Inferred role: tone blm min; named after the game accessor ml::ScnRenderDrSysParmAcc::setToneBlmMin.
  f32 m_toneBlmRatio;     // Inferred role: tone blm ratio; named after the game accessor ml::ScnRenderDrSysParmAcc::setToneBlmRatio.
  f32 m_toneBlmRatioLast; // Inferred role: tone blm ratio last; named after the game accessor ml::ScnRenderDrSysParmAcc::setToneBlmRatioLast.
  f32 unknown28;          // Inferred role: tone ave min rate; original member name unknown.
  f32 unknown2c;          // Inferred role: tone ave max rate; original member name unknown.
  f32 unknown30;          // Inferred role: tone map parameter written with the tone ave max rate by resetToneMapParams; original member name unknown.
  u8 _0034[0x003c - 0x0034];
  bool m_bloomOn;
  bool unknown3d;   // Inferred role: bloom debug render; original member name unknown. `ldrb w8, [x8, #0x3d]` at 0x71008552d8 (DrPixlPostObjBloom::debugRender).
  bool m_lensFlare; // Inferred role: lens flare; named after the game accessor ml::ScnRenderDrSysParmAcc::isLensFlare.
  u8 _003f[0x0040 - 0x003f];
  f32 m_borderBlmSub; // Inferred role: border blm sub; named after the game accessor ml::ScnRenderDrSysParmAcc::getBorderBlmSub.
  f32 m_borderBlmMul;
  f32 m_borderBlmSecSub; // Inferred role: border blm sec sub; named after the game accessor ml::ScnRenderDrSysParmAcc::getBorderBlmSecSub.
  f32 m_borderBlmSecMul; // Inferred role: border blm sec mul; named after the game accessor ml::ScnRenderDrSysParmAcc::getBorderBlmSecMul.
  f32 m_borderBlmMax;    // Inferred role: border blm max; named after the game accessor ml::ScnRenderDrSysParmAcc::getBorderBlmMax.
  f32 m_blmWeight[10];   // Inferred role: blm weight (getBlmWeight returns its start); the blm weight groups blended by DrEnvColiParameter::calcParams fill its 10 elements and the 15 of m_blmStr.
  f32 m_blmStr[15];      // Inferred role: blm str (getBlmStr returns its start); the gauss of getBlmGauss is element 5 (0x90) and updateBloomParams copies 0x7c to 0xb7; one array so that the adjacent
                         // loads of the blend merge as the game's.
  u8 _00b8[0x00c0 - 0x00b8];
  f32 unknownc0[1];      // Inferred role: bloom parameter copied from the default post parm by updateBloomParams (the word after it is the u32 unknownc4); original member name unknown.
  u32 unknownc4;         // Inferred role: bloom parameter blended through float by DrEnvColiParameter::calcParams (0x71007d3570); original member name unknown.
  f32 m_blmLensSub;      // Inferred role: blm lens sub; named after the game accessor ml::ScnRenderDrSysParmAcc::getBlmLensSub.
  f32 m_blmLensMul;      // Inferred role: blm lens mul; named after the game accessor ml::ScnRenderDrSysParmAcc::getBlmLensMul.
  s32 m_blmLensMax;      // Inferred role: blm lens max; named after the game accessor ml::ScnRenderDrSysParmAcc::getBlmLensMax.
  f32 m_blmLensRot;      // Inferred role: blm lens rot; named after the game accessor ml::ScnRenderDrSysParmAcc::getBlmLensRot.
  f32 m_blmLensWeight;   // Inferred role: blm lens weight; named after the game accessor ml::ScnRenderDrSysParmAcc::getBlmLensWeight.
  f32 m_blmLensDecay;    // Inferred role: blm lens decay; named after the game accessor ml::ScnRenderDrSysParmAcc::getBlmLensDecay.
  f32 m_blmLensStrength; // Inferred role: blm lens strength; named after the game accessor ml::ScnRenderDrSysParmAcc::getBlmLensStrength.
  f32 m_blmLensParmMax;  // Inferred role: blm lens parm max; named after the game accessor ml::ScnRenderDrSysParmAcc::getBlmLensParmMax.
  f32 m_blmLensUVDecay;  // Inferred role: blm lens uv decay; named after the game accessor ml::ScnRenderDrSysParmAcc::getBlmLensUVDecay.
  bool m_godRay;         // Inferred role: god ray; named after the game accessor ml::ScnRenderDrSysParmAcc::isGodRay.
  u8 _00ed[0x00f0 - 0x00ed];
  f32 m_godRayWeight;   // Inferred role: god ray weight; named after the game accessor ml::ScnRenderDrSysParmAcc::getGodRayWeight.
  f32 m_godRayDecay;    // Inferred role: god ray decay; named after the game accessor ml::ScnRenderDrSysParmAcc::getGodRayDecay.
  f32 m_godRayStrength; // Inferred role: god ray strength; named after the game accessor ml::ScnRenderDrSysParmAcc::getGodRayStrength.
  bool m_AAOn;
  u8 _00fd[0x0100 - 0x00fd];
  f32 m_aAEdgeSharpness;    // Inferred role: aa edge sharpness; named after the game accessor ml::ScnRenderDrSysParmAcc::getAAEdgeSharpness.
  f32 m_aAEdgeThreshold;    // Inferred role: aa edge threshold; named after the game accessor ml::ScnRenderDrSysParmAcc::getAAEdgeThreshold.
  f32 m_aAEdgeThresholdMin; // Inferred role: aa edge threshold min; named after the game accessor ml::ScnRenderDrSysParmAcc::getAAEdgeThresholdMin.
  f32 m_aAEdgeRanges;       // Inferred role: aa edge ranges; named after the game accessor ml::ScnRenderDrSysParmAcc::getAAEdgeRanges.
  u8 _0110[0x0111 - 0x0110];
  bool m_TMAAOn;
  u8 _0112[0x0114 - 0x0112];
  f32 unknown114[6]; // Inferred role: tmaa sharpness; original member name unknown.
  f32 unknown12c[6]; // Inferred role: tmaa sharpness; original member name unknown.
  u8 _0144[0x0148 - 0x0144];
  // Inferred role: squared into the second gParam value of DrPixlPostMan::renderDeferredTemporal (0x7100844148); original member name unknown.
  f32 unknown148;
  u32 unknown14c; // Inferred role: tmaa jitter sample count, read by DrCalcViewWork::begin (1.0.0: 0x71008aab94); original member name unknown.
  // Inferred role: strength clamped to [0.2, 1] by DrPixlPostMan::renderDeferredTemporal (0x7100844174); original member name unknown.
  f32 unknown150;
  u8 _0154[0x0158 - 0x0154];
  bool unknown158; // Inferred role: tmaa reset request; original member name unknown.
  u8 _0159[0x016d - 0x0159];
  bool unknown16d; // Inferred role: tmaa sharpness pass flag, tested by DrPixlPostMan::render (0x7100845a54) with the AA and TMAA flags; original member name unknown.
  u8 _016e[0x0174 - 0x016e];
  bool unknown174; // Inferred role: tssao; original member name unknown.
  // Inferred role: tssao debug render; original member name unknown. Evidence: byte cleared by DrPixlPostParm::reset (strb at 0x710085bf98).
  bool unknown175;
  u8 _0176[0x0178 - 0x0176];
  // Inferred role: tssao ssao radius scale, first factor of the gParam uniform of DrPixlPostObjTSSAO::passQuaterNormal (0x71008c1ea0) and passSSAO
  // (0x71008c2388), squared in its second value; original member name unknown.
  f32 unknown178;
  // Inferred role: tssao upscale first parameter, first value of the gParam uniform written by DrPixlPostObjTSSAO::passUpScaleToMiddle
  // (0x71008c4544) and passUpScaleToFull (0x71008c485c); original member name unknown.
  f32 unknown17c;
  f32 unknown180; // Inferred role: tssao ssao strength, times 100 in the gParam2 uniform of passQuaterNormal and passSSAO; original member name unknown.
  f32 unknown184; // Inferred role: tssao upscale fourth parameter, last value of the same gParam uniform; original member name unknown.
  f32 unknown188; // Inferred role: tssao post blur strength; original member name unknown.
  f32 unknown18c; // Inferred role: tssao parameter blended by DrEnvColiParameter::calcParams (0x71007d4590); original member name unknown.
  f32 unknown190; // Inferred role: tssao upscale blend, the third gParam value is 1 - this clamped to [0, 1]; original member name unknown.
  bool m_sSAO;    // Inferred role: ssao; named after the game accessor ml::DrMan::setSSAO.
  u8 _0195[0x019c - 0x0195];
  f32 m_sSAOBlurStr; // Inferred role: ssao blur str; named after the game accessor ml::ScnRenderDrSysParmAcc::getSSAOBlurStr.
  u8 _01a0[0x01ca - 0x01a0];
  bool unknown1ca; // Inferred role: mot blur; original member name unknown.
  bool unknown1cb; // Inferred role: mot blur second flag, tested together with unknown1ca by isMotBlur; original member name unknown.
  bool unknown1cc; // Inferred role: motion blur render flag, tested by DrPixlPostObjMotionBlur::calcBlurWork (0x7100857e88); original member name unknown.
  bool unknown1cd; // Inferred role: obj mot blur; original member name unknown.
  bool m_appBlur;  // Inferred role: app blur; named after the game accessor ml::ScnRenderDrSysParmAcc::setAppBlur.
  bool unknown1cf; // Inferred role: motion blur 2 high level mode; original member name unknown.
  bool m_spBlur;   // Inferred role: sp blur; named after the game accessor ml::ScnRenderDrSysParmAcc::setSpBlur.
  u8 _01d1[0x01d4 - 0x01d1];
  f32 unknown1d4; // Inferred role: mot blur strength; original member name unknown.
  f32 unknown1d8; // Inferred role: mot blur sub; original member name unknown.
  u8 _01dc[0x01e0 - 0x01dc];
  f32 unknown1e0;   // Inferred role: first component of the motion blur dpch vector (DrPixlPostObjMotionBlur::calcBlurWork, 0x7100858024; loaded with unknown1e4 as one 64 bit pair); original member
                    // name unknown.
  f32 unknown1e4;   // Inferred role: third component of the motion blur dpch vector; original member name unknown.
  f32 unknown1e8;   // Inferred role: fourth component of the motion blur dpch vector; original member name unknown.
  f32 unknown1ec;   // Inferred role: obj mot blur strength; original member name unknown.
  f32 m_blurSpParm; // Inferred role: blur sp parm; named after the game accessor ml::ScnRenderDrSysParmAcc::setBlurSpParm.
  f32 unknown1f4;   // Inferred role: first component of the motion blur parameter (DrPixlPostObjMotionBlur::calcBlurWork, 0x71008588d4); original member name unknown.
  f32 unknown1f8;   // Inferred role: second component of the motion blur parameter, multiplied by the unknown798 of the view work (0x71008588e8); original member name unknown.
  bool m_motBlur2;
  u8 _01fd[0x0200 - 0x01fd];
  f32 unknown200;    // Inferred role: first component of the motion blur 2 dpch vector (DrPixlPostObjMotionBlur2::calcBlurWork, 0x71008bc294); original member name unknown.
  f32 unknown204;    // Inferred role: fourth component of the motion blur 2 dpch vector (the game loads it with unknown200 as one 64 bit pair, as two f32 members do); original member name unknown.
  f32 unknown208;    // Inferred role: motion blur 2 velocity blur scale, tested against zero and multiplied into the sizes by DrPixlPostObjMotionBlur2::calcVelocityBlur; original member name unknown.
  f32 unknown20c;    // Inferred role: second component of the motion blur 2 dpch vector; original member name unknown.
  f32 unknown210;    // Inferred role: third component of the motion blur 2 dpch vector, multiplied by the unknown798 of the view work; original member name unknown.
  f32 unknown214;    // Inferred role: motion blur 2 strength of the blur parameter; original member name unknown.
  bool unknown218;   // Inferred role: dof; original member name unknown.
  bool unknown219;   // Inferred role: dof override; original member name unknown.
  bool m_dofHLvMode; // Inferred role: dof h lv mode; named after the game accessor ml::ScnRenderDrSysParmAcc::isDofHLvMode.
  bool unknown21b;   // Inferred role: dof down sec; original member name unknown.
  bool m_dOFAutoFocus; // Inferred role: dof auto focus; named after the game accessor ml::ScnRenderDrSysParmAcc::isDOFAutoFocus.
  u8 _021d[0x021e - 0x021d];
  bool m_DOFAutoFocusDebug;
  u8 _021f[0x0220 - 0x021f];
  f32 m_doFPixlRatio;      // Inferred role: dof pixl ratio; named after the game accessor ml::ScnRenderDrSysParmAcc::getDoFPixlRatio.
  f32 m_doFDistance;       // Inferred role: dof distance; named after the game accessor ml::ScnRenderDrSysParmAcc::getDoFDistance.
  f32 m_doFRange;          // Inferred role: dof range; named after the game accessor ml::ScnRenderDrSysParmAcc::getDoFRange.
  f32 m_doFStrength;       // Inferred role: dof strength; named after the game accessor ml::ScnRenderDrSysParmAcc::getDoFStrength.
  f32 m_doFLens;           // Inferred role: dof lens; named after the game accessor ml::ScnRenderDrSysParmAcc::getDoFLens.
  f32 m_doFBlend;          // Inferred role: dof blend; named after the game accessor ml::ScnRenderDrSysParmAcc::getDoFBlend.
  s32 m_dofPixlLv;         // Inferred role: dof pixl lv; named after the game accessor ml::ScnRenderDrSysParmAcc::getDofPixlLv.
  s32 m_dOFFocusNum;       // Inferred role: dof focus num; named after the game accessor ml::ScnRenderDrSysParmAcc::getDOFFocusNum.
  f32 m_dOFFocusRatio;     // Inferred role: dof focus ratio; named after the game accessor ml::ScnRenderDrSysParmAcc::getDOFFocusRatio.
  f32 m_dOFFocusMin;       // Inferred role: dof focus min; named after the game accessor ml::ScnRenderDrSysParmAcc::getDOFFocusMin.
  bool m_dispGlobalIBLTex; // Inferred role: disp global ibl tex; named after the game accessor ml::ScnRenderDrSysParmAcc::isDispGlobalIBLTex.
  u8 _0249[0x024c - 0x0249];
  u32 unknown24c; // Inferred role: mip level of the debug IBL cube map display (DrPixlPostObjCubeMapIBL::debugRender); original member name unknown.
  u8 _0250[0x0269 - 0x0250];
  bool unknown269; // Inferred role: global IBL relight request enable; original member name unknown.
  bool m_colTblOn;
  u8 _026b[0x026c - 0x026b];
  u32 unknown26c;       // Inferred role: color filter near first texture id; original member name unknown.
  f32 m_colorFilterFrm; // Inferred role: color filter frm; named after the game accessor ml::ScnRenderDrSysParmAcc::getColorFilterFrm.
  bool m_colorFilterTransZ;
  u8 _0275[0x0278 - 0x0275];
  u32 unknown278; // Inferred role: color filter far first texture id; original member name unknown.
  f32 unknown27c;
  f32 unknown280;
  f32 unknown284;
  f32 unknown288;  // Inferred role: color filter parameters blended by DrEnvColiParameter::calcParams (0x71007d3a5c); original member name unknown.
  u32 unknown28c;  // Inferred role: color filter near second texture id; original member name unknown.
  u32 unknown290;  // Inferred role: color filter far second texture id; original member name unknown.
  f32 unknown294;  // Inferred role: color filter near ratio; original member name unknown.
  f32 unknown298;  // Inferred role: color filter far ratio; original member name unknown.
  bool unknown29c; // Inferred role: color filter flag set by DrEnvColiParameter::calcParams (0x71007d514c); original member name unknown.
  bool unknown29d; // Inferred role: color filter flag set by DrEnvColiParameter::calcParams (0x71007d5150); original member name unknown.
  u8 _029e[0x02a0 - 0x029e];
  f32 unknown2a0; // Inferred role: toon dir light scale; original member name unknown.
  u8 _02a4[0x02c4 - 0x02a4];
  f32 unknown2c4; // Inferred role: outline value scale; original member name unknown.
  u8 _02c8[0x02cc - 0x02c8];
  f32 unknown2cc; // Inferred role: outline range end; original member name unknown.
  f32 unknown2d0; // Inferred role: outline range start; original member name unknown.
  u8 _02d4[0x02e4 - 0x02d4];
  f32 unknown2e4; // Inferred role: value moved by DrEnvColiParameter::calcParams and clamped between unknown2e8 and 1 (0x71007d2e38); original member name unknown.
  f32 unknown2e8; // Inferred role: lower bound of unknown2e4; original member name unknown.
  u8 _02ec[0x02f0 - 0x02ec];
  bool unknown2f0; // Inferred role: enables the movement of unknown2e4; original member name unknown.
  u8 _02f1[0x0304 - 0x02f1];
  bool m_defferedColor; // Inferred role: deffered color; named after the game accessor ml::ScnRenderDrSysParmAcc::isDefferedColor.
  // Inferred role: deferred debug render flags 0x305 to 0x31d, read with m_defferedColor by DrPixlPostMan::debugDeferredRenderImpl (0x7100850af4), which lists them
  // in the order of the entries it renders (the entries 16, 19 and 21 are the bytes 0x313, 0x311 and 0x312); original member names unknown.
  bool unknown305;
  bool unknown306;
  bool unknown307;
  bool unknown308;
  bool unknown309;
  bool unknown30a;
  bool unknown30b;
  bool unknown30c;
  bool unknown30d;
  bool unknown30e;
  bool unknown30f;
  bool unknown310;
  bool unknown311;
  bool unknown312;
  bool unknown313;
  bool unknown314;
  bool unknown315; // Inferred role: enables its entry only when the refraction map target exists; original member name unknown.
  bool unknown316;
  bool unknown317;
  bool unknown318;
  bool unknown319;
  bool unknown31a;
  bool unknown31b;
  bool unknown31c;
  bool unknown31d;
  u8 _031e[0x0320 - 0x031e];
  unknown038 unknown320[8]; // Inferred role: g buff debug ranges; original member name unknown. The scene accessor writes the first five, DrPixlMan::debugGBuffRender reads all eight.
  f32 m_shadowStr;          // Inferred role: shadow str; named after the game accessor ml::ScnRenderDrSysParmAcc::getShadowStr.
  u8 _0364[0x037c - 0x0364];
  f32 m_shadowChacheAngle[10]; // Inferred role: shadow chache angle; named after the game accessor ml::ScnRenderDrSysParmAcc::getShadowChacheAngle.
  u8 _03a4[0x03b8 - 0x03a4];
  bool m_rainDropOn;
  u8 _03b9[0x03c0 - 0x03b9];
  f32 unknown3c0[6]; // Inferred role: rain drop value moved by DrEnvColiParameter::calcParams and clamped between 0 and unknown3c4 (0x71007d2d4c); original member name unknown.
  u8 _03d8[0x03dc - 0x03d8];
  f32 unknown3dc[27]; // Inferred role: rain drop values blended by DrEnvColiParameter::calcParams (0x71007d3d40); original member name unknown.
  u8 _0448[0x045c - 0x0448];
  f32 unknown45c; // Inferred role: rain drop parameter blended by DrEnvColiParameter::calcParams (0x71007d4b9c); original member name unknown.
  bool m_shwRaytrace;
  u8 _0461[0x0468 - 0x0461];
  f32 unknown468;    // Inferred role: sky luminance weight; original member name unknown.
  f32 unknown46c;    // Inferred role: sky luminance weight; original member name unknown.
  f32 m_specularStr; // Inferred role: specular str; named after the game accessor ml::ScnRenderDrSysParmAcc::getSpecularStr.
  u8 _0474[0x0480 - 0x0474];
  bool unknown480; // Inferred role: illuminance debug render, tested by DrPixlPostMan::render (0x7100845bfc); original member name unknown.
  u8 _0481[0x0484 - 0x0481];
  f32 unknown484;    // Inferred role: illuminance debug scale; original member name unknown.
  bool m_gBuffDebug; // Inferred role: g buff debug; named after the game accessor ml::ScnRenderDrSysParmAcc::setGBuffDebug.
  bool unknown489;   // Inferred role: SSR debug; original member name unknown.
  bool unknown48a;   // Inferred role: SSR; original member name unknown.
  u8 _048b[0x04d0 - 0x048b];
  bool m_glassBr; // Inferred role: glass br; named after the game accessor ml::ScnRenderDrSysParmAcc::isGlassBr.
  u8 _04d1[0x04d8 - 0x04d1];
  f32 unknown4d8;           // Inferred role: glass break parameter set by setGlassBrk; original member name unknown.
  f32 unknown4dc;           // Inferred role: glass break parameter set by setGlassBrk; original member name unknown.
  f32 unknown4e0;           // Inferred role: glass break parameter set by setGlassBrk; original member name unknown.
  f32 unknown4e4;           // Inferred role: glass break parameter set by setGlassBrk; original member name unknown.
  f32 unknown4e8;           // Inferred role: glass break parameter set by setGlassBrk; original member name unknown.
  f32 unknown4ec;           // Inferred role: glass break parameter set by setGlassBrk; original member name unknown.
  f32 unknown4f0;           // Inferred role: glass break parameter set by setGlassBrk; original member name unknown.
  f32 unknown4f4;           // Inferred role: glass break parameter set by setGlassBrk; original member name unknown.
  f32 unknown4f8;           // Inferred role: glass break parameter set by setGlassBrk; original member name unknown.
  f32 unknown4fc;           // Inferred role: glass break parameter set by setGlassBrk; original member name unknown.
  f32 unknown500;           // Inferred role: glass break parameter set by setGlassBrk; original member name unknown.
  f32 unknown504;           // Inferred role: glass break parameter set by setGlassBrk; original member name unknown.
  f32 unknown508;           // Inferred role: glass break parameter set by setGlassBrk; original member name unknown.
  f32 unknown50c;           // Inferred role: glass break parameter set by setGlassBrk; original member name unknown.
  f32 unknown510;           // Inferred role: glass break parameter set by setGlassBrk; original member name unknown.
  unknown039 unknown514[2]; // Inferred role: dbl parms; original member name unknown.
  bool unknownf54;          // Inferred role: histgram reset; original member name unknown.
  u8 _0f55[0x0f58 - 0x0f55];
  s32 unknownf58; // Inferred role: bloom scale type; original member name unknown.
  f32 unknownf5c; // Inferred role: tone ratio below which setToneStr blends the strength; original member name unknown. `ldr s0, [x9, #0xf5c]` in DrPixlMan::setToneStr 0x710083df60.
  f32 unknownf60; // Inferred role: first bound of the tone value range; original member name unknown. `ldr s4, [x9, #0xf60]` at 0x710083dfcc.
  f32 unknownf64; // Inferred role: second bound (maximum) of the tone value range; original member name unknown. `ldr s8, [x9, #0xf64]` at 0x710083dfd0.
  u8 _0f68[0x0f71 - 0x0f68];
  bool unknownf71; // Inferred role: bloom down scale with the reduction offsets; original member name unknown. `ldrb w8, [x19, #0xf71]` at 0x7100854444 (calculateDownScaleImpl).
  bool unknownf72; // Inferred role: blm 2 pass; original member name unknown.
  bool unknownf73; // Inferred role: selects the second bloom buffer for the bloom render; original member name unknown.
  u32 unknownf74;  // Inferred role: bloom debug render target index; original member name unknown. `ldr w10, [x10, #0xf74]` with an unsigned clamp at 0x71008553cc, `str wzr` in DrPixlPostParm::reset
                   // 0x710085c1c0.
  u32 unknownf78;  // Inferred role: SSR debug scale shift; original member name unknown.
  u8 _0f7c[0x0f94 - 0x0f7c];
  f32 unknownf94; // Inferred role: tssao prev blur strength; original member name unknown.
  u8 _0f98[0x0fa0 - 0x0f98];
  // Inferred role: tssao option whose target DrPixlPostObjTSSAO::debugRender shows; original member name unknown. Evidence: byte cleared by
  // DrPixlPostParm::reset (strb at 0x710085c3a8) and read by DrPixlPostObjTSSAO::passSSAO (ldrb at 0x71008c2400).
  bool unknownfa0;
  u8 _0fa1[0x0fa4 - 0x0fa1];
  // Inferred role: tssao ssao second value copied unchanged into the gParam2 uniform of DrPixlPostObjTSSAO::passQuaterNormal (0x71008c1ea0) and
  // passSSAO (0x71008c2388); original member name unknown.
  f32 unknownfa4;
  u8 _0fa8[0x0fb0 - 0x0fa8];
  bool unknownfb0;  // Inferred role: tssao ssao mpf skip, selects the MPF_SKIP declaration of DrPixlPostObjTSSAO::passSSAO; original member name unknown.
  bool unknownfb1;  // Inferred role: tssao quarter normal; original member name unknown.
  bool m_reduction; // Inferred role: reduction; named after the game accessor ml::ScnRenderDrSysParmAcc::isReduction.
  bool unknownfb3;  // Inferred role: reduction buffer; original member name unknown.
  bool unknownfb4;  // Inferred role: separate trans; original member name unknown.
  u8 _0fb5[0x0fb8 - 0x0fb5];
  f32 m_reductionScX; // Inferred role: reduction sc x; named after the game accessor ml::ScnRenderDrSysParmAcc::getReductionScX.
  f32 m_reductionScY; // Inferred role: reduction sc y; named after the game accessor ml::ScnRenderDrSysParmAcc::getReductionScY.
  f32 unknownfc0;     // Inferred role: reduction buffer sc x; original member name unknown.
  f32 unknownfc4;     // Inferred role: reduction buffer sc y; original member name unknown.
  u32 unknownfc8;     // Inferred role: ofs render check; original member name unknown.
  u8 _0fcc[0x0fdc - 0x0fcc];
  f32 unknownfdc; // Inferred role: reduction trans sc x; original member name unknown.
  f32 unknownfe0; // Inferred role: reduction trans sc y; original member name unknown.
  s32 unknownfe4; // Inferred role: render mode; original member name unknown.
  u8 _0fe8[0x0ff0 - 0x0fe8];
  mm::Vec3 unknownff0; // Inferred role: sp blur target; original member name unknown.
  bool unknown1000;    // Inferred role: debug blur mask render; original member name unknown.
  u8 _1001[0x1008 - 0x1001];
  s32 unknown1008; // Inferred role: debug mode of DrPixlShadowRaytrace::debugRender (1 draws three targets, 2 to 4 one); original member name unknown. Split out of _1001 (decision 2026-11-14 #17).
  u8 _100c[0x1010 - 0x100c];
  f32 unknown1010; // Inferred role: shw raytrace temporal filtering depth scale, its inverse is the third value of gParam (DrPixlShadowRaytrace::temporalFiltering, 0x71008c6420); original member name
                   // unknown.
  u8 _1014[0x101c - 0x1014];
  f32 unknown101c; // Inferred role: unbranch to depth quarter size scale parameter; original member name unknown.
  u8 _1020[0x1024 - 0x1020];
  bool unknown1024; // Inferred role: shw raytrace temporal; original member name unknown.
  bool unknown1025; // Inferred role: debug shadow render; original member name unknown.
  u8 _1026[0x1027 - 0x1026];
  bool unknown1027; // Inferred role: debug deferred render; original member name unknown.
  bool unknown1028; // Inferred role: debug shadow cache render; original member name unknown.
  u8 _1029[0x102c - 0x1029];
  f32 unknown102c; // Inferred role: debug shadow cache render grid count; original member name unknown.
  u8 _1030[0x103c - 0x1030];
  bool unknown103c;     // Inferred role: temporal shadow enable; original member name unknown.
  bool unknown103d;     // Inferred role: temporal shadow history valid; original member name unknown.
  bool m_charDirShadow; // Inferred role: char dir shadow; named after the game accessor ml::ScnRenderDrSysParmAcc::isCharDirShadow.
  u8 _103f[0x1048 - 0x103f];
  f32 unknown1048; // Inferred role: temporal shadow buffer scale; original member name unknown.
  u8 _104c[0x105f - 0x104c];
  bool unknown105f; // Inferred role: fade direction flag of the global IBL direct render (DrShdLgtGlobalIBL::renderDirect, `ldrb w8, [x8, x9]` with x9 = 0x105f at 0x7100898558); original member name
                    // unknown.
  u8 _1060[0x1061 - 0x1060];
  bool unknown1061; // Inferred role: selects the IBL pixl objs; original member name unknown.
  u8 _1062[0x1064 - 0x1062];
  f32 unknown1064; // Inferred role: toon gradation value set from the ambient light data; original member name unknown.
  u8 _1068[0x1074 - 0x1068];
  bool unknown1074; // Inferred role: 3D LUT debug display flag, read by DrPixlPostObj3dLut::debugRender; original member name unknown.
  u8 _1075[0x1078 - 0x1075];
  s32 unknown1078; // Inferred role: 3D LUT debug display slice, read by DrPixlPostObj3dLut::debugRender; original member name unknown.
  s32 m_lightNum;  // Inferred role: light num; named after the game accessor ml::ScnRenderDrSysParmAcc::getLightNum.
  bool m_inOut;    // Inferred role: in out; named after the game accessor ml::ScnRenderDrSysParmAcc::isInOut.
  u8 _1081[0x1084 - 0x1081];
  s32 m_weather; // Inferred role: weather; named after the game accessor ml::ScnRenderDrSysParmAcc::getWeather.
  f32 m_weatherFrame[2];
  f32 unknown1090; // Inferred role: wetness, the product of unknown10a4 and unknown10ac (0x71007d2ccc); original member name unknown.
  u8 _1094[0x109c - 0x1094];
  f32 unknown109c; // Inferred role: wetness value, its ini default is the fallback of DrIniSys::getWetnessSetting; original member name unknown.
  f32 unknown10a0; // Inferred role: second wetness ratio (0x71007d2cd0); original member name unknown.
  f32 unknown10a4; // Inferred role: first wetness ratio; original member name unknown.
  f32 unknown10a8; // Inferred role: second wetness ratio; original member name unknown.
  f32 unknown10ac; // Inferred role: rain wetness, moved by the rain fade frames; original member name unknown.
  f32 unknown10b0; // Inferred role: first wetness step per frame; original member name unknown.
  f32 unknown10b4; // Inferred role: second wetness step per frame; original member name unknown.
  u32 unknown10b8; // Inferred role: rain wetness frames when getting wet; original member name unknown.
  u32 unknown10bc; // Inferred role: rain wetness frames when drying; original member name unknown.
  u32 unknown10c0; // Inferred role: rain drop fade frames; original member name unknown.
  u8 _10c4[0x10d4 - 0x10c4];
  f32 unknown10d4;    // Inferred role: first area parameter, set from the seam resource area table; original member name unknown.
  f32 unknown10d8;    // Inferred role: second area parameter, set from the seam resource area table; original member name unknown.
  f32 unknown10dc;    // Inferred role: third area parameter, set from the seam resource area table; original member name unknown.
  s32 unknown10e0[4]; // Inferred role: g buff debug counts; original member name unknown.
  u8 _10f0[0x10fc - 0x10f0];
  bool unknown10fc; // Inferred role: attri menu closed; original member name unknown.
  u8 _10fd[0x10fe - 0x10fd];
  bool m_dispReduction; // Inferred role: disp reduction; named after the game accessor ml::ScnRenderDrSysParmAcc::isDispReduction.
  u8 _10ff[0x1104 - 0x10ff];
  bool unknown1104;    // Inferred role: SSR disable by scene; original member name unknown.
  bool unknown1105[2]; // Inferred role: reset scenes; original member name unknown.
  u8 _1107[0x1110 - 0x1107];
};

static_assert(offsetof(DrPixlPostParm, m_toneMapOn) == 0x0000, "");
static_assert(offsetof(DrPixlPostParm, m_toneMax) == 0x0008, "");
static_assert(offsetof(DrPixlPostParm, m_toneMin) == 0x000c, "");
static_assert(offsetof(DrPixlPostParm, m_toneRatio) == 0x0010, "");
static_assert(offsetof(DrPixlPostParm, m_toneRatioLast) == 0x0014, "");
static_assert(offsetof(DrPixlPostParm, m_toneBlmMax) == 0x0018, "");
static_assert(offsetof(DrPixlPostParm, m_toneBlmMin) == 0x001c, "");
static_assert(offsetof(DrPixlPostParm, m_toneBlmRatio) == 0x0020, "");
static_assert(offsetof(DrPixlPostParm, unknown48a) == 0x048a, "");
static_assert(offsetof(DrPixlPostParm, unknown1104) == 0x1104, "");
static_assert(offsetof(DrPixlPostParm, m_toneBlmRatioLast) == 0x0024, "");
static_assert(offsetof(DrPixlPostParm, unknown28) == 0x0028, "");
static_assert(offsetof(DrPixlPostParm, unknown2c) == 0x002c, "");
static_assert(offsetof(DrPixlPostParm, m_bloomOn) == 0x003c, "");
static_assert(offsetof(DrPixlPostParm, unknown3d) == 0x003d, "");
static_assert(offsetof(DrPixlPostParm, m_lensFlare) == 0x003e, "");
static_assert(offsetof(DrPixlPostParm, m_borderBlmSub) == 0x0040, "");
static_assert(offsetof(DrPixlPostParm, m_borderBlmMul) == 0x0044, "");
static_assert(offsetof(DrPixlPostParm, m_borderBlmSecSub) == 0x0048, "");
static_assert(offsetof(DrPixlPostParm, m_borderBlmSecMul) == 0x004c, "");
static_assert(offsetof(DrPixlPostParm, unknown30) == 0x0030, "");
static_assert(offsetof(DrPixlPostParm, m_borderBlmMax) == 0x0050, "");
static_assert(offsetof(DrPixlPostParm, m_blmWeight) == 0x0054, "");
static_assert(offsetof(DrPixlPostParm, m_blmStr) == 0x007c, "");
static_assert(offsetof(DrPixlPostParm, unknownc0) == 0x00c0, "");
static_assert(offsetof(DrPixlPostParm, m_blmLensSub) == 0x00c8, "");
static_assert(offsetof(DrPixlPostParm, m_blmLensMul) == 0x00cc, "");
static_assert(offsetof(DrPixlPostParm, m_blmLensMax) == 0x00d0, "");
static_assert(offsetof(DrPixlPostParm, m_blmLensRot) == 0x00d4, "");
static_assert(offsetof(DrPixlPostParm, m_blmLensWeight) == 0x00d8, "");
static_assert(offsetof(DrPixlPostParm, m_blmLensDecay) == 0x00dc, "");
static_assert(offsetof(DrPixlPostParm, m_blmLensStrength) == 0x00e0, "");
static_assert(offsetof(DrPixlPostParm, m_blmLensParmMax) == 0x00e4, "");
static_assert(offsetof(DrPixlPostParm, m_blmLensUVDecay) == 0x00e8, "");
static_assert(offsetof(DrPixlPostParm, m_godRay) == 0x00ec, "");
static_assert(offsetof(DrPixlPostParm, m_godRayWeight) == 0x00f0, "");
static_assert(offsetof(DrPixlPostParm, m_godRayDecay) == 0x00f4, "");
static_assert(offsetof(DrPixlPostParm, m_godRayStrength) == 0x00f8, "");
static_assert(offsetof(DrPixlPostParm, m_AAOn) == 0x00fc, "");
static_assert(offsetof(DrPixlPostParm, m_aAEdgeSharpness) == 0x0100, "");
static_assert(offsetof(DrPixlPostParm, unknown114) == 0x0114, "");
static_assert(offsetof(DrPixlPostParm, unknown12c) == 0x012c, "");
static_assert(offsetof(DrPixlPostParm, unknown148) == 0x0148, "");
static_assert(offsetof(DrPixlPostParm, unknown14c) == 0x014c, "");
static_assert(offsetof(DrPixlPostParm, unknown150) == 0x0150, "");
static_assert(offsetof(DrPixlPostParm, unknown158) == 0x0158, "");
static_assert(offsetof(DrPixlPostParm, unknown174) == 0x0174, "");
static_assert(offsetof(DrPixlPostParm, unknown175) == 0x0175, "");
static_assert(offsetof(DrPixlPostParm, unknown178) == 0x0178, "");
static_assert(offsetof(DrPixlPostParm, unknown17c) == 0x017c, "");
static_assert(offsetof(DrPixlPostParm, unknown180) == 0x0180, "");
static_assert(offsetof(DrPixlPostParm, unknown184) == 0x0184, "");
static_assert(offsetof(DrPixlPostParm, unknown188) == 0x0188, "");
static_assert(offsetof(DrPixlPostParm, unknown190) == 0x0190, "");
static_assert(offsetof(DrPixlPostParm, m_aAEdgeThreshold) == 0x0104, "");
static_assert(offsetof(DrPixlPostParm, m_aAEdgeThresholdMin) == 0x0108, "");
static_assert(offsetof(DrPixlPostParm, m_aAEdgeRanges) == 0x010c, "");
static_assert(offsetof(DrPixlPostParm, m_TMAAOn) == 0x0111, "");
static_assert(offsetof(DrPixlPostParm, unknown16d) == 0x016d, "");
static_assert(offsetof(DrPixlPostParm, m_sSAO) == 0x0194, "");
static_assert(offsetof(DrPixlPostParm, m_sSAOBlurStr) == 0x019c, "");
static_assert(offsetof(DrPixlPostParm, unknown1ca) == 0x01ca, "");
static_assert(offsetof(DrPixlPostParm, unknown1cc) == 0x01cc, "");
static_assert(offsetof(DrPixlPostParm, unknown1cd) == 0x01cd, "");
static_assert(offsetof(DrPixlPostParm, m_appBlur) == 0x01ce, "");
static_assert(offsetof(DrPixlPostParm, unknown1cf) == 0x01cf, "");
static_assert(offsetof(DrPixlPostParm, m_spBlur) == 0x01d0, "");
static_assert(offsetof(DrPixlPostParm, unknown1d4) == 0x01d4, "");
static_assert(offsetof(DrPixlPostParm, unknown1d8) == 0x01d8, "");
static_assert(offsetof(DrPixlPostParm, unknown1e0) == 0x01e0, "");
static_assert(offsetof(DrPixlPostParm, unknown1e4) == 0x01e4, "");
static_assert(offsetof(DrPixlPostParm, unknown1e8) == 0x01e8, "");
static_assert(offsetof(DrPixlPostParm, unknown1ec) == 0x01ec, "");
static_assert(offsetof(DrPixlPostParm, m_blurSpParm) == 0x01f0, "");
static_assert(offsetof(DrPixlPostParm, unknown1f4) == 0x01f4, "");
static_assert(offsetof(DrPixlPostParm, unknown1f8) == 0x01f8, "");
static_assert(offsetof(DrPixlPostParm, m_motBlur2) == 0x01fc, "");
static_assert(offsetof(DrPixlPostParm, unknown200) == 0x0200, "");
static_assert(offsetof(DrPixlPostParm, unknown204) == 0x0204, "");
static_assert(offsetof(DrPixlPostParm, unknown208) == 0x0208, "");
static_assert(offsetof(DrPixlPostParm, unknown20c) == 0x020c, "");
static_assert(offsetof(DrPixlPostParm, unknown210) == 0x0210, "");
static_assert(offsetof(DrPixlPostParm, unknown214) == 0x0214, "");
static_assert(offsetof(DrPixlPostParm, unknown218) == 0x0218, "");
static_assert(offsetof(DrPixlPostParm, unknown219) == 0x0219, "");
static_assert(offsetof(DrPixlPostParm, m_dofHLvMode) == 0x021a, "");
static_assert(offsetof(DrPixlPostParm, unknown21b) == 0x021b, "");
static_assert(offsetof(DrPixlPostParm, m_dOFAutoFocus) == 0x021c, "");
static_assert(offsetof(DrPixlPostParm, m_DOFAutoFocusDebug) == 0x021e, "");
static_assert(offsetof(DrPixlPostParm, m_doFPixlRatio) == 0x0220, "");
static_assert(offsetof(DrPixlPostParm, m_doFDistance) == 0x0224, "");
static_assert(offsetof(DrPixlPostParm, m_doFRange) == 0x0228, "");
static_assert(offsetof(DrPixlPostParm, m_doFStrength) == 0x022c, "");
static_assert(offsetof(DrPixlPostParm, m_doFLens) == 0x0230, "");
static_assert(offsetof(DrPixlPostParm, m_doFBlend) == 0x0234, "");
static_assert(offsetof(DrPixlPostParm, m_dofPixlLv) == 0x0238, "");
static_assert(offsetof(DrPixlPostParm, m_dOFFocusNum) == 0x023c, "");
static_assert(offsetof(DrPixlPostParm, m_dOFFocusRatio) == 0x0240, "");
static_assert(offsetof(DrPixlPostParm, m_dOFFocusMin) == 0x0244, "");
static_assert(offsetof(DrPixlPostParm, m_dispGlobalIBLTex) == 0x0248, "");
static_assert(offsetof(DrPixlPostParm, unknown24c) == 0x024c, "");
static_assert(offsetof(DrPixlPostParm, unknown269) == 0x0269, "");
static_assert(offsetof(DrPixlPostParm, m_colTblOn) == 0x026a, "");
static_assert(offsetof(DrPixlPostParm, unknown26c) == 0x026c, "");
static_assert(offsetof(DrPixlPostParm, unknown278) == 0x0278, "");
static_assert(offsetof(DrPixlPostParm, unknown28c) == 0x028c, "");
static_assert(offsetof(DrPixlPostParm, unknown294) == 0x0294, "");
static_assert(offsetof(DrPixlPostParm, unknown298) == 0x0298, "");
static_assert(offsetof(DrPixlPostParm, m_colorFilterFrm) == 0x0270, "");
static_assert(offsetof(DrPixlPostParm, m_colorFilterTransZ) == 0x0274, "");
static_assert(offsetof(DrPixlPostParm, unknown2a0) == 0x02a0, "");
static_assert(offsetof(DrPixlPostParm, unknown2c4) == 0x02c4, "");
static_assert(offsetof(DrPixlPostParm, unknown2cc) == 0x02cc, "");
static_assert(offsetof(DrPixlPostParm, unknown2d0) == 0x02d0, "");
static_assert(offsetof(DrPixlPostParm, m_defferedColor) == 0x0304, "");
static_assert(offsetof(DrPixlPostParm, unknown310) == 0x0310, "");
static_assert(offsetof(DrPixlPostParm, unknown313) == 0x0313, "");
static_assert(offsetof(DrPixlPostParm, unknown31d) == 0x031d, "");
static_assert(offsetof(DrPixlPostParm, unknown320) == 0x0320, "");
static_assert(offsetof(DrPixlPostParm, m_shadowStr) == 0x0360, "");
static_assert(offsetof(DrPixlPostParm, m_shadowChacheAngle) == 0x037c, "");
static_assert(offsetof(DrPixlPostParm, m_rainDropOn) == 0x03b8, "");
static_assert(offsetof(DrPixlPostParm, m_shwRaytrace) == 0x0460, "");
static_assert(offsetof(DrPixlPostParm, unknown480) == 0x0480, "");
static_assert(offsetof(DrPixlPostParm, unknown484) == 0x0484, "");
static_assert(offsetof(DrPixlPostParm, unknown468) == 0x0468, "");
static_assert(offsetof(DrPixlPostParm, unknown46c) == 0x046c, "");
static_assert(offsetof(DrPixlPostParm, m_specularStr) == 0x0470, "");
static_assert(offsetof(DrPixlPostParm, m_gBuffDebug) == 0x0488, "");
static_assert(offsetof(DrPixlPostParm, unknown489) == 0x0489, "");
static_assert(offsetof(DrPixlPostParm, m_glassBr) == 0x04d0, "");
static_assert(offsetof(DrPixlPostParm, unknown514) == 0x0514, "");
static_assert(offsetof(DrPixlPostParm, unknownf54) == 0x0f54, "");
static_assert(offsetof(DrPixlPostParm, unknownf58) == 0x0f58, "");
static_assert(offsetof(DrPixlPostParm, unknownf5c) == 0x0f5c, "");
static_assert(offsetof(DrPixlPostParm, unknownf60) == 0x0f60, "");
static_assert(offsetof(DrPixlPostParm, unknownf64) == 0x0f64, "");
static_assert(offsetof(DrPixlPostParm, unknownf72) == 0x0f72, "");
static_assert(offsetof(DrPixlPostParm, unknownf71) == 0x0f71, "");
static_assert(offsetof(DrPixlPostParm, unknownf74) == 0x0f74, "");
static_assert(offsetof(DrPixlPostParm, unknownf73) == 0x0f73, "");
static_assert(offsetof(DrPixlPostParm, unknownf94) == 0x0f94, "");
static_assert(offsetof(DrPixlPostParm, unknownfa0) == 0x0fa0, "");
static_assert(offsetof(DrPixlPostParm, unknownfa4) == 0x0fa4, "");
static_assert(offsetof(DrPixlPostParm, unknownfb0) == 0x0fb0, "");
static_assert(offsetof(DrPixlPostParm, unknownf78) == 0x0f78, "");
static_assert(offsetof(DrPixlPostParm, unknownfb1) == 0x0fb1, "");
static_assert(offsetof(DrPixlPostParm, m_reduction) == 0x0fb2, "");
static_assert(offsetof(DrPixlPostParm, unknownfb3) == 0x0fb3, "");
static_assert(offsetof(DrPixlPostParm, unknownfb4) == 0x0fb4, "");
static_assert(offsetof(DrPixlPostParm, unknownfdc) == 0x0fdc, "");
static_assert(offsetof(DrPixlPostParm, m_reductionScX) == 0x0fb8, "");
static_assert(offsetof(DrPixlPostParm, m_reductionScY) == 0x0fbc, "");
static_assert(offsetof(DrPixlPostParm, unknownfc0) == 0x0fc0, "");
static_assert(offsetof(DrPixlPostParm, unknownfc8) == 0x0fc8, "");
static_assert(offsetof(DrPixlPostParm, unknownff0) == 0x0ff0, "");
static_assert(offsetof(DrPixlPostParm, unknown1000) == 0x1000, "");
static_assert(offsetof(DrPixlPostParm, unknown1008) == 0x1008, "");
static_assert(offsetof(DrPixlPostParm, unknown1010) == 0x1010, "");
static_assert(offsetof(DrPixlPostParm, unknown101c) == 0x101c, "");
static_assert(offsetof(DrPixlPostParm, unknown1024) == 0x1024, "");
static_assert(offsetof(DrPixlPostParm, unknown1025) == 0x1025, "");
static_assert(offsetof(DrPixlPostParm, unknown1027) == 0x1027, "");
static_assert(offsetof(DrPixlPostParm, unknown1028) == 0x1028, "");
static_assert(offsetof(DrPixlPostParm, unknown102c) == 0x102c, "");
static_assert(offsetof(DrPixlPostParm, unknown103c) == 0x103c, "");
static_assert(offsetof(DrPixlPostParm, unknown103d) == 0x103d, "");
static_assert(offsetof(DrPixlPostParm, m_charDirShadow) == 0x103e, "");
static_assert(offsetof(DrPixlPostParm, unknown1048) == 0x1048, "");
static_assert(offsetof(DrPixlPostParm, unknown105f) == 0x105f, "");
static_assert(offsetof(DrPixlPostParm, unknown1061) == 0x1061, "");
static_assert(offsetof(DrPixlPostParm, unknown1064) == 0x1064, "");
static_assert(offsetof(DrPixlPostParm, unknown1074) == 0x1074, "");
static_assert(offsetof(DrPixlPostParm, unknown1078) == 0x1078, "");
static_assert(offsetof(DrPixlPostParm, m_lightNum) == 0x107c, "");
static_assert(offsetof(DrPixlPostParm, m_inOut) == 0x1080, "");
static_assert(offsetof(DrPixlPostParm, m_weather) == 0x1084, "");
static_assert(offsetof(DrPixlPostParm, m_weatherFrame) == 0x1088, "");
static_assert(offsetof(DrPixlPostParm, unknown109c) == 0x109c, "");
static_assert(offsetof(DrPixlPostParm, unknown10c0) == 0x10c0, "");
static_assert(offsetof(DrPixlPostParm, unknown10d4) == 0x10d4, "");
static_assert(offsetof(DrPixlPostParm, unknown10dc) == 0x10dc, "");
static_assert(offsetof(DrPixlPostParm, unknown10e0) == 0x10e0, "");
static_assert(offsetof(DrPixlPostParm, unknown10fc) == 0x10fc, "");
static_assert(offsetof(DrPixlPostParm, m_dispReduction) == 0x10fe, "");
static_assert(offsetof(DrPixlPostParm, unknown1105) == 0x1105, "");
static_assert(sizeof(DrPixlPostParm) == 0x1110, "");
static_assert(sizeof(DrPixlPostParm::stRainDropLayerInfo) == 0x14, "");

} // namespace ml
