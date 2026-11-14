#pragma once
#include <stddef.h>

#include "types.h"

namespace fw {
class Reflection;
} // namespace fw

namespace gf {

// Field name from the reflection built by BattleFieldParam::createReflection.
struct BattleFieldParam {
  static void createReflection(fw::Reflection *reflection, const char *name, u32 index);

  f32 waterWarpTime;
};

static_assert(offsetof(BattleFieldParam, waterWarpTime) == 0x0, "");
static_assert(sizeof(BattleFieldParam) == 0x4, "");

} // namespace gf
