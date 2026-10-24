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

ScnObjClipDySys::ScnObjClipDySys(Scn *scn, const void *data, int screen) : ScnObjClip(scn), unknown58(nullptr), unknown60(screen), m_name("clipList") { createClipObj(data); }

void ScnObjClipDySys::createClipObj(const void *data) {
  DrCreator creator;
  unknown58 = creator.createClipObj(data, unknown60);
}

ScnObjClipDySys::~ScnObjClipDySys() {
  if (unknown58 != nullptr) {
    unknown58->release();
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

const char *ScnObjClipDySys::getName() const { return m_name.c_str(); }

ScnObjEnvColiDr::ScnObjEnvColiDr(Scn *scn, const void *data, int screen) : ScnObjEnvColi(scn) {
  DrCreator creator;
  unknown58 = creator.createEnvColi(data, screen);
}

ScnObjEnvColiDr::~ScnObjEnvColiDr() {
  if (unknown58 != nullptr) {
    unknown58->release();
  }
}

void ScnObjEnvColiDr::setPause(bool isPause) {
  if (unknown58 != nullptr) {
    unknown58->setPause(isPause);
  }
}

bool ScnObjEnvColiDr::isPause() const {
  if (unknown58 != nullptr) {
    return unknown58->isPause();
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

ScnObjIBLDr::ScnObjIBLDr(Scn *scn, const void *data, int screen) : ScnObjIBL(scn), unknown18(nullptr), unknown20(screen) { createIBLObj(data); }

void ScnObjIBLDr::createIBLObj(const void *data) {
  if (unknown18 == nullptr && m_scn->renderDrSys != nullptr) {
    DrMan *drMan = m_scn->renderDrSys->unknown10;
    if (drMan != nullptr) {
      DrGlobalIBLMan *globalIBLMan = drMan->unknown160[unknown20];
      if (globalIBLMan != nullptr) {
        unknown18 = globalIBLMan->createObj(data);
      }
    }
  }
}

ScnObjIBLDr::~ScnObjIBLDr() {
  if (unknown18 != nullptr && m_scn->renderDrSys != nullptr) {
    DrMan *drMan = m_scn->renderDrSys->unknown10;
    if (drMan != nullptr) {
      DrGlobalIBLMan *globalIBLMan = drMan->unknown160[unknown20];
      if (globalIBLMan != nullptr) {
        globalIBLMan->releaseObj(unknown18);
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

void ScnObjIBLDr::setFromCaptureTool() { unknown18->unknown58 = 2; }

void ScnObjIBLDr::dispDebugWindow(bool isOpen, const char *title, WinProc *window) {}

void ScnObjIBLDr::apply() {
  DrGlobalIBLPack *pack = unknown18;
  if (pack != nullptr) {
    pack->unknown50 = !isDisp() ? pack->unknown50 | DrGlobalIBLPack::FLAG_DISP_OFF : pack->unknown50 & ~DrGlobalIBLPack::FLAG_DISP_OFF;
  }
}

void ScnObjIBLDr::setName(const char *name) {}

const char *ScnObjIBLDr::getName() const { return "IBLList"; }

ScnObjLightDrSys::ScnObjLightDrSys(Scn *scn, const void *data, int screen) : ScnObjLight(scn), m_data(data), unknown320(nullptr), unknown328(screen) { createDrLgt(); }

void ScnObjLightDrSys::createDrLgt() {
  if (!m_scn->poolObj->isExistLgtEnv()) {
    DrMan *drMan = m_scn->renderDrSys->unknown10;
    drMan->unknownc0[unknown328]->releaseFastLight();
  }
  DrCreator creator;
  unknown320 = creator.createLgt(m_data, unknown328);
}

ScnObjLightDrSys::~ScnObjLightDrSys() {
  if (unknown320 != nullptr) {
    unknown320->release();
  }
}

void ScnObjLightDrSys::apply() {
  getTrans(false)->update();
  DrEnvironmentObj *drEnv = unknown320;
  if (drEnv != nullptr) {
    if (isDisp()) {
      drEnv->unknown8c &= ~DrEnvironmentObj::FLAG_DISP_OFF;
    } else {
      drEnv->unknown8c |= DrEnvironmentObj::FLAG_DISP_OFF;
    }
    if (isOfsMatrix()) {
      unknown320->unknown8c |= DrEnvironmentObj::FLAG_OFS_MATRIX;
      unknown320->setMatrix(getTrans(false)->m_worldMatrix);
    } else {
      unknown320->unknown8c &= ~DrEnvironmentObj::FLAG_GROUP;
    }
  }
}

void ScnObjLightDrSys::tail() {}

f32 ScnObjLightDrSys::getFrame() const {
  if (unknown320 != nullptr) {
    return unknown320->getFrame();
  }
  return 0.0f;
}

void ScnObjLightDrSys::setFrame(f32 frame) {
  if (unknown320 != nullptr) {
    unknown320->setFrame(frame);
  }
}

f32 ScnObjLightDrSys::getMaxFrame() const {
  if (unknown320 != nullptr) {
    return unknown320->getMaxFrame();
  }
  return 0.0f;
}

void ScnObjLightDrSys::setFrameSpd(f32 speed) {
  if (unknown320 != nullptr) {
    unknown320->setFrameSpd(speed);
  }
}

f32 ScnObjLightDrSys::getFrameSpd() const {
  if (unknown320 != nullptr) {
    return unknown320->getFrameSpd();
  }
  return 0.0f;
}

void ScnObjLightDrSys::setGroup(int group) { unknown320->unknown90 = group; }

int ScnObjLightDrSys::getGroup() const { return unknown320->unknown90; }

void ScnObjLightDrSys::setOffsetPos(const mm::Vec3 &position) {
  if (unknown320 != nullptr) {
    unknown320->unknown70 = position;
  }
}

const mm::Vec3 &ScnObjLightDrSys::getOffsetPos() const { return unknown320->unknown70; }

void ScnObjLightDrSys::setDeugDisp2D(bool isDisp) {
  if (isDisp) {
    unknown320->unknown8c |= DrEnvironmentObj::FLAG_DEBUG_DISP_2D;
  } else {
    unknown320->unknown8c &= ~DrEnvironmentObj::FLAG_DEBUG_DISP_2D;
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

bool ScnObjLightDrSys::isEnv() const { return unknown320 != nullptr; }

ScnObjModelDrSysStandard::ScnObjModelDrSysStandard(Scn *scn, const void *data, const char *name, int screen) : ScnObjModelDrSys(scn, data, name), _438(nullptr) { createScnMdl(screen); }

void ScnObjModelDrSysStandard::createScnMdl(int screen) {
  if (unknown3d8 == nullptr) {
    DrCreator creator;
    unknown3d8 = creator.createMdl(m_data, m_streamPath.c_str(), screen);
    if (unknown3d8->unknown1c == DR_MDL_TYPE_SEAM) {
      m_flags |= FLAG_SEAM;
    }
  }
}

ScnObjModelDrSysStandard::~ScnObjModelDrSysStandard() {
  if (unknown3d8 != nullptr) {
    unknown3d8->setDisp(false);
    unknown3d8->setDeleteCall(DrMan::s_nDblStockIdx);
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
