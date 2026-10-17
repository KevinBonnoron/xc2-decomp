#pragma once
#include "types.h"

namespace ml {

class TimeCount {
public:
  void reset();
  void start();
  void getClockLap(s64 &clock) const;
  f32 getSecLap() const;

private:
  u64 startTick;
};

static_assert(sizeof(TimeCount) == 8, "");

} // namespace ml
