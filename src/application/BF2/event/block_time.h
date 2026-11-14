#pragma once
#include "types.h"

namespace event {

class BlockTime {
public:
  static constexpr u32 TIME_UNKNOWN_8 = 8; // Inferred role: time count; original name unknown.

  BlockTime();
  void setRules(const char *rules);
  bool isBlock(u32 index) const { return unknown00[index]; }

private:
  bool unknown00[TIME_UNKNOWN_8]; // Inferred role: is block; original member name unknown.
};

static_assert(sizeof(BlockTime) == 0x8, "");

} // namespace event
