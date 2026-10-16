#include "event/chara_tar_player.h"

#include "event/chara_ik_updater.h"
#include "event/chara_tar_util.h"
#include "event/chara_weight_item.h"
#include "event/chara_weight_player.h"
#include "event/curve.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/gf_obj_handle.h"

namespace event {

CharaTarPlayer::CharaTarPlayer() : handle(gf::INVALID_HANDLE), ik(nullptr), flags(0) {}

void CharaTarPlayer::create(gf::GF_OBJ_HANDLE *handle, CharaIKUpdater *ik) {
  this->handle = handle;
  this->ik = ik;
  tar = mm::Vec3::zero;
  startTar = mm::Vec3::zero;
  targetPos = mm::Vec3::zero;
  moveAnm.clear();
}

void CharaTarPlayer::destroy() {
  update(1.0f);
  ik = nullptr;
}

void CharaTarPlayer::update(f32 delta) {
  if (ik == nullptr) {
    return;
  }
  tar = targetPos;
  while (!requests.empty()) {
    Request &request = requests[0];
    switch (request.type) {
    case TYPE_ENABLE:
      if (request.isFirst) {
        ik->setTargetIK(true, request.frame, request.isNoSpine);
        flags |= FLAG_ENABLE;
      }
      request.isFirst = false;
      break;
    case TYPE_DISABLE:
      if (request.isFirst) {
        ik->setTargetIK(false, request.frame, false);
        flags &= ~FLAG_ENABLE;
      }
      request.isFirst = false;
      break;
    case TYPE_MOVE: {
      mm::Vec3 eyePos = CharaTarUtil::getCharaEyePos(handle);
      f32 eyeRotY = CharaTarUtil::getCharaEyeRotY(handle);
      moveAnm.update(delta);
      if (moveAnm.isEnd()) {
        moveAnm.clear();
      }
      if (moveAnm.isPlay()) {
        tar = CharaTarUtil::calcTarget(startTar, targetPos, moveAnm.getValue(), eyePos, eyeRotY);
      }
      if (moveAnm.isEnd()) {
        moveAnm.clear();
      }
      request.isFirst = false;
      break;
    }
    default:
      break;
    }
    request.remainFrame -= delta;
    if (request.remainFrame < 0.0f) {
      requests.erase(requests.begin());
    } else {
      break;
    }
  }
  if ((flags & FLAG_ENABLE) != 0) {
    ik->setTargetPos(tar);
  }
}

void CharaTarPlayer::setTargetPos(const mm::Vec3 &position) { targetPos = position; }

CharaTarPlayerMot::CharaTarPlayerMot()
    : handle(gf::INVALID_HANDLE), weight(nullptr), flags(0), request(REQUEST_NONE), requestFrame(0.0f), isNoSpine(false), aimmotWeights() {}

void CharaTarPlayerMot::create(gf::GF_OBJ_HANDLE *handle, CharaWeightPlayer *weight) {
  this->handle = handle;
  this->weight = weight;
  tar = mm::Vec3::zero;
  startTar = mm::Vec3::zero;
  targetPos = mm::Vec3::zero;
  weightAnm.clear();
  weightAnm.append(0.0f, 1.0f, CV_TYPE_EASE_IN_OUT);
  moveAnm.clear();
  moveAnm.append(0.0f, 1.0f, CV_TYPE_EASE_IN_OUT);
  for (u32 i = 0; i < AIMMOT_COUNT; i++) {
    aimmotWeights[i] = 0.0f;
  }
}

void CharaTarPlayerMot::destroy() {
  update(1.0f);
  weight = nullptr;
}

void CharaTarPlayerMot::update(f32 delta) {
  if (weight == nullptr) {
    return;
  }
  if (request != REQUEST_NONE) {
    switch (request) {
    case REQUEST_ENABLE:
      weightAnm.clear();
      if (requestFrame > 0.0f) {
        weightAnm.append(0.0f, 0.0f, CV_TYPE_EASE_IN_OUT);
      }
      weightAnm.append(requestFrame, 1.0f, CV_TYPE_EASE_IN_OUT);
      moveAnm.clear();
      moveAnm.append(0.0f, 1.0f, CV_TYPE_EASE_IN_OUT);
      startTar = tar;
      flags |= FLAG_ENABLE;
      setFlag(FLAG_NO_SPINE, isNoSpine);
      break;
    case REQUEST_MOVE:
      moveAnm.clear();
      if (requestFrame > 0.0f) {
        moveAnm.append(0.0f, 0.0f, CV_TYPE_EASE_IN_OUT);
      }
      moveAnm.append(requestFrame, 1.0f, CV_TYPE_EASE_IN_OUT);
      startTar = tar;
      setFlag(FLAG_NO_SPINE, isNoSpine);
      break;
    case REQUEST_DISABLE:
      for (u32 i = 0; i < AIMMOT_COUNT; i++) {
        weight->easeOut(gf::ANIM_LAYER_HEAD, CharaTarUtil::aimmotType2stat(i), requestFrame, CV_TYPE_EASE_IN_OUT, WEIGHT_LAYER_PLAY);
      }
      for (u32 i = 0; i < AIMMOT_COUNT; i++) {
        aimmotWeights[i] = 0.0f;
      }
      flags &= ~FLAG_ENABLE;
      break;
    default:
      break;
    }
    request = REQUEST_NONE;
  }
  weightAnm.update(delta);
  moveAnm.update(delta);
  if ((flags & FLAG_ENABLE) == 0) {
    return;
  }
  f32 prevWeights[AIMMOT_COUNT];
  for (u32 i = 0; i < AIMMOT_COUNT; i++) {
    prevWeights[i] = aimmotWeights[i];
  }
  mm::Vec3 eyePos = CharaTarUtil::getCharaEyePos(handle);
  f32 eyeRotY = CharaTarUtil::getCharaEyeRotY(handle);
  tar = targetPos;
  if (moveAnm.isPlay()) {
    tar = CharaTarUtil::calcTarget(startTar, targetPos, moveAnm.getValue(), eyePos, eyeRotY);
  }
  mm::Vec3 aim = CharaTarUtil::calcWeight(tar, eyePos, eyeRotY);
  aim *= weightAnm.getValue();
  aimmotWeights[0] = aim.y > 0.0f ? ((flags & FLAG_NO_SPINE) != 0 ? 0.0f : aim.y) : 0.0f;
  aimmotWeights[1] = aim.y < 0.0f ? ((flags & FLAG_NO_SPINE) != 0 ? 0.0f : -aim.y) : 0.0f;
  aimmotWeights[2] = aim.y > 0.0f ? ((flags & FLAG_NO_SPINE) != 0 ? aim.y : 0.0f) : 0.0f;
  aimmotWeights[3] = aim.y < 0.0f ? ((flags & FLAG_NO_SPINE) != 0 ? -aim.y : 0.0f) : 0.0f;
  aimmotWeights[4] = aim.x < 0.0f ? -aim.x : 0.0f;
  aimmotWeights[5] = aim.x > 0.0f ? aim.x : 0.0f;
  for (u32 i = 0; i < AIMMOT_COUNT; i++) {
    if (prevWeights[i] == aimmotWeights[i]) {
      continue;
    }
    const char *stat = CharaTarUtil::aimmotType2stat(i);
    if (prevWeights[i] > 0.0f && aimmotWeights[i] <= 0.0f) {
      weight->easeOut(gf::ANIM_LAYER_HEAD, stat, 0.0f, CV_TYPE_EASE_IN_OUT, WEIGHT_LAYER_PLAY);
    }
    if (prevWeights[i] <= 0.0f && aimmotWeights[i] > 0.0f) {
      weight->easeIn(gf::ANIM_LAYER_HEAD, stat, 0.0f, 1.0f, 1.0f, CV_TYPE_EASE_IN_OUT, WEIGHT_LAYER_PLAY);
    }
    if (aimmotWeights[i] > 0.0f) {
      weight->setAddWeight(stat, aimmotWeights[i], WEIGHT_LAYER_PLAY);
    }
  }
}

void CharaTarPlayerMot::setEnable(bool isEnable, f32 frame, bool isNoSpine) {
  if (isEnable) {
    if ((flags & FLAG_ENABLE) != 0) {
      request = REQUEST_MOVE;
      requestFrame = frame;
      this->isNoSpine = isNoSpine;
    } else {
      request = REQUEST_ENABLE;
      requestFrame = frame;
    }
  } else {
    request = REQUEST_DISABLE;
    requestFrame = frame;
  }
}

void CharaTarPlayerMot::setTargetPos(const mm::Vec3 &position) { targetPos = position; }

} // namespace event
