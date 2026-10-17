#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {
class DrShdLgtHybrid;

class DrShdLgtMan {
public:
  DrShdLgtHybrid *getHybridLight();

  u8 _00[0x50 - 0x00];
  DrShdLgtHybrid *m_hybridLight;
};

static_assert(offsetof(DrShdLgtMan, m_hybridLight) == 0x50, "");

} // namespace ml
