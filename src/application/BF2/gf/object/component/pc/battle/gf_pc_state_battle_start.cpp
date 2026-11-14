#include "gf/object/component/pc/battle/gf_pc_state_battle_start.h"

#include "battle/character/battle_character.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_pc_property_battle.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_util.h"
#include "types.h"

namespace gf {
namespace pc {

bool StateBattleStart::Enter(GfComBehaviorPc *behavior, ai::State *previous) {
  StateUtil::setFallDamageDisable(*behavior, false);
  GfObjUtil::setEnableEyeBlink(static_cast<GfObj *>(behavior->unknown08)->unknownf8, false);
  if (!StateBattleActionBase::Enter(behavior, previous)) {
    return false;
  }
  DataParamAcc acc(static_cast<GfObj *>(behavior->unknown08)->unknownf8);
  u32 weaponType = acc.getWeaponType(-1, false);
  GetBattleCharacter()->SetWeaponType(weaponType);
  return true;
}

void StateBattleStart::Leave(GfComBehaviorPc *behavior, ai::State *next) {}

void StateBattleStart::Update(btl::BattleCharacter *character, GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  StateBattleActionBase::Update(character, behavior, info);
  if (unknown21) {
    return;
  }

  const GfPropertyBattle *battle = GetBattlePropertyConst();
  switch (battle->unknown14) {
  case 0:
    ChangeState(STATE_ID_UNKNOWN_65, 0);
    break;
  case 1:
    ChangeState(STATE_ID_UNKNOWN_64, 1);
    break;
  case 2:
    ChangeState(STATE_ID_UNKNOWN_80, 1);
    break;
  case 3:
    ChangeState(STATE_ID_UNKNOWN_64, battle->unknown15 << 16 | battle->unknown16);
    break;
  default:
    ChangeState(STATE_ID_UNKNOWN_65, 0);
    break;
  }
}

} // namespace pc
} // namespace gf
