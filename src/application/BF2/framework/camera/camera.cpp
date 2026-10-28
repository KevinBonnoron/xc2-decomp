#include "fw/fw_camera.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/intrusive_ptr.h" // IWYU pragma: keep
#include "mm_mtl/vector.h"        // IWYU pragma: keep

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

template void mm::mtl::Vector<mm::mtl::IntrusivePtr<fw::Camera>>::destroy();
template void mm::mtl::Vector<mm::mtl::IntrusivePtr<fw::Camera>>::expand(size_t, size_t);
template void mm::mtl::Vector<mm::mtl::IntrusivePtr<fw::Camera>>::push_back(const mm::mtl::IntrusivePtr<fw::Camera> &);
