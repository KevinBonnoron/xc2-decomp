#include "ml/scn.h"

#include "ml/proc_desktop.h"
#include "ml/scn_obj_model.h"
#include "ml/scn_pool_obj.h"
#include "ml/work_cpu.h"
#include "scn/scn_debug.h"
#include "scn/scn_render_dr_sys.h"

namespace ml {

void Scn::setPause(bool isPause) {
  if (m_isPause != isPause) {
    m_isPause = isPause;
  }
}

void Scn::setDebDraw(SCNCAM cam, SCNPRIO_CB priority) { m_debDrawInfos[cam].priority = priority; }

ScnObjModel *Scn::createMdl(const void *data, const char *name, int screenID) {
  ScnObjModel *model = renderDrSys->createMdl(this, data, name, screenID);
  if (model != nullptr) {
    model->setAlwaysTexStm(!m_isTexStm);
  }
  return model;
}

ScnObj *Scn::createLgt(const void *data, int screenID) { return renderDrSys->createLgt(this, data, screenID); }

ScnObj *Scn::createClip(const void *data, int screenID) { return renderDrSys->createClip(this, data, screenID); }

ScnObj *Scn::createIBL(const void *data, int screenID) { return renderDrSys->createIBL(this, data, screenID); }

ScnObj *Scn::createEnvColi(const void *data, int screenID) { return renderDrSys->createEnvColi(this, data, screenID); }

void Scn::releaseItem(ScnObj *obj) {
  if (obj != nullptr) {
    poolObj->release(obj);
  }
}

void Scn::setDeleteRender() {
  if (renderDrSys != nullptr) {
    WorkCpu::runThread(WorkCpu::getRenderCPUID(), thRenderKillTerminate, this, nullptr, nullptr, true, WKCPU_SYNC_WAIT);
  }
}

u32 Scn::thRenderKillTerminate(void *argument, void *userData) {
  Scn *scn = static_cast<Scn *>(argument);
  if (scn->renderDrSys != nullptr) {
    delete scn->renderDrSys;
    scn->renderDrSys = nullptr;
  }
  return 0;
}

void Scn::renderStop() { m_isRenderStop = true; }

void Scn::setFrameSpd(f32 speed) { ProcDesktop::setUpdateRatio(speed); }

f32 Scn::getFrameSpd() const { return ProcDesktop::getUpdateRatio(); }

void Scn::enableScnDebug(bool isEnable) {
  if (m_scnDebug != nullptr) {
    m_scnDebug->_30 = isEnable;
  }
}

void Scn::setView(WinView *view, int screen) { m_camMan->setView(view, screen); }

void Scn::clrView(WinView *view, int screen) { m_camMan->clrView(view, screen); }

const ScnObjCam *ScnCamMan::getCam(const WinView *view) const { return m_scn->poolObj->getCam(view); }

ScnObjCam *ScnCamMan::getCam(const WinView *view) { return m_scn->poolObj->getCam(view); }

ScnObjCam *Scn::getCam(const WinView *view) { return m_camMan->getCam(view); }

const ScnObjCam *Scn::getCam(const WinView *view) const { return m_camMan->getCam(view); }

} // namespace ml
