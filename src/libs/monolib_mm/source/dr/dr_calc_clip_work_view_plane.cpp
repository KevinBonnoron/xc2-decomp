#include "dr/dr_calc_clip_work_view_plane.h"

#include "mm_math/mm_vec3.h"

namespace ml {

DrCalcClipWorkViewPlane::DrCalcClipWorkViewPlane() { unknown08 = 0; }

DrCalcClipWorkViewPlane::~DrCalcClipWorkViewPlane() {}

bool DrCalcClipWorkViewPlane::clipTest(const mm::Vec3 &position, f32 radius) const {
  for (int i = 0; i < 5; i++) {
    if (position.x * unknown10[i].unknown00.x + position.y * unknown10[i].unknown00.y + position.z * unknown10[i].unknown00.z + unknown10[i].unknown10 > radius) {
      return false;
    }
  }
  return true;
}

bool DrCalcClipWorkViewPlane::clipTest(const f32 *min, const f32 *max) const {
  for (int i = 0; i < 5; i++) {
    const unknown001 &plane = unknown10[i];
    f32 sumX = (min[0] + max[0]) * plane.unknown00.x;
    f32 sumY = (min[1] + max[1]) * plane.unknown00.y;
    f32 sumZ = (min[2] + max[2]) * plane.unknown00.z;
    f32 diffX = (min[0] - max[0]) * plane.unknown00.x;
    f32 diffY = (min[1] - max[1]) * plane.unknown00.y;
    f32 diffZ = (min[2] - max[2]) * plane.unknown00.z;
    if (!(((sumX + sumY) + sumZ) + plane.unknown10 < 0.0f || ((sumX + sumY) + diffZ) + plane.unknown10 < 0.0f || ((diffX + sumY) + sumZ) + plane.unknown10 < 0.0f ||
          ((diffX + sumY) + diffZ) + plane.unknown10 < 0.0f || ((sumX + diffY) + sumZ) + plane.unknown10 < 0.0f || ((sumX + diffY) + diffZ) + plane.unknown10 < 0.0f ||
          ((diffX + diffY) + sumZ) + plane.unknown10 < 0.0f || ((diffX + diffY) + diffZ) + plane.unknown10 < 0.0f)) {
      return false;
    }
  }
  return true;
}

bool DrCalcClipWorkViewPlane::clipTest(const mm::Vec3 *points, int count) const {
  for (int i = 0; i < 5; i++) {
    const unknown001 &plane = unknown10[i];
    bool inside = false;
    for (int j = 0; j < count; j++) {
      if (points[j].x * plane.unknown00.x + points[j].y * plane.unknown00.y + points[j].z * plane.unknown00.z + plane.unknown10 < 0.0f) {
        inside = true;
        break;
      }
    }
    if (!inside) {
      return false;
    }
  }
  return true;
}

} // namespace ml
