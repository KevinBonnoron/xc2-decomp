#include "event/chara_lens_player.h"

namespace event {

f32 CharaLensPlayer::MILD = 0.35f;

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
