#include "event/chara_wink_player.h"

#include "event/chara_weight_item.h"
#include "event/chara_weight_player.h"
#include "event/curve.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "ml/rand.h"

namespace event {

CharaWinkPlayer::CharaWinkPlayer() : flags(), mWeight(nullptr), state(nullptr), mStatus("") {}

void CharaWinkPlayer::open(bool isDirect) {
  mWeight->easeOut(gf::ANIM_LAYER_EYE, "S_eye_close", isDirect ? 0.0f : 4.0f, CV_TYPE_LINEAR, WEIGHT_LAYER_WINK);
  mStatus = "open";
  state = nullptr;
}

void CharaWinkPlayer::idle(bool isDirect) {
  mWeight->easeOut(gf::ANIM_LAYER_EYE, "S_eye_close", isDirect ? 0.0f : 4.0f, CV_TYPE_LINEAR, WEIGHT_LAYER_WINK);
  mStatus = "open";
  state = &CharaWinkPlayer::idle_start;
}

void CharaWinkPlayer::idle_start() {
  mCounter = ml::mtRand(60) + 90;
  state = &CharaWinkPlayer::idle_waiting;
}

void CharaWinkPlayer::close(bool isDirect) {
  mWeight->easeIn(gf::ANIM_LAYER_EYE, "S_eye_close", isDirect ? 0.0f : 4.0f, 1.0f, 1.0f, CV_TYPE_LINEAR, WEIGHT_LAYER_WINK);
  mStatus = "close";
  state = nullptr;
}

void CharaWinkPlayer::idle_waiting() {
  if (flags.test(FLAG_DISABLE_IDLE)) {
    return;
  }
  if (mCounter-- > 0) {
    return;
  }
  mWeight->easeIn(gf::ANIM_LAYER_EYE, "S_eye_close", 4.0f, 1.0f, 1.0f, CV_TYPE_LINEAR, WEIGHT_LAYER_WINK);
  mStatus = "close";
  state = &CharaWinkPlayer::idle_wink;
  mCounter = 7;
}

} // namespace event
