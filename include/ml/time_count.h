#pragma once
#include "types.h"

namespace ml {

class TimeCount {
public:
  void start();
  f32 getSecLap() const;

private:
  u64 startTick;
};

static_assert(sizeof(TimeCount) == 8, "");

} // namespace ml
