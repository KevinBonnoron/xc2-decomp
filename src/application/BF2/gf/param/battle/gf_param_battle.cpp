// Original file name from the game string C:/Monolithsoft/BF2/prog/application/BF2/gf/param/battle/gf_param_battle.cpp.
#include "gf/param/battle/gf_param_battle.h"

#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "framework/reflection.h"

namespace gf {

void BattleFieldParam::createReflection(fw::Reflection *reflection, const char *name, u32 index) {
#line 15
  fw::ReflectionValueStruct *value = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueStruct(name, sizeof(BattleFieldParam));
#line 16
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("waterWarpTime", offsetof(BattleFieldParam, waterWarpTime), 0.0f, 1000.0f, 30.0f));
  reflection->setReflectionStruct(index, value);
}

} // namespace gf
