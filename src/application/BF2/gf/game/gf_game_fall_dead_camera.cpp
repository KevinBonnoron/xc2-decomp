#include "gf/game/gf_game_fall_dead_camera.h"

#include "gf/camera/gf_camera_player_target.h"
#include "gf/gf_info.h"

namespace fw {
enum CAMERA_PRIO : int;
} // namespace fw

namespace gf {

static constexpr fw::CAMERA_PRIO CAMERA_PRIO_FALL_DEAD = static_cast<fw::CAMERA_PRIO>(55);

GfGameFallDeadCamera::GfGameFallDeadCamera() : fw::Camera(CAMERA_PRIO_FALL_DEAD), unknownb0(mm::Vec3::zero) {}

GfGameFallDeadCamera::~GfGameFallDeadCamera() {}

void GfGameFallDeadCamera::onActivate() {
  PlayerCameraTarget *target = PlayerCameraTarget::get();
  if (target != nullptr) {
    unknownb0 = GfInfo::m_camTgt - target->unknown20;
  }
  unknownd0 = GfInfo::m_camTgt;
  unknownc0 = GfInfo::m_camPos;
  m_fov = GfInfo::m_camFov;
  setLookAt(unknownc0, unknownd0, 0.0f);
}

void GfGameFallDeadCamera::update(const fw::UpdateInfo &info) {
  PlayerCameraTarget *target = PlayerCameraTarget::get();
  if (target != nullptr) {
    unknownd0 = target->unknown20 + unknownb0;
  }
  setLookAt(unknownc0, unknownd0, 0.0f);
}

} // namespace gf
