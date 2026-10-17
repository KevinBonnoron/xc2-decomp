#pragma once
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace mm {
struct Vec3;
}

namespace gf {
namespace util {

bool getScreenPos(mm::Vec3 &screenPos, const mm::Vec3 &position);
bool getUpperHitCollision(mm::Vec3 &hit, const mm::Vec3 &position, f32 distance);
f32 getGameCameraFov();
f32 getGameCameraNearClip();
f32 getGameCameraFarClip();
int strToInt(const u8 *string);
bool strToInt(const char *string, int &value);
f32 strToFloat(const u8 *string);
bool strToFloat(const char *string, f32 &value);
void utf8Toutf16(const char *source, u16 *destination, u32 destinationLength);
void utf16Tosjis(const u16 *source, char *destination, u32 destinationSize);
bool utf8Tosjis(const char *source, char *destination, u32 destinationSize);
const char *getFilePtrFromPath(const char *path);
mm::mtl::FixStr<64> getNoPathExtName(const char *path);
void itoa(mm::mtl::FixStr<16> &string, int value, int base);

} // namespace util
} // namespace gf
