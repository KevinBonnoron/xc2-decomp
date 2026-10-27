#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

struct _MPFWorkAutoInf {
  u8 _00[0x02];
  u16 unknown02; // Inferred role: state flags, bit 1 is in use; original member name unknown.
  u8 _04[0x1c - 0x04];
  s32 unknown1c; // Inferred role: block size; original member name unknown.
  u8 _20[0x28 - 0x20];
  _MPFWorkAutoInf *unknown28; // Inferred role: first link of the work list; original member name unknown.
  _MPFWorkAutoInf *unknown30; // Inferred role: second link of the work list; original member name unknown.
  _MPFWorkAutoInf *unknown38; // Inferred role: following block; original member name unknown.
  _MPFWorkAutoInf *unknown40; // Inferred role: preceding block; original member name unknown.
};

static_assert(offsetof(_MPFWorkAutoInf, unknown02) == 0x02, "");
static_assert(offsetof(_MPFWorkAutoInf, unknown1c) == 0x1c, "");
static_assert(offsetof(_MPFWorkAutoInf, unknown28) == 0x28, "");
static_assert(offsetof(_MPFWorkAutoInf, unknown30) == 0x30, "");
static_assert(offsetof(_MPFWorkAutoInf, unknown38) == 0x38, "");
static_assert(offsetof(_MPFWorkAutoInf, unknown40) == 0x40, "");

} // namespace ml
