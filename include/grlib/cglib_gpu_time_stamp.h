#pragma once
#include <stddef.h>

#include "types.h"

struct NVNcounterData;

namespace grlib {

class CGLibGpuTimeStamp {
public:
  CGLibGpuTimeStamp();
  ~CGLibGpuTimeStamp();
  void release();
  static void reset();
  void begin();
  void end();

  struct unknown001 {
    NVNcounterData *unknown00; // Inferred role: report counter data; original member name unknown.
    u32 unknown08;             // Inferred role: report buffer id; original member name unknown.
    u32 unknown0c;             // Inferred role: report buffer offset; original member name unknown.
    bool unknown10;            // Inferred role: reported; original member name unknown.
  };

  s64 unknown00;           // Inferred role: elapsed nanoseconds; original member name unknown.
  unknown001 unknown08[2]; // Inferred role: begin reports; original member name unknown.
  unknown001 unknown38[2]; // Inferred role: end reports; original member name unknown.
};

static_assert(offsetof(CGLibGpuTimeStamp, unknown08) == 0x08, "");
static_assert(offsetof(CGLibGpuTimeStamp, unknown38) == 0x38, "");
static_assert(sizeof(CGLibGpuTimeStamp) == 0x68, "");

} // namespace grlib
