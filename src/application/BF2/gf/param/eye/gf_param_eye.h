#pragma once
#include <stddef.h>

#include "types.h"

namespace fw {
class Reflection;
} // namespace fw

namespace gf {

// Names are the reflection names registered by EyeParam::createReflection (gf_param_eye.cpp).
struct EyeParam {
  static void createReflection(fw::Reflection *reflection, const char *name, u32 index);

  f32 intervalMin;
  f32 intervalMax;
  f32 closeTime;
  f32 openTime;
  f32 waitTime;
  f32 doubleBlink;
};

static_assert(offsetof(EyeParam, intervalMax) == 0x04, "");
static_assert(offsetof(EyeParam, closeTime) == 0x08, "");
static_assert(offsetof(EyeParam, openTime) == 0x0c, "");
static_assert(offsetof(EyeParam, waitTime) == 0x10, "");
static_assert(offsetof(EyeParam, doubleBlink) == 0x14, "");
static_assert(sizeof(EyeParam) == 0x18, "");

} // namespace gf
