#include "gf/menu/object/gf_menu_blade_create_camera.h"

namespace fw {
enum CAMERA_PRIO : int;
} // namespace fw

namespace gf {

// Inferred role: camera priority of the blade creation; original name unknown.
static constexpr fw::CAMERA_PRIO CAMERA_PRIO_UNKNOWN_55 = static_cast<fw::CAMERA_PRIO>(55);

GfMenuBladeCreateCamera::GfMenuBladeCreateCamera()
    : fw::Camera(CAMERA_PRIO_UNKNOWN_55), unknownf0(0.0f), unknownf4(0.0f), m_rotOffsetY(0.0f), unknownfc(0.0f), unknown100(0.0f), unknown104(0.0f), unknown108(0) {}

GfMenuBladeCreateCamera::~GfMenuBladeCreateCamera() {}

const mm::mtl::RTTI *GfMenuBladeCreateCamera::getRTTI() const { return &m_rtti; }

const char *GfMenuBladeCreateCamera::getName() const { return "GfMenuBladeCreateCamera"; }

void GfMenuBladeCreateCamera::setRotY(f32 rot, u32 direction, f32 duration) {
  f32 current = unknownfc;
  if (direction == 0 && rot - current > 0.0f) {
    rot += -6.2831855f;
  } else if (direction == 1 && rot - current < 0.0f) {
    if (current + rot < 6.2831855f) {
      rot = 6.2831855f - rot;
    } else {
      rot += 6.2831855f;
    }
  }
  unknown100 = rot;
  unknown108 = direction;
  unknownf0 = duration;
  unknownf4 = 0.0f;
  if (duration == 0.0f) {
    unknownfc = rot;
    current = rot;
  }
  unknown104 = current;
}

void GfMenuBladeCreateCamera::setRotOffsetY(f32 offset) { m_rotOffsetY = offset; }

void GfMenuBladeCreateCamera::setDefault(const mm::Vec3 &position, const mm::Vec3 &target) {
  unknownb0 = position;
  unknownc0 = target;
}

void GfMenuBladeCreateCamera::getDefault(mm::Vec3 &position, mm::Vec3 &target) {
  position = unknownb0;
  target = unknownc0;
}

void GfMenuBladeCreateCamera::getCurrent(mm::Vec3 &position, mm::Vec3 &target) {
  position = unknownd0;
  target = unknowne0;
}

} // namespace gf
