#pragma once
#include "types.h"

namespace fw {

struct UpdateInfo {
  f32 unknown00; // Inferred role: frame time; original member name unknown.
  f32 unknown04; // Inferred role: delta time; original member name unknown.
  f32 unknown08; // Inferred role: speed; original member name unknown.
};

static_assert(sizeof(UpdateInfo) == 0x0c, "");

} // namespace fw
