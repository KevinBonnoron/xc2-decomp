#include "scn/scn_render_dr_sys.h"

#include "dr/dr_man.h"
#include "ml/scn.h"
#include "ml/work_cpu.h"
#include "mtl/alloc_handle.h"
#include "scn/scn_obj_dr_sys.h"

namespace ml {

ScnRenderDrSys::ScnRenderDrSys(Scn *scn) : ScnRender(scn) { m_drMan = new (scn->m_ALLOC_HANDLE) DrMan(scn); }

ScnRenderDrSys::~ScnRenderDrSys() {
  if (m_drMan != nullptr) {
    delete m_drMan;
    m_drMan = nullptr;
  }
}

void ScnRenderDrSys::setDefaultEvn() {}

void ScnRenderDrSys::applyCamera(ScnObjCam *camera) {}

void ScnRenderDrSys::update() {}

void ScnRenderDrSys::applyBegin() { m_drMan->begin(); }

void ScnRenderDrSys::applyEnd() { m_drMan->end(); }

int ScnRenderDrSys::applyLoopCnt() { return m_drMan->loopCnt(); }

void ScnRenderDrSys::applyUpdate(int loop) { m_drMan->apply(loop); }

void ScnRenderDrSys::applyRender(int loop) { m_drMan->render(loop); }

void ScnRenderDrSys::tail() { m_drMan->tail(); }

void ScnRenderDrSys::setMdlDblPause(bool isPause) { m_drMan->m_mdlDblPause = isPause; }

void ScnRenderDrSys::setGlbSpd(f32 speed) { m_drMan->m_glbSpd = speed; }

void ScnRenderDrSys::setup(const ScnSetup *setup) {}

void ScnRenderDrSys::setCallBack(IDrDrawCallback *callback) { m_drMan->setCallBack(callback); }

void ScnRenderDrSys::releaseCallBack(IDrDrawCallback *callback) { m_drMan->releaseCallBack(callback); }

void ScnRenderDrSys::setReduction(bool isReduction, f32 scaleX, f32 scaleY) { m_drMan->setReduction(isReduction, scaleX, scaleY); }

void ScnRenderDrSys::setAA(bool isAA) { m_drMan->setAA(isAA); }

void ScnRenderDrSys::setColorFilter(bool isColorFilter) { m_drMan->setColorFilter(isColorFilter); }

void ScnRenderDrSys::setSSAO(bool isSSAO) { m_drMan->setSSAO(isSSAO); }

void ScnRenderDrSys::setBloom(bool isBloom, bool isLensFlare) { m_drMan->setBloom(isBloom, false); }

void ScnRenderDrSys::setToneMap(bool isToneMap) { m_drMan->setToneMap(isToneMap); }

void ScnRenderDrSys::setMotionBlur(bool isMotionBlur) { m_drMan->setMotionBlur(isMotionBlur); }

void ScnRenderDrSys::setMotionBlur(f32 strength, f32 sub) { m_drMan->setMotionBlur(strength, sub); }

void ScnRenderDrSys::setDepthOfField(bool isDepthOfField) { m_drMan->setDepthOfField(isDepthOfField); }

void ScnRenderDrSys::setDepthOfFieldParm(f32 distance, f32 range, f32 strength, f32 blend) { m_drMan->setDepthOfFieldParm(distance, range, strength, blend); }

void ScnRenderDrSys::setTimeVal(f32 timeVal) { m_drMan->setTimeVal(timeVal); }

void ScnRenderDrSys::openPixelDebugWindow(WinProc *window) { m_drMan->openPixelDebugWindow(window); }

void ScnRenderDrSys::openHisgtramDebugWindow(WinProc *window) { m_drMan->openHistgramDebugWindow(window); }

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

void ScnRenderDrSys::createDrRender(Scn *scn) { WorkCpu::runThread(WorkCpu::getRenderCPUID(), thDrSysInitialize, scn, nullptr, nullptr, true, WKCPU_SYNC_UNKNOWN_1); }

u32 ScnRenderDrSys::thDrSysInitialize(void *argument, void *userData) {
  Scn *scn = static_cast<Scn *>(argument);
  if (scn->unknown38 == nullptr) {
    scn->unknown38 = new (scn->m_ALLOC_HANDLE) ScnRenderDrSys(scn);
  }
  return 0;
}

} // namespace ml
