#include "ml/time_count.h"

#include "ml/dev_clock.h"
#include "ml/dev_graph.h"

namespace ml {

void TimeCount::reset() { DevClock::getClockNow(m_clock); }

void TimeCount::start() { DevClock::getClockNow(m_clock); }

void TimeCount::getClockLap(long &clock) const {
  long now;
  DevClock::getClockNow(now);
  clock = now - m_clock;
}

u32 TimeCount::getMicroLap() const {
  f32 sec;
  DevClock::getTimeNow(sec, m_clock);
  return sec * 1000000.0f;
}

f32 TimeCount::getSecLap() const {
  f32 sec;
  DevClock::getTimeNow(sec, m_clock);
  return sec;
}

f32 TimeCount::getMicro2Cpu(u32 micro) { return micro * 0.000001f / DevGraph::getFrameSyncSec() * 100.0f; }

TimeCountBreak::TimeCountBreak(f32 breakSec, const char *name) : m_clock(0), m_breakSec(breakSec) {
  if (name != nullptr) {
    m_name = name;
  }
  DevClock::getClockNow(m_clock);
}

TimeCountBreak::~TimeCountBreak() {}

} // namespace ml
