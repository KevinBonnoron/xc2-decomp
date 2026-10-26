#pragma once
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace mm {
struct Col4;
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
  static void drawCameraInfo(int x, int y, const mm::Vec3 &position, const mm::Vec3 &target, const mm::Vec3 &rotation, f32 lens, bool isFocal);
  static void drawChara(const char *name, const mm::Vec3 &position, const mm::Vec3 &rotation, const char *target, f32 height, gf::GF_OBJ_HANDLE *handle);
  static void drawEffect(const char *name, const mm::Vec3 &position, const mm::Vec3 &rotation, const mm::Vec3 &scale, const mm::Col4 &color, unsigned long count);
  static void drawState(const mm::Vec3 &position, f32 height, gf::GF_OBJ_HANDLE *handle);
  static void drawEffectCaster(const char *name, const mm::Vec3 &position, bool isMount, const char *bone);
};

} // namespace event
