#include "gf/game/salvage/gf_game_salvage.h"

#include "fw/fw_camera.h"
#include "gf/camera/gimmick/gf_camera_gimmick.h"
#include "gf/data/gf_data_map.h"
#include "gf/data/gf_data_util.h"
#include "gf/data/gf_game_flag.h"
#include "gf/event/gf_event.h"
#include "gf/event/gf_evt_model.h"
#include "gf/game/event/gf_game_event.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_util.h"
#include "gf/gf_allocator.h"
#include "gf/request/gf_req_scom.h"

namespace gf {

constexpr u32 SALVAGER_POINT_MAX = 0xff;
constexpr u16 SCENARIO_CHASE_KIKU_START = 0xfbd;
constexpr u16 SCENARIO_CHASE_KIKU_END = 0xfc9;

static const char *CAMERA_NAMES[] = {
    nullptr,
    "salvage_dive_start",
    "salvage_dive_success",
    "salvage_dive_great_success",
    "salvage_dive_failure",
    "salvage_climb00",
    "salvage_climb01",
    "salvage_climb02",
    "salvage_climb03",
};

GfGameSalvage::GfGameSalvage(const GfSetupParam &param)
    : unknown08(getAllocator(ALLOCATOR_DEFAULT)), unknowna0(false), unknownb0(0), unknownb4(0), unknownc0(nullptr), unknownc8(nullptr), m_climbAnimationType(ANIMATION_RESULT_00), unknownd4(0),
      unknownd8(0) {
  initialize(param);
}

void GfGameSalvage::initialize(const GfSetupParam &) {
  unknown08.beginSetup(this, STATE_MAX);
  unknown08.registerState<StateSalvageWait>(STATE_WAIT);
  unknown08.registerState<StateSalvageTBoxCheck>(STATE_TBOX_CHECK);
  unknown08.registerState<StateSalvageErrorMessage>(STATE_ERROR_MESSAGE);
  unknown08.registerState<StateSalvageItemSelect>(STATE_ITEM_SELECT);
  unknown08.registerState<StateSalvageSetupFadeOut>(STATE_SETUP_FADE_OUT);
  unknown08.registerState<StateSalvageLoad>(STATE_LOAD);
  unknown08.registerState<StateSalvageSetupFadeIn>(STATE_SETUP_FADE_IN);
  unknown08.registerState<StateSalvageSkillCheck>(STATE_SKILL_CHECK);
  unknown08.registerState<StateSalvageStartVoice>(STATE_START_VOICE);
  unknown08.registerState<StateSalvageDiveStart>(STATE_DIVE_START);
  unknown08.registerState<StateSalvageDiveWait>(STATE_DIVE_WAIT);
  unknown08.registerState<StateSalvageDiveEnd>(STATE_DIVE_END);
  unknown08.registerState<StateSalvageDiveFadeOut>(STATE_DIVE_FADE_OUT);
  unknown08.registerState<StateSalvageDiveFadeWait>(STATE_DIVE_FADE_WAIT);
  unknown08.registerState<StateSalvageDiveFadeIn>(STATE_DIVE_FADE_IN);
  unknown08.registerState<StateSalvageClimbStart>(STATE_CLIMB_START);
  unknown08.registerState<StateSalvageResult>(STATE_RESULT);
  unknown08.registerState<StateSalvageResultUi>(STATE_RESULT_UI);
  unknown08.registerState<StateSalvagePartyFormDelay>(STATE_PARTY_FORM_DELAY);
  unknown08.registerState<StateSalvageCamWait>(STATE_CAM_WAIT);
  unknown08.registerState<StateSalvageFinish>(STATE_FINISH);
  unknown08.endSetup();
  unknown08.setState(STATE_WAIT);
  unknowna0 = true;
}

GfGameSalvage::~GfGameSalvage() {}

void GfGameSalvage::build(const GfSetupParam &param) {
  // __LINE__ must be 160 as in the original file: its value changes the instruction order.
#line 160
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfGameSalvage(param);
}

void GfGameSalvage::destroy() {
  GfGameSalvage *salvage = get();
  salvage->finalize();
  delete salvage;
}

void GfGameSalvage::finalize() {
  unknown08.cleanup();
  unknowna0 = false;
}

bool GfGameSalvage::isInitialized() { return get() != nullptr && get()->unknowna0; }

void GfGameSalvage::update(const fw::UpdateInfo &info) {
  if (get() != nullptr) {
    get()->unknown08.update(&info);
  }
}

void GfGameSalvage::startSalvage(GF_OBJ_HANDLE *handle) {
  get()->unknowna8 = handle;
  if (GfGameManager::getState() == GF_STATE_SALVAGE && !GfGameManager::isBattle() && get()->unknown08.getState()->stateID == STATE_WAIT) {
    get()->unknown08.setState(STATE_TBOX_CHECK);
  }
}

bool GfGameSalvage::isStateWait() { return get()->unknown08.getState()->stateID == STATE_WAIT; }

void GfGameSalvage::cancelSalvage() {}

void GfGameSalvage::createCameraDive(AnimationType animation, const mm::Vec3 &position, f32 rotation) {
  fw::CameraManager *manager = fw::CameraManager::get();
  unknown88 = GimmickCamera::create(CAMERA_NAMES[animation], position, rotation);
  static_cast<GimmickCamera *>(unknown88.get())->setAuto(false);
  manager->unknown20[0].push(unknown88, 0.0f);
}

void GfGameSalvage::createCameraClimb(AnimationType animation, const mm::Vec3 &position, f32 rotation) {
  fw::CameraManager *manager = fw::CameraManager::get();
  unknown90 = GimmickCamera::create(CAMERA_NAMES[animation], position, rotation);
  static_cast<GimmickCamera *>(unknown90.get())->setAuto(false);
  manager->unknown20[0].push(unknown90, 0.0f);
}

void GfGameSalvage::createCameraCut01(const mm::Vec3 &position, f32 rotation) {
  unknown98 = GimmickCamera::create("salvage_cut01", position, rotation);
  static_cast<GimmickCamera *>(unknown98.get())->setAuto(false);
}

void GfGameSalvage::destroyCameraDiveStart() {
  fw::CameraManager *manager = fw::CameraManager::get();
  if (unknown80.get() != nullptr && unknown80.get()->unknowna0) {
    manager->unknown20[0].pop(unknown80, 0.0f);
  }
  unknown80 = nullptr;
}

void GfGameSalvage::destroyCameraDive() {
  fw::CameraManager *manager = fw::CameraManager::get();
  if (unknown88.get() != nullptr && unknown88.get()->unknowna0) {
    manager->unknown20[0].pop(unknown88, 0.0f);
  }
  unknown88 = nullptr;
}

void GfGameSalvage::destroyCameraClimb() {
  fw::CameraManager *manager = fw::CameraManager::get();
  if (unknown90.get() != nullptr && unknown90.get()->unknowna0) {
    manager->unknown20[0].pop(unknown90, 0.0f);
  }
  unknown90 = nullptr;
}

void GfGameSalvage::destroyCameraCut01() {
  fw::CameraManager *manager = fw::CameraManager::get();
  if (unknown98.get() != nullptr && unknown98.get()->unknowna0) {
    manager->unknown20[0].pop(unknown98, 1.0f);
  }
  unknown98 = nullptr;
}

void GfGameSalvage::playCameraDiveStart() {
  GimmickCamera *camera = static_cast<GimmickCamera *>(unknown80.get());
  if (camera != nullptr && camera->unknowna0) {
    camera->play();
  }
}

void GfGameSalvage::playCameraDive() {
  GimmickCamera *camera = static_cast<GimmickCamera *>(unknown88.get());
  if (camera != nullptr && camera->unknowna0) {
    camera->play();
  }
}

void GfGameSalvage::playCameraClimb() {
  GimmickCamera *camera = static_cast<GimmickCamera *>(unknown90.get());
  if (camera != nullptr && camera->unknowna0) {
    camera->play();
  }
}

void GfGameSalvage::playCameraCut01() {
  if (unknown98.get() != nullptr && !unknown98.get()->unknowna0) {
    fw::CameraManager::get()->unknown20[0].push(unknown98, 0.0f);
    if (unknown98.get() != nullptr) {
      static_cast<GimmickCamera *>(unknown98.get())->play();
    }
  }
}

bool GfGameSalvage::isCameraDiveStartEnd() {
  GimmickCamera *camera = static_cast<GimmickCamera *>(unknown80.get());
  if (camera != nullptr && camera->unknowna0) {
    return camera->isPlayEnd();
  }
  return true;
}

bool GfGameSalvage::isCameraDiveEnd() {
  GimmickCamera *camera = static_cast<GimmickCamera *>(unknown88.get());
  if (camera != nullptr && camera->unknowna0) {
    return camera->isPlayEnd();
  }
  return true;
}

bool GfGameSalvage::isCameraClimbEnd() {
  GimmickCamera *camera = static_cast<GimmickCamera *>(unknown90.get());
  if (camera != nullptr && camera->unknowna0) {
    return camera->isPlayEnd();
  }
  return true;
}

bool GfGameSalvage::isCameraCut01End() {
  GimmickCamera *camera = static_cast<GimmickCamera *>(unknown98.get());
  if (camera != nullptr && camera->unknowna0) {
    return camera->isPlayEnd();
  }
  return true;
}

bool GfGameSalvage::isCameraDive() {
  GimmickCamera *camera = static_cast<GimmickCamera *>(unknown88.get());
  if (camera != nullptr && camera->unknowna0) {
    return camera->isLoaded();
  }
  return true;
}

void GfGameSalvage::createModel() {
  if (unknownc0 == nullptr) {
    unknownc0 = GfGameEvent::createSalvage();
  }
}

bool GfGameSalvage::isValidModel() {
  if (unknownc0 != nullptr) {
    return unknownc0->isValid();
  }
  return false;
}

void GfGameSalvage::setModelTransform(const mm::Vec3 &position, f32 rotation) {
  if (unknownc0 != nullptr) {
    unknownc0->setTransform(position, rotation);
  }
}

bool GfGameSalvage::isVoiceEnd() {
  if (unknownc8 != nullptr) {
    return SCOM_SALVAGE_VOICE::isPlayEnd(unknownc8);
  }
  return true;
}

GfGameSalvage::AnimationType GfGameSalvage::getClimbAnimationType() const { return m_climbAnimationType; }

void GfGameSalvage::playWireStart(f32 time, f32 speed, f32 length) {
  if (unknownc0 != nullptr) {
    GfGameUtil::startWireWithClose(unknownc0->unknown20, unknowna8, time, speed, length);
  }
}

void GfGameSalvage::addSalvagerPoint(u32 point) {
  if (point == 0) {
    return;
  }
  u32 current = GfGameFlag::getLocal(8, FLAG_SALVAGER_POINT);
  if (current < SALVAGER_POINT_MAX) {
    u32 total = current + point;
    GfGameFlag::setLocal(8, FLAG_SALVAGER_POINT, total > SALVAGER_POINT_MAX ? SALVAGER_POINT_MAX : total);
  }
}

bool GfGameSalvage::isChaseKikuInSupervia() {
  if (GfGameManager::getMapID() == MAP_SUPERBIA) {
    u16 scenario = GfDataUtil::getScenarioFlag();
    return scenario >= SCENARIO_CHASE_KIKU_START && scenario <= SCENARIO_CHASE_KIKU_END;
  }
  return false;
}

void GfGameSalvage::createLog() {}

void GfGameSalvage::setLogSkill(bool, u32) {}

void GfGameSalvage::clearLogSkill() {}

void GfGameSalvage::setLogButtonChallenge(int, int) {}

void GfGameSalvage::clearLogButtonChallenge() {}

void GfGameSalvage::setLogButtonChallengeResult(int) {}

void GfGameSalvage::setLogLapsedTime(int) {}

} // namespace gf
