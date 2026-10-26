#pragma once
#include "mm_math/mm_pnt.h"
#include <stddef.h>

#include "scn/scn_render.h"
#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
}

namespace ml {
class DrMan;
class IDrDrawCallback;
class Scn;

class ScnRenderDrSys : public ScnRender {
public:
  ScnRenderDrSys(Scn *scn);
  ~ScnRenderDrSys() override;
  void setDefaultEvn() override;
  void applyCamera(ScnObjCam *camera) override;
  void update() override;
  void applyBegin() override;
  void applyEnd() override;
  int applyLoopCnt() override;
  void applyUpdate(int loop) override;
  void applyRender(int loop) override;
  void tail() override;
  void setMdlDblPause(bool isPause) override;
  void setGlbSpd(f32 speed) override;
  void setup(const ScnSetup *setup) override;
  void setCallBack(IDrDrawCallback *callback);
  void releaseCallBack(IDrDrawCallback *callback);
  void setReduction(bool isReduction, f32 scaleX, f32 scaleY);
  void setAA(bool isAA);
  void setColorFilter(bool isColorFilter);
  void setSSAO(bool isSSAO);
  void setBloom(bool isBloom, bool isLensFlare);
  void setToneMap(bool isToneMap);
  void setMotionBlur(bool isMotionBlur);
  void setMotionBlur(f32 strength, f32 sub);
  void setDepthOfField(bool isDepthOfField);
  void setDepthOfFieldParm(f32 distance, f32 range, f32 strength, f32 blend);
  void setTimeVal(f32 timeVal);
  void openPixelDebugWindow(WinProc *window) override;
  void openHisgtramDebugWindow(WinProc *window) override;
  ScnObjModel *createMdl(Scn *scn, const void *data, const char *name, int screen) override;
  ScnObj *createLgt(Scn *scn, const void *data, int screen) override;
  ScnObj *createClip(Scn *scn, const void *data, int screen) override;
  ScnObj *createIBL(Scn *scn, const void *data, int screen) override;
  ScnObj *createEnvColi(Scn *scn, const void *data, int screen) override;
  static void createDrRender(Scn *scn);
  static u32 thDrSysInitialize(void *argument, void *userData);

  DrMan *unknown10; // Inferred role: dr man; original member name unknown.
};

static_assert(offsetof(ScnRenderDrSys, unknown10) == 0x10, "");
static_assert(sizeof(ScnRenderDrSys) == 0x18, "");

class ScnRenderDrViewCtrl {
public:
  mm::Pnt<int> unknown00;               // Role and original member name unknown.
  s32 unknown08;                        // Inferred role: view id; original member name unknown.
  s32 unknown0c;                        // Role and original member name unknown.
  s32 unknown10;                        // Role and original member name unknown.
  s32 unknown14;                        // Role and original member name unknown.
  s32 unknown18;                        // Role and original member name unknown.
  bool unknown1c;                       // Role and original member name unknown.
  grlib::CGLibTextureBuffer *unknown20; // Inferred role: texture; original member name unknown.
  bool unknown28;                       // Role and original member name unknown.
  f32 unknown2c;                        // Role and original member name unknown.
  f32 unknown30;                        // Role and original member name unknown.
  bool unknown34;                       // Role and original member name unknown.
  bool unknown35;                       // Role and original member name unknown.
};

static_assert(offsetof(ScnRenderDrViewCtrl, unknown08) == 0x08, "");
static_assert(offsetof(ScnRenderDrViewCtrl, unknown1c) == 0x1c, "");
static_assert(offsetof(ScnRenderDrViewCtrl, unknown20) == 0x20, "");
static_assert(offsetof(ScnRenderDrViewCtrl, unknown28) == 0x28, "");
static_assert(offsetof(ScnRenderDrViewCtrl, unknown2c) == 0x2c, "");
static_assert(offsetof(ScnRenderDrViewCtrl, unknown30) == 0x30, "");
static_assert(offsetof(ScnRenderDrViewCtrl, unknown35) == 0x35, "");
static_assert(sizeof(ScnRenderDrViewCtrl) == 0x38, "");

class ScnRenderDrCapture {
public:
  grlib::CGLibTextureBuffer *texture;
};

} // namespace ml
