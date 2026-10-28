#include "ml/scn_cam_util.h"

#include "ml/dev_graph.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace ml {

bool ScnCamUtil::getScreenPos(mm::Vec3 &screen, const ScnObjCam *cam, const mm::Vec3 &position) { return getScreenPos(screen, cam, false, position); }

bool ScnCamUtil::isDispScreen(const ScnObjCam *cam, const mm::Vec3 &position) {
  mm::Vec3 screen;
  if (!getScreenPos(screen, cam, false, position)) {
    return false;
  }
  f32 x = screen.x;
  if (x < 0.0f || static_cast<f32>(DevGraph::getRootWidth()) < x) {
    return false;
  }
  f32 y = screen.y;
  if (y < 0.0f) {
    return false;
  }
  return !(static_cast<f32>(DevGraph::getRootHeight()) < y);
}

} // namespace ml
