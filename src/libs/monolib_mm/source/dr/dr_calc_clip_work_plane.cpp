#include "dr/dr_calc_clip_work_plane.h"

#include "mm_math/mm_vec3.h"

namespace ml {

DrCalcClipWorkPlane::DrCalcClipWorkPlane() { unknown08 = 0; }

DrCalcClipWorkPlane::~DrCalcClipWorkPlane() {}

bool DrCalcClipWorkPlane::clipTest(const mm::Vec3 &position, f32 radius) const {
  for (int i = 0; i < 6; i++) {
    if (position.x * unknown10[i].unknown00.x + position.y * unknown10[i].unknown00.y + position.z * unknown10[i].unknown00.z + unknown10[i].unknown10 > radius) {
      return false;
    }
  }
  return true;
}

} // namespace ml
