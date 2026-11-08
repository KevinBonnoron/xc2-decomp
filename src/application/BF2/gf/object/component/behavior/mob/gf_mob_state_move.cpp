#include "gf/object/component/behavior/mob/gf_mob_state_move.h"

#include "gf/field/gf_field_exec_cmd_turn.h"
#include "gf/field/gf_field_local_steer.h"
#include "gf/object/component/behavior/gf_com_behavior_mob.h"
#include "gf/object/gf_obj.h"

namespace gf {
namespace mob {

bool StateMove::isCondMatch(const GfComBehaviorMob &behavior) { return behavior.unknownb8 != nullptr; }

void StateMove::enter(GfComBehaviorMob *behavior, ai::State *previous) {
  execEndSchedule(*behavior);
  behavior->init(true);
  unknown18.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj *>(behavior->unknown08)->unknownf8, "C_move"));
  unknown50 = &StateMove::seqUpdateMove;
}

void StateMove::leave(GfComBehaviorMob *behavior, ai::State *next) {}

void StateMove::seqWaitTurnEnd(GfComBehaviorMob &behavior, const fw::UpdateInfo &info) {
  if (behavior.unknown250.unknown6c) {
    behavior.init(true);
    unknown18.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj *>(behavior.unknown08)->unknownf8, "C_move"));
    unknown50 = &StateMove::seqUpdateMove;
  }
}

} // namespace mob
} // namespace gf
