#pragma once
#include <stddef.h>

#include "types.h"

struct NVNcounterData;

namespace grlib {

class CGLibGpuCounter {
public:
  void begin();
  void end();
  int getTimeStamp();
  int getCntNum(u32 index);
  int getVertexNum();
  int getPrimitiveNum();
  int getVsShdNum();
  int getPsShdNum();
  int get8x8ZCullNum();
  int get4x2ZCullNum();

  struct unknown001 {
    NVNcounterData *unknown00; // Inferred role: timestamp report data; original member name unknown.
    u32 unknown08;             // Inferred role: report buffer id; original member name unknown.
    u32 unknown0c;             // Inferred role: report buffer offset; original member name unknown.
  };

  struct unknown003 {
    int unknown00[2]; // Inferred role: first counter values; original member name unknown.
    u8 _08[0x10 - 0x08];
    int unknown10[2]; // Inferred role: following counter values; original member name unknown.
  };

  struct unknown002 {
    unknown003 *unknown00; // Inferred role: counter report data; original member name unknown.
    u32 unknown08;         // Inferred role: report buffer id; original member name unknown.
    u32 unknown0c;         // Inferred role: report buffer offset; original member name unknown.
  };

  u8 _00[0x10];
  unknown001 unknown10[2];  // Inferred role: begin timestamps; original member name unknown.
  unknown001 unknown30[2];  // Inferred role: end timestamps; original member name unknown.
  unknown002 unknown50[10]; // Inferred role: begin counters, two buffers per counter type; original member name unknown.
  unknown002 unknownf0[10]; // Inferred role: end counters, two buffers per counter type; original member name unknown.
};

static_assert(offsetof(CGLibGpuCounter, unknown10) == 0x10, "");
static_assert(offsetof(CGLibGpuCounter, unknown30) == 0x30, "");
static_assert(offsetof(CGLibGpuCounter, unknown50) == 0x50, "");
static_assert(offsetof(CGLibGpuCounter, unknownf0) == 0xf0, "");
static_assert(sizeof(CGLibGpuCounter) == 0x190, "");

} // namespace grlib
