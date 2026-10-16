#include "gf/util/gf_util.h"

#include "gf/camera/gf_camera_player.h"
#include "ml/char_code.h"
#include "ml/path_util.h"
#include <stdio.h>
#include <stdlib.h>

namespace gf {
namespace util {

constexpr u32 UTF16_BUFFER_LENGTH = 0x400;

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
