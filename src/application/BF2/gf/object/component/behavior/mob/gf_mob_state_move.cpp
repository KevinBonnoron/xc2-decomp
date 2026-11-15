#include "gf/object/component/behavior/mob/gf_mob_state_move.h"

#include "gf/field/gf_field_exec_cmd_turn.h"
#include "gf/field/gf_field_local_steer.h"
#include "gf/object/component/behavior/gf_com_behavior_mob.h"
#include "gf/object/gf_obj.h"
#include "gmk/gmk_squad.h"

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

void StateMove::update(GfComBehaviorMob *behavior, const fw::UpdateInfo &info) {
  // Ruling 8 (P4): repeats the statements of GfComBehaviorMob::isSquadMember() (gf_com_behavior_mob.cpp, also called out
  // of line by StateSquadMember::isCondMatch). The game inlines the body here (0x710052ff4c has no call and keeps the
  // incoming x1 and x2 for the seq call); calling it gives a bl and 40 instructions against the game's 41.
  if (behavior->unknownc0.unknown001() && behavior->unknownc0.unknown28 != 0) {
    reqState(STATE_ID_UNKNOWN_3);
  } else if (unknown50) {
    (this->*unknown50)(*behavior, info);
  }
}

void StateMove::seqWaitTurnEnd(GfComBehaviorMob &behavior, const fw::UpdateInfo &info) {
  if (behavior.unknown250.unknown6c) {
    behavior.init(true);
    unknown18.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj *>(behavior.unknown08)->unknownf8, "C_move"));
    unknown50 = &StateMove::seqUpdateMove;
  }
}

} // namespace mob
} // namespace gf
