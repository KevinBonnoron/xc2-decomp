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

} // namespace ml
