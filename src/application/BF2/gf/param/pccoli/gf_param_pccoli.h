#pragma once
#include <stddef.h>

#include "types.h"

namespace fw {
class Reflection;
} // namespace fw

namespace gf {

// Layout from createReflection (1.0.0: 0x71005baf5c); the member names are the names the reflection registers.
struct PcColiParam {
  f32 radiusCapsule;
  f32 heightCapsule;
  f32 radiusShpere; // Sic: the game's name.
  int type;         // Registered as an enumeration of two elements, "capsule" (0) and "sphere" (1).
  f32 bakkyoHeadDist;

  static void createReflection(fw::Reflection *reflection, const char *name, u32 index);
};

static_assert(offsetof(PcColiParam, type) == 0xc, "");
static_assert(offsetof(PcColiParam, bakkyoHeadDist) == 0x10, "");
static_assert(sizeof(PcColiParam) == 0x14, "");

const PcColiParam *getPcColiParameter();

} // namespace gf
