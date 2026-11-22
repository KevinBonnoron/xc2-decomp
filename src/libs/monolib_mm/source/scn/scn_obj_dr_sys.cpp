#include "scn/scn_obj_dr_sys.h"

#include "dr/dr_calc_clip_obj.h"
#include "dr/dr_creator.h"
#include "dr/dr_env_coli_obj.h"
#include "dr/dr_environment_obj.h"
#include "dr/dr_environment_obj_lgt.h"
#include "dr/dr_global_ibl_man.h"
#include "dr/dr_light_man.h"
#include "dr/dr_man.h"
#include "dr/dr_mdl_base.h"
#include "dr/dr_mdl_obj.h"
#include "ml/attr_transform.h"
#include "ml/scn.h"
#include "ml/scn_obj_model.h"
#include "ml/scn_pool_obj.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_array.h"
#include "mtl/alloc_handle.h"
#include "scn/scn_render_dr_sys.h"

namespace ml {

ScnObjClipDySys::ScnObjClipDySys(Scn *scn, const void *data, int screen) : ScnObjClip(scn), m_drCalcClipObj(nullptr), unknown60(screen), m_name("clipList") { createClipObj(data); }

void ScnObjClipDySys::createClipObj(const void *data) {
  DrCreator creator;
  m_drCalcClipObj = creator.createClipObj(data, unknown60);
}

ScnObjClipDySys::~ScnObjClipDySys() {
  if (m_drCalcClipObj != nullptr) {
    m_drCalcClipObj->release();
  }
}

ScnObj *ScnObjClipDySys::create(Scn *scn, const void *data, int screen) {
  if (!scn->m_scnPoolObj->isValidInsert(TYPE_UNKNOWN_4)) {
    return nullptr;
  }
  ScnObjClipDySys *clip = new (scn->m_ALLOC_HANDLE) ScnObjClipDySys(scn, data, screen);
  scn->m_scnPoolObj->insert(clip);
  return clip;
}

const char *ScnObjClipDySys::getName() const { return m_name.c_str(); }

ScnObjEnvColiDr::ScnObjEnvColiDr(Scn *scn, const void *data, int screen) : ScnObjEnvColi(scn) {
  DrCreator creator;
  m_drEnvColiObj = creator.createEnvColi(data, screen);
}

ScnObjEnvColiDr::~ScnObjEnvColiDr() {
  if (m_drEnvColiObj != nullptr) {
    m_drEnvColiObj->release();
  }
}

void ScnObjEnvColiDr::setPause(bool isPause) {
  if (m_drEnvColiObj != nullptr) {
    m_drEnvColiObj->setPause(isPause);
  }
}

bool ScnObjEnvColiDr::isPause() const {
  if (m_drEnvColiObj != nullptr) {
    return m_drEnvColiObj->isPause();
  }
  return false;
}

ScnObj *ScnObjEnvColiDr::create(Scn *scn, const void *data, int screen) {
  if (!scn->m_scnPoolObj->isValidInsert(TYPE_UNKNOWN_4)) {
    return nullptr;
  }
  ScnObjEnvColiDr *envColi = new (scn->m_ALLOC_HANDLE) ScnObjEnvColiDr(scn, data, screen);
  scn->m_scnPoolObj->insert(envColi);
  return envColi;
}

ScnObjIBLDr::ScnObjIBLDr(Scn *scn, const void *data, int screen) : ScnObjIBL(scn), m_drGlobalIBLPack(nullptr), unknown20(screen) { createIBLObj(data); }

void ScnObjIBLDr::createIBLObj(const void *data) {
  if (m_drGlobalIBLPack == nullptr && m_scn->unknown38 != nullptr) {
    DrMan *drMan = m_scn->unknown38->m_drMan;
    if (drMan != nullptr) {
      DrGlobalIBLMan *globalIBLMan = drMan->unknown160[unknown20];
      if (globalIBLMan != nullptr) {
        m_drGlobalIBLPack = globalIBLMan->createObj(data);
      }
    }
  }
}

ScnObjIBLDr::~ScnObjIBLDr() {
  if (m_drGlobalIBLPack != nullptr && m_scn->unknown38 != nullptr) {
    DrMan *drMan = m_scn->unknown38->m_drMan;
    if (drMan != nullptr) {
      DrGlobalIBLMan *globalIBLMan = drMan->unknown160[unknown20];
      if (globalIBLMan != nullptr) {
        globalIBLMan->releaseObj(m_drGlobalIBLPack);
      }
    }
  }
}

ScnObj *ScnObjIBLDr::create(Scn *scn, const void *data, int screen) {
  if (!scn->m_scnPoolObj->isValidInsert(TYPE_UNKNOWN_5)) {
    return nullptr;
  }
  ScnObjIBLDr *ibl = new (scn->m_ALLOC_HANDLE) ScnObjIBLDr(scn, data, screen);
  scn->m_scnPoolObj->insert(ibl);
  return ibl;
}

void ScnObjIBLDr::setReferencePos(const mm::Vec3 &position) {}

const mm::Vec3 &ScnObjIBLDr::getReferencePos() const { return mm::Vec3::zero; }

void ScnObjIBLDr::setFromCaptureTool() { m_drGlobalIBLPack->m_fromCaptureTool = 2; }

void ScnObjIBLDr::dispDebugWindow(bool isOpen, const char *title, WinProc *window) {}

void ScnObjIBLDr::apply() {
  DrGlobalIBLPack *pack = m_drGlobalIBLPack;
  if (pack != nullptr) {
    pack->unknown50 = !isDisp() ? pack->unknown50 | DrGlobalIBLPack::FLAG_UNKNOWN_0 : pack->unknown50 & ~DrGlobalIBLPack::FLAG_UNKNOWN_0;
  }
}

void ScnObjIBLDr::setName(const char *name) {}

const char *ScnObjIBLDr::getName() const { return "IBLList"; }

ScnObjLightDrSys::ScnObjLightDrSys(Scn *scn, const void *data, int screen) : ScnObjLight(scn), m_data(data), m_drEnvironmentObj(nullptr), unknown328(screen) { createDrLgt(); }

void ScnObjLightDrSys::createDrLgt() {
  if (!m_scn->m_scnPoolObj->isExistLgtEnv()) {
    DrMan *drMan = m_scn->unknown38->m_drMan;
    drMan->unknownc0[unknown328]->releaseFastLight();
  }
  DrCreator creator;
  m_drEnvironmentObj = creator.createLgt(m_data, unknown328);
}

ScnObjLightDrSys::~ScnObjLightDrSys() {
  if (m_drEnvironmentObj != nullptr) {
    m_drEnvironmentObj->release();
  }
}

void ScnObjLightDrSys::apply() {
  getTrans(false)->update();
  DrEnvironmentObj *drEnv = m_drEnvironmentObj;
  if (drEnv != nullptr) {
    if (isDisp()) {
      drEnv->unknown8c &= ~DrEnvironmentObj::FLAG_UNKNOWN_0;
    } else {
      drEnv->unknown8c |= DrEnvironmentObj::FLAG_UNKNOWN_0;
    }
    if (isOfsMatrix()) {
      m_drEnvironmentObj->unknown8c |= DrEnvironmentObj::FLAG_UNKNOWN_3;
      m_drEnvironmentObj->setMatrix(getTrans(false)->unknown70);
    } else {
      m_drEnvironmentObj->unknown8c &= ~DrEnvironmentObj::FLAG_UNKNOWN_2;
    }
  }
}

void ScnObjLightDrSys::tail() {}

f32 ScnObjLightDrSys::getFrame() const {
  if (m_drEnvironmentObj != nullptr) {
    return m_drEnvironmentObj->getFrame();
  }
  return 0.0f;
}

void ScnObjLightDrSys::setFrame(f32 frame) {
  if (m_drEnvironmentObj != nullptr) {
    m_drEnvironmentObj->setFrame(frame);
  }
}

f32 ScnObjLightDrSys::getMaxFrame() const {
  if (m_drEnvironmentObj != nullptr) {
    return m_drEnvironmentObj->getMaxFrame();
  }
  return 0.0f;
}

void ScnObjLightDrSys::setFrameSpd(f32 speed) {
  if (m_drEnvironmentObj != nullptr) {
    m_drEnvironmentObj->setFrameSpd(speed);
  }
}

f32 ScnObjLightDrSys::getFrameSpd() const {
  if (m_drEnvironmentObj != nullptr) {
    return m_drEnvironmentObj->getFrameSpd();
  }
  return 0.0f;
}

void ScnObjLightDrSys::setGroup(int group) { m_drEnvironmentObj->m_group = group; }

int ScnObjLightDrSys::getGroup() const { return m_drEnvironmentObj->m_group; }

void ScnObjLightDrSys::setOffsetPos(const mm::Vec3 &position) {
  if (m_drEnvironmentObj != nullptr) {
    m_drEnvironmentObj->m_offsetPos = position;
  }
}

const mm::Vec3 &ScnObjLightDrSys::getOffsetPos() const { return m_drEnvironmentObj->m_offsetPos; }

void ScnObjLightDrSys::setDeugDisp2D(bool isDisp) {
  if (isDisp) {
    m_drEnvironmentObj->unknown8c |= DrEnvironmentObj::FLAG_UNKNOWN_20;
  } else {
    m_drEnvironmentObj->unknown8c &= ~DrEnvironmentObj::FLAG_UNKNOWN_20;
  }
}

void ScnObjLightDrSys::setFromCaptureTool() { static_cast<DrEnvironmentObjLgt *>(m_drEnvironmentObj)->m_fromCaptureTool = 2; }

void ScnObjLightDrSys::setLocalIBLName(const char *name) {}

ScnObj *ScnObjLightDrSys::create(Scn *scn, const void *data, int screen) {
  if (!scn->m_scnPoolObj->isValidInsert(TYPE_UNKNOWN_4)) {
    return nullptr;
  }
  ScnObjLightDrSys *light = new (scn->m_ALLOC_HANDLE) ScnObjLightDrSys(scn, data, screen);
  scn->m_scnPoolObj->insert(light);
  return light;
}

bool ScnObjLightDrSys::isEnv() const { return m_drEnvironmentObj != nullptr; }

ScnObjModelDrSysStandard::ScnObjModelDrSysStandard(Scn *scn, const void *data, const char *name, int screen) : ScnObjModelDrSys(scn, data, name), _438(nullptr) { createScnMdl(screen); }

void ScnObjModelDrSysStandard::createScnMdl(int screen) {
  if (unknown3d8 == nullptr) {
    DrCreator creator;
    unknown3d8 = creator.createMdl(m_data, unknown350.c_str(), screen);
    if (unknown3d8->unknown1c == unknown037_3) {
      unknown34c |= FLAG_UNKNOWN_5;
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

// Inferred role: scales the rows of a world matrix by the scale of the transform of a model; original name unknown.
static void unknown001(mm::Mat44 &matrix, const ScnObjModel &model) {
  const AttrTransform *trans = model.getTrans(false);
  matrix.rows[0][0] = trans->unknown20.x * matrix.rows[0][0];
  matrix.rows[0][1] = trans->unknown20.x * matrix.rows[0][1];
  matrix.rows[0][2] = trans->unknown20.x * matrix.rows[0][2];
  matrix.rows[1][0] = trans->unknown20.y * matrix.rows[1][0];
  matrix.rows[1][1] = trans->unknown20.y * matrix.rows[1][1];
  matrix.rows[1][2] = trans->unknown20.y * matrix.rows[1][2];
  matrix.rows[2][0] = trans->unknown20.z * matrix.rows[2][0];
  matrix.rows[2][1] = trans->unknown20.z * matrix.rows[2][1];
  matrix.rows[2][2] = trans->unknown20.z * matrix.rows[2][2];
}

void ScnObjModelDrSysStandard::apply() {
  ScnObjModelDrSys::apply();
  if (unknown3d8 != nullptr) {
    mm::Mat44 matrix(getTrans(false)->unknown70);
    unknown001(matrix, *this);
    unknown3d8->setMatrix(matrix);
    unknown3d8->setOffsetPos(getOffsetInfo(false)->unknown00);
  }
}

void ScnObjModelDrSysStandard::tail() { ScnObjModel::tail(); }

ScnObjModelDrSysStandard *ScnObjModelDrSysStandard::create(Scn *scn, const void *data, const char *name, int screen) {
  if (!scn->m_scnPoolObj->isValidInsert(TYPE_UNKNOWN_1)) {
    return nullptr;
  }
  ScnObjModelDrSysStandard *model = new (scn->m_ALLOC_HANDLE) ScnObjModelDrSysStandard(scn, data, name, screen);
  scn->m_scnPoolObj->insert(model);
  return model;
}

} // namespace ml
