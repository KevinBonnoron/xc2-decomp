#pragma once
#include "mm_math/mm_pnt.h"
#include "types.h"

namespace ml {

class EventView {
public:
  enum {
    BUTTON_LEFT = 1 << 0,
  };

  mm::Pnt<int> pos;
  u8 _08[0x24 - 0x08];
  u8 buttons;
};

} // namespace ml
