#pragma once
#include <stddef.h>

#include "types.h"

namespace fw {
class Reflection;
} // namespace fw

namespace gf {

// Field names and offsets from the reflection built by gf::FootEnvParam::createReflection (gf_param_env_foot.cpp).
struct FootEnvParam {
  static void createReflection(fw::Reflection *reflection, const char *name, u32 index);

  f32 len;
  f32 rayUp;
  f32 rayDown;
  f32 rayUpSubBody;
  f32 rayDownSubBody;
};

static_assert(offsetof(FootEnvParam, rayDown) == 0x08, "");
static_assert(offsetof(FootEnvParam, rayDownSubBody) == 0x10, "");
static_assert(sizeof(FootEnvParam) == 0x14, "");

} // namespace gf
