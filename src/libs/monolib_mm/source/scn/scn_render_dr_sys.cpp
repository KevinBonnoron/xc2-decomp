#include "scn/scn_render_dr_sys.h"

#include "dr/dr_man.h"
#include "ml/scn.h"
#include "ml/work_cpu.h"
#include "mtl/alloc_handle.h"
#include "scn/scn_obj_dr_sys.h"

namespace ml {

ScnRenderDrSys::ScnRenderDrSys(Scn *scn) : ScnRender(scn) { unknown10 = new (scn->unknown64) DrMan(scn); }

ScnRenderDrSys::~ScnRenderDrSys() {
  if (unknown10 != nullptr) {
    delete unknown10;
    unknown10 = nullptr;
  }
}

void ScnRenderDrSys::setDefaultEvn() {}

void ScnRenderDrSys::applyCamera(ScnObjCam *camera) {}

void ScnRenderDrSys::update() {}

void ScnRenderDrSys::applyBegin() { unknown10->begin(); }

void ScnRenderDrSys::applyEnd() { unknown10->end(); }

int ScnRenderDrSys::applyLoopCnt() { return unknown10->loopCnt(); }

void ScnRenderDrSys::applyUpdate(int loop) { unknown10->apply(loop); }

void ScnRenderDrSys::applyRender(int loop) { unknown10->render(loop); }

void ScnRenderDrSys::tail() { unknown10->tail(); }

void ScnRenderDrSys::setMdlDblPause(bool isPause) { unknown10->unknown1d7b = isPause; }

void ScnRenderDrSys::setGlbSpd(f32 speed) { unknown10->unknown1c84 = speed; }

void ScnRenderDrSys::setup(const ScnSetup *setup) {}

void ScnRenderDrSys::setCallBack(IDrDrawCallback *callback) { unknown10->setCallBack(callback); }

void ScnRenderDrSys::releaseCallBack(IDrDrawCallback *callback) { unknown10->releaseCallBack(callback); }

void ScnRenderDrSys::setReduction(bool isReduction, f32 scaleX, f32 scaleY) { unknown10->setReduction(isReduction, scaleX, scaleY); }

void ScnRenderDrSys::setAA(bool isAA) { unknown10->setAA(isAA); }

void ScnRenderDrSys::setColorFilter(bool isColorFilter) { unknown10->setColorFilter(isColorFilter); }

void ScnRenderDrSys::setSSAO(bool isSSAO) { unknown10->setSSAO(isSSAO); }

void ScnRenderDrSys::setBloom(bool isBloom, bool isLensFlare) { unknown10->setBloom(isBloom, false); }

void ScnRenderDrSys::setToneMap(bool isToneMap) { unknown10->setToneMap(isToneMap); }

void ScnRenderDrSys::setMotionBlur(bool isMotionBlur) { unknown10->setMotionBlur(isMotionBlur); }

void ScnRenderDrSys::setMotionBlur(f32 strength, f32 sub) { unknown10->setMotionBlur(strength, sub); }

void ScnRenderDrSys::setDepthOfField(bool isDepthOfField) { unknown10->setDepthOfField(isDepthOfField); }

void ScnRenderDrSys::setDepthOfFieldParm(f32 distance, f32 range, f32 strength, f32 blend) { unknown10->setDepthOfFieldParm(distance, range, strength, blend); }

void ScnRenderDrSys::setTimeVal(f32 timeVal) { unknown10->setTimeVal(timeVal); }

void ScnRenderDrSys::openPixelDebugWindow(WinProc *window) { unknown10->openPixelDebugWindow(window); }

void ScnRenderDrSys::openHisgtramDebugWindow(WinProc *window) { unknown10->openHistgramDebugWindow(window); }

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

void ScnRenderDrSys::createDrRender(Scn *scn) { WorkCpu::runThread(WorkCpu::getRenderCPUID(), thDrSysInitialize, scn, nullptr, nullptr, true, WKCPU_SYNC_WAIT); }

u32 ScnRenderDrSys::thDrSysInitialize(void *argument, void *userData) {
  Scn *scn = static_cast<Scn *>(argument);
  if (scn->unknown38 == nullptr) {
    scn->unknown38 = new (scn->unknown64) ScnRenderDrSys(scn);
  }
  return 0;
}

} // namespace ml
