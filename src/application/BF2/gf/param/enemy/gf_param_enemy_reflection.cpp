// Original file name from the game string C:/Monolithsoft/BF2/prog/application/BF2/gf/param/enemy/gf_param_enemy_reflection.cpp.
#include "gf/param/enemy/gf_param_enemy_reflection.h"

#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "framework/reflection.h"
#include "gf/param/enemy/gf_param_enemy.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace gf {

fw::Reflection *createReflectionEnemey() {
#line 25
  fw::Reflection *reflection = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::Reflection();
  reflection->unknown10.resize(30, nullptr);
  for (u32 index = 0; index < 30; index++) {
    mm::mtl::FixStr<32> name;
    name.format("enemy_move_%02d", index);
    EnemyMoveParam::createReflection(reflection, name.c_str(), index);
  }
  return reflection;
}

} // namespace gf
