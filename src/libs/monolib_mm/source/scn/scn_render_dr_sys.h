#pragma once
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

  DrMan *drMan;
};

static_assert(offsetof(ScnRenderDrSys, drMan) == 0x10, "");
static_assert(sizeof(ScnRenderDrSys) == 0x18, "");

class ScnRenderDrViewCtrl {
public:
  u8 _00[0x08 - 0x00];
  s32 viewId;
  u8 _0c[0x20 - 0x0c];
  grlib::CGLibTextureBuffer *texture;
};

static_assert(offsetof(ScnRenderDrViewCtrl, viewId) == 0x08, "");
static_assert(offsetof(ScnRenderDrViewCtrl, texture) == 0x20, "");

class ScnRenderDrCapture {
public:
  grlib::CGLibTextureBuffer *texture;
};

} // namespace ml
