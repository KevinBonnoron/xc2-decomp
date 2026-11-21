// Original file name from the game string C:/Monolithsoft/BF2/prog/application/BF2/gf/param/eye/gf_param_eye_reflection.cpp.
#include "gf/param/eye/gf_param_eye_reflection.h"

#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "framework/reflection.h"
#include "gf/param/eye/gf_param_eye.h"
#include "mm_mtl/vector.h"

namespace gf {

fw::Reflection *createReflectionEye() {
#line 25
  fw::Reflection *reflection = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::Reflection();
  reflection->unknown10.resize(1, nullptr);
  EyeParam::createReflection(reflection, "eye00", 0);
  return reflection;
}

} // namespace gf
