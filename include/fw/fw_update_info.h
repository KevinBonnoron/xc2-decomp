#pragma once
#include "types.h"

namespace fw {

struct UpdateInfo {
  f32 frameTime;
  f32 deltaTime;
  f32 speed;
};

static_assert(sizeof(UpdateInfo) == 0x0c, "");

} // namespace fw
