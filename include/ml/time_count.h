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

  long unknown00; // Inferred role: clock; original member name unknown.
};

static_assert(sizeof(TimeCount) == 8, "");

class TimeCountBreak {
public:
  TimeCountBreak(f32 breakSec, const char *name);
  ~TimeCountBreak();

  long unknown00;                // Inferred role: clock; original member name unknown.
  f32 unknown08;                 // Inferred role: break sec; original member name unknown.
  mm::mtl::FixStr<32> unknown0c; // Inferred role: name; original member name unknown.
};

static_assert(offsetof(TimeCountBreak, unknown08) == 0x08, "");
static_assert(offsetof(TimeCountBreak, unknown0c) == 0x0c, "");

} // namespace ml
