#include "dr/dr_calc_clip_work_cone.h"

#include <math.h>

namespace ml {

DrCalcClipWorkCone::DrCalcClipWorkCone() { unknown08 = 2; }

DrCalcClipWorkCone::~DrCalcClipWorkCone() {}

void DrCalcClipWorkCone::setConeWork(const mm::Vec3 &position, const mm::Vec3 &direction, f32 angle, f32 length) {
  unknown10 = position;
  unknown20 = direction;
  unknown30 = direction * length;
  unknown50 = unknown20.x * unknown10.x + unknown20.y * unknown10.y + unknown20.z * unknown10.z;
  unknown44 = angle;
  unknown4c = sinf(angle);
  unknown48 = cosf(angle * 0.5f);
  unknown40 = length;
}

bool DrCalcClipWorkCone::clipTest(const mm::Vec3 &position, f32 radius) const {
  mm::Vec3 delta = position - unknown10;
  f32 range = unknown40 + radius;
  if (delta.x * delta.x + delta.y * delta.y + delta.z * delta.z > range * range) {
    return false;
  }
  if (-(position.x * unknown20.x + position.y * unknown20.y + position.z * unknown20.z - unknown50) > radius) {
    return false;
  }
  mm::Vec3 direction = delta;
  direction.unknown001();
  if (direction.x * unknown20.x + direction.y * unknown20.y + direction.z * unknown20.z - unknown48 > 0.0f) {
    return true;
  }
  mm::Vec3 side(delta.y * unknown20.z - delta.z * unknown20.y, delta.z * unknown20.x - delta.x * unknown20.z, delta.x * unknown20.y - delta.y * unknown20.x);
  mm::Vec3 up(unknown20.y * side.z - unknown20.z * side.y, unknown20.z * side.x - unknown20.x * side.z, unknown20.x * side.y - unknown20.y * side.x);
  up.unknown001();
  up *= unknown4c;
  mm::Vec3 edge = unknown20 + up;
  mm::Vec3 normal(side.z * edge.y - side.y * edge.z, side.x * edge.z - side.z * edge.x, side.y * edge.x - side.x * edge.y);
  normal.unknown001();
  return normal.x * position.x + normal.y * position.y + normal.z * position.z - (normal.x * unknown10.x + normal.y * unknown10.y + normal.z * unknown10.z) <= radius;
}

int DrCalcClipWorkCone::clipTypeTest(const mm::Vec3 &position, f32 radius) const {
  mm::Vec3 delta = position - unknown10;
  f32 range = unknown40 + radius;
  if (delta.x * delta.x + delta.y * delta.y + delta.z * delta.z > range * range) {
    return false;
  }
  if (-(position.x * unknown20.x + position.y * unknown20.y + position.z * unknown20.z - unknown50) > radius) {
    return false;
  }
  mm::Vec3 direction = delta;
  direction.unknown001();
  if (direction.x * unknown20.x + direction.y * unknown20.y + direction.z * unknown20.z - unknown48 > 0.0f) {
    return true;
  }
  mm::Vec3 side(delta.y * unknown20.z - delta.z * unknown20.y, delta.z * unknown20.x - delta.x * unknown20.z, delta.x * unknown20.y - delta.y * unknown20.x);
  mm::Vec3 up(unknown20.y * side.z - unknown20.z * side.y, unknown20.z * side.x - unknown20.x * side.z, unknown20.x * side.y - unknown20.y * side.x);
  up.unknown001();
  up *= unknown4c;
  mm::Vec3 edge = unknown20 + up;
  mm::Vec3 normal(side.z * edge.y - side.y * edge.z, side.x * edge.z - side.z * edge.x, side.y * edge.x - side.x * edge.y);
  normal.unknown001();
  return normal.x * position.x + normal.y * position.y + normal.z * position.z - (normal.x * unknown10.x + normal.y * unknown10.y + normal.z * unknown10.z) <= radius;
}

void DrCalcClipWorkCone::debugDraw() {}

} // namespace ml
