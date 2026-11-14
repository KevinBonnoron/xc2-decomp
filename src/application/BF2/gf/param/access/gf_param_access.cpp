#include "gf/param/access/gf_param_access.h"

#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "framework/reflection.h"

namespace gf {

void AccessParam::createReflection(fw::Reflection *reflection, const char *name, u32 index) {
#line 13
  fw::ReflectionValueStruct *value = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueStruct(name, sizeof(AccessParam));
#line 14
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("offsetFront", offsetof(AccessParam, offsetFront), 0.0f, 1000.0f, 1.0f));
#line 15
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("accessRadius", offsetof(AccessParam, accessRadius), 0.01f, 1000.0f, 1.0f));
#line 16
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("accessUpper", offsetof(AccessParam, accessUpper), 0.0f, 1000.0f, 1.5f));
#line 17
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("accessDown", offsetof(AccessParam, accessDown), 0.0f, 1000.0f, 0.0f));
  reflection->setReflectionStruct(index, value);
}

void LookParam::createReflection(fw::Reflection *reflection, const char *name, u32 index) {
#line 20
  fw::ReflectionValueStruct *value = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueStruct(name, sizeof(LookParam));
#line 21
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("lookAngle", offsetof(LookParam, lookAngle), 0.0f, 180.0f, 140.0f));
#line 22
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("targetMoveTime", offsetof(LookParam, targetMoveTime), 0.0f, 100.0f, 0.2f));
#line 23
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("fadeInTime", offsetof(LookParam, fadeInTime), 0.0f, 100.0f, 0.5f));
#line 24
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("changeTargetTime", offsetof(LookParam, changeTargetTime), 0.0f, 100.0f, 0.8f));
#line 25
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("fadeOutTime", offsetof(LookParam, fadeOutTime), 0.0f, 100.0f, 0.8f));
#line 26
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("changeBehaviorTime", offsetof(LookParam, changeBehaviorTime), 0.01f, 100.0f, 0.3f));
  reflection->setReflectionStruct(index, value);
}

void ItemGetParam::createReflection(fw::Reflection *reflection, const char *name, u32 index) {
#line 29
  fw::ReflectionValueStruct *value = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueStruct(name, sizeof(ItemGetParam));
#line 30
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("radius", offsetof(ItemGetParam, radius), 0.0f, 1000.0f, 1.5f));
#line 31
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("upper", offsetof(ItemGetParam, upper), 0.0f, 100.0f, 1.5f));
#line 32
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("lower", offsetof(ItemGetParam, lower), 0.0f, 100.0f, 0.2f));
  reflection->setReflectionStruct(index, value);
}

} // namespace gf
