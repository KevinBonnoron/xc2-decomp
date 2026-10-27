#include "ml/time_util.h"

#include "mm_mtl/fixstr.h"

namespace ml {

bool TimeUtil::getDateStr(mm::mtl::FixStr<64> &str) {
  str.clear();
  TimeInfo info;
  if (getTime(info)) {
    str.format("%04d/%02d/%02d", info.unknown06_2, info.unknown05_6, info.unknown04_0);
    return true;
  }
  return false;
}

bool TimeUtil::getTimeStr(mm::mtl::FixStr<64> &str) {
  str.clear();
  TimeInfo info;
  if (getTime(info)) {
    str.format("%02d:%02d:%02d", info.unknown03_2, info.unknown02_4, info.unknown01_6);
    return true;
  }
  return false;
}

int TimeUtil::aggregateNumberOfDays(int year, int month, int day) {
  if (month < 3) {
    year -= 1;
    month += 12;
  }
  return day + year * 365 - 366 - year / 100 + (year >> 2) + (year / 100 >> 2) + (month * 979 - 1033 >> 5);
}

} // namespace ml
