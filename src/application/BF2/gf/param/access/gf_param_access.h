#pragma once
#include <stddef.h>

#include "types.h"

namespace fw {
class Reflection;
} // namespace fw

namespace gf {

// Field names and offsets from the reflection built by gf::AccessParam::createReflection.
struct AccessParam {
  static void createReflection(fw::Reflection *reflection, const char *name, u32 index);

  // Inferred helper: tests whether a height lies in the range of the access param, shared by gf::pc::isActiveRange and
  // gf::pc::isActiveRangeLure; original name unknown. Only the non short-circuit and matches the game.
  static bool unknown001(f32 value, f32 maximum, f32 minimum) { return (value <= maximum) & (minimum <= value); }

  f32 offsetFront;
  f32 accessRadius;
  f32 accessUpper;
  f32 accessDown;
};

static_assert(offsetof(AccessParam, accessRadius) == 0x04, "");
static_assert(offsetof(AccessParam, accessUpper) == 0x08, "");
static_assert(offsetof(AccessParam, accessDown) == 0x0c, "");
static_assert(sizeof(AccessParam) == 0x10, "");

// Field names and offsets from the reflection built by gf::LookParam::createReflection.
struct LookParam {
  static void createReflection(fw::Reflection *reflection, const char *name, u32 index);

  f32 lookAngle;
  f32 targetMoveTime;
  f32 fadeInTime;
  f32 changeTargetTime;
  f32 fadeOutTime;
  f32 changeBehaviorTime;
};

static_assert(offsetof(LookParam, fadeInTime) == 0x08, "");
static_assert(offsetof(LookParam, changeBehaviorTime) == 0x14, "");
static_assert(sizeof(LookParam) == 0x18, "");

struct ItemGetParam {
  static void createReflection(fw::Reflection *reflection, const char *name, u32 index);

  f32 radius;
  f32 upper;
  f32 lower;
};

static_assert(offsetof(ItemGetParam, upper) == 0x04, "");
static_assert(offsetof(ItemGetParam, lower) == 0x08, "");
static_assert(sizeof(ItemGetParam) == 0x0c, "");

} // namespace gf
