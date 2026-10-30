#include "gf/object/component/enemy/gf_enemy_battle_property.h"

#include "battle/battle_global.h"
#include "battle/btl_system_balance_access.h"
#include "battle/character/battle_character.h"
#include "battle/character/character_manager_battle.h"
#include "battle/character/character_parameter_battle.h"
#include "gf/object/component/enemy/gf_com_property_enemy.h"
#include "gf/object/component/enemy/gf_enemy_asm_callback.h"
#include "gf/object/gf_obj.h"

namespace anm {
class ResASM;
} // namespace anm

namespace gf {
struct GF_OBJ_HANDLE;

namespace enemy {

bool registerAsmCallbackBattle(GF_OBJ_HANDLE *handle, anm::ResASM *resAsm) { return false; }

GfEnemyBattleProperty::GfEnemyBattleProperty() {
  _10 = 0xffffffff;
  unknown1e = false;
  unknown1f = false;
}

void GfEnemyBattleProperty::Initialize(const GfComPropertyEnemy &property) {
  _10 = btl::CharacterManager::get()->Register(static_cast<GfObj *>(property.unknown08)->unknownf8, true);
  unknown00 = mm::Vec3::zero;
  unknown14 = -1.0f;
  unknown18 = -1.0f;
  unknown1c = 0;
  unknown1d = 0;
  unknown1e = false;
  unknown1f = false;
}

void GfEnemyBattleProperty::Finalize(const GfComPropertyEnemy &property) {
  if (_10 >= 0) {
    btl::CharacterManager::get()->Release(_10, static_cast<GfObj *>(property.unknown08)->unknownf8);
    _10 = -1;
  }
}

const btl::CharacterParameter *GfEnemyBattleProperty::GetCharacterParameterConst() const {
  int id = _10;
  btl::BattleCharacter *character = btl::CharacterManager::get()->GetCharacterConst(id);
  return character->GetCharacterParameterConst(true);
}

const btl::EnemyParameter *GfEnemyBattleProperty::GetEnemyParameterConst() const { return static_cast<const btl::EnemyParameter *>(GetCharacterParameterConst()); }

f32 GfEnemyBattleProperty::GetReturnHomeDistance() const {
  if (!btl::BattleGlobal::get()->unknown65e0_5) {
    return unknown14;
  }

  return btl::BtlSystemBalanceAccess::get()->unknownaa;
}

f32 GfEnemyBattleProperty::GetReturnHomeCharacterDistance() const {
  if (!btl::BattleGlobal::get()->unknown65e0_5) {
    return unknown18;
  }

  return btl::BtlSystemBalanceAccess::get()->unknownaa;
}

void GfEnemyBattleProperty::NotifyDamage(const MsgObjectNotifyDamage &message) {
  btl::BattleCharacter *character = btl::CharacterManager::get()->GetCharacterConst(_10);
  if (character != nullptr) {
    character->NotifySufferDamage(message);
  }
}

} // namespace enemy
} // namespace gf
