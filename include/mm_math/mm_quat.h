#pragma once
#include "types.h"

namespace mm {

struct alignas(16) Quat {
  static const Quat identity;

  f32 x;
  f32 y;
  f32 z;
  f32 w;
};

} // namespace mm
