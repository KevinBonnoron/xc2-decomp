#pragma once
#include "types.h"
#include <stddef.h>

namespace gf {

constexpr u32 SAVE_DATA_VERSION = 0x3a15b;

struct SDataSystem {
  SDataSystem() : unknown00(SAVE_DATA_VERSION), unknown08(0) {}

  u32 unknown00; // Inferred role: version; original member name unknown.
  u64 unknown08; // Inferred role: flags; original member name unknown.
};

static_assert(offsetof(SDataSystem, unknown08) == 0x08, "");
static_assert(sizeof(SDataSystem) == 0x10, "");

} // namespace gf
