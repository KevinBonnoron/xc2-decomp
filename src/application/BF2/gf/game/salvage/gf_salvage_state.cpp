#include <math.h>

#include "bdat.h"
#include "gf/camera/gf_camera_player.h"
#include "gf/event/gf_event.h"
#include "gf/field/gf_field_time.h"
#include "gf/game/gf_game_util.h"
#include "gf/game/salvage/gf_game_salvage.h"
#include "gf/gf_manager.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_field_skill.h"
#include "gf/menu/object/gf_menu_obj_common_text.h"
#include "gf/scom/gf_scom_fade.h"
#include "gf/util/gf_item_util.h"
#include "gmk/gmk_manager.h"
#include "ml/dev_clock.h"
#include "ml/rand.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
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
constexpr f32 DIVE_FADE_WAIT_SEC = 2.0f;
constexpr f32 PARTY_FORM_DELAY_SEC = 0.2f;
constexpr f32 CAM_WAIT_SEC = 1.0f;
constexpr u32 FADE_FRAME = 10;
constexpr int SALVAGE_ID_NO_TIME_LAPSE = 0x2a;
constexpr int LAPSED_TIME_RANGE = 120;
constexpr int LAPSED_TIME_BASE = 300;

void StateSalvageSkillCheck::leave(GfGameSalvage *, ai::State *) {}

void StateSalvageSkillCheck::update(GfGameSalvage *, const fw::UpdateInfo &) {
  if (GfManager::isDestroyNow()) {
    reqState(GfGameSalvage::STATE_FINISH);
  }
  if (!GfMenuFieldSkill::isRunning()) {
    reqState(unknown08 + 1);
  }
}

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

void StateSalvageItemSelect::update(GfGameSalvage *salvage, const fw::UpdateInfo &) {
  if (context->isTerm() && !context->unknown18.empty()) {
    GfMenuCallContext::GfMenuResult result;
    context->popResult(result);
    if (result.unknown00 == 0) {
      salvage->unknownb8 = result.unknown04;
      GfItemUtil::addItemBox(result.unknown04, -1);
      reqState(unknown08 + 1);
    } else {
      reqState(GfGameSalvage::STATE_FINISH);
    }
  }
  if (GfManager::isDestroyNow()) {
    reqState(GfGameSalvage::STATE_FINISH);
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

void StateSalvageLoad::leave(GfGameSalvage *salvage, ai::State *) {
  mm::Mat44 matrix;
  if (salvage->getEventOrigin(matrix) && salvage->isValidModel()) {
    mm::Vec3 position(matrix.rows[3][0], matrix.rows[3][1], matrix.rows[3][2]);
    f32 rotation = atan2f(matrix.rows[2][0], matrix.rows[2][2]);
    salvage->setModelTransform(position, rotation * mm::RAD_TO_DEG);
    salvage->createCameraDiveStart(position, rotation);
  }
}

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

void StateSalvageDiveFadeWait::enter(GfGameSalvage *salvage, ai::State *) {
  ml::DevClock::getClockNow(startClock);
  if (salvage->getBindedBdatId() != SALVAGE_ID_NO_TIME_LAPSE && !salvage->isChaseKikuInSupervia()) {
    int lapsedTime = ml::mtRand(-LAPSED_TIME_RANGE, LAPSED_TIME_RANGE + 1) + LAPSED_TIME_BASE;
    int hour = GfFieldTime::get()->getHour();
    int minute = GfFieldTime::get()->getMin();
    int time = lapsedTime + hour * 60 + minute;
    if (time >= 24 * 60) {
      time -= 24 * 60;
    }
    hour = time / 60;
    minute = time - hour * 60;
    GfFieldTime::get()->setHour(hour);
    GfFieldTime::get()->setMin(minute);
    salvage->setLogLapsedTime(lapsedTime);
  } else {
    salvage->setLogLapsedTime(0);
  }
  int item = salvage->unknownb8;
  u8 *bdat = salvage->getBindedBdatFp();
  int id = salvage->getBindedBdatId();
  u16 specialEventId = Bdat::getValCheck(bdat, "SpecialEventID", id, 2);
  u16 specialItem = Bdat::getValCheck(bdat, "SpecialItem", id, 2);
  int tableIndex = item - 20000;
  if (tableIndex > 4) {
    tableIndex = 5;
  }
  mm::mtl::FixStr<16> table;
  table.format("SalvageTable%d", tableIndex);
  if (!specialEventId || specialItem != item) {
    u16 count = Bdat::getValCheck(bdat, table.c_str(), id, 2);
    GfGameSalvage::RaffleInfo info;
    info.unknown00 = count == 0 ? 1 : count;
    info.unknown04 = salvage->unknownb0;
    info.unknown08 = salvage->unknownb4;
    salvage->execRaffle(info);
  }
  salvage->calcClimb();
  salvage->playSE(GfGameSalvage::SEID_UNKNOWN_25C);
  salvage->playDiveVibration();
}

void StateSalvageDiveFadeWait::leave(GfGameSalvage *salvage, ai::State *) {
  salvage->destroyCameraDive();
  mm::Mat44 matrix;
  if (salvage->getEventOrigin(matrix)) {
    mm::Vec3 position(matrix.rows[3][0], matrix.rows[3][1], matrix.rows[3][2]);
    f32 rotation = atan2f(matrix.rows[2][0], matrix.rows[2][2]);
    salvage->createCameraClimb(salvage->getClimbAnimationType(), position, rotation);
  }
}

void StateSalvageDiveFadeWait::update(GfGameSalvage *, const fw::UpdateInfo &) {
  f32 time = 0.0f;
  ml::DevClock::getTimeNow(time, startClock);
  if (time >= DIVE_FADE_WAIT_SEC) {
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

void StateSalvagePartyFormDelay::leave(GfGameSalvage *salvage, ai::State *) {
  PlayerCamera::setOnceOff();
  salvage->destroyCameraCut01();
  salvage->destroyModel();
  salvage->createLog();
}

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
