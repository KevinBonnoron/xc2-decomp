#include "battle/character/character_parameter_battle.h"

#include <float.h>
#include <math.h>

#include "battle/battle_global.h"
#include "battle/blade_change_manager.h"
#include "battle/chain_attack_manager.h"
#include "battle/character/battle_character.h"
#include "battle/character/character_manager_battle.h"
#include "battle/data_manager_battle.h"
#include "battle/group_data.h"
#include "battle/misc_battle.h"
#include "battle/utility_battle.h"
#include "gf/data/gf_bdat_chrenarrange.h"
#include "gf/data/gf_data_enemy.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/game/gf_game_util.h"
#include "gf/object/component/property/gf_com_property.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_property.h"
#include "gf/object/gf_obj_util.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_vec3.h"

namespace btl {

constexpr f32 DEGREE_TO_RADIAN = 3.14159265f / 180.0f;
constexpr int ENHANCE_LINK_DISTANCE_BONUS = 258;
constexpr int unknown001 = 5; // Inferred role: damage armor buff id; original name unknown.

gf::GfObj *CharacterParameter::GetUserObject() const { return gf::GfObjUtil::getObj(unknown08); }

gf::GfObjPropertyCharacter *CharacterParameter::GetCharacterProperty() const {
  gf::GF_OBJ_HANDLE *handle = unknown08;
  gf::GfObjProperty *property = gf::GfObjUtil::getProperty(handle);
  gf::GfObjAcc acc(handle);
  switch (acc.getType()) {
  case 3:
    return &property->getDriver()->unknown88;
  case 4:
    return &property->getBlade()->unknown88;
  case 5:
    return &property->getEnemy()->unknown88;
  default:
    return nullptr;
  }
}

gf::GfObj *CharacterParameter::GetBuddyObject() const { return gf::GfObjUtil::getObj(unknown10); }

bool CharacterParameter::InitializeEnhance() const {
  unknown5e0_2 = true;
  return true;
}

void CharacterParameter::BattleStart(int) {
  InitializeArtsPalette(0);
  if (unknown20 != BattleGlobal::get()->unknown864 && !BladeChangeManager::get()->IsRegister(unknown08)) {
    ResetRecast();
  }
  unknown20 = BattleGlobal::get()->unknown864;
  unknown5df_1 = true;
}

void CharacterParameter::BattleEnd() {
  ResetRecast();
  unknown5df_1 = false;
}

void CharacterParameter::ResetSpecialEnhanceRate(bool isAll) {
  int last = SPECIAL_ENHANCE_COUNT - 1;
  if (!isAll) {
    last = BattleGlobal::get()->unknown65de_0 ? SPECIAL_ENHANCE_COUNT - 3 : SPECIAL_ENHANCE_COUNT - 1;
  }
  for (int i = 0; i <= last; i++) {
    SetSpecialEnhanceRate(static_cast<SPECIAL_ENHANCE_TYPE>(i), 0.0f);
  }
}

int CharacterParameter::GetClass() const {
  if (unknown5af < 0) {
    gf::DataParamAcc acc(m_invalidTarget ? unknown10 : unknown08);
    return acc.getClass(false);
  }

  return unknown5af;
}

f32 CharacterParameter::GetHPRate() const {
  int hp = gf::GfGameUtil::getNowHp(unknown08, unknown5a7_0, unknown18);
  int maxHp = GetMaxHP();
  if (hp <= 0 || maxHp <= 0) {
    return 0.0f;
  }

  if (hp >= maxHp) {
    return 1.0f;
  }

  return static_cast<f32>(hp) / static_cast<f32>(maxHp);
}

void CharacterParameter::PostUpdate(const fw::UpdateInfo &) {}

gf::GfStatusProperty *CharacterParameter::GetStatusProperty() const {
  gf::GfObj *obj = gf::GfObjUtil::getObj(unknown08);
  if (obj != nullptr) {
    gf::GfComProperty *property = obj->getComponent<gf::GfComProperty>();
    if (property != nullptr) {
      return property->unknown10;
    }
  }

  return nullptr;
}

void CharacterParameter::SetHP(u32 hp) {
  gf::GfStatusProperty *status = GetStatusProperty();
  if (status != nullptr) {
    status->unknown10 = hp;
  }
}

u32 CharacterParameter::GetHP() const { return gf::GfGameUtil::getNowHp(unknown08, unknown5a7_0, unknown18); }

u32 CharacterParameter::GetMaxHP() const {
  u32 maxHp = gf::GfGameUtil::getMaxHp(unknown08, unknown5a7_0, unknown18);
  ENHANCE_DATA data;
  if (GetAdditionalEnhanceEffect(data, ADD_ENHANCE_TYPE_HP, nullptr)) {
    maxHp += static_cast<int>(data.unknown00);
  }

  return maxHp;
}

int CharacterParameter::ApplyStatusEnhance(int value, int rateType, int addType) const {
  ENHANCE_DATA data;
  if (rateType != 0 && GetAdditionalEnhanceEffect(data, rateType, nullptr)) {
    value += static_cast<int>(value * data.unknown00);
  }
  if (addType != 0 && GetAdditionalEnhanceEffect(data, addType, nullptr)) {
    value += static_cast<int>(data.unknown00);
  }
  return value;
}

bool CharacterParameter::IsBuff(int buff) const {
  if (m_invalidTarget) {
    if (unknown5df_6) {
      return false;
    }

    gf::GF_OBJ_HANDLE *handle = unknown10;
    BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
    if (character == nullptr) {
      return false;
    }

    const CharacterParameter *parameter = character->GetCharacterParameterConst(true);
    if (parameter == nullptr) {
      return false;
    }

    return parameter->IsBuff(buff);
  }

  return (unknown599[buff >> 3] & (1 << (buff & 7))) != 0;
}

void CharacterParameter::CheckDebuff() {
  bool isDebuff = false;
  if (unknown598 != 0) {
    int buff = 1;
    for (u32 flags = BattleGlobal::get()->unknown5b88; flags != 0; flags >>= 1, buff++) {
      if ((flags & 1) && IsBuff(buff)) {
        isDebuff = true;
        break;
      }
    }
  }
  unknown5df_7 = isDebuff;
}

void CharacterParameter::ClearBuff(int buff, bool isEnd) {
  f32 rest = FLT_MAX;
  int count = unknown598;
  for (int i = 0; i < count; i++) {
    if (unknown458[i].unknown00 == buff) {
      rest = unknown458[i].unknown08;
      unknown458[i] = unknown458[count - 1];
      unknown458[count - 1] = BUFF_DATA();
      unknown598--;
      break;
    }
  }
  u8 &flags = unknown599[buff >> 3];
  flags &= ~(1 << (buff & 7));
  CharacterManager *manager = CharacterManager::get();
  BattleCharacter *character = manager->GetCharacterConst(unknown5ae);
  if (character != nullptr) {
    character->NotifyBuffEnd(buff, rest, isEnd);
  }
  character = manager->GetCharacterConst(unknown10);
  if (character != nullptr) {
    character->NotifyBuffEnd(buff, rest, isEnd);
  }
  CheckDebuff();
}

u32 CharacterParameter::CalcDamageArmor(u32 damage) {
  damage = CalcDamageArmorEx(damage);
  if (damage == 0) {
    return 0;
  }
  if (!IsBuff(unknown001)) {
    return damage;
  }
  BUFF_DATA *data = const_cast<BUFF_DATA *>(GetBuffDataConst(unknown001, nullptr));
  if (data == nullptr) {
    return damage;
  }
  u32 armor = static_cast<u32>(data->unknown08);
  u32 rest = damage - armor;
  if (damage > armor) {
    ClearBuff(unknown001, false);
    return rest;
  }
  data->unknown08 = static_cast<f32>(armor - damage);
  return 0;
}

void CharacterParameter::AddEnhance(int enhance) const {
  ENHANCE_EFFECT_DATA data;
  if (DataManager::GetEnhanceData(enhance, data, false)) {
    ENHANCE_EFFECT_DATA *effect = const_cast<ENHANCE_EFFECT_DATA *>(GetEnhanceEffectDataConst(data.unknown00));
    if (effect != nullptr) {
      effect->unknown08 += data.unknown08;
      return;
    }
    unknownf0.push_back(data);
    unknown5b0[data.unknown00 >> 3] |= 1 << (data.unknown00 & 7);
  }
}

bool CharacterParameter::SetElementalComboID(int combo, int id) {
  if (unknown5a5 == combo) {
    return false;
  }
  unknown5a5 = combo;
  if (combo == 0) {
    return false;
  }
  bool isUnite = CheckUniteCombo(id, false);
  CharacterManager *manager = CharacterManager::get();
  BattleCharacter *character = manager->GetCharacterConst(id);
  if (character != nullptr) {
    character->NotifyElementalCombo(unknown08, combo, isUnite);
    const CharacterParameter *parameter = character->GetCharacterParameterConst(true);
    if (parameter != nullptr) {
      BattleCharacter *buddy = manager->GetCharacterConst(parameter->unknown10);
      if (buddy != nullptr) {
        buddy->NotifyElementalCombo(unknown08, combo, isUnite);
      }
    }
    int stage = BattleGlobal::get()->GetElementalComboStage(combo);
    int value = stage == 2 ? 11 : -1;
    if (stage == 1) {
      value = 10;
    }
    if (value >= 0) {
      character->FluctuatePartyGauge(value);
    }
  }
  manager->GetCharacterConst(unknown5ae)->NotifySufferElementalCombo(id, combo);
  character = manager->GetCharacterConst(unknown10);
  if (character != nullptr) {
    character->NotifySufferElementalCombo(id, combo);
  }
  if (IsEnemyParameter()) {
    BattleGlobal::get()->Tutorial(BTL_TUTORIAL_COND_UNKNOWN_0B, 0, nullptr);
  }
  return isUnite;
}

void CharacterParameter::AddHP(int value) {
  int hp = GetHP() + value;
  int maxHp = GetMaxHP();
  SetHP(mm::clamp(hp, 0, maxHp));
}

u32 CharacterParameter::GetWeakAttributeFlag() const {
  int attribute = Utility::GetAntiAttribute(GetAttribute());
  return attribute >= 0 ? 1 << attribute : 0;
}

const FIGHT_COMBO_DATA *CharacterParameter::GetFightComboDataConst() const {
  if (unknown5e0_1 && unknownd8.unknown00 != 0) {
    return &unknownd8;
  }
  return &unknownc0;
}

u32 CharacterParameter::GetLevel() const {
  gf::DataParamAcc acc(m_invalidTarget ? unknown10 : unknown08);
  return acc.getLevel(false);
}

void EnemyParameter::AddHate(int index, int type, f32 hate) {
  if (static_cast<u32>(type) < 2) {
    HATE_DATA &data = unknown820[index >= 0 && index < HATE_COUNT ? index : 0];
    data.Set(type, data.unknown00[type] + hate);
  }
}

f32 CharacterParameter::GetBuffEffect(int buff) const {
  for (int i = 0; i < unknown598; i++) {
    if (unknown458[i].unknown00 == buff) {
      return unknown458[i].unknown08;
    }
  }

  return 0.0f;
}

bool CharacterParameter::IsBuffInfinite(int buff) const {
  for (int i = 0; i < unknown598; i++) {
    if (unknown458[i].unknown00 == buff) {
      return unknown458[i].unknown04 < 0.0f;
    }
  }

  return false;
}

const BUFF_DATA *CharacterParameter::GetBuffDataConst(int buff, int *index) const {
  for (int i = 0; i < unknown598; i++) {
    if (unknown458[i].unknown00 == buff) {
      if (index != nullptr) {
        *index = i;
      }

      return &unknown458[i];
    }
  }

  return nullptr;
}

f32 CharacterParameter::GetBuffRestFrame(int buff) const {
  for (int i = 0; i < unknown598; i++) {
    if (unknown458[i].unknown00 == buff) {
      return unknown458[i].unknown04;
    }
  }

  return 0.0f;
}

f32 CharacterParameter::GetBlowRotSpeed() const { return unknown5ad * DEGREE_TO_RADIAN; }

bool CharacterParameter::IsBlowRot() const {
  if (unknown5ad == 0) {
    return false;
  }

  if (unknown5aa == 0 && unknown5ab == 0 && unknown5ac == 0) {
    return false;
  }

  return true;
}

bool CharacterParameter::GetBlowRotAxis(mm::Vec3 &axis) const {
  if ((unknown5aa | unknown5ab | unknown5ac) == 0) {
    return false;
  }

  axis = mm::Vec3(unknown5aa, unknown5ab, unknown5ac);
  f32 length = sqrtf(axis.x * axis.x + axis.y * axis.y + axis.z * axis.z);
  if (length <= 1e-06f) {
    axis = mm::Vec3::zero;
  } else {
    axis = axis * (1.0f / length);
  }
  return true;
}

bool CharacterParameter::IsProgressCoolTime() const {
  if (!unknown5df_1) {
    return false;
  }
  if (ChainAttackManager::get()->IsProc(true)) {
    return false;
  }
  return unknown5df_3;
}

void CharacterParameter::SetupLinkDistanceBonus() const {
  f32 bonus = 0.0f;
  ENHANCE_DATA data;
  if (GetEnhanceEffect(data, ENHANCE_LINK_DISTANCE_BONUS)) {
    bonus += data.unknown00;
  }
  unknown5a2 = bonus;
}

const ENHANCE_EFFECT_DATA *CharacterParameter::GetEnhanceEffectDataConst(int enhance) const {
  for (const ENHANCE_EFFECT_DATA &effect : unknownf0) {
    if (effect.unknown00 == enhance) {
      return &effect;
    }
  }

  return nullptr;
}

void CharacterParameter::SetSpecialEnhanceRate(SPECIAL_ENHANCE_TYPE type, f32 rate, u16 value) {
  if (!m_invalidTarget && unknown10 != gf::INVALID_HANDLE) {
    BattleCharacter *character = CharacterManager::get()->GetCharacterConst(unknown10);
    if (character != nullptr) {
      CharacterParameter *parameter = character->GetCharacterParameter(true);
      if (parameter != nullptr) {
        parameter->SetSpecialEnhanceRate(type, rate);
      }
    }
    return;
  }
  if (static_cast<u32>(type) < SPECIAL_ENHANCE_COUNT) {
    unknown5c[type] = rate;
    unknown94[value] = value;
  }
}

void CharacterParameter::AddSpecialEnhanceRate(SPECIAL_ENHANCE_TYPE type, f32 rate, u16 value) {
  if (!m_invalidTarget && unknown10 != gf::INVALID_HANDLE) {
    BattleCharacter *character = CharacterManager::get()->GetCharacterConst(unknown10);
    if (character != nullptr) {
      CharacterParameter *parameter = character->GetCharacterParameter(true);
      if (parameter != nullptr) {
        parameter->AddSpecialEnhanceRate(type, rate, value);
      }
    }
    return;
  }
  if (static_cast<u32>(type) < SPECIAL_ENHANCE_COUNT && rate != 0.0f) {
    unknown5c[type] += rate;
    unknown94[value] = value;
  }
}

void CharacterParameter::MinSpecialEnhanceRate(SPECIAL_ENHANCE_TYPE type, f32 rate, u16 value) {
  if (!m_invalidTarget && unknown10 != gf::INVALID_HANDLE) {
    BattleCharacter *character = CharacterManager::get()->GetCharacterConst(unknown10);
    if (character != nullptr) {
      CharacterParameter *parameter = character->GetCharacterParameter(true);
      if (parameter != nullptr) {
        parameter->MinSpecialEnhanceRate(type, rate, value);
      }
    }
    return;
  }
  if (static_cast<u32>(type) < SPECIAL_ENHANCE_COUNT && rate != 0.0f) {
    f32 current = unknown5c[type];
    unknown5c[type] = current == 0.0f ? rate : (current < rate ? current : rate);
    unknown94[value] = value;
  }
}

void CharacterParameter::MaxSpecialEnhanceRate(SPECIAL_ENHANCE_TYPE type, f32 rate, u16 value) {
  if (!m_invalidTarget && unknown10 != gf::INVALID_HANDLE) {
    BattleCharacter *character = CharacterManager::get()->GetCharacterConst(unknown10);
    if (character != nullptr) {
      CharacterParameter *parameter = character->GetCharacterParameter(true);
      if (parameter != nullptr) {
        parameter->MaxSpecialEnhanceRate(type, rate, value);
      }
    }
    return;
  }
  if (static_cast<u32>(type) < SPECIAL_ENHANCE_COUNT && rate != 0.0f) {
    f32 current = unknown5c[type];
    unknown5c[type] = current == 0.0f ? rate : (current > rate ? current : rate);
    unknown94[value] = value;
  }
}

f32 CharacterParameter::GetSpecialEnhanceRate(SPECIAL_ENHANCE_TYPE type, int *value) const {
  if (!m_invalidTarget && unknown10 != gf::INVALID_HANDLE) {
    BattleCharacter *character = CharacterManager::get()->GetCharacterConst(unknown10);
    if (character != nullptr) {
      CharacterParameter *parameter = character->GetCharacterParameter(true);
      if (parameter != nullptr) {
        return parameter->GetSpecialEnhanceRate(type, value);
      }
    }
    return 0.0f;
  }
  if (static_cast<u32>(type) < SPECIAL_ENHANCE_COUNT) {
    if (value != nullptr) {
      *value = unknown94[type];
    }
    return unknown5c[type];
  }
  return 0.0f;
}

int CharacterParameter::GetGender() const {
  gf::DataParamAcc acc(unknown08);
  return acc.getGender();
}

int CharacterParameter::GetAttribute() const {
  gf::DataParamAcc acc(unknown08);
  return acc.getAttribute(-1, false);
}

int CharacterParameter::GetBaseSTR() const {
  gf::DataParamAcc acc(m_invalidTarget ? unknown10 : unknown08);
  return acc.getStrength(false);
}

int CharacterParameter::GetBaseDEX() const {
  gf::DataParamAcc acc(m_invalidTarget ? unknown10 : unknown08);
  return acc.getDex(false);
}

int CharacterParameter::GetBaseAGI() const {
  gf::DataParamAcc acc(m_invalidTarget ? unknown10 : unknown08);
  return acc.getAgility(false);
}

int CharacterParameter::GetBaseLUK() const {
  gf::DataParamAcc acc(m_invalidTarget ? unknown10 : unknown08);
  return acc.getLuck(false);
}

int CharacterParameter::GetBaseEtherPower() const {
  gf::DataParamAcc acc(m_invalidTarget ? unknown10 : unknown08);
  return acc.getPowerEther(false);
}

int CharacterParameter::GetBasePArmor() const {
  gf::DataParamAcc acc(m_invalidTarget ? unknown10 : unknown08);
  return acc.getPArmor(false);
}

int CharacterParameter::GetBaseEArmor() const {
  gf::DataParamAcc acc(m_invalidTarget ? unknown10 : unknown08);
  return acc.getEArmor(false);
}

int CharacterParameter::GetBaseCriticalPercent() const {
  gf::DataParamAcc acc(m_invalidTarget ? unknown10 : unknown08);
  return acc.getCriticalRate(false);
}

int CharacterParameter::GetBaseGuardPercent() const {
  gf::DataParamAcc acc(m_invalidTarget ? unknown10 : unknown08);
  return acc.getGuardRate(false);
}

int CharacterParameter::GetBaseResistPowerAttack() const {
  gf::DataParamAcc acc(m_invalidTarget ? unknown10 : unknown08);
  return static_cast<s8>(acc.getResistancePower());
}

int CharacterParameter::GetBaseResistEtherAttack() const {
  gf::DataParamAcc acc(m_invalidTarget ? unknown10 : unknown08);
  return static_cast<s8>(acc.getResistanceEther());
}

void CharacterParameter::GetBaseDamage(u32 &minimum, u32 &maximum) const {
  gf::DataParamAcc acc(m_invalidTarget ? unknown10 : unknown08);
  minimum = acc.getNorAtkDmgMin(false);
  maximum = acc.getNorAtkDmgMax(false);
}

int CharacterParameter::GetSTR() const {
  int value = GetBaseSTR();
  ENHANCE_DATA data;
  if (GetAdditionalEnhanceEffect(data, ADD_ENHANCE_TYPE_STRENGTH_RATE, nullptr)) {
    value += static_cast<int>(value * data.unknown00);
  }

  if (GetAdditionalEnhanceEffect(data, ADD_ENHANCE_TYPE_STRENGTH, nullptr)) {
    value += static_cast<int>(data.unknown00);
  }

  return value;
}

int CharacterParameter::GetDEX() const {
  int value = GetBaseDEX();
  ENHANCE_DATA data;
  if (GetAdditionalEnhanceEffect(data, ADD_ENHANCE_TYPE_DEX_RATE, nullptr)) {
    value += static_cast<int>(value * data.unknown00);
  }

  if (GetAdditionalEnhanceEffect(data, ADD_ENHANCE_TYPE_DEX, nullptr)) {
    value += static_cast<int>(data.unknown00);
  }

  return value;
}

int CharacterParameter::GetAGI() const {
  int value = GetBaseAGI();
  ENHANCE_DATA data;
  if (GetAdditionalEnhanceEffect(data, ADD_ENHANCE_TYPE_AGILITY_RATE, nullptr)) {
    value += static_cast<int>(value * data.unknown00);
  }

  if (GetAdditionalEnhanceEffect(data, ADD_ENHANCE_TYPE_AGILITY, nullptr)) {
    value += static_cast<int>(data.unknown00);
  }

  return value;
}

int CharacterParameter::GetLUK() const {
  int value = GetBaseLUK();
  ENHANCE_DATA data;
  if (GetAdditionalEnhanceEffect(data, ADD_ENHANCE_TYPE_LUCK_RATE, nullptr)) {
    value += static_cast<int>(value * data.unknown00);
  }

  if (GetAdditionalEnhanceEffect(data, ADD_ENHANCE_TYPE_LUCK, nullptr)) {
    value += static_cast<int>(data.unknown00);
  }

  return value;
}

int CharacterParameter::GetEtherPower() const {
  int value = GetBaseEtherPower();
  ENHANCE_DATA data;
  if (GetAdditionalEnhanceEffect(data, ADD_ENHANCE_TYPE_ETHER_POWER_RATE, nullptr)) {
    value += static_cast<int>(value * data.unknown00);
  }

  if (GetAdditionalEnhanceEffect(data, ADD_ENHANCE_TYPE_ETHER_POWER, nullptr)) {
    value += static_cast<int>(data.unknown00);
  }

  return value;
}

int CharacterParameter::GetPArmor() const {
  int value = GetBasePArmor();
  ENHANCE_DATA data;
  if (GetAdditionalEnhanceEffect(data, ADD_ENHANCE_TYPE_PHYSICAL_ARMOR_RATE, nullptr)) {
    value += static_cast<int>(value * data.unknown00);
  }

  if (GetAdditionalEnhanceEffect(data, ADD_ENHANCE_TYPE_PHYSICAL_ARMOR, nullptr)) {
    value += static_cast<int>(data.unknown00);
  }

  return value;
}

int CharacterParameter::GetEArmor() const {
  int value = GetBaseEArmor();
  ENHANCE_DATA data;
  if (GetAdditionalEnhanceEffect(data, ADD_ENHANCE_TYPE_ETHER_ARMOR_RATE, nullptr)) {
    value += static_cast<int>(value * data.unknown00);
  }

  if (GetAdditionalEnhanceEffect(data, ADD_ENHANCE_TYPE_ETHER_ARMOR, nullptr)) {
    value += static_cast<int>(data.unknown00);
  }

  return value;
}

int CharacterParameter::GetCriticalPercent() const {
  int value = GetBaseCriticalPercent();
  ENHANCE_DATA data;
  if (GetAdditionalEnhanceEffect(data, ADD_ENHANCE_TYPE_CRITICAL_RATE, nullptr)) {
    value += static_cast<int>(value * data.unknown00);
  }

  if (GetAdditionalEnhanceEffect(data, ADD_ENHANCE_TYPE_CRITICAL, nullptr)) {
    value += static_cast<int>(data.unknown00);
  }

  return value;
}

int CharacterParameter::GetGuardPercent() const {
  int value = GetBaseGuardPercent();
  ENHANCE_DATA data;
  if (GetAdditionalEnhanceEffect(data, ADD_ENHANCE_TYPE_GUARD_RATE, nullptr)) {
    value += static_cast<int>(value * data.unknown00);
  }

  if (GetAdditionalEnhanceEffect(data, ADD_ENHANCE_TYPE_GUARD, nullptr)) {
    value += static_cast<int>(data.unknown00);
  }

  return value;
}

int CharacterParameter::GetResistPowerAttack() const {
  int value = GetBaseResistPowerAttack();
  ENHANCE_DATA data;
  if (GetAdditionalEnhanceEffect(data, ADD_ENHANCE_TYPE_PHYSICAL_ARMOR_RATE, nullptr)) {
    value += static_cast<int>(value * data.unknown00);
  }

  if (GetAdditionalEnhanceEffect(data, ADD_ENHANCE_TYPE_PHYSICAL_ARMOR, nullptr)) {
    value += static_cast<int>(data.unknown00);
  }

  return value;
}

int CharacterParameter::GetResistEtherAttack() const {
  int value = GetBaseResistEtherAttack();
  ENHANCE_DATA data;
  if (GetAdditionalEnhanceEffect(data, ADD_ENHANCE_TYPE_ETHER_ARMOR_RATE, nullptr)) {
    value += static_cast<int>(value * data.unknown00);
  }

  if (GetAdditionalEnhanceEffect(data, ADD_ENHANCE_TYPE_ETHER_ARMOR, nullptr)) {
    value += static_cast<int>(data.unknown00);
  }

  return value;
}

PlayerParameter::PlayerParameter() : unknown5e8(nullptr), m_artsPaletteNum(0), m_bladeChangeType(0) {}

PlayerParameter::~PlayerParameter() {
  if (unknown5e8 != nullptr) {
    delete[] unknown5e8;
    unknown5e8 = nullptr;
  }
}

void PlayerParameter::ResetUseWeapon() {
  for (int i = 0; i < gf::WEAPON_TYPE_COUNT + 1; i++) {
    unknown5f0[i] = 0;
  }

  unknown65c = 0;
}

void PlayerParameter::CheckChangeArtsPalette() {
  if (unknown5df_0 && !unknown5df_1 && !BattleGlobal::get()->unknown65de_0) {
    InitializeArtsPalette(0);
  }
}

void PlayerParameter::SetupPouchDamageArmor() {
  if (unknown660 >= 0) {
    return;
  }

  f32 rate = DataManager::get()->GetPouchBuffParam(DataManager::POUCH_BUFF_TYPE_DAMAGE_ARMOR, unknown1c);
  int armor = 0;
  if (!(rate <= 0.0f)) {
    u32 maxHp = gf::GfGameUtil::getMaxHp(unknown08, unknown5a7_0, unknown18);
    ENHANCE_DATA data;
    if (GetAdditionalEnhanceEffect(data, ADD_ENHANCE_TYPE_HP, nullptr)) {
      maxHp += static_cast<int>(data.unknown00);
    }
    f32 hp = maxHp;
    armor = NextFloat(rate * 0.01f * hp);
  }
  unknown660 = armor;
}

void PlayerParameter::BattleEnd() {
  CharacterParameter::BattleEnd();
  ResetUseWeapon();
}

void PlayerParameter::BattleEndInitialize() {
  CharacterParameter::BattleEndInitialize();
  unknown660 = -1;
}

void PlayerParameter::WritebackRecast(GROUP_DATA *groupData) {
  if (unknown5df_1 && m_invalidTarget) {
    const ARTS_PALETTE_DATA *palette = GetArtsPaletteDataConst(-1);
    for (int i = 0; i < 3; i++) {
      const ARTS_SLOT_DATA *slot = palette->GetSlotDataConst(i, false);
      bool isValid = slot->unknown00_0 != 0;
      f32 recast = slot->unknown04;
      groupData->unknowne4[i] = isValid ? recast : 0.0f;
    }
  }
}

void PlayerParameter::AddUseWeapon(int weapon) {
  unknown5f0[weapon]++;
  unknown65c++;
}

f32 PlayerParameter::GetUseWeaponRate(int weapon) const {
  if (unknown65c == 0) {
    return weapon == unknownbc_0 ? 1.0f : 0.0f;
  }

  u32 count = unknown5f0[weapon];
  if (count >= unknown65c) {
    return 1.0f;
  }
  return static_cast<f32>(count) / unknown65c;
}

const ARTS_PALETTE_DATA *PlayerParameter::GetArtsPaletteDataConst(int index) const {
  if (index < 0) {
    index = m_invalidTarget ? 0 : GetBladeIndex();
  }

  return &unknown5e8[index];
}

u32 PlayerParameter::CalcDamageArmorEx(u32 damage) {
  SetupPouchDamageArmor();
  u32 armor = unknown660;
  if (armor != 0) {
    if (armor >= damage) {
      unknown660 = armor - damage;
      damage = 0;
    } else {
      damage -= armor;
      unknown660 = 0;
    }
  }
  return damage;
}

void PlayerParameter::ResetRecast() {
  if (unknown5e8 == nullptr) {
    return;
  }

  u8 num = m_artsPaletteNum;
  for (int i = 0; i < num; i++) {
    const_cast<ARTS_PALETTE_DATA *>(GetArtsPaletteDataConst(i))->ResetAllRecast();
  }
}

int PlayerParameter::GetBladeIndex() const {
  gf::DataParamAcc acc(m_invalidTarget ? unknown10 : unknown08);
  return acc.getBladeSet(false);
}

int PlayerParameter::GetWeaponID(int slot) const {
  gf::DataParamAcc acc(m_invalidTarget ? unknown10 : unknown08);
  return acc.getEquipWeapon(slot, false);
}

int PlayerParameter::GetEquipAccessory() const {
  gf::DataParamAcc acc(m_invalidTarget ? unknown10 : unknown08);
  return acc.getEquipAcce(0, false);
}

int PlayerParameter::GetIdeaLevel(int idea) const {
  gf::DataParamAcc acc(m_invalidTarget ? unknown10 : unknown08);
  gf::DataIdeaAcc ideaAcc(acc);
  return ideaAcc.getLevel(idea);
}

EnemyParameter::~EnemyParameter() { DataManager::get()->ReleaseEnemyGroup(unknown08); }

const gf::SDataEnemy *EnemyParameter::GetEnemyData() const {
  gf::DataParamAcc acc(unknown08);
  return acc.getSDataEnemy();
}

void CharacterParameter::SetBuddy(gf::GF_OBJ_HANDLE *handle, bool isIgnoreBuddy) {
  unknown10 = handle;
  this->unknown5df_6 = isIgnoreBuddy;
}

void EnemyParameter::BattleEnd() {
  CharacterParameter::BattleEnd();
  DataManager::get()->ReleaseEnemyGroup(unknown08);
}

void EnemyParameter::BattleEndInitialize() { CharacterParameter::BattleEndInitialize(); }

void EnemyParameter::MulHate(int index, int type, f32 rate) {
  if (static_cast<u32>(type) < 2) {
    HATE_DATA &data = unknown820[index >= 0 && index < HATE_COUNT ? index : 0];
    data.Set(type, data.unknown00[type] * rate);
  }
}

int EnemyParameter::GetBGMID() const {
  const gf::SDataEnemy *data = GetEnemyData();
  if (data == nullptr) {
    return 0;
  }

  return gf::GfBdatChrEnArrange::get()->getChrEnArrangeBGMID(data->unknown00);
}

void EnemyParameter::SetupBGM() {
  int bgm = GetBGMID();
  BattleGlobal::get()->SetBGM(bgm);
}

int EnemyParameter::GetAttribute() const {
  if (m_overwriteAttr <= ATTRIBUTE_COUNT) {
    return m_overwriteAttr;
  }

  if (IsAngry() && m_angryAttr <= ATTRIBUTE_COUNT) {
    return m_angryAttr;
  }

  gf::DataParamAcc acc(unknown08);
  return acc.getAttribute(-1, false);
}

void EnemyParameter::CheckChangeAttr() {
  if (!unknown5df_1) {
    unknown869 = 9;
    return;
  }

  int attribute = GetAttribute();
  int oldAttribute = unknown869;
  if (oldAttribute < 9 && attribute != oldAttribute) {
    mm::mtl::FixedVector<u8, CHARACTER_COUNT> list;
    Utility::GetCharacterList(list, unknown08, Utility::CHECK_CHR_NUM_MODE_ENEMY, Utility::CHARACTER_LIST_BATTLE | Utility::CHARACTER_LIST_ALIVE | Utility::CHARACTER_LIST_EXCLUDE_BLADE);
    CharacterManager *characterManager = CharacterManager::get();
    for (u8 id : list) {
      BattleCharacter *character = characterManager->GetCharacterConst(id);
      character->NotifyChangeAttr(unknown08, attribute, oldAttribute);
    }
  }
  unknown869 = attribute;
}

void EnemyParameter::SetBuddy(gf::GF_OBJ_HANDLE *handle, bool isIgnoreBuddy) {
  unknown10 = handle;
  unknown5df_6 = isIgnoreBuddy;
  gf::GF_OBJ_HANDLE *self = unknown08;
  if (handle == gf::INVALID_HANDLE) {
    DataManager::get()->ReleaseEnemyGroup(self);
    return;
  }

  int group = DataManager::get()->GetEnemyGroupIndex(self);
  if (group < 0) {
    gf::GF_OBJ_HANDLE *leader = CharacterParameter::m_invalidTarget ? handle : self;
    gf::GF_OBJ_HANDLE *member = CharacterParameter::m_invalidTarget ? self : handle;
    group = DataManager::get()->RegisterEnemyGroup(leader, member);
  }
  unknown1c = group < 0 ? -1 : group;
}

void EnemyParameter::AngryInfection(f32 range) {
  mm::mtl::FixedVector<u8, CHARACTER_COUNT> list;
  if (Utility::GetCharacterList(list, unknown08, Utility::CHECK_CHR_NUM_MODE_FRIEND, 0x1a) < 1) {
    return;
  }

  CharacterManager *characterManager = CharacterManager::get();
  BattleCharacter *center = characterManager->GetCharacterConst(unknown5ae);
  mm::Vec3 centerPosition = center->unknown10;
  for (u8 id : list) {
    BattleCharacter *character = characterManager->GetCharacterConst(id);
    CharacterParameter *parameter = character->GetCharacterParameter(true);
    if (Misc::CheckInRange(centerPosition, character, parameter->unknown2c + range, false) && !parameter->IsAngry()) {
      parameter->SetAngry(true, -1.0f);
    }
  }
}

int EnemyParameter::GetWeaponID(int) const {
  gf::DataParamAcc acc(CharacterParameter::m_invalidTarget ? unknown10 : unknown08);
  return acc.getEquipWeapon(0, false);
}

bool EnemyParameter::IsBoss() const {
  const gf::SDataEnemy *data = GetEnemyData();
  return data != nullptr && data->unknown04_1;
}

bool EnemyParameter::IsNamed() const {
  const gf::SDataEnemy *data = GetEnemyData();
  return data != nullptr && data->unknown04_0;
}

bool EnemyParameter::IsBossOrNamed() const {
  const gf::SDataEnemy *data = GetEnemyData();
  return data != nullptr && (data->unknown04_0 | data->unknown04_1);
}

bool EnemyParameter::IsEatTarget() const { return m_eatTarget; }

bool EnemyParameter::IsChild() const { return m_child; }

bool EnemyParameter::IsInvalidHikariSp() const { return m_invalidHikariSp; }

bool EnemyParameter::IsAlwaysKakusei() const { return m_alwaysKakusei; }

bool EnemyParameter::UsePerfectAvoid() const {
  if (unknown86b > 0) {
    unknown86b = unknown86b - 1;
    return true;
  }

  return false;
}

const EnemyParameter::HATE_DATA *EnemyParameter::GetHateDataConst(int index) const { return &unknown820[index >= 0 && index < HATE_COUNT ? index : 0]; }

void EnemyParameter::HATE_DATA::Set(int type, f32 hate) {
  if (!BattleGlobal::get()->unknown65df_4 && static_cast<u32>(type) < 2) {
    unknown00[type] = hate > 0.0f ? hate : 0.0f;
    unknown0c = false;
  }
}

int EnemyParameter::GetHateTarget() const {
  if (!unknown5df_1) {
    return -1;
  }

  return unknown850;
}

void CharacterParameter::ClearAllBuff() {
  if (unknown598 != 0) {
    for (int buff = 1; buff < 23; buff++) {
      if (IsBuff(buff)) {
        ClearBuff(buff, false);
        if (unknown598 == 0) {
          break;
        }
      }
    }
    __builtin_memset(unknown458, 0, sizeof(unknown458));
    unknown598 = 0;
    unknown599[0] = 0;
    unknown599[1] = 0;
    unknown599[2] = 0;
  }
}

void CharacterParameter::ResetEnhance(bool isAll) {
  if (isAll || unknown5e0_2) {
    unknownf0.clear();
    __builtin_memset(unknown5b0, 0, sizeof(unknown5b0));
    __builtin_memset(unknown3f8, 0, sizeof(unknown3f8));
    ResetSpecialEnhanceRate(isAll);
    unknown5e0_2 = false;
  }
}

void CharacterParameter::BattleEndInitialize() {
  ResetEnhance(false);
  unknown5a4 = 0;
}

void EnemyParameter::BattleStart(int arg) {
  CharacterParameter::BattleStart(arg);
  if (IsBoss()) {
    BattleGlobal::get()->unknown65e0_2 = true;
  }
  if (IsNamed()) {
    BattleGlobal::get()->unknown65e0_3 = true;
  }
  gf::GfBdatChrEnArrange *arrange = gf::GfBdatChrEnArrange::get();
  u32 id = unknown24;
  if (arrange->isChrEnArrangeFlagHikari(id)) {
    BattleGlobal::get()->unknown65e1_4 = true;
  }
  if (arrange->isChrEnArrangeFlagPGMax(id)) {
    if (BattleGlobal::get()->unknown65de_0) {
      DataManager::get()->FluctuatePartyGauge(0x2713, -1);
    } else {
      BattleGlobal::get()->unknown65e2_1 = true;
    }
  }
  if (m_invalidWarp) {
    BattleGlobal::get()->unknown65e1_5 = true;
  }
  SetupBGM();
}

} // namespace btl
