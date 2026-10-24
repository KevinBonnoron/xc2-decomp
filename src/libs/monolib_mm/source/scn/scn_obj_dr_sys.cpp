#include "scn/scn_obj_dr_sys.h"

#include "dr/dr_calc_clip_obj.h"
#include "dr/dr_creator.h"
#include "dr/dr_env_coli_obj.h"
#include "dr/dr_environment_obj.h"
#include "dr/dr_global_ibl_man.h"
#include "dr/dr_light_man.h"
#include "dr/dr_man.h"
#include "dr/dr_mdl_base.h"
#include "dr/dr_mdl_obj.h"
#include "ml/attr_transform.h"
#include "ml/scn.h"
#include "ml/scn_obj_model.h"
#include "ml/scn_pool_obj.h"
#include "mm_math/mm_vec3.h"
#include "mtl/alloc_handle.h"
#include "scn/scn_render_dr_sys.h"

namespace ml {

ScnObjClipDySys::ScnObjClipDySys(Scn *scn, const void *data, int screen) : ScnObjClip(scn), m_clipObj(nullptr), m_screen(screen), m_listName("clipList") { createClipObj(data); }

void ScnObjClipDySys::createClipObj(const void *data) {
  DrCreator creator;
  m_clipObj = creator.createClipObj(data, m_screen);
}

ScnObjClipDySys::~ScnObjClipDySys() {
  if (m_clipObj != nullptr) {
    m_clipObj->release();
  }
}

ScnObj *ScnObjClipDySys::create(Scn *scn, const void *data, int screen) {
  if (!scn->poolObj->isValidInsert(TYPE_LIGHT)) {
    return nullptr;
  }
  ScnObjClipDySys *clip = new (scn->allocHandle) ScnObjClipDySys(scn, data, screen);
  scn->poolObj->insert(clip);
  return clip;
}

const char *ScnObjClipDySys::getName() const { return m_listName.c_str(); }

ScnObjEnvColiDr::ScnObjEnvColiDr(Scn *scn, const void *data, int screen) : ScnObjEnvColi(scn) {
  DrCreator creator;
  m_envColiObj = creator.createEnvColi(data, screen);
}

ScnObjEnvColiDr::~ScnObjEnvColiDr() {
  if (m_envColiObj != nullptr) {
    m_envColiObj->release();
  }
}

void ScnObjEnvColiDr::setPause(bool isPause) {
  if (m_envColiObj != nullptr) {
    m_envColiObj->setPause(isPause);
  }
}

bool ScnObjEnvColiDr::isPause() const {
  if (m_envColiObj != nullptr) {
    return m_envColiObj->isPause();
  }
  return false;
}

ScnObj *ScnObjEnvColiDr::create(Scn *scn, const void *data, int screen) {
  if (!scn->poolObj->isValidInsert(TYPE_LIGHT)) {
    return nullptr;
  }
  ScnObjEnvColiDr *envColi = new (scn->allocHandle) ScnObjEnvColiDr(scn, data, screen);
  scn->poolObj->insert(envColi);
  return envColi;
}

ScnObjIBLDr::ScnObjIBLDr(Scn *scn, const void *data, int screen) : ScnObjIBL(scn), m_pack(nullptr), m_screen(screen) { createIBLObj(data); }

void ScnObjIBLDr::createIBLObj(const void *data) {
  if (m_pack == nullptr && m_scn->renderDrSys != nullptr) {
    DrMan *drMan = m_scn->renderDrSys->drMan;
    if (drMan != nullptr) {
      DrGlobalIBLMan *globalIBLMan = drMan->globalIBLMans[m_screen];
      if (globalIBLMan != nullptr) {
        m_pack = globalIBLMan->createObj(data);
      }
    }
  }
}

ScnObjIBLDr::~ScnObjIBLDr() {
  if (m_pack != nullptr && m_scn->renderDrSys != nullptr) {
    DrMan *drMan = m_scn->renderDrSys->drMan;
    if (drMan != nullptr) {
      DrGlobalIBLMan *globalIBLMan = drMan->globalIBLMans[m_screen];
      if (globalIBLMan != nullptr) {
        globalIBLMan->releaseObj(m_pack);
      }
    }
  }
}

ScnObj *ScnObjIBLDr::create(Scn *scn, const void *data, int screen) {
  if (!scn->poolObj->isValidInsert(TYPE_IBL)) {
    return nullptr;
  }
  ScnObjIBLDr *ibl = new (scn->allocHandle) ScnObjIBLDr(scn, data, screen);
  scn->poolObj->insert(ibl);
  return ibl;
}

void ScnObjIBLDr::setReferencePos(const mm::Vec3 &position) {}

const mm::Vec3 &ScnObjIBLDr::getReferencePos() const { return mm::Vec3::zero; }

void ScnObjIBLDr::setFromCaptureTool() { m_pack->m_captureMode = 2; }

void ScnObjIBLDr::dispDebugWindow(bool isOpen, const char *title, WinProc *window) {}

void ScnObjIBLDr::apply() {
  DrGlobalIBLPack *pack = m_pack;
  if (pack != nullptr) {
    pack->m_flags = !isDisp() ? pack->m_flags | DrGlobalIBLPack::FLAG_DISP_OFF : pack->m_flags & ~DrGlobalIBLPack::FLAG_DISP_OFF;
  }
}

void ScnObjIBLDr::setName(const char *name) {}

const char *ScnObjIBLDr::getName() const { return "IBLList"; }

ScnObjLightDrSys::ScnObjLightDrSys(Scn *scn, const void *data, int screen) : ScnObjLight(scn), m_data(data), m_drEnv(nullptr), m_screen(screen) { createDrLgt(); }

void ScnObjLightDrSys::createDrLgt() {
  if (!m_scn->poolObj->isExistLgtEnv()) {
    DrMan *drMan = m_scn->renderDrSys->drMan;
    drMan->lightMans[m_screen]->releaseFastLight();
  }
  DrCreator creator;
  m_drEnv = creator.createLgt(m_data, m_screen);
}

ScnObjLightDrSys::~ScnObjLightDrSys() {
  if (m_drEnv != nullptr) {
    m_drEnv->release();
  }
}

void ScnObjLightDrSys::apply() {
  getTrans(false)->update();
  DrEnvironmentObj *drEnv = m_drEnv;
  if (drEnv != nullptr) {
    if (isDisp()) {
      drEnv->m_flags &= ~DrEnvironmentObj::FLAG_DISP_OFF;
    } else {
      drEnv->m_flags |= DrEnvironmentObj::FLAG_DISP_OFF;
    }
    if (isOfsMatrix()) {
      m_drEnv->m_flags |= DrEnvironmentObj::FLAG_OFS_MATRIX;
      m_drEnv->setMatrix(getTrans(false)->m_worldMatrix);
    } else {
      m_drEnv->m_flags &= ~DrEnvironmentObj::FLAG_GROUP;
    }
  }
}

void ScnObjLightDrSys::tail() {}

f32 ScnObjLightDrSys::getFrame() const {
  if (m_drEnv != nullptr) {
    return m_drEnv->getFrame();
  }
  return 0.0f;
}

void ScnObjLightDrSys::setFrame(f32 frame) {
  if (m_drEnv != nullptr) {
    m_drEnv->setFrame(frame);
  }
}

f32 ScnObjLightDrSys::getMaxFrame() const {
  if (m_drEnv != nullptr) {
    return m_drEnv->getMaxFrame();
  }
  return 0.0f;
}

void ScnObjLightDrSys::setFrameSpd(f32 speed) {
  if (m_drEnv != nullptr) {
    m_drEnv->setFrameSpd(speed);
  }
}

f32 ScnObjLightDrSys::getFrameSpd() const {
  if (m_drEnv != nullptr) {
    return m_drEnv->getFrameSpd();
  }
  return 0.0f;
}

void ScnObjLightDrSys::setGroup(int group) { m_drEnv->m_group = group; }

int ScnObjLightDrSys::getGroup() const { return m_drEnv->m_group; }

void ScnObjLightDrSys::setOffsetPos(const mm::Vec3 &position) {
  if (m_drEnv != nullptr) {
    m_drEnv->m_offsetPos = position;
  }
}

const mm::Vec3 &ScnObjLightDrSys::getOffsetPos() const { return m_drEnv->m_offsetPos; }

void ScnObjLightDrSys::setDeugDisp2D(bool isDisp) {
  if (isDisp) {
    m_drEnv->m_flags |= DrEnvironmentObj::FLAG_DEBUG_DISP_2D;
  } else {
    m_drEnv->m_flags &= ~DrEnvironmentObj::FLAG_DEBUG_DISP_2D;
  }
}

void ScnObjLightDrSys::setLocalIBLName(const char *name) {}

ScnObj *ScnObjLightDrSys::create(Scn *scn, const void *data, int screen) {
  if (!scn->poolObj->isValidInsert(TYPE_LIGHT)) {
    return nullptr;
  }
  ScnObjLightDrSys *light = new (scn->allocHandle) ScnObjLightDrSys(scn, data, screen);
  scn->poolObj->insert(light);
  return light;
}

bool ScnObjLightDrSys::isEnv() const { return m_drEnv != nullptr; }

ScnObjModelDrSysStandard::ScnObjModelDrSysStandard(Scn *scn, const void *data, const char *name, int screen) : ScnObjModelDrSys(scn, data, name), _438(nullptr) { createScnMdl(screen); }

void ScnObjModelDrSysStandard::createScnMdl(int screen) {
  if (m_drMdl == nullptr) {
    DrCreator creator;
    m_drMdl = creator.createMdl(m_data, m_streamPath.c_str(), screen);
    if (m_drMdl->m_type == DR_MDL_TYPE_SEAM) {
      m_flags |= FLAG_SEAM;
    }
  }
}

ScnObjModelDrSysStandard::~ScnObjModelDrSysStandard() {
  if (m_drMdl != nullptr) {
    m_drMdl->setDisp(false);
    m_drMdl->setDeleteCall(DrMan::s_nDblStockIdx);
  }
}

void ScnObjModelDrSysStandard::update() { ScnObjModelDrSys::update(); }

void ScnObjModelDrSysStandard::tail() { ScnObjModel::tail(); }

ScnObjModelDrSysStandard *ScnObjModelDrSysStandard::create(Scn *scn, const void *data, const char *name, int screen) {
  if (!scn->poolObj->isValidInsert(TYPE_MODEL)) {
    return nullptr;
  }
  ScnObjModelDrSysStandard *model = new (scn->allocHandle) ScnObjModelDrSysStandard(scn, data, name, screen);
  scn->poolObj->insert(model);
  return model;
}

} // namespace ml
