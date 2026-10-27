#include "dr/dr_calc_clip_man.h"

#include "dr/dr_calc_clip_obj.h"
#include "dr/dr_calc_cp_plane_obj.h"

namespace ml {

bool DrCalcClipMan::testObjectClip(const mm::Vec3 &position, f32 radius) {
  for (DrCalcClipObj *object = unknown10; object != nullptr; object = object->unknown08) {
    if (object->testObjectClip(position, radius, unknown70)) {
      return true;
    }
  }
  return false;
}

bool DrCalcClipMan::testPlaneClip(const mm::Vec3 &position, f32 radius) {
  for (DrCalcCpPlaneObj *plane = unknown40; plane != nullptr; plane = plane->unknown08) {
    if (!plane->testClip(position, radius)) {
      return false;
    }
  }
  return true;
}

} // namespace ml
