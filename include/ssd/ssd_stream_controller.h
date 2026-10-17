#pragma once
#include <stddef.h>

#include "types.h"

namespace ssd {

class StreamController {
public:
  u8 _00[0x68 - 0x00];
  bool isLoop;
  u8 _69[0xf5 - 0x69];
  bool isKeepOpen;
  u8 _f6[0x218 - 0xf6];
  u64 filePosition;
  u8 _220[0x250 - 0x220];
  int remainLoopCount;
};

static_assert(offsetof(StreamController, isLoop) == 0x68, "");
static_assert(offsetof(StreamController, isKeepOpen) == 0xf5, "");
static_assert(offsetof(StreamController, filePosition) == 0x218, "");
static_assert(offsetof(StreamController, remainLoopCount) == 0x250, "");

} // namespace ssd
