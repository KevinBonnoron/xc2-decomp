#pragma once
#include <stddef.h>

#include "types.h"

namespace fw {
class Reflection;
} // namespace fw

namespace gf {
namespace pc {

// Field name and offset from the reflection built by gf::pc::InputParam::createReflection (gf_pc_param.cpp).
struct InputParam {
  static void createReflection(fw::Reflection *reflection, const char *name, u32 index);

  f32 threshold;
};

static_assert(sizeof(InputParam) == 0x04, "");

// Field names and offsets from the reflection built by gf::pc::MoveParam::createReflection (gf_pc_param.cpp); the names are
// the reflection strings of the game.
struct MoveParam {
  static void createReflection(fw::Reflection *reflection, const char *name, u32 index);

  f32 gravity;
  f32 adsorptionMin;
  f32 adsorptionMax;
  f32 adsorptionMaxAngle;
  f32 colVelDamping;
  f32 colVelLanchMax;
  f32 landBigDist;
  f32 bigSplashSpeed;
  f32 jumpRatio;
  f32 addMaxSpeedBuddy;
  f32 addMaxSpeedBuddySwim;
};

static_assert(offsetof(MoveParam, landBigDist) == 0x18, "");
static_assert(offsetof(MoveParam, bigSplashSpeed) == 0x1c, "");
static_assert(offsetof(MoveParam, jumpRatio) == 0x20, "");
static_assert(offsetof(MoveParam, addMaxSpeedBuddySwim) == 0x28, "");
static_assert(sizeof(MoveParam) == 0x2c, "");

// Field names and offsets from the reflection built by gf::pc::WarpParam::createReflection (gf_pc_param.cpp).
struct WarpParam {
  static void createReflection(fw::Reflection *reflection, const char *name, u32 index);

  f32 distanceHorz;
  f32 distanceVert;
  f32 stackTime;
  f32 naviSearchUp;
  f32 naviSearchDown;
  f32 fadeTime;
  f32 wallSearchDist;
  f32 distanceHorzWall;
  f32 distanceVertWall;
};

static_assert(offsetof(WarpParam, stackTime) == 0x08, "");
static_assert(offsetof(WarpParam, distanceHorzWall) == 0x1c, "");
static_assert(offsetof(WarpParam, distanceVertWall) == 0x20, "");
static_assert(sizeof(WarpParam) == 0x24, "");

// Field names and offsets from the reflection built by gf::pc::SlideParam::createReflection (gf_pc_param.cpp).
struct SlideParam {
  static void createReflection(fw::Reflection *reflection, const char *name, u32 index);

  f32 minAngle;
  f32 maxSpeed;
  f32 gravity;
  f32 friction;
  f32 slideFriction;
  f32 stopVel;
  f32 startTime;
  f32 startVel;
  f32 endVel;
  f32 fallDistance;
  f32 slideLandHeight;
  f32 ignoreLandTime;
};

static_assert(offsetof(SlideParam, stopVel) == 0x14, "");
static_assert(offsetof(SlideParam, fallDistance) == 0x24, "");
static_assert(offsetof(SlideParam, ignoreLandTime) == 0x2c, "");
static_assert(sizeof(SlideParam) == 0x30, "");

// Field names and offsets from the reflection built by gf::pc::SensorAIParam::createReflection (gf_pc_param.cpp).
struct SensorAIParam {
  static void createReflection(fw::Reflection *reflection, const char *name, u32 index);

  f32 stackThreashold;
  f32 obstacleAngle;
  f32 enableJumpOffset;
  f32 enableJumpCeil;
};

static_assert(offsetof(SensorAIParam, enableJumpCeil) == 0x0c, "");
static_assert(sizeof(SensorAIParam) == 0x10, "");

} // namespace pc
} // namespace gf
