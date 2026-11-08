#pragma once
#include <stddef.h>

#include "types.h"

namespace fw {
class Reflection;
} // namespace fw

namespace gf {
namespace pc {

// Field names and offsets from the reflection built by gf::pc::FieldParam::createReflection.
struct FieldParam {
  f32 accelThreshold;
  u32 stopCnt;
  f32 turnAngle;
  f32 turnEndAngle;
  f32 turnInputThreshold;
  f32 backAngle;
  f32 ignoreTimeJump;
  f32 waterSlow;
  f32 poisonSlow;
  f32 stopMotionThreshold;
  f32 stopMotionThresholdWater;
};

static_assert(offsetof(FieldParam, stopCnt) == 0x04, "");
static_assert(offsetof(FieldParam, turnEndAngle) == 0x0c, "");
static_assert(offsetof(FieldParam, backAngle) == 0x14, "");
static_assert(offsetof(FieldParam, ignoreTimeJump) == 0x18, "");
static_assert(offsetof(FieldParam, stopMotionThresholdWater) == 0x28, "");
static_assert(sizeof(FieldParam) == 0x2c, "");

// Field names and offsets from the reflection built by gf::pc::WaterCommonParam::createReflection.
struct WaterCommonParam {
  f32 sinkTime;
  f32 sinkDepth;
  f32 swimEnableSpeed;
  f32 swimSinkTime;
  f32 riseBrakeHeight;
  f32 swimMotionMin;
  f32 waterHoleDiveTime;
  f32 waterDeadVelMin;
  f32 waterDiveMinSpeed;
};

static_assert(offsetof(WaterCommonParam, waterDiveMinSpeed) == 0x20, "");
static_assert(sizeof(WaterCommonParam) == 0x24, "");

// Field names and offsets from the reflection built by gf::pc::WallCommonParam::createReflection.
struct WallCommonParam {
  f32 adsorptionAngle;
  f32 adsorptionAngleUuderGround;
  f32 adsorptionOffset;
  f32 wallFloat;
  f32 moveSearchLength;
  f32 adsorptionTime;
  f32 noAdsorptionTime;
  f32 rotSpeedX;
  f32 rotSpeedY;
  f32 rotSpeedZ;
  f32 rotThreasouldX;
  f32 rotThreasouldY;
  f32 rotThreasouldZ;
  f32 jumpSpeed;
  f32 wallHeightRatio;
};

static_assert(offsetof(WallCommonParam, adsorptionTime) == 0x14, "");
static_assert(offsetof(WallCommonParam, wallHeightRatio) == 0x38, "");
static_assert(sizeof(WallCommonParam) == 0x3c, "");

// Field names and offsets from the reflection built by gf::pc::WallMoveParam::createReflection.
struct WallMoveParam {
  f32 upSpeed;
  f32 sideSpeed;
  f32 downSpeed;
};

static_assert(offsetof(WallMoveParam, downSpeed) == 0x08, "");
static_assert(sizeof(WallMoveParam) == 0x0c, "");

// Field names and offsets from the reflection built by gf::pc::ForceWarpAiParam::createReflection.
struct ForceWarpAiParam {
  static void createReflection(fw::Reflection *reflection, const char *name, u32 index);

  f32 baseWaitTime;
  f32 waitTimeRange;
};

static_assert(offsetof(ForceWarpAiParam, waitTimeRange) == 0x04, "");
static_assert(sizeof(ForceWarpAiParam) == 0x08, "");

// Field names and offsets from the reflection built by gf::pc::JumpAIParam::createReflection.
struct JumpAIParam {
  static void createReflection(fw::Reflection *reflection, const char *name, u32 index);

  f32 minVel;
};

static_assert(sizeof(JumpAIParam) == 0x04, "");

// Field names and offsets from the reflection built by gf::pc::FollowMainPcParam::createReflection.
struct FollowMainPcParam {
  static void createReflection(fw::Reflection *reflection, const char *name, u32 index);

  f32 followDist;
  f32 stopDist;
  f32 powMinDist;
  f32 powMaxDist;
  f32 adjustTime;
  f32 adjustDist;
  f32 walkDistStopFollower;
};

static_assert(offsetof(FollowMainPcParam, powMinDist) == 0x08, "");
static_assert(offsetof(FollowMainPcParam, walkDistStopFollower) == 0x18, "");
static_assert(sizeof(FollowMainPcParam) == 0x1c, "");

// Field names and offsets from the reflection built by gf::pc::FollowBuddyPcParam::createReflection.
struct FollowBuddyPcParam {
  static void createReflection(fw::Reflection *reflection, const char *name, u32 index);

  f32 stopDist;
  f32 powMinDist;
  f32 powMaxDist;
  f32 walkDistStopFollower;
};

static_assert(offsetof(FollowBuddyPcParam, powMinDist) == 0x04, "");
static_assert(offsetof(FollowBuddyPcParam, walkDistStopFollower) == 0x0c, "");
static_assert(sizeof(FollowBuddyPcParam) == 0x10, "");

// Field names and offsets from the reflection built by gf::pc::WallAiParam::createReflection.
struct WallAiParam {
  static void createReflection(fw::Reflection *reflection, const char *name, u32 index);

  f32 prepareRange;
  f32 minDist;
  f32 fallDelay;
  f32 climbEndSafeRange;
  f32 escapeRange;
  f32 nearRange;
  u32 delay;
};

static_assert(offsetof(WallAiParam, fallDelay) == 0x08, "");
static_assert(offsetof(WallAiParam, escapeRange) == 0x10, "");
static_assert(offsetof(WallAiParam, delay) == 0x18, "");
static_assert(sizeof(WallAiParam) == 0x1c, "");

// Field names and offsets from the reflection built by gf::pc::WarpParam::createReflection.
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

fw::Reflection *createReflectionFieldAI();

} // namespace pc
} // namespace gf
