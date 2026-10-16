#pragma once
#include <stddef.h>

#include "types.h"

namespace ui {

struct EventData {
  EventData() : type(0), param0(0), param1(0), param2(0), param3(0) {}

  u16 type;
  u8 _02[0x08 - 0x02];
  u32 param0;
  u32 param1;
  u32 param2;
  u32 param3;
};

static_assert(offsetof(EventData, param0) == 0x08, "");
static_assert(offsetof(EventData, param1) == 0x0c, "");
static_assert(offsetof(EventData, param2) == 0x10, "");
static_assert(offsetof(EventData, param3) == 0x14, "");
static_assert(sizeof(EventData) == 0x18, "");

} // namespace ui
