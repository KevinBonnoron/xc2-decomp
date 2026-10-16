#pragma once
#include <stddef.h>

#include "dr/dr_draw_work_info.h"
#include "ml/work_event.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace cloud {
class CloudMan;
} // namespace cloud

namespace ml {
class DrAPCache;
class DrCalcGpuCost;
class DrCalcTexStreamMan;
class DrEnvironmentMan;
class DrIrrVolMan;
class DrLightMan;
class DrMdlMan;
class DrPixlTileParm;
class DrShdMan;
class IDrDrawCallback;
class DrPixlMan;
class DrPixlPostParm;
class Scn;
class WinProc;

enum FILE_PRIO {};
enum RenderSpecMode {};

struct DR_CAPCUBE_PARAM;

struct DrMotBlurState {
  u8 _000[0xb6c - 0x000];
  bool motBlurDefault;
};

static_assert(offsetof(DrMotBlurState, motBlurDefault) == 0xb6c, "");

class DrMan : public IWorkBackground {
public:
  static DrMan *getIns();
  static DrMan *get();
  DrMan(Scn *scn);
  ~DrMan() override;
  void resetModelTexture(u32 index);
  void deleteAddRenderSystem(u32 id);
  void begin();
  void end();
  int loopCnt();
  void apply(int loop);
  void applyEnd(int loop);
  void applyViewBegin();
  void render(int loop);
  void renderBegin(int loop);
  void tail();
  void setMainRenderTarget();
  bool isIBLHalfRes() const;
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

  static DrMan *s_pTop;
  static s32 s_nDblStockIdx;
  static s32 s_nDblIdx;
  static s32 s_nDblMemIdx;
  static s32 s_nDblNowIdx;
  static bool s_bSRGBMode;
  static bool s_bFogSRGB;
  static bool s_bSeamDebug;

  u8 _0008[0x0070 - 0x0008];
  DrMotBlurState *motBlurState;
  DrPixlMan *pixlMan;
  DrShdMan *shdMan;
  DrMdlMan *mdlMan;
  DrIrrVolMan *irrVolMan;
  u8 _0098[0x00c0 - 0x0098];
  DrLightMan *lightMans[4];
  u8 _00e0[0x0100 - 0x00e0];
  DrEnvironmentMan *environmentMans[4];
  DrPixlPostParm *postParms[4];
  u8 _0140[0x0180 - 0x0140];
  DrPixlTileParm *tileParm;
  u8 _0188[0x05b0 - 0x0188];
  DrCalcTexStreamMan *texStreamMan;
  u8 _05b8[0x05c0 - 0x05b8];
  DrAPCache *apCache;
  DrCalcGpuCost *gpuCost;
  u8 _05d0[0x05d8 - 0x05d0];
  IDrDrawCallback *callbacks[16];
  s32 callbackNum;
  u8 _065c[0x0660 - 0x065c];
  IDrDrawWorkInfo drawWorkInfos[4];
  u8 _1c60[0x1c70 - 0x1c60];
  mm::Vec3 seamMapReadPos;
  bool seamMapAddPosMode;
  u8 captureModes[2];
  f32 glbSpd;
  f32 mdlSpd;
  u8 _1c8c[0x1c90 - 0x1c8c];
  f32 gamma;
  u8 _1c94[0x1c98 - 0x1c94];
  s32 viewIndex;
  u32 viewRenderSkip;
  u8 _1ca0[0x1ca4 - 0x1ca0];
  f32 timeVals[2];
  f32 timerVal;
  u8 _1cb0[0x1cc0 - 0x1cb0];
  bool homeMenuOpened;
  bool autoResetScene;
  u8 _1cc2[0x1cc4 - 0x1cc2];
  bool mdlHeightTexSkip;
  bool heightTexSkip;
  bool seamHeightTexSkip;
  bool seamMapOpenMode;
  bool screenDispOff;
  bool writeZBuffer;
  u8 _1cca[0x1cfc - 0x1cca];
  s32 seamReadLv;
  u8 _1d00[0x1d20 - 0x1d00];
  u32 *gblTbl;
  RenderSpecMode renderSpecMode;
  u8 _1d2c[0x1d30 - 0x1d2c];
  mm::Vec3 globalWinds[2];
  u8 _1d50[0x1d60 - 0x1d50];
  bool charaDispOff;
  u8 _1d61[0x1d71 - 0x1d61];
  bool fogSkip;
  u8 _1d72[0x1d7b - 0x1d72];
  bool mdlDblPause;
  u8 _1d7c[0x1d80 - 0x1d7c];
  bool clip;
  u8 _1d81[0x1d94 - 0x1d81];
  FILE_PRIO seamMapPriMdl;
  FILE_PRIO seamMapPriColi;
  bool allMiddelTexStmChks[2];
  bool seamMapStmOks[2];
  bool cameraLight;
  u8 _1da1[0x1e00 - 0x1da1];
  cloud::CloudMan *cloudMan;
  bool toonDirLightScale;
  u8 _1e09[0x1e0c - 0x1e09];
  s32 toonAmbient;
  u8 _1e10[0x1e20 - 0x1e10];
};

static_assert(offsetof(DrMan, motBlurState) == 0x0070, "");
static_assert(offsetof(DrMan, pixlMan) == 0x0078, "");
static_assert(offsetof(DrMan, shdMan) == 0x0080, "");
static_assert(offsetof(DrMan, mdlMan) == 0x0088, "");
static_assert(offsetof(DrMan, irrVolMan) == 0x0090, "");
static_assert(offsetof(DrMan, lightMans) == 0x00c0, "");
static_assert(offsetof(DrMan, environmentMans) == 0x0100, "");
static_assert(offsetof(DrMan, postParms) == 0x0120, "");
static_assert(offsetof(DrMan, tileParm) == 0x0180, "");
static_assert(offsetof(DrMan, texStreamMan) == 0x05b0, "");
static_assert(offsetof(DrMan, apCache) == 0x05c0, "");
static_assert(offsetof(DrMan, gpuCost) == 0x05c8, "");
static_assert(offsetof(DrMan, callbacks) == 0x05d8, "");
static_assert(offsetof(DrMan, callbackNum) == 0x0658, "");
static_assert(offsetof(DrMan, drawWorkInfos) == 0x0660, "");
static_assert(offsetof(DrMan, seamMapReadPos) == 0x1c70, "");
static_assert(offsetof(DrMan, seamMapAddPosMode) == 0x1c80, "");
static_assert(offsetof(DrMan, captureModes) == 0x1c81, "");
static_assert(offsetof(DrMan, glbSpd) == 0x1c84, "");
static_assert(offsetof(DrMan, mdlSpd) == 0x1c88, "");
static_assert(offsetof(DrMan, gamma) == 0x1c90, "");
static_assert(offsetof(DrMan, viewIndex) == 0x1c98, "");
static_assert(offsetof(DrMan, viewRenderSkip) == 0x1c9c, "");
static_assert(offsetof(DrMan, timeVals) == 0x1ca4, "");
static_assert(offsetof(DrMan, timerVal) == 0x1cac, "");
static_assert(offsetof(DrMan, homeMenuOpened) == 0x1cc0, "");
static_assert(offsetof(DrMan, autoResetScene) == 0x1cc1, "");
static_assert(offsetof(DrMan, mdlHeightTexSkip) == 0x1cc4, "");
static_assert(offsetof(DrMan, heightTexSkip) == 0x1cc5, "");
static_assert(offsetof(DrMan, seamHeightTexSkip) == 0x1cc6, "");
static_assert(offsetof(DrMan, seamMapOpenMode) == 0x1cc7, "");
static_assert(offsetof(DrMan, screenDispOff) == 0x1cc8, "");
static_assert(offsetof(DrMan, writeZBuffer) == 0x1cc9, "");
static_assert(offsetof(DrMan, seamReadLv) == 0x1cfc, "");
static_assert(offsetof(DrMan, gblTbl) == 0x1d20, "");
static_assert(offsetof(DrMan, renderSpecMode) == 0x1d28, "");
static_assert(offsetof(DrMan, globalWinds) == 0x1d30, "");
static_assert(offsetof(DrMan, charaDispOff) == 0x1d60, "");
static_assert(offsetof(DrMan, fogSkip) == 0x1d71, "");
static_assert(offsetof(DrMan, mdlDblPause) == 0x1d7b, "");
static_assert(offsetof(DrMan, clip) == 0x1d80, "");
static_assert(offsetof(DrMan, seamMapPriMdl) == 0x1d94, "");
static_assert(offsetof(DrMan, seamMapPriColi) == 0x1d98, "");
static_assert(offsetof(DrMan, allMiddelTexStmChks) == 0x1d9c, "");
static_assert(offsetof(DrMan, seamMapStmOks) == 0x1d9e, "");
static_assert(offsetof(DrMan, cameraLight) == 0x1da0, "");
static_assert(offsetof(DrMan, cloudMan) == 0x1e00, "");
static_assert(offsetof(DrMan, toonDirLightScale) == 0x1e08, "");
static_assert(offsetof(DrMan, toonAmbient) == 0x1e0c, "");
static_assert(sizeof(DrMan) == 0x1e20, "");

} // namespace ml
