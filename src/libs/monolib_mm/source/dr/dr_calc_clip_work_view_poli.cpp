#include "dr/dr_calc_clip_work_view_poli.h"

namespace ml {

DrCalcClipWorkViewPoli::DrCalcClipWorkViewPoli() { unknown08 = 3; }

DrCalcClipWorkViewPoli::~DrCalcClipWorkViewPoli() {}

void DrCalcClipWorkViewPoli::createLineNormal(mm::Vec3 &normal, const mm::Vec3 &linePoint, const mm::Vec3 &lineDirection, const mm::Vec3 &point) const {
  f32 lengthSquared = lineDirection.x * lineDirection.x + lineDirection.y * lineDirection.y + lineDirection.z * lineDirection.z;
  mm::Vec3 delta = point - linePoint;
  f32 t = (lineDirection.x * delta.x + lineDirection.y * delta.y + lineDirection.z * delta.z) / lengthSquared;
  mm::Vec3 nearest = linePoint + lineDirection * t;
  normal.x = point.x - nearest.x;
  normal.y = point.y - nearest.y;
  normal.z = point.z - nearest.z;
  normal.unknown001();
}

} // namespace ml
