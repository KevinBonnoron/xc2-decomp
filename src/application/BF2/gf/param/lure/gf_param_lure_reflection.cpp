// Original file name from the game string C:/Monolithsoft/BF2/prog/application/BF2/gf/param/lure/gf_param_lure_reflection.cpp.
#include "gf/param/lure/gf_param_lure_reflection.h"

#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "framework/reflection.h"
#include "gf/param/access/gf_param_access.h"
#include "mm_mtl/vector.h"

namespace gf {

fw::Reflection *createReflectionLure() {
#line 25
  fw::Reflection *reflection = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::Reflection();
  reflection->unknown10.resize(1, nullptr);
  AccessParam::createReflection(reflection, "lure_range", 0);
  return reflection;
}

} // namespace gf
