#include "ml/dev_clock.h"

#include "ml/reslist.h"
#include "ml/work_obj.h"

namespace ml {
class DevFileTh;

bool DevClock::getClockNow(long &clock) {
  DevClock *devClock = get();
  if (devClock != nullptr && !devClock->wkIsWaitException() && devClock->wkIsActive()) {
    devClock->getClockNowSys(clock);
    return true;
  }

  return false;
}

void DevClock::getSec2Clock(long &clock, f32 sec) {
  DevClock *devClock = get();
  if (devClock != nullptr && !devClock->wkIsWaitException() && devClock->wkIsActive()) {
    devClock->getSec2ClockSys(clock, sec);
  }
}

bool DevClock::getTimeNow(long &time, const long &clock) {
  DevClock *devClock = get();
  if (devClock != nullptr && !devClock->wkIsWaitException() && devClock->wkIsActive()) {
    devClock->getClockNowSys(time);
    time -= clock;
    return true;
  }

  return false;
}

bool DevClock::getTimeNow(f32 &time, const long &clock) {
  DevClock *devClock = get();
  if (devClock != nullptr && !devClock->wkIsWaitException() && devClock->wkIsActive()) {
    time = devClock->getSecNowSys(clock);
    return true;
  }

  return false;
}

bool DevClock::getTimeNow(u32 &time, const long &clock) {
  long now;
  bool result = getTimeNow(now, clock);
  if (now > 0xffffffff) {
    time = 0xffffffff;
  } else {
    time = now;
  }
  return result;
}

f32 DevClock::getClock2Sec(const long &clock) {
  DevClock *devClock = get();
  if (devClock != nullptr) {
    return devClock->getClock2SecSys(clock);
  }

  return 0.0f;
}

void DevClock::getMicro2Clock(long &clock, u32 micro) { getSec2Clock(clock, micro * 0.000001f); }

bool DevClock::isInitialized() {
  DevClock *clock = get();
  if (clock == nullptr || clock->wkIsWaitException()) {
    return false;
  }

  return clock->wkIsActive();
}

bool DevClock::wkStandbyLogin() { return WorkObj::wkStandbyLogin(); }

bool DevClock::wkStandbyLogout() {
  if (m_children.size() == 0 && mm::mtl::PtrSingleton<DevFileTh>::get() == nullptr) {
    return WorkObj::wkStandbyLogout();
  }

  return false;
}

} // namespace ml
