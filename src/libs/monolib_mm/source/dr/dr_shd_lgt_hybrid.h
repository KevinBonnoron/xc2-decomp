#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {
class DrMan;
class DrShdLgtClustered;
class DrShdLgtTileBasedDr;

class DrShdLgtHybrid {
public:
  virtual ~DrShdLgtHybrid();

  u8 _08[0x10 - 0x08];
  DrMan *m_drMan;
  DrShdLgtClustered *m_clustered;
  DrShdLgtTileBasedDr *m_tileBasedDr;
};

static_assert(offsetof(DrShdLgtHybrid, m_drMan) == 0x10, "");
static_assert(offsetof(DrShdLgtHybrid, m_clustered) == 0x18, "");
static_assert(offsetof(DrShdLgtHybrid, m_tileBasedDr) == 0x20, "");

} // namespace ml
