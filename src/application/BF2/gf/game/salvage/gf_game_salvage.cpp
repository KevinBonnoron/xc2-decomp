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
    : fsm(getAllocator(ALLOCATOR_DEFAULT)), initialized(false), buttonChallengePoint(0), skillPoint(0), model(nullptr), voice(nullptr),
      climbAnimation(ANIMATION_RESULT_00), climbVoice(0), diveVibration(0) {
  initialize(param);
}

void GfGameSalvage::initialize(const GfSetupParam &) {
  fsm.beginSetup(this, STATE_MAX);
  fsm.registerState<StateSalvageWait>(STATE_WAIT);
  fsm.registerState<StateSalvageTBoxCheck>(STATE_TBOX_CHECK);
  fsm.registerState<StateSalvageErrorMessage>(STATE_ERROR_MESSAGE);
  fsm.registerState<StateSalvageItemSelect>(STATE_ITEM_SELECT);
  fsm.registerState<StateSalvageSetupFadeOut>(STATE_SETUP_FADE_OUT);
  fsm.registerState<StateSalvageLoad>(STATE_LOAD);
  fsm.registerState<StateSalvageSetupFadeIn>(STATE_SETUP_FADE_IN);
  fsm.registerState<StateSalvageSkillCheck>(STATE_SKILL_CHECK);
  fsm.registerState<StateSalvageStartVoice>(STATE_START_VOICE);
  fsm.registerState<StateSalvageDiveStart>(STATE_DIVE_START);
  fsm.registerState<StateSalvageDiveWait>(STATE_DIVE_WAIT);
  fsm.registerState<StateSalvageDiveEnd>(STATE_DIVE_END);
  fsm.registerState<StateSalvageDiveFadeOut>(STATE_DIVE_FADE_OUT);
  fsm.registerState<StateSalvageDiveFadeWait>(STATE_DIVE_FADE_WAIT);
  fsm.registerState<StateSalvageDiveFadeIn>(STATE_DIVE_FADE_IN);
  fsm.registerState<StateSalvageClimbStart>(STATE_CLIMB_START);
  fsm.registerState<StateSalvageResult>(STATE_RESULT);
  fsm.registerState<StateSalvageResultUi>(STATE_RESULT_UI);
  fsm.registerState<StateSalvagePartyFormDelay>(STATE_PARTY_FORM_DELAY);
  fsm.registerState<StateSalvageCamWait>(STATE_CAM_WAIT);
  fsm.registerState<StateSalvageFinish>(STATE_FINISH);
  fsm.endSetup();
  fsm.setState(STATE_WAIT);
  initialized = true;
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
  fsm.cleanup();
  initialized = false;
}

bool GfGameSalvage::isInitialized() { return get() != nullptr && get()->initialized; }

void GfGameSalvage::update(const fw::UpdateInfo &info) {
  if (get() != nullptr) {
    get()->fsm.update(&info);
  }
}

void GfGameSalvage::startSalvage(GF_OBJ_HANDLE *handle) {
  get()->handle = handle;
  if (GfGameManager::getState() == GF_STATE_SALVAGE && !GfGameManager::isBattle() && get()->fsm.getState()->stateID == STATE_WAIT) {
    get()->fsm.setState(STATE_TBOX_CHECK);
  }
}

bool GfGameSalvage::isStateWait() { return get()->fsm.getState()->stateID == STATE_WAIT; }

void GfGameSalvage::cancelSalvage() {}

void GfGameSalvage::createCameraDive(AnimationType animation, const mm::Vec3 &position, f32 rotation) {
  fw::CameraManager *manager = fw::CameraManager::get();
  cameraDive = GimmickCamera::create(CAMERA_NAMES[animation], position, rotation);
  static_cast<GimmickCamera *>(cameraDive.get())->setAuto(false);
  manager->layers[0].push(cameraDive, 0.0f);
}

void GfGameSalvage::createCameraClimb(AnimationType animation, const mm::Vec3 &position, f32 rotation) {
  fw::CameraManager *manager = fw::CameraManager::get();
  cameraClimb = GimmickCamera::create(CAMERA_NAMES[animation], position, rotation);
  static_cast<GimmickCamera *>(cameraClimb.get())->setAuto(false);
  manager->layers[0].push(cameraClimb, 0.0f);
}

void GfGameSalvage::createCameraCut01(const mm::Vec3 &position, f32 rotation) {
  cameraCut01 = GimmickCamera::create("salvage_cut01", position, rotation);
  static_cast<GimmickCamera *>(cameraCut01.get())->setAuto(false);
}

void GfGameSalvage::destroyCameraDiveStart() {
  fw::CameraManager *manager = fw::CameraManager::get();
  if (cameraDiveStart.get() != nullptr && cameraDiveStart.get()->isActive) {
    manager->layers[0].pop(cameraDiveStart, 0.0f);
  }
  cameraDiveStart = nullptr;
}

void GfGameSalvage::destroyCameraDive() {
  fw::CameraManager *manager = fw::CameraManager::get();
  if (cameraDive.get() != nullptr && cameraDive.get()->isActive) {
    manager->layers[0].pop(cameraDive, 0.0f);
  }
  cameraDive = nullptr;
}

void GfGameSalvage::destroyCameraClimb() {
  fw::CameraManager *manager = fw::CameraManager::get();
  if (cameraClimb.get() != nullptr && cameraClimb.get()->isActive) {
    manager->layers[0].pop(cameraClimb, 0.0f);
  }
  cameraClimb = nullptr;
}

void GfGameSalvage::destroyCameraCut01() {
  fw::CameraManager *manager = fw::CameraManager::get();
  if (cameraCut01.get() != nullptr && cameraCut01.get()->isActive) {
    manager->layers[0].pop(cameraCut01, 1.0f);
  }
  cameraCut01 = nullptr;
}

void GfGameSalvage::playCameraDiveStart() {
  GimmickCamera *camera = static_cast<GimmickCamera *>(cameraDiveStart.get());
  if (camera != nullptr && camera->isActive) {
    camera->play();
  }
}

void GfGameSalvage::playCameraDive() {
  GimmickCamera *camera = static_cast<GimmickCamera *>(cameraDive.get());
  if (camera != nullptr && camera->isActive) {
    camera->play();
  }
}

void GfGameSalvage::playCameraClimb() {
  GimmickCamera *camera = static_cast<GimmickCamera *>(cameraClimb.get());
  if (camera != nullptr && camera->isActive) {
    camera->play();
  }
}

void GfGameSalvage::playCameraCut01() {
  if (cameraCut01.get() != nullptr && !cameraCut01.get()->isActive) {
    fw::CameraManager::get()->layers[0].push(cameraCut01, 0.0f);
    if (cameraCut01.get() != nullptr) {
      static_cast<GimmickCamera *>(cameraCut01.get())->play();
    }
  }
}

bool GfGameSalvage::isCameraDiveStartEnd() {
  GimmickCamera *camera = static_cast<GimmickCamera *>(cameraDiveStart.get());
  if (camera != nullptr && camera->isActive) {
    return camera->isPlayEnd();
  }
  return true;
}

bool GfGameSalvage::isCameraDiveEnd() {
  GimmickCamera *camera = static_cast<GimmickCamera *>(cameraDive.get());
  if (camera != nullptr && camera->isActive) {
    return camera->isPlayEnd();
  }
  return true;
}

bool GfGameSalvage::isCameraClimbEnd() {
  GimmickCamera *camera = static_cast<GimmickCamera *>(cameraClimb.get());
  if (camera != nullptr && camera->isActive) {
    return camera->isPlayEnd();
  }
  return true;
}

bool GfGameSalvage::isCameraCut01End() {
  GimmickCamera *camera = static_cast<GimmickCamera *>(cameraCut01.get());
  if (camera != nullptr && camera->isActive) {
    return camera->isPlayEnd();
  }
  return true;
}

bool GfGameSalvage::isCameraDive() {
  GimmickCamera *camera = static_cast<GimmickCamera *>(cameraDive.get());
  if (camera != nullptr && camera->isActive) {
    return camera->isLoaded();
  }
  return true;
}

void GfGameSalvage::createModel() {
  if (model == nullptr) {
    model = GfGameEvent::createSalvage();
  }
}

bool GfGameSalvage::isValidModel() {
  if (model != nullptr) {
    return model->isValid();
  }
  return false;
}

void GfGameSalvage::setModelTransform(const mm::Vec3 &position, f32 rotation) {
  if (model != nullptr) {
    model->setTransform(position, rotation);
  }
}

bool GfGameSalvage::isVoiceEnd() {
  if (voice != nullptr) {
    return SCOM_SALVAGE_VOICE::isPlayEnd(voice);
  }
  return true;
}

GfGameSalvage::AnimationType GfGameSalvage::getClimbAnimationType() const { return climbAnimation; }

void GfGameSalvage::playWireStart(f32 time, f32 speed, f32 length) {
  if (model != nullptr) {
    GfGameUtil::startWireWithClose(model->handle, handle, time, speed, length);
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
