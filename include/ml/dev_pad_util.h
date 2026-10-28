#pragma once
#include "types.h"

namespace ml {

class DevPadUtil {
public:
  enum Type {
    TYPE_UNKNOWN_0,
    TYPE_UNKNOWN_1,
  };

  static int getControlPadNo();
  static int getDebugPadNo();
  static u32 getBtn(Type type);
  static u32 getDown(Type type);
  static u32 getUp(Type type);
  static u32 getRepeat(Type type);
  static u32 getDbl(Type type);
  static f32 getALX(Type type);
  static f32 getALY(Type type);
  static f32 getARX(Type type);
  static f32 getARY(Type type);
};

} // namespace ml
