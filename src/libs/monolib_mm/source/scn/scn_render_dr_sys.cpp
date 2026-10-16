#include "scn/scn_render_dr_sys.h"

#include "dr/dr_man.h"
#include "ml/scn.h"
#include "ml/work_cpu.h"
#include "mtl/alloc_handle.h"
#include "scn/scn_obj_dr_sys.h"

namespace ml {

ScnRenderDrSys::ScnRenderDrSys(Scn *scn) : ScnRender(scn) { drMan = new (scn->allocHandle) DrMan(scn); }

ScnRenderDrSys::~ScnRenderDrSys() {
  if (drMan != nullptr) {
    delete drMan;
    drMan = nullptr;
  }
}

void ScnRenderDrSys::setDefaultEvn() {}

void ScnRenderDrSys::applyCamera(ScnObjCam *camera) {}

void ScnRenderDrSys::update() {}

void ScnRenderDrSys::applyBegin() { drMan->begin(); }

void ScnRenderDrSys::applyEnd() { drMan->end(); }

int ScnRenderDrSys::applyLoopCnt() { return drMan->loopCnt(); }

void ScnRenderDrSys::applyUpdate(int loop) { drMan->apply(loop); }

void ScnRenderDrSys::applyRender(int loop) { drMan->render(loop); }

void ScnRenderDrSys::tail() { drMan->tail(); }

void ScnRenderDrSys::setMdlDblPause(bool isPause) { drMan->mdlDblPause = isPause; }

void ScnRenderDrSys::setGlbSpd(f32 speed) { drMan->glbSpd = speed; }

void ScnRenderDrSys::setup(const ScnSetup *setup) {}

void ScnRenderDrSys::setCallBack(IDrDrawCallback *callback) { drMan->setCallBack(callback); }

void ScnRenderDrSys::releaseCallBack(IDrDrawCallback *callback) { drMan->releaseCallBack(callback); }

void ScnRenderDrSys::setReduction(bool isReduction, f32 scaleX, f32 scaleY) { drMan->setReduction(isReduction, scaleX, scaleY); }

void ScnRenderDrSys::setAA(bool isAA) { drMan->setAA(isAA); }

void ScnRenderDrSys::setColorFilter(bool isColorFilter) { drMan->setColorFilter(isColorFilter); }

void ScnRenderDrSys::setSSAO(bool isSSAO) { drMan->setSSAO(isSSAO); }

void ScnRenderDrSys::setBloom(bool isBloom, bool isLensFlare) { drMan->setBloom(isBloom, false); }

void ScnRenderDrSys::setToneMap(bool isToneMap) { drMan->setToneMap(isToneMap); }

void ScnRenderDrSys::setMotionBlur(bool isMotionBlur) { drMan->setMotionBlur(isMotionBlur); }

void ScnRenderDrSys::setMotionBlur(f32 strength, f32 sub) { drMan->setMotionBlur(strength, sub); }

void ScnRenderDrSys::setDepthOfField(bool isDepthOfField) { drMan->setDepthOfField(isDepthOfField); }

void ScnRenderDrSys::setDepthOfFieldParm(f32 distance, f32 range, f32 strength, f32 blend) {
  drMan->setDepthOfFieldParm(distance, range, strength, blend);
}

void ScnRenderDrSys::setTimeVal(f32 timeVal) { drMan->setTimeVal(timeVal); }

void ScnRenderDrSys::openPixelDebugWindow(WinProc *window) { drMan->openPixelDebugWindow(window); }

void ScnRenderDrSys::openHisgtramDebugWindow(WinProc *window) { drMan->openHistgramDebugWindow(window); }

ScnObjModel *ScnRenderDrSys::createMdl(Scn *scn, const void *data, const char *name, int screen) {
  if (data == nullptr) {
    return nullptr;
  }
  return ScnObjModelDrSysStandard::create(scn, data, name, screen);
}

ScnObj *ScnRenderDrSys::createLgt(Scn *scn, const void *data, int screen) { return ScnObjLightDrSys::create(scn, data, screen); }

ScnObj *ScnRenderDrSys::createClip(Scn *scn, const void *data, int screen) { return ScnObjClipDySys::create(scn, data, screen); }

ScnObj *ScnRenderDrSys::createIBL(Scn *scn, const void *data, int screen) { return ScnObjIBLDr::create(scn, data, screen); }

ScnObj *ScnRenderDrSys::createEnvColi(Scn *scn, const void *data, int screen) { return ScnObjEnvColiDr::create(scn, data, screen); }

void ScnRenderDrSys::createDrRender(Scn *scn) {
  WorkCpu::runThread(WorkCpu::getRenderCPUID(), thDrSysInitialize, scn, nullptr, nullptr, true, WKCPU_SYNC_WAIT);
}

u32 ScnRenderDrSys::thDrSysInitialize(void *argument, void *userData) {
  Scn *scn = static_cast<Scn *>(argument);
  if (scn->renderDrSys == nullptr) {
    scn->renderDrSys = new (scn->allocHandle) ScnRenderDrSys(scn);
  }
  return 0;
}

} // namespace ml
