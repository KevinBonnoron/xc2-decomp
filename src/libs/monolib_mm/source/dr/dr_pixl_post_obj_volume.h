#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "types.h"

namespace ml {

class DrPixlPostObjVolume {
public:
  void resetColorBuff();
  void calcColorBuff();
  void update();
  u8 _00[0x30 - 0x00];
  mm::Vec3 unknown30; // Inferred role: pos; original member name unknown.
};

static_assert(offsetof(DrPixlPostObjVolume, unknown30) == 0x30, "");

} // namespace ml
