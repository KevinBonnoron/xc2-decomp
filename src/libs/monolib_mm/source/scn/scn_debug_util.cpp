#include "ml/scn_debug_util.h"

#include "ml/attr_transform.h"
#include "ml/cache_draw.h"
#include "ml/scn.h"
#include "ml/scn_cam_util.h"
#include "ml/scn_util.h"
#include "ml/threadval.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace ml {

bool ScnDebugUtil::renderGuide(DebDraw *debDraw, const ScnObjCam *cam, const mm::Vec3 &position, int offset, int length, mm::Vec3 *screen) {
  mm::Vec3 pos;
  if (!ScnCamUtil::getScreenPos(pos, cam, false, position)) {
    return false;
  }
  if (screen != nullptr) {
    *screen = pos;
  }
  debDraw->setOrtho();
  debDraw->setZComp(false);
  debDraw->begin(3, 3);
  debDraw->add(pos);
  f32 size = offset;
  debDraw->add(mm::Vec3(size, -size, 0.0f) + pos);
  debDraw->add(mm::Vec3(offset + length, -size, 0.0f) + pos);
  debDraw->end();
  debDraw->setZComp(true);
  return true;
}

void ScnDebugUtil::renderCamera(DebDraw *debDraw, ScnObjCam *cam, const mm::Mat44 *matrix) {
  mm::Mat44 camMatrix;
  if (matrix == nullptr) {
    camMatrix = cam->unknown70.m_front->unknown00.unknown70;
    matrix = &camMatrix;
  }
  ScnUtil::setPerspective(cam->m_scn, debDraw, nullptr);
  debDraw->setMatrix(*matrix);
  debDraw->setCol(0.1f, 0.5f, 0.0f, 1.0f);
  debDraw->renderCamera();
}

void ScnDebugUtil::renderSekeleton(DebDraw *debDraw, const ScnObjCam *cam, ScnObjModel *model) {}

} // namespace ml
