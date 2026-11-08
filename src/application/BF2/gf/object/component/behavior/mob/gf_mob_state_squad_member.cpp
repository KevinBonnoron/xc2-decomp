#include "gf/object/component/behavior/mob/gf_mob_state_squad_member.h"

#include <math.h>

#include "gf/object/component/behavior/gf_com_behavior_mob.h"
#include "gf/object/gf_obj.h"
#include "mm_math/mm_vec3.h"

namespace gf {
namespace mob {

bool StateSquadMember::isCondMatch(const GfComBehaviorMob &behavior) { return behavior.isSquadMember(); }

void StateSquadMember::enter(GfComBehaviorMob *behavior, ai::State *previous) {
  unknown20.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj *>(behavior->unknown08)->unknownf8, "C_move"));
  unknown58 = &StateSquadMember::seqUpdateMove;
  behavior->init(true);
}

void StateSquadMember::leave(GfComBehaviorMob *behavior, ai::State *next) {}

void StateSquadMember::seqUpdateIdle(GfComBehaviorMob &behavior, const fw::UpdateInfo &info) {
  const mm::Vec3 &position = behavior.getPos();
  f32 distance = sqrtf((behavior.unknown110.x - position.x) * (behavior.unknown110.x - position.x) + (behavior.unknown110.z - position.z) * (behavior.unknown110.z - position.z));
  if (unknown18 <= distance) {
    unknown20.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj *>(behavior.unknown08)->unknownf8, "C_move"));
    unknown58 = &StateSquadMember::seqUpdateMove;
    behavior.init(true);
  }
}

} // namespace mob
} // namespace gf
