#pragma once
#include "types.h"

namespace event {

class BlockWtr {
public:
  static constexpr u32 WTR_COUNT = 32;

  BlockWtr();
  void setRules(const char *rules);
  bool isBlock(u32 index) const { return unknown00[index]; }

private:
  bool unknown00[WTR_COUNT]; // Inferred role: is block; original member name unknown.
};

static_assert(sizeof(BlockWtr) == 0x20, "");

} // namespace event
