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
  u8 _08[0x10 - 0x08];
  mm::Pnt<int> unknown10; // Inferred role: mouse move; original member name unknown.
  u8 _18[0x24 - 0x18];
  u32 buttons;
  u32 unknown28; // Inferred role: key flags; original member name unknown.
};

static_assert(offsetof(EventView, unknown10) == 0x10, "");
static_assert(offsetof(EventView, unknown28) == 0x28, "");

} // namespace ml
