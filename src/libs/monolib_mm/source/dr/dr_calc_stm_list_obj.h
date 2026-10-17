#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

struct DrCalcStmRes {
  const u8 *data;
  u8 _08[0x10 - 0x08];
  u8 flags;
  u8 _11[0x18 - 0x11];
};

static_assert(offsetof(DrCalcStmRes, flags) == 0x10, "");
static_assert(sizeof(DrCalcStmRes) == 0x18, "");

class DrCalcStmListObj {
public:
  DrCalcStmRes *getResVertexObj();
};

} // namespace ml
