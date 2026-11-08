#pragma once
#include "types.h"

namespace fw {
class Reflection;
} // namespace fw

namespace gf {

// Parameters of gf_param_access.cpp; the layouts are not reconstructed yet.
struct AccessParam {
  static void createReflection(fw::Reflection *reflection, const char *name, u32 index);
};

struct LookParam {
  static void createReflection(fw::Reflection *reflection, const char *name, u32 index);
};

struct ItemGetParam {
  static void createReflection(fw::Reflection *reflection, const char *name, u32 index);
};

} // namespace gf
