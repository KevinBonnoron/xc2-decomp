#include "event/bgm_manager.h"

#include "gf/game/event/gf_game_event.h"
#include "mm_math/mm_math.h"

namespace event {

BgmManager::BgmManager() : flags(0), dispFlags(0), mPlayFrame(0.0f) {}

void BgmManager::setHandOver(bool isHandOver) { setFlag(FLAG_HAND_OVER, isHandOver); }

void BgmManager::changeVolume(f32 volume, f32 frame) {
  if ((flags & FLAG_PLAY) == 0) {
    return;
  }
  mm::clampRef(volume, 0.0f, 1.0f);
  mVolume = volume;
  gf::EventBgmSetup setup;
  setup.volumeSec = frame * TO_SEC;
  setup.volume = volume;
  gf::GfGameEvent::changeVolume(setup);
}

f32 BgmManager::getStartedTotalFrame() const { return mStartedTotalFrame; }

void BgmManager::cancelOverTime() const {
  if ((flags & FLAG_PLAY) != 0 && mOverTimeFrame != 0.0f) {
    gf::GfGameEvent::cancelOverTime();
  }
}

void BgmManager::setDisp(bool isDisp) {
  if (isDisp) {
    dispFlags |= DISP_FLAG_DISP;
  } else {
    dispFlags &= ~DISP_FLAG_DISP;
  }
}

bool BgmManager::isDisp() const { return (dispFlags & DISP_FLAG_DISP) != 0; }

} // namespace event
