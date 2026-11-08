// Original file name from the game string C:/Monolithsoft/BF2/prog/application/BF2/gf/object/component/pc/field/gf_pc_param_field.cpp.
#include "gf/object/component/pc/field/gf_pc_param_field.h"

#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "framework/reflection.h"
#include "mm_mtl/vector.h"

namespace gf {
namespace pc {

fw::Reflection *createReflectionFieldAI() {
#line 184
  fw::Reflection *reflection = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::Reflection();
  reflection->unknown10.resize(8, nullptr);
  FollowMainPcParam::createReflection(reflection, "follow_main", 0);
  FollowMainPcParam::createReflection(reflection, "follow_water_main", 1);
  FollowBuddyPcParam::createReflection(reflection, "follow_buddy", 2);
  FollowBuddyPcParam::createReflection(reflection, "follow_water_buddy", 3);
  JumpAIParam::createReflection(reflection, "ai_jump", 4);
  WallAiParam::createReflection(reflection, "wall_ai", 5);
  ForceWarpAiParam::createReflection(reflection, "high_jump_ai", 6);
  ForceWarpAiParam::createReflection(reflection, "water_warp_ai", 7);
  return reflection;
}

} // namespace pc
} // namespace gf
