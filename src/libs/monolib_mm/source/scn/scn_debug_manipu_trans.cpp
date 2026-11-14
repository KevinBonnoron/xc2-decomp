#include "scn/scn_debug_manipu_trans.h"

namespace ml {

ScnDebugManipuTrans::ScnDebugManipuTrans(Scn *scn, const mm::Mat44 *matrix, const mm::Vec3 *scale) : ScnDebugManipuObj(SCNMANIPU_UNKNOWN_0, scn, matrix, scale) {
  unknown380 = 0;
  unknown388 = 7;
}

ScnDebugManipuTrans::~ScnDebugManipuTrans() {}

void ScnDebugManipuTrans::setRadius(f32 radius) {}

bool ScnDebugManipuTrans::checkMouseButtonUp(EventView *event) {
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

void ScnDebugManipuTrans::update() {}

} // namespace ml
