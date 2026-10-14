#pragma once
#include "types.h"
#include <stddef.h>

namespace gf {

constexpr u32 SAVE_DATA_VERSION = 0x3a15b;

struct SDataSystem {
  SDataSystem() : version(SAVE_DATA_VERSION), flags(0) {}

  u32 version;
  u64 flags;
};

static_assert(offsetof(SDataSystem, flags) == 0x08, "");
static_assert(sizeof(SDataSystem) == 0x10, "");

} // namespace gf
