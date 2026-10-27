#pragma once
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace ml {

struct TimeInfo {
  TimeInfo() : unknown00_0(0), unknown01_6(0), unknown02_4(0), unknown03_2(0), unknown04_0(0), unknown04_5(0), unknown05_6(0), unknown06_2(0) {}

  u32 unknown00_0 : 14; // Inferred role: millisecond; original member name unknown.
  u32 unknown01_6 : 6;  // Inferred role: second; original member name unknown.
  u32 unknown02_4 : 6;  // Inferred role: minute; original member name unknown.
  u32 unknown03_2 : 6;  // Inferred role: hour; original member name unknown.
  u32 : 0;
  u32 unknown04_0 : 5;  // Inferred role: day; original member name unknown.
  u32 unknown04_5 : 9;  // Inferred role: day of year; original member name unknown.
  u32 unknown05_6 : 4;  // Inferred role: month; original member name unknown.
  u32 unknown06_2 : 14; // Inferred role: year; original member name unknown.
};

static_assert(sizeof(TimeInfo) == 8, "");

class TimeUtil {
public:
  static bool getTime(TimeInfo &info);
  static bool getDateStr(mm::mtl::FixStr<64> &str);
  static bool getTimeStr(mm::mtl::FixStr<64> &str);
  static int aggregateNumberOfDays(int year, int month, int day);
};

} // namespace ml

extern "C" {

void mlGetDateName(char *name, int size);
}
