#include "event/chara_lens_player.h"

namespace event {

f32 CharaLensPlayer::MILD = 0.35f;

// The constructor at 0x71000babb8 clears +0x8 and +0x40, and copies
// mm::Vec2::zero into +0x10, +0x20, and +0x30.
CharaLensPlayer::CharaLensPlayer() : flags() {
  f32 x = mm::Vec2::zero.x;
  f32 y = mm::Vec2::zero.y;
  mTarget.x = x;
  mTarget.y = y;
  mManualTarget.x = x;
  mManualTarget.y = y;
  mAutoTarget.x = x;
  mAutoTarget.y = y;
  mIK = nullptr;
}

void CharaLensPlayer::create(CharaIKUpdater *ik) { mIK = ik; }

void CharaLensPlayer::destroy() { mIK = nullptr; }

void CharaLensPlayer::setManualTarget(bool isManual, const mm::Vec2 &target, bool isDirect) {
  if (isManual) {
    flags.set(FLAG_MANUAL, true);
    mManualTarget = target;
  } else {
    flags.set(FLAG_MANUAL, false);
    mManualTarget = mm::Vec2::zero;
  }
  flags.set(FLAG_DIRECT, isDirect);
}

void CharaLensPlayer::setAutoTarget(const mm::Vec2 &target, bool isDirect) {
  mAutoTarget = target;
  flags.set(FLAG_DIRECT, isDirect);
}

const mm::Vec2 &CharaLensPlayer::getTarget() const { return mTarget; }

} // namespace event
