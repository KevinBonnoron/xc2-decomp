#pragma once
#include <stddef.h>

#include "types.h"

namespace gf {

class GfMobSlotManager {
public:
  bool addFailedPopDistSq(f32 distSq);
  void update();

  u8 _00[0x520];
  u64 unknown520; // Inferred role: number of failed pop squared distances; original member name unknown.
  f32 unknown528; // Inferred role: squared mob pop distance; original member name unknown.
  u8 _52c[0x530 - 0x52c];
};

static_assert(offsetof(GfMobSlotManager, unknown520) == 0x520, "");
static_assert(offsetof(GfMobSlotManager, unknown528) == 0x528, "");
static_assert(sizeof(GfMobSlotManager) == 0x530, "");

} // namespace gf
