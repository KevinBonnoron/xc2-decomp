#pragma once
#include <stddef.h>

#include "types.h"

namespace fw {
class Reflection;
} // namespace fw

namespace gf {

// Names are the reflection names registered by UniqueMotionParam::createReflection (gf_param_unique_motion.cpp).
struct UniqueMotionParam {
  static void createReflection(fw::Reflection *reflection, const char *name, u32 index);

  f32 interval;
  f32 presetProbablity;
};

static_assert(offsetof(UniqueMotionParam, presetProbablity) == 0x04, "");
static_assert(sizeof(UniqueMotionParam) == 0x08, "");

} // namespace gf
