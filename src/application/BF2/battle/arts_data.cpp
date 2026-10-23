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
  if (static_cast<u32>(hit) < 16 && unknown05_3 != 0 && unknown30[hit].unknown01 != 0) {
    if (unknown30[hit].unknown01 < unknown05_3) {
      rate = static_cast<f32>(unknown30[hit].unknown01) / unknown05_3;
    } else {
      rate = 1.0f;
    }
    if (unknown0b_4 > 1) {
      rate /= static_cast<u32>(unknown0b_4);
    }
    if (unknown12_7 > 1) {
      rate /= static_cast<u32>(unknown12_7);
    }
    if (unknown10_0 != 0) {
      u8 addAttackNum = Bdat::getValCheck(gf::GfDataBdat::getFP(gf::BDAT_BTL_BULLET), "AddAtkNum", unknown10_0, 1);
      if (addAttackNum) {
        rate *= 1.0f / (addAttackNum + 1);
      }
    }
  }
  return rate;
}

f32 ARTS_SLOT_DATA::AddRecast(f32 recast, bool isRate) {
  f32 added = 0.0f;
  if (unknown03_7 || unknown00_0 == 0) {
    return added;
  }

  int index = 0;
  if (unknown02_5 != 0 && unknown02_5 != ARTS_LEVEL_INVALID) {
    index = unknown02_5 - 1;
  }
  if (unknown0c[index] == 0) {
    this->unknown04 = 1.0f;
    added = 0.0f;
  } else {
    f32 frames = unknown0c[index];
    added = isRate ? frames * recast : recast;
    f32 current = frames * this->unknown04;
    f32 total = added + current;
    if (total >= frames) {
      added = frames - current;
      this->unknown04 = 1.0f;
    } else if (total <= 0.0f) {
      this->unknown04 = 0.0f;
      return -current;
    } else {
      this->unknown04 = total / frames;
      return added;
    }
  }

  if (unknown01_3 == ARTS_DATA::DATA_TYPE_DRIVER) {
    BattleCharacter *character = CharacterManager::get()->GetCharacterConst(unknown03_0);
    if (character != nullptr && character->IsControlCharacter()) {
      BattleGlobal::get()->Tutorial(BTL_TUTORIAL_COND_DRIVER_ARTS_RECAST_END, 0, nullptr);
    }
  } else if (unknown01_3 == ARTS_DATA::DATA_TYPE_BLADE) {
    BattleCharacter *character = CharacterManager::get()->GetCharacterConst(unknown03_0);
    if (character != nullptr && character->IsControlCharacterGroup()) {
      BattleGlobal::get()->Tutorial(BTL_TUTORIAL_COND_BLADE_ARTS_RECAST_END, 0, nullptr);
      if (unknown01_6 == 2) {
        BattleGlobal::get()->Tutorial(BTL_TUTORIAL_COND_SP_ATTACK_LEVEL3_RECAST_END, 0, nullptr);
      }
    }
  }
  return added;
}

void ARTS_SLOT_DATA::ResetRecast(bool isStart, bool) {
  if (unknown00_0 == 0) {
    return;
  }

  unknown04 = 0.0f;
  if (!unknown03_7 && isStart) {
    ARTS_DATA data;
    DataManager::get()->GetArtsData(static_cast<ARTS_DATA::DATA_TYPE>(unknown01_3), unknown00_0, data);
    if (data.unknown07_1 != 0) {
      unknown04 = static_cast<u32>(data.unknown07_1) * 0.01f;
    }
  }
}

void ARTS_SLOT_DATA::GetArtsData(ARTS_DATA &data) const {
  DataManager::get()->GetArtsData(static_cast<ARTS_DATA::DATA_TYPE>(unknown01_3), unknown00_0, data);
}

void ARTS_PALETTE_DATA::AddAllRecast(f32 recast, bool isRate) {
  AddArtsRecast(recast, isRate, -1);
  unknown08[16].AddRecast(recast, isRate);
  unknown08[17].AddRecast(recast, isRate);
  unknown08[18].AddRecast(recast, isRate);
  AddSupportRecast(recast, isRate);
}

bool ARTS_PALETTE_DATA::AddArtsRecast(f32 recast, bool isRate, int exceptSlot) {
  bool isRecastEnd = false;
  if (unknown230_0 == 1) {
    for (int i = 0; i < 16; i++) {
      ARTS_SLOT_DATA &slot = unknown08[i];
      if (slot.unknown00_0 == 0) {
        break;
      }
      if (recast >= 0.0f && slot.unknown04 >= 1.0f) {
        continue;
      }
      f32 added = slot.AddRecast(recast, isRate);
      if (slot.unknown04 >= 1.0f) {
        isRecastEnd = true;
      }
      if (recast == added || added == 0.0f) {
        return isRecastEnd;
      }
      recast -= added;
    }
  } else {
    for (int i = 0; i < 16; i++) {
      ARTS_SLOT_DATA &slot = unknown08[i];
      if (exceptSlot == i || slot.unknown00_0 == 0 || (recast >= 0.0f && slot.unknown04 >= 1.0f)) {
        continue;
      }
      slot.AddRecast(recast, isRate);
      isRecastEnd |= slot.unknown04 >= 1.0f;
    }
  }
  return isRecastEnd;
}

void ARTS_PALETTE_DATA::AddSupportRecast(f32 recast, bool isRate) {
  unknown1e8[0].AddRecast(recast, isRate);
  unknown1e8[1].AddRecast(recast, isRate);
  unknown1e8[2].AddRecast(recast, isRate);
}

void ARTS_PALETTE_DATA::ResetAllRecast() {
  for (int i = 0; i < 19; i++) {
    unknown08[i].ResetRecast(false, false);
  }
  unknown1d0.ResetRecast(false, false);
  ResetSupportRecast();
}

void ARTS_PALETTE_DATA::ResetArtsRecast(bool isStart) {
  for (int i = 0; i < 19; i++) {
    unknown08[i].ResetRecast(isStart, false);
  }
}

void ARTS_PALETTE_DATA::ResetSupportRecast() {
  for (ARTS_SLOT_DATA &slot : unknown1e8) {
    slot.ResetRecast(false, false);
  }
}

const ARTS_SLOT_DATA *ARTS_PALETTE_DATA::GetSlotDataConst(int slot, bool isTalent) const {
  if (slot == SP_ATTACK_LEVEL_4_SLOT) {
    return &unknown1d0;
  }
  return &unknown08[isTalent ? slot + 16 : slot];
}

const ARTS_SLOT_DATA *ARTS_PALETTE_DATA::GetSupportSlotDataConst(int slot) const { return &unknown1e8[slot]; }

bool ARTS_PALETTE_DATA::IsEnableHealArts(bool isRecastEnd) const {
  for (int i = 0; i < 19; i++) {
    const ARTS_SLOT_DATA &slot = unknown08[i];
    if (slot.unknown00_0 == 0 || (isRecastEnd && slot.unknown04 < 1.0f)) {
      continue;
    }
    ARTS_DATA data;
    DataManager::get()->GetArtsData(static_cast<ARTS_DATA::DATA_TYPE>(slot.unknown01_3), slot.unknown00_0, data);
    if (data.unknown03_0 == ARTS_DATA::ARTS_TYPE_HEAL) {
      return true;
    }
    ENHANCE_EFFECT_DATA enhance;
    if (data.unknown90[slot.unknown02_5 - 1].unknown04 != 0 &&
        DataManager::GetEnhanceData(data.unknown90[slot.unknown02_5 - 1].unknown04, enhance, false) && enhance.id == ENHANCE_HEAL) {
      return true;
    }
  }
  return false;
}

} // namespace btl
