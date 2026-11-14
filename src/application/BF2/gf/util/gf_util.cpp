#include "gf/util/gf_util.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "fw/fw_coli_check.h"
#include "gf/camera/gf_camera_player.h"
#include "gf/gf_info.h"
#include "ml/char_code.h"
#include "ml/path_util.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_plane.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"

namespace gf {
namespace util {

constexpr u32 LENGTH_UNKNOWN_1024 = 0x400; // Inferred role: utf16 buffer length; original name unknown.

void getViewLocalToDeviceCoord(mm::Vec3 &device, const mm::Mat44 &frustum, const mm::Vec3 &local) {
  device.x = frustum.rows[0][0] * (local.x / local.z) - frustum.rows[2][0];
  device.y = frustum.rows[1][1] * (local.y / local.z) - frustum.rows[2][1];
  device.z = -frustum.rows[3][2] / local.z - frustum.rows[2][2];
}

void getDeviceCoordToViewLocal(mm::Vec3 &local, const mm::Mat44 &frustum, const mm::Vec3 &device) {
  local.z = -frustum.rows[3][2] / (device.z + frustum.rows[2][2]);
  local.x = local.z * ((device.x + frustum.rows[2][0]) / frustum.rows[0][0]);
  local.y = ((device.y + frustum.rows[2][1]) / frustum.rows[1][1]) * local.z;
}

bool getHitCollision(mm::Vec3 &hit, const mm::Vec3 &start, const mm::Vec3 &end) {
  fw::TColiCheckResult<256> result;
  fw::ColiCheckConfig config;
  config.unknown04 = 0xffffffff;
  config.unknown10 = 1;
  config.unknown08 = 0.0f;
  config.unknown0c = 0.0f;
  config.unknown14 = false;
  config.unknown15 = false;
  config.unknown00 = 9;
  if (!fw::ColiCheck::testLine(result, start, end, config)) {
    return false;
  }

  hit = result.getPosition(0);
  return true;
}

bool getUnderHitCollision(mm::Vec3 &hit, const mm::Vec3 &position, f32 distance) {
  fw::TColiCheckResult<256> result;
  fw::ColiCheckConfig config;
  config.unknown04 = 0xffffffff;
  config.unknown10 = 1;
  config.unknown08 = 0.0f;
  config.unknown0c = 0.0f;
  config.unknown14 = false;
  config.unknown15 = false;
  config.unknown00 = 9;
  mm::Vec3 end = position + mm::Vec3(0.0f, -distance, 0.0f);
  if (!fw::ColiCheck::testLine(result, position, end, config)) {
    return false;
  }

  hit = result.getPosition(0);
  return true;
}

bool getUpperHitCollision(mm::Vec3 &hit, const mm::Vec3 &position, f32 distance) {
  fw::TColiCheckResult<256> result;
  fw::ColiCheckConfig config;
  config.unknown04 = 0xffffffff;
  config.unknown10 = 1;
  config.unknown08 = 0.0f;
  config.unknown0c = 0.0f;
  config.unknown14 = false;
  config.unknown15 = false;
  config.unknown00 = 9;
  mm::Vec3 end = position + mm::Vec3(0.0f, distance, 0.0f);
  if (!fw::ColiCheck::testLine(result, position, end, config)) {
    return false;
  }

  hit = result.getPosition(0);
  return true;
}

void getEulerRotateModel(mm::Vec3 &euler, const mm::Quat &quat) {
  f32 x2 = quat.x + quat.x;
  f32 y2 = quat.y + quat.y;
  f32 z2 = quat.z + quat.z;
  f32 r = -(quat.x * z2 - y2 * quat.w);
  if (r >= 1.0f) {
    r = 1.0f;
  } else if (r <= -1.0f) {
    r = -1.0f;
  }
  euler.y = mm::asin(r);
  f32 xx = x2 * quat.x;
  f32 xy = y2 * quat.x;
  f32 wz = z2 * quat.w;
  f32 zz = z2 * quat.z;
  if (euler.y < 1.5707964f) {
    if (euler.y > -1.5707964f) {
      f32 yz = z2 * quat.y;
      f32 wx = x2 * quat.w;
      f32 yy = y2 * quat.y;
      euler.x = atan2f(wx + yz, 1.0f - (xx + yy));
      euler.z = atan2f(xy + wz, 1.0f - (zz + yy));
    } else {
      euler.x = -atan2f(xy - wz, 1.0f - (xx + zz));
      euler.z = 0.0f;
    }
  } else {
    euler.x = atan2f(xy - wz, 1.0f - (xx + zz));
    euler.z = 0.0f;
  }
}

void getEulerRotateCamera(mm::Vec3 &euler, const mm::Quat &quat) { mm::quatToEuler(quat, euler); }

bool isInsideView(const mm::Vec3 &position, f32 radius) {
  for (u32 i = 0; i < GfInfo::PLANE_UNKNOWN_6; i++) {
    const mm::Plane &plane = GfInfo::m_camPlanes[i];
    if (position.x * plane.normal.x + position.y * plane.normal.y + position.z * plane.normal.z + plane.distance < -radius) {
      return false;
    }
  }
  return true;
}

f32 getGameCameraFov() { return PlayerCamera::getFov(); }

f32 getGameCameraNearClip() { return PlayerCamera::getNearClip(); }

f32 getGameCameraFarClip() { return PlayerCamera::getFarClip(); }

int strToInt(const u8 *string) {
  char *end;
  return strtol(reinterpret_cast<const char *>(string), &end, 0);
}

bool strToInt(const char *string, int &value) {
  char *end;
  value = strtol(string, &end, 0);
  return end != string;
}

f32 strToFloat(const u8 *string) {
  f32 value = 0.0f;
  sscanf(reinterpret_cast<const char *>(string), "%f", &value);
  return value;
}

bool strToFloat(const char *string, f32 &value) {
  sscanf(string, "%f", &value);
  return true;
}

void utf8Toutf16(const char *source, u16 *destination, u32 destinationLength) { mlUTF8toUTF16(destination, destinationLength, source); }

void utf16Tosjis(const u16 *source, char *destination, u32 destinationSize) { mlUTF16toSJIS(destination, destinationSize, source); }

bool utf8Tosjis(const char *source, char *destination, u32 destinationSize) {
  u16 buffer[LENGTH_UNKNOWN_1024];
  mlUTF8toUTF16(buffer, LENGTH_UNKNOWN_1024, source);
  return mlUTF16toSJIS(destination, destinationSize, buffer);
}

const char *getFilePtrFromPath(const char *path) { return ml::PathUtil::getFilePtrFromPath(path); }

mm::mtl::FixStr<64> getNoPathExtName(const char *path) { return ml::PathUtil::getNoPathExtName(path); }

void itoa(mm::mtl::FixStr<16> &string, int value, int base) { ml::PathUtil::itoa(string, value, base); }

} // namespace util
} // namespace gf
