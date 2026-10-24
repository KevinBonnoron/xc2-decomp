#include "event/chara_lens_player.h"

namespace event {

f32 CharaLensPlayer::MILD = 0.35f;

// The constructor at 0x71000babb8 clears +0x8 and +0x40, and copies
// mm::Vec2::zero into +0x10, +0x20, and +0x30.
CharaLensPlayer::CharaLensPlayer() : unknown08() {
  f32 x = mm::Vec2::zero.x;
  f32 y = mm::Vec2::zero.y;
  m_target.x = x;
  m_target.y = y;
  unknown20.x = x;
  unknown20.y = y;
  unknown30.x = x;
  unknown30.y = y;
  unknown40 = nullptr;
}

void CharaLensPlayer::create(CharaIKUpdater *ik) { unknown40 = ik; }

void CharaLensPlayer::destroy() { unknown40 = nullptr; }

void CharaLensPlayer::setManualTarget(bool isManual, const mm::Vec2 &target, bool isDirect) {
  if (isManual) {
    unknown08.set(FLAG_MANUAL, true);
    unknown20 = target;
  } else {
    unknown08.set(FLAG_MANUAL, false);
    unknown20 = mm::Vec2::zero;
  }
  unknown08.set(FLAG_DIRECT, isDirect);
}

void CharaLensPlayer::setAutoTarget(const mm::Vec2 &target, bool isDirect) {
  unknown30 = target;
  unknown08.set(FLAG_DIRECT, isDirect);
}

const mm::Vec2 &CharaLensPlayer::getTarget() const { return m_target; }

} // namespace event
