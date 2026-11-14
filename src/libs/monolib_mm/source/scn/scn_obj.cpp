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

ScnObjLight::ScnObjLight(Scn *scn) : ScnObj(scn, TYPE_UNKNOWN_4), unknown310(0) {
  unknown60.m_back->unknown00.clear();
  memcpy(unknown60.m_front, unknown60.m_back, sizeof(RENDER_INFO));
  unknown60.m_flags.set(threadval<RENDER_INFO>::FLAG_UNKNOWN_0);
  unknown310 |= FLAG_UNKNOWN_0;
}

const AttrTransform *ScnObjLight::getTrans(bool isBack) const { return &(isBack ? unknown60.m_back : unknown60.m_front)->unknown00; }

AttrTransform *ScnObjLight::getTrans(bool isBack) { return &(isBack ? unknown60.m_back : unknown60.m_front)->unknown00; }

void ScnObjLight::setDisp(bool isDisp) {
  if (isDisp) {
    unknown310 |= FLAG_UNKNOWN_0;
  } else {
    unknown310 &= ~FLAG_UNKNOWN_0;
  }
}

bool ScnObjLight::isDisp() const { return unknown310 & FLAG_UNKNOWN_0; }

void ScnObjLight::setOfsMatrix(bool isOfsMatrix) {
  if (isOfsMatrix) {
    unknown310 |= FLAG_UNKNOWN_1;
  } else {
    unknown310 &= ~FLAG_UNKNOWN_1;
  }
}

bool ScnObjLight::isOfsMatrix() const { return unknown310 & FLAG_UNKNOWN_1; }

ScnObjClip::ScnObjClip(Scn *scn) : ScnObj(scn, TYPE_UNKNOWN_6), m_name("clipList") {}

ScnObjClip::~ScnObjClip() {}

ScnObjEnvColi::ScnObjEnvColi(Scn *scn) : ScnObj(scn, TYPE_UNKNOWN_6), m_name("envColi") {}

ScnObjEnvColi::~ScnObjEnvColi() {}

void ScnObjModel::setDelete() { m_delete = true; }

void ScnObj::setDelete() { m_delete = true; }

void ScnObjModel::setFrameSpd(f32 speed) { m_frameSpd = speed; }

void ScnObjModel::setDisp(bool isDisp) {
  if (isDisp) {
    unknown34c |= FLAG_UNKNOWN_16;
  } else {
    unknown34c &= ~FLAG_UNKNOWN_16;
  }
}

void ScnObjModel::setClip(bool isClip) {
  if (isClip) {
    unknown34c |= FLAG_UNKNOWN_1;
  } else {
    unknown34c &= ~FLAG_UNKNOWN_1;
  }
}

AttrTransform *ScnObjModel::getTrans(bool isBack) { return &(isBack ? unknown20.m_back : unknown20.m_front)->unknown00; }

const AttrTransform *ScnObjModel::getTrans(bool isBack) const { return &(isBack ? unknown20.m_back : unknown20.m_front)->unknown00; }

ScnObjModel::RENDER_OFFSET_INFO *ScnObjModel::getOffsetInfo(bool isBack) { return isBack ? unknown2d0.m_back : unknown2d0.m_front; }

const ScnObjModel::RENDER_OFFSET_INFO *ScnObjModel::getOffsetInfo(bool isBack) const { return isBack ? unknown2d0.m_back : unknown2d0.m_front; }

bool ScnObjModel::isDisp() const { return unknown34c & FLAG_UNKNOWN_0; }

bool ScnObjModel::isClip() const { return unknown34c & FLAG_UNKNOWN_1; }

void ScnObjModel::renderDebug(DebDraw *debDraw) {}

ScnObjIBL::ScnObjIBL(Scn *scn) : ScnObj(scn, TYPE_UNKNOWN_5), unknown14(FLAG_UNKNOWN_0) {}

ScnObjIBL::~ScnObjIBL() {}

void ScnObjIBL::setDisp(bool isDisp) {
  if (isDisp) {
    unknown14 |= FLAG_UNKNOWN_0;
  } else {
    unknown14 &= ~FLAG_UNKNOWN_0;
  }
}

bool ScnObjIBL::isDisp() const { return unknown14 & FLAG_UNKNOWN_0; }

} // namespace ml
