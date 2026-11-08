#pragma once
#include <stddef.h>

#include "types.h"

namespace ui {

struct EventData {
  EventData() : unknown00(0), unknown08(0), unknown0c(0), unknown10(0), unknown14(0) {}

  u16 unknown00; // Inferred role: type; original member name unknown.
  u8 _02[0x08 - 0x02];
  union {
    u32 unknown08;     // Inferred role: param0; original member name unknown.
    f32 unknown08_f32; // View of the first parameter slot: read as a float by GfMenuObjZoneTelop's MainListener::reciveEvent; original member name unknown.
    struct {
      u16 unknown08_u16; // Inferred role: param0 low half; original member name unknown.
      u16 unknown0a;     // Inferred role: param0 high half; original member name unknown.
    };
  };
  union {
    u32 unknown0c; // Inferred role: param1; original member name unknown.
    struct {
      u16 unknown0c_u16; // Inferred role: param1 low half; original member name unknown.
      u16 unknown0e;     // Inferred role: param1 high half; original member name unknown.
    };
  };
  union {
    u64 unknown10_u64; // 8-aligned 64-bit view of the last parameter slot: the game zeroes it with one str xzr.
    struct {
      union {
        u32 unknown10; // Inferred role: param2; original member name unknown.
        struct {
          u16 unknown10_u16; // Inferred role: param2 low half; original member name unknown.
          u16 unknown12;     // Inferred role: param2 high half; original member name unknown.
        };
      };
      u32 unknown14; // Inferred role: param3; original member name unknown.
    };
  };
};

static_assert(offsetof(EventData, unknown08) == 0x08, "");
static_assert(offsetof(EventData, unknown08_f32) == 0x08, "");
static_assert(offsetof(EventData, unknown08_u16) == 0x08, "");
static_assert(offsetof(EventData, unknown0a) == 0x0a, "");
static_assert(offsetof(EventData, unknown0c) == 0x0c, "");
static_assert(offsetof(EventData, unknown0c_u16) == 0x0c, "");
static_assert(offsetof(EventData, unknown0e) == 0x0e, "");
static_assert(offsetof(EventData, unknown10) == 0x10, "");
static_assert(offsetof(EventData, unknown10_u16) == 0x10, "");
static_assert(offsetof(EventData, unknown12) == 0x12, "");
static_assert(offsetof(EventData, unknown14) == 0x14, "");
static_assert(offsetof(EventData, unknown10_u64) == 0x10, "");
static_assert(sizeof(EventData) == 0x18, "");
static_assert(alignof(EventData) == 8, "");

} // namespace ui
