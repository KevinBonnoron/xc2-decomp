#include "gf/object/component/pc/gf_pc_state_util_battle.h"

namespace gf {
namespace pc {

namespace {

// Inferred type: one entry of the battle state and battle action correspondence table; original name unknown.
struct unknown001 {
  STATE_ID unknown00;                        // Inferred role: battle state; original member name unknown.
  btl::BattleCharacter::ACTION_ID unknown04; // Inferred role: battle action; original member name unknown.
};

} // namespace

// Inferred role: battle states and actions, indexed by action; original name unknown.
static const unknown001 unknown002[] = {
    {STATE_ID_UNKNOWN_63, btl::BattleCharacter::ACTION_ID_UNKNOWN_0},  {STATE_ID_UNKNOWN_64, btl::BattleCharacter::ACTION_ID_IDLE},
    {STATE_ID_UNKNOWN_65, btl::BattleCharacter::ACTION_ID_UNKNOWN_2},  {STATE_ID_UNKNOWN_66, btl::BattleCharacter::ACTION_ID_PUT_AWAY_WEAPON},
    {STATE_ID_UNKNOWN_67, btl::BattleCharacter::ACTION_ID_MOVE},       {STATE_ID_UNKNOWN_68, btl::BattleCharacter::ACTION_ID_UNKNOWN_5},
    {STATE_ID_UNKNOWN_69, btl::BattleCharacter::ACTION_ID_ATTACK},     {STATE_ID_UNKNOWN_70, btl::BattleCharacter::ACTION_ID_ARTS},
    {STATE_ID_UNKNOWN_71, btl::BattleCharacter::ACTION_ID_BLADE_ARTS}, {STATE_ID_UNKNOWN_72, btl::BattleCharacter::ACTION_ID_BLADE_CHANGE},
    {STATE_ID_UNKNOWN_73, btl::BattleCharacter::ACTION_ID_SP_ATTACK},  {STATE_ID_UNKNOWN_74, btl::BattleCharacter::ACTION_ID_UNKNOWN_11},
    {STATE_ID_UNKNOWN_75, btl::BattleCharacter::ACTION_ID_UNKNOWN_12}, {STATE_ID_UNKNOWN_76, btl::BattleCharacter::ACTION_ID_UNKNOWN_13},
    {STATE_ID_UNKNOWN_77, btl::BattleCharacter::ACTION_ID_UNKNOWN_0E}, {STATE_ID_UNKNOWN_78, btl::BattleCharacter::ACTION_ID_UNKNOWN_15},
    {STATE_ID_UNKNOWN_79, btl::BattleCharacter::ACTION_ID_UNKNOWN_16}, {STATE_ID_UNKNOWN_80, btl::BattleCharacter::ACTION_ID_UNKNOWN_17},
    {STATE_ID_UNKNOWN_81, btl::BattleCharacter::ACTION_ID_RESCUE},
};

bool StateUtilBattle::IsBattleState(STATE_ID state) { return state >= STATE_ID_UNKNOWN_62 && state <= STATE_ID_UNKNOWN_81; }

STATE_ID StateUtilBattle::ConversionActionToState(btl::BattleCharacter::ACTION_ID action) { return unknown002[action].unknown00; }

btl::BattleCharacter::ACTION_ID StateUtilBattle::ConversionStateToAction(STATE_ID state) {
  if (state < STATE_ID_UNKNOWN_63) {
    return btl::BattleCharacter::ACTION_ID_UNKNOWN_0;
  }

  return unknown002[state - STATE_ID_UNKNOWN_63].unknown04;
}

} // namespace pc
} // namespace gf
