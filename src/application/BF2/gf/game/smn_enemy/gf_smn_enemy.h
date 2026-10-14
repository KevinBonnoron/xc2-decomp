#pragma once
#include "types.h"

namespace gf {

class GfSmnEnemyManager {
public:
  static void create();
  static void dispose();
  static void update(f32 deltaTime);
};

} // namespace gf
