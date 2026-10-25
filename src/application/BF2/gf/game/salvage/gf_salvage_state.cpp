#include "gf/event/gf_event.h"
#include "gf/game/gf_game_util.h"
#include "gf/game/salvage/gf_game_salvage.h"
#include "gf/gf_manager.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/object/gf_menu_obj_common_text.h"
#include "gf/scom/gf_scom_fade.h"
#include "gmk/gmk_manager.h"
#include "ml/dev_clock.h"
#include "mm_math/mm_col4.h"
#include "types.h"

namespace ai {
class State;
} // namespace ai
namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {

constexpr f32 SETUP_FADE_OUT_SEC = 0.4f;
constexpr f32 SETUP_FADE_IN_SEC = 0.9f;
constexpr f32 DIVE_FADE_SEC = 0.9f;
constexpr f32 PARTY_FORM_DELAY_SEC = 0.2f;
constexpr f32 CAM_WAIT_SEC = 1.0f;
constexpr u32 FADE_FRAME = 10;

void StateSalvageWait::enter(GfGameSalvage *, ai::State *) {}

void StateSalvageWait::leave(GfGameSalvage *, ai::State *) {}

void StateSalvageWait::update(GfGameSalvage *, const fw::UpdateInfo &) {}

void StateSalvageTBoxCheck::enter(GfGameSalvage *, ai::State *) {}

void StateSalvageTBoxCheck::leave(GfGameSalvage *, ai::State *) {}

void StateSalvageTBoxCheck::update(GfGameSalvage *salvage, const fw::UpdateInfo &) {
  if (salvage->isTboxExist()) {
    reqState(GfGameSalvage::STATE_ERROR_MESSAGE);
  } else {
    reqState(GfGameSalvage::STATE_ITEM_SELECT);
  }
}

void StateSalvageErrorMessage::enter(GfGameSalvage *, ai::State *) {
  context = GfMenuCallContext::create();
  GfMenuObjCommonText::open(context, 0xe, 0);
}

void StateSalvageErrorMessage::leave(GfGameSalvage *, ai::State *) {
  if (context != nullptr) {
    context->release();
    context = nullptr;
  }
}

void StateSalvageErrorMessage::update(GfGameSalvage *, const fw::UpdateInfo &) {
  if (context->isTerm()) {
    reqState(GfGameSalvage::STATE_WAIT);
  }
  if (GfManager::isDestroyNow()) {
    reqState(GfGameSalvage::STATE_FINISH);
  }
}

void StateSalvageItemSelect::leave(GfGameSalvage *, ai::State *) {
  if (context != nullptr) {
    context->release();
    context = nullptr;
  }
}

void StateSalvageSetupFadeOut::enter(GfGameSalvage *, ai::State *) {
  ml::DevClock::getClockNow(startClock);
  SCOM_FADE::create(0, FADE_FRAME, mm::Col4::black);
  GfEvent::callSalvageStateChange(GfGameSalvage::STATE_SETUP_FADE_OUT);
}

void StateSalvageSetupFadeOut::leave(GfGameSalvage *, ai::State *) {}

void StateSalvageSetupFadeOut::update(GfGameSalvage *, const fw::UpdateInfo &) {
  f32 time = 0.0f;
  ml::DevClock::getTimeNow(time, startClock);
  if (time >= SETUP_FADE_OUT_SEC) {
    reqState(unknown08 + 1);
  }
}

void StateSalvageLoad::enter(GfGameSalvage *salvage, ai::State *) { salvage->createModel(); }

void StateSalvageLoad::update(GfGameSalvage *salvage, const fw::UpdateInfo &) {
  if (salvage->isValidModel()) {
    reqState(unknown08 + 1);
  }
  if (GfManager::isDestroyNow()) {
    reqState(GfGameSalvage::STATE_FINISH);
  }
}

void StateSalvageSetupFadeIn::enter(GfGameSalvage *salvage, ai::State *) {
  ml::DevClock::getClockNow(startClock);
  salvage->setPartyDisp(false);
  SCOM_FADE::create(0, FADE_FRAME, mm::Col4(0.0f, 0.0f, 0.0f, 0.0f));
  GfEvent::callSalvageStateChange(GfGameSalvage::STATE_SETUP_FADE_IN);
}

void StateSalvageSetupFadeIn::leave(GfGameSalvage *, ai::State *) {}

void StateSalvageSetupFadeIn::update(GfGameSalvage *, const fw::UpdateInfo &) {
  f32 time = 0.0f;
  ml::DevClock::getTimeNow(time, startClock);
  if (time >= SETUP_FADE_IN_SEC) {
    reqState(unknown08 + 1);
  }
  if (GfManager::isDestroyNow()) {
    reqState(GfGameSalvage::STATE_FINISH);
  }
}

void StateSalvageStartVoice::enter(GfGameSalvage *salvage, ai::State *) {
  ml::DevClock::getClockNow(startClock);
  if (salvage->unknownb4 != 0) {
    salvage->playVoice(GfGameSalvage::VOICE_START_SKILL);
  } else {
    salvage->playVoice(GfGameSalvage::VOICE_START);
  }
}

void StateSalvageStartVoice::leave(GfGameSalvage *, ai::State *) {}

void StateSalvageStartVoice::update(GfGameSalvage *salvage, const fw::UpdateInfo &) {
  if (GfManager::isDestroyNow()) {
    reqState(GfGameSalvage::STATE_FINISH);
  }
  if (salvage->isVoiceEnd()) {
    reqState(unknown08 + 1);
  }
}

void StateSalvageDiveWait::enter(GfGameSalvage *, ai::State *) {}

void StateSalvageDiveWait::leave(GfGameSalvage *, ai::State *) {}

void StateSalvageDiveWait::update(GfGameSalvage *salvage, const fw::UpdateInfo &) {
  if (GfManager::isDestroyNow()) {
    reqState(GfGameSalvage::STATE_FINISH);
  }
  if (salvage->isCameraDive()) {
    salvage->playCameraDive();
    reqState(unknown08 + 1);
  }
}

void StateSalvageDiveEnd::enter(GfGameSalvage *, ai::State *) {}

void StateSalvageDiveEnd::leave(GfGameSalvage *, ai::State *) {}

void StateSalvageDiveEnd::update(GfGameSalvage *salvage, const fw::UpdateInfo &) {
  if (GfManager::isDestroyNow()) {
    reqState(GfGameSalvage::STATE_FINISH);
  }
  if (salvage->isAnimationEnd()) {
    reqState(unknown08 + 1);
  }
}

void StateSalvageDiveFadeOut::enter(GfGameSalvage *, ai::State *) {
  ml::DevClock::getClockNow(startClock);
  SCOM_FADE::create(0, FADE_FRAME, mm::Col4::black);
}

void StateSalvageDiveFadeOut::leave(GfGameSalvage *, ai::State *) {}

void StateSalvageDiveFadeOut::update(GfGameSalvage *, const fw::UpdateInfo &) {
  f32 time = 0.0f;
  ml::DevClock::getTimeNow(time, startClock);
  if (time >= DIVE_FADE_SEC) {
    reqState(unknown08 + 1);
  }
  if (GfManager::isDestroyNow()) {
    reqState(GfGameSalvage::STATE_FINISH);
  }
}

void StateSalvageDiveFadeIn::enter(GfGameSalvage *salvage, ai::State *) {
  ml::DevClock::getClockNow(startClock);
  SCOM_FADE::create(0, FADE_FRAME, mm::Col4(0.0f, 0.0f, 0.0f, 0.0f));
  salvage->playClimbReady();
  salvage->playWireStart(0.0f, 2.0f, 0.3f);
}

void StateSalvageDiveFadeIn::leave(GfGameSalvage *, ai::State *) {}

void StateSalvageDiveFadeIn::update(GfGameSalvage *, const fw::UpdateInfo &) {
  f32 time = 0.0f;
  ml::DevClock::getTimeNow(time, startClock);
  if (time >= DIVE_FADE_SEC) {
    reqState(unknown08 + 1);
  }
  if (GfManager::isDestroyNow()) {
    reqState(GfGameSalvage::STATE_FINISH);
  }
}

void StateSalvageResult::enter(GfGameSalvage *salvage, ai::State *) {
  ml::DevClock::getClockNow(startClock);
  isVibrated = false;
  salvage->destroyCameraClimb();
  salvage->playCameraCut01();
  salvage->execPop();
}

void StateSalvageResult::leave(GfGameSalvage *, ai::State *) {}

void StateSalvageResultUi::update(GfGameSalvage *, const fw::UpdateInfo &) {
  if (GfManager::isDestroyNow()) {
    reqState(GfGameSalvage::STATE_FINISH);
  }
  if (context->isTerm()) {
    reqState(unknown08 + 1);
  }
}

void StateSalvagePartyFormDelay::enter(GfGameSalvage *, ai::State *) { ml::DevClock::getClockNow(startClock); }

void StateSalvagePartyFormDelay::update(GfGameSalvage *, const fw::UpdateInfo &) {
  f32 time = 0.0f;
  ml::DevClock::getTimeNow(time, startClock);
  if (time >= PARTY_FORM_DELAY_SEC) {
    reqState(unknown08 + 1);
  }
}

void StateSalvageCamWait::enter(GfGameSalvage *, ai::State *) { ml::DevClock::getClockNow(startClock); }

void StateSalvageCamWait::leave(GfGameSalvage *, ai::State *) {}

void StateSalvageCamWait::update(GfGameSalvage *, const fw::UpdateInfo &) {
  f32 time = 0.0f;
  ml::DevClock::getTimeNow(time, startClock);
  if (time >= CAM_WAIT_SEC) {
    reqState(unknown08 + 1);
  }
}

void StateSalvageFinish::enter(GfGameSalvage *, ai::State *) { ml::DevClock::getClockNow(startClock); }

void StateSalvageFinish::leave(GfGameSalvage *, ai::State *) {
  GfGameUtil::setDispByGmkType(gmk::GMK_TYPE_SALVAGE, true);
  GfEvent::callSalvageStateChange(GfGameSalvage::STATE_FINISH);
}

void StateSalvageFinish::update(GfGameSalvage *, const fw::UpdateInfo &) { reqState(GfGameSalvage::STATE_WAIT); }

} // namespace gf
