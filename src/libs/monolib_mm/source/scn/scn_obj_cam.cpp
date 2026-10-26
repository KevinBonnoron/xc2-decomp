#include "ml/scn.h"
#include "ml/threadval.h"
#include "mm_math/mm_plane.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace ml {
class DebDraw;

const char *ScnObjCam::getName() const { return m_name.c_str(); }

const mm::Plane *ScnObjCam::getPlaneLcl(u32 index, bool isBack) const {
  const RENDER_INFO *info = isBack ? unknown80 : renderInfo;
  return &info->unknown200[index];
}

const mm::Plane *ScnObjCam::getPlaneGbl(u32 index, bool isBack) const {
  const RENDER_INFO *info = isBack ? unknown80 : renderInfo;
  return &info->unknown2c0[index];
}

void ScnObjCam::setRot(const mm::Vec3 &rot) {
  unknown80->unknownf0 = rot;
  updateViewMatrix(false);
}

void ScnObjCam::addRotAtCam(const mm::Vec3 &rot) {
  unknown80->unknownf0 = unknown80->unknownf0 + rot;
  updateViewMatrix(false);
}

void ScnObjCam::renderDebug(DebDraw *debDraw) {}

void ScnObjCam::setCopydataCam(bool isCopydata) {}

template class threadval<ScnObjCam::RENDER_INFO>;

} // namespace ml
