#include "event/outsider_field.h"

namespace event {

OutsiderField::OutsiderField() { clear(); }

void OutsiderField::clear() {
  unknown00 = TYPE_CIRCLE;
  unknown10 = mm::Vec3::zero;
  unknown20 = 0.0f;
  unknown30 = mm::Vec3::zero;
  unknown40 = 0.0f;
}

void OutsiderField::setField(TYPE type, const mm::Vec3 &pos, f32 radius) {
  unknown00 = type;
  unknown10 = pos;
  unknown20 = radius;
}

bool OutsiderField::isInside(const mm::Vec3 &pos) const {
  if (unknown00 < TYPE_CIRCLE) {
    return false;
  }
  if (unknown40 <= 0.0f) {
    return false;
  }
  f32 distanceX = unknown30.x - pos.x;
  f32 distanceZ = unknown30.z - pos.z;
  f32 squaredX = distanceX * distanceX;
  f32 squaredZ = distanceZ * distanceZ;
  f32 squaredRadius = unknown40 * unknown40;
  return squaredX + squaredZ < squaredRadius;
}

} // namespace event
