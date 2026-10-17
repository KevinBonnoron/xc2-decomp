#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class DrShdMdoDecExtTbl {
public:
  u32 getValGlobalParam(int index);

  u8 _00[0x28 - 0x00];
  u32 *m_globalParams;
};

static_assert(offsetof(DrShdMdoDecExtTbl, m_globalParams) == 0x28, "");

} // namespace ml
