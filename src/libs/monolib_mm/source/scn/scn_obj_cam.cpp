#include <math.h>

#include "ml/dev_graph.h"
#include "ml/scn.h"
#include "ml/threadval.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_plane.h"
#include "mm_math/mm_rect.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixstr.h"
#include "scn/scn_render_dr_sys.h"
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

void ScnObjCam::setPos(const mm::Vec3 &pos) {
  RENDER_INFO *info = unknown80;
  f32 dx = info->m_targetPos.x - pos.x;
  f32 dy = info->m_targetPos.y - pos.y;
  f32 dz = info->m_targetPos.z - pos.z;
  info->m_targetDist = sqrtf(dx * dx + dy * dy + dz * dz);
  info->m_pos = pos;
  updateViewMatrix(true);
}

void ScnObjCam::setTargetPos(const mm::Vec3 &pos) {
  RENDER_INFO *info = unknown80;
  info->m_targetPos = pos;
  f32 dx = pos.x - info->m_pos.x;
  f32 dy = pos.y - info->m_pos.y;
  f32 dz = pos.z - info->m_pos.z;
  info->m_targetDist = sqrtf(dx * dx + dy * dy + dz * dz);
  info->unknownf0.y = -atan2f(dx, -dz);
  info->unknownf0.x = atan2f(dy, sqrtf(dx * dx + dz * dz));
  updateViewMatrix(true);
}

void ScnObjCam::addPosTarget(const mm::Vec3 &pos) {
  RENDER_INFO *info = unknown80;
  info->m_targetPos += pos;
  info->m_pos = info->m_pos + pos;
  updateViewMatrix(true);
}

void ScnObjCam::addTrack(const mm::Vec3 &pos) {
  RENDER_INFO *info = unknown80;
  info->m_pos = info->m_pos + pos;
  info->m_targetPos += pos;
  updateViewMatrix(true);
}

void ScnObjCam::setDist(const f32 &dist) {
  RENDER_INFO *info = unknown80;
  info->m_targetDist = dist;
  const mm::Mat44 &matrix = info->unknown70;
  mm::Vec3 pos;
  pos.x = matrix.rows[0][0] * 0.0f + matrix.rows[1][0] * 0.0f + dist * matrix.rows[2][0];
  pos.y = matrix.rows[0][1] * 0.0f + matrix.rows[1][1] * 0.0f + dist * matrix.rows[2][1];
  pos.z = matrix.rows[0][2] * 0.0f + matrix.rows[1][2] * 0.0f + dist * matrix.rows[2][2];
  info->m_pos = pos + info->m_targetPos;
  updateViewMatrix(true);
}

void ScnObjCam::apply() {
  RENDER_INFO *info = renderInfo;
  const mm::Rect<int> &viewport = DevGraph::getViewport();
  if (viewport.width == 0 || viewport.height == 0) {
    info->unknown1f0 = 1.0f;
  } else {
    info->unknown1f0 = static_cast<f32>(viewport.width) / static_cast<f32>(viewport.height);
  }
  ScnRenderDrSys *render = unknown08->unknown38;
  if (render != nullptr) {
    render->applyCamera(this);
  }
}

void ScnObjCam::updateFovNearFar() {
  RENDER_INFO *info = unknown80;
  f32 inverseTan = 1.0f / tanf(info->unknown1e8 * 0.017453292f * 0.5f);
  info->unknown1ec = inverseTan;
  f32 edge = -info->unknown1f4 / inverseTan;
  info->unknown150[0] = edge;
  info->unknown150[1] = -edge;
  info->unknown150[2] = edge * info->unknown1f0;
  info->unknown150[3] = info->unknown1f0 * -edge;
}

void ScnObjCam::setFovDefault() {
  unknown80->unknown1e8 = 40.0f;
  updateFovNearFar();
}

void ScnObjCam::renderDebug(DebDraw *debDraw) {}

void ScnObjCam::setCopydataCam(bool isCopydata) {}

template class threadval<ScnObjCam::RENDER_INFO>;

} // namespace ml
