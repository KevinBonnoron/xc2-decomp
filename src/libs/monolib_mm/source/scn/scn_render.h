#pragma once
#include <stddef.h>

#include "ml/work_event.h"
#include "types.h"

namespace ml {
class Scn;
class ScnObj;
class ScnObjCam;
class ScnObjModel;
class ScnSetup;
class WinProc;

class ScnRender : public IWorkEvent {
public:
  ScnRender(Scn *scn);
  ~ScnRender() override;
  virtual void setDefaultEvn() {}
  virtual void applyCamera(ScnObjCam *camera) {}
  virtual void update() {}
  virtual void applyBegin() {}
  virtual void applyEnd() {}
  virtual int applyLoopCnt() { return 1; }
  virtual void applyUpdate(int loop) {}
  virtual void applyRender(int loop) {}
  virtual void tail() {}
  virtual void setMdlDblPause(bool isPause) {}
  virtual void setGlbSpd(f32 speed) {}
  virtual bool attachModel(ScnObjModel *model) { return false; }
  virtual void setup(const ScnSetup *setup) {}
  virtual void openPixelDebugWindow(WinProc *window) {}
  virtual void openHisgtramDebugWindow(WinProc *window) {}
  virtual ScnObjModel *createMdl(Scn *scn, const void *data, const char *name, int screen) { return nullptr; }
  virtual ScnObj *createLgt(Scn *scn, const void *data, int screen) { return nullptr; }
  virtual ScnObj *createClip(Scn *scn, const void *data, int screen) = 0;
  virtual ScnObj *createIBL(Scn *scn, const void *data, int screen) = 0;
  virtual ScnObj *createEnvColi(Scn *scn, const void *data, int screen) = 0;

  Scn *unknown08; // Inferred role: scn; original member name unknown.
};

static_assert(offsetof(ScnRender, unknown08) == 0x08, "");

} // namespace ml
