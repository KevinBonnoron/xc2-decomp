#pragma once
#include "types.h"
#include <stddef.h>

namespace gf {

struct SDataSystem {
  u32 version;
  u64 flags;
};

static_assert(offsetof(SDataSystem, flags) == 0x08, "");
static_assert(sizeof(SDataSystem) == 0x10, "");

} // namespace gf
