// Original file name from the game string C:/Monolithsoft/BF2/prog/application/BF2/gf/object/component/pc/field/gf_pc_param_field.cpp.
#include "gf/object/component/pc/field/gf_pc_param_field.h"

#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "framework/reflection.h"
#include "gf/object/component/behavior/movement/gf_move_brake.h"
#include "gf/object/component/behavior/movement/gf_move_fall.h"
#include "gf/object/component/behavior/movement/gf_move_jump.h"
#include "gf/object/component/behavior/movement/gf_move_jump_back.h"
#include "gf/object/component/behavior/movement/gf_move_run.h"
#include "gf/object/component/behavior/movement/gf_move_slide.h"
#include "gf/object/component/behavior/movement/gf_move_turn.h"
#include "gf/object/component/behavior/movement/gf_move_walk.h"
#include "gf/object/component/behavior/movement/gf_move_water_rise.h"
#include "gf/object/component/behavior/movement/gf_move_water_sink.h"
#include "gf/object/component/pc/plugin/gf_pc_fade_plugin.h"
#include "mm_mtl/vector.h"

namespace gf {
namespace pc {

fw::Reflection *createReflectionField() {
#line 130
  fw::Reflection *reflection = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::Reflection();
  reflection->unknown10.resize(20, nullptr);
  FieldParam::createReflection(reflection, "common", 0);
  GfMoveBrakeControler::createReflection(reflection, "brake", 1);
  GfMoveWalkControler::createReflection(reflection, "walk", 2);
  GfMoveRunControler::createReflection(reflection, "run", 3);
  GfMoveTurnControler::createReflection(reflection, "turn", 4);
  GfMoveTurnControler::createReflection(reflection, "idle_turn", 5);
  GfMoveJumpControler::createReflection(reflection, "jump", 6);
  GfMoveJumpBackControler::createReflection(reflection, "jump_back", 7);
  GfMoveFallControler::createReflection(reflection, "fall_down", 8);
  WaterCommonParam::createReflection(reflection, "water_common", 9);
  GfMoveRunControler::createReflection(reflection, "swim", 10);
  GfMoveTurnControler::createReflection(reflection, "water_turn", 11);
  GfMoveWaterSinkControler::createReflection(reflection, "water_sink", 12);
  GfMoveWaterRiseControler::createReflection(reflection, "water_rise", 13);
  GfMoveWaterRiseControler::createReflection(reflection, "water_hole_rise", 14);
  WallCommonParam::createReflection(reflection, "wall_common", 15);
  WallMoveParam::createReflection(reflection, "wall_move", 16);
  GfMoveSlideControler::createReflection(reflection, "slide_move", 17);
  FadeParam::createReflection(reflection, "water_fade", 18);
  UniqueIdleParam::createReflection(reflection, "unique_idle", 19);
  return reflection;
}

fw::Reflection *createReflectionFieldAI() {
#line 184
  fw::Reflection *reflection = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::Reflection();
  reflection->unknown10.resize(8, nullptr);
  FollowMainPcParam::createReflection(reflection, "follow_main", 0);
  FollowMainPcParam::createReflection(reflection, "follow_water_main", 1);
  FollowBuddyPcParam::createReflection(reflection, "follow_buddy", 2);
  FollowBuddyPcParam::createReflection(reflection, "follow_water_buddy", 3);
  JumpAIParam::createReflection(reflection, "ai_jump", 4);
  WallAiParam::createReflection(reflection, "wall_ai", 5);
  ForceWarpAiParam::createReflection(reflection, "high_jump_ai", 6);
  ForceWarpAiParam::createReflection(reflection, "water_warp_ai", 7);
  return reflection;
}

void FadeParam::createReflection(fw::Reflection *reflection, const char *name, u32 index) {
#line 40
  fw::ReflectionValueStruct *value = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueStruct(name, sizeof(FadeParam));
#line 41
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("fadeInTime", offsetof(FadeParam, fadeInTime), 0.0f, 1.0f, 0.3f));
#line 42
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("blackOutTime", offsetof(FadeParam, blackOutTime), 0.0f, 1.0f, 0.3f));
#line 43
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("fadeOutTime", offsetof(FadeParam, fadeOutTime), 0.0f, 1.0f, 0.3f));
  reflection->setReflectionStruct(index, value);
}

void ForceWarpAiParam::createReflection(fw::Reflection *reflection, const char *name, u32 index) {
#line 113
  fw::ReflectionValueStruct *value = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueStruct(name, sizeof(ForceWarpAiParam));
#line 114
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("baseWaitTime", offsetof(ForceWarpAiParam, baseWaitTime), 0.0f, 100.0f, 0.3f));
#line 115
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("waitTimeRange", offsetof(ForceWarpAiParam, waitTimeRange), 0.0f, 100.0f, 0.3f));
  reflection->setReflectionStruct(index, value);
}

void FieldParam::createReflection(fw::Reflection *reflection, const char *name, u32 index) {
#line 26
  fw::ReflectionValueStruct *value = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueStruct(name, sizeof(FieldParam));
#line 27
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("accelThreshold", offsetof(FieldParam, accelThreshold), 0.0f, 1.0f, 0.3f));
#line 28
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueU32("stopCnt", offsetof(FieldParam, stopCnt), 0u, 100u, 2u));
#line 29
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("turnAngle", offsetof(FieldParam, turnAngle), 0.0f, 6.0f, 1.5f));
#line 30
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("turnEndAngle", offsetof(FieldParam, turnEndAngle), 0.0f, 6.0f, 0.01f));
#line 31
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("turnInputThreshold", offsetof(FieldParam, turnInputThreshold), 0.0f, 1.0f, 0.1f));
#line 32
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("backAngle", offsetof(FieldParam, backAngle), 0.0f, 6.0f, 1.5f));
#line 33
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("ignoreTimeJump", offsetof(FieldParam, ignoreTimeJump), 0.0f, 1000.0f, 0.1f));
#line 34
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("waterSlow", offsetof(FieldParam, waterSlow), 0.0f, 1.0f, 0.2f));
#line 35
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("poisonSlow", offsetof(FieldParam, poisonSlow), 0.0f, 1.0f, 0.3f));
#line 36
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("stopMotionThreshold", offsetof(FieldParam, stopMotionThreshold), 0.0f, 1000.0f, 0.0f));
#line 37
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("stopMotionThresholdWater", offsetof(FieldParam, stopMotionThresholdWater), 0.0f, 1000.0f, 0.1f));
  reflection->setReflectionStruct(index, value);
}

void JumpAIParam::createReflection(fw::Reflection *reflection, const char *name, u32 index) {
#line 63
  fw::ReflectionValueStruct *value = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueStruct(name, sizeof(JumpAIParam));
#line 64
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("minVel", offsetof(JumpAIParam, minVel), 0.0f, 1000.0f, 1.5f));
  reflection->setReflectionStruct(index, value);
}

void FollowMainPcParam::createReflection(fw::Reflection *reflection, const char *name, u32 index) {
#line 46
  fw::ReflectionValueStruct *value = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueStruct(name, sizeof(FollowMainPcParam));
#line 47
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("followDist", offsetof(FollowMainPcParam, followDist), 0.0f, 1000.0f, 7.0f));
#line 48
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("stopDist", offsetof(FollowMainPcParam, stopDist), 0.0f, 1000.0f, 0.2f));
#line 49
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("powMinDist", offsetof(FollowMainPcParam, powMinDist), 0.0f, 1000.0f, 0.2f));
#line 50
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("powMaxDist", offsetof(FollowMainPcParam, powMaxDist), 0.0f, 1000.0f, 5.0f));
#line 51
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("adjustTime", offsetof(FollowMainPcParam, adjustTime), 0.0f, 1000.0f, 1.0f));
#line 52
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("adjustDist", offsetof(FollowMainPcParam, adjustDist), 0.0f, 1000.0f, 0.5f));
#line 53
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("walkDistStopFollower", offsetof(FollowMainPcParam, walkDistStopFollower), 0.0f, 1000.0f, 3.0f));
  reflection->setReflectionStruct(index, value);
}

void FollowBuddyPcParam::createReflection(fw::Reflection *reflection, const char *name, u32 index) {
#line 56
  fw::ReflectionValueStruct *value = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueStruct(name, sizeof(FollowBuddyPcParam));
#line 57
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("stopDist", offsetof(FollowBuddyPcParam, stopDist), 0.0f, 1000.0f, 0.2f));
#line 58
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("powMinDist", offsetof(FollowBuddyPcParam, powMinDist), 0.0f, 1000.0f, 0.4f));
#line 59
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("powMaxDist", offsetof(FollowBuddyPcParam, powMaxDist), 0.0f, 1000.0f, 2.5f));
#line 60
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("walkDistStopFollower", offsetof(FollowBuddyPcParam, walkDistStopFollower), 0.0f, 1000.0f, 3.0f));
  reflection->setReflectionStruct(index, value);
}

void WaterCommonParam::createReflection(fw::Reflection *reflection, const char *name, u32 index) {
#line 67
  fw::ReflectionValueStruct *value = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueStruct(name, sizeof(WaterCommonParam));
#line 68
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("sinkTime", offsetof(WaterCommonParam, sinkTime), 0.0f, 1000.0f, 0.3f));
#line 69
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("sinkDepth", offsetof(WaterCommonParam, sinkDepth), 0.0f, 1000.0f, 5.0f));
#line 70
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("swimEnableSpeed", offsetof(WaterCommonParam, swimEnableSpeed), 0.0f, 0.0f, 1000.0f));
#line 71
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("swimSinkTime", offsetof(WaterCommonParam, swimSinkTime), 0.0f, 1000.0f, 0.3f));
#line 72
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("riseBrakeHeight", offsetof(WaterCommonParam, riseBrakeHeight), 0.0f, 1000.0f, 0.3f));
#line 73
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("swimMotionMin", offsetof(WaterCommonParam, swimMotionMin), 0.0f, 1.0f, 0.8f));
#line 74
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("waterHoleDiveTime", offsetof(WaterCommonParam, waterHoleDiveTime), 0.0f, 1000.0f, 4.0f));
#line 75
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("waterDeadVelMin", offsetof(WaterCommonParam, waterDeadVelMin), 0.0f, 1000.0f, 5.0f));
#line 76
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("waterDiveMinSpeed", offsetof(WaterCommonParam, waterDiveMinSpeed), -10000.0f, 10000.0f, -2.0f));
  reflection->setReflectionStruct(index, value);
}

void WallCommonParam::createReflection(fw::Reflection *reflection, const char *name, u32 index) {
#line 79
  fw::ReflectionValueStruct *value = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueStruct(name, sizeof(WallCommonParam));
#line 80
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("adsorptionAngle", offsetof(WallCommonParam, adsorptionAngle), 0.0f, 180.0f, 14.0f));
#line 81
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__)
                 fw::ReflectionValueF32("adsorptionAngleUuderGround", offsetof(WallCommonParam, adsorptionAngleUuderGround), 0.0f, 180.0f, 45.0f));
#line 82
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("adsorptionOffset", offsetof(WallCommonParam, adsorptionOffset), 0.0f, 100.0f, 0.75f));
#line 83
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("wallFloat", offsetof(WallCommonParam, wallFloat), 0.0f, 100.0f, 0.5f));
#line 84
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("moveSearchLength", offsetof(WallCommonParam, moveSearchLength), 0.0f, 100.0f, 5.0f));
#line 85
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("adsorptionTime", offsetof(WallCommonParam, adsorptionTime), 0.0f, 100.0f, 0.1f));
#line 86
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("noAdsorptionTime", offsetof(WallCommonParam, noAdsorptionTime), 0.0f, 100.0f, 0.5f));
#line 87
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("rotSpeedX", offsetof(WallCommonParam, rotSpeedX), 0.0f, 100.0f, 1.0f));
#line 88
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("rotSpeedY", offsetof(WallCommonParam, rotSpeedY), 0.0f, 100.0f, 4.0f));
#line 89
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("rotSpeedZ", offsetof(WallCommonParam, rotSpeedZ), 0.0f, 100.0f, 1.0f));
#line 90
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("rotThreasouldX", offsetof(WallCommonParam, rotThreasouldX), 0.0f, 1.0f, 0.01f));
#line 91
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("rotThreasouldY", offsetof(WallCommonParam, rotThreasouldY), 0.0f, 1.0f, 0.01f));
#line 92
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("rotThreasouldZ", offsetof(WallCommonParam, rotThreasouldZ), 0.0f, 1.0f, 0.03f));
#line 93
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("jumpSpeed", offsetof(WallCommonParam, jumpSpeed), 0.01f, 1000.0f, 10.0f));
#line 94
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("wallHeightRatio", offsetof(WallCommonParam, wallHeightRatio), 0.01f, 1.0f, 0.9f));
  reflection->setReflectionStruct(index, value);
}

void WallMoveParam::createReflection(fw::Reflection *reflection, const char *name, u32 index) {
#line 97
  fw::ReflectionValueStruct *value = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueStruct(name, sizeof(WallMoveParam));
#line 98
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("upSpeed", offsetof(WallMoveParam, upSpeed), 0.0f, 100.0f, 5.85f));
#line 99
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("sideSpeed", offsetof(WallMoveParam, sideSpeed), 0.0f, 100.0f, 3.0f));
#line 100
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("downSpeed", offsetof(WallMoveParam, downSpeed), 0.0f, 100.0f, 7.8f));
  reflection->setReflectionStruct(index, value);
}

void WallAiParam::createReflection(fw::Reflection *reflection, const char *name, u32 index) {
#line 103
  fw::ReflectionValueStruct *value = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueStruct(name, sizeof(WallAiParam));
#line 104
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("prepareRange", offsetof(WallAiParam, prepareRange), 0.0f, 100.0f, 0.5f));
#line 105
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("minDist", offsetof(WallAiParam, minDist), 0.0f, 100.0f, 1.5f));
#line 106
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("fallDelay", offsetof(WallAiParam, fallDelay), 0.0f, 100.0f, 1.0f));
#line 107
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("climbEndSafeRange", offsetof(WallAiParam, climbEndSafeRange), 0.0f, 100.0f, 1.0f));
#line 108
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("escapeRange", offsetof(WallAiParam, escapeRange), 0.0f, 100.0f, 1.3f));
#line 109
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("nearRange", offsetof(WallAiParam, nearRange), 0.0f, 100.0f, 2.0f));
#line 110
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueU32("delay", offsetof(WallAiParam, delay), 0u, 10u, 2u));
  reflection->setReflectionStruct(index, value);
}

void UniqueIdleParam::createReflection(fw::Reflection *reflection, const char *name, u32 index) {
#line 118
  fw::ReflectionValueStruct *value = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueStruct(name, sizeof(UniqueIdleParam));
#line 119
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("interval", offsetof(UniqueIdleParam, interval), 0.0f, 100.0f, 10.0f));
#line 120
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("probability", offsetof(UniqueIdleParam, probability), 0.0f, 1.0f, 0.5f));
  reflection->setReflectionStruct(index, value);
}

} // namespace pc
} // namespace gf
