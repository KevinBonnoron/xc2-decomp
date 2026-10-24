#include "event/bgm_manager.h"

#include "gf/game/event/gf_game_event.h"
#include "mm_math/mm_math.h"

namespace event {

BgmManager::BgmManager() : unknown10(0), unknown14(0), unknown7c(0.0f) {}

void BgmManager::setHandOver(bool isHandOver) { setFlag(FLAG_HAND_OVER, isHandOver); }

void BgmManager::changeVolume(f32 volume, f32 frame) {
  if ((unknown10 & FLAG_PLAY) == 0) {
    return;
  }
  mm::clampRef(volume, 0.0f, 1.0f);
  unknown5c = volume;
  gf::EventBgmSetup setup;
  setup.unknown48 = frame * TO_SEC;
  setup.unknown44 = volume;
  gf::GfGameEvent::changeVolume(setup);
}

f32 BgmManager::getStartedTotalFrame() const { return m_startedTotalFrame; }

void BgmManager::cancelOverTime() const {
  if ((unknown10 & FLAG_PLAY) != 0 && unknown74 != 0.0f) {
    gf::GfGameEvent::cancelOverTime();
  }
}

void BgmManager::setDisp(bool isDisp) {
  if (isDisp) {
    unknown14 |= DISP_FLAG_DISP;
  } else {
    unknown14 &= ~DISP_FLAG_DISP;
  }
}

bool BgmManager::isDisp() const { return (unknown14 & DISP_FLAG_DISP) != 0; }

} // namespace event
