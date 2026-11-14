#include "event/bgm_manager.h"

#include "event/debug_manager.h"
#include "event/extend.h"
#include "event/frame_manager.h"
#include "event/skip_manager.h"
#include "fw/fw_debug.h"
#include "gf/game/event/gf_event_bgm_setup.h"
#include "gf/game/event/gf_game_event.h"
#include "ml/rand.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_rect.h"

namespace event {

const s32 BgmManager::unknown001[7] = {15, 20, 23, 25, 23, 20, 15};

BgmManager::BgmManager() : unknown10(0), unknown14(0), unknown7c(0.0f) {}

void BgmManager::render() {
  if (!(unknown14 & DISP_FLAG_UNKNOWN_0) || !(unknown10 & FLAG_UNKNOWN_1)) {
    return;
  }
  fw::debug::drawCompareZ(false);
  fw::debug::drawSquare2D(mm::Rect<s32>(20, 560, 350, 60), mm::Col4(0.0f, 0.0f, 0.0f, 0.25f));
  fw::debug::drawLineSquare2D(mm::Rect<s32>(20, 560, 350, 60), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFont(25, 565, mm::Col4::white, "BGM");
  if (!(unknown10 & FLAG_UNKNOWN_2)) {
    if (mm::mtl::Singleton<FrameManager>::getPtr()->isPause(FrameManager::PAUSE_TYPE_UNKNOWN_17_2)) {
      ml::mtInit(0);
    }
    for (s32 i = 0; i < 7; i++) {
      fw::debug::drawSquare2D(mm::Rect<s32>(30 + i * 5, 610, 5, -unknown001[i] - ml::mtRand(5)), mm::Col4(1.0f, 0.5f, 0.5f, 1.0f));
    }
  }
  if (!(unknown10 & FLAG_UNKNOWN_2)) {
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
  if (!(unknown10 & FLAG_UNKNOWN_3)) {
    fw::debug::drawFont(270, 570, "life %d", static_cast<int>(unknown7c));
  } else {
    fw::debug::drawFont(270, 570, "life ∞");
  }
  if (mm::mtl::Singleton<FrameManager>::getPtr()->isPause(FrameManager::PAUSE_TYPE_UNKNOWN_17_2)) {
    fw::debug::drawFont(270, 595, "PAUSE");
  }
  if (unknown70 > 0.0f) {
    fw::debug::drawFont(380, 630, "DELAYSTOP %.2f", unknown70);
  }
  if (unknown74 != 0.0f) {
    fw::debug::drawFont(380, 605, "OVERTIME  %.2f", unknown74);
  }
}

void BgmManager::stop() {
  if (unknown10 & FLAG_UNKNOWN_1) {
    gf::EventBgmSetup setup;
    setup.unknown00 = "";
    setup.unknown44 = 1.0f;
    setup.unknown48 = 0.0f;
    setup.unknown4c = 0.0f;
    setup.unknown50 = 0.0f;
    setup.unknown54 = 0.0f;
    setup.unknown58 = 0.0f;
    setup.unknown5c = 0.0f;
    setup.unknown60 = false;
    setup.unknown62 = true;
    setup.unknown63 = true;
    setup.unknown64 = true;
    setup.unknown65 = true;
    gf::GfGameEvent::playBgm(setup);
    setFlag(FLAG_UNKNOWN_1, false);
    setFlag(FLAG_UNKNOWN_6, false);
    setFlag(FLAG_UNKNOWN_5, true);
  }
}

void BgmManager::setHandOver(bool isHandOver) { setFlag(FLAG_UNKNOWN_0, isHandOver); }

void BgmManager::playDefaultBgm(f32 fadeFrame) {
  if (fadeFrame >= 0.0f) {
    gf::EventBgmSetup setup;
    setup.unknown00 = "";
    setup.unknown44 = 1.0f;
    setup.unknown48 = 0.0f;
    setup.unknown4c = fadeFrame * TO_SEC;
    setup.unknown50 = 0.0f;
    setup.unknown54 = 0.0f;
    setup.unknown58 = 0.0f;
    setup.unknown60 = true;
    setup.unknown62 = true;
    setup.unknown65 = true;
    setup.unknown5c = 0.0f;
    gf::GfGameEvent::playBgm(setup);
  }
  gf::EventBgmSetup setup;
  setup.unknown00 = "";
  setup.unknown44 = 1.0f;
  setup.unknown48 = 0.0f;
  setup.unknown4c = 0.0f;
  setup.unknown50 = 0.0f;
  setup.unknown54 = 0.0f;
  setup.unknown58 = 0.0f;
  setup.unknown5c = 0.0f;
  setup.unknown60 = false;
  setup.unknown62 = true;
  setup.unknown63 = true;
  setup.unknown64 = true;
  setup.unknown65 = true;
  gf::GfGameEvent::playBgm(setup);
  unknown10 |= FLAG_UNKNOWN_5;
}

void BgmManager::changeVolume(f32 volume, f32 frame) {
  if ((unknown10 & FLAG_UNKNOWN_1) == 0) {
    return;
  }
  mm::clampRef(volume, 0.0f, 1.0f);
  unknown5c = volume;
  gf::EventBgmSetup setup;
  setup.unknown48 = frame * TO_SEC;
  setup.unknown44 = volume;
  gf::GfGameEvent::changeVolume(setup);
}

void BgmManager::setSyncFrame(f32 frame) {
  if (unknown10 & FLAG_UNKNOWN_1) {
    frame = __builtin_fmaxf(frame, 0.0f);
    if (frame < gf::GfGameEvent::getPlayBgmTotalTime() * TO_FR) {
      mm::mtl::Singleton<DebugManager>::getPtr()->playMessage("bgm play offset %.1f", __builtin_fmaxf(frame + unknown68 - unknown6c, 0.0f));
      gf::EventBgmSetup setup;
      setup.unknown00 = "";
      setup.unknown44 = 1.0f;
      setup.unknown48 = 0.0f;
      setup.unknown4c = 0.0f;
      setup.unknown50 = 0.0f;
      setup.unknown54 = 0.0f;
      setup.unknown58 = 0.0f;
      setup.unknown5c = 0.0f;
      setup.unknown60 = false;
      setup.unknown62 = true;
      setup.unknown63 = true;
      setup.unknown64 = true;
      setup.unknown65 = true;
      gf::GfGameEvent::playBgm(setup);
      unknown10 |= FLAG_UNKNOWN_6;
      unknown80 = frame;
      unknown84 = 1;
    } else {
      stop();
    }
  }
}

f32 BgmManager::getStartedTotalFrame() const { return m_startedTotalFrame; }

void BgmManager::cancelOverTime() const {
  if ((unknown10 & FLAG_UNKNOWN_1) != 0 && unknown74 != 0.0f) {
    gf::GfGameEvent::cancelOverTime();
  }
}

void BgmManager::setDisp(bool isDisp) {
  if (isDisp) {
    unknown14 |= DISP_FLAG_UNKNOWN_0;
  } else {
    unknown14 &= ~DISP_FLAG_UNKNOWN_0;
  }
}

bool BgmManager::isDisp() const { return (unknown14 & DISP_FLAG_UNKNOWN_0) != 0; }

} // namespace event
