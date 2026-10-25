#include "fw/fw_camera.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace fw {
enum CAMERA_PRIO : int;
struct UpdateInfo;

const mm::mtl::RTTI *Camera::getRTTI() const { return &m_rtti; }

const char *Camera::getName() const { return "Camera"; }

void Camera::onPush() {}

void Camera::onPop() {}

void Camera::onActivate() {}

void Camera::onDeactivate() {}

void Camera::update(const UpdateInfo &info) {}

Camera::Camera(CAMERA_PRIO prio)
    : unknown20(nullptr), unknown28(prio), m_fov(40.0f), unknown30(0.01f), unknown34(40000.0f), unknown40(mm::Vec3::zero), unknown50(mm::Vec3::unitZ), unknowna0(false), unknowna4(0.0f) {
  unknown60 = mm::Mat44::identity;
}

} // namespace fw
