#include "event/cam_interface.h"

#include "mm_math/mm_vec3.h"

namespace fw {
enum CAMERA_PRIO : int;
} // namespace fw

namespace event {

static constexpr fw::CAMERA_PRIO CAMERA_PRIO_EVENT = static_cast<fw::CAMERA_PRIO>(15);

CamInterface::CamInterface(fw::CAMERA_TYPE type) : fw::Camera(CAMERA_PRIO_EVENT), type(type), isEnable(false), currentRoll(0.0f), self(this) {
  setLookAt(mm::Vec3(4.0f, 5.0f, 5.0f), mm::Vec3(0.0f, 1.0f, 0.0f), 0.0f);
}

void CamInterface::setEnable(bool isEnable) {
  if (isEnable) {
    if (!this->isEnable) {
      fw::CameraManager *manager = fw::CameraManager::get();
      manager->layers[type].push(self, 0.0f);
    }
    this->isEnable = true;
  } else {
    if (this->isEnable) {
      fw::CameraManager *manager = fw::CameraManager::get();
      manager->layers[type].pop(self, 0.0f);
    }
    this->isEnable = false;
  }
}

void CamInterface::setTargetPos(const mm::Vec3 &position, const mm::Vec3 &target, f32 roll) {
  currentRoll = roll;
  setLookAt(position, target, roll);
}

void CamInterface::setRoll(f32 roll) {
  currentRoll = roll;
  setLookAt(position, target, roll);
}

void CamInterface::setFov(f32 fov) { this->fov = fov; }

void CamInterface::setNearFar(f32 nearClip, f32 farClip) {
  this->nearClip = nearClip;
  this->farClip = farClip;
}

} // namespace event
