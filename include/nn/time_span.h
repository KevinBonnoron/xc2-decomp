#pragma once
#include "types.h"

namespace nn {

class TimeSpan {
public:
  static TimeSpan FromNanoSeconds(s64 nanoSeconds) {
    TimeSpan span;
    span.nanoSeconds = nanoSeconds;
    return span;
  }

  static TimeSpan FromMicroSeconds(s64 microSeconds) { return FromNanoSeconds(microSeconds * 1000); }

  static TimeSpan FromMilliSeconds(s64 milliSeconds) { return FromMicroSeconds(milliSeconds * 1000); }

  static TimeSpan FromSeconds(s64 seconds) { return FromMilliSeconds(seconds * 1000); }

  s64 GetNanoSeconds() const { return nanoSeconds; }

private:
  s64 nanoSeconds;
};

} // namespace nn
