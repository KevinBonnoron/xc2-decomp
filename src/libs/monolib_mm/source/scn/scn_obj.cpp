#include "ml/scn_obj.h"

#include <string.h>

#include "ml/attr_transform.h"
#include "ml/scn_obj_clip.h"
#include "ml/scn_obj_env_coli.h"
#include "ml/scn_obj_ibl.h"
#include "ml/scn_obj_light.h"
#include "ml/scn_obj_model.h"
#include "ml/threadval.h"
#include "types.h"

namespace ml {
class Scn;

ScnObjLight::ScnObjLight(Scn *scn) : ScnObj(scn, TYPE_LIGHT), unknown310(0) {
  unknown60.m_back->unknown00.clear();
  memcpy(unknown60.m_front, unknown60.m_back, sizeof(RENDER_INFO));
  unknown60.m_flags.set(threadval<RENDER_INFO>::FLAG_SYNC);
  unknown310 |= FLAG_DISP;
}

const AttrTransform *ScnObjLight::getTrans(bool isBack) const { return &(isBack ? unknown60.m_back : unknown60.m_front)->unknown00; }

AttrTransform *ScnObjLight::getTrans(bool isBack) { return &(isBack ? unknown60.m_back : unknown60.m_front)->unknown00; }

void ScnObjLight::setDisp(bool isDisp) {
  if (isDisp) {
    unknown310 |= FLAG_DISP;
  } else {
    unknown310 &= ~FLAG_DISP;
  }
}

bool ScnObjLight::isDisp() const { return unknown310 & FLAG_DISP; }

void ScnObjLight::setOfsMatrix(bool isOfsMatrix) {
  if (isOfsMatrix) {
    unknown310 |= FLAG_OFS_MATRIX;
  } else {
    unknown310 &= ~FLAG_OFS_MATRIX;
  }
}

bool ScnObjLight::isOfsMatrix() const { return unknown310 & FLAG_OFS_MATRIX; }

ScnObjClip::ScnObjClip(Scn *scn) : ScnObj(scn, TYPE_CLIP), m_name("clipList") {}

ScnObjClip::~ScnObjClip() {}

ScnObjEnvColi::ScnObjEnvColi(Scn *scn) : ScnObj(scn, TYPE_CLIP), m_name("envColi") {}

ScnObjEnvColi::~ScnObjEnvColi() {}

void ScnObjModel::setDelete() { unknown12 = true; }

void ScnObj::setDelete() { unknown12 = true; }

void ScnObjModel::setFrameSpd(f32 speed) { m_frameSpd = speed; }

void ScnObjModel::setDisp(bool isDisp) {
  if (isDisp) {
    unknown34c |= FLAG_DISP_NEXT;
  } else {
    unknown34c &= ~FLAG_DISP_NEXT;
  }
}

void ScnObjModel::setClip(bool isClip) {
  if (isClip) {
    unknown34c |= FLAG_CLIP;
  } else {
    unknown34c &= ~FLAG_CLIP;
  }
}

AttrTransform *ScnObjModel::getTrans(bool isBack) { return &(isBack ? unknown20.m_back : unknown20.m_front)->unknown00; }

const AttrTransform *ScnObjModel::getTrans(bool isBack) const { return &(isBack ? unknown20.m_back : unknown20.m_front)->unknown00; }

ScnObjModel::RENDER_OFFSET_INFO *ScnObjModel::getOffsetInfo(bool isBack) { return isBack ? unknown2d0.m_back : unknown2d0.m_front; }

const ScnObjModel::RENDER_OFFSET_INFO *ScnObjModel::getOffsetInfo(bool isBack) const { return isBack ? unknown2d0.m_back : unknown2d0.m_front; }

bool ScnObjModel::isDisp() const { return unknown34c & FLAG_DISP; }

bool ScnObjModel::isClip() const { return unknown34c & FLAG_CLIP; }

void ScnObjModel::renderDebug(DebDraw *debDraw) {}

ScnObjIBL::ScnObjIBL(Scn *scn) : ScnObj(scn, TYPE_IBL), unknown14(FLAG_DISP) {}

ScnObjIBL::~ScnObjIBL() {}

void ScnObjIBL::setDisp(bool isDisp) {
  if (isDisp) {
    unknown14 |= FLAG_DISP;
  } else {
    unknown14 &= ~FLAG_DISP;
  }
}

bool ScnObjIBL::isDisp() const { return unknown14 & FLAG_DISP; }

} // namespace ml
