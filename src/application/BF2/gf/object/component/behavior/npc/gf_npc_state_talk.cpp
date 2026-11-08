#include "gf/object/component/behavior/npc/gf_npc_state_talk.h"

#include "gf/field/gf_field_exec_cmd_turn.h"
#include "gf/object/component/behavior/gf_com_behavior_npc.h"

namespace gf {
namespace npc {

StateTalk::StateTalk() : unknown18(), unknown50(nullptr), unknown60(false) {}

void StateTalk::leave(GfComBehaviorNpc *behavior, ai::State *next) { setCollideNpcMob(true); }

void StateTalk::update(GfComBehaviorNpc *behavior, const fw::UpdateInfo &info) {
  if (unknown50) {
    (this->*unknown50)(*behavior, info);
  }
}

void StateTalk::seqWaitTurnEnd(GfComBehaviorNpc &behavior, const fw::UpdateInfo &info) {
  if (behavior.unknown2e0.unknown6c) {
    reqState(STATE_ID_UNKNOWN_0);
  }
}

} // namespace npc
} // namespace gf
