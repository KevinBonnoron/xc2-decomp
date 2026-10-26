#include "ml/time_util.h"

namespace ml {

int TimeUtil::aggregateNumberOfDays(int year, int month, int day) {
  if (month < 3) {
    year -= 1;
    month += 12;
  }
  return day + year * 365 - 366 - year / 100 + (year >> 2) + (year / 100 >> 2) + (month * 979 - 1033 >> 5);
}

} // namespace ml
