#include "rcha/rcha_cam_eff.h"

#include "ml/ml_mem.h"
#include "mtl/alloc_handle.h"
#include "rcha/rcha_anm.h"

RchaCamEff::RchaCamEff() : unknown19a0(false) {
  for (int i = 0; i < NAME_COUNT; i++) {
    unknown19a4[i] = -1;
  }
}

bool RchaCamEff::hasAnm(const void *data) {
  if (data == nullptr) {
    return false;
  }
  RchaCamEff anm;
  anm.setup(ml::MlMem::getDebugMem(), data);
  return anm.unknown19a0;
}

int RchaCamEff::getValueInt(int slot, f32 frame, int defaultValue) const {
  if (unknown19a4[slot] >= 0) {
    return unknown10[unknown19a4[slot]].getValueInt(frame);
  }
  return defaultValue;
}

f32 RchaCamEff::getValue(int slot, f32 frame, f32 defaultValue) const {
  if (unknown19a4[slot] >= 0) {
    return unknown10[unknown19a4[slot]].getValue(frame);
  }
  return defaultValue;
}

bool RchaCamEff::isEnableColFilter(f32 frame) const {
  if (unknown19a4[CAMATR_COL_FILTER_UNKNOWN_0] >= 0) {
    return unknown10[unknown19a4[CAMATR_COL_FILTER_UNKNOWN_0]].getValue(frame) > 0.9f;
  }
  return false;
}

bool RchaCamEff::getColFilter(int &filter, f32 frame) const {
  int index = unknown19a4[CAMATR_COL_FILTER_UNKNOWN_0];
  if (index >= 0) {
    filter = unknown10[index].getValueInt(frame);
    return true;
  }
  return false;
}

int RchaCamEff::getNearColFilter(f32 frame) const { return getValueInt(CAMATR_COL_FILTER_UNKNOWN_1, frame, 0); }

int RchaCamEff::getFarColFilter(f32 frame) const { return getValueInt(CAMATR_COL_FILTER_UNKNOWN_2, frame, 0); }

f32 RchaCamEff::getFrColFilter(f32 frame) const { return getValue(CAMATR_COL_FILTER_UNKNOWN_3, frame, 0.0f); }
