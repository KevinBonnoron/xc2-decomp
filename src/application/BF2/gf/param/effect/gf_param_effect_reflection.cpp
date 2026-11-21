// Original file name from the game string C:/Monolithsoft/BF2/prog/application/BF2/gf/param/effect/gf_param_effect_reflection.cpp.
#include "gf/param/effect/gf_param_effect_reflection.h"

#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "framework/reflection.h"
#include "gf/object/component/behavior/plugin/gf_foot_step_plugin.h"
#include "mm_mtl/vector.h"

namespace gf {

fw::Reflection *createReflectionEffFootStep() {
#line 23
  fw::Reflection *reflection = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::Reflection();
  reflection->unknown10.resize(1, nullptr);
  FootStepParam::createReflection(reflection, "footstep", 0);
  return reflection;
}

} // namespace gf
