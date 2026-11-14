#pragma once
#include <stddef.h>

#include "mm_math/mm_pnt.h"
#include "types.h"

namespace ml {

class EventView {
public:
  enum {
    BUTTON_UNKNOWN_0 = 1 << 0, // Inferred role: left; original name unknown.
  };

  mm::Pnt<int> pos;
  mm::Pnt<int> unknown08; // Inferred role: picking position of the debug manipulators; original member name unknown.
  mm::Pnt<int> unknown10; // Inferred role: mouse move; original member name unknown.
  u8 _18[0x24 - 0x18];
  u32 buttons;
  u32 unknown28; // Inferred role: key flags; original member name unknown.
  u8 _2c[0x33 - 0x2c];
  u8 unknown33; // Inferred role: key code; original member name unknown.
};

static_assert(offsetof(EventView, unknown08) == 0x8, "");
static_assert(offsetof(EventView, unknown10) == 0x10, "");
static_assert(offsetof(EventView, unknown28) == 0x28, "");
static_assert(offsetof(EventView, unknown33) == 0x33, "");

} // namespace ml
