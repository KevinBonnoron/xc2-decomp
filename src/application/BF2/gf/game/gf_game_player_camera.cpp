#include "gf/game/gf_game_player_camera.h"

#include "fw/fw_camera.h"
#include "gf/camera/gf_camera_player_target.h"
#include "gf/gf_allocator.h"
#include "mm_mtl/rtti.h"

namespace gf {

constexpr u32 MSG_PC_RESET_CAMERA = 0x1000006;

static PlayerCamera *getPlayerCamera() {
  GfGamePlayerCamera *playerCamera = GfGamePlayerCamera::get();
  if (playerCamera == nullptr) {
    return nullptr;
  }

  fw::Camera *camera = playerCamera->camera.get();
  if (camera == nullptr) {
    return nullptr;
  }

  return mm::mtl::dynamicCast<PlayerCamera>(camera);
}

void GfGamePlayerCamera::build(const GfSetupParam &) {
// __LINE__ of the operator new call changes the instruction order.
#line 29
  GfGamePlayerCamera *playerCamera = new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfGamePlayerCamera();
  playerCamera->setup();
}

void GfGamePlayerCamera::setup() { GfEvent::addEventCallback(this); }

void GfGamePlayerCamera::destroy() {
  GfGamePlayerCamera *playerCamera = get();
  playerCamera->cleanup();
  delete playerCamera;
}

void GfGamePlayerCamera::cleanup() {
  GfEvent::removeEventCallback(this);
  if (target.get() != nullptr) {
    target = nullptr;
    fw::CameraManager *manager = fw::CameraManager::get();
    if (manager != nullptr) {
      manager->target = target;
    }
  }

  if (camera.get() != nullptr) {
    fw::CameraManager *manager = fw::CameraManager::get();
    if (manager != nullptr) {
      manager->layers[0].pop(camera, 0.0f);
    }

    camera = nullptr;
  }
}

void GfGamePlayerCamera::resetCameraForSceneJump() {
  GfGamePlayerCamera *playerCamera = get();
  if (playerCamera == nullptr) {
    return;
  }

  fw::CameraManager *manager = fw::CameraManager::get();
  if (manager == nullptr) {
    return;
  }

  if (playerCamera->camera.get() != nullptr) {
    manager->layers[0].pop(playerCamera->camera, 0.0f);
    playerCamera->camera = nullptr;
  }

  playerCamera->camera = PlayerCamera::create();
  manager->layers[0].push(playerCamera->camera, 0.0f);
}

void GfGamePlayerCamera::resetCamera() {
  PlayerCamera *camera = getPlayerCamera();
  if (camera != nullptr) {
    camera->reset();
  }
}

void GfGamePlayerCamera::requestResetCamera() {
  GfGamePlayerCamera *playerCamera = get();
  if (playerCamera == nullptr) {
    return;
  }

  fw::CameraTarget *target = playerCamera->target.get();
  if (target != nullptr) {
    target->requestResetCamera();
  }
}

void GfGamePlayerCamera::resetCameraClimb(ResetCameraWallTiming timing) {
  PlayerCamera *camera = getPlayerCamera();
  if (camera != nullptr) {
    camera->resetClimb(timing);
  }
}

void GfGamePlayerCamera::resetCameraLoad() {
  PlayerCamera *camera = getPlayerCamera();
  if (camera != nullptr) {
    camera->resetLoad();
  }
}

void GfGamePlayerCamera::resetCameraBattleWarp() {
  PlayerCamera *camera = getPlayerCamera();
  if (camera != nullptr) {
    camera->resetBattleWarp();
  }
}

void GfGamePlayerCamera::setTargetObject(GF_OBJ_HANDLE *handle) {
  PlayerCamera *camera = getPlayerCamera();
  if (camera != nullptr) {
    camera->setTarget(handle);
  }
}

void GfGamePlayerCamera::setTargetPlayer(GF_OBJ_HANDLE *handle) {
  GfGamePlayerCamera *playerCamera = get();
  if (playerCamera == nullptr) {
    return;
  }

  fw::CameraTarget *target = playerCamera->target.get();
  if (target == nullptr) {
    return;
  }

  PlayerCameraTarget *playerTarget = mm::mtl::dynamicCast<PlayerCameraTarget>(target);
  if (playerTarget != nullptr) {
    playerTarget->player = handle;
  }
}

f32 GfGamePlayerCamera::getSaveYaw() {
  PlayerCamera *camera = getPlayerCamera();
  if (camera != nullptr) {
    return camera->getSaveYaw();
  }

  return 0.0f;
}

f32 GfGamePlayerCamera::getSavePitch() {
  PlayerCamera *camera = getPlayerCamera();
  if (camera != nullptr) {
    return camera->getSavePitch();
  }

  return 0.0f;
}

f32 GfGamePlayerCamera::getSaveDistance() {
  PlayerCamera *camera = getPlayerCamera();
  if (camera != nullptr) {
    return camera->getSaveDistance();
  }

  return 6.0f;
}

f32 GfGamePlayerCamera::getSaveHeight() {
  PlayerCamera *camera = getPlayerCamera();
  if (camera != nullptr) {
    return camera->getSaveHeight();
  }

  return 0.0f;
}

u32 GfGamePlayerCamera::getSaveSide() {
  PlayerCamera *camera = getPlayerCamera();
  if (camera != nullptr) {
    return camera->getSaveSide();
  }

  return 1;
}

GfGamePlayerCamera::GfGamePlayerCamera() {}

GfGamePlayerCamera::~GfGamePlayerCamera() {}

void GfGamePlayerCamera::gevPartyMemberOK(bool isOK) {
  if (!isOK) {
    return;
  }

  if (target.get() == nullptr) {
    target = PlayerCameraTarget::create();
    fw::CameraManager *manager = fw::CameraManager::get();
    if (manager != nullptr) {
      manager->target = target;
    }
  }

  if (camera.get() == nullptr) {
    camera = PlayerCamera::create();
    fw::CameraManager *manager = fw::CameraManager::get();
    if (manager != nullptr) {
      manager->layers[0].push(camera, 0.0f);
    }
  }
}

bool GfGamePlayerCamera::recieveMessage(fw::MessageObject *sender, fw::Message &message) {
  if (message.id == MSG_PC_RESET_CAMERA) {
    procMsgPcResetCamera(sender, static_cast<MsgPcResetCamera &>(message));
    return true;
  }

  return false;
}

void GfGamePlayerCamera::procMsgPcResetCamera(fw::MessageObject *, MsgPcResetCamera &) { resetCamera(); }

} // namespace gf
