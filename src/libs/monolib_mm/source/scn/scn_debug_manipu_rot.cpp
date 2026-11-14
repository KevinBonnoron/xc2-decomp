#include "scn/scn_debug_manipu_rot.h"

namespace ml {

ScnDebugManipuRot::ScnDebugManipuRot(Scn *scn, const mm::Mat44 *matrix, const mm::Vec3 *scale) : ScnDebugManipuObj(SCNMANIPU_UNKNOWN_1, scn, matrix, scale) {
  unknown970 = 0;
  unknown990 = 70.0f;
  unknown994 = 80.0f;
}

ScnDebugManipuRot::~ScnDebugManipuRot() {}

void ScnDebugManipuRot::setRadius(f32 radius) {
  if (radius > 0.0f) {
    unknown990 = radius;
    unknown994 = radius + 10.0f;
  } else {
    unknown990 = 70.0f;
    unknown994 = 80.0f;
  }
}

bool ScnDebugManipuRot::checkMouseButtonUp(EventView *event) {
  if (!unknown20) {
    return false;
  }
  if (unknown18 != 0) {
    unknown18 = 0;
    return true;
  }
  return false;
}

void ScnDebugManipuRot::update() {}

} // namespace ml
