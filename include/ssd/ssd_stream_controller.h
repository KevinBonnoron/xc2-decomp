#pragma once
#include <stddef.h>

#include "types.h"

namespace ssd {

class StreamController {
public:
  u8 _00[0x68 - 0x00];
  bool unknown68; // Inferred role: loop; original member name unknown.
  u8 _69[0xf5 - 0x69];
  bool unknownf5; // Inferred role: keep open; original member name unknown.
  u8 _f6[0x218 - 0xf6];
  u64 unknown218; // Inferred role: file position; original member name unknown.
  u8 _220[0x250 - 0x220];
  int unknown250; // Inferred role: remain loop count; original member name unknown.
};

static_assert(offsetof(StreamController, unknown68) == 0x68, "");
static_assert(offsetof(StreamController, unknownf5) == 0xf5, "");
static_assert(offsetof(StreamController, unknown218) == 0x218, "");
static_assert(offsetof(StreamController, unknown250) == 0x250, "");

} // namespace ssd
