// Original file name from the game string C:/Monolithsoft/BF2/prog/application/BF2/gf/param/effect/gf_param_effect.cpp.
#include <stddef.h>

#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "framework/reflection.h"
#include "gf/object/component/behavior/plugin/gf_foot_step_plugin.h"
#include "types.h"

namespace gf {

void FootStepParam::createReflection(fw::Reflection *reflection, const char *name, u32 index) {
#line 14
  fw::ReflectionValueStruct *value = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueStruct(name, sizeof(FootStepParam));
#line 15
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("rapidSpeed", offsetof(FootStepParam, rapidSpeed), 0.0f, 100.0f, 22.0f));
#line 16
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueU32("ankleHeight", offsetof(FootStepParam, ankleHeight), 0, 1000, 20));
  reflection->setReflectionStruct(index, value);
}

} // namespace gf
