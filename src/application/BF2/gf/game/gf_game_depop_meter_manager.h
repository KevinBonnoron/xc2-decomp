#pragma once
#include "types.h"

namespace gf {

class GfGameDepopMeterManager {
public:
  static void create(u32 count);
  static void dispose();
  static void update(f32 deltaTime);
};

} // namespace gf
