#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class DrPixlPostObjMotionBlur {
public:
  u8 _00[0x28 - 0x00];
  void *m_velocityMap;
};

static_assert(offsetof(DrPixlPostObjMotionBlur, m_velocityMap) == 0x28, "");

} // namespace ml
