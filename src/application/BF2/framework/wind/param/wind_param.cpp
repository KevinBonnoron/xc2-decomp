#include "framework/wind/param/wind_param.h"

#include <stddef.h>

#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "framework/reflection.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/vector.h"

namespace fw {

void GlobalWindParam::createReflection(Reflection *reflection, const char *name, u32 index) {
#line 43
  ReflectionValueStruct *value = new (Allocator::getDebAllocator(), 16, __FILE__, __LINE__) ReflectionValueStruct(name, sizeof(GlobalWindParam));
#line 44
  value->add(new (Allocator::getDebAllocator(), 16, __FILE__, __LINE__) ReflectionValueF32("powMaxFront", offsetof(GlobalWindParam, powMaxFront), -50.0f, 50.0f, 0.0f));
#line 45
  value->add(new (Allocator::getDebAllocator(), 16, __FILE__, __LINE__) ReflectionValueF32("powMinFront", offsetof(GlobalWindParam, powMinFront), -50.0f, 50.0f, 0.0f));
#line 46
  value->add(new (Allocator::getDebAllocator(), 16, __FILE__, __LINE__) ReflectionValueF32("cycleFront", offsetof(GlobalWindParam, cycleFront), 0.001f, 20.0f, 2.0f));
#line 47
  value->add(new (Allocator::getDebAllocator(), 16, __FILE__, __LINE__) ReflectionValueF32("offsetFront", offsetof(GlobalWindParam, offsetFront), 0.0f, 20.0f, 0.0f));
#line 48
  value->add(new (Allocator::getDebAllocator(), 16, __FILE__, __LINE__) ReflectionValueF32("powMaxBack", offsetof(GlobalWindParam, powMaxBack), -50.0f, 50.0f, 0.0f));
#line 49
  value->add(new (Allocator::getDebAllocator(), 16, __FILE__, __LINE__) ReflectionValueF32("powMinBack", offsetof(GlobalWindParam, powMinBack), -50.0f, 50.0f, 0.0f));
#line 50
  value->add(new (Allocator::getDebAllocator(), 16, __FILE__, __LINE__) ReflectionValueF32("cycleBack", offsetof(GlobalWindParam, cycleBack), 0.001f, 20.0f, 2.0f));
#line 51
  value->add(new (Allocator::getDebAllocator(), 16, __FILE__, __LINE__) ReflectionValueF32("offsetBack", offsetof(GlobalWindParam, offsetBack), 0.0f, 20.0f, 0.0f));
#line 52
  value->add(new (Allocator::getDebAllocator(), 16, __FILE__, __LINE__) ReflectionValueF32("powMaxLeft", offsetof(GlobalWindParam, powMaxLeft), -50.0f, 50.0f, 0.0f));
#line 53
  value->add(new (Allocator::getDebAllocator(), 16, __FILE__, __LINE__) ReflectionValueF32("powMinLeft", offsetof(GlobalWindParam, powMinLeft), -50.0f, 50.0f, 0.0f));
#line 54
  value->add(new (Allocator::getDebAllocator(), 16, __FILE__, __LINE__) ReflectionValueF32("cycleLeft", offsetof(GlobalWindParam, cycleLeft), 0.001f, 20.0f, 2.0f));
#line 55
  value->add(new (Allocator::getDebAllocator(), 16, __FILE__, __LINE__) ReflectionValueF32("offsetLeft", offsetof(GlobalWindParam, offsetLeft), 0.0f, 20.0f, 0.0f));
#line 56
  value->add(new (Allocator::getDebAllocator(), 16, __FILE__, __LINE__) ReflectionValueF32("powMaxRight", offsetof(GlobalWindParam, powMaxRight), -50.0f, 50.0f, 0.0f));
#line 57
  value->add(new (Allocator::getDebAllocator(), 16, __FILE__, __LINE__) ReflectionValueF32("powMinRight", offsetof(GlobalWindParam, powMinRight), -50.0f, 50.0f, 0.0f));
#line 58
  value->add(new (Allocator::getDebAllocator(), 16, __FILE__, __LINE__) ReflectionValueF32("cycleRight", offsetof(GlobalWindParam, cycleRight), 0.001f, 20.0f, 2.0f));
#line 59
  value->add(new (Allocator::getDebAllocator(), 16, __FILE__, __LINE__) ReflectionValueF32("offsetRight", offsetof(GlobalWindParam, offsetRight), 0.0f, 20.0f, 0.0f));
#line 60
  value->add(new (Allocator::getDebAllocator(), 16, __FILE__, __LINE__) ReflectionValueF32("powMaxUp", offsetof(GlobalWindParam, powMaxUp), -50.0f, 50.0f, 0.0f));
#line 61
  value->add(new (Allocator::getDebAllocator(), 16, __FILE__, __LINE__) ReflectionValueF32("powMinUp", offsetof(GlobalWindParam, powMinUp), -50.0f, 50.0f, 0.0f));
#line 62
  value->add(new (Allocator::getDebAllocator(), 16, __FILE__, __LINE__) ReflectionValueF32("cycleRUp", offsetof(GlobalWindParam, cycleRUp), 0.001f, 20.0f, 2.0f));
#line 63
  value->add(new (Allocator::getDebAllocator(), 16, __FILE__, __LINE__) ReflectionValueF32("offsetUp", offsetof(GlobalWindParam, offsetUp), 0.0f, 20.0f, 0.0f));
  reflection->setReflectionStruct(index, value);
}

Reflection *createGlobalWindReflection() {
#line 73
  Reflection *reflection = new (Allocator::getDebAllocator(), 16, __FILE__, __LINE__) Reflection();
  reflection->unknown10.resize(20, nullptr);
  mm::mtl::FixStr<128> name;
  for (u32 i = 0; i < 20; i++) {
    name.format("wind_%d", i);
    GlobalWindParam::createReflection(reflection, name.c_str(), i);
  }

  return reflection;
}

} // namespace fw
