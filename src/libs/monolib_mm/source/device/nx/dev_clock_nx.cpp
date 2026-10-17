#include "device/nx/dev_clock_nx.h"

#include "nn/time_span.h"

namespace ml {
class WorkObj;

const f32 DevClockNx::NANO_TO_SEC = 1000000000.0f;

DevClockNx::DevClockNx(const char *name, WorkObj *parent) : DevClock(name, parent) { m_powerOnTick = nn::os::GetSystemTick(); }

f32 DevClockNx::getPowerOnTimeSys() const { return getClock2SecSys(nn::os::GetSystemTick().GetInt64Value() - m_powerOnTick.GetInt64Value()); }

void DevClockNx::getClockNowSys(long &clock) const { clock = nn::os::GetSystemTick().GetInt64Value(); }

void DevClockNx::getSec2ClockSys(long &clock, f32 sec) const { nn::os::ConvertToTick(nn::TimeSpan::FromSeconds(sec)); }

f32 DevClockNx::getSecNowSys(const long &clock) const { return getClock2SecSys(nn::os::GetSystemTick().GetInt64Value() - clock); }

f32 DevClockNx::getClock2SecSys(const long &clock) const { return nn::os::ConvertToTimeSpan(nn::os::Tick(clock)).GetNanoSeconds() / NANO_TO_SEC; }

} // namespace ml
