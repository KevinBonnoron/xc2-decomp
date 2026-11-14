#include "ml/scn_cam_util.h"

#include <math.h>

#include "ml/attr_transform.h"
#include "ml/cam_util.h"
#include "ml/dev_graph.h"
#include "ml/scn.h"
#include "ml/threadval.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_sphere.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace ml {

bool ScnCamUtil::getScreenPos(mm::Vec3 &screen, const ScnObjCam *cam, const mm::Vec3 &position) { return getScreenPos(screen, cam, false, position); }

bool ScnCamUtil::getScreenPos(mm::Vec3 &screen, const ScnObjCam *cam, bool isBack, const mm::Vec3 &position) {
  if (cam == nullptr) {
    return false;
  }
  ScnObjCam::RENDER_INFO *const &info = isBack ? cam->unknown70.m_back : cam->unknown70.m_front;
  const mm::Mat44 &view = info->unknown00.unknownb0;
  mm::Vec3 pos = position;
  f32 viewZ = pos.x * view.rows[0][2] + pos.y * view.rows[1][2] + pos.z * view.rows[2][2] + view.rows[3][2];
  if (fabsf(viewZ) < 0.000001f) {
    return false;
  }
  f32 viewY = pos.x * view.rows[0][1] + pos.y * view.rows[1][1] + pos.z * view.rows[2][1] + view.rows[3][1];
  f32 viewX = pos.x * view.rows[0][0] + pos.y * view.rows[1][0] + pos.z * view.rows[2][0] + view.rows[3][0];
  bool isFront = !(viewZ >= -info->unknown1f4);
  const mm::Mat44 &proj = info->unknown160;
  f32 numeratorX = proj.rows[0][0] * viewX + viewY * proj.rows[1][0] + viewZ * proj.rows[2][0] + proj.rows[3][0];
  f32 numeratorY = viewX * proj.rows[0][1] + viewY * proj.rows[1][1] + viewZ * proj.rows[2][1] + proj.rows[3][1];
  f32 numeratorZ = viewX * proj.rows[0][2] + viewY * proj.rows[1][2] + viewZ * proj.rows[2][2] + proj.rows[3][2];
  f32 w = viewX * proj.rows[0][3] + viewY * proj.rows[1][3] + viewZ * proj.rows[2][3] + proj.rows[3][3];
  f32 x = numeratorX / w / info->unknown1f0;
  f32 y = numeratorY / w;
  f32 z = numeratorZ / w;
  screen.x = x;
  screen.y = y * info->unknown1f0;
  screen.z = z;
  screen.x = (1.0f - screen.x) * (static_cast<f32>(info->unknown1e0.x) * 0.5f);
  screen.y = (screen.y + 1.0f) * (static_cast<f32>(info->unknown1e0.y) * 0.5f);
  return isFront;
}

void ScnCamUtil::getSphereScreenRadius(mm::Sphere &sphere, const ScnObjCam *cam, const mm::Vec3 &position, f32 radius) {
  if (cam == nullptr) {
    return;
  }
  const ScnObjCam::RENDER_INFO *info = cam->unknown70.m_front;
  const mm::Mat44 &view = info->unknown00.unknownb0;
  f32 vx = position.x * view.rows[0][0] + position.y * view.rows[1][0] + position.z * view.rows[2][0] + view.rows[3][0];
  f32 vy = position.x * view.rows[0][1] + position.y * view.rows[1][1] + position.z * view.rows[2][1] + view.rows[3][1];
  f32 vz = position.x * view.rows[0][2] + position.y * view.rows[1][2] + position.z * view.rows[2][2] + view.rows[3][2];
  mm::Vec3 viewLocal;
  viewLocal.y = vy;
  viewLocal.z = vz;
  viewLocal.x = vx;
  mm::Vec3 device;
  CamUtil::getViewLocalToDeviceCoord(device, info->unknown160, viewLocal);
  info = cam->unknown70.m_front;
  f32 delta = radius / (static_cast<f32>(info->unknown1e0.x) * 0.5f);
  device.x = info->unknown1f0 * delta + device.x;
  device.y = device.y + 0.0f;
  device.z = device.z + 0.0f;
  CamUtil::getDeviceCoordToViewLocal(viewLocal, info->unknown160, device);
  info = cam->unknown70.m_front;
  const mm::Mat44 &world = info->unknown00.unknown70;
  f32 x = viewLocal.x * world.rows[0][0] + viewLocal.y * world.rows[1][0] + viewLocal.z * world.rows[2][0] + world.rows[3][0];
  f32 y = viewLocal.x * world.rows[0][1] + viewLocal.y * world.rows[1][1] + viewLocal.z * world.rows[2][1] + world.rows[3][1];
  f32 z = viewLocal.x * world.rows[0][2] + viewLocal.y * world.rows[1][2] + viewLocal.z * world.rows[2][2] + world.rows[3][2];
  viewLocal.y = y;
  viewLocal.z = z;
  viewLocal.x = x;
  f32 dx = position.x - x;
  f32 dy = position.y - y;
  f32 dz = position.z - z;
  f32 screenRadius = sqrtf(dx * dx + dy * dy + dz * dz);
  sphere.pos = position;
  sphere.rot = mm::Quat::identity;
  sphere.scale = mm::Vec3(screenRadius, screenRadius, screenRadius);
}

void ScnCamUtil::getPerspective(mm::Mat44 &matrix, const ScnObjCam *cam) {
  if (cam == nullptr) {
    return;
  }
  const ScnObjCam::RENDER_INFO *info = cam->unknown70.m_front;
  f32 aspect = info->unknown1f0;
  f32 nearClip = info->unknown1f4;
  f32 farClip = info->unknown1f8;
  f32 inverseTan = 1.0f / tanf(info->unknown1e8 * 0.5f);
  f32 scaleX = inverseTan / aspect;
  f32 depthScale = -(nearClip + farClip) / (farClip - nearClip);
  f32 depthOffset = (nearClip * -2.0f * farClip) / (farClip - nearClip);
  matrix.rows[0][0] = scaleX;
  matrix.rows[0][1] = 0.0f;
  matrix.rows[0][2] = 0.0f;
  matrix.rows[0][3] = 0.0f;
  matrix.rows[1][0] = 0.0f;
  matrix.rows[1][1] = inverseTan;
  matrix.rows[1][2] = 0.0f;
  matrix.rows[1][3] = 0.0f;
  matrix.rows[2][0] = 0.0f;
  matrix.rows[2][1] = 0.0f;
  matrix.rows[2][2] = depthScale;
  matrix.rows[2][3] = -1.0f;
  matrix.rows[3][0] = 0.0f;
  matrix.rows[3][1] = 0.0f;
  matrix.rows[3][2] = depthOffset;
  matrix.rows[3][3] = 0.0f;
}

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
