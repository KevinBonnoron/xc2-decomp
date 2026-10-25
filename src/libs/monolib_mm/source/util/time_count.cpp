#include "ml/time_count.h"

#include "ml/dev_clock.h"
#include "ml/dev_graph.h"

namespace ml {

void TimeCount::reset() { DevClock::getClockNow(unknown00); }

void TimeCount::start() { DevClock::getClockNow(unknown00); }

void TimeCount::getClockLap(long &clock) const {
  long now;
  DevClock::getClockNow(now);
  clock = now - unknown00;
}

u32 TimeCount::getMicroLap() const {
  f32 sec;
  DevClock::getTimeNow(sec, unknown00);
  return sec * 1000000.0f;
}

f32 TimeCount::getSecLap() const {
  f32 sec;
  DevClock::getTimeNow(sec, unknown00);
  return sec;
}

f32 TimeCount::getCpuLap() const {
  u32 micro = getMicroLap();
  f32 microSec = micro * 0.000001f;
  return microSec / DevGraph::getFrameSyncSec() * 100.0f;
}

f32 TimeCount::getMicro2Cpu(u32 micro) { return micro * 0.000001f / DevGraph::getFrameSyncSec() * 100.0f; }

void TimeCount::logLapRatio(const char *name) {
  f32 ratio = getCpuLap();
  mm::mtl::FixStr<128> lap;
  lap.format("[LAP]: [%6.2f] [%s]", ratio, name);
  reset();
}

TimeCountBreak::TimeCountBreak(f32 breakSec, const char *name) : unknown00(0), unknown08(breakSec) {
  if (name != nullptr) {
    unknown0c = name;
  }
  DevClock::getClockNow(unknown00);
}

TimeCountBreak::~TimeCountBreak() {}

} // namespace ml
