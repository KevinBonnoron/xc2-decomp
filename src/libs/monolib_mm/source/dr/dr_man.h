#pragma once
#include <stddef.h>

#include "dr/dr_draw_work_info.h"
#include "ml/work_background.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_array.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace cloud {
class CloudMan;
} // namespace cloud

namespace ml {
class CriticalSection;
class DrAPCache;
class DrCalcMan;
class DrCalcGpuCost;
class DrCalcTexStreamMan;
class DrIniSys;
class DrEnvironmentMan;
class DrFogMan;
class DrGlobalIBLMan;
class DrIBLMan;
class DrIrrVolMan;
class DrLightMan;
class DrMdlMan;
class DrPixlTileParm;
class DrResFilterData;
class DrShdMan;
class IDrDrawCallback;
class DrPixlMan;
class DrPixlMemMan;
class DrPixlMdlSampler;
class DrPixlPostParm;
class Scn;
class WinProc;

enum FILE_PRIO {};
enum RenderSpecMode {};

struct DR_CAPCUBE_PARAM;

struct DR_VIEW_PARAM {
  s32 unknown00;                         // Inferred role: view position x; original member name unknown.
  s32 unknown04;                         // Inferred role: view position y; original member name unknown.
  s32 unknown08;                         // Inferred role: render system id; original member name unknown.
  bool unknown0c;                        // Role and original member name unknown.
  bool unknown0d;                        // Role and original member name unknown.
  bool unknown0e;                        // Role and original member name unknown.
  s32 *unknown10;                        // Inferred role: view size source; original member name unknown.
  bool *unknown18;                       // Role and original member name unknown.
  f32 *unknown20;                        // Role and original member name unknown.
  f32 *unknown28;                        // Role and original member name unknown.
  grlib::CGLibTextureBuffer **unknown30; // Inferred role: render target source; original member name unknown.
};

static_assert(offsetof(DR_VIEW_PARAM, unknown08) == 0x08, "");
static_assert(offsetof(DR_VIEW_PARAM, unknown0c) == 0x0c, "");
static_assert(offsetof(DR_VIEW_PARAM, unknown10) == 0x10, "");
static_assert(offsetof(DR_VIEW_PARAM, unknown18) == 0x18, "");
static_assert(offsetof(DR_VIEW_PARAM, unknown20) == 0x20, "");
static_assert(offsetof(DR_VIEW_PARAM, unknown28) == 0x28, "");
static_assert(offsetof(DR_VIEW_PARAM, unknown30) == 0x30, "");
static_assert(sizeof(DR_VIEW_PARAM) == 0x38, "");

struct DR_CAPTURE_PARAM {
  grlib::CGLibTextureBuffer *unknown00; // Inferred role: capture target; original member name unknown.
  u32 unknown08;                        // Inferred role: capture width; original member name unknown.
  u32 unknown0c;                        // Inferred role: capture height; original member name unknown.
  bool unknown10;                       // Inferred role: capture double index; original member name unknown.
};

static_assert(sizeof(DR_CAPTURE_PARAM) == 0x18, "");

struct DR_MODEL_TEXTURE {
  grlib::CGLibTextureBuffer *unknown00; // Inferred role: model texture; original member name unknown.
  bool unknown08;                       // Inferred role: texture enable; original member name unknown.
};

static_assert(sizeof(DR_MODEL_TEXTURE) == 0x10, "");

// Inferred role: screen info; original type name unknown.
struct unknown057 {
  u8 _00[0x18 - 0x00];
  s32 unknown18; // Inferred role: width; original member name unknown.
  s32 unknown1c; // Inferred role: height; original member name unknown.
  s32 unknown20; // Inferred role: render width; original member name unknown.
  s32 unknown24; // Inferred role: render height; original member name unknown.
  s32 unknown28; // Inferred role: screen width; original member name unknown.
  s32 unknown2c; // Inferred role: screen height; original member name unknown.
  s32 unknown30; // Inferred role: divisor of the screen share of a model (DrMdoMat::oneTextureStream); original member name unknown.
  u8 _34[0x38 - 0x34];
  u32 unknown38; // Inferred role: view flags; original member name unknown.
  u8 _3c[0x40 - 0x3c];
};

static_assert(offsetof(unknown057, unknown18) == 0x18, "");
static_assert(offsetof(unknown057, unknown20) == 0x20, "");
static_assert(offsetof(unknown057, unknown28) == 0x28, "");
static_assert(offsetof(unknown057, unknown30) == 0x30, "");
static_assert(offsetof(unknown057, unknown2c) == 0x2c, "");
static_assert(offsetof(unknown057, unknown38) == 0x38, "");
static_assert(sizeof(unknown057) == 0x40, "");

class DrMan : public IWorkBackground {
public:
  static DrMan *getIns();
  static DrMan *get();
  static CriticalSection &getCriticalSection();
  DrMan(Scn *scn);
  ~DrMan() override;
  void resetModelTexture(u32 index);
  void deleteAddRenderSystem(u32 id);
  void begin();
  void beginSetup();
  void end();
  void endSetup();
  void debugUpdate();
  int loopCnt();
  void apply(int loop);
  void applyView(int view);
  void applyBegin(int loop);
  void applyEnd(int loop);
  void applyViewBegin();
  void render(int loop);
  void renderView(int view);
  void renderBegin(int loop);
  void setAlphaRenderTarget();
  void setSkyGodRayRenderTarget();
  void renderEnd(int loop);
  void renderViewBegin();
  void renderViewEnd();
  void GBuffRender();
  void blurCallBackRender();
  static void setSRGBMode(bool isSRGBMode);
  void tail();
  void setMainRenderTarget();
  bool isIBLHalfRes() const;
  bool isIBLSkip() const;
  bool isTemporalUPSToGlobalIBL() const;
  void fastRender();
  void setCallBack(IDrDrawCallback *callback);
  void releaseCallBack(IDrDrawCallback *callback);
  void setCacherClearMode(bool cacherClearMode);
  void openPixelDebugWindow(WinProc *window);
  void openHistgramDebugWindow(WinProc *window);
  void memcpyLcDMA(void *destination, const void *source, u32 size);
  u32 getMem1AlphaFree();
  void setGblIdx(s32 id);
  void offGblIdx(s32 id);
  // Name from Xenoblade Chronicles DE: _ZNK2ml5DrMan8isGblIdxEi (same class, same bit test of the global index table; the DE copy also tests a second table).
  u32 isGblIdx(s32 id) const { return m_gblIdx[id >> 5] & (1 << (id & 31)); }
  void setTimeVal(f32 timeVal);
  void setGroupsDisp(s32 group, bool disp);
  void setReduction(bool isReduction, f32 scaleX, f32 scaleY);
  void setAutoReduction(bool autoReduction);
  void setAA(bool isAA);
  void setColorFilter(bool isColorFilter);
  void setSSAO(bool isSSAO);
  void setBloom(bool isBloom, bool isLensFlare);
  void setToneMap(bool isToneMap);
  void setMotionBlur(bool isMotionBlur);
  void setMotionBlur(f32 strength, f32 sub);
  void setDepthOfField(bool isDepthOfField);
  void setDepthOfFieldParm(f32 distance, f32 range, f32 strength, f32 blend);
  void setGlobalWind(const mm::Vec3 &globalWind);
  const mm::Vec3 &getGlobalWind() const;
  void callCubeMapRender(const DR_CAPCUBE_PARAM &param);
  static bool isSRGBMode();
  static bool isFogSRGB();
  static bool isSeamDebug();
  static void beginMetric(const char *name);
  static void endMetric(const char *name);
  void releaseFastLight(s32 index);
  void setAllMiddelTexStmChk(bool isCheck);
  bool isAllMiddelTexStmChk() const;
  void setSeamMapStmOk(bool isOk);
  bool isSeamMapStmOk() const;
  void setAvatarCapMode(s32 avatarCapMode);
  static void setDblNowIdx(int index);
  void bkgHomeMenu(bool isOpen) override;
  void createAddRenderSystem(DR_VIEW_PARAM *param);
  void startCapture(DR_CAPTURE_PARAM *param);
  void captureRender(bool isDouble);
  void setModelTexture(DR_MODEL_TEXTURE *texture, u32 index);

  // Inferred role: true when the renders of the current view are skipped; original name unknown.
  bool unknown058() const {
    s32 view = unknown1c98;
    return (unknown1c9c & (1 << view)) != 0;
  }

  // Inferred role: true when the view is active; original name unknown.
  // Evidence: the same bit test repeats in DrMan::beginSetup, DrMdoMat::checkCallBackParam and DrShdLgtGlobalIBL::update.
  bool unknown059(int view) const { return (unknown440[view].unknown38 & 1) != 0; }

  // Inferred name; kept as an exception to the unknown-name rule (AGENTS.md): single-user helper whose existence only the match proves; rename if a sibling build gives a symbol.
  // Selects a view (screen info, view index and the per view calc, light, fog, environment, IBL and global IBL managers). Its only user is DrMan::begin (1.0.0: 0x71007c9a08, two calls: the
  // loops at 0x71007c9a48 and 0x71007c9af0). Forms tried without the helper: the eight assignments written in each loop give the game's 138 instructions, but the induction variable updates of the
  // latch come out in another order (the +8 step of the manager arrays after the +16 and +13 steps of DrMdlMan::setupCate instead of before them; first difference at 0x71007c9ac8).
  void selectView(int view) {
    unknown5b8 = &unknown440[view];
    unknown1c98 = view;
    m_drCalcMan = unknowna0[view];
    unknown588 = unknownc0[view];
    m_drFogMan = unknowne0[view];
    m_drEnvironmentMan = unknown100[view];
    m_drIBLMan = unknown140[view];
    m_drGlobalIBLMan = unknown160[view];
  }

  static DrMan *s_pTop;
  static s32 s_nDblStockIdx;
  static s32 s_nDblIdx;
  static s32 s_nDblMemIdx;
  static s32 s_nDblNowIdx;
  static bool s_bSRGBMode;
  static bool s_bFogSRGB;
  static bool s_bSeamDebug;

  mtl::ALLOC_HANDLE unknown08; // Inferred role: mem; original member name unknown.
  mtl::ALLOC_HANDLE unknown0c; // Inferred role: mem sys; original member name unknown.
  mtl::ALLOC_HANDLE unknown10; // Inferred role: mem class; original member name unknown.
  mtl::ALLOC_HANDLE unknown14; // Inferred role: mem work; original member name unknown.
  mtl::ALLOC_HANDLE unknown18; // Inferred role: mem; original member name unknown.
  mtl::ALLOC_HANDLE unknown1c; // Inferred role: mem data ("DrData"); original member name unknown.
  mtl::ALLOC_HANDLE unknown20; // Inferred role: mem; original member name unknown.
  u8 _0024[0x0068 - 0x0024];
  Scn *unknown68;                                        // Inferred role: scn passed to the constructor, DrCalcViewWork::begin (1.0.0: 0x71008aa6e0) takes its camera; original member name unknown.
  DrIniSys *m_drIniSys;                                  // Inferred role: ini sys; original member name unknown.
  DrPixlMan *m_drPixlMan;                                // Inferred role: pixl man; original member name unknown.
  DrShdMan *m_drShdMan;                                  // Inferred role: shd man; original member name unknown.
  DrMdlMan *m_drMdlMan;                                  // Inferred role: mdl man; original member name unknown.
  DrIrrVolMan *m_drIrrVolMan;                            // Inferred role: irr vol man; original member name unknown.
  DrResFilterData *m_drResFilterData;                    // Inferred role: filter data; original member name unknown.
  mm::mtl::FixedArray<DrCalcMan *, 4> unknowna0;         // Inferred role: calc mans; original member name unknown.
  mm::mtl::FixedArray<DrLightMan *, 4> unknownc0;        // Inferred role: light mans; original member name unknown.
  mm::mtl::FixedArray<DrFogMan *, 4> unknowne0;          // Inferred role: fog mans; original member name unknown.
  mm::mtl::FixedArray<DrEnvironmentMan *, 4> unknown100; // Inferred role: environment mans; original member name unknown.
  mm::mtl::FixedArray<DrPixlPostParm *, 4> unknown120;   // Inferred role: post parms; original member name unknown.
  mm::mtl::FixedArray<DrIBLMan *, 4> unknown140;         // Inferred role: ibl mans; original member name unknown.
  mm::mtl::FixedArray<DrGlobalIBLMan *, 4> unknown160;   // Inferred role: global ibl mans; original member name unknown.
  DrPixlTileParm *m_drPixlTileParm;                      // Inferred role: tile parm; original member name unknown.
  DrPixlMdlSampler *m_drPixlMdlSampler;                  // Inferred role: model sampler; original member name unknown.
  DR_VIEW_PARAM unknown190[2][4];                        // Inferred role: additional render system view params; original member name unknown.
  s32 unknown350[2];                                     // Inferred role: additional render system counts; original member name unknown.
  u32 unknown358[2][4];                                  // Inferred role: deleted render system ids; original member name unknown.
  s32 unknown378[2];                                     // Inferred role: deleted render system counts; original member name unknown.
  DR_CAPTURE_PARAM m_DR_CAPTURE_PARAM[2];                // Inferred role: capture requests; original member name unknown.
  u32 unknown3b0;                                        // Inferred role: capture request mask; original member name unknown.
  u8 _03b4[0x03b8 - 0x03b4];
  DR_MODEL_TEXTURE unknown3b8[2][4];        // Inferred role: model textures; original member name unknown.
  u32 unknown438[2];                        // Inferred role: model texture update masks; original member name unknown.
  unknown057 unknown440[5];                 // Inferred role: screen info per view; original member name unknown.
  DrCalcMan *m_drCalcMan;                   // Inferred role: calc man; original member name unknown.
  DrLightMan *unknown588;                   // Inferred role: light man; original member name unknown.
  DrFogMan *m_drFogMan;                     // Inferred role: fog man; original member name unknown.
  DrEnvironmentMan *m_drEnvironmentMan;     // Inferred role: environment man; original member name unknown.
  DrIBLMan *m_drIBLMan;                     // Inferred role: ibl man; original member name unknown.
  DrGlobalIBLMan *m_drGlobalIBLMan;         // Inferred role: global ibl man; original member name unknown.
  DrCalcTexStreamMan *m_drCalcTexStreamMan; // Inferred role: tex stream man; original member name unknown.
  unknown057 *unknown5b8;                   // Inferred role: screen info; original member name unknown.
  DrAPCache *m_drAPCache;                   // Inferred role: ap cache; original member name unknown.
  DrCalcGpuCost *m_drCalcGpuCost;           // Inferred role: gpu cost; original member name unknown.
  DrPixlMemMan *m_drPixlMemMan;             // Inferred role: pixl mem man, created by the constructor (0x71007c8c5c); original member name unknown.
  IDrDrawCallback *unknown5d8[16];          // Inferred role: callbacks; original member name unknown.
  s32 unknown658;                           // Inferred role: callback num; original member name unknown.
  u8 _065c[0x0660 - 0x065c];
  IDrDrawWorkInfo m_iDrDrawWorkInfo[4]; // Inferred role: draw work infos; original member name unknown.
  s32 unknown1c60;                      // Inferred role: tmaa mode; original member name unknown.
  u8 _1c64[0x1c70 - 0x1c64];
  mm::Vec3 unknown1c70;     // Inferred role: seam map read pos; original member name unknown.
  bool m_seamMapAddPosMode; // Inferred role: seam map add pos mode; named after the game accessor ml::ScnRenderDrSysParmAcc::setSeamMapAddPosMode.
  u8 unknown1c81[2];        // Inferred role: capture modes; original member name unknown.
  bool unknown1c83;         // Inferred role: capture request, read by DrPixlPostMan::beginUpdate (0x710084199c); original member name unknown.
  f32 m_glbSpd;             // Inferred role: glb spd; named after the game accessor ml::ScnRenderDrSysParmAcc::getGlbSpd.
  f32 m_mdlSpd;             // Inferred role: mdl spd; named after the game accessor ml::ScnRenderDrSysParmAcc::getMdlSpd.
  f32 unknown1c8c;          // Inferred role: model speed scaled by the global speed; original member name unknown.
  f32 m_gamma;              // Inferred role: gamma; named after the game accessor ml::ScnRenderDrSysParmAcc::getGamma.
  u8 _1c94[0x1c98 - 0x1c94];
  s32 unknown1c98; // Inferred role: view index; original member name unknown.
  u32 unknown1c9c; // Inferred role: view render skip; original member name unknown.
  u8 _1ca0[0x1ca4 - 0x1ca0];
  f32 unknown1ca4[2]; // Inferred role: time vals; original member name unknown.
  f32 m_timerVal;     // Inferred role: timer val; named after the game accessor ml::ScnRenderDrSysParmAcc::getTimerVal.
  u8 _1cb0[0x1cc0 - 0x1cb0];
  bool unknown1cc0;      // Inferred role: home menu opened; original member name unknown.
  bool m_autoResetScene; // Inferred role: auto reset scene; named after the game accessor ml::ScnRenderDrSysParmAcc::setAutoResetScene.
  bool unknown1cc2; // Inferred role: render list flag, set to true by the constructor (0x71007c885c) and tested by DrMdoCtlNom::createRenderList, DrMdoCtlPos::createPosRenderList and the base and
                    // instance map render list updates (0x7100808718, 0x71008137f8, 0x7100821180, 0x7100823a70); original member name unknown.
  u8 _1cc3[0x1cc4 - 0x1cc3];
  bool m_mdlHeightTexSkip;  // Inferred role: mdl height tex skip; named after the game accessor ml::ScnRenderDrSysParmAcc::isMdlHeightTexSkip.
  bool m_heightTexSkip;     // Inferred role: height tex skip; named after the game accessor ml::ScnRenderDrSysParmAcc::isHeightTexSkip.
  bool m_seamHeightTexSkip; // Inferred role: seam height tex skip; named after the game accessor ml::ScnRenderDrSysParmAcc::isSeamHeightTexSkip.
  bool m_seamMapOpenMode;   // Inferred role: seam map open mode; named after the game accessor ml::ScnRenderDrSysParmAcc::isSeamMapOpenMode.
  bool m_screenDispOff;     // Inferred role: screen disp off; named after the game accessor ml::ScnRenderDrSysParmAcc::setScreenDispOff.
  bool m_writeZBuffer;      // Inferred role: write z buffer; named after the game accessor ml::ScnRenderDrSysParmAcc::setWriteZBuffer.
  u8 _1cca[0x1ccc - 0x1cca];
  s32 unknown1ccc;    // Inferred role: operation mode index of the distance tables; original member name unknown.
  f32 unknown1cd0[2]; // Inferred role: pos model far render distance per operation mode; original member name unknown.
  u8 _1cd8[0x1cfc - 0x1cd8];
  s32 unknown1cfc; // Inferred role: seam read lv; original member name unknown.
  f32 unknown1d00; // Inferred role: seam base map read distance, added to the read check distance by DrMdoCtlSeamBaseMap::readBaseMapCheck; original member name unknown.
  f32 unknown1d04; // Inferred role: seam base map vertex read distance, copied by DrMdoCtlSeamBaseMap::readBaseMapCheck; original member name unknown.
  f32 unknown1d08; // Inferred role: seam base map vertex middle read distance, copied by DrMdoCtlSeamBaseMap::readBaseMapCheck; original member name unknown.
  f32 unknown1d0c; // Inferred role: seam low map read distance, added to the read check distance by DrMdoCtlSeamLowMap::readLowMapCheck; original member name unknown.
  u8 _1d10[0x1d18 - 0x1d10];
  void *unknown1d18;               // Inferred role: memory block released by the destructor; original member name unknown.
  u32 *m_gblIdx;                   // Named after setGblIdx and offGblIdx, which write its bits; Xenoblade Chronicles DE has isGblIdx and clearGblIdx on its table.
  RenderSpecMode m_renderSpecMode; // Inferred role: render spec mode; named after the game accessor ml::ScnRenderDrSysParmAcc::setRenderSpecMode.
  u8 _1d2c[0x1d30 - 0x1d2c];
  mm::Vec3 m_globalWind[2];
  u8 _1d50[0x1d60 - 0x1d50];
  bool m_dispChara; // Inferred role: chara disp off; named after the game accessor ml::ScnRenderDrSysParmAcc::setDispChara.
  bool unknown1d61; // Inferred role: seam render skip; original member name unknown.
  bool unknown1d62; // Inferred role: copied to the draw work info of each view; original member name unknown.
  bool unknown1d63; // Inferred role: model render skip; original member name unknown.
  bool unknown1d64; // Inferred role: light pre pass and GBuff render skip; original member name unknown.
  bool unknown1d65; // Inferred role: refraction render skip; original member name unknown.
  bool unknown1d66; // Inferred role: alpha render skip; original member name unknown.
  bool unknown1d67; // Inferred role: sp alpha render skip; original member name unknown.
  bool unknown1d68; // Inferred role: shadow render skip; original member name unknown.
  bool unknown1d69; // Inferred role: seam base map shadow render skip; original member name unknown.
  bool unknown1d6a; // Inferred role: occlusion render skip; original member name unknown.
  bool unknown1d6b; // Inferred role: seam mpf map render skip; original member name unknown.
  bool unknown1d6c; // Inferred role: seam env map render skip; original member name unknown.
  u8 _1d6d[0x1d6e - 0x1d6d];
  bool unknown1d6e; // Inferred role: skips the light buffer render of DrPixlDeferred::fastDeferredRender; original member name unknown.
  u8 _1d6f[0x1d70 - 0x1d6f];
  bool unknown1d70; // Inferred role: shadow light skip; original member name unknown.
  bool m_fogSkip;   // Inferred role: fog skip; named after the game accessor ml::ScnRenderDrSysParmAcc::setFogSkip.
  u8 _1d72[0x1d73 - 0x1d72];
  bool unknown1d73; // Inferred role: simple shadow render skip, read by DrMdoSmlShadowMan::shadowRender; original member name unknown.
  u8 _1d74[0x1d75 - 0x1d74];
  bool unknown1d75; // Inferred role: IBL skip; original member name unknown.
  u8 _1d76[0x1d78 - 0x1d76];
  bool unknown1d78; // Inferred role: skips the clustered light render of DrPixlDeferred::fastDeferredRender; original member name unknown.
  u8 _1d79[0x1d7a - 0x1d79];
  bool unknown1d7a;   // Inferred role: shadow map override; original member name unknown.
  bool m_mdlDblPause; // Inferred role: mdl dbl pause; named after the game accessor ml::ScnRenderDrSys::setMdlDblPause.
  bool unknown1d7c;   // Inferred role: skips the mpf wind update; original member name unknown.
  bool unknown1d7d;   // Inferred role: skips the deferred render and the sky render of a view; original member name unknown.
  bool unknown1d7e;   // Inferred role: skips GBuffRender; original member name unknown.
  u8 _1d7f[0x1d80 - 0x1d7f];
  bool m_clip; // Inferred role: clip; named after the game accessor ml::ScnRenderDrSysParmAcc::setClip.
  u8 _1d81[0x1d86 - 0x1d81];
  bool unknown1d86; // Inferred role: keeps the camera position of DrCalcViewWork::begin and skips its view clip setup (1.0.0: 0x71008aa70c); original member name unknown.
  u8 _1d87[0x1d8c - 0x1d87];
  bool unknown1d8c; // Inferred role: flag, copied to unknown1d8d at the end of the setup; original member name unknown.
  bool unknown1d8d; // Inferred role: copy of unknown1d8c; original member name unknown.
  bool unknown1d8e; // Inferred role: skips the env coli parameters; original member name unknown.
  u8 _1d8f[0x1d94 - 0x1d8f];
  FILE_PRIO m_seamMapPriMdl;  // Inferred role: seam map pri mdl; named after the game accessor ml::ScnRenderDrSysParmAcc::getSeamMapPriMdl.
  FILE_PRIO m_seamMapPriColi; // Inferred role: seam map pri coli; named after the game accessor ml::ScnRenderDrSysParmAcc::getSeamMapPriColi.
  bool m_allMiddelTexStmChk[2];
  bool m_seamMapStmOk[2];
  bool m_cameraLight; // Inferred role: camera light; named after the game accessor ml::ScnRenderDrSysParmAcc::setCameraLight.
  u8 _1da1[0x1da4 - 0x1da1];
  s32 unknown1da4; // Inferred role: dynamic light type; original member name unknown.
  u8 _1da8[0x1dac - 0x1da8];
  bool unknown1dac[14]; // Inferred role: debug requests to reload a shader or a file, one flag per type, cleared by debugUpdate; original member name unknown.
  u8 _1dba[0x1dbc - 0x1dba];
  s32 unknown1dbc; // Inferred role: render skip; original member name unknown.
  s16 unknown1dc0; // Inferred role: render stage request (renderView clears 1 before and 2 after the deferred render); original member name unknown.
  u8 _1dc2[0x1de4 - 0x1dc2];
  u32 unknown1de4;  // Inferred role: histgram size shift; original member name unknown.
  bool unknown1de8; // Inferred role: histgram uses the tone map target; original member name unknown.
  u8 _1de9[0x1e00 - 0x1de9];
  cloud::CloudMan *unknown1e00; // Inferred role: cloud man; original member name unknown.
  bool m_toonDirLightScale;     // Inferred role: toon dir light scale; named after the game accessor ml::ScnRenderDrSysParmAcc::setToonDirLightScale.
  u8 _1e09[0x1e0c - 0x1e09];
  s32 unknown1e0c;  // Inferred role: toon ambient; original member name unknown.
  bool unknown1e10; // Inferred role: quarter depth; original member name unknown.
  u8 _1e11[0x1e20 - 0x1e11];
};

static_assert(offsetof(DrMan, unknown08) == 0x0008, "");
static_assert(offsetof(DrMan, unknown0c) == 0x000c, "");
static_assert(offsetof(DrMan, unknown10) == 0x0010, "");
static_assert(offsetof(DrMan, unknown14) == 0x0014, "");
static_assert(offsetof(DrMan, unknown18) == 0x0018, "");
static_assert(offsetof(DrMan, unknown1c) == 0x001c, "");
static_assert(offsetof(DrMan, unknown20) == 0x0020, "");
static_assert(offsetof(DrMan, unknown68) == 0x0068, "");
static_assert(offsetof(DrMan, m_drIniSys) == 0x0070, "");
static_assert(offsetof(DrMan, m_drPixlMan) == 0x0078, "");
static_assert(offsetof(DrMan, m_drShdMan) == 0x0080, "");
static_assert(offsetof(DrMan, m_drMdlMan) == 0x0088, "");
static_assert(offsetof(DrMan, m_drIrrVolMan) == 0x0090, "");
static_assert(offsetof(DrMan, m_drResFilterData) == 0x0098, "");
static_assert(offsetof(DrMan, unknowna0) == 0x00a0, "");
static_assert(offsetof(DrMan, unknownc0) == 0x00c0, "");
static_assert(offsetof(DrMan, unknowne0) == 0x00e0, "");
static_assert(offsetof(DrMan, unknown100) == 0x0100, "");
static_assert(offsetof(DrMan, unknown120) == 0x0120, "");
static_assert(offsetof(DrMan, unknown140) == 0x0140, "");
static_assert(offsetof(DrMan, unknown160) == 0x0160, "");
static_assert(offsetof(DrMan, m_drPixlTileParm) == 0x0180, "");
static_assert(offsetof(DrMan, unknown190) == 0x0190, "");
static_assert(offsetof(DrMan, unknown350) == 0x0350, "");
static_assert(offsetof(DrMan, unknown358) == 0x0358, "");
static_assert(offsetof(DrMan, unknown378) == 0x0378, "");
static_assert(offsetof(DrMan, m_DR_CAPTURE_PARAM) == 0x0380, "");
static_assert(offsetof(DrMan, unknown3b0) == 0x03b0, "");
static_assert(offsetof(DrMan, unknown3b8) == 0x03b8, "");
static_assert(offsetof(DrMan, unknown438) == 0x0438, "");
static_assert(offsetof(DrMan, unknown440) == 0x0440, "");
static_assert(offsetof(DrMan, m_drCalcMan) == 0x0580, "");
static_assert(offsetof(DrMan, unknown588) == 0x0588, "");
static_assert(offsetof(DrMan, m_drFogMan) == 0x0590, "");
static_assert(offsetof(DrMan, m_drEnvironmentMan) == 0x0598, "");
static_assert(offsetof(DrMan, m_drIBLMan) == 0x05a0, "");
static_assert(offsetof(DrMan, m_drGlobalIBLMan) == 0x05a8, "");
static_assert(offsetof(DrMan, m_drCalcTexStreamMan) == 0x05b0, "");
static_assert(offsetof(DrMan, unknown5b8) == 0x05b8, "");
static_assert(offsetof(DrMan, m_drAPCache) == 0x05c0, "");
static_assert(offsetof(DrMan, m_drCalcGpuCost) == 0x05c8, "");
static_assert(offsetof(DrMan, m_drPixlMemMan) == 0x05d0, "");
static_assert(offsetof(DrMan, unknown5d8) == 0x05d8, "");
static_assert(offsetof(DrMan, unknown658) == 0x0658, "");
static_assert(offsetof(DrMan, m_iDrDrawWorkInfo) == 0x0660, "");
static_assert(offsetof(DrMan, unknown1c60) == 0x1c60, "");
static_assert(offsetof(DrMan, unknown1c70) == 0x1c70, "");
static_assert(offsetof(DrMan, m_seamMapAddPosMode) == 0x1c80, "");
static_assert(offsetof(DrMan, unknown1c81) == 0x1c81, "");
static_assert(offsetof(DrMan, unknown1c83) == 0x1c83, "");
static_assert(offsetof(DrMan, m_glbSpd) == 0x1c84, "");
static_assert(offsetof(DrMan, m_mdlSpd) == 0x1c88, "");
static_assert(offsetof(DrMan, unknown1c8c) == 0x1c8c, "");
static_assert(offsetof(DrMan, m_gamma) == 0x1c90, "");
static_assert(offsetof(DrMan, unknown1c98) == 0x1c98, "");
static_assert(offsetof(DrMan, unknown1c9c) == 0x1c9c, "");
static_assert(offsetof(DrMan, unknown1ca4) == 0x1ca4, "");
static_assert(offsetof(DrMan, m_timerVal) == 0x1cac, "");
static_assert(offsetof(DrMan, unknown1cc0) == 0x1cc0, "");
static_assert(offsetof(DrMan, m_autoResetScene) == 0x1cc1, "");
static_assert(offsetof(DrMan, unknown1cc2) == 0x1cc2, "");
static_assert(offsetof(DrMan, m_mdlHeightTexSkip) == 0x1cc4, "");
static_assert(offsetof(DrMan, m_heightTexSkip) == 0x1cc5, "");
static_assert(offsetof(DrMan, m_seamHeightTexSkip) == 0x1cc6, "");
static_assert(offsetof(DrMan, m_seamMapOpenMode) == 0x1cc7, "");
static_assert(offsetof(DrMan, m_screenDispOff) == 0x1cc8, "");
static_assert(offsetof(DrMan, m_writeZBuffer) == 0x1cc9, "");
static_assert(offsetof(DrMan, unknown1ccc) == 0x1ccc, "");
static_assert(offsetof(DrMan, unknown1cd0) == 0x1cd0, "");
static_assert(offsetof(DrMan, unknown1cfc) == 0x1cfc, "");
static_assert(offsetof(DrMan, unknown1d00) == 0x1d00, "");
static_assert(offsetof(DrMan, unknown1d04) == 0x1d04, "");
static_assert(offsetof(DrMan, unknown1d08) == 0x1d08, "");
static_assert(offsetof(DrMan, unknown1d0c) == 0x1d0c, "");
static_assert(offsetof(DrMan, unknown1d18) == 0x1d18, "");
static_assert(offsetof(DrMan, m_gblIdx) == 0x1d20, "");
static_assert(offsetof(DrMan, m_renderSpecMode) == 0x1d28, "");
static_assert(offsetof(DrMan, m_globalWind) == 0x1d30, "");
static_assert(offsetof(DrMan, m_dispChara) == 0x1d60, "");
static_assert(offsetof(DrMan, unknown1d61) == 0x1d61, "");
static_assert(offsetof(DrMan, unknown1d62) == 0x1d62, "");
static_assert(offsetof(DrMan, unknown1d63) == 0x1d63, "");
static_assert(offsetof(DrMan, unknown1d64) == 0x1d64, "");
static_assert(offsetof(DrMan, unknown1d65) == 0x1d65, "");
static_assert(offsetof(DrMan, unknown1d66) == 0x1d66, "");
static_assert(offsetof(DrMan, unknown1d67) == 0x1d67, "");
static_assert(offsetof(DrMan, unknown1d6c) == 0x1d6c, "");
static_assert(offsetof(DrMan, unknown1d6e) == 0x1d6e, "");
static_assert(offsetof(DrMan, m_fogSkip) == 0x1d71, "");
static_assert(offsetof(DrMan, unknown1d73) == 0x1d73, "");
static_assert(offsetof(DrMan, unknown1d75) == 0x1d75, "");
static_assert(offsetof(DrMan, unknown1d78) == 0x1d78, "");
static_assert(offsetof(DrMan, unknown1d7a) == 0x1d7a, "");
static_assert(offsetof(DrMan, m_mdlDblPause) == 0x1d7b, "");
static_assert(offsetof(DrMan, unknown1d7d) == 0x1d7d, "");
static_assert(offsetof(DrMan, unknown1d7e) == 0x1d7e, "");
static_assert(offsetof(DrMan, m_clip) == 0x1d80, "");
static_assert(offsetof(DrMan, unknown1d86) == 0x1d86, "");
static_assert(offsetof(DrMan, unknown1d8c) == 0x1d8c, "");
static_assert(offsetof(DrMan, unknown1d8d) == 0x1d8d, "");
static_assert(offsetof(DrMan, unknown1d8e) == 0x1d8e, "");
static_assert(offsetof(DrMan, m_seamMapPriMdl) == 0x1d94, "");
static_assert(offsetof(DrMan, m_seamMapPriColi) == 0x1d98, "");
static_assert(offsetof(DrMan, m_allMiddelTexStmChk) == 0x1d9c, "");
static_assert(offsetof(DrMan, m_seamMapStmOk) == 0x1d9e, "");
static_assert(offsetof(DrMan, m_cameraLight) == 0x1da0, "");
static_assert(offsetof(DrMan, unknown1da4) == 0x1da4, "");
static_assert(offsetof(DrMan, unknown1dac) == 0x1dac, "");
static_assert(offsetof(DrMan, unknown1dbc) == 0x1dbc, "");
static_assert(offsetof(DrMan, unknown1dc0) == 0x1dc0, "");
static_assert(offsetof(DrMan, unknown1de4) == 0x1de4, "");
static_assert(offsetof(DrMan, unknown1de8) == 0x1de8, "");
static_assert(offsetof(DrMan, unknown1e00) == 0x1e00, "");
static_assert(offsetof(DrMan, m_toonDirLightScale) == 0x1e08, "");
static_assert(offsetof(DrMan, unknown1e0c) == 0x1e0c, "");
static_assert(sizeof(DrMan) == 0x1e20, "");

} // namespace ml
