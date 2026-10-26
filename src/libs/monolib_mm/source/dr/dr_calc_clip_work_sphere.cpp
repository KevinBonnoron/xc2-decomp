#include "dr/dr_calc_clip_work_sphere.h"

namespace ml {

DrCalcClipWorkSphere::DrCalcClipWorkSphere() { unknown08 = 1; }

DrCalcClipWorkSphere::~DrCalcClipWorkSphere() {}

void DrCalcClipWorkSphere::setSphereWork(const mm::Vec3 &position, f32 radius, int sign) {
  unknown10 = position;
  unknown30 = radius;
  unknown20.x = 0.0f;
  unknown20.y = 0.0f;
  if (sign != 0) {
    unknown20.z = 1.0f;
  } else {
    unknown20.z = -1.0f;
  }
}

bool DrCalcClipWorkSphere::clipTest(const mm::Vec3 &position, f32 radius) const {
  f32 dx = position.x - unknown10.x;
  f32 dy = position.y - unknown10.y;
  f32 dz = position.z - unknown10.z;
  f32 range = unknown30 + radius;
  return dx * dx + dy * dy + dz * dz <= range * range;
}

int DrCalcClipWorkSphere::clipTypeTest(const mm::Vec3 &position, f32 radius) const {
  f32 dx = position.x - unknown10.x;
  f32 dy = position.y - unknown10.y;
  f32 dz = position.z - unknown10.z;
  f32 range = unknown30 + radius;
  return dx * dx + dy * dy + dz * dz <= range * range;
}

void DrCalcClipWorkSphere::debugDraw() {}

} // namespace ml
