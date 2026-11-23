// Original file name from the game string C:/Monolithsoft/BF2/prog/application/BF2/gf/param/battle/gf_param_battle_reflection.cpp.
#include "gf/param/battle/gf_param_battle_reflection.h"

#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "framework/reflection.h"
#include "gf/param/battle/gf_param_battle.h"
#include "mm_mtl/vector.h"

namespace gf {

fw::Reflection *createReflectionBattle() {
#line 23
  fw::Reflection *reflection = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::Reflection();
  reflection->unknown10.resize(1, nullptr);
  BattleFieldParam::createReflection(reflection, "field", 0);
  return reflection;
}

} // namespace gf
