#pragma once
#include "gf/field/gf_real_time.h"
#include "types.h"
#include <stddef.h>

namespace gf {

constexpr u32 SAVE_UNKNOWN_237915 = 0x3a15b; // Inferred role: save data version; original name unknown.

struct SDataSystem {
  SDataSystem() : unknown00(SAVE_UNKNOWN_237915), m_realTime() {}

  u32 unknown00;       // Inferred role: version; original member name unknown.
  RealTime m_realTime; // Inferred role: real time of the save; original member name unknown.
};

static_assert(offsetof(SDataSystem, m_realTime) == 0x08, "");
static_assert(sizeof(SDataSystem) == 0x10, "");

} // namespace gf
