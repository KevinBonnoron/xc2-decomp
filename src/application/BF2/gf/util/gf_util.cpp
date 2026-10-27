#include "gf/util/gf_util.h"

#include <stdio.h>
#include <stdlib.h>

#include "fw/fw_coli_check.h"
#include "gf/camera/gf_camera_player.h"
#include "gf/gf_info.h"
#include "ml/char_code.h"
#include "ml/path_util.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_plane.h"
#include "mm_math/mm_vec3.h"

namespace gf {
namespace util {

constexpr u32 UTF16_BUFFER_LENGTH = 0x400;

void getViewLocalToDeviceCoord(mm::Vec3 &device, const mm::Mat44 &frustum, const mm::Vec3 &local) {
  device.x = frustum.rows[0][0] * (local.x / local.z) - frustum.rows[2][0];
  device.y = frustum.rows[1][1] * (local.y / local.z) - frustum.rows[2][1];
  device.z = -frustum.rows[3][2] / local.z - frustum.rows[2][2];
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

bool isInsideView(const mm::Vec3 &position, f32 radius) {
  for (u32 i = 0; i < GfInfo::CAMERA_PLANE_COUNT; i++) {
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
  u16 buffer[UTF16_BUFFER_LENGTH];
  mlUTF8toUTF16(buffer, UTF16_BUFFER_LENGTH, source);
  return mlUTF16toSJIS(destination, destinationSize, buffer);
}

const char *getFilePtrFromPath(const char *path) { return ml::PathUtil::getFilePtrFromPath(path); }

mm::mtl::FixStr<64> getNoPathExtName(const char *path) { return ml::PathUtil::getNoPathExtName(path); }

void itoa(mm::mtl::FixStr<16> &string, int value, int base) { ml::PathUtil::itoa(string, value, base); }

} // namespace util
} // namespace gf
