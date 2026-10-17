#pragma once
#include "ml/dev_base.h"
#include "mm_mtl/singleton.h"

namespace ml {

class DevClock : public DevBase, public mm::mtl::PtrSingleton<DevClock> {
public:
  static void getClockNow(long &clock);
  static void getTimeNow(float &time, const long &clock);
};

} // namespace ml
