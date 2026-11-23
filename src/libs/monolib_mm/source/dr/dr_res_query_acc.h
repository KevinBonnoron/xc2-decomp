#pragma once
#include "types.h"

namespace ml {

struct DrResQueryObj;

class DrResQueryAcc {
public:
  DrResQueryAcc();
  void releaseQuery();
  u32 getOccPixel();

  DrResQueryObj *m_drResQueryObj; // Inferred role: query; original member name unknown.
};

static_assert(sizeof(DrResQueryAcc) == 0x8, "");

} // namespace ml
