#pragma once
#include "types.h"

namespace mm {

struct alignas(16) Vec3 {
  f32 x;
  f32 y;
  f32 z;
};

} // namespace mm
