#pragma once
#include "ml/dev_base.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace ml {

class DevClock : public DevBase, public mm::mtl::PtrSingleton<DevClock> {
public:
  static bool getClockNow(long &clock);
  static void getSec2Clock(long &clock, f32 sec);
  static bool getTimeNow(long &time, const long &clock);
  static bool getTimeNow(f32 &time, const long &clock);
  static bool getTimeNow(u32 &time, const long &clock);
  static f32 getClock2Sec(const long &clock);
  static void getMicro2Clock(long &clock, u32 micro);
  static bool isInitialized();
  bool wkStandbyLogin() override;
  bool wkStandbyLogout() override;
  virtual long getPowerOnTimeSys() const = 0;
  virtual void getClockNowSys(long &clock) const = 0;
  virtual void getSec2ClockSys(long &clock, f32 sec) const = 0;
  virtual f32 getSecNowSys(const long &clock) const = 0;
  virtual f32 getClock2SecSys(const long &clock) const = 0;
};

} // namespace ml
