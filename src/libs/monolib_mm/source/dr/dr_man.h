#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "types.h"

namespace cloud {
class CloudMan;
} // namespace cloud

namespace ml {
class DrIrrVolMan;
class DrPixlPostParm;

enum FILE_PRIO {};
enum RenderSpecMode {};

struct DR_CAPCUBE_PARAM;

struct DrMotBlurState {
  u8 _000[0xb6c - 0x000];
  bool motBlurDefault;
};

static_assert(offsetof(DrMotBlurState, motBlurDefault) == 0xb6c, "");

struct DrBlurTarget {
  u8 _00[0x28 - 0x00];
  void *velocityMap;
};

static_assert(offsetof(DrBlurTarget, velocityMap) == 0x28, "");

struct DrViewBlur {
  u8 _00[0x50 - 0x00];
  DrBlurTarget *target;
};

static_assert(offsetof(DrViewBlur, target) == 0x50, "");

struct DrView {
  u8 _000[0x190 - 0x000];
  DrViewBlur *blur;
  u8 _198[0x1f8 - 0x198];
};

static_assert(offsetof(DrView, blur) == 0x190, "");
static_assert(sizeof(DrView) == 0x1f8, "");

class DrMan {
public:
  static DrMan *get();
  static DrMan *getIns();

  void setTimeVal(f32 timeVal);
  void setGlobalWind(const mm::Vec3 &globalWind);
  void setGroupsDisp(s32 group, bool disp);
  void setAutoReduction(bool autoReduction);
  void setAvatarCapMode(s32 avatarCapMode);
  void setCacherClearMode(bool cacherClearMode);
  void releaseFastLight(s32 index);
  void setGblIdx(s32 id);
  void offGblIdx(s32 id);
  void callCubeMapRender(const DR_CAPCUBE_PARAM &param);
  void resetModelTexture(u32 index);
  void deleteAddRenderSystem(u32 id);
  bool isSeamMapStmOk() const;
  bool isAllMiddelTexStmChk() const;

  static s32 s_nDblStockIdx;

  u8 _0000[0x0070 - 0x0000];
  DrMotBlurState *motBlurState;
  DrView *views;
  u8 _0080[0x0090 - 0x0080];
  DrIrrVolMan *irrVolMan;
  u8 _0098[0x0120 - 0x0098];
  DrPixlPostParm *postParms[4];
  u8 _0140[0x1c70 - 0x0140];
  mm::Vec3 seamMapReadPos;
  bool seamMapAddPosMode;
  u8 captureModes[2];
  f32 glbSpd;
  f32 mdlSpd;
  u8 _1c8c[0x1c90 - 0x1c8c];
  f32 gamma;
  u8 _1c94[0x1c9c - 0x1c94];
  u32 viewRenderSkip;
  u8 _1ca0[0x1cac - 0x1ca0];
  f32 timerVal;
  u8 _1cb0[0x1cc1 - 0x1cb0];
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
  u8 _1d2c[0x1d60 - 0x1d2c];
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
  u8 _1d9c[0x1da0 - 0x1d9c];
  bool cameraLight;
  u8 _1da1[0x1e00 - 0x1da1];
  cloud::CloudMan *cloudMan;
  bool toonDirLightScale;
  u8 _1e09[0x1e0c - 0x1e09];
  s32 toonAmbient;
};

static_assert(offsetof(DrMan, motBlurState) == 0x0070, "");
static_assert(offsetof(DrMan, views) == 0x0078, "");
static_assert(offsetof(DrMan, irrVolMan) == 0x0090, "");
static_assert(offsetof(DrMan, postParms) == 0x0120, "");
static_assert(offsetof(DrMan, seamMapReadPos) == 0x1c70, "");
static_assert(offsetof(DrMan, seamMapAddPosMode) == 0x1c80, "");
static_assert(offsetof(DrMan, captureModes) == 0x1c81, "");
static_assert(offsetof(DrMan, glbSpd) == 0x1c84, "");
static_assert(offsetof(DrMan, mdlSpd) == 0x1c88, "");
static_assert(offsetof(DrMan, gamma) == 0x1c90, "");
static_assert(offsetof(DrMan, viewRenderSkip) == 0x1c9c, "");
static_assert(offsetof(DrMan, timerVal) == 0x1cac, "");
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
static_assert(offsetof(DrMan, charaDispOff) == 0x1d60, "");
static_assert(offsetof(DrMan, fogSkip) == 0x1d71, "");
static_assert(offsetof(DrMan, mdlDblPause) == 0x1d7b, "");
static_assert(offsetof(DrMan, clip) == 0x1d80, "");
static_assert(offsetof(DrMan, seamMapPriMdl) == 0x1d94, "");
static_assert(offsetof(DrMan, seamMapPriColi) == 0x1d98, "");
static_assert(offsetof(DrMan, cameraLight) == 0x1da0, "");
static_assert(offsetof(DrMan, cloudMan) == 0x1e00, "");
static_assert(offsetof(DrMan, toonDirLightScale) == 0x1e08, "");
static_assert(offsetof(DrMan, toonAmbient) == 0x1e0c, "");

} // namespace ml
