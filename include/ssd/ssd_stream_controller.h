#pragma once
#include <stddef.h>

#include "types.h"

namespace ssd {

class StreamController {
public:
  s64 ResetStream();
  u32 SampleToPosition(int sample);
  void SetReadPosition(u64 position);
  int PositionToFrame(u64 position);

  u8 _00[0x68 - 0x00];
  bool unknown68; // Inferred role: loop; original member name unknown.
  u8 _69[0xf0 - 0x69];
  bool unknownf0; // Inferred role: open; original member name unknown.
  bool unknownf1; // Inferred role: set position done; original member name unknown.
  u8 _f2[0xf5 - 0xf2];
  bool unknownf5; // Inferred role: keep open; original member name unknown.
  bool unknownf6; // Inferred role: set position request; original member name unknown.
  bool unknownf7; // Inferred role: set position pending; original member name unknown.
  u32 unknownf8;  // Inferred role: state; original member name unknown.
  u8 _fc[0x1c0 - 0xfc];
  const u32 *unknown1c0; // Inferred role: frame position table; original member name unknown.
  u8 _1c8[0x208 - 0x1c8];
  u64 unknown208; // Inferred role: read position; original member name unknown.
  u8 _210[0x218 - 0x210];
  u64 unknown218; // Inferred role: file position; original member name unknown.
  u8 _220[0x248 - 0x220];
  int unknown248; // Inferred role: frame count; original member name unknown.
  u8 _24c[0x250 - 0x24c];
  int unknown250; // Inferred role: remain loop count; original member name unknown.
};

static_assert(offsetof(StreamController, unknown68) == 0x68, "");
static_assert(offsetof(StreamController, unknownf0) == 0xf0, "");
static_assert(offsetof(StreamController, unknownf5) == 0xf5, "");
static_assert(offsetof(StreamController, unknownf8) == 0xf8, "");
static_assert(offsetof(StreamController, unknown1c0) == 0x1c0, "");
static_assert(offsetof(StreamController, unknown208) == 0x208, "");
static_assert(offsetof(StreamController, unknown218) == 0x218, "");
static_assert(offsetof(StreamController, unknown248) == 0x248, "");
static_assert(offsetof(StreamController, unknown250) == 0x250, "");

} // namespace ssd
