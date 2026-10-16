#pragma once
#include "types.h"

enum EVT_nearfar {};

namespace event {

class CamUtil {
public:
  static f32 toFov(f32 focal);
  static f32 toFocal(f32 fov);
  static f32 id2near(int id);
  static f32 id2far(int id);
  static const char *id2nearfarName(int id);
};

} // namespace event
