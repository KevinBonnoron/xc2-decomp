#include "gf/param/unique_motion/gf_param_unique_motion.h"

#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "framework/reflection.h"

namespace gf {

void UniqueMotionParam::createReflection(fw::Reflection *reflection, const char *name, u32 index) {
#line 14
  fw::ReflectionValueStruct *value = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueStruct(name, sizeof(UniqueMotionParam));
#line 15
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("interval", offsetof(UniqueMotionParam, interval), 0.0f, 1000.0f, 10.0f));
#line 16
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("presetProbablity", offsetof(UniqueMotionParam, presetProbablity), 0.0f, 100.0f, 0.0f));
  reflection->setReflectionStruct(index, value);
}

} // namespace gf
