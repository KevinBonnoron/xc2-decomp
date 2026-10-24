#pragma once
#include "types.h"

namespace event {

class BlockTime {
public:
  static constexpr u32 TIME_COUNT = 8;

  BlockTime();
  void setRules(const char *rules);
  bool isBlock(u32 index) const { return unknown00[index]; }

private:
  bool unknown00[TIME_COUNT]; // Inferred role: is block; original member name unknown.
};

static_assert(sizeof(BlockTime) == 0x8, "");

} // namespace event
