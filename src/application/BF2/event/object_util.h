#pragma once
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace event {

class ObjectUtil {
public:
  static f32 toFov(f32 focal);
  static f32 toFocal(f32 fov);
  static bool isBackSide(const mm::Vec3 &position);
  static const char *num2str(u32 number);
  static const char *num2strMulti(u32 number);
  static int getElementCount(const char *string);
  static s32 getElementS32(const char *string, int index, int group);
  static void getElement(mm::mtl::FixStr<128> &element, const char *string, int index, int group);
  static f32 getElementF32(const char *string, int index, int group);
  static bool isNumber(int character);
};

} // namespace event
