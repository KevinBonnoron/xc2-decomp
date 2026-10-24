#include "ml/scn.h"

#include "ml/proc_desktop.h"
#include "ml/scn_obj_model.h"
#include "ml/scn_pool_obj.h"
#include "ml/work_cpu.h"
#include "scn/scn_debug.h"
#include "scn/scn_render_dr_sys.h"

namespace ml {

void Scn::setPause(bool isPause) {
  if (unknowndf8 != isPause) {
    unknowndf8 = isPause;
  }
}

void Scn::setDebDraw(SCNCAM cam, SCNPRIO_CB priority) { unknowne00[cam].unknown00 = priority; }

ScnObjModel *Scn::createMdl(const void *data, const char *name, int screenID) {
  ScnObjModel *model = unknown38->createMdl(this, data, name, screenID);
  if (model != nullptr) {
    model->setAlwaysTexStm(!unknownac);
  }
  return model;
}

ScnObj *Scn::createLgt(const void *data, int screenID) { return unknown38->createLgt(this, data, screenID); }

ScnObj *Scn::createClip(const void *data, int screenID) { return unknown38->createClip(this, data, screenID); }

ScnObj *Scn::createIBL(const void *data, int screenID) { return unknown38->createIBL(this, data, screenID); }

ScnObj *Scn::createEnvColi(const void *data, int screenID) { return unknown38->createEnvColi(this, data, screenID); }

void Scn::releaseItem(ScnObj *obj) {
  if (obj != nullptr) {
    unknown20->release(obj);
  }
}

void Scn::setDeleteRender() {
  if (unknown38 != nullptr) {
    WorkCpu::runThread(WorkCpu::getRenderCPUID(), thRenderKillTerminate, this, nullptr, nullptr, true, WKCPU_SYNC_WAIT);
  }
}

u32 Scn::thRenderKillTerminate(void *argument, void *userData) {
  Scn *scn = static_cast<Scn *>(argument);
  if (scn->unknown38 != nullptr) {
    delete scn->unknown38;
    scn->unknown38 = nullptr;
  }
  return 0;
}

void Scn::renderStop() { unknowndf9 = true; }

void Scn::setFrameSpd(f32 speed) { ProcDesktop::setUpdateRatio(speed); }

f32 Scn::getFrameSpd() const { return ProcDesktop::getUpdateRatio(); }

void Scn::enableScnDebug(bool isEnable) {
  if (unknown30 != nullptr) {
    unknown30->_30 = isEnable;
  }
}

void Scn::setView(WinView *view, int screen) { unknown28->setView(view, screen); }

void Scn::clrView(WinView *view, int screen) { unknown28->clrView(view, screen); }

const ScnObjCam *ScnCamMan::getCam(const WinView *view) const { return unknown08->unknown20->getCam(view); }

ScnObjCam *ScnCamMan::getCam(const WinView *view) { return unknown08->unknown20->getCam(view); }

ScnObjCam *Scn::getCam(const WinView *view) { return unknown28->getCam(view); }

const ScnObjCam *Scn::getCam(const WinView *view) const { return unknown28->getCam(view); }

} // namespace ml
