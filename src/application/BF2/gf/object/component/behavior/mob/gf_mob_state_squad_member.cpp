#include "gf/object/component/behavior/mob/gf_mob_state_squad_member.h"

#include "gf/object/component/behavior/gf_com_behavior_mob.h"
#include "gf/object/gf_obj.h"

namespace gf {
namespace mob {

bool StateSquadMember::isCondMatch(const GfComBehaviorMob &behavior) { return behavior.isSquadMember(); }

void StateSquadMember::enter(GfComBehaviorMob *behavior, ai::State *previous) {
  unknown20.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj *>(behavior->unknown08)->unknownf8, "C_move"));
  unknown58 = &StateSquadMember::seqUpdateMove;
  behavior->init(true);
}

void StateSquadMember::leave(GfComBehaviorMob *behavior, ai::State *next) {}

} // namespace mob
} // namespace gf
