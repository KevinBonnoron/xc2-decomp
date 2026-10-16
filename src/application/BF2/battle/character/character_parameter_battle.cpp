#include "battle/character/character_parameter_battle.h"

#include "battle/battle_global.h"
#include "battle/chain_attack_manager.h"
#include "battle/character/battle_character.h"
#include "battle/character/character_manager_battle.h"
#include "battle/data_manager_battle.h"
#include "battle/group_data.h"
#include "battle/utility_battle.h"
#include "gf/data/gf_bdat_chrenarrange.h"
#include "gf/data/gf_data_enemy.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/game/gf_game_util.h"
#include "gf/object/component/property/gf_com_property.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"

namespace btl {

constexpr f32 DEGREE_TO_RADIAN = 3.14159265f / 180.0f;

gf::GfObj *CharacterParameter::GetUserObject() const { return gf::GfObjUtil::getObj(user); }

gf::GfObj *CharacterParameter::GetBuddyObject() const { return gf::GfObjUtil::getObj(buddy); }

bool CharacterParameter::InitializeEnhance() const {
  isInitializedEnhance = true;
  return true;
}

void CharacterParameter::BattleEnd() {
  ResetRecast();
  isBattle = false;
}

void CharacterParameter::ResetSpecialEnhanceRate(bool isAll) {
  int last = SPECIAL_ENHANCE_COUNT - 1;
  if (!isAll) {
    last = BattleGlobal::get()->isLockArtsPalette ? SPECIAL_ENHANCE_COUNT - 3 : SPECIAL_ENHANCE_COUNT - 1;
  }
  for (int i = 0; i <= last; i++) {
    SetSpecialEnhanceRate(static_cast<SPECIAL_ENHANCE_TYPE>(i), 0.0f);
  }
}

int CharacterParameter::GetClass() const {
  if (classId < 0) {
    gf::DataParamAcc acc(isBlade ? buddy : user);
    return acc.getClass(false);
  }

  return classId;
}

f32 CharacterParameter::GetHPRate() const {
  int hp = gf::GfGameUtil::getNowHp(user, objectType, gameObjectId);
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
  gf::GfObj *obj = gf::GfObjUtil::getObj(user);
  if (obj != nullptr) {
    gf::GfComProperty *property = obj->getComponent<gf::GfComProperty>();
    if (property != nullptr) {
      return property->status;
    }
  }

  return nullptr;
}

void CharacterParameter::SetHP(u32 hp) {
  gf::GfStatusProperty *status = GetStatusProperty();
  if (status != nullptr) {
    status->hp = hp;
  }
}

u32 CharacterParameter::GetHP() const { return gf::GfGameUtil::getNowHp(user, objectType, gameObjectId); }

u32 CharacterParameter::GetMaxHP() const {
  u32 maxHp = gf::GfGameUtil::getMaxHp(user, objectType, gameObjectId);
  ENHANCE_DATA data;
  if (GetAdditionalEnhanceEffect(data, ADD_ENHANCE_TYPE_HP, nullptr)) {
    maxHp += static_cast<int>(data.value);
  }

  return maxHp;
}

bool CharacterParameter::IsBuff(int buff) const {
  if (isBlade) {
    if (isIgnoreBuddy) {
      return false;
    }

    gf::GF_OBJ_HANDLE *handle = buddy;
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

  return (buffFlags[buff >> 3] & (1 << (buff & 7))) != 0;
}

u32 CharacterParameter::GetWeakAttributeFlag() const {
  int attribute = Utility::GetAntiAttribute(GetAttribute());
  return attribute >= 0 ? 1 << attribute : 0;
}

const FIGHT_COMBO_DATA *CharacterParameter::GetFightComboDataConst() const {
  if (isOverwriteFightCombo && overwriteFightCombo.id != 0) {
    return &overwriteFightCombo;
  }
  return &fightCombo;
}

u32 CharacterParameter::GetLevel() const {
  gf::DataParamAcc acc(isBlade ? buddy : user);
  return acc.getLevel(false);
}

f32 CharacterParameter::GetBuffEffect(int buff) const {
  for (int i = 0; i < buffNum; i++) {
    if (buffs[i].id == buff) {
      return buffs[i].effect;
    }
  }

  return 0.0f;
}

bool CharacterParameter::IsBuffInfinite(int buff) const {
  for (int i = 0; i < buffNum; i++) {
    if (buffs[i].id == buff) {
      return buffs[i].restFrame < 0.0f;
    }
  }

  return false;
}

const BUFF_DATA *CharacterParameter::GetBuffDataConst(int buff, int *index) const {
  for (int i = 0; i < buffNum; i++) {
    if (buffs[i].id == buff) {
      if (index != nullptr) {
        *index = i;
      }

      return &buffs[i];
    }
  }

  return nullptr;
}

f32 CharacterParameter::GetBuffRestFrame(int buff) const {
  for (int i = 0; i < buffNum; i++) {
    if (buffs[i].id == buff) {
      return buffs[i].restFrame;
    }
  }

  return 0.0f;
}

f32 CharacterParameter::GetBlowRotSpeed() const { return rotateDeg * DEGREE_TO_RADIAN; }

bool CharacterParameter::IsBlowRot() const {
  if (rotateDeg == 0) {
    return false;
  }

  if (rotateX == 0 && rotateY == 0 && rotateZ == 0) {
    return false;
  }

  return true;
}

bool CharacterParameter::IsProgressCoolTime() const {
  if (!isBattle) {
    return false;
  }
  if (ChainAttackManager::get()->IsProc(true)) {
    return false;
  }
  return isEnableCoolTime;
}

const ENHANCE_EFFECT_DATA *CharacterParameter::GetEnhanceEffectDataConst(int enhance) const {
  for (const ENHANCE_EFFECT_DATA &effect : enhanceEffects) {
    if (effect.id == enhance) {
      return &effect;
    }
  }

  return nullptr;
}

void CharacterParameter::SetSpecialEnhanceRate(SPECIAL_ENHANCE_TYPE type, f32 rate, u16 value) {
  if (!isBlade && buddy != gf::INVALID_HANDLE) {
    BattleCharacter *character = CharacterManager::get()->GetCharacterConst(buddy);
    if (character != nullptr) {
      CharacterParameter *parameter = character->GetCharacterParameter(true);
      if (parameter != nullptr) {
        parameter->SetSpecialEnhanceRate(type, rate);
      }
    }
    return;
  }
  if (static_cast<u32>(type) < SPECIAL_ENHANCE_COUNT) {
    specialEnhanceRates[type] = rate;
    specialEnhanceValues[value] = value;
  }
}

void CharacterParameter::AddSpecialEnhanceRate(SPECIAL_ENHANCE_TYPE type, f32 rate, u16 value) {
  if (!isBlade && buddy != gf::INVALID_HANDLE) {
    BattleCharacter *character = CharacterManager::get()->GetCharacterConst(buddy);
    if (character != nullptr) {
      CharacterParameter *parameter = character->GetCharacterParameter(true);
      if (parameter != nullptr) {
        parameter->AddSpecialEnhanceRate(type, rate, value);
      }
    }
    return;
  }
  if (static_cast<u32>(type) < SPECIAL_ENHANCE_COUNT && rate != 0.0f) {
    specialEnhanceRates[type] += rate;
    specialEnhanceValues[value] = value;
  }
}

void CharacterParameter::MinSpecialEnhanceRate(SPECIAL_ENHANCE_TYPE type, f32 rate, u16 value) {
  if (!isBlade && buddy != gf::INVALID_HANDLE) {
    BattleCharacter *character = CharacterManager::get()->GetCharacterConst(buddy);
    if (character != nullptr) {
      CharacterParameter *parameter = character->GetCharacterParameter(true);
      if (parameter != nullptr) {
        parameter->MinSpecialEnhanceRate(type, rate, value);
      }
    }
    return;
  }
  if (static_cast<u32>(type) < SPECIAL_ENHANCE_COUNT && rate != 0.0f) {
    f32 current = specialEnhanceRates[type];
    specialEnhanceRates[type] = current == 0.0f ? rate : (current < rate ? current : rate);
    specialEnhanceValues[value] = value;
  }
}

void CharacterParameter::MaxSpecialEnhanceRate(SPECIAL_ENHANCE_TYPE type, f32 rate, u16 value) {
  if (!isBlade && buddy != gf::INVALID_HANDLE) {
    BattleCharacter *character = CharacterManager::get()->GetCharacterConst(buddy);
    if (character != nullptr) {
      CharacterParameter *parameter = character->GetCharacterParameter(true);
      if (parameter != nullptr) {
        parameter->MaxSpecialEnhanceRate(type, rate, value);
      }
    }
    return;
  }
  if (static_cast<u32>(type) < SPECIAL_ENHANCE_COUNT && rate != 0.0f) {
    f32 current = specialEnhanceRates[type];
    specialEnhanceRates[type] = current == 0.0f ? rate : (current > rate ? current : rate);
    specialEnhanceValues[value] = value;
  }
}

f32 CharacterParameter::GetSpecialEnhanceRate(SPECIAL_ENHANCE_TYPE type, int *value) const {
  if (!isBlade && buddy != gf::INVALID_HANDLE) {
    BattleCharacter *character = CharacterManager::get()->GetCharacterConst(buddy);
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
      *value = specialEnhanceValues[type];
    }
    return specialEnhanceRates[type];
  }
  return 0.0f;
}

int CharacterParameter::GetGender() const {
  gf::DataParamAcc acc(user);
  return acc.getGender();
}

int CharacterParameter::GetAttribute() const {
  gf::DataParamAcc acc(user);
  return acc.getAttribute(-1, false);
}

int CharacterParameter::GetBaseSTR() const {
  gf::DataParamAcc acc(isBlade ? buddy : user);
  return acc.getStrength(false);
}

int CharacterParameter::GetBaseDEX() const {
  gf::DataParamAcc acc(isBlade ? buddy : user);
  return acc.getDex(false);
}

int CharacterParameter::GetBaseAGI() const {
  gf::DataParamAcc acc(isBlade ? buddy : user);
  return acc.getAgility(false);
}

int CharacterParameter::GetBaseLUK() const {
  gf::DataParamAcc acc(isBlade ? buddy : user);
  return acc.getLuck(false);
}

int CharacterParameter::GetBaseEtherPower() const {
  gf::DataParamAcc acc(isBlade ? buddy : user);
  return acc.getPowerEther(false);
}

int CharacterParameter::GetBasePArmor() const {
  gf::DataParamAcc acc(isBlade ? buddy : user);
  return acc.getPArmor(false);
}

int CharacterParameter::GetBaseEArmor() const {
  gf::DataParamAcc acc(isBlade ? buddy : user);
  return acc.getEArmor(false);
}

int CharacterParameter::GetBaseCriticalPercent() const {
  gf::DataParamAcc acc(isBlade ? buddy : user);
  return acc.getCriticalRate(false);
}

int CharacterParameter::GetBaseGuardPercent() const {
  gf::DataParamAcc acc(isBlade ? buddy : user);
  return acc.getGuardRate(false);
}

int CharacterParameter::GetBaseResistPowerAttack() const {
  gf::DataParamAcc acc(isBlade ? buddy : user);
  return static_cast<s8>(acc.getResistancePower());
}

int CharacterParameter::GetBaseResistEtherAttack() const {
  gf::DataParamAcc acc(isBlade ? buddy : user);
  return static_cast<s8>(acc.getResistanceEther());
}

void CharacterParameter::GetBaseDamage(u32 &minimum, u32 &maximum) const {
  gf::DataParamAcc acc(isBlade ? buddy : user);
  minimum = acc.getNorAtkDmgMin(false);
  maximum = acc.getNorAtkDmgMax(false);
}

int CharacterParameter::GetSTR() const {
  int value = GetBaseSTR();
  ENHANCE_DATA data;
  if (GetAdditionalEnhanceEffect(data, ADD_ENHANCE_TYPE_STRENGTH_RATE, nullptr)) {
    value += static_cast<int>(value * data.value);
  }

  if (GetAdditionalEnhanceEffect(data, ADD_ENHANCE_TYPE_STRENGTH, nullptr)) {
    value += static_cast<int>(data.value);
  }

  return value;
}

int CharacterParameter::GetDEX() const {
  int value = GetBaseDEX();
  ENHANCE_DATA data;
  if (GetAdditionalEnhanceEffect(data, ADD_ENHANCE_TYPE_DEX_RATE, nullptr)) {
    value += static_cast<int>(value * data.value);
  }

  if (GetAdditionalEnhanceEffect(data, ADD_ENHANCE_TYPE_DEX, nullptr)) {
    value += static_cast<int>(data.value);
  }

  return value;
}

int CharacterParameter::GetAGI() const {
  int value = GetBaseAGI();
  ENHANCE_DATA data;
  if (GetAdditionalEnhanceEffect(data, ADD_ENHANCE_TYPE_AGILITY_RATE, nullptr)) {
    value += static_cast<int>(value * data.value);
  }

  if (GetAdditionalEnhanceEffect(data, ADD_ENHANCE_TYPE_AGILITY, nullptr)) {
    value += static_cast<int>(data.value);
  }

  return value;
}

int CharacterParameter::GetLUK() const {
  int value = GetBaseLUK();
  ENHANCE_DATA data;
  if (GetAdditionalEnhanceEffect(data, ADD_ENHANCE_TYPE_LUCK_RATE, nullptr)) {
    value += static_cast<int>(value * data.value);
  }

  if (GetAdditionalEnhanceEffect(data, ADD_ENHANCE_TYPE_LUCK, nullptr)) {
    value += static_cast<int>(data.value);
  }

  return value;
}

int CharacterParameter::GetEtherPower() const {
  int value = GetBaseEtherPower();
  ENHANCE_DATA data;
  if (GetAdditionalEnhanceEffect(data, ADD_ENHANCE_TYPE_ETHER_POWER_RATE, nullptr)) {
    value += static_cast<int>(value * data.value);
  }

  if (GetAdditionalEnhanceEffect(data, ADD_ENHANCE_TYPE_ETHER_POWER, nullptr)) {
    value += static_cast<int>(data.value);
  }

  return value;
}

int CharacterParameter::GetPArmor() const {
  int value = GetBasePArmor();
  ENHANCE_DATA data;
  if (GetAdditionalEnhanceEffect(data, ADD_ENHANCE_TYPE_PHYSICAL_ARMOR_RATE, nullptr)) {
    value += static_cast<int>(value * data.value);
  }

  if (GetAdditionalEnhanceEffect(data, ADD_ENHANCE_TYPE_PHYSICAL_ARMOR, nullptr)) {
    value += static_cast<int>(data.value);
  }

  return value;
}

int CharacterParameter::GetEArmor() const {
  int value = GetBaseEArmor();
  ENHANCE_DATA data;
  if (GetAdditionalEnhanceEffect(data, ADD_ENHANCE_TYPE_ETHER_ARMOR_RATE, nullptr)) {
    value += static_cast<int>(value * data.value);
  }

  if (GetAdditionalEnhanceEffect(data, ADD_ENHANCE_TYPE_ETHER_ARMOR, nullptr)) {
    value += static_cast<int>(data.value);
  }

  return value;
}

int CharacterParameter::GetCriticalPercent() const {
  int value = GetBaseCriticalPercent();
  ENHANCE_DATA data;
  if (GetAdditionalEnhanceEffect(data, ADD_ENHANCE_TYPE_CRITICAL_RATE, nullptr)) {
    value += static_cast<int>(value * data.value);
  }

  if (GetAdditionalEnhanceEffect(data, ADD_ENHANCE_TYPE_CRITICAL, nullptr)) {
    value += static_cast<int>(data.value);
  }

  return value;
}

int CharacterParameter::GetGuardPercent() const {
  int value = GetBaseGuardPercent();
  ENHANCE_DATA data;
  if (GetAdditionalEnhanceEffect(data, ADD_ENHANCE_TYPE_GUARD_RATE, nullptr)) {
    value += static_cast<int>(value * data.value);
  }

  if (GetAdditionalEnhanceEffect(data, ADD_ENHANCE_TYPE_GUARD, nullptr)) {
    value += static_cast<int>(data.value);
  }

  return value;
}

int CharacterParameter::GetResistPowerAttack() const {
  int value = GetBaseResistPowerAttack();
  ENHANCE_DATA data;
  if (GetAdditionalEnhanceEffect(data, ADD_ENHANCE_TYPE_PHYSICAL_ARMOR_RATE, nullptr)) {
    value += static_cast<int>(value * data.value);
  }

  if (GetAdditionalEnhanceEffect(data, ADD_ENHANCE_TYPE_PHYSICAL_ARMOR, nullptr)) {
    value += static_cast<int>(data.value);
  }

  return value;
}

int CharacterParameter::GetResistEtherAttack() const {
  int value = GetBaseResistEtherAttack();
  ENHANCE_DATA data;
  if (GetAdditionalEnhanceEffect(data, ADD_ENHANCE_TYPE_ETHER_ARMOR_RATE, nullptr)) {
    value += static_cast<int>(value * data.value);
  }

  if (GetAdditionalEnhanceEffect(data, ADD_ENHANCE_TYPE_ETHER_ARMOR, nullptr)) {
    value += static_cast<int>(data.value);
  }

  return value;
}

PlayerParameter::PlayerParameter() : artsPalettes(nullptr), artsPaletteNum(0), bladeChangeType(0) {}

PlayerParameter::~PlayerParameter() {
  if (artsPalettes != nullptr) {
    delete[] artsPalettes;
    artsPalettes = nullptr;
  }
}

void PlayerParameter::ResetUseWeapon() {
  for (int i = 0; i < gf::WEAPON_TYPE_COUNT + 1; i++) {
    useWeaponCounts[i] = 0;
  }

  useWeaponTotal = 0;
}

void PlayerParameter::BattleEnd() {
  CharacterParameter::BattleEnd();
  ResetUseWeapon();
}

void PlayerParameter::BattleEndInitialize() {
  CharacterParameter::BattleEndInitialize();
  pouchDamageArmor = -1;
}

void PlayerParameter::WritebackRecast(GROUP_DATA *groupData) {
  if (isBattle && isBlade) {
    const ARTS_PALETTE_DATA *palette = GetArtsPaletteDataConst(-1);
    for (int i = 0; i < 3; i++) {
      const ARTS_SLOT_DATA *slot = palette->GetSlotDataConst(i, false);
      bool isValid = slot->id != 0;
      f32 recast = slot->recast;
      groupData->recasts[i] = isValid ? recast : 0.0f;
    }
  }
}

void PlayerParameter::AddUseWeapon(int weapon) {
  useWeaponCounts[weapon]++;
  useWeaponTotal++;
}

f32 PlayerParameter::GetUseWeaponRate(int weapon) const {
  if (useWeaponTotal == 0) {
    return weapon == attackWeaponType ? 1.0f : 0.0f;
  }

  u32 count = useWeaponCounts[weapon];
  if (count >= useWeaponTotal) {
    return 1.0f;
  }
  return static_cast<f32>(count) / useWeaponTotal;
}

const ARTS_PALETTE_DATA *PlayerParameter::GetArtsPaletteDataConst(int index) const {
  if (index < 0) {
    index = isBlade ? 0 : GetBladeIndex();
  }

  return &artsPalettes[index];
}

void PlayerParameter::ResetRecast() {
  if (artsPalettes == nullptr) {
    return;
  }

  u8 num = artsPaletteNum;
  for (int i = 0; i < num; i++) {
    const_cast<ARTS_PALETTE_DATA *>(GetArtsPaletteDataConst(i))->ResetAllRecast();
  }
}

int PlayerParameter::GetBladeIndex() const {
  gf::DataParamAcc acc(isBlade ? buddy : user);
  return acc.getBladeSet(false);
}

int PlayerParameter::GetWeaponID(int slot) const {
  gf::DataParamAcc acc(isBlade ? buddy : user);
  return acc.getEquipWeapon(slot, false);
}

int PlayerParameter::GetEquipAccessory() const {
  gf::DataParamAcc acc(isBlade ? buddy : user);
  return acc.getEquipAcce(0, false);
}

int PlayerParameter::GetIdeaLevel(int idea) const {
  gf::DataParamAcc acc(isBlade ? buddy : user);
  gf::DataIdeaAcc ideaAcc(acc);
  return ideaAcc.getLevel(idea);
}

EnemyParameter::~EnemyParameter() { DataManager::get()->ReleaseEnemyGroup(user); }

const gf::SDataEnemy *EnemyParameter::GetEnemyData() const {
  gf::DataParamAcc acc(user);
  return acc.getSDataEnemy();
}

void CharacterParameter::SetBuddy(gf::GF_OBJ_HANDLE *handle, bool isIgnoreBuddy) {
  buddy = handle;
  this->isIgnoreBuddy = isIgnoreBuddy;
}

void EnemyParameter::BattleEnd() {
  CharacterParameter::BattleEnd();
  DataManager::get()->ReleaseEnemyGroup(user);
}

void EnemyParameter::BattleEndInitialize() { CharacterParameter::BattleEndInitialize(); }

int EnemyParameter::GetBGMID() const {
  const gf::SDataEnemy *data = GetEnemyData();
  if (data == nullptr) {
    return 0;
  }

  return gf::GfBdatChrEnArrange::get()->getChrEnArrangeBGMID(data->arrange);
}

void EnemyParameter::SetupBGM() {
  int bgm = GetBGMID();
  BattleGlobal::get()->SetBGM(bgm);
}

int EnemyParameter::GetAttribute() const {
  if (overwriteAttr <= ATTRIBUTE_COUNT) {
    return overwriteAttr;
  }

  if (IsAngry() && angryAttr <= ATTRIBUTE_COUNT) {
    return angryAttr;
  }

  gf::DataParamAcc acc(user);
  return acc.getAttribute(-1, false);
}

int EnemyParameter::GetWeaponID(int) const {
  gf::DataParamAcc acc(isBlade ? buddy : user);
  return acc.getEquipWeapon(0, false);
}

bool EnemyParameter::IsBoss() const {
  const gf::SDataEnemy *data = GetEnemyData();
  return data != nullptr && data->boss;
}

bool EnemyParameter::IsNamed() const {
  const gf::SDataEnemy *data = GetEnemyData();
  return data != nullptr && data->named;
}

bool EnemyParameter::IsBossOrNamed() const {
  const gf::SDataEnemy *data = GetEnemyData();
  return data != nullptr && (data->named | data->boss);
}

bool EnemyParameter::IsEatTarget() const { return isEatTarget; }

bool EnemyParameter::IsChild() const { return isChild; }

bool EnemyParameter::IsInvalidHikariSp() const { return isInvalidHikariSp; }

bool EnemyParameter::IsAlwaysKakusei() const { return isAlwaysKakusei; }

bool EnemyParameter::UsePerfectAvoid() const {
  if (perfectAvoidNum > 0) {
    perfectAvoidNum = perfectAvoidNum - 1;
    return true;
  }

  return false;
}

const EnemyParameter::HATE_DATA *EnemyParameter::GetHateDataConst(int index) const { return &hates[index >= 0 && index < 3 ? index : 0]; }

int EnemyParameter::GetHateTarget() const {
  if (!isBattle) {
    return -1;
  }

  return hateTarget;
}

} // namespace btl
