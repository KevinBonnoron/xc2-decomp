#include "ml/scn_obj.h"
#include "ml/attr_transform.h"
#include "ml/scn_obj_clip.h"
#include "ml/scn_obj_env_coli.h"
#include "ml/scn_obj_ibl.h"
#include "ml/scn_obj_light.h"
#include "ml/scn_obj_model.h"
#include "ml/threadval.h"
#include "string.h"
#include "types.h"

namespace ml {
class Scn;

ScnObjLight::ScnObjLight(Scn *scn) : ScnObj(scn, TYPE_LIGHT), m_flags(0) {
  m_renderInfo.m_back->transform.clear();
  memcpy(m_renderInfo.m_front, m_renderInfo.m_back, sizeof(RENDER_INFO));
  m_renderInfo.m_flags.set(threadval<RENDER_INFO>::FLAG_SYNC);
  m_flags |= FLAG_DISP;
}

const AttrTransform *ScnObjLight::getTrans(bool isBack) const { return &(isBack ? m_renderInfo.m_back : m_renderInfo.m_front)->transform; }

AttrTransform *ScnObjLight::getTrans(bool isBack) { return &(isBack ? m_renderInfo.m_back : m_renderInfo.m_front)->transform; }

void ScnObjLight::setDisp(bool isDisp) {
  if (isDisp) {
    m_flags |= FLAG_DISP;
  } else {
    m_flags &= ~FLAG_DISP;
  }
}

bool ScnObjLight::isDisp() const { return m_flags & FLAG_DISP; }

void ScnObjLight::setOfsMatrix(bool isOfsMatrix) {
  if (isOfsMatrix) {
    m_flags |= FLAG_OFS_MATRIX;
  } else {
    m_flags &= ~FLAG_OFS_MATRIX;
  }
}

bool ScnObjLight::isOfsMatrix() const { return m_flags & FLAG_OFS_MATRIX; }

ScnObjClip::ScnObjClip(Scn *scn) : ScnObj(scn, TYPE_CLIP), m_name("clipList") {}

ScnObjClip::~ScnObjClip() {}

ScnObjEnvColi::ScnObjEnvColi(Scn *scn) : ScnObj(scn, TYPE_CLIP), m_name("envColi") {}

ScnObjEnvColi::~ScnObjEnvColi() {}

void ScnObjModel::setDelete() { m_isDelete = true; }

void ScnObj::setDelete() { m_isDelete = true; }

void ScnObjModel::setFrameSpd(f32 speed) { m_frameSpd = speed; }

void ScnObjModel::setDisp(bool isDisp) {
  if (isDisp) {
    m_flags |= FLAG_DISP_NEXT;
  } else {
    m_flags &= ~FLAG_DISP_NEXT;
  }
}

void ScnObjModel::setClip(bool isClip) {
  if (isClip) {
    m_flags |= FLAG_CLIP;
  } else {
    m_flags &= ~FLAG_CLIP;
  }
}

AttrTransform *ScnObjModel::getTrans(bool isBack) { return &(isBack ? m_renderInfo.m_back : m_renderInfo.m_front)->transform; }

const AttrTransform *ScnObjModel::getTrans(bool isBack) const { return &(isBack ? m_renderInfo.m_back : m_renderInfo.m_front)->transform; }

ScnObjModel::RENDER_OFFSET_INFO *ScnObjModel::getOffsetInfo(bool isBack) { return isBack ? m_offsetInfo.m_back : m_offsetInfo.m_front; }

const ScnObjModel::RENDER_OFFSET_INFO *ScnObjModel::getOffsetInfo(bool isBack) const { return isBack ? m_offsetInfo.m_back : m_offsetInfo.m_front; }

bool ScnObjModel::isDisp() const { return m_flags & FLAG_DISP; }

bool ScnObjModel::isClip() const { return m_flags & FLAG_CLIP; }

void ScnObjModel::renderDebug(DebDraw *debDraw) {}

ScnObjIBL::ScnObjIBL(Scn *scn) : ScnObj(scn, TYPE_IBL), m_flags(FLAG_DISP) {}

ScnObjIBL::~ScnObjIBL() {}

void ScnObjIBL::setDisp(bool isDisp) {
  if (isDisp) {
    m_flags |= FLAG_DISP;
  } else {
    m_flags &= ~FLAG_DISP;
  }
}

bool ScnObjIBL::isDisp() const { return m_flags & FLAG_DISP; }

} // namespace ml
