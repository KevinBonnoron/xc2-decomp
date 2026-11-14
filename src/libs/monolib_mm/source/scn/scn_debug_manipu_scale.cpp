#include "scn/scn_debug_manipu_scale.h"

#include "mm_math/mm_vec3.h"

namespace ml {

ScnDebugManipuScale::ScnDebugManipuScale(Scn *scn, const mm::Mat44 *matrix, const mm::Vec3 *scale) : ScnDebugManipuObj(SCNMANIPU_UNKNOWN_2, scn, matrix, scale) {
  unknown380 = 0;
  unknown388 = 7;
  unknown390 = mm::Vec3::zero;
}

ScnDebugManipuScale::~ScnDebugManipuScale() {}

void ScnDebugManipuScale::setRadius(f32 radius) {}

bool ScnDebugManipuScale::checkMouseButtonUp(EventView *event) {
  if (!unknown20) {
    return false;
  }
  unknown388 = 7;
  if (unknown18 != 0) {
    unknown18 = 0;
    return true;
  }
  return false;
}

void ScnDebugManipuScale::update() {}

} // namespace ml
