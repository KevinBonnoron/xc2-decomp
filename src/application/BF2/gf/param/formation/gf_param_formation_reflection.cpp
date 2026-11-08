// Original file name from the game string C:/Monolithsoft/BF2/prog/application/BF2/gf/param/formation/gf_param_formation_reflection.cpp.
#include "gf/param/formation/gf_param_formation_reflection.h"

#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "framework/reflection.h"
#include "gf/game/gf_game_player_formation.h"
#include "mm_mtl/vector.h"

namespace gf {

fw::Reflection *createReflectionFormation() {
#line 25
  fw::Reflection *reflection = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::Reflection();
  reflection->unknown10.resize(4, nullptr);
  FormationParam::createReflection(reflection, "formation", 0);
  FormationParam::createReflection(reflection, "battle_formation", 1);
  WarpForRandomTalkParam::createReflection(reflection, "random_talk_warp", 2);
  FormationParam::createReflection(reflection, "elevator_formation", 3);
  return reflection;
}

} // namespace gf
