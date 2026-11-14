#include "gf/param/eye/gf_param_eye.h"

#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "framework/reflection.h"

namespace gf {

void EyeParam::createReflection(fw::Reflection *reflection, const char *name, u32 index) {
#line 14
  fw::ReflectionValueStruct *value = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueStruct(name, sizeof(EyeParam));
#line 15
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("intervalMin", offsetof(EyeParam, intervalMin), 0.0f, 1000.0f, 1.0f));
#line 16
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("intervalMax", offsetof(EyeParam, intervalMax), 0.0f, 1000.0f, 10.0f));
#line 17
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("closeTime", offsetof(EyeParam, closeTime), 0.0f, 1.0f, 0.15f));
#line 18
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("openTime", offsetof(EyeParam, openTime), 0.0f, 1.0f, 0.05f));
#line 19
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("waitTime", offsetof(EyeParam, waitTime), 0.0f, 1.0f, 0.05f));
#line 20
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("doubleBlink", offsetof(EyeParam, doubleBlink), 0.0f, 1.0f, 0.3f));
  reflection->setReflectionStruct(index, value);
}

} // namespace gf
