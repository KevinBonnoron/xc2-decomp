#include <math.h>

#include "bdat.h"
#include "fw/fw_pad.h"
#include "gf/camera/gf_camera_player.h"
#include "gf/event/gf_event.h"
#include "gf/field/gf_field_time.h"
#include "gf/game/gf_game_speed.h"
#include "gf/game/gf_game_util.h"
#include "gf/game/salvage/gf_game_salvage.h"
#include "gf/gf_manager.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_field_skill.h"
#include "gf/menu/object/gf_menu_obj_button_challenge2.h"
#include "gf/menu/object/gf_menu_obj_common_text.h"
#include "gf/menu/object/gf_menu_obj_cylinder_select.h"
#include "gf/object/component/behavior/gf_com_behavior_salvage.h"
#include "gf/scom/gf_scom_fade.h"
#include "gf/scom/gf_scom_obj.h"
#include "gf/util/gf_item_util.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_manager.h"
#include "ml/dev_clock.h"
#include "ml/dev_pad.h"
#include "ml/rand.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/delegate.h"
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

constexpr f32 unknown015 = 0.4f;             // Inferred role: setup fade out sec; original name unknown.
constexpr f32 unknown016 = 0.9f;             // Inferred role: setup fade in sec; original name unknown.
constexpr f32 unknown017 = 0.9f;             // Inferred role: dive fade sec; original name unknown.
constexpr f32 unknown036 = 2.0f;             // Inferred role: dive fade wait sec; original name unknown.
constexpr f32 unknown038 = 0.2f;             // Inferred role: party form delay sec; original name unknown.
constexpr f32 unknown039 = 1.0f;             // Inferred role: cam wait sec; original name unknown.
constexpr u32 FRAME_UNKNOWN_10 = 10;         // Inferred role: fade frame; original name unknown.
constexpr int SALVAGE_ID_UNKNOWN_42 = 0x2a;  // Inferred role: salvage id no time lapse; original name unknown.
constexpr int LAPSED_TIME_UNKNOWN_120 = 120; // Inferred role: lapsed time range; original name unknown.
constexpr int LAPSED_TIME_UNKNOWN_300 = 300; // Inferred role: lapsed time base; original name unknown.

void StateSalvageSkillCheck::leave(GfGameSalvage *, ai::State *) {}

void StateSalvageSkillCheck::update(GfGameSalvage *, const fw::UpdateInfo &) {
  if (GfManager::isDestroyNow()) {
    reqState(GfGameSalvage::STATE_UNKNOWN_20);
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
    reqState(GfGameSalvage::STATE_UNKNOWN_2);
  } else {
    reqState(GfGameSalvage::STATE_UNKNOWN_3);
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
    reqState(GfGameSalvage::STATE_UNKNOWN_0);
  }
  if (GfManager::isDestroyNow()) {
    reqState(GfGameSalvage::STATE_UNKNOWN_20);
  }
}

void StateSalvageItemSelect::enter(GfGameSalvage *salvage, ai::State *) {
  u8 *bdat = salvage->getBindedBdatFp();
  int id = salvage->getBindedBdatId();
  u32 specialItem = static_cast<u16>(Bdat::getValCheck(bdat, "SpecialItem", id, 2));
  context = GfMenuCallContext::create();
  GfMenuObjCylinderSelect::open(context, specialItem);
  GfGameUtil::setDispByGmkType(gmk::GMK_TYPE_SALVAGE, false);
  GfEvent::callSalvageStateChange(GfGameSalvage::STATE_UNKNOWN_3);
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
      reqState(GfGameSalvage::STATE_UNKNOWN_20);
    }
  }
  if (GfManager::isDestroyNow()) {
    reqState(GfGameSalvage::STATE_UNKNOWN_20);
  }
}

void StateSalvageSetupFadeOut::enter(GfGameSalvage *, ai::State *) {
  ml::DevClock::getClockNow(startClock);
  SCOM_FADE::create(0, FRAME_UNKNOWN_10, mm::Col4::black);
  GfEvent::callSalvageStateChange(GfGameSalvage::STATE_UNKNOWN_4);
}

void StateSalvageSetupFadeOut::leave(GfGameSalvage *, ai::State *) {}

void StateSalvageSetupFadeOut::update(GfGameSalvage *, const fw::UpdateInfo &) {
  f32 time = 0.0f;
  ml::DevClock::getTimeNow(time, startClock);
  if (time >= unknown015) {
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
    reqState(GfGameSalvage::STATE_UNKNOWN_20);
  }
}

void StateSalvageSetupFadeIn::enter(GfGameSalvage *salvage, ai::State *) {
  ml::DevClock::getClockNow(startClock);
  salvage->setPartyDisp(false);
  SCOM_FADE::create(0, FRAME_UNKNOWN_10, mm::Col4(0.0f, 0.0f, 0.0f, 0.0f));
  GfEvent::callSalvageStateChange(GfGameSalvage::STATE_UNKNOWN_6);
}

void StateSalvageSetupFadeIn::leave(GfGameSalvage *, ai::State *) {}

void StateSalvageSetupFadeIn::update(GfGameSalvage *, const fw::UpdateInfo &) {
  f32 time = 0.0f;
  ml::DevClock::getTimeNow(time, startClock);
  if (time >= unknown016) {
    reqState(unknown08 + 1);
  }
  if (GfManager::isDestroyNow()) {
    reqState(GfGameSalvage::STATE_UNKNOWN_20);
  }
}

void StateSalvageStartVoice::enter(GfGameSalvage *salvage, ai::State *) {
  ml::DevClock::getClockNow(startClock);
  if (salvage->unknownb4 != 0) {
    salvage->playVoice(GfGameSalvage::VOICETYPE_UNKNOWN_1);
  } else {
    salvage->playVoice(GfGameSalvage::VOICETYPE_UNKNOWN_0);
  }
}

void StateSalvageStartVoice::leave(GfGameSalvage *, ai::State *) {}

void StateSalvageStartVoice::update(GfGameSalvage *salvage, const fw::UpdateInfo &) {
  if (GfManager::isDestroyNow()) {
    reqState(GfGameSalvage::STATE_UNKNOWN_20);
  }
  if (salvage->isVoiceEnd()) {
    reqState(unknown08 + 1);
  }
}

void StateSalvageDiveStart::enter(GfGameSalvage *salvage, ai::State *) {
  salvage->clearLogButtonChallenge();
  salvage->playAnimation(GfGameSalvage::ANIMATION_UNKNOWN_1);
  salvage->playCameraDiveStart();
  unknown30 = 0;
  unknown34 = 0;
  unknown38 = 0;
  for (u32 i = 0; i < 3; i++) {
    unknown18[i] = nullptr;
  }
  for (u32 i = 0; i < 3; i++) {
    unknown3c[i] = salvage->getButtonChallengeId(i);
  }
  GfComBehaviorSalvage *behavior = salvage->getGfComBehaviorSalvage();
  if (behavior != nullptr) {
    behavior->unknown98.bind(this, &StateSalvageDiveStart::callback);
  }
}

void StateSalvageDiveStart::leave(GfGameSalvage *salvage, ai::State *) {
  GfComBehaviorSalvage *behavior = salvage->getGfComBehaviorSalvage();
  if (behavior != nullptr) {
    behavior->unknown98.clear();
  }
  for (u32 i = 0; i < 3; i++) {
    if (unknown18[i] != nullptr) {
      unknown18[i]->release();
      unknown18[i] = nullptr;
    }
  }
}

void StateSalvageDiveStart::callback() {
  if (unknown30 < 3) {
    int index = unknown30++;
    unknown34 = unknown3c[index];
    GfMenuCallContext *&context = unknown18[index];
    if (context == nullptr) {
      context = GfMenuCallContext::create();
    } else {
      if (!context->isTerm()) {
        GfMenuObjButtonChallenge2::close(context);
      }
      context->reset();
    }
    GfMenuObjButtonChallenge2::OptionParam option;
    option.unknown02 = false;
    option.unknown00 = false;
    option.unknown01 = false;
    option.unknown04 = 0.16f;
    GfMenuObjButtonChallenge2::open(context, unknown34, option);
    GfGameSpeed::setSalvageSpeed((3 - unknown30) * 0.05f + 0.1f);
  }
}

void StateSalvageDiveWait::enter(GfGameSalvage *, ai::State *) {}

void StateSalvageDiveWait::leave(GfGameSalvage *, ai::State *) {}

void StateSalvageDiveWait::update(GfGameSalvage *salvage, const fw::UpdateInfo &) {
  if (GfManager::isDestroyNow()) {
    reqState(GfGameSalvage::STATE_UNKNOWN_20);
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
    reqState(GfGameSalvage::STATE_UNKNOWN_20);
  }
  if (salvage->isAnimationEnd()) {
    reqState(unknown08 + 1);
  }
}

void StateSalvageDiveFadeOut::enter(GfGameSalvage *, ai::State *) {
  ml::DevClock::getClockNow(startClock);
  SCOM_FADE::create(0, FRAME_UNKNOWN_10, mm::Col4::black);
}

void StateSalvageDiveFadeOut::leave(GfGameSalvage *, ai::State *) {}

void StateSalvageDiveFadeOut::update(GfGameSalvage *, const fw::UpdateInfo &) {
  f32 time = 0.0f;
  ml::DevClock::getTimeNow(time, startClock);
  if (time >= unknown017) {
    reqState(unknown08 + 1);
  }
  if (GfManager::isDestroyNow()) {
    reqState(GfGameSalvage::STATE_UNKNOWN_20);
  }
}

void StateSalvageDiveFadeWait::enter(GfGameSalvage *salvage, ai::State *) {
  ml::DevClock::getClockNow(startClock);
  if (salvage->getBindedBdatId() != SALVAGE_ID_UNKNOWN_42 && !salvage->isChaseKikuInSupervia()) {
    int lapsedTime = ml::mtRand(-LAPSED_TIME_UNKNOWN_120, LAPSED_TIME_UNKNOWN_120 + 1) + LAPSED_TIME_UNKNOWN_300;
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
  salvage->playSE(GfGameSalvage::SEID_UNKNOWN_604);
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
  if (time >= unknown036) {
    reqState(unknown08 + 1);
  }
  if (GfManager::isDestroyNow()) {
    reqState(GfGameSalvage::STATE_UNKNOWN_20);
  }
}

void StateSalvageDiveFadeIn::enter(GfGameSalvage *salvage, ai::State *) {
  ml::DevClock::getClockNow(startClock);
  SCOM_FADE::create(0, FRAME_UNKNOWN_10, mm::Col4(0.0f, 0.0f, 0.0f, 0.0f));
  salvage->playClimbReady();
  salvage->playWireStart(0.0f, 2.0f, 0.3f);
}

void StateSalvageDiveFadeIn::leave(GfGameSalvage *, ai::State *) {}

void StateSalvageDiveFadeIn::update(GfGameSalvage *, const fw::UpdateInfo &) {
  f32 time = 0.0f;
  ml::DevClock::getTimeNow(time, startClock);
  if (time >= unknown017) {
    reqState(unknown08 + 1);
  }
  if (GfManager::isDestroyNow()) {
    reqState(GfGameSalvage::STATE_UNKNOWN_20);
  }
}

void StateSalvageClimbStart::enter(GfGameSalvage *salvage, ai::State *) {
  unknown18 = salvage->getClimbAnimationType();
  unknown19 = 0;
  salvage->playClimb();
  salvage->playCameraClimb();
  mm::Mat44 matrix;
  if (salvage->getEventTbox(matrix)) {
    mm::Vec3 position(matrix.rows[3][0], matrix.rows[3][1], matrix.rows[3][2]);
    f32 rotation = atan2f(matrix.rows[2][0], matrix.rows[2][2]);
    salvage->createCameraCut01(position, rotation);
  }
  GfComBehaviorSalvage *behavior = salvage->getGfComBehaviorSalvage();
  if (behavior != nullptr) {
    behavior->unknown98.bind(this, &StateSalvageClimbStart::callback);
  }
}

void StateSalvageClimbStart::leave(GfGameSalvage *salvage, ai::State *) {
  GfComBehaviorSalvage *behavior = salvage->getGfComBehaviorSalvage();
  if (behavior != nullptr) {
    behavior->unknown98.clear();
  }
}

void StateSalvageClimbStart::callback() {
  fw::VibrationID vibration = fw::VIBRATION_ID_UNKNOWN_15;
  switch (unknown18) {
  case GfGameSalvage::ANIMATION_UNKNOWN_5:
    vibration = fw::VIBRATION_ID_UNKNOWN_13;
    break;
  case GfGameSalvage::ANIMATION_UNKNOWN_6:
    vibration = unknown19 == 0 ? fw::VIBRATION_ID_UNKNOWN_10 : fw::VIBRATION_ID_UNKNOWN_13;
    break;
  case GfGameSalvage::ANIMATION_UNKNOWN_7:
    vibration = fw::VIBRATION_ID_UNKNOWN_7;
    break;
  case GfGameSalvage::ANIMATION_UNKNOWN_8:
    vibration = fw::VIBRATION_ID_UNKNOWN_14;
    break;
  case GfGameSalvage::ANIMATION_UNKNOWN_9:
    vibration = fw::VIBRATION_ID_UNKNOWN_22;
    break;
  case GfGameSalvage::ANIMATION_UNKNOWN_10:
    vibration = unknown19 == 0 ? fw::VIBRATION_ID_UNKNOWN_8 : fw::VIBRATION_ID_UNKNOWN_14;
    break;
  }
  fw::PadManager::playVibration(ml::PadVibrationInfo(vibration));
  unknown19++;
}

void StateSalvageClimbStart::update(GfGameSalvage *salvage, const fw::UpdateInfo &) {
  if (GfManager::isDestroyNow()) {
    reqState(GfGameSalvage::STATE_UNKNOWN_20);
  }
  if (salvage->isClimbEnd() && salvage->isCameraClimbEnd()) {
    reqState(unknown08 + 1);
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

void StateSalvageResultUi::leave(GfGameSalvage *salvage, ai::State *) {
  if (context != nullptr) {
    context->release();
    context = nullptr;
  }
  salvage->setPartyDisp(true);
  SCOM_QUEST_GIMMICK::createSalvage(gmk::getBindedGmkInst(GfGameSalvage::get()->unknowna8)->unknown20.unknown18, 0.0f);
}

void StateSalvageResultUi::update(GfGameSalvage *, const fw::UpdateInfo &) {
  if (GfManager::isDestroyNow()) {
    reqState(GfGameSalvage::STATE_UNKNOWN_20);
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
  if (time >= unknown038) {
    reqState(unknown08 + 1);
  }
}

void StateSalvageCamWait::enter(GfGameSalvage *, ai::State *) { ml::DevClock::getClockNow(startClock); }

void StateSalvageCamWait::leave(GfGameSalvage *, ai::State *) {}

void StateSalvageCamWait::update(GfGameSalvage *, const fw::UpdateInfo &) {
  f32 time = 0.0f;
  ml::DevClock::getTimeNow(time, startClock);
  if (time >= unknown039) {
    reqState(unknown08 + 1);
  }
}

void StateSalvageFinish::enter(GfGameSalvage *, ai::State *) { ml::DevClock::getClockNow(startClock); }

void StateSalvageFinish::leave(GfGameSalvage *, ai::State *) {
  GfGameUtil::setDispByGmkType(gmk::GMK_TYPE_SALVAGE, true);
  GfEvent::callSalvageStateChange(GfGameSalvage::STATE_UNKNOWN_20);
}

void StateSalvageFinish::update(GfGameSalvage *, const fw::UpdateInfo &) { reqState(GfGameSalvage::STATE_UNKNOWN_0); }

} // namespace gf
