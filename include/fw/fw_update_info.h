#pragma once
#include "types.h"

namespace fw {

struct UpdateInfo {
  u8 _00[0x04 - 0x00];
  f32 deltaTime;
};

} // namespace fw
