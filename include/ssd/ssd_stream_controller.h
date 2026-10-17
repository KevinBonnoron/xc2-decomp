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
};

static_assert(offsetof(StreamController, isLoop) == 0x68, "");
static_assert(offsetof(StreamController, isKeepOpen) == 0xf5, "");

} // namespace ssd
