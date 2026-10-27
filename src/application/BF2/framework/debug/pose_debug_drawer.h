#pragma once
#include <stddef.h>

#include "types.h"

namespace fw {

class PoseDebugDrawer {
public:
  PoseDebugDrawer();

  u64 unknown00; // Inferred role: unknown; original member name unknown.
  u64 unknown08; // Inferred role: unknown; original member name unknown.
  u64 unknown10; // Inferred role: unknown; original member name unknown.
  u64 unknown18; // Inferred role: unknown; original member name unknown.
  u32 unknown20; // Inferred role: unknown; original member name unknown.
  f32 unknown24; // Inferred role: scale; original member name unknown.
};

static_assert(offsetof(PoseDebugDrawer, unknown10) == 0x10, "");
static_assert(offsetof(PoseDebugDrawer, unknown20) == 0x20, "");
static_assert(offsetof(PoseDebugDrawer, unknown24) == 0x24, "");

} // namespace fw
