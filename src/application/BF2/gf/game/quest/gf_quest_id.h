#pragma once
#include "types.h"

namespace gf {

struct QuestID {
  u16 id;
  u16 variant;

  bool empty() const;
};

static_assert(sizeof(QuestID) == 4, "");

} // namespace gf
