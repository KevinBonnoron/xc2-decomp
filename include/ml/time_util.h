#pragma once
#include "types.h"

namespace ml {

struct TimeInfo {
  TimeInfo() : millisecond(0), second(0), minute(0), hour(0), day(0), dayOfYear(0), month(0), year(0) {}

  u32 millisecond : 14;
  u32 second : 6;
  u32 minute : 6;
  u32 hour : 6;
  u32 : 0;
  u32 day : 5;
  u32 dayOfYear : 9;
  u32 month : 4;
  u32 year : 14;
};

static_assert(sizeof(TimeInfo) == 8, "");

class TimeUtil {
public:
  static bool getTime(TimeInfo &info);
};

} // namespace ml
