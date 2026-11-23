#include "gf/menu/model_view/gf_menu_model_view_camera.h"

#include "mm_math/mm_quat.h"

namespace fw {
enum CAMERA_PRIO : int;
} // namespace fw

namespace gf {

// Inferred role: camera priority of the model view; original name unknown.
static constexpr fw::CAMERA_PRIO CAMERA_PRIO_UNKNOWN_55 = static_cast<fw::CAMERA_PRIO>(55);

GfMenuModelViewCamera::GfMenuModelViewCamera(const GimmickCameraParams::Param &param) : fw::Camera(CAMERA_PRIO_UNKNOWN_55) {
  unknownb0 = mm::Vec3(param.unknown00, param.unknown04, param.unknown08);
  unknownc0 = mm::Vec3(param.unknown0c, param.unknown10, param.unknown14);
  updateLookAt();
}

// Game address 0x71003e6914 (219 instructions). Looks from the position along the forward axis turned by the euler angles of the rotation, like
// GfMenuBladeCreateCamera::updateLookAt (the same quaternion mm::unknown005 and the in-place rotation mm::unknown010, each measured there). Evidence for the rest:
// - The identity quaternion is copied into a local before the euler quaternion is built (its loads come before the first sinf call).
// - `position` is a copy of the member whose three loads come before its three stores (ldp, ldr, stp, str at the top): the copy constructor gives ldp, stp, ldr, str.
//   The rotation is read from the member: a copy of it also gives 219 instructions but loads it before the identity quaternion.
void GfMenuModelViewCamera::updateLookAt() {
  mm::Vec3 position(unknownb0.x, unknownb0.y, unknownb0.z);
  mm::Vec3 target(0.0f, 0.0f, 1.0f);
  mm::Quat current = mm::Quat::identity;
  mm::Quat quat = mm::Quat::mul(current, mm::unknown005(unknownc0));
  mm::unknown010(quat, target);
  target += position;
  setLookAt(position, target, 0.0f);
}

GfMenuModelViewCamera::~GfMenuModelViewCamera() { ; }

void GfMenuModelViewCamera::setPos(const mm::Vec3 &position) {
  unknownb0 = position;
  updateLookAt();
}

void GfMenuModelViewCamera::setRotY(f32 rotation) {
  unknownc0.y = rotation;
  updateLookAt();
}

const mm::mtl::RTTI *GfMenuModelViewCamera::getRTTI() const { return &m_rtti; }

const char *GfMenuModelViewCamera::getName() const { return "GfMenuModelViewCamera"; }

} // namespace gf
