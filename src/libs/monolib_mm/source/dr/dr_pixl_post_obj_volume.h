#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "types.h"

namespace ml {

class DrPixlPostObjVolume {
public:
  u8 _00[0x30 - 0x00];
  mm::Vec3 m_pos;
};

static_assert(offsetof(DrPixlPostObjVolume, m_pos) == 0x30, "");

} // namespace ml
