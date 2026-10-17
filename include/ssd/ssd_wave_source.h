#pragma once
#include <stddef.h>

#include "types.h"

namespace ssd {

class WaveSource {
public:
  virtual ~WaveSource();

  u8 _08[0x2c - 0x08];
  f32 sampleRate;
  u8 _30[0x44 - 0x30];
  u32 loopStart;
  u32 loopEnd;
  u8 _4c[0x50 - 0x4c];
  bool isLoop;
};

static_assert(offsetof(WaveSource, sampleRate) == 0x2c, "");
static_assert(offsetof(WaveSource, isLoop) == 0x50, "");

} // namespace ssd
