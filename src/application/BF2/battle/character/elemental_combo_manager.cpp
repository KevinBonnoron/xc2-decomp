#include "battle/character/elemental_combo_manager.h"

#include "battle/battle_global.h"
#include "battle/chain_attack_manager.h"
#include "battle/character/battle_character.h"
#include "battle/character/character_manager_battle.h"
#include "battle/character/character_parameter_battle.h"
#include "battle/data_manager_battle.h"
#include "framework/effect/effect_manager.h"

namespace btl {

ElementalComboManager::~ElementalComboManager() {
  if (BattleGlobal::get()->elementalComboImmortal == handle) {
    BattleGlobal::get()->SetElementalComboImmortal(reinterpret_cast<gf::GF_OBJ_HANDLE *>(-1));
  }
  if (BattleGlobal::get()->uniteComboTarget == handle && !BattleGlobal::get()->isUniteComboDirection) {
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
    if (balls[i].effectHandle != 0) {
      effectManager->destroyComboBall(balls[i].effectHandle);
      balls[i].effectHandle = 0;
    }
  }
}

void ElementalComboManager::Initialize(gf::GF_OBJ_HANDLE *handle) {
  characterId = -1;
  this->handle = handle;
  isPlayer = false;
  CheckCharacterID();
}

int ElementalComboManager::GetResistantAttrBreakDamage(int attribute) const {
  if (static_cast<u32>(attribute) > ATTRIBUTE_COUNT || !ChainAttackManager::get()->IsProc(true)) {
    return 0;
  }

  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(characterId);
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
  return parameter->resistantAttributeFlags & (1 << anti) ? 2 : 1;
}

int ElementalComboManager::GetResistantAttrBreakTotalDamage(int attribute) const {
  if (static_cast<u32>(attribute - 1) < ATTRIBUTE_COUNT) {
    return resistantAttrBreakTotalDamages[attribute - 1];
  }
  return 0;
}

bool ElementalComboManager::IsFullElementalValue(int attribute) const {
  int first = 0;
  int last = ATTRIBUTE_COUNT;
  if (attribute >= 0) {
    first = attribute;
    last = attribute;
  }
  for (int i = first; i <= last; i++) {
    if (elements[i].ratio >= 1.0f) {
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
    if (elements[i].state >= ELEMENTAL_STATE_DIRECTING) {
      return true;
    }
  }
  return false;
}

bool ElementalComboManager::IsEnableStartElementalCombo() const {
  if (burstComboId != 0) {
    return false;
  }
  if (comboIndex == ELEMENTAL_COMBO_COUNT) {
    return false;
  }
  return !(startWaitTime > 0.0f);
}

int ElementalComboManager::GetElementalComboID(bool isIncludeBurst) const {
  if (isIncludeBurst) {
    if (DataManager::get()->permitTarget == handle) {
      return DataManager::get()->permitComboId;
    }
    if (burstComboId != 0) {
      return burstComboId;
    }
  }
  if (comboIndex != 0) {
    return combos[comboIndex - 1].comboId;
  }
  return 0;
}

f32 ElementalComboManager::CalcRestTimeRatio(const ELEMENTAL_COMBO_DATA &combo) const {
  if (combo.restTime <= 0.0f || combo.restTimeMax <= 0.0f) {
    return 0.0f;
  }
  if (combo.restTime >= combo.restTimeMax) {
    return 1.0f;
  }
  return combo.restTime / combo.restTimeMax;
}

void ElementalComboManager::SetElementalValue(int attribute, f32 value) {
  if (static_cast<u32>(attribute) > ATTRIBUTE_COUNT) {
    return;
  }

  ELEMENTAL_DATA &element = elements[attribute];
  int maximum = elementalValueMax;
  if (static_cast<int>(value) >= maximum) {
    element.value = maximum;
    element.ratio = 1.0f;
  } else if (static_cast<int>(value) < 1 || maximum == 0) {
    element.value = 0.0f;
    element.ratio = 0.0f;
  } else {
    element.value = value;
    element.ratio = value / maximum;
  }
}

f32 ElementalComboManager::GetElementalValue(int attribute) const {
  if (static_cast<u32>(attribute) <= ATTRIBUTE_COUNT) {
    return elements[attribute].value;
  }
  return 0.0f;
}

f32 ElementalComboManager::GetRestTimeRatio(bool &isSuspend) const {
  isSuspend = false;
  if (comboIndex == 0) {
    return 0.0f;
  }
  const ELEMENTAL_COMBO_DATA &combo = combos[comboIndex - 1];
  if (combo.comboId == 0) {
    return 0.0f;
  }
  if (combo.isSuspend) {
    isSuspend = true;
    return combo.suspendRatio;
  }
  return CalcRestTimeRatio(combo);
}

} // namespace btl
