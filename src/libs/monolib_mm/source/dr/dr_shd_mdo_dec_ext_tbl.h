#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class DrShdMdoDecExtTbl {
public:
  u32 getValGlobalParam(int index);

  u8 _00[0x28 - 0x00];
  u32 *unknown28; // Inferred role: global params; original member name unknown.
};

static_assert(offsetof(DrShdMdoDecExtTbl, unknown28) == 0x28, "");

} // namespace ml
