#include "gf/game/gf_game_fall_dead_camera.h"

#include "fw/fw_transform.h"
#include "gf/camera/gf_camera_player_target.h"
#include "gf/gf_info.h"

namespace fw {
enum CAMERA_PRIO : int;
} // namespace fw

namespace gf {

static constexpr fw::CAMERA_PRIO CAMERA_PRIO_UNKNOWN_55 = static_cast<fw::CAMERA_PRIO>(55); // Inferred role: camera prio fall dead; original name unknown.

GfGameFallDeadCamera::GfGameFallDeadCamera() : fw::Camera(CAMERA_PRIO_UNKNOWN_55), unknownb0(mm::Vec3::zero) {}

GfGameFallDeadCamera::~GfGameFallDeadCamera() {}

void GfGameFallDeadCamera::onActivate() {
  PlayerCameraTarget *target = PlayerCameraTarget::get();
  if (target != nullptr) {
    unknownb0 = GfInfo::m_camTgt - target->unknown20.unknown00;
  }
  unknownd0 = GfInfo::m_camTgt;
  unknownc0 = GfInfo::m_camPos;
  m_fov = GfInfo::m_camFov;
  setLookAt(unknownc0, unknownd0, 0.0f);
}

void GfGameFallDeadCamera::update(const fw::UpdateInfo &info) {
  PlayerCameraTarget *target = PlayerCameraTarget::get();
  if (target != nullptr) {
    unknownd0 = target->unknown20.unknown00 + unknownb0;
  }
  setLookAt(unknownc0, unknownd0, 0.0f);
}

} // namespace gf
