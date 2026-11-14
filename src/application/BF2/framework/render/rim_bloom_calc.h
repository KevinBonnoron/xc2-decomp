#pragma once
#include <stddef.h>

#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace fw {

// Layout evidence: getVal (1.0.0: 0x7100175e90) indexes the channels with a stride of 0x420 and reads the keys 0x18 bytes into a channel;
// calcEndFrame (1.0.0: 0x710016f138) reads the key counts at 0x418, 0x838 and 0xc58 and keeps the largest last key time at 0xc80.
class RimBloomCalc {
public:
  // Inferred role: key of a curve, a cubic Hermite segment starts at it; original type name unknown.
  struct unknown001 {
    f32 unknown00; // Inferred role: time; original member name unknown.
    f32 unknown04; // Inferred role: value; original member name unknown.
    f32 unknown08; // Inferred role: tangent entering the key; original member name unknown.
    f32 unknown0c; // Inferred role: tangent leaving the key; original member name unknown.
  };

  // Inferred role: curve of one channel; original type name unknown.
  struct unknown002 {
    u8 _00[0x18];
    mm::mtl::FixedVector<unknown001, 64> unknown18; // Inferred role: keys; original member name unknown.
  };

  f32 getVal(f32 time, u32 channel) const;
  void calcEndFrame();
  f32 calcValFromCurve(f32 time, u32 channel) const;

  unknown002 unknown00[3];
  u8 _c60[0xc80 - 0xc60];
  f32 unknownc80; // Inferred role: time of the last key of all channels; original member name unknown.
};

static_assert(sizeof(RimBloomCalc::unknown001) == 0x10, "");
static_assert(offsetof(RimBloomCalc::unknown002, unknown18) == 0x18, "");
static_assert(sizeof(RimBloomCalc::unknown002) == 0x420, "");
static_assert(offsetof(RimBloomCalc, unknownc80) == 0xc80, "");

} // namespace fw
