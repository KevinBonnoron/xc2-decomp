#include "battle/battle_global.h"

#include "battle/character/battle_character.h"
#include "battle/character/character_manager_battle.h"
#include "battle/misc_battle.h"
#include "battle/shake_camera_manager.h"
#include "battle/ui_manager_battle.h"
#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/game/gf_game_manager.h"
#include "gf/gf_allocator.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/object/gf_obj_handle.h"

namespace btl {

constexpr int ELEMENTAL_COMBO_NUM = 50;
constexpr int MAP_DRIVER_REV_NUM = 9;
constexpr int ATTACK_ATTRIBUTE_NONE = 9;
constexpr f32 DAMAGE_RATE_SCALE = 65536.0f;
constexpr u32 SE_COMMON_ERROR = 2;

void BattleGlobal::Create() {
  // __LINE__ must be 265 as in the original file: its value changes the instruction order.
#line 265
  BattleGlobal *global = new (gf::getAllocator(gf::ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) BattleGlobal();
  global->Initialize();
}

void BattleGlobal::Destroy() {
  BattleGlobal *global = get();
  global->Finalize();
  if (global != nullptr) {
    delete global;
  }
}

void BattleGlobal::Finalize() {
  if (unknown5e0 != nullptr) {
    delete unknown5e0;
    unknown5e0 = nullptr;
  }
}

int BattleGlobal::GetNormalAttackArtsID(int type, int weapon, int index) const {
  u16 arts = unknown5b90[type][weapon][index];
  if (arts == 0) {
    arts = unknown5b90[0][weapon][index];
  }

  return arts;
}

const BattleGlobal::ELEMENTAL_COMBO_FLOW_DATA *BattleGlobal::GetElementalComboFlowData(int combo) const {
  return &unknown56a0[combo >= 0 && combo < ELEMENTAL_COMBO_NUM ? combo : 0];
}

int BattleGlobal::GetElementalComboStage(int combo) const { return GetElementalComboFlowData(combo)->unknown01_0; }

int BattleGlobal::GetFirstStageElementalComboData(int combo) const {
  int first;
  bool isFirstStage;
  do {
    first = combo;
    if (first == 0) {
      break;
    }
    const ELEMENTAL_COMBO_FLOW_DATA *flow = GetElementalComboFlowData(first);
    isFirstStage = flow->unknown01_0 == 1;
    combo = flow->unknown00;
  } while (!isFirstStage);
  return first;
}

void BattleGlobal::PreUpdate(const fw::UpdateInfo &updateInfo) { get()->PreUpdateProc(updateInfo); }

void BattleGlobal::Update(const fw::UpdateInfo &updateInfo) { get()->UpdateProc(updateInfo); }

bool BattleGlobal::IsSlowProc(u32 slow) const { return GetSlowProcDataConst(slow) != nullptr; }

void BattleGlobal::PostUpdate(const fw::UpdateInfo &updateInfo) { get()->PostUpdateProc(updateInfo); }

void BattleGlobal::ResetBGM() {
  unknown65d2 = 0;
  unknown65d4 = 0xff;
}

void BattleGlobal::SetElementalComboImmortal(gf::GF_OBJ_HANDLE *handle) { m_elementalComboImmortal = handle; }

bool BattleGlobal::IsGameOver() const {
  if (unknown65e0_0) {
    return true;
  }
  return gf::GfGameManager::isPlayerDeadSequence();
}

bool BattleGlobal::IsEnableBattle() const { return !gf::GfGameManager::isBattleStop(); }

void BattleGlobal::NotifyShiftNone() {
  unknown65e1_6 = false;
  unknown65e1_7 = false;
}

void BattleGlobal::NotifyShiftTimeOver() {
  if (UIManager::get()->unknown44_7) {
    unknown65e1_7 = true;
  }
}

int BattleGlobal::GetAttackDamageDataNum() const { return unknown878.size(); }

const BattleGlobal::ATTACK_DAMAGE_DATA *BattleGlobal::GetAttackDamageDataConst(u32 attack) const {
  if (attack == 0) {
    return nullptr;
  }

  for (const ATTACK_DAMAGE_DATA &data : unknown878) {
    if (data.unknown00 == attack) {
      data.unknown10_7 = true;
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

  return data->unknown04;
}

gf::GF_OBJ_HANDLE *BattleGlobal::GetAttackMainTargetHandle(u32 attack) const {
  const ATTACK_DAMAGE_DATA *data = GetAttackDamageDataConst(attack);
  if (data == nullptr) {
    return gf::INVALID_HANDLE;
  }

  return CharacterManager::get()->GetCharacterHandle(data->unknown13);
}

void BattleGlobal::SetAttackAttr(u32 attack, int attribute) {
  ATTACK_DAMAGE_DATA *data = const_cast<ATTACK_DAMAGE_DATA *>(GetAttackDamageDataConst(attack));
  if (data != nullptr) {
    data->unknown0b_3 = attribute;
  }
}

int BattleGlobal::GetAttackAttr(u32 attack) const {
  const ATTACK_DAMAGE_DATA *data = GetAttackDamageDataConst(attack);
  if (data != nullptr) {
    int attribute = data->unknown0b_3;
    if (attribute != ATTACK_ATTRIBUTE_NONE) {
      return attribute;
    }
  }

  return -1;
}

void BattleGlobal::SetEndDropHealPot2(u32 attack) {
  ATTACK_DAMAGE_DATA *data = const_cast<ATTACK_DAMAGE_DATA *>(GetAttackDamageDataConst(attack));
  if (data != nullptr) {
    data->unknown10_5 = true;
  }
}

bool BattleGlobal::IsEndDropHealPot2(u32 attack) const {
  const ATTACK_DAMAGE_DATA *data = GetAttackDamageDataConst(attack);
  return data != nullptr ? data->unknown10_5 : false;
}

void BattleGlobal::SetCriticalRecastEnhanceEnd(u32 attack) {
  ATTACK_DAMAGE_DATA *data = const_cast<ATTACK_DAMAGE_DATA *>(GetAttackDamageDataConst(attack));
  if (data != nullptr) {
    data->unknown10_6 = true;
  }
}

bool BattleGlobal::IsEndCriticalRecastEnhance(u32 attack) const {
  const ATTACK_DAMAGE_DATA *data = GetAttackDamageDataConst(attack);
  return data != nullptr ? data->unknown10_6 : false;
}

void BattleGlobal::SetJustDistanceAttack(u32 attack) {
  ATTACK_DAMAGE_DATA *data = const_cast<ATTACK_DAMAGE_DATA *>(GetAttackDamageDataConst(attack));
  if (data != nullptr) {
    data->unknown10_0 = true;
  }
}

bool BattleGlobal::IsJustDistanceAttack(u32 attack) const {
  const ATTACK_DAMAGE_DATA *data = GetAttackDamageDataConst(attack);
  return data != nullptr ? data->unknown10_0 : false;
}

void BattleGlobal::SetEnableAddElementalBall(u32 attack, bool isEnable) {
  ATTACK_DAMAGE_DATA *data = const_cast<ATTACK_DAMAGE_DATA *>(GetAttackDamageDataConst(attack));
  if (data != nullptr) {
    data->unknown12_0 = isEnable;
  }
}

bool BattleGlobal::IsEnableAddElementalBall(u32 attack) const {
  const ATTACK_DAMAGE_DATA *data = GetAttackDamageDataConst(attack);
  return data != nullptr ? data->unknown12_0 : true;
}

void BattleGlobal::SetResistantBreakDamageEnd(u32 attack) {
  ATTACK_DAMAGE_DATA *data = const_cast<ATTACK_DAMAGE_DATA *>(GetAttackDamageDataConst(attack));
  if (data != nullptr) {
    data->unknown10_1 = true;
  }
}

bool BattleGlobal::IsEnableResistantBreakDamage(u32 attack) const {
  const ATTACK_DAMAGE_DATA *data = GetAttackDamageDataConst(attack);
  return data != nullptr ? !data->unknown10_1 : false;
}

void BattleGlobal::SetPermitArts(u32 attack) {
  ATTACK_DAMAGE_DATA *data = const_cast<ATTACK_DAMAGE_DATA *>(GetAttackDamageDataConst(attack));
  if (data != nullptr) {
    data->unknown10_2 = true;
  }
}

bool BattleGlobal::IsPermitArts(u32 attack) const {
  const ATTACK_DAMAGE_DATA *data = GetAttackDamageDataConst(attack);
  return data != nullptr ? data->unknown10_2 : false;
}

void BattleGlobal::SetShootBullet(u32 attack, bool isShoot) {
  ATTACK_DAMAGE_DATA *data = const_cast<ATTACK_DAMAGE_DATA *>(GetAttackDamageDataConst(attack));
  if (data != nullptr) {
    data->unknown10_3 = !isShoot;
  }
}

bool BattleGlobal::IsShootBullet(u32 attack) const {
  const ATTACK_DAMAGE_DATA *data = GetAttackDamageDataConst(attack);
  return data != nullptr ? !data->unknown10_3 : true;
}

void BattleGlobal::SetValidAttackRange(u32 attack, bool isValid) {
  ATTACK_DAMAGE_DATA *data = const_cast<ATTACK_DAMAGE_DATA *>(GetAttackDamageDataConst(attack));
  if (data != nullptr) {
    data->unknown12_1 = isValid;
  }
}

bool BattleGlobal::IsValidAttackRange(u32 attack) const {
  const ATTACK_DAMAGE_DATA *data = GetAttackDamageDataConst(attack);
  return data != nullptr ? data->unknown12_1 : true;
}

void BattleGlobal::SetDamageRate(u32 attack, f32 rate, bool isOverwrite) {
  ATTACK_DAMAGE_DATA *data = const_cast<ATTACK_DAMAGE_DATA *>(GetAttackDamageDataConst(attack));
  if (data == nullptr) {
    return;
  }

  data->unknown08_0 = static_cast<u32>(rate * DAMAGE_RATE_SCALE);
  if (isOverwrite) {
    data->unknown10_4 = true;
  }
}

void BattleGlobal::AddDamageRate(u32 attack, f32 rate, bool isOverwrite) {
  ATTACK_DAMAGE_DATA *data = const_cast<ATTACK_DAMAGE_DATA *>(GetAttackDamageDataConst(attack));
  if (data == nullptr) {
    return;
  }

  data->unknown08_0 = static_cast<u32>((static_cast<u32>(data->unknown08_0) * (1.0f / DAMAGE_RATE_SCALE) + rate) * DAMAGE_RATE_SCALE);
  if (isOverwrite) {
    data->unknown10_4 = true;
  }
}

void BattleGlobal::MulDamageRate(u32 attack, f32 rate, bool isOverwrite) {
  ATTACK_DAMAGE_DATA *data = const_cast<ATTACK_DAMAGE_DATA *>(GetAttackDamageDataConst(attack));
  if (data == nullptr) {
    return;
  }

  data->unknown08_0 = static_cast<u32>(static_cast<u32>(data->unknown08_0) * (1.0f / DAMAGE_RATE_SCALE) * rate * DAMAGE_RATE_SCALE);
  if (isOverwrite) {
    data->unknown10_4 = true;
  }
}

f32 BattleGlobal::GetDamageRate(u32 attack, bool *isOverwrite) const {
  const ATTACK_DAMAGE_DATA *data = GetAttackDamageDataConst(attack);
  if (data != nullptr) {
    if (isOverwrite != nullptr) {
      *isOverwrite = data->unknown10_4;
    }

    return static_cast<u32>(data->unknown08_0) * (1.0f / DAMAGE_RATE_SCALE);
  }

  if (isOverwrite != nullptr) {
    *isOverwrite = false;
  }

  return 1.0f;
}

void BattleGlobal::SetPause(int pause, bool isPause) {
  unknown65d6[pause >> 3] = isPause ? unknown65d6[pause >> 3] | (1 << (pause & 7)) : unknown65d6[pause >> 3] & ~(1 << (pause & 7));
}

bool BattleGlobal::IsPause(int pause) const {
  if (pause >= 0) {
    return (unknown65d6[pause >> 3] & (1 << (pause & 7))) != 0;
  }

  return unknown65d6[0] != 0;
}

void BattleGlobal::RegisterStop(f32 time) { unknown6b8 = unknown6b8 > time ? unknown6b8 : time; }

const BattleGlobal::SLOW_PROC_DATA *BattleGlobal::GetSlowProcDataConst(u32 slow) const {
  if (slow == 0) {
    return nullptr;
  }

  for (const SLOW_PROC_DATA &data : unknown6c0) {
    if (data.unknown0c == slow) {
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
  if (unknown65d4 == 0xff || priority > unknown65d4) {
    this->unknown65d2 = bgm;
    unknown65d4 = priority;
  }
}

void BattleGlobal::RequestJingle(JINGLE_TYPE jingle) { unknown65d5 = jingle; }

bool BattleGlobal::IsJinglePlaying() const { return unknown5aa0 != reinterpret_cast<gf::GF_SE_CATEGORY_HANDLE *>(-1); }

void BattleGlobal::PlayErrorSE() {
  if (!unknown65e2_2) {
    gf::GfMenuObjUtil::playSECommon(SE_COMMON_ERROR);
    unknown65e2_2 = true;
  }
}

const BattleGlobal::MAP_DRIVER_REV_DATA *BattleGlobal::GetMapDriverRevData(const BattleCharacter *character) const {
  if (character != nullptr && character->IsPlayer() && character->IsDriver()) {
    return GetMapDriverRevDataByBdatID(character->unknowncc8);
  }

  return nullptr;
}

const BattleGlobal::MAP_DRIVER_REV_DATA *BattleGlobal::GetMapDriverRevDataByBdatID(int driver) const {
  int index = driver - 1;
  return index >= 0 && index < MAP_DRIVER_REV_NUM ? &unknown5ac0[index] : nullptr;
}

int BattleGlobal::GetKizunaMax(const BattleCharacter *character) const {
  const MAP_DRIVER_REV_DATA *data = GetMapDriverRevData(character);
  if (data == nullptr) {
    return 1000;
  }

  return data->unknown00_0;
}

f32 BattleGlobal::GetAttackRate(const BattleCharacter *character) const {
  const MAP_DRIVER_REV_DATA *data = GetMapDriverRevData(character);
  if (data == nullptr) {
    return 1.0f;
  }
  return NextFloat(data->unknown02 * 0.01f);
}

f32 BattleGlobal::GetDefenceRate(const BattleCharacter *character) const {
  const MAP_DRIVER_REV_DATA *data = GetMapDriverRevData(character);
  if (data == nullptr) {
    return 1.0f;
  }
  return NextFloat(data->unknown03 * 0.01f);
}

int BattleGlobal::GetSpLevelMax(const BattleCharacter *character) const {
  const MAP_DRIVER_REV_DATA *data = GetMapDriverRevData(character);
  if (data == nullptr) {
    return 4;
  }

  return data->unknown01_3;
}

bool BattleGlobal::IsEnableSupport(const BattleCharacter *character) const {
  const MAP_DRIVER_REV_DATA *data = GetMapDriverRevData(character);
  if (data == nullptr) {
    return true;
  }

  return data->unknown01_7;
}

bool BattleGlobal::IsKakuseiFinished() const { return unknown65df_5; }

bool BattleGlobal::IsKakuseiOrder(bool isCheckRestTime) const {
  if (unknown65df_3) {
    return true;
  }
  if (isCheckRestTime && unknown5b68 >= 0.0f) {
    return true;
  }
  return false;
}

void BattleGlobal::ApplyBattleCameraAdjustment(mm::Vec3 &position, mm::Vec3 &target) {
  if (unknown5e0 != nullptr) {
    unknown5e0->ApplyShake(position, target);
  }
}

} // namespace btl
