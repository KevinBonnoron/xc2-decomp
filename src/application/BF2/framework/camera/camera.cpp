#include "fw/fw_camera.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"

namespace fw {
enum CAMERA_PRIO : int;

Camera::Camera(CAMERA_PRIO prio)
    : layer(nullptr), prio(prio), fov(40.0f), nearClip(0.01f), farClip(40000.0f), position(mm::Vec3::zero), target(mm::Vec3::unitZ), isActive(false),
      roll(0.0f) {
  viewMatrix = mm::Mat44::identity;
}

} // namespace fw
