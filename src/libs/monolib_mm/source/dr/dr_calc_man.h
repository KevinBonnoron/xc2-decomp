#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {
class DrCalcViewWork;

class DrCalcMan {
public:
  void end();
  void renderEnd();
  void shadowEnd();

  u8 _00[0x10 - 0x00];
  DrCalcViewWork *unknown10; // Inferred role: view work; original member name unknown.
};

static_assert(offsetof(DrCalcMan, unknown10) == 0x10, "");

} // namespace ml
