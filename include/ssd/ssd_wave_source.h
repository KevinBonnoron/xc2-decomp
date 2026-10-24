#pragma once
#include <stddef.h>

#include "types.h"

namespace ssd {

class WaveSource {
public:
  virtual ~WaveSource();

  u8 _08[0x2c - 0x08];
  f32 unknown2c; // Inferred role: sample rate; original member name unknown.
  u8 _30[0x44 - 0x30];
  u32 unknown44; // Inferred role: loop start; original member name unknown.
  u32 unknown48; // Inferred role: loop end; original member name unknown.
  u8 _4c[0x50 - 0x4c];
  bool unknown50; // Inferred role: loop; original member name unknown.
};

static_assert(offsetof(WaveSource, unknown2c) == 0x2c, "");
static_assert(offsetof(WaveSource, unknown50) == 0x50, "");

} // namespace ssd
