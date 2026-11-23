#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {
class DrCalcClipMan;
class DrCalcViewWork;
class DrMan;

class DrCalcMan {
public:
  DrCalcMan(DrMan *man, int loopCount);
  ~DrCalcMan();
  void begin();
  void end();
  void renderEnd();
  void shadowEnd();

  DrMan *m_drMan;                   // Inferred role: dr man; original member name unknown.
  s32 unknown08;                    // Inferred role: view loop count; original member name unknown.
  DrCalcViewWork *m_drCalcViewWork; // Inferred role: view work; original member name unknown.
  DrCalcClipMan *m_drCalcClipMan;   // Inferred role: clip man; original member name unknown.
};

static_assert(offsetof(DrCalcMan, unknown08) == 0x08, "");
static_assert(offsetof(DrCalcMan, m_drCalcViewWork) == 0x10, "");

} // namespace ml
