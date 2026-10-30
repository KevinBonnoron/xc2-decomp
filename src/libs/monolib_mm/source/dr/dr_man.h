#pragma once
#include <stddef.h>

#include "dr/dr_draw_work_info.h"
#include "ml/work_background.h"
#include "mm_math/mm_vec3.h"
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
class DrGlobalIBLMan;
class DrIrrVolMan;
class DrLightMan;
class DrMdlMan;
class DrPixlTileParm;
class DrResFilterData;
class DrShdMan;
class IDrDrawCallback;
class DrPixlMan;
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
};

static_assert(offsetof(unknown057, unknown18) == 0x18, "");
static_assert(offsetof(unknown057, unknown20) == 0x20, "");
static_assert(offsetof(unknown057, unknown28) == 0x28, "");
static_assert(offsetof(unknown057, unknown2c) == 0x2c, "");

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
  void end();
  int loopCnt();
  void apply(int loop);
  void applyBegin(int loop);
  void applyEnd(int loop);
  void applyViewBegin();
  void render(int loop);
  void renderBegin(int loop);
  void setAlphaRenderTarget();
  void setSkyGodRayRenderTarget();
  void renderEnd(int loop);
  void renderViewBegin();
  void renderViewEnd();
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

  static DrMan *s_pTop;
  static s32 s_nDblStockIdx;
  static s32 s_nDblIdx;
  static s32 s_nDblMemIdx;
  static s32 s_nDblNowIdx;
  static bool s_bSRGBMode;
  static bool s_bFogSRGB;
  static bool s_bSeamDebug;

  u8 _0008[0x000c - 0x0008];
  mtl::ALLOC_HANDLE unknown0c; // Inferred role: mem sys; original member name unknown.
  mtl::ALLOC_HANDLE unknown10; // Inferred role: mem class; original member name unknown.
  mtl::ALLOC_HANDLE unknown14; // Inferred role: mem work; original member name unknown.
  u8 _0018[0x0070 - 0x0018];
  DrIniSys *unknown70;        // Inferred role: ini sys; original member name unknown.
  DrPixlMan *unknown78;       // Inferred role: pixl man; original member name unknown.
  DrShdMan *unknown80;        // Inferred role: shd man; original member name unknown.
  DrMdlMan *unknown88;        // Inferred role: mdl man; original member name unknown.
  DrIrrVolMan *unknown90;     // Inferred role: irr vol man; original member name unknown.
  DrResFilterData *unknown98; // Inferred role: filter data; original member name unknown.
  DrCalcMan *unknowna0[4];    // Inferred role: calc mans; original member name unknown.
  DrLightMan *unknownc0[4];   // Inferred role: light mans; original member name unknown.
  u8 _00e0[0x0100 - 0x00e0];
  DrEnvironmentMan *unknown100[4]; // Inferred role: environment mans; original member name unknown.
  DrPixlPostParm *unknown120[4];   // Inferred role: post parms; original member name unknown.
  u8 _0140[0x0160 - 0x0140];
  DrGlobalIBLMan *unknown160[4]; // Inferred role: global ibl mans; original member name unknown.
  DrPixlTileParm *unknown180;    // Inferred role: tile parm; original member name unknown.
  u8 _0188[0x0190 - 0x0188];
  DR_VIEW_PARAM unknown190[2][4]; // Inferred role: additional render system view params; original member name unknown.
  s32 unknown350[2];              // Inferred role: additional render system counts; original member name unknown.
  u32 unknown358[2][4];           // Inferred role: deleted render system ids; original member name unknown.
  s32 unknown378[2];              // Inferred role: deleted render system counts; original member name unknown.
  DR_CAPTURE_PARAM unknown380[2]; // Inferred role: capture requests; original member name unknown.
  u32 unknown3b0;                 // Inferred role: capture request mask; original member name unknown.
  u8 _03b4[0x03b8 - 0x03b4];
  DR_MODEL_TEXTURE unknown3b8[2][4]; // Inferred role: model textures; original member name unknown.
  u32 unknown438[2];                 // Inferred role: model texture update masks; original member name unknown.
  u8 _0440[0x0580 - 0x0440];
  DrCalcMan *unknown580;  // Inferred role: calc man; original member name unknown.
  DrLightMan *unknown588; // Inferred role: light man; original member name unknown.
  u8 _0590[0x0598 - 0x0590];
  DrEnvironmentMan *unknown598; // Inferred role: environment man; original member name unknown.
  u8 _05a0[0x05b0 - 0x05a0];
  DrCalcTexStreamMan *unknown5b0; // Inferred role: tex stream man; original member name unknown.
  unknown057 *unknown5b8;         // Inferred role: screen info; original member name unknown.
  DrAPCache *unknown5c0;          // Inferred role: ap cache; original member name unknown.
  DrCalcGpuCost *unknown5c8;      // Inferred role: gpu cost; original member name unknown.
  u8 _05d0[0x05d8 - 0x05d0];
  IDrDrawCallback *unknown5d8[16]; // Inferred role: callbacks; original member name unknown.
  s32 unknown658;                  // Inferred role: callback num; original member name unknown.
  u8 _065c[0x0660 - 0x065c];
  IDrDrawWorkInfo unknown660[4]; // Inferred role: draw work infos; original member name unknown.
  s32 unknown1c60;               // Inferred role: tmaa mode; original member name unknown.
  u8 _1c64[0x1c70 - 0x1c64];
  mm::Vec3 unknown1c70; // Inferred role: seam map read pos; original member name unknown.
  bool unknown1c80;     // Inferred role: seam map add pos mode; original member name unknown.
  u8 unknown1c81[2];    // Inferred role: capture modes; original member name unknown.
  f32 unknown1c84;      // Inferred role: glb spd; original member name unknown.
  f32 unknown1c88;      // Inferred role: mdl spd; original member name unknown.
  f32 unknown1c8c;      // Inferred role: model speed scaled by the global speed; original member name unknown.
  f32 unknown1c90;      // Inferred role: gamma; original member name unknown.
  u8 _1c94[0x1c98 - 0x1c94];
  s32 unknown1c98; // Inferred role: view index; original member name unknown.
  u32 unknown1c9c; // Inferred role: view render skip; original member name unknown.
  u8 _1ca0[0x1ca4 - 0x1ca0];
  f32 unknown1ca4[2]; // Inferred role: time vals; original member name unknown.
  f32 unknown1cac;    // Inferred role: timer val; original member name unknown.
  u8 _1cb0[0x1cc0 - 0x1cb0];
  bool unknown1cc0; // Inferred role: home menu opened; original member name unknown.
  bool unknown1cc1; // Inferred role: auto reset scene; original member name unknown.
  u8 _1cc2[0x1cc4 - 0x1cc2];
  bool unknown1cc4; // Inferred role: mdl height tex skip; original member name unknown.
  bool unknown1cc5; // Inferred role: height tex skip; original member name unknown.
  bool unknown1cc6; // Inferred role: seam height tex skip; original member name unknown.
  bool unknown1cc7; // Inferred role: seam map open mode; original member name unknown.
  bool unknown1cc8; // Inferred role: screen disp off; original member name unknown.
  bool unknown1cc9; // Inferred role: write z buffer; original member name unknown.
  u8 _1cca[0x1cfc - 0x1cca];
  s32 unknown1cfc; // Inferred role: seam read lv; original member name unknown.
  u8 _1d00[0x1d20 - 0x1d00];
  u32 *unknown1d20;           // Inferred role: gbl tbl; original member name unknown.
  RenderSpecMode unknown1d28; // Inferred role: render spec mode; original member name unknown.
  u8 _1d2c[0x1d30 - 0x1d2c];
  mm::Vec3 unknown1d30[2]; // Inferred role: global winds; original member name unknown.
  u8 _1d50[0x1d60 - 0x1d50];
  bool unknown1d60; // Inferred role: chara disp off; original member name unknown.
  u8 _1d61[0x1d63 - 0x1d61];
  bool unknown1d63; // Inferred role: model render skip; original member name unknown.
  bool unknown1d64; // Inferred role: light pre pass and GBuff render skip; original member name unknown.
  bool unknown1d65; // Inferred role: refraction render skip; original member name unknown.
  bool unknown1d66; // Inferred role: alpha render skip; original member name unknown.
  bool unknown1d67; // Inferred role: sp alpha render skip; original member name unknown.
  bool unknown1d68; // Inferred role: shadow render skip; original member name unknown.
  u8 _1d69[0x1d70 - 0x1d69];
  bool unknown1d70; // Inferred role: shadow light skip; original member name unknown.
  bool unknown1d71; // Inferred role: fog skip; original member name unknown.
  u8 _1d72[0x1d75 - 0x1d72];
  bool unknown1d75; // Inferred role: IBL skip; original member name unknown.
  u8 _1d76[0x1d7a - 0x1d76];
  bool unknown1d7a; // Inferred role: shadow map override; original member name unknown.
  bool unknown1d7b; // Inferred role: mdl dbl pause; original member name unknown.
  u8 _1d7c[0x1d80 - 0x1d7c];
  bool unknown1d80; // Inferred role: clip; original member name unknown.
  u8 _1d81[0x1d94 - 0x1d81];
  FILE_PRIO unknown1d94; // Inferred role: seam map pri mdl; original member name unknown.
  FILE_PRIO unknown1d98; // Inferred role: seam map pri coli; original member name unknown.
  bool unknown1d9c[2];   // Inferred role: all middel tex stm chks; original member name unknown.
  bool unknown1d9e[2];   // Inferred role: seam map stm oks; original member name unknown.
  bool unknown1da0;      // Inferred role: camera light; original member name unknown.
  u8 _1da1[0x1da4 - 0x1da1];
  s32 unknown1da4; // Inferred role: dynamic light type; original member name unknown.
  u8 _1da8[0x1e00 - 0x1da8];
  cloud::CloudMan *unknown1e00; // Inferred role: cloud man; original member name unknown.
  bool unknown1e08;             // Inferred role: toon dir light scale; original member name unknown.
  u8 _1e09[0x1e0c - 0x1e09];
  s32 unknown1e0c;  // Inferred role: toon ambient; original member name unknown.
  bool unknown1e10; // Inferred role: quarter depth; original member name unknown.
  u8 _1e11[0x1e20 - 0x1e11];
};

static_assert(offsetof(DrMan, unknown0c) == 0x000c, "");
static_assert(offsetof(DrMan, unknown10) == 0x0010, "");
static_assert(offsetof(DrMan, unknown14) == 0x0014, "");
static_assert(offsetof(DrMan, unknown70) == 0x0070, "");
static_assert(offsetof(DrMan, unknown78) == 0x0078, "");
static_assert(offsetof(DrMan, unknown80) == 0x0080, "");
static_assert(offsetof(DrMan, unknown88) == 0x0088, "");
static_assert(offsetof(DrMan, unknown90) == 0x0090, "");
static_assert(offsetof(DrMan, unknown98) == 0x0098, "");
static_assert(offsetof(DrMan, unknowna0) == 0x00a0, "");
static_assert(offsetof(DrMan, unknownc0) == 0x00c0, "");
static_assert(offsetof(DrMan, unknown100) == 0x0100, "");
static_assert(offsetof(DrMan, unknown120) == 0x0120, "");
static_assert(offsetof(DrMan, unknown160) == 0x0160, "");
static_assert(offsetof(DrMan, unknown180) == 0x0180, "");
static_assert(offsetof(DrMan, unknown190) == 0x0190, "");
static_assert(offsetof(DrMan, unknown350) == 0x0350, "");
static_assert(offsetof(DrMan, unknown358) == 0x0358, "");
static_assert(offsetof(DrMan, unknown378) == 0x0378, "");
static_assert(offsetof(DrMan, unknown380) == 0x0380, "");
static_assert(offsetof(DrMan, unknown3b0) == 0x03b0, "");
static_assert(offsetof(DrMan, unknown3b8) == 0x03b8, "");
static_assert(offsetof(DrMan, unknown438) == 0x0438, "");
static_assert(offsetof(DrMan, unknown580) == 0x0580, "");
static_assert(offsetof(DrMan, unknown588) == 0x0588, "");
static_assert(offsetof(DrMan, unknown598) == 0x0598, "");
static_assert(offsetof(DrMan, unknown5b0) == 0x05b0, "");
static_assert(offsetof(DrMan, unknown5b8) == 0x05b8, "");
static_assert(offsetof(DrMan, unknown5c0) == 0x05c0, "");
static_assert(offsetof(DrMan, unknown5c8) == 0x05c8, "");
static_assert(offsetof(DrMan, unknown5d8) == 0x05d8, "");
static_assert(offsetof(DrMan, unknown658) == 0x0658, "");
static_assert(offsetof(DrMan, unknown660) == 0x0660, "");
static_assert(offsetof(DrMan, unknown1c60) == 0x1c60, "");
static_assert(offsetof(DrMan, unknown1c70) == 0x1c70, "");
static_assert(offsetof(DrMan, unknown1c80) == 0x1c80, "");
static_assert(offsetof(DrMan, unknown1c81) == 0x1c81, "");
static_assert(offsetof(DrMan, unknown1c84) == 0x1c84, "");
static_assert(offsetof(DrMan, unknown1c88) == 0x1c88, "");
static_assert(offsetof(DrMan, unknown1c8c) == 0x1c8c, "");
static_assert(offsetof(DrMan, unknown1c90) == 0x1c90, "");
static_assert(offsetof(DrMan, unknown1c98) == 0x1c98, "");
static_assert(offsetof(DrMan, unknown1c9c) == 0x1c9c, "");
static_assert(offsetof(DrMan, unknown1ca4) == 0x1ca4, "");
static_assert(offsetof(DrMan, unknown1cac) == 0x1cac, "");
static_assert(offsetof(DrMan, unknown1cc0) == 0x1cc0, "");
static_assert(offsetof(DrMan, unknown1cc1) == 0x1cc1, "");
static_assert(offsetof(DrMan, unknown1cc4) == 0x1cc4, "");
static_assert(offsetof(DrMan, unknown1cc5) == 0x1cc5, "");
static_assert(offsetof(DrMan, unknown1cc6) == 0x1cc6, "");
static_assert(offsetof(DrMan, unknown1cc7) == 0x1cc7, "");
static_assert(offsetof(DrMan, unknown1cc8) == 0x1cc8, "");
static_assert(offsetof(DrMan, unknown1cc9) == 0x1cc9, "");
static_assert(offsetof(DrMan, unknown1cfc) == 0x1cfc, "");
static_assert(offsetof(DrMan, unknown1d20) == 0x1d20, "");
static_assert(offsetof(DrMan, unknown1d28) == 0x1d28, "");
static_assert(offsetof(DrMan, unknown1d30) == 0x1d30, "");
static_assert(offsetof(DrMan, unknown1d60) == 0x1d60, "");
static_assert(offsetof(DrMan, unknown1d63) == 0x1d63, "");
static_assert(offsetof(DrMan, unknown1d64) == 0x1d64, "");
static_assert(offsetof(DrMan, unknown1d65) == 0x1d65, "");
static_assert(offsetof(DrMan, unknown1d66) == 0x1d66, "");
static_assert(offsetof(DrMan, unknown1d67) == 0x1d67, "");
static_assert(offsetof(DrMan, unknown1d71) == 0x1d71, "");
static_assert(offsetof(DrMan, unknown1d75) == 0x1d75, "");
static_assert(offsetof(DrMan, unknown1d7a) == 0x1d7a, "");
static_assert(offsetof(DrMan, unknown1d7b) == 0x1d7b, "");
static_assert(offsetof(DrMan, unknown1d80) == 0x1d80, "");
static_assert(offsetof(DrMan, unknown1d94) == 0x1d94, "");
static_assert(offsetof(DrMan, unknown1d98) == 0x1d98, "");
static_assert(offsetof(DrMan, unknown1d9c) == 0x1d9c, "");
static_assert(offsetof(DrMan, unknown1d9e) == 0x1d9e, "");
static_assert(offsetof(DrMan, unknown1da0) == 0x1da0, "");
static_assert(offsetof(DrMan, unknown1da4) == 0x1da4, "");
static_assert(offsetof(DrMan, unknown1e00) == 0x1e00, "");
static_assert(offsetof(DrMan, unknown1e08) == 0x1e08, "");
static_assert(offsetof(DrMan, unknown1e0c) == 0x1e0c, "");
static_assert(sizeof(DrMan) == 0x1e20, "");

} // namespace ml
