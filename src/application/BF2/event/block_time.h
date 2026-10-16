#pragma once
#include "types.h"

namespace event {

class BlockTime {
public:
  static constexpr u32 TIME_COUNT = 8;

  BlockTime();
  void setRules(const char *rules);
  bool isBlock(u32 index) const { return mIsBlock[index]; }

private:
  bool mIsBlock[TIME_COUNT];
};

static_assert(sizeof(BlockTime) == 0x8, "");

} // namespace event
