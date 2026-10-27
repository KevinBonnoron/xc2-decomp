#include "idcoli/idcoli.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace idcoli {

void IDColiMove::setShapeParms(f32 radius, f32 height) {
  unknown1b8 = radius;
  unknown1bc = height;
}

void IDColiMove::setAngle(f32 angle) { m_angle = angle; }

void IDColiMove::setFloor(f32 floor) { m_floor = floor; }

void IDColiMove::setDown(f32 down) { m_down = down; }

void IDColiMove::setAccuracy(bool accuracy) { m_accuracy = accuracy; }

void IDColiMove::calcVecDeceleration(f32 &value, mm::Vec3 vector) {
  if (unknown1f3) {
    f32 dot = unknown1a0.x * vector.x + unknown1a0.z * vector.z;
    if (dot > value) {
      value = dot;
    }
  }
}

} // namespace idcoli
