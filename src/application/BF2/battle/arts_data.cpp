#include "battle/arts_data.h"

#include "battle/battle_global.h"
#include "battle/character/battle_character.h"
#include "battle/character/character_manager_battle.h"
#include "battle/character/character_parameter_battle.h"
#include "battle/data_manager_battle.h"
#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"

namespace btl {

constexpr int ARTS_LEVEL_INVALID = 7;
constexpr int ENHANCE_HEAL = 363;

f32 ARTS_DATA::GetHitWeightRate(int hit) const {
  f32 rate = 0.0f;
  if (static_cast<u32>(hit) < 16 && totalDamageRate != 0 && hits[hit].damageRate != 0) {
    if (hits[hit].damageRate < totalDamageRate) {
      rate = static_cast<f32>(hits[hit].damageRate) / totalDamageRate;
    } else {
      rate = 1.0f;
    }
    if (loopNum > 1) {
      rate /= static_cast<u32>(loopNum);
    }
    if (bulletNum > 1) {
      rate /= static_cast<u32>(bulletNum);
    }
    if (bulletId != 0) {
      u8 addAttackNum = Bdat::getValCheck(gf::GfDataBdat::getFP(gf::BDAT_BTL_BULLET), "AddAtkNum", bulletId, 1);
      if (addAttackNum) {
        rate *= 1.0f / (addAttackNum + 1);
      }
    }
  }
  return rate;
}

f32 ARTS_SLOT_DATA::AddRecast(f32 recast, bool isRate) {
  f32 added = 0.0f;
  if (isLock || id == 0) {
    return added;
  }

  int index = 0;
  if (level != 0 && level != ARTS_LEVEL_INVALID) {
    index = level - 1;
  }
  if (recastFrames[index] == 0) {
    this->recast = 1.0f;
    added = 0.0f;
  } else {
    f32 frames = recastFrames[index];
    added = isRate ? frames * recast : recast;
    f32 current = frames * this->recast;
    f32 total = added + current;
    if (total >= frames) {
      added = frames - current;
      this->recast = 1.0f;
    } else if (total <= 0.0f) {
      this->recast = 0.0f;
      return -current;
    } else {
      this->recast = total / frames;
      return added;
    }
  }

  if (dataType == ARTS_DATA::DATA_TYPE_DRIVER) {
    BattleCharacter *character = CharacterManager::get()->GetCharacterConst(characterId);
    if (character != nullptr && character->IsControlCharacter()) {
      BattleGlobal::get()->Tutorial(BTL_TUTORIAL_COND_DRIVER_ARTS_RECAST_END, 0, nullptr);
    }
  } else if (dataType == ARTS_DATA::DATA_TYPE_BLADE) {
    BattleCharacter *character = CharacterManager::get()->GetCharacterConst(characterId);
    if (character != nullptr && character->IsControlCharacterGroup()) {
      BattleGlobal::get()->Tutorial(BTL_TUTORIAL_COND_BLADE_ARTS_RECAST_END, 0, nullptr);
      if (slot == 2) {
        BattleGlobal::get()->Tutorial(BTL_TUTORIAL_COND_SP_ATTACK_LEVEL3_RECAST_END, 0, nullptr);
      }
    }
  }
  return added;
}

void ARTS_SLOT_DATA::ResetRecast(bool isStart, bool) {
  if (id == 0) {
    return;
  }

  recast = 0.0f;
  if (!isLock && isStart) {
    ARTS_DATA data;
    DataManager::get()->GetArtsData(static_cast<ARTS_DATA::DATA_TYPE>(dataType), id, data);
    if (data.startRecast != 0) {
      recast = static_cast<u32>(data.startRecast) * 0.01f;
    }
  }
}

void ARTS_SLOT_DATA::GetArtsData(ARTS_DATA &data) const { DataManager::get()->GetArtsData(static_cast<ARTS_DATA::DATA_TYPE>(dataType), id, data); }

void ARTS_PALETTE_DATA::AddAllRecast(f32 recast, bool isRate) {
  AddArtsRecast(recast, isRate, -1);
  arts[16].AddRecast(recast, isRate);
  arts[17].AddRecast(recast, isRate);
  arts[18].AddRecast(recast, isRate);
  AddSupportRecast(recast, isRate);
}

bool ARTS_PALETTE_DATA::AddArtsRecast(f32 recast, bool isRate, int exceptSlot) {
  bool isRecastEnd = false;
  if (isBlade == 1) {
    for (int i = 0; i < 16; i++) {
      ARTS_SLOT_DATA &slot = arts[i];
      if (slot.id == 0) {
        break;
      }
      if (recast >= 0.0f && slot.recast >= 1.0f) {
        continue;
      }
      f32 added = slot.AddRecast(recast, isRate);
      if (slot.recast >= 1.0f) {
        isRecastEnd = true;
      }
      if (recast == added || added == 0.0f) {
        return isRecastEnd;
      }
      recast -= added;
    }
  } else {
    for (int i = 0; i < 16; i++) {
      ARTS_SLOT_DATA &slot = arts[i];
      if (exceptSlot == i || slot.id == 0 || (recast >= 0.0f && slot.recast >= 1.0f)) {
        continue;
      }
      slot.AddRecast(recast, isRate);
      isRecastEnd |= slot.recast >= 1.0f;
    }
  }
  return isRecastEnd;
}

void ARTS_PALETTE_DATA::AddSupportRecast(f32 recast, bool isRate) {
  supports[0].AddRecast(recast, isRate);
  supports[1].AddRecast(recast, isRate);
  supports[2].AddRecast(recast, isRate);
}

void ARTS_PALETTE_DATA::ResetAllRecast() {
  for (int i = 0; i < 19; i++) {
    arts[i].ResetRecast(false, false);
  }
  spAttackLevel4.ResetRecast(false, false);
  ResetSupportRecast();
}

void ARTS_PALETTE_DATA::ResetArtsRecast(bool isStart) {
  for (int i = 0; i < 19; i++) {
    arts[i].ResetRecast(isStart, false);
  }
}

void ARTS_PALETTE_DATA::ResetSupportRecast() {
  for (ARTS_SLOT_DATA &slot : supports) {
    slot.ResetRecast(false, false);
  }
}

const ARTS_SLOT_DATA *ARTS_PALETTE_DATA::GetSlotDataConst(int slot, bool isTalent) const {
  if (slot == SP_ATTACK_LEVEL_4_SLOT) {
    return &spAttackLevel4;
  }
  return &arts[isTalent ? slot + 16 : slot];
}

const ARTS_SLOT_DATA *ARTS_PALETTE_DATA::GetSupportSlotDataConst(int slot) const { return &supports[slot]; }

bool ARTS_PALETTE_DATA::IsEnableHealArts(bool isRecastEnd) const {
  for (int i = 0; i < 19; i++) {
    const ARTS_SLOT_DATA &slot = arts[i];
    if (slot.id == 0 || (isRecastEnd && slot.recast < 1.0f)) {
      continue;
    }
    ARTS_DATA data;
    DataManager::get()->GetArtsData(static_cast<ARTS_DATA::DATA_TYPE>(slot.dataType), slot.id, data);
    if (data.artsType == ARTS_DATA::ARTS_TYPE_HEAL) {
      return true;
    }
    ENHANCE_EFFECT_DATA enhance;
    if (data.levels[slot.level - 1].enhance != 0 && DataManager::GetEnhanceData(data.levels[slot.level - 1].enhance, enhance, false) &&
        enhance.id == ENHANCE_HEAL) {
      return true;
    }
  }
  return false;
}

} // namespace btl
