#include <math.h>
#include <string.h>

#include "ml/attr_transform.h"
#include "ml/dev_graph.h"
#include "ml/scn.h"
#include "ml/scn_obj.h"
#include "ml/threadval.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_plane.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "mm_math/mm_sphere.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixstr.h"
#include "scn/scn_render_dr_sys.h"
#include "types.h"

namespace ml {

static const mm::Vec3 unknown002(0.0f, 5.0f, 20.0f); // Inferred role: default camera position; original name unknown.
static const mm::Vec3 unknown003(0.0f, 0.0f, 0.0f);  // Inferred role: default camera target; original name unknown.

const char *ScnObjCam::getName() const { return m_name.c_str(); }

const mm::Plane *ScnObjCam::getPlaneLcl(u32 index, bool isBack) const {
  const RENDER_INFO *info = isBack ? unknown70.m_back : unknown70.m_front;
  return &info->unknown200[index];
}

const mm::Plane *ScnObjCam::getPlaneGbl(u32 index, bool isBack) const {
  const RENDER_INFO *info = isBack ? unknown70.m_back : unknown70.m_front;
  return &info->unknown2c0[index];
}

void ScnObjCam::setRot(const mm::Vec3 &rot) {
  unknown70.m_back->unknown00.unknownf0 = rot;
  updateViewMatrix(false);
}

void ScnObjCam::addRotAtCam(const mm::Vec3 &rot) {
  unknown70.m_back->unknown00.unknownf0 = unknown70.m_back->unknown00.unknownf0 + rot;
  updateViewMatrix(false);
}

void ScnObjCam::setPos(const mm::Vec3 &pos) {
  RENDER_INFO *info = unknown70.m_back;
  f32 dx = info->m_targetPos.x - pos.x;
  f32 dy = info->m_targetPos.y - pos.y;
  f32 dz = info->m_targetPos.z - pos.z;
  info->m_targetDist = sqrtf(dx * dx + dy * dy + dz * dz);
  info->unknown00.unknown00 = pos;
  updateViewMatrix(true);
}

void ScnObjCam::setTargetPos(const mm::Vec3 &pos) {
  RENDER_INFO *info = unknown70.m_back;
  info->m_targetPos = pos;
  f32 dx = pos.x - info->unknown00.unknown00.x;
  f32 dy = pos.y - info->unknown00.unknown00.y;
  f32 dz = pos.z - info->unknown00.unknown00.z;
  info->m_targetDist = sqrtf(dx * dx + dy * dy + dz * dz);
  info->unknown00.unknownf0.y = -atan2f(dx, -dz);
  info->unknown00.unknownf0.x = atan2f(dy, sqrtf(dx * dx + dz * dz));
  updateViewMatrix(true);
}

void ScnObjCam::addPosTarget(const mm::Vec3 &pos) {
  RENDER_INFO *info = unknown70.m_back;
  info->m_targetPos += pos;
  info->unknown00.unknown00 = info->unknown00.unknown00 + pos;
  updateViewMatrix(true);
}

void ScnObjCam::addTrack(const mm::Vec3 &pos) {
  RENDER_INFO *info = unknown70.m_back;
  info->unknown00.unknown00 = info->unknown00.unknown00 + pos;
  info->m_targetPos += pos;
  updateViewMatrix(true);
}

void ScnObjCam::setDist(const f32 &dist) {
  RENDER_INFO *info = unknown70.m_back;
  info->m_targetDist = dist;
  const mm::Mat44 &matrix = info->unknown00.unknown70;
  mm::Vec3 pos;
  pos.x = matrix.rows[0][0] * 0.0f + matrix.rows[1][0] * 0.0f + dist * matrix.rows[2][0];
  pos.y = matrix.rows[0][1] * 0.0f + matrix.rows[1][1] * 0.0f + dist * matrix.rows[2][1];
  pos.z = matrix.rows[0][2] * 0.0f + matrix.rows[1][2] * 0.0f + dist * matrix.rows[2][2];
  info->unknown00.unknown00 = pos + info->m_targetPos;
  updateViewMatrix(true);
}

void ScnObjCam::apply() {
  RENDER_INFO *info = unknown70.m_front;
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
  RENDER_INFO *info = unknown70.m_back;
  f32 inverseTan = 1.0f / tanf(info->unknown1e8 * 0.017453292f * 0.5f);
  info->unknown1ec = inverseTan;
  f32 edge = -info->unknown1f4 / inverseTan;
  info->unknown150[0] = edge;
  info->unknown150[1] = -edge;
  info->unknown150[2] = edge * info->unknown1f0;
  info->unknown150[3] = info->unknown1f0 * -edge;
}

void ScnObjCam::setFovDefault() {
  unknown70.m_back->unknown1e8 = 40.0f;
  updateFovNearFar();
}

void ScnObjCam::renderDebug(DebDraw *debDraw) {}

void ScnObjCam::setCopydataCam(bool isCopydata) {}

ScnObjCam::ScnObjCam(Scn *scn, const char *name) : ScnObj(scn, TYPE_UNKNOWN_2), m_info(-1), m_name(name), unknown5c(false), unknown60(nullptr) {
  infoInit(unknown70.m_back);
  infoInit(unknown70.m_front);
  updateViewMatrix(false);
  DevGraph::getPers(unknown70.m_back->unknown1a0, unknown70.m_front->unknown1e8, unknown70.m_front->unknown1f4, unknown70.m_front->unknown1f8);
  setDefault();
  memcpy(unknown70.m_front, unknown70.m_back, sizeof(RENDER_INFO));
  unknown70.m_flags.set(threadval<RENDER_INFO>::FLAG_UNKNOWN_0);
}

ScnObjCam::~ScnObjCam() {
  if (unknown60 != nullptr) {
    delete unknown60;
    unknown60 = nullptr;
  }
}

void ScnObjCam::update() {
  if (unknown60 != nullptr) {
    unknown60->unknown40();
  }
}

void ScnObjCam::infoInit(RENDER_INFO *info) {
  info->unknown1e8 = 40.0f;
  info->unknown1f4 = 0.1f;
  info->unknown1f8 = 80000.0f;
  info->m_targetDist = 4.0f;
  info->unknown1ec = 1.0f;
  info->m_targetPos = mm::Vec3(0.0f, 0.0f, 0.0f);
  for (int i = 0; i < 4; i++) {
    info->unknown150[i] = 0.0f;
  }
  info->unknown1f0 = static_cast<f32>(DevGraph::getRootWidth()) / static_cast<f32>(DevGraph::getRootHeight());
  info->unknown00.clear();
  info->unknown00.unknown130 |= AttrTransform::FLAG_UNKNOWN_3;
  int width = DevGraph::getRootWidth();
  int height = DevGraph::getRootHeight();
  info->unknown1e0.x = width;
  info->unknown1e0.y = height;
}

void ScnObjCam::setSize(const mm::Pnt<int> &size) {
  RENDER_INFO *info = unknown70.m_back;
  if (info->unknown1e0 != size) {
    info->unknown1e0.set(size);
    if (info->unknown1e0.x != 0 && info->unknown1e0.y != 0) {
      info->unknown1f0 = static_cast<f32>(info->unknown1e0.x) / static_cast<f32>(info->unknown1e0.y);
    } else {
      info->unknown1f0 = 1.0f;
    }
    updateViewMatrix(false);
  }
}

void ScnObjCam::setDefault() {
  setLookAt(unknown002, unknown003, 0.0f);
  unknown70.m_back->unknown1e8 = 40.0f;
  updateViewMatrix(false);
}

void ScnObjCam::setInfo(int info) {
  m_info = info;
  setDefault();
}

void ScnObjCam::setLookAt(const mm::Vec3 &position, const mm::Vec3 &target, f32 roll) {
  RENDER_INFO *info = unknown70.m_back;
  info->unknown00.unknown00 = position;
  info->m_targetPos = target;
  info->unknown00.unknownf0.z = roll;
  mm::Vec3 delta;
  delta.x = info->m_targetPos.x - position.x;
  delta.y = info->m_targetPos.y - position.y;
  delta.z = info->m_targetPos.z - position.z;
  if (fabsf(delta.x) <= 0.000001f && fabsf(delta.y) <= 0.000001f && fabsf(delta.z) <= 0.000001f) {
    delta = mm::Vec3::unitZ;
    info->m_targetPos = delta + position;
  }
  info->m_targetDist = sqrtf(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
  info->unknown00.unknownf0.y = -atan2f(delta.x, -delta.z);
  info->unknown00.unknownf0.x = atan2f(delta.y, sqrtf(delta.x * delta.x + delta.z * delta.z));
  updateViewMatrix(true);
}

void ScnObjCam::calcFrameFit(const mm::Sphere &sphere) {
  RENDER_INFO *info = unknown70.m_back;
  if (!(sphere.scale.x > 0.000001f)) {
    info->unknown1e8 = 40.0f;
    updateViewMatrix(false);
    unknown70.m_back->unknown00.unknownf0.z = 0.0f;
    updateViewMatrix(false);
    return;
  }
  mm::Vec3 cameraPosition = info->unknown00.unknown70.unknown004();
  mm::Vec3 direction = cameraPosition - unknown70.m_front->m_targetPos;
  direction.unknown001();
  f32 distance = sphere.scale.x / sinf(unknown70.m_front->unknown1e8 * 0.017453292f * 0.5f);
  mm::Vec3 position = sphere.getPos() + direction * distance;
  setLookAt(position, sphere.getPos(), 0.0f);
}

template class threadval<ScnObjCam::RENDER_INFO>;

} // namespace ml
