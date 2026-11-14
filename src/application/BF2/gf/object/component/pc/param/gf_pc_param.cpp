#include "gf/object/component/pc/param/gf_pc_param.h"

#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "framework/reflection.h"

namespace gf {
namespace pc {

void InputParam::createReflection(fw::Reflection *reflection, const char *name, u32 index) {
#line 15
  fw::ReflectionValueStruct *value = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueStruct(name, sizeof(InputParam));
#line 16
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("threshold", offsetof(InputParam, threshold), 0.0f, 1.0f, 0.1f));
  reflection->setReflectionStruct(index, value);
}

void MoveParam::createReflection(fw::Reflection *reflection, const char *name, u32 index) {
#line 19
  fw::ReflectionValueStruct *value = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueStruct(name, sizeof(MoveParam));
#line 20
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("gravity", offsetof(MoveParam, gravity), 0.0f, 1000.0f, 9.8f));
#line 21
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("adsorptionMin", offsetof(MoveParam, adsorptionMin), 0.0f, 1000.0f, 0.1f));
#line 22
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("adsorptionMax", offsetof(MoveParam, adsorptionMax), 0.0f, 1000.0f, 0.6f));
#line 23
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("adsorptionMaxAngle", offsetof(MoveParam, adsorptionMaxAngle), 0.001f, 1000.0f, 45.0f));
#line 24
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("colVelDamping", offsetof(MoveParam, colVelDamping), 0.001f, 100.0f, 0.2f));
#line 25
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("colVelLanchMax", offsetof(MoveParam, colVelLanchMax), 0.001f, 100.0f, 0.1f));
#line 26
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("landBigDist", offsetof(MoveParam, landBigDist), 0.001f, 10000.0f, 10.0f));
#line 27
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("bigSplashSpeed", offsetof(MoveParam, bigSplashSpeed), 0.001f, 10000.0f, 10.0f));
#line 28
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("jumpRatio", offsetof(MoveParam, jumpRatio), 0.001f, 10.0f, 1.0f));
#line 29
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("addMaxSpeedBuddy", offsetof(MoveParam, addMaxSpeedBuddy), 0.0f, 100.0f, 3.0f));
#line 30
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("addMaxSpeedBuddySwim", offsetof(MoveParam, addMaxSpeedBuddySwim), 0.0f, 100.0f, 2.0f));
  reflection->setReflectionStruct(index, value);
}

void WarpParam::createReflection(fw::Reflection *reflection, const char *name, u32 index) {
#line 33
  fw::ReflectionValueStruct *value = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueStruct(name, sizeof(WarpParam));
#line 34
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("distanceHorz", offsetof(WarpParam, distanceHorz), 0.0f, 1000.0f, 100.0f));
#line 35
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("distanceVert", offsetof(WarpParam, distanceVert), 0.0f, 1000.0f, 100.0f));
#line 36
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("stackTime", offsetof(WarpParam, stackTime), 0.0f, 1000.0f, 5.0f));
#line 37
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("naviSearchUp", offsetof(WarpParam, naviSearchUp), 0.0f, 1000.0f, 3.0f));
#line 38
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("naviSearchDown", offsetof(WarpParam, naviSearchDown), 0.0f, 1000.0f, 1.0f));
#line 39
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("fadeTime", offsetof(WarpParam, fadeTime), 0.0f, 1000.0f, 0.5f));
#line 40
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("wallSearchDist", offsetof(WarpParam, wallSearchDist), 0.0f, 1000.0f, 1.0f));
#line 41
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("distanceHorzWall", offsetof(WarpParam, distanceHorzWall), 0.0f, 1000.0f, 8.0f));
#line 42
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("distanceVertWall", offsetof(WarpParam, distanceVertWall), 0.0f, 1000.0f, 8.0f));
  reflection->setReflectionStruct(index, value);
}

void SensorAIParam::createReflection(fw::Reflection *reflection, const char *name, u32 index) {
#line 45
  fw::ReflectionValueStruct *value = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueStruct(name, sizeof(SensorAIParam));
#line 46
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("stackThreashold", offsetof(SensorAIParam, stackThreashold), 0.0f, 1000.0f, 0.1f));
#line 47
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("obstacleAngle", offsetof(SensorAIParam, obstacleAngle), 0.0f, 90.0f, 45.0f));
#line 48
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("enableJumpOffset", offsetof(SensorAIParam, enableJumpOffset), 0.0f, 1000.0f, 0.3f));
#line 49
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("enableJumpCeil", offsetof(SensorAIParam, enableJumpCeil), 0.0f, 1000.0f, 2.0f));
  reflection->setReflectionStruct(index, value);
}

void SlideParam::createReflection(fw::Reflection *reflection, const char *name, u32 index) {
#line 52
  fw::ReflectionValueStruct *value = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueStruct(name, sizeof(SlideParam));
#line 53
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("minAngle", offsetof(SlideParam, minAngle), 0.0f, 360.0f, 3.0f));
#line 54
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("maxSpeed", offsetof(SlideParam, maxSpeed), 0.0f, 10000.0f, 100.0f));
#line 55
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("gravity", offsetof(SlideParam, gravity), 0.0f, 1000.0f, 10.0f));
#line 56
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("friction", offsetof(SlideParam, friction), 0.0f, 10000.0f, 2.0f));
#line 57
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("slideFriction", offsetof(SlideParam, slideFriction), 0.0f, 10000.0f, 0.5f));
#line 58
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("stopVel", offsetof(SlideParam, stopVel), 0.0f, 1.0f, 1.0f));
#line 59
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("startTime", offsetof(SlideParam, startTime), 0.0f, 1000.0f, 4.0f));
#line 60
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("startVel", offsetof(SlideParam, startVel), 0.0f, 1000.0f, 10.0f));
#line 61
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("endVel", offsetof(SlideParam, endVel), 0.0f, 1000.0f, 7.0f));
#line 62
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("fallDistance", offsetof(SlideParam, fallDistance), 0.0f, 1000.0f, 1.0f));
#line 63
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("slideLandHeight", offsetof(SlideParam, slideLandHeight), 0.0f, 1000.0f, 0.2f));
#line 64
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("ignoreLandTime", offsetof(SlideParam, ignoreLandTime), 0.0f, 1000.0f, 0.3f));
  reflection->setReflectionStruct(index, value);
}

} // namespace pc
} // namespace gf
