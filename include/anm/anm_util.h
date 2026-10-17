#pragma once
#include "types.h"

namespace anm {

class Binding;

enum PlayMode {
  PLAY_MODE_LOOP,
  PLAY_MODE_ONCE,
};

class Util {
public:
  static PlayMode getPlayMode(const Binding &binding);
  static f32 getPlayBackTime(const Binding &binding);
  static f32 calcLocalTime(f32 time, f32 start, f32 end, PlayMode playMode);
};

} // namespace anm
