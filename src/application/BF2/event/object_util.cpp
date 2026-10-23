#include "event/object_util.h"

#include <math.h>
#include <stdlib.h>

#include "event/manager.h"
#include "ml/scn.h"
#include "ml/scn_cam_util.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixstr.h"

namespace event {

f32 ObjectUtil::toFov(f32 focal) { return 2.0f * atanf(25.39f / (2.0f * focal)) * 180.0f / 3.1415f; }

f32 ObjectUtil::toFocal(f32 fov) { return 25.39f / (2.0f * tanf(fov * 0.017452778f * 0.5f)); }

bool ObjectUtil::isBackSide(const mm::Vec3 &position) {
  mm::Vec3 screen;
  return !ml::ScnCamUtil::getScreenPos(screen, Manager::sys()->getScn()->getCam(-1), position);
}

const char *ObjectUtil::num2str(u32 number) {
  static const char *const NUMBERS[] = {"", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
  return NUMBERS[number];
}

const char *ObjectUtil::num2strMulti(u32 number) {
  static const char *const NUMBERS[] = {"", "２", "３", "４", "５", "６", "７", "８", "９", "１０"};
  return NUMBERS[number];
}

int ObjectUtil::getElementCount(const char *string) {
  int count = 0;
  while (string != nullptr && *string != '\0') {
    string = __builtin_strchr(string, '|');
    if (string != nullptr) {
      string++;
      count++;
    }
  }
  return count;
}

s32 ObjectUtil::getElementS32(const char *string, int index, int group) {
  mm::mtl::FixStr<128> element;
  getElement(element, string, index, group);
  return atoi(element.c_str());
}

f32 ObjectUtil::getElementF32(const char *string, int index, int group) {
  mm::mtl::FixStr<128> element;
  getElement(element, string, index, group);
  return atof(element.c_str());
}

bool ObjectUtil::isNumber(int character) {
  if (static_cast<s8>(character) >= 0 && static_cast<u32>(character - '0') < 10) {
    return true;
  }
  return character == '+' || character == '-' || character == '.';
}

} // namespace event
