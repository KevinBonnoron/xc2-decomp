#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {
class DrCalcViewWork;

class DrCalcMan {
public:
  u8 _00[0x10 - 0x00];
  DrCalcViewWork *m_viewWork;
};

static_assert(offsetof(DrCalcMan, m_viewWork) == 0x10, "");

} // namespace ml
