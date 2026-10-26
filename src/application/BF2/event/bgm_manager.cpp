#include "event/bgm_manager.h"

#include "event/extend.h"
#include "event/frame_manager.h"
#include "event/skip_manager.h"
#include "fw/fw_debug.h"
#include "gf/game/event/gf_game_event.h"
#include "ml/rand.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_rect.h"

namespace event {

const s32 BgmManager::unknown001[7] = {15, 20, 23, 25, 23, 20, 15};

BgmManager::BgmManager() : unknown10(0), unknown14(0), unknown7c(0.0f) {}

void BgmManager::render() {
  if (!(unknown14 & DISP_FLAG_DISP) || !(unknown10 & FLAG_PLAY)) {
    return;
  }
  fw::debug::drawCompareZ(false);
  fw::debug::drawSquare2D(mm::Rect<s32>(20, 560, 350, 60), mm::Col4(0.0f, 0.0f, 0.0f, 0.25f));
  fw::debug::drawLineSquare2D(mm::Rect<s32>(20, 560, 350, 60), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFont(25, 565, mm::Col4::white, "BGM");
  if (!(unknown10 & FLAG_DELAY)) {
    if (mm::mtl::Singleton<FrameManager>::getPtr()->isPause(FrameManager::PAUSE_TYPE_ALL)) {
      ml::mtInit(0);
    }
    for (s32 i = 0; i < 7; i++) {
      fw::debug::drawSquare2D(mm::Rect<s32>(30 + i * 5, 610, 5, -unknown001[i] - ml::mtRand(5)), mm::Col4(1.0f, 0.5f, 0.5f, 1.0f));
    }
  }
  if (!(unknown10 & FLAG_DELAY)) {
    fw::debug::drawFont(70, 580, "  %s", mm::mtl::Singleton<Extend>::getPtr()->filename(unknown18.c_str()));
  } else {
    fw::debug::drawFont(70, 580, "delay(%.2f)", unknown6c);
  }
  if (!mm::mtl::Singleton<SkipManager>::getPtr()->isSkip()) {
    fw::debug::drawFont(70, 600, "   %d / %d", static_cast<int>(gf::GfGameEvent::getPlayBgmTime() * 30.0f), static_cast<int>(gf::GfGameEvent::getPlayBgmTotalTime() * 30.0f));
  } else {
    fw::debug::drawFont(70, 600, "   SKIP..");
  }
  fw::debug::drawSquare2D(mm::Rect<s32>(210, 600, 8, static_cast<int>(gf::GfGameEvent::getPlayBgmVolume() * -30.0f)), mm::Col4(1.0f, 0.5f, 0.5f, 1.0f));
  fw::debug::drawFont(225, 580, "vol");
  fw::debug::drawFont(200, 600, "%.2f", gf::GfGameEvent::getPlayBgmVolume());
  if (!(unknown10 & FLAG_ENDLESS)) {
    fw::debug::drawFont(270, 570, "life %d", static_cast<int>(unknown7c));
  } else {
    fw::debug::drawFont(270, 570, "life ∞");
  }
  if (mm::mtl::Singleton<FrameManager>::getPtr()->isPause(FrameManager::PAUSE_TYPE_ALL)) {
    fw::debug::drawFont(270, 595, "PAUSE");
  }
  if (unknown70 > 0.0f) {
    fw::debug::drawFont(380, 630, "DELAYSTOP %.2f", unknown70);
  }
  if (unknown74 != 0.0f) {
    fw::debug::drawFont(380, 605, "OVERTIME  %.2f", unknown74);
  }
}

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
