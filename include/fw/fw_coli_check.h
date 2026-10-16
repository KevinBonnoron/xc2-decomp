#pragma once
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace fw {

class ColiCheck {
public:
  static bool getSnapPos(mm::Vec3 &result, const mm::Vec3 &position, f32 distance, u32 mask);
};

} // namespace fw
