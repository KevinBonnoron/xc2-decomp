#pragma once
#include <stddef.h>

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
  u8 _25[0x28 - 0x25];
  u32 unknown28; // Inferred role: key flags; original member name unknown.
};

static_assert(offsetof(EventView, unknown28) == 0x28, "");

} // namespace ml
