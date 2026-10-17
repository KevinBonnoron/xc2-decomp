#include "gf/object/component/pc/battle/gf_pc_battle_states.h"

#include "ai/ai_state.h"
#include "ai/ai_state_hfsm.h"
#include "gf/object/component/pc/battle/gf_pc_state_battle.h"
#include "gf/object/component/pc/battle/gf_pc_state_battle_arts.h"
#include "gf/object/component/pc/battle/gf_pc_state_battle_attack.h"
#include "gf/object/component/pc/battle/gf_pc_state_battle_blade_arts.h"
#include "gf/object/component/pc/battle/gf_pc_state_battle_blade_change.h"
#include "gf/object/component/pc/battle/gf_pc_state_battle_blade_guard.h"
#include "gf/object/component/pc/battle/gf_pc_state_battle_break.h"
#include "gf/object/component/pc/battle/gf_pc_state_battle_dead.h"
#include "gf/object/component/pc/battle/gf_pc_state_battle_down.h"
#include "gf/object/component/pc/battle/gf_pc_state_battle_idle.h"
#include "gf/object/component/pc/battle/gf_pc_state_battle_kizuna_max.h"
#include "gf/object/component/pc/battle/gf_pc_state_battle_knock_back.h"
#include "gf/object/component/pc/battle/gf_pc_state_battle_move.h"
#include "gf/object/component/pc/battle/gf_pc_state_battle_put_away_weapon.h"
#include "gf/object/component/pc/battle/gf_pc_state_battle_put_out_weapon.h"
#include "gf/object/component/pc/battle/gf_pc_state_battle_repelled.h"
#include "gf/object/component/pc/battle/gf_pc_state_battle_rescue.h"
#include "gf/object/component/pc/battle/gf_pc_state_battle_sp_attack.h"
#include "gf/object/component/pc/battle/gf_pc_state_battle_start.h"
#include "gf/object/component/pc/battle/gf_pc_state_battle_support.h"
#include "gf/object/component/pc/gf_pc_state_id.h"

namespace gf {
namespace pc {

void registerBattleStates(ai::Hfsm &hfsm) {
  hfsm.registerState<StateBattle>(STATE_ID_BATTLE, static_cast<int>(ai::INVALID_STATE_ID));
  hfsm.registerState<StateBattleStart>(STATE_ID_BATTLE_START, STATE_ID_BATTLE);
  hfsm.registerState<StateBattleIdle>(STATE_ID_BATTLE_IDLE, STATE_ID_BATTLE);
  hfsm.registerState<StateBattlePutOutWeapon>(STATE_ID_BATTLE_PUT_OUT_WEAPON, STATE_ID_BATTLE);
  hfsm.registerState<StateBattlePutAwayWeapon>(STATE_ID_BATTLE_PUT_AWAY_WEAPON, STATE_ID_BATTLE);
  hfsm.registerState<StateBattleMove>(STATE_ID_BATTLE_MOVE, STATE_ID_BATTLE);
  hfsm.registerState<StateBattleKizunaMax>(STATE_ID_BATTLE_KIZUNA_MAX, STATE_ID_BATTLE);
  hfsm.registerState<StateBattleAttack>(STATE_ID_BATTLE_ATTACK, STATE_ID_BATTLE);
  hfsm.registerState<StateBattleArts>(STATE_ID_BATTLE_ARTS, STATE_ID_BATTLE);
  hfsm.registerState<StateBattleBladeArts>(STATE_ID_BATTLE_BLADE_ARTS, STATE_ID_BATTLE);
  hfsm.registerState<StateBattleBladeChange>(STATE_ID_BATTLE_BLADE_CHANGE, STATE_ID_BATTLE);
  hfsm.registerState<StateBattleSpAttack>(STATE_ID_BATTLE_SP_ATTACK, STATE_ID_BATTLE);
  hfsm.registerState<StateBattleSupport>(STATE_ID_BATTLE_SUPPORT, STATE_ID_BATTLE);
  hfsm.registerState<StateBattleBladeGuard>(STATE_ID_BATTLE_BLADE_GUARD, STATE_ID_BATTLE);
  hfsm.registerState<StateBattleRepelled>(STATE_ID_BATTLE_REPELLED, STATE_ID_BATTLE);
  hfsm.registerState<StateBattleDown>(STATE_ID_BATTLE_DOWN, STATE_ID_BATTLE);
  hfsm.registerState<StateBattleKnockBack>(STATE_ID_BATTLE_KNOCK_BACK, STATE_ID_BATTLE);
  hfsm.registerState<StateBattleBreak>(STATE_ID_BATTLE_BREAK, STATE_ID_BATTLE);
  hfsm.registerState<StateBattleDead>(STATE_ID_BATTLE_DEAD, STATE_ID_BATTLE);
  hfsm.registerState<StateBattleRescue>(STATE_ID_BATTLE_RESCUE, STATE_ID_BATTLE);
}

} // namespace pc
} // namespace gf
