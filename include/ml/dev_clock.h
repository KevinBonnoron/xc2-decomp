#pragma once

namespace ml {

class DevClock {
public:
  static void getClockNow(long &clock);
  static void getTimeNow(float &time, const long &clock);
};

} // namespace ml
