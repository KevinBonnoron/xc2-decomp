#include "battle/character/elemental_combo_manager.h"

#include "battle/battle_global.h"
#include "battle/btl_system_balance_access.h"
#include "battle/chain_attack_manager.h"
#include "battle/character/battle_character.h"
#include "battle/character/character_manager_battle.h"
#include "battle/character/character_parameter_battle.h"
#include "battle/data_manager_battle.h"
#include "framework/effect/effect_manager.h"
#include "gf/object/gf_obj_handle.h"
#include "mm_math/mm_math.h"

namespace btl {

constexpr int ELEMENTAL_STAGE_NONE = 3;

ElementalComboManager::~ElementalComboManager() {
  if (BattleGlobal::get()->unknown5af8 == unknown08) {
    BattleGlobal::get()->SetElementalComboImmortal(reinterpret_cast<gf::GF_OBJ_HANDLE *>(-1));
  }
  if (BattleGlobal::get()->unknown5b28 == unknown08 && !BattleGlobal::get()->unknown5b5f) {
    BattleGlobal::get()->DeleteUniteComboDirection();
  }
  DeleteBallEffect(-1);
}

void ElementalComboManager::DeleteBallEffect(int attribute) {
  fw::EffectManager *effectManager = fw::EffectManager::get();
  if (effectManager == nullptr) {
    return;
  }

  int first = 0;
  int last = ATTRIBUTE_COUNT;
  if (attribute >= 0) {
    first = attribute;
    last = attribute;
  }
  for (int i = first; i <= last; i++) {
    if (unknown860[i].unknown34 != 0) {
      effectManager->destroyComboBall(unknown860[i].unknown34);
      unknown860[i].unknown34 = 0;
    }
  }
}

void ElementalComboManager::Initialize(gf::GF_OBJ_HANDLE *handle) {
  unknown10 = -1;
  this->unknown08 = handle;
  unknownaaf_0 = false;
  CheckCharacterID();
}

void ElementalComboManager::CheckCharacterID() {
  if (unknown10 >= 0 || unknown08 == gf::INVALID_HANDLE) {
    return;
  }

  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(unknown08);
  if (character == nullptr) {
    return;
  }

  unknown10 = character->unknownf7d;
  unknownaaf_0 = character->IsPlayer();
  const CharacterParameter *parameter = character->GetCharacterParameterConst(true);
  f32 scale = parameter->unknown30 * 0.1f;
  f32 radiusScale = parameter->unknown3c * (1.0f / 6.0f);
  scale = scale > radiusScale ? scale : radiusScale;
  BtlSystemBalanceAccess *balance = BtlSystemBalanceAccess::get();
  unknown14 = mm::clamp(scale, balance->unknown41 * 0.01f, balance->unknown42 * 0.01f);
  if (unknownaaf_0) {
    unknownaa5 = BtlSystemBalanceAccess::get()->unknown34;
  } else {
    unknownaa5 = 0;
  }
}

void ElementalComboManager::ResetElement(int attribute) {
  int first = 0;
  int last = ATTRIBUTE_COUNT;
  if (attribute >= 0) {
    first = attribute;
    last = attribute;
  }
  for (int i = first; i <= last; i++) {
    ELEMENTAL_DATA &element = unknown1c[i];
    element.unknownb4 = 0;
    element.unknown00 = 0.0f;
    element.unknown04 = 0.0f;
    element.unknown08 = 0.0f;
    element.unknown0c = 0;
    element.unknownb8 = -1;
    element.unknownb9 = 0;
    element.unknownba = ELEMENTAL_STAGE_NONE;
    __builtin_memset(element.unknown14, 0, sizeof(element.unknown14));
    __builtin_memset(element.unknown64, 0, sizeof(element.unknown64));
    element.unknownbb = i;
  }
  unknown18 = 0.0f;
  unknownaa6 = 0;
}

int ElementalComboManager::GetResistantAttrBreakDamage(int attribute) const {
  if (static_cast<u32>(attribute) > ATTRIBUTE_COUNT || !ChainAttackManager::get()->IsProc(true)) {
    return 0;
  }

  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(unknown10);
  if (character == nullptr) {
    return 0;
  }
  const CharacterParameter *parameter = character->GetCharacterParameterConst(true);
  if (parameter == nullptr) {
    return 0;
  }
  int anti = Utility::GetAntiAttribute(attribute);
  if (anti < 0) {
    return 1;
  }
  return parameter->unknown59e & (1 << anti) ? 2 : 1;
}

int ElementalComboManager::GetResistantAttrBreakTotalDamage(int attribute) const {
  if (static_cast<u32>(attribute - 1) < ATTRIBUTE_COUNT) {
    return unknownaa7[attribute - 1];
  }
  return 0;
}

bool ElementalComboManager::IsEnableElementalCombo(int attribute, int stage, bool isIncludeBurst, bool isAnyAttribute) const {
  if (!IsFullElementalValue(attribute)) {
    return false;
  }
  if (unknownaa4_0 == ELEMENTAL_COMBO_COUNT) {
    return false;
  }
  if (unknown18 > 0.0f) {
    return false;
  }
  int combo = GetNextElementalComboID(attribute, isIncludeBurst, isAnyAttribute);
  if (combo == 0) {
    return false;
  }
  if (stage >= 0) {
    int comboStage = isIncludeBurst ? BattleGlobal::get()->GetElementalComboStage(combo) : unknownaa4_0 + 1;
    if (stage < comboStage) {
      return false;
    }
  }
  return true;
}

bool ElementalComboManager::IsFullElementalValue(int attribute) const {
  int first = 0;
  int last = ATTRIBUTE_COUNT;
  if (attribute >= 0) {
    first = attribute;
    last = attribute;
  }
  for (int i = first; i <= last; i++) {
    if (unknown1c[i].unknown04 >= 1.0f) {
      return true;
    }
  }
  return false;
}

bool ElementalComboManager::IsDirecting(int attribute) const {
  int first = 0;
  int last = ATTRIBUTE_COUNT;
  if (attribute >= 0) {
    first = attribute;
    last = attribute;
  }
  for (int i = first; i <= last; i++) {
    if (unknown1c[i].unknown0c >= ELEMENTAL_STATE_DIRECTING) {
      return true;
    }
  }
  return false;
}

bool ElementalComboManager::IsEnableStartElementalCombo() const {
  if (unknownaa6 != 0) {
    return false;
  }
  if (unknownaa4_0 == ELEMENTAL_COMBO_COUNT) {
    return false;
  }
  return !(unknown18 > 0.0f);
}

int ElementalComboManager::GetElementalComboID(bool isIncludeBurst) const {
  if (isIncludeBurst) {
    if (DataManager::get()->permitTarget == unknown08) {
      return DataManager::get()->permitComboId;
    }
    if (unknownaa6 != 0) {
      return unknownaa6;
    }
  }
  if (unknownaa4_0 != 0) {
    return unknown6b8[unknownaa4_0 - 1].unknown76;
  }
  return 0;
}

f32 ElementalComboManager::CalcRestTimeRatio(const ELEMENTAL_COMBO_DATA &combo) const {
  if (combo.unknown10 <= 0.0f || combo.unknown0c <= 0.0f) {
    return 0.0f;
  }
  if (combo.unknown10 >= combo.unknown0c) {
    return 1.0f;
  }
  return combo.unknown10 / combo.unknown0c;
}

void ElementalComboManager::SetElementalValue(int attribute, f32 value) {
  if (static_cast<u32>(attribute) > ATTRIBUTE_COUNT) {
    return;
  }

  ELEMENTAL_DATA &element = unknown1c[attribute];
  int maximum = unknownaa5;
  if (static_cast<int>(value) >= maximum) {
    element.unknown00 = maximum;
    element.unknown04 = 1.0f;
  } else if (static_cast<int>(value) < 1 || maximum == 0) {
    element.unknown00 = 0.0f;
    element.unknown04 = 0.0f;
  } else {
    element.unknown00 = value;
    element.unknown04 = value / maximum;
  }
}

f32 ElementalComboManager::GetElementalValue(int attribute) const {
  if (static_cast<u32>(attribute) <= ATTRIBUTE_COUNT) {
    return unknown1c[attribute].unknown00;
  }
  return 0.0f;
}

f32 ElementalComboManager::GetRestTimeRatio(bool &isSuspend) const {
  isSuspend = false;
  if (unknownaa4_0 == 0) {
    return 0.0f;
  }
  const ELEMENTAL_COMBO_DATA &combo = unknown6b8[unknownaa4_0 - 1];
  if (combo.unknown76 == 0) {
    return 0.0f;
  }
  if (combo.unknown88_0) {
    isSuspend = true;
    return combo.unknown14;
  }
  return CalcRestTimeRatio(combo);
}

} // namespace btl
