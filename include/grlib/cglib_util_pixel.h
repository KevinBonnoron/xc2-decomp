#pragma once
#include "types.h"

namespace grlib {

class CGLibUtilPixel {
public:
  static f32 convF16toF32(u16 value);
  static u16 convF32toF16(f32 value);
};

} // namespace grlib
