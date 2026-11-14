#include "rcha/rcha_eff.h"

#include "ml/ml_mem.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_vec3.h"
#include "mtl/alloc_handle.h"
#include "rcha/rcha_anm.h"

RchaEff::RchaEff() : unknown19a0(false) {
  for (int i = 0; i < NAME_COUNT; i++) {
    unknown19a4[i] = -1;
  }
}

bool RchaEff::hasAnm(const void *data) {
  if (data == nullptr) {
    return false;
  }
  RchaEff anm;
  anm.setup(ml::MlMem::getDebugMem(), data);
  return anm.unknown19a0;
}

void RchaEff::clear() { RchaNode::clear(); }

int RchaEff::getValueInt(int slot, f32 frame, int defaultValue) const {
  if (unknown19a4[slot] >= 0) {
    return unknown10[unknown19a4[slot]].getValueInt(frame);
  }
  return defaultValue;
}

f32 RchaEff::getValue(int slot, f32 frame, f32 defaultValue) const {
  if (unknown19a4[slot] >= 0) {
    return unknown10[unknown19a4[slot]].getValue(frame);
  }
  return defaultValue;
}

bool RchaEff::getPos(mm::Vec3 &pos, f32 frame) const {
  pos.x = getValue(EFF_UNKNOWN_0, frame, 0.0f);
  pos.y = getValue(EFF_UNKNOWN_1, frame, 0.0f);
  pos.z = getValue(EFF_UNKNOWN_2, frame, 0.0f);
  return true;
}

bool RchaEff::getRot(mm::Vec3 &rot, f32 frame) const {
  rot.x = getValue(EFF_UNKNOWN_3, frame, 0.0f);
  rot.y = getValue(EFF_UNKNOWN_4, frame, 0.0f);
  rot.z = getValue(EFF_UNKNOWN_5, frame, 0.0f);
  return true;
}

bool RchaEff::getScl(mm::Vec3 &scale, f32 frame) const {
  scale.x = getValue(EFF_UNKNOWN_6, frame, 0.0f);
  scale.y = getValue(EFF_UNKNOWN_7, frame, 0.0f);
  scale.z = getValue(EFF_UNKNOWN_8, frame, 0.0f);
  return true;
}

bool RchaEff::getProgress(int &current, int &total, f32 frame) const {
  current = getValue(EFFATR_UNKNOWN_15, frame, 0.0f);
  total = getValue(EFFATR_UNKNOWN_16, frame, 0.0f);
  return true;
}

bool RchaEff::getCol(mm::Col4 &color, f32 frame) const {
  color.r = getValue(EFFATR_UNKNOWN_12, frame, 0.0f);
  color.g = getValue(EFFATR_UNKNOWN_13, frame, 0.0f);
  color.b = getValue(EFFATR_UNKNOWN_14, frame, 0.0f);
  color.a = getValue(EFFATR_UNKNOWN_11, frame, 0.0f);
  return true;
}

bool RchaEff::isGenelate(f32 frame) const {
  if (unknown19a4[EFFATR_UNKNOWN_10] >= 0) {
    return unknown10[unknown19a4[EFFATR_UNKNOWN_10]].getValue(frame) > 0.8f;
  }
  return false;
}

bool RchaEff::isEnd(f32 frame) const {
  if (unknown19a4[EFFATR_UNKNOWN_18] >= 0) {
    return unknown10[unknown19a4[EFFATR_UNKNOWN_18]].getValue(frame) > 0.8f;
  }
  return false;
}

bool RchaEff::isKill(f32 frame) const {
  if (unknown19a4[EFFATR_UNKNOWN_19] >= 0) {
    return unknown10[unknown19a4[EFFATR_UNKNOWN_19]].getValue(frame) > 0.8f;
  }
  return false;
}

bool RchaEff::getSpeed(f32 &speed, f32 frame) const {
  speed = getValue(EFFATR_UNKNOWN_9, frame, 0.0f);
  return true;
}
