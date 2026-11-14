#include "rcha/rcha_cam.h"

#include "ml/ml_mem.h"
#include "mm_math/mm_vec3.h"
#include "mtl/alloc_handle.h"
#include "rcha/rcha_anm.h"

RchaCam::RchaCam() : unknown19a0(false) {
  for (int i = 0; i < NAME_COUNT; i++) {
    unknown19a4[i] = -1;
  }
}

bool RchaCam::hasAnm(const void *data) {
  if (data == nullptr) {
    return false;
  }
  RchaCam anm;
  anm.setup(ml::MlMem::getDebugMem(), data);
  return anm.unknown19a0;
}

int RchaCam::getValueInt(int slot, f32 frame, int defaultValue) const {
  if (unknown19a4[slot] >= 0) {
    return unknown10[unknown19a4[slot]].getValueInt(frame);
  }
  return defaultValue;
}

f32 RchaCam::getValue(int slot, f32 frame, f32 defaultValue) const {
  if (unknown19a4[slot] >= 0) {
    return unknown10[unknown19a4[slot]].getValue(frame);
  }
  return defaultValue;
}

bool RchaCam::getPos(mm::Vec3 *pos, f32 frame) const {
  pos->x = getValue(CAM_UNKNOWN_0, frame, 0.0f);
  pos->y = getValue(CAM_UNKNOWN_1, frame, 0.0f);
  pos->z = getValue(CAM_UNKNOWN_2, frame, 0.0f);
  return true;
}

bool RchaCam::getRot(mm::Vec3 *rot, f32 frame) const {
  rot->x = getValue(CAM_UNKNOWN_3, frame, 0.0f);
  rot->y = getValue(CAM_UNKNOWN_4, frame, 0.0f);
  rot->z = getValue(CAM_UNKNOWN_5, frame, 0.0f);
  return true;
}

int RchaCam::getRotOrder(f32 frame) const { return getValueInt(CAM_UNKNOWN_6, frame, 0); }

f32 RchaCam::getFov(f32 frame) const { return getValue(CAMATR_UNKNOWN_9, frame, 30.0f); }

f32 RchaCam::getNear(f32 frame) const { return getValue(CAMATR_UNKNOWN_7, frame, 0.1f); }

f32 RchaCam::getFar(f32 frame) const { return getValue(CAMATR_UNKNOWN_8, frame, 80000.0f); }

f32 RchaCam::getMBlurStr(f32 frame) const { return getValue(CAMATR_UNKNOWN_20, frame, 0.5f); }

bool RchaCam::isEnableMBlur(f32 frame) const {
  if (unknown19a4[CAMATR_UNKNOWN_19] >= 0) {
    return unknown10[unknown19a4[CAMATR_UNKNOWN_19]].getValue(frame) > 0.9f;
  }
  return false;
}

f32 RchaCam::getMBlurSub(f32 frame) const { return getValue(CAMATR_UNKNOWN_21, frame, 0.1f); }

bool RchaCam::isEnableDOF(f32 frame) const {
  if (unknown19a4[CAMATR_UNKNOWN_10] >= 0) {
    return unknown10[unknown19a4[CAMATR_UNKNOWN_10]].getValue(frame) > 0.9f;
  }
  return false;
}

f32 RchaCam::getDistanceDOF(f32 frame) const { return getValue(CAMATR_UNKNOWN_11, frame, 20.0f); }

f32 RchaCam::getRangeDOF(f32 frame) const { return getValue(CAMATR_UNKNOWN_12, frame, 40.0f); }

f32 RchaCam::getPixelDOF(f32 frame) const { return getValue(CAMATR_UNKNOWN_13, frame, 5.0f); }

f32 RchaCam::getLensDOF(f32 frame) const { return getValue(CAMATR_UNKNOWN_14, frame, 0.6f); }

f32 RchaCam::getStrengthDOF(f32 frame) const { return getValue(CAMATR_UNKNOWN_15, frame, 4.0f); }

f32 RchaCam::getBlendDOF(f32 frame) const { return getValue(CAMATR_UNKNOWN_16, frame, 1.0f); }

int RchaCam::getPixelLvDOF(f32 frame) const { return getValueInt(CAMATR_UNKNOWN_17, frame, 0); }

bool RchaCam::isHlvDOF(f32 frame) const {
  if (unknown19a4[CAMATR_UNKNOWN_18] >= 0) {
    return unknown10[unknown19a4[CAMATR_UNKNOWN_18]].getValue(frame) > 0.9f;
  }
  return false;
}

bool RchaCam::isSMapVis(f32 frame) const {
  if (unknown19a4[CAMATR_UNKNOWN_22] >= 0) {
    return unknown10[unknown19a4[CAMATR_UNKNOWN_22]].getValue(frame) > 0.9f;
  }
  return true;
}

bool RchaCam::isEnableTime(f32 frame) const {
  if (unknown19a4[CAMATR_UNKNOWN_23] >= 0) {
    return unknown10[unknown19a4[CAMATR_UNKNOWN_23]].getValue(frame) > 0.9f;
  }
  return false;
}

f32 RchaCam::getTimeVal(f32 frame) const {
  f32 time = 0.0f;
  if (unknown19a4[CAMATR_UNKNOWN_24] >= 0) {
    time = unknown10[unknown19a4[CAMATR_UNKNOWN_24]].getValue(frame);
    if (time < 0.0f) {
      time = 0.0f;
    } else if (time > 23.999998f) {
      time = 23.999998f;
    }
  }
  return time;
}

bool RchaCam::isEnableWeather(f32 frame) const {
  if (unknown19a4[CAMATR_UNKNOWN_25] >= 0) {
    return unknown10[unknown19a4[CAMATR_UNKNOWN_25]].getValue(frame) > 0.9f;
  }
  return false;
}

bool RchaCam::isCamLgtStop(f32 frame) const {
  if (unknown19a4[CAMATR_UNKNOWN_28] >= 0) {
    return unknown10[unknown19a4[CAMATR_UNKNOWN_28]].getValue(frame) > 0.9f;
  }
  return false;
}

int RchaCam::getNearFarType(f32 frame) const { return getValueInt(CAMATR_UNKNOWN_29, frame, 0); }

int RchaCam::getWeatherType(f32 frame) const { return getValueInt(CAMATR_UNKNOWN_26, frame, 0); }

int RchaCam::getWeatherFrame(f32 frame) const { return getValueInt(CAMATR_UNKNOWN_27, frame, 0); }
