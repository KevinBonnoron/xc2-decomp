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
  hfsm.registerState<StateBattle>(STATE_ID_UNKNOWN_62, static_cast<int>(ai::INVALID_STATE_ID));
  hfsm.registerState<StateBattleStart>(STATE_ID_UNKNOWN_63, STATE_ID_UNKNOWN_62);
  hfsm.registerState<StateBattleIdle>(STATE_ID_UNKNOWN_64, STATE_ID_UNKNOWN_62);
  hfsm.registerState<StateBattlePutOutWeapon>(STATE_ID_UNKNOWN_65, STATE_ID_UNKNOWN_62);
  hfsm.registerState<StateBattlePutAwayWeapon>(STATE_ID_UNKNOWN_66, STATE_ID_UNKNOWN_62);
  hfsm.registerState<StateBattleMove>(STATE_ID_UNKNOWN_67, STATE_ID_UNKNOWN_62);
  hfsm.registerState<StateBattleKizunaMax>(STATE_ID_UNKNOWN_68, STATE_ID_UNKNOWN_62);
  hfsm.registerState<StateBattleAttack>(STATE_ID_UNKNOWN_69, STATE_ID_UNKNOWN_62);
  hfsm.registerState<StateBattleArts>(STATE_ID_UNKNOWN_70, STATE_ID_UNKNOWN_62);
  hfsm.registerState<StateBattleBladeArts>(STATE_ID_UNKNOWN_71, STATE_ID_UNKNOWN_62);
  hfsm.registerState<StateBattleBladeChange>(STATE_ID_UNKNOWN_72, STATE_ID_UNKNOWN_62);
  hfsm.registerState<StateBattleSpAttack>(STATE_ID_UNKNOWN_73, STATE_ID_UNKNOWN_62);
  hfsm.registerState<StateBattleSupport>(STATE_ID_UNKNOWN_74, STATE_ID_UNKNOWN_62);
  hfsm.registerState<StateBattleBladeGuard>(STATE_ID_UNKNOWN_75, STATE_ID_UNKNOWN_62);
  hfsm.registerState<StateBattleRepelled>(STATE_ID_UNKNOWN_76, STATE_ID_UNKNOWN_62);
  hfsm.registerState<StateBattleDown>(STATE_ID_UNKNOWN_77, STATE_ID_UNKNOWN_62);
  hfsm.registerState<StateBattleKnockBack>(STATE_ID_UNKNOWN_78, STATE_ID_UNKNOWN_62);
  hfsm.registerState<StateBattleBreak>(STATE_ID_UNKNOWN_79, STATE_ID_UNKNOWN_62);
  hfsm.registerState<StateBattleDead>(STATE_ID_UNKNOWN_80, STATE_ID_UNKNOWN_62);
  hfsm.registerState<StateBattleRescue>(STATE_ID_UNKNOWN_81, STATE_ID_UNKNOWN_62);
}

} // namespace pc
} // namespace gf
