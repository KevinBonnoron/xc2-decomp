#include "event/cam_interface.h"

#include "mm_math/mm_vec3.h"

namespace fw {
enum CAMERA_PRIO : int;
} // namespace fw

namespace event {

static constexpr fw::CAMERA_PRIO CAMERA_PRIO_EVENT = static_cast<fw::CAMERA_PRIO>(15);

CamInterface::CamInterface(fw::CAMERA_TYPE type) : fw::Camera(CAMERA_PRIO_EVENT), unknowna8(type), unknownac(false), unknownb0(0.0f), unknownb8(this) {
  setLookAt(mm::Vec3(4.0f, 5.0f, 5.0f), mm::Vec3(0.0f, 1.0f, 0.0f), 0.0f);
}

void CamInterface::setEnable(bool isEnable) {
  if (isEnable) {
    if (!this->unknownac) {
      fw::CameraManager *manager = fw::CameraManager::get();
      manager->unknown20[unknowna8].push(unknownb8, 0.0f);
    }
    this->unknownac = true;
  } else {
    if (this->unknownac) {
      fw::CameraManager *manager = fw::CameraManager::get();
      manager->unknown20[unknowna8].pop(unknownb8, 0.0f);
    }
    this->unknownac = false;
  }
}

void CamInterface::setTargetPos(const mm::Vec3 &position, const mm::Vec3 &target, f32 roll) {
  unknownb0 = roll;
  setLookAt(position, target, roll);
}

void CamInterface::setRoll(f32 roll) {
  unknownb0 = roll;
  setLookAt(unknown40, unknown50, roll);
}

void CamInterface::setFov(f32 fov) { this->m_fov = fov; }

void CamInterface::setNearFar(f32 nearClip, f32 farClip) {
  this->unknown30 = nearClip;
  this->unknown34 = farClip;
}

} // namespace event
