#pragma once
#include "types.h"

namespace event {

class VoiceUtil {
public:
  static u32 playVoice(const char *path, f32 volume, bool isPrepare);
};

} // namespace event
