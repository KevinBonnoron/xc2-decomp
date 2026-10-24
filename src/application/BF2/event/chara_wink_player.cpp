#include "event/chara_wink_player.h"

#include "event/chara_weight_item.h"
#include "event/chara_weight_player.h"
#include "event/curve.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "ml/rand.h"

namespace event {

CharaWinkPlayer::CharaWinkPlayer() : unknown08(), unknown10(nullptr), unknown18(nullptr), unknown30("") {}

void CharaWinkPlayer::create(CharaWeightPlayer *weight) {
  unknown18 = nullptr;
  unknown10 = weight;
}

void CharaWinkPlayer::destroy() {
  unknown18 = nullptr;
  unknown10 = nullptr;
}

void CharaWinkPlayer::open(bool isDirect) {
  unknown10->easeOut(gf::ANIM_LAYER_EYE, "S_eye_close", isDirect ? 0.0f : 4.0f, CV_TYPE_LINEAR, WEIGHT_LAYER_WINK);
  unknown30 = "open";
  unknown18 = nullptr;
}

void CharaWinkPlayer::idle(bool isDirect) {
  unknown10->easeOut(gf::ANIM_LAYER_EYE, "S_eye_close", isDirect ? 0.0f : 4.0f, CV_TYPE_LINEAR, WEIGHT_LAYER_WINK);
  unknown30 = "open";
  unknown18 = &CharaWinkPlayer::idle_start;
}

void CharaWinkPlayer::idle_start() {
  unknown28 = ml::mtRand(60) + 90;
  unknown18 = &CharaWinkPlayer::idle_waiting;
}

void CharaWinkPlayer::close(bool isDirect) {
  unknown10->easeIn(gf::ANIM_LAYER_EYE, "S_eye_close", isDirect ? 0.0f : 4.0f, 1.0f, 1.0f, CV_TYPE_LINEAR, WEIGHT_LAYER_WINK);
  unknown30 = "close";
  unknown18 = nullptr;
}

void CharaWinkPlayer::idle_waiting() {
  if (unknown08.test(FLAG_DISABLE_IDLE)) {
    return;
  }
  if (unknown28-- > 0) {
    return;
  }
  unknown10->easeIn(gf::ANIM_LAYER_EYE, "S_eye_close", 4.0f, 1.0f, 1.0f, CV_TYPE_LINEAR, WEIGHT_LAYER_WINK);
  unknown30 = "close";
  unknown18 = &CharaWinkPlayer::idle_wink;
  unknown28 = 7;
}

void CharaWinkPlayer::idle_wink() {
  if (unknown28-- > 0)
    return;
  unknown10->easeOut(gf::ANIM_LAYER_EYE, "S_eye_close", 4.0f, CV_TYPE_LINEAR, WEIGHT_LAYER_WINK);
  unknown30 = "open";
  unknown18 = &CharaWinkPlayer::idle_start;
}

} // namespace event
