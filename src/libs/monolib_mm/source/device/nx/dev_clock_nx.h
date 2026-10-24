#pragma once
#include <stddef.h>

#include "ml/dev_clock.h"
#include "nn/os.h"
#include "types.h"

namespace ml {
class WorkObj;

class DevClockNx : public DevClock {
public:
  static const f32 NANO_TO_SEC;

  DevClockNx(const char *name, WorkObj *parent);
  f32 getPowerOnTimeSys() const override;
  void getClockNowSys(long &clock) const override;
  void getSec2ClockSys(long &clock, f32 sec) const override;
  f32 getSecNowSys(const long &clock) const override;
  f32 getClock2SecSys(const long &clock) const override;

  u8 _1b8[0x1c0 - 0x1b8];
  nn::os::Tick unknown1c0; // Inferred role: power on tick; original member name unknown.
};

static_assert(offsetof(DevClockNx, unknown1c0) == 0x1c0, "");

} // namespace ml
