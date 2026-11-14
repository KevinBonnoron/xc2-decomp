#include "rcha/rcha_chr_eff.h"

#include "ml/ml_mem.h"
#include "mm_math/mm_vec3.h"
#include "mtl/alloc_handle.h"
#include "rcha/rcha_anm.h"

RchaChrEff::RchaChrEff() : unknown19a0(false) {
  for (int i = 0; i < NAME_COUNT; i++) {
    unknown19a4[i] = -1;
  }
}

bool RchaChrEff::hasAnm(const void *data) {
  if (data == nullptr) {
    return false;
  }
  RchaChrEff anm;
  anm.setup(ml::MlMem::getDebugMem(), data);
  return anm.unknown19a0;
}

bool RchaChrEff::getVolumeFade(int &type, f32 frame) const { return unknown001(type, CHREFF_UNKNOWN_0, frame); }

int RchaChrEff::getValueInt(int slot, f32 frame, int defaultValue) const {
  if (unknown19a4[slot] >= 0) {
    return unknown10[unknown19a4[slot]].getValueInt(frame);
  }
  return defaultValue;
}

bool RchaChrEff::getVolumeFadeId(int &id, f32 frame) const { return unknown001(id, CHREFF_UNKNOWN_1, frame); }

void RchaChrEff::getVolumeFadeUVWScale(mm::Vec3 &scale, f32 frame) const {
  scale.x = getValue(CHREFF_UNKNOWN_2, frame, 0.0f);
  scale.y = getValue(CHREFF_UNKNOWN_3, frame, 0.0f);
  scale.z = getValue(CHREFF_UNKNOWN_4, frame, 0.0f);
}

f32 RchaChrEff::getValue(int slot, f32 frame, f32 defaultValue) const {
  if (unknown19a4[slot] >= 0) {
    return unknown10[unknown19a4[slot]].getValue(frame);
  }
  return defaultValue;
}

void RchaChrEff::getVolumeFadeCenterPos(mm::Vec3 &pos, f32 frame) const {
  pos.x = getValue(CHREFF_UNKNOWN_5, frame, 0.0f);
  pos.y = getValue(CHREFF_UNKNOWN_6, frame, 0.0f);
  pos.z = getValue(CHREFF_UNKNOWN_7, frame, 0.0f);
}

bool RchaChrEff::getVolumeFadeDistance(f32 &distance, f32 frame) const { return unknown002(distance, CHREFF_UNKNOWN_8, frame); }

bool RchaChrEff::getVolumeFadeDirectivity(f32 &directivity, f32 frame) const { return unknown002(directivity, CHREFF_UNKNOWN_9, frame); }

bool RchaChrEff::getVolumeFadeMesh(int &mesh, f32 frame) const { return unknown001(mesh, CHREFF_UNKNOWN_10, frame); }

bool RchaChrEff::getVolumeFadeRatio(f32 &ratio, f32 frame) const { return unknown002(ratio, CHREFF_UNKNOWN_11, frame); }

bool RchaChrEff::getRimBloom(int &type, f32 frame) const { return unknown001(type, CHREFF_UNKNOWN_12, frame); }

bool RchaChrEff::getRimBloomId(int &id, f32 frame) const { return unknown001(id, CHREFF_UNKNOWN_13, frame); }

bool RchaChrEff::getAfterImage(int &type, f32 frame) const { return unknown001(type, CHREFF_UNKNOWN_14, frame); }

bool RchaChrEff::getAfterImageId1(int &id, f32 frame) const { return unknown001(id, CHREFF_UNKNOWN_15, frame); }

bool RchaChrEff::getAfterImageId2(int &id, f32 frame) const { return unknown001(id, CHREFF_UNKNOWN_16, frame); }

bool RchaChrEff::getAfterImageCaptureFrame(f32 &captureFrame, f32 frame) const { return unknown002(captureFrame, CHREFF_UNKNOWN_17, frame); }

bool RchaChrEff::getAfterImageExistFrame(f32 &existFrame, f32 frame) const { return unknown002(existFrame, CHREFF_UNKNOWN_18, frame); }

bool RchaChrEff::getAfterImageFadeOutFrame(f32 &fadeOutFrame, f32 frame) const { return unknown002(fadeOutFrame, CHREFF_UNKNOWN_19, frame); }

void RchaChrEff::clear() {
  RchaNode::clear();
  unknown19a0 = false;
}
