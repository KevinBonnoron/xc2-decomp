#include "gf/param/env/gf_param_env_foot.h"

#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "framework/reflection.h"

namespace gf {

void FootEnvParam::createReflection(fw::Reflection *reflection, const char *name, u32 index) {
#line 14
  fw::ReflectionValueStruct *value = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueStruct(name, sizeof(FootEnvParam));
#line 15
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("len", offsetof(FootEnvParam, len), 0.0f, 100.0f, 0.1f));
#line 16
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("rayUp", offsetof(FootEnvParam, rayUp), 0.0f, 1000.0f, 0.5f));
#line 17
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("rayDown", offsetof(FootEnvParam, rayDown), 0.0f, 1000.0f, 1.0f));
#line 18
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("rayUpSubBody", offsetof(FootEnvParam, rayUpSubBody), 0.0f, 1000.0f, 3.0f));
#line 19
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("rayDownSubBody", offsetof(FootEnvParam, rayDownSubBody), 0.0f, 1000.0f, 3.0f));
  reflection->setReflectionStruct(index, value);
}

} // namespace gf
