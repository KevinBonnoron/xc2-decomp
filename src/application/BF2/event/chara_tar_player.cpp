#include "event/chara_tar_player.h"

#include "event/chara_ik_updater.h"
#include "event/chara_tar_util.h"
#include "event/chara_weight_item.h"
#include "event/chara_weight_player.h"
#include "event/curve.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/gf_obj_handle.h"

namespace event {

CharaTarPlayer::CharaTarPlayer() : unknown08(gf::unknown020), unknown10(nullptr), unknown18(0) {}

void CharaTarPlayer::create(gf::GF_OBJ_HANDLE *handle, CharaIKUpdater *ik) {
  this->unknown08 = handle;
  this->unknown10 = ik;
  unknown90 = mm::Vec3::zero;
  unknowna0 = mm::Vec3::zero;
  unknownb0 = mm::Vec3::zero;
  unknownc0.clear();
}

void CharaTarPlayer::destroy() {
  update(1.0f);
  unknown10 = nullptr;
}

void CharaTarPlayer::update(f32 delta) {
  if (unknown10 == nullptr) {
    return;
  }
  unknown90 = unknownb0;
  while (!unknown20.empty()) {
    Request &request = unknown20[0];
    switch (request.unknown00) {
    case TYPE_UNKNOWN_1:
      if (request.unknown09) {
        unknown10->setTargetIK(true, request.unknown04, request.unknown08);
        unknown18 |= FLAG_UNKNOWN_0;
      }
      request.unknown09 = false;
      break;
    case TYPE_UNKNOWN_2:
      if (request.unknown09) {
        unknown10->setTargetIK(false, request.unknown04, false);
        unknown18 &= ~FLAG_UNKNOWN_0;
      }
      request.unknown09 = false;
      break;
    case TYPE_UNKNOWN_3: {
      mm::Vec3 eyePos = CharaTarUtil::getCharaEyePos(unknown08);
      f32 eyeRotY = CharaTarUtil::getCharaEyeRotY(unknown08);
      unknownc0.update(delta);
      if (unknownc0.isEnd()) {
        unknownc0.clear();
      }
      if (unknownc0.isPlay()) {
        unknown90 = CharaTarUtil::calcTarget(unknowna0, unknownb0, unknownc0.getValue(), eyePos, eyeRotY);
      }
      if (unknownc0.isEnd()) {
        unknownc0.clear();
      }
      request.unknown09 = false;
      break;
    }
    default:
      break;
    }
    request.unknown0c -= delta;
    if (request.unknown0c < 0.0f) {
      unknown20.erase(unknown20.begin());
    } else {
      break;
    }
  }
  if ((unknown18 & FLAG_UNKNOWN_0) != 0) {
    unknown10->setTargetPos(unknown90);
  }
}

void CharaTarPlayer::setTargetPos(const mm::Vec3 &position) { unknownb0 = position; }

CharaTarPlayerMot::CharaTarPlayerMot() : unknown08(gf::unknown020), unknown10(nullptr), unknown18(0), unknown1c(REQUEST_UNKNOWN_0), unknown20(0.0f), unknown24(false), unknown280() {}

void CharaTarPlayerMot::create(gf::GF_OBJ_HANDLE *handle, CharaWeightPlayer *weight) {
  this->unknown08 = handle;
  this->unknown10 = weight;
  unknown30 = mm::Vec3::zero;
  unknown40 = mm::Vec3::zero;
  unknown50 = mm::Vec3::zero;
  unknown60.clear();
  unknown60.append(0.0f, 1.0f, CV_TYPE_UNKNOWN_2);
  unknown170.clear();
  unknown170.append(0.0f, 1.0f, CV_TYPE_UNKNOWN_2);
  for (u32 i = 0; i < AIMMOT_UNKNOWN_6; i++) {
    unknown280[i] = 0.0f;
  }
}

void CharaTarPlayerMot::destroy() {
  update(1.0f);
  unknown10 = nullptr;
}

void CharaTarPlayerMot::update(f32 delta) {
  if (unknown10 == nullptr) {
    return;
  }
  if (unknown1c != REQUEST_UNKNOWN_0) {
    switch (unknown1c) {
    case REQUEST_UNKNOWN_1:
      unknown60.clear();
      if (unknown20 > 0.0f) {
        unknown60.append(0.0f, 0.0f, CV_TYPE_UNKNOWN_2);
      }
      unknown60.append(unknown20, 1.0f, CV_TYPE_UNKNOWN_2);
      unknown170.clear();
      unknown170.append(0.0f, 1.0f, CV_TYPE_UNKNOWN_2);
      unknown40 = unknown30;
      unknown18 |= FLAG_UNKNOWN_0;
      setFlag(FLAG_UNKNOWN_1, unknown24);
      break;
    case REQUEST_UNKNOWN_2:
      unknown170.clear();
      if (unknown20 > 0.0f) {
        unknown170.append(0.0f, 0.0f, CV_TYPE_UNKNOWN_2);
      }
      unknown170.append(unknown20, 1.0f, CV_TYPE_UNKNOWN_2);
      unknown40 = unknown30;
      setFlag(FLAG_UNKNOWN_1, unknown24);
      break;
    case REQUEST_UNKNOWN_3:
      for (u32 i = 0; i < AIMMOT_UNKNOWN_6; i++) {
        unknown10->easeOut(gf::ANIM_LAYER_UNKNOWN_2, CharaTarUtil::aimmotType2stat(i), unknown20, CV_TYPE_UNKNOWN_2, WEIGHT_LAYER_UNKNOWN_0);
      }
      for (u32 i = 0; i < AIMMOT_UNKNOWN_6; i++) {
        unknown280[i] = 0.0f;
      }
      unknown18 &= ~FLAG_UNKNOWN_0;
      break;
    default:
      break;
    }
    unknown1c = REQUEST_UNKNOWN_0;
  }
  unknown60.update(delta);
  unknown170.update(delta);
  if ((unknown18 & FLAG_UNKNOWN_0) == 0) {
    return;
  }
  f32 prevWeights[AIMMOT_UNKNOWN_6];
  for (u32 i = 0; i < AIMMOT_UNKNOWN_6; i++) {
    prevWeights[i] = unknown280[i];
  }
  mm::Vec3 eyePos = CharaTarUtil::getCharaEyePos(unknown08);
  f32 eyeRotY = CharaTarUtil::getCharaEyeRotY(unknown08);
  unknown30 = unknown50;
  if (unknown170.isPlay()) {
    unknown30 = CharaTarUtil::calcTarget(unknown40, unknown50, unknown170.getValue(), eyePos, eyeRotY);
  }
  mm::Vec3 aim = CharaTarUtil::calcWeight(unknown30, eyePos, eyeRotY);
  aim *= unknown60.getValue();
  unknown280[0] = aim.y > 0.0f ? ((unknown18 & FLAG_UNKNOWN_1) != 0 ? 0.0f : aim.y) : 0.0f;
  unknown280[1] = aim.y < 0.0f ? ((unknown18 & FLAG_UNKNOWN_1) != 0 ? 0.0f : -aim.y) : 0.0f;
  unknown280[2] = aim.y > 0.0f ? ((unknown18 & FLAG_UNKNOWN_1) != 0 ? aim.y : 0.0f) : 0.0f;
  unknown280[3] = aim.y < 0.0f ? ((unknown18 & FLAG_UNKNOWN_1) != 0 ? -aim.y : 0.0f) : 0.0f;
  unknown280[4] = aim.x < 0.0f ? -aim.x : 0.0f;
  unknown280[5] = aim.x > 0.0f ? aim.x : 0.0f;
  for (u32 i = 0; i < AIMMOT_UNKNOWN_6; i++) {
    if (prevWeights[i] == unknown280[i]) {
      continue;
    }
    const char *stat = CharaTarUtil::aimmotType2stat(i);
    if (prevWeights[i] > 0.0f && unknown280[i] <= 0.0f) {
      unknown10->easeOut(gf::ANIM_LAYER_UNKNOWN_2, stat, 0.0f, CV_TYPE_UNKNOWN_2, WEIGHT_LAYER_UNKNOWN_0);
    }
    if (prevWeights[i] <= 0.0f && unknown280[i] > 0.0f) {
      unknown10->easeIn(gf::ANIM_LAYER_UNKNOWN_2, stat, 0.0f, 1.0f, 1.0f, CV_TYPE_UNKNOWN_2, WEIGHT_LAYER_UNKNOWN_0);
    }
    if (unknown280[i] > 0.0f) {
      unknown10->setAddWeight(stat, unknown280[i], WEIGHT_LAYER_UNKNOWN_0);
    }
  }
}

void CharaTarPlayerMot::setEnable(bool isEnable, f32 frame, bool isNoSpine) {
  if (isEnable) {
    if ((unknown18 & FLAG_UNKNOWN_0) != 0) {
      unknown1c = REQUEST_UNKNOWN_2;
      unknown20 = frame;
      this->unknown24 = isNoSpine;
    } else {
      unknown1c = REQUEST_UNKNOWN_1;
      unknown20 = frame;
      this->unknown24 = isNoSpine;
    }
  } else {
    unknown1c = REQUEST_UNKNOWN_3;
    unknown20 = frame;
  }
}

void CharaTarPlayerMot::setTargetPos(const mm::Vec3 &position) { unknown50 = position; }

} // namespace event
