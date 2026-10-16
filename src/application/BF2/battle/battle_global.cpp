#include "battle/battle_global.h"

#include "battle/character/battle_character.h"
#include "battle/character/character_manager_battle.h"
#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/game/gf_game_manager.h"
#include "gf/gf_allocator.h"
#include "gf/object/gf_obj_handle.h"

namespace btl {

constexpr int ELEMENTAL_COMBO_NUM = 50;
constexpr int MAP_DRIVER_REV_NUM = 9;
constexpr int ATTACK_ATTRIBUTE_NONE = 9;
constexpr f32 DAMAGE_RATE_SCALE = 65536.0f;

void BattleGlobal::Create() {
  // __LINE__ must be 265 as in the original file: its value changes the instruction order.
#line 265
  BattleGlobal *global = new (gf::getAllocator(gf::ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) BattleGlobal();
  global->Initialize();
}

int BattleGlobal::GetNormalAttackArtsID(int type, int weapon, int index) const {
  u16 arts = normalAttackArtsIds[type][weapon][index];
  if (arts == 0) {
    arts = normalAttackArtsIds[0][weapon][index];
  }

  return arts;
}

const BattleGlobal::ELEMENTAL_COMBO_FLOW_DATA *BattleGlobal::GetElementalComboFlowData(int combo) const {
  return &elementalComboFlows[combo >= 0 && combo < ELEMENTAL_COMBO_NUM ? combo : 0];
}

int BattleGlobal::GetElementalComboStage(int combo) const { return GetElementalComboFlowData(combo)->stage; }

void BattleGlobal::PreUpdate(const fw::UpdateInfo &updateInfo) { get()->PreUpdateProc(updateInfo); }

void BattleGlobal::Update(const fw::UpdateInfo &updateInfo) { get()->UpdateProc(updateInfo); }

bool BattleGlobal::IsSlowProc(u32 slow) const { return GetSlowProcDataConst(slow) != nullptr; }

void BattleGlobal::PostUpdate(const fw::UpdateInfo &updateInfo) { get()->PostUpdateProc(updateInfo); }

void BattleGlobal::ResetBGM() {
  bgm = 0;
  bgmPriority = 0xff;
}

void BattleGlobal::SetElementalComboImmortal(gf::GF_OBJ_HANDLE *handle) { elementalComboImmortal = handle; }

bool BattleGlobal::IsEnableBattle() const { return !gf::GfGameManager::isBattleStop(); }

int BattleGlobal::GetAttackDamageDataNum() const { return attackDamages.size(); }

const BattleGlobal::ATTACK_DAMAGE_DATA *BattleGlobal::GetAttackDamageDataConst(u32 attack) const {
  if (attack == 0) {
    return nullptr;
  }

  for (const ATTACK_DAMAGE_DATA &data : attackDamages) {
    if (data.id == attack) {
      data.isUpdated = true;
      return &data;
    }
  }

  return nullptr;
}

void BattleGlobal::UpdateAttackData(u32 attack) { GetAttackDamageDataConst(attack); }

int BattleGlobal::GetAttackDamage(u32 attack) const {
  const ATTACK_DAMAGE_DATA *data = GetAttackDamageDataConst(attack);
  if (data == nullptr) {
    return -1;
  }

  return data->damage;
}

gf::GF_OBJ_HANDLE *BattleGlobal::GetAttackMainTargetHandle(u32 attack) const {
  const ATTACK_DAMAGE_DATA *data = GetAttackDamageDataConst(attack);
  if (data == nullptr) {
    return gf::INVALID_HANDLE;
  }

  return CharacterManager::get()->GetCharacterHandle(data->mainTarget);
}

void BattleGlobal::SetAttackAttr(u32 attack, int attribute) {
  ATTACK_DAMAGE_DATA *data = const_cast<ATTACK_DAMAGE_DATA *>(GetAttackDamageDataConst(attack));
  if (data != nullptr) {
    data->attribute = attribute;
  }
}

int BattleGlobal::GetAttackAttr(u32 attack) const {
  const ATTACK_DAMAGE_DATA *data = GetAttackDamageDataConst(attack);
  if (data != nullptr) {
    int attribute = data->attribute;
    if (attribute != ATTACK_ATTRIBUTE_NONE) {
      return attribute;
    }
  }

  return -1;
}

void BattleGlobal::SetEndDropHealPot2(u32 attack) {
  ATTACK_DAMAGE_DATA *data = const_cast<ATTACK_DAMAGE_DATA *>(GetAttackDamageDataConst(attack));
  if (data != nullptr) {
    data->isEndDropHealPot2 = true;
  }
}

bool BattleGlobal::IsEndDropHealPot2(u32 attack) const {
  const ATTACK_DAMAGE_DATA *data = GetAttackDamageDataConst(attack);
  return data != nullptr ? data->isEndDropHealPot2 : false;
}

void BattleGlobal::SetCriticalRecastEnhanceEnd(u32 attack) {
  ATTACK_DAMAGE_DATA *data = const_cast<ATTACK_DAMAGE_DATA *>(GetAttackDamageDataConst(attack));
  if (data != nullptr) {
    data->isEndCriticalRecastEnhance = true;
  }
}

bool BattleGlobal::IsEndCriticalRecastEnhance(u32 attack) const {
  const ATTACK_DAMAGE_DATA *data = GetAttackDamageDataConst(attack);
  return data != nullptr ? data->isEndCriticalRecastEnhance : false;
}

void BattleGlobal::SetJustDistanceAttack(u32 attack) {
  ATTACK_DAMAGE_DATA *data = const_cast<ATTACK_DAMAGE_DATA *>(GetAttackDamageDataConst(attack));
  if (data != nullptr) {
    data->isJustDistanceAttack = true;
  }
}

bool BattleGlobal::IsJustDistanceAttack(u32 attack) const {
  const ATTACK_DAMAGE_DATA *data = GetAttackDamageDataConst(attack);
  return data != nullptr ? data->isJustDistanceAttack : false;
}

void BattleGlobal::SetEnableAddElementalBall(u32 attack, bool isEnable) {
  ATTACK_DAMAGE_DATA *data = const_cast<ATTACK_DAMAGE_DATA *>(GetAttackDamageDataConst(attack));
  if (data != nullptr) {
    data->isEnableAddElementalBall = isEnable;
  }
}

bool BattleGlobal::IsEnableAddElementalBall(u32 attack) const {
  const ATTACK_DAMAGE_DATA *data = GetAttackDamageDataConst(attack);
  return data != nullptr ? data->isEnableAddElementalBall : true;
}

void BattleGlobal::SetResistantBreakDamageEnd(u32 attack) {
  ATTACK_DAMAGE_DATA *data = const_cast<ATTACK_DAMAGE_DATA *>(GetAttackDamageDataConst(attack));
  if (data != nullptr) {
    data->isResistantBreakDamageEnd = true;
  }
}

bool BattleGlobal::IsEnableResistantBreakDamage(u32 attack) const {
  const ATTACK_DAMAGE_DATA *data = GetAttackDamageDataConst(attack);
  return data != nullptr ? !data->isResistantBreakDamageEnd : false;
}

void BattleGlobal::SetPermitArts(u32 attack) {
  ATTACK_DAMAGE_DATA *data = const_cast<ATTACK_DAMAGE_DATA *>(GetAttackDamageDataConst(attack));
  if (data != nullptr) {
    data->isPermitArts = true;
  }
}

bool BattleGlobal::IsPermitArts(u32 attack) const {
  const ATTACK_DAMAGE_DATA *data = GetAttackDamageDataConst(attack);
  return data != nullptr ? data->isPermitArts : false;
}

void BattleGlobal::SetShootBullet(u32 attack, bool isShoot) {
  ATTACK_DAMAGE_DATA *data = const_cast<ATTACK_DAMAGE_DATA *>(GetAttackDamageDataConst(attack));
  if (data != nullptr) {
    data->isNotShootBullet = !isShoot;
  }
}

bool BattleGlobal::IsShootBullet(u32 attack) const {
  const ATTACK_DAMAGE_DATA *data = GetAttackDamageDataConst(attack);
  return data != nullptr ? !data->isNotShootBullet : true;
}

void BattleGlobal::SetValidAttackRange(u32 attack, bool isValid) {
  ATTACK_DAMAGE_DATA *data = const_cast<ATTACK_DAMAGE_DATA *>(GetAttackDamageDataConst(attack));
  if (data != nullptr) {
    data->isValidAttackRange = isValid;
  }
}

bool BattleGlobal::IsValidAttackRange(u32 attack) const {
  const ATTACK_DAMAGE_DATA *data = GetAttackDamageDataConst(attack);
  return data != nullptr ? data->isValidAttackRange : true;
}

void BattleGlobal::SetDamageRate(u32 attack, f32 rate, bool isOverwrite) {
  ATTACK_DAMAGE_DATA *data = const_cast<ATTACK_DAMAGE_DATA *>(GetAttackDamageDataConst(attack));
  if (data == nullptr) {
    return;
  }

  data->damageRate = static_cast<u32>(rate * DAMAGE_RATE_SCALE);
  if (isOverwrite) {
    data->isOverwriteDamageRate = true;
  }
}

void BattleGlobal::AddDamageRate(u32 attack, f32 rate, bool isOverwrite) {
  ATTACK_DAMAGE_DATA *data = const_cast<ATTACK_DAMAGE_DATA *>(GetAttackDamageDataConst(attack));
  if (data == nullptr) {
    return;
  }

  data->damageRate = static_cast<u32>((static_cast<u32>(data->damageRate) * (1.0f / DAMAGE_RATE_SCALE) + rate) * DAMAGE_RATE_SCALE);
  if (isOverwrite) {
    data->isOverwriteDamageRate = true;
  }
}

void BattleGlobal::MulDamageRate(u32 attack, f32 rate, bool isOverwrite) {
  ATTACK_DAMAGE_DATA *data = const_cast<ATTACK_DAMAGE_DATA *>(GetAttackDamageDataConst(attack));
  if (data == nullptr) {
    return;
  }

  data->damageRate = static_cast<u32>(static_cast<u32>(data->damageRate) * (1.0f / DAMAGE_RATE_SCALE) * rate * DAMAGE_RATE_SCALE);
  if (isOverwrite) {
    data->isOverwriteDamageRate = true;
  }
}

f32 BattleGlobal::GetDamageRate(u32 attack, bool *isOverwrite) const {
  const ATTACK_DAMAGE_DATA *data = GetAttackDamageDataConst(attack);
  if (data != nullptr) {
    if (isOverwrite != nullptr) {
      *isOverwrite = data->isOverwriteDamageRate;
    }

    return static_cast<u32>(data->damageRate) * (1.0f / DAMAGE_RATE_SCALE);
  }

  if (isOverwrite != nullptr) {
    *isOverwrite = false;
  }

  return 1.0f;
}

void BattleGlobal::SetPause(int pause, bool isPause) {
  pauseFlags[pause >> 3] = isPause ? pauseFlags[pause >> 3] | (1 << (pause & 7)) : pauseFlags[pause >> 3] & ~(1 << (pause & 7));
}

bool BattleGlobal::IsPause(int pause) const {
  if (pause >= 0) {
    return (pauseFlags[pause >> 3] & (1 << (pause & 7))) != 0;
  }

  return pauseFlags[0] != 0;
}

void BattleGlobal::RegisterStop(f32 time) { stopTime = stopTime > time ? stopTime : time; }

const BattleGlobal::SLOW_PROC_DATA *BattleGlobal::GetSlowProcDataConst(u32 slow) const {
  if (slow == 0) {
    return nullptr;
  }

  for (const SLOW_PROC_DATA &data : slowProcs) {
    if (data.id == slow) {
      return &data;
    }
  }

  return nullptr;
}

void BattleGlobal::SetBGM(u32 bgm) {
  if (bgm == 0) {
    return;
  }

  u8 priority = Bdat::getValCheck(gf::GfDataBdat::getFP(gf::BDAT_RSC_BGM_CONDITION), "Priority", bgm, 1);
  if (bgmPriority == 0xff || priority > bgmPriority) {
    this->bgm = bgm;
    bgmPriority = priority;
  }
}

void BattleGlobal::RequestJingle(JINGLE_TYPE jingle) { requestJingle = jingle; }

bool BattleGlobal::IsJinglePlaying() const { return jingleHandle != reinterpret_cast<gf::GF_SE_CATEGORY_HANDLE *>(-1); }

const BattleGlobal::MAP_DRIVER_REV_DATA *BattleGlobal::GetMapDriverRevData(const BattleCharacter *character) const {
  if (character != nullptr && character->IsPlayer() && character->IsDriver()) {
    return GetMapDriverRevDataByBdatID(character->bdatId);
  }

  return nullptr;
}

const BattleGlobal::MAP_DRIVER_REV_DATA *BattleGlobal::GetMapDriverRevDataByBdatID(int driver) const {
  int index = driver - 1;
  return index >= 0 && index < MAP_DRIVER_REV_NUM ? &mapDriverRevs[index] : nullptr;
}

int BattleGlobal::GetKizunaMax(const BattleCharacter *character) const {
  const MAP_DRIVER_REV_DATA *data = GetMapDriverRevData(character);
  if (data == nullptr) {
    return 1000;
  }

  return data->kizunaMax;
}

int BattleGlobal::GetSpLevelMax(const BattleCharacter *character) const {
  const MAP_DRIVER_REV_DATA *data = GetMapDriverRevData(character);
  if (data == nullptr) {
    return 4;
  }

  return data->spLevelMax;
}

bool BattleGlobal::IsEnableSupport(const BattleCharacter *character) const {
  const MAP_DRIVER_REV_DATA *data = GetMapDriverRevData(character);
  if (data == nullptr) {
    return true;
  }

  return data->isEnableSupport;
}

} // namespace btl
