// Original file name from the game string C:/Monolithsoft/BF2/prog/application/BF2/gf/param/unique_motion/gf_param_unique_motion_reflection.cpp.
#include "gf/param/unique_motion/gf_param_unique_motion_reflection.h"

#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "framework/reflection.h"
#include "gf/param/unique_motion/gf_param_unique_motion.h"
#include "mm_mtl/vector.h"

namespace gf {

fw::Reflection *createReflectionUniqueMotion() {
#line 25
  fw::Reflection *reflection = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::Reflection();
  reflection->unknown10.resize(1, nullptr);
  UniqueMotionParam::createReflection(reflection, "unique_motion", 0);
  return reflection;
}

} // namespace gf
