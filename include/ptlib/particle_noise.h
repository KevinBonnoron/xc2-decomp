#pragma once
#include <stddef.h>

#include "types.h"

namespace ptlib {

class ImprovedNoise {
public:
  ImprovedNoise();
  ~ImprovedNoise();
  f32 noise(f32 x, f32 y, f32 z);

  int unknown000[512]; // Inferred role: permutation table repeated twice; original member name unknown.
};

static_assert(offsetof(ImprovedNoise, unknown000) == 0x000, "");
static_assert(sizeof(ImprovedNoise) == 0x800, "");

class TurbulenceN {
public:
  static void init();
  static f32 getTotalTime();
  static void updateTime(f32 deltaTime);

  static f32 s_fTotalTime;
  static ImprovedNoise s_noise;
};

} // namespace ptlib
