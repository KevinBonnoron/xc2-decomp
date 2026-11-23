#include "event/chara_wink_player.h"

#include "event/chara_weight_item.h"
#include "event/chara_weight_player.h"
#include "event/curve.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "ml/rand.h"

namespace event {

CharaWinkPlayer::CharaWinkPlayer() : unknown08(), m_charaWeightPlayer(nullptr), unknown18(nullptr), unknown30("") {}

void CharaWinkPlayer::create(CharaWeightPlayer *weight) {
  unknown18 = nullptr;
  m_charaWeightPlayer = weight;
}

void CharaWinkPlayer::destroy() {
  unknown18 = nullptr;
  m_charaWeightPlayer = nullptr;
}

void CharaWinkPlayer::open(bool isDirect) {
  m_charaWeightPlayer->easeOut(gf::ANIM_LAYER_UNKNOWN_3, "S_eye_close", isDirect ? 0.0f : 4.0f, CV_TYPE_UNKNOWN_1, WEIGHT_LAYER_UNKNOWN_1);
  unknown30 = "open";
  unknown18 = nullptr;
}

void CharaWinkPlayer::idle(bool isDirect) {
  m_charaWeightPlayer->easeOut(gf::ANIM_LAYER_UNKNOWN_3, "S_eye_close", isDirect ? 0.0f : 4.0f, CV_TYPE_UNKNOWN_1, WEIGHT_LAYER_UNKNOWN_1);
  unknown30 = "open";
  unknown18 = &CharaWinkPlayer::idle_start;
}

void CharaWinkPlayer::idle_start() {
  unknown28 = ml::mtRand(60) + 90;
  unknown18 = &CharaWinkPlayer::idle_waiting;
}

void CharaWinkPlayer::close(bool isDirect) {
  m_charaWeightPlayer->easeIn(gf::ANIM_LAYER_UNKNOWN_3, "S_eye_close", isDirect ? 0.0f : 4.0f, 1.0f, 1.0f, CV_TYPE_UNKNOWN_1, WEIGHT_LAYER_UNKNOWN_1);
  unknown30 = "close";
  unknown18 = nullptr;
}

void CharaWinkPlayer::idle_waiting() {
  if (unknown08.test(FLAG_UNKNOWN_0)) {
    return;
  }
  if (unknown28-- > 0) {
    return;
  }
  m_charaWeightPlayer->easeIn(gf::ANIM_LAYER_UNKNOWN_3, "S_eye_close", 4.0f, 1.0f, 1.0f, CV_TYPE_UNKNOWN_1, WEIGHT_LAYER_UNKNOWN_1);
  unknown30 = "close";
  unknown18 = &CharaWinkPlayer::idle_wink;
  unknown28 = 7;
}

void CharaWinkPlayer::idle_wink() {
  if (unknown28-- > 0)
    return;
  m_charaWeightPlayer->easeOut(gf::ANIM_LAYER_UNKNOWN_3, "S_eye_close", 4.0f, CV_TYPE_UNKNOWN_1, WEIGHT_LAYER_UNKNOWN_1);
  unknown30 = "open";
  unknown18 = &CharaWinkPlayer::idle_start;
}

} // namespace event
