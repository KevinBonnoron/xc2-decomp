#pragma once
#include "types.h"

namespace gf {

struct ElapseTime {
  u32 second : 6;
  u32 minute : 6;
  u32 hour : 20;
};

static_assert(sizeof(ElapseTime) == 4, "");

} // namespace gf
