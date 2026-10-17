#pragma once
#include <stddef.h>

#include "mm_mtl/fixstr.h"
#include "types.h"

namespace ml {

class TimeCount {
public:
  void reset();
  void start();
  void getClockLap(long &clock) const;
  u32 getMicroLap() const;
  f32 getSecLap() const;
  f32 getCpuLap() const;
  static f32 getMicro2Cpu(u32 micro);
  void logLapRatio(const char *name);

  long m_clock;
};

static_assert(sizeof(TimeCount) == 8, "");

class TimeCountBreak {
public:
  TimeCountBreak(f32 breakSec, const char *name);
  ~TimeCountBreak();

  long m_clock;
  f32 m_breakSec;
  mm::mtl::FixStr<32> m_name;
};

static_assert(offsetof(TimeCountBreak, m_breakSec) == 0x08, "");
static_assert(offsetof(TimeCountBreak, m_name) == 0x0c, "");

} // namespace ml
