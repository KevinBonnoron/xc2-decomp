#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {
class DrCalcClipMan;
class DrCalcViewWork;

class DrCalcMan {
public:
  void begin();
  void end();
  void renderEnd();
  void shadowEnd();

  u8 _00[0x08 - 0x00];
  s32 unknown08;             // Inferred role: view loop count; original member name unknown.
  DrCalcViewWork *unknown10; // Inferred role: view work; original member name unknown.
  DrCalcClipMan *unknown18;  // Inferred role: clip man; original member name unknown.
};

static_assert(offsetof(DrCalcMan, unknown08) == 0x08, "");
static_assert(offsetof(DrCalcMan, unknown10) == 0x10, "");

} // namespace ml
