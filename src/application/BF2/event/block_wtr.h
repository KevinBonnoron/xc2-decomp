#pragma once
#include "types.h"

namespace event {

class BlockWtr {
public:
  static constexpr u32 WTR_COUNT = 32;

  BlockWtr();
  void setRules(const char *rules);
  bool isBlock(u32 index) const { return mIsBlock[index]; }

private:
  bool mIsBlock[WTR_COUNT];
};

static_assert(sizeof(BlockWtr) == 0x20, "");

} // namespace event
