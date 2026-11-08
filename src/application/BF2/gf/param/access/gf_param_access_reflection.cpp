// Original file name from the game string C:/Monolithsoft/BF2/prog/application/BF2/gf/param/access/gf_param_access_reflection.cpp.
#include "gf/param/access/gf_param_access_reflection.h"

#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "framework/reflection.h"
#include "gf/param/access/gf_param_access.h"
#include "mm_mtl/vector.h"

namespace gf {

fw::Reflection *createReflectionAccess() {
#line 25
  fw::Reflection *reflection = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::Reflection();
  reflection->unknown10.resize(6, nullptr);
  AccessParam::createReflection(reflection, "access", 0);
  AccessParam::createReflection(reflection, "access_wall", 1);
  AccessParam::createReflection(reflection, "access_dog", 2);
  AccessParam::createReflection(reflection, "access_dog_wall", 3);
  LookParam::createReflection(reflection, "look", 4);
  ItemGetParam::createReflection(reflection, "item_get", 5);
  return reflection;
}

} // namespace gf
