#include "battle/utility_battle.h"
#include "battle/battle_global.h"
#include "battle/btl_system_balance_access.h"
#include "battle/chain_attack_manager.h"
#include "battle/character/battle_character.h"
#include "battle/character/character_manager_battle.h"
#include "battle/character/character_parameter_battle.h"
#include "battle/data_manager_battle.h"
#include "battle/misc_battle.h"
#include "battle/sp_attack_manager.h"
#include "battle/talk_manager_battle.h"
#include "bdat.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_blade.h"
#include "gf/game/gf_game_cond.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_party.h"
#include "gf/game/gf_game_util.h"
#include "gf/object/gf_obj_util.h"
#include "gf/scom/gf_scom_achiev.h"
#include "gf/scom/gf_scom_enbook.h"
#include <float.h>
#include <math.h>
#include <stdlib.h>

namespace btl {

enum {
  BDAT_BTL_CONDITION = 0x1e,
  BDAT_BTL_SE = 0x35,
};

enum {
  SPECIAL_EFFECT_BENKEI_WEATHER = 2,
};

constexpr int WEAPON_TYPE_COUNT = 26;
constexpr int ATTRIBUTE_COUNT = 8;
constexpr int CHARACTER_PLAYER_COUNT = 20;
constexpr int CHARACTER_COUNT = 90;
constexpr int AI_ID_PLAYER_COUNT = 3;
constexpr int AI_ID_ENEMY_OFFSET = 100;
constexpr int AI_ID_ENEMY_COUNT = 69;
constexpr f32 FRAME_TO_SECOND = 1.0f / 30.0f;
constexpr f32 POS_BACKWARD_DISTANCE = 0.7f;

static gf::GF_OBJ_HANDLE *const INVALID_HANDLE = reinterpret_cast<gf::GF_OBJ_HANDLE *>(-1);

static const u16 s_weaponSeTypes[WEAPON_TYPE_COUNT] = {12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30};
static const u16 s_attributeSeTypes[ATTRIBUTE_COUNT] = {4, 5, 6, 7, 8, 9, 10, 11};
static const s8 s_antiAttributes[ATTRIBUTE_COUNT + 1] = {-1, 2, 1, 6, 5, 4, 3, 8, 7};

gf::GF_OBJ_HANDLE *Utility::GetLeader() { return gf::GfGameManager::getPartyLeaderDriver(); }

gf::GF_OBJ_HANDLE *Utility::GetControlCharacterHandle() {
  if (ChainAttackManager::get()->IsProc(false)) {
    int group = ChainAttackManager::get()->GetGroupIndex();
    if (group >= 0) {
      return gf::GfGameParty::getHandleDriver(group);
    }
  }

  return gf::GfGameManager::getPartyLeaderDriver();
}

bool Utility::IsSatisfyCondition(int condition) {
  u16 gameCondition = Bdat::getValCheck(gf::GfDataBdat::getFP(BDAT_BTL_CONDITION), "FLD_CondID", condition, 2);
  return gf::GfGameCond::isGameCond(gameCondition);
}

bool Utility::IsSatisfyConditionFld(int condition) { return gf::GfGameCond::isGameCond(condition); }

void Utility::AchieveCondition(BTL_ACHIEVE_COND condition, gf::GF_OBJ_HANDLE *handle, u32 value) {
  switch (condition) {
  case BTL_ACHIEVE_COND_BLADE_ARTS:
    gf::SCOM_ACHIEV_INC::createBladeArts(handle, value);
    break;
  case BTL_ACHIEVE_COND_BLADE_ARTS_SP:
    gf::SCOM_ACHIEV_INC::createBladeArtsSp(handle, value);
    break;
  case BTL_ACHIEVE_COND_BLADE_N_ARTS:
    gf::SCOM_ACHIEV_INC::createBladeNArts(handle);
    break;
  case BTL_ACHIEVE_COND_KIZUNA:
    gf::SCOM_ACHIEV_INC::createKizuna(handle);
    break;
  case BTL_ACHIEVE_COND_FIGHT_COMBO:
    gf::SCOM_ACHIEV_INC::createFightCombo(handle);
    break;
  case BTL_ACHIEVE_COND_FIGHT_COMBO_FINISH:
    gf::SCOM_ACHIEV_INC::createFightComboFinish(handle);
    break;
  case BTL_ACHIEVE_COND_ELEMENTAL_COMBO:
    gf::SCOM_ACHIEV_INC::createElementalCombo(handle);
    break;
  case BTL_ACHIEVE_COND_ELEMENTAL_COMBO_FINISH:
    gf::SCOM_ACHIEV_INC::createElementalComboFinish(handle);
    break;
  case BTL_ACHIEVE_COND_CHAIN_ATTACK:
    gf::SCOM_ACHIEV_INC::createChainAttack(handle);
    break;
  case BTL_ACHIEVE_COND_BUTTON_CHALLENGE:
    gf::SCOM_ACHIEV_INC::createButtonChallenge();
    break;
  case BTL_ACHIEVE_COND_HELP:
    gf::SCOM_ACHIEV_INC::createHelp(handle);
    break;
  case BTL_ACHIEVE_COND_POT_GET:
    gf::SCOM_ACHIEV_INC::createPotGet();
    break;
  case BTL_ACHIEVE_COND_AVOID:
    gf::SCOM_ACHIEV_INC::createAvoid(handle);
    break;
  case BTL_ACHIEVE_COND_GUARD:
    gf::SCOM_ACHIEV_INC::createGuard(handle);
    break;
  case BTL_ACHIEVE_COND_BLADE_CHANGE:
    gf::SCOM_ACHIEV_INC::createBladeChange(handle);
    break;
  case BTL_ACHIEVE_COND_RECOVER:
    gf::SCOM_ACHIEV_INC::createRecover(handle, value);
    break;
  case BTL_ACHIEVE_COND_BACK_ATTACK:
    gf::SCOM_ACHIEV_INC::createBackAttack(handle);
    break;
  }
}

int Utility::GetSeType(const char *packName) {
  if (packName != nullptr && packName[0] != '\0') {
    u8 *bdat = gf::GfDataBdat::getFP(BDAT_BTL_SE);
    int top = Bdat::getIdTop(bdat);
    int count = Bdat::getIdCount(bdat);
    for (int id = top; id < top + count; id++) {
      const char *name = reinterpret_cast<const char *>(Bdat::getValCheck(bdat, "PackName", id, 7));
      if (name != nullptr && __builtin_strcmp(name, packName) == 0) {
        return id;
      }
    }
  }

  return 0;
}

int Utility::GetWeaponSeType(int weaponType) {
  if (weaponType >= 1 && weaponType <= WEAPON_TYPE_COUNT) {
    return s_weaponSeTypes[weaponType - 1];
  }

  return 0;
}

int Utility::GetAttrSeType(int attribute) {
  if (attribute >= 1 && attribute <= ATTRIBUTE_COUNT) {
    return s_attributeSeTypes[attribute - 1];
  }

  return 0;
}

int Utility::GetAntiAttribute(u32 attribute) {
  if (attribute > ATTRIBUTE_COUNT) {
    return -1;
  }

  return s_antiAttributes[attribute];
}

int Utility::GetElementalEffectID() { return DataManager::get()->elementalEffectId; }

int Utility::GetUniteComboID(int attribute, int combo) {
  if (attribute == 0 || combo == 0) {
    return 0;
  }

  int stage = BattleGlobal::get()->GetElementalComboStage(combo) + attribute;
  return stage < 2 ? 0 : stage - 1;
}

int Utility::GetCharacterList(mm::mtl::FixedVector<u8, 90> &list, gf::GF_OBJ_HANDLE *handle, CHECK_CHR_NUM_MODE mode, u32 flags) {
  CharacterManager *characterManager = CharacterManager::get();
  int first = 0;
  int last = CHARACTER_COUNT - 1;
  if (mode != CHECK_CHR_NUM_MODE_ALL) {
    BattleCharacter *character = characterManager->GetCharacterConst(handle);
    if (character == nullptr) {
      return 0;
    }

    bool isPlayer = character->IsPlayer();
    if ((mode == CHECK_CHR_NUM_MODE_FRIEND && isPlayer) || (mode == CHECK_CHR_NUM_MODE_ENEMY && !isPlayer)) {
      last = CHARACTER_PLAYER_COUNT - 1;
    } else if ((mode == CHECK_CHR_NUM_MODE_ENEMY && isPlayer) || (mode == CHECK_CHR_NUM_MODE_FRIEND && !isPlayer)) {
      first = CHARACTER_PLAYER_COUNT;
    }
  }

  for (int id = first; id <= last; id++) {
    BattleCharacter *character = characterManager->GetCharacterConst(id);
    if (character == nullptr) {
      continue;
    }

    if ((flags & CHARACTER_LIST_BATTLE) && !character->IsBattle()) {
      continue;
    }

    if ((flags & CHARACTER_LIST_ALIVE) && character->IsDead(0)) {
      continue;
    }

    if ((flags & CHARACTER_LIST_DEAD) && !character->IsDead(0)) {
      continue;
    }

    if ((flags & CHARACTER_LIST_EXCLUDE_BLADE) && character->IsBlade()) {
      continue;
    }

    if ((flags & CHARACTER_LIST_EXCLUDE_SELF) && character->handle == handle) {
      continue;
    }

    list.push_back(id);
  }

  return list.size();
}

int Utility::GetPartyID(gf::GF_OBJ_HANDLE *handle) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
  if (character != nullptr) {
    const CharacterParameter *parameter = character->GetCharacterParameterConst(true);
    if (parameter != nullptr) {
      return parameter->partyId;
    }
  }

  return -1;
}

f32 Utility::GetDyingHpRate() { return BtlSystemBalanceAccess::get()->dyingHpRate; }

int Utility::GetResistantAttrMaxHP() { return BtlSystemBalanceAccess::get()->resistantAttrMaxHP; }

int Utility::GetTrustRank(int blade) { return gf::GfDataBlade::getTrustRank(blade); }

bool Utility::IsEnableDeadSequence() { return !TalkManager::get()->IsPlayingEnemyWinVoice(); }

bool Utility::IsThirdCharacter(gf::GF_OBJ_HANDLE *handle) { return gf::GfObjUtil::isTrinityBlade(handle); }

bool Utility::IsBladeArtsBuff(int buff) { return buff >= 1 && buff <= 9; }

void Utility::RegisterEnemyBook(ENBOOK_TYPE type, gf::GF_OBJ_HANDLE *handle, int value) {
  switch (type) {
  case ENBOOK_TYPE_IN_BATTLE:
    gf::SCOM_ENBOOK_IN_BATTLE::create(handle);
    break;
  case ENBOOK_TYPE_BOSS_TIME:
    gf::SCOM_ENBOOK_BOSS_TIME::create(handle, value);
    break;
  case ENBOOK_TYPE_DEFEAT_ENEMY:
    gf::SCOM_ENBOOK_DEFEAT_ENEMY::create(handle);
    break;
  case ENBOOK_TYPE_DEAD_PLAYER:
    gf::SCOM_ENBOOK_DEAD_PLAYER::create(handle);
    break;
  }
}

int Utility::AI_GetCharacterID(gf::GF_OBJ_HANDLE *handle) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
  if (character != nullptr) {
    return character->id;
  }

  return -1;
}

int Utility::AI_GetCharacterAIID(gf::GF_OBJ_HANDLE *handle) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
  if (character == nullptr) {
    return -1;
  }

  return AI_GetCharacterAIID(character);
}

int Utility::AI_GetCharacterAIID(const BattleCharacter *character) {
  int aiId = character->aiId;
  if (!character->IsPlayer()) {
    aiId += AI_ID_ENEMY_OFFSET;
  }

  return aiId;
}

gf::GF_OBJ_HANDLE *Utility::AI_GetCharacterHandle(int aiId) {
  if (aiId >= 0) {
    int id = AI_ConversionID_AItoBtl(aiId);
    if (id >= 0) {
      BattleCharacter *character = CharacterManager::get()->GetCharacterConst(id);
      if (character != nullptr) {
        return character->handle;
      }
    }
  }

  return INVALID_HANDLE;
}

int Utility::AI_ConversionID_AItoBtl(int aiId) {
  bool isPlayer;
  if (static_cast<u32>(aiId) < AI_ID_PLAYER_COUNT) {
    isPlayer = true;
  } else if (static_cast<u32>(aiId - AI_ID_ENEMY_OFFSET) < AI_ID_ENEMY_COUNT) {
    aiId -= AI_ID_ENEMY_OFFSET;
    isPlayer = false;
  } else {
    return -1;
  }

  return CharacterManager::get()->GetCharacterIDByAiChrID(aiId, isPlayer);
}

int Utility::AI_ConversionID_BtltoAI(int id) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(id);
  if (character == nullptr) {
    return -1;
  }

  return AI_GetCharacterAIID(character);
}

bool Utility::AI_IsValidID(int aiId) { return AI_GetCharacterHandle(aiId) != INVALID_HANDLE; }

void Utility::AI_GetObjectPosition(gf::GF_OBJ_HANDLE *handle, mm::Vec3 &position) {
  Misc::GetObjectTransform(handle, position, Misc::TRANS_TYPE_POSITION);
}

int Utility::AI_GetTargetCharacterID(gf::GF_OBJ_HANDLE *handle) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
  if (character == nullptr || character->target == INVALID_HANDLE) {
    return -1;
  }

  return AI_GetCharacterAIID(character->target);
}

int Utility::AI_IsFly(gf::GF_OBJ_HANDLE *handle) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
  if (character == nullptr) {
    return 0;
  }

  return character->isFly;
}

f32 Utility::AI_GetVertDiff(gf::GF_OBJ_HANDLE *handle, gf::GF_OBJ_HANDLE *target) {
  mm::Vec3 position;
  mm::Vec3 targetPosition;
  f32 diff = FLT_MAX;
  if (Misc::GetObjectTransform(handle, position, Misc::TRANS_TYPE_POSITION) &&
      Misc::GetObjectTransform(target, targetPosition, Misc::TRANS_TYPE_POSITION)) {
    diff = targetPosition.y - position.y;
  }

  return diff;
}

int Utility::AI_GetEatTargetCharacterID(gf::GF_OBJ_HANDLE *handle, f32 range) {
  mm::Vec3 position;
  if (!Misc::GetObjectTransform(handle, position, Misc::TRANS_TYPE_POSITION)) {
    return -1;
  }

  mm::mtl::FixedVector<u8, 90> list;
  if (GetCharacterList(list, handle, CHECK_CHR_NUM_MODE_FRIEND, CHARACTER_LIST_ALIVE | CHARACTER_LIST_EXCLUDE_BLADE | CHARACTER_LIST_EXCLUDE_SELF) <
      1) {
    return -1;
  }

  CharacterManager *characterManager = CharacterManager::get();
  int nearest = -1;
  f32 nearestDistance = FLT_MAX;
  for (u8 id : list) {
    BattleCharacter *character = characterManager->GetCharacterConst(id);
    const CharacterParameter *parameter = character->GetCharacterParameterConst(true);
    if (parameter != nullptr && parameter->IsEatTarget()) {
      mm::Vec3 targetPosition;
      Misc::GetObjectTransform(character->handle, targetPosition, Misc::TRANS_TYPE_POSITION);
      f32 x = targetPosition.x - position.x;
      f32 y = targetPosition.y - position.y;
      f32 z = targetPosition.z - position.z;
      f32 distance = sqrtf(x * x + y * y + z * z) - parameter->radius;
      if (distance > range) {
        continue;
      }

      if (distance < nearestDistance) {
        nearestDistance = distance;
        nearest = id;
      }
    }
  }

  if (nearest < 0) {
    return -1;
  }

  return AI_ConversionID_BtltoAI(nearest);
}

int Utility::AI_GetEnemyNum() {
  int count = 0;
  for (int id = CHARACTER_PLAYER_COUNT; id < CHARACTER_COUNT; id++) {
    BattleCharacter *character = CharacterManager::get()->GetCharacterConst(id);
    if (character != nullptr && !character->IsBlade() && !character->IsDead(0) && character->IsBattle()) {
      count++;
    }
  }

  return count;
}

int Utility::AI_GetPlayerNum() {
  int count = 0;
  for (int id = 0; id < CHARACTER_PLAYER_COUNT; id++) {
    BattleCharacter *character = CharacterManager::get()->GetCharacterConst(id);
    if (character != nullptr && !character->IsBlade() && !character->IsDead(0) && character->IsBattle()) {
      count++;
    }
  }

  return count;
}

int Utility::AI_GetAimCharacterNum(gf::GF_OBJ_HANDLE *handle) {
  mm::mtl::FixedVector<u8, 90> list;
  int count = 0;
  if (GetCharacterList(list, handle, CHECK_CHR_NUM_MODE_ENEMY, CHARACTER_LIST_BATTLE | CHARACTER_LIST_ALIVE | CHARACTER_LIST_EXCLUDE_BLADE) > 0) {
    CharacterManager *characterManager = CharacterManager::get();
    for (u8 id : list) {
      if (characterManager->GetCharacterConst(id)->target == handle) {
        count++;
      }
    }
  }

  return count;
}

int Utility::AI_GetFightComboID(gf::GF_OBJ_HANDLE *handle) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
  if (character == nullptr) {
    return 0;
  }

  return character->GetCharacterParameterConst(true)->GetFightComboDataConst()->id;
}

int Utility::AI_GetElementalComboID(gf::GF_OBJ_HANDLE *handle) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
  if (character == nullptr) {
    return 0;
  }

  return character->GetCharacterParameterConst(true)->elementalComboId;
}

int Utility::AI_GetReactionID(gf::GF_OBJ_HANDLE *handle) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
  if (character == nullptr) {
    return 0;
  }

  return character->reactionId;
}

int Utility::AI_GetStamp(gf::GF_OBJ_HANDLE *handle) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
  if (character == nullptr || character->IsDead(0)) {
    return 0;
  }

  return character->stamp;
}

f32 Utility::AI_GetHpPercent(gf::GF_OBJ_HANDLE *handle) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
  f32 percent = 0.0f;
  if (character != nullptr && !character->IsDead(0)) {
    const CharacterParameter *parameter = character->GetCharacterParameterConst(true);
    if (parameter != nullptr) {
      f32 hp = parameter->GetHP();
      u32 maxHp = parameter->GetMaxHP();
      if (maxHp != 0) {
        percent = hp >= maxHp ? 100.0f : hp / maxHp * 100.0f;
      }
    }
  }

  return percent;
}

u32 Utility::AI_GetLevel(gf::GF_OBJ_HANDLE *handle) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
  if (character != nullptr && !character->IsDead(0)) {
    const CharacterParameter *parameter = character->GetCharacterParameterConst(true);
    if (parameter != nullptr) {
      return parameter->GetLevel();
    }
  }

  return 0;
}

int Utility::AI_GetAttribute(gf::GF_OBJ_HANDLE *handle) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
  if (character != nullptr && !character->IsDead(0)) {
    const CharacterParameter *parameter = character->GetCharacterParameterConst(true);
    if (parameter != nullptr) {
      return parameter->GetAttribute();
    }
  }

  return 0;
}

int Utility::AI_GetRescueTargetCharacterID(gf::GF_OBJ_HANDLE *handle) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
  if (character != nullptr) {
    gf::GF_OBJ_HANDLE *target = character->GetRescueTarget();
    if (target != INVALID_HANDLE) {
      return AI_GetCharacterAIID(target);
    }
  }

  return -1;
}

int Utility::AI_GetBackAttackerCharacterID(gf::GF_OBJ_HANDLE *handle) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
  if (character == nullptr) {
    return -1;
  }

  return AI_ConversionID_BtltoAI(character->backAttacker);
}

bool Utility::AI_StartActionRescue(gf::GF_OBJ_HANDLE *handle, int aiId) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
  if (character != nullptr) {
    int target = AI_ConversionID_AItoBtl(aiId);
    if (target >= 0 && character->IsProcAI(false)) {
      return character->AI_Rescue(static_cast<BattleCharacter::ACTION_ID>(character->actionId), target);
    }
  }

  return false;
}

void Utility::AI_StartActionEscape(gf::GF_OBJ_HANDLE *handle) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
  if (character != nullptr) {
    character->StartBackHome();
  }
}

bool Utility::AI_StartActionArts(gf::GF_OBJ_HANDLE *handle, int slot, int aiId) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
  if (character == nullptr) {
    return false;
  }

  int target = -1;
  if (aiId >= 0) {
    target = AI_ConversionID_AItoBtl(aiId);
    if (target < 0) {
      return false;
    }
  }

  if (!character->IsProcAI(false) || !character->AI_Arts(static_cast<BattleCharacter::ACTION_ID>(character->actionId), slot)) {
    return false;
  }

  character->artsTarget = target;
  return true;
}

bool Utility::AI_StartActionArtsByID(gf::GF_OBJ_HANDLE *handle, int arts, int aiId) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
  if (character == nullptr) {
    return false;
  }

  int slot = character->GetArtsSlotIndex(arts);
  if (slot < 0) {
    return false;
  }

  return AI_StartActionArts(handle, slot, aiId);
}

bool Utility::AI_StartActionAttack(gf::GF_OBJ_HANDLE *handle) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
  if (character != nullptr && character->IsProcAI(false)) {
    return character->AI_Attack(static_cast<BattleCharacter::ACTION_ID>(character->actionId), false);
  }

  return false;
}

bool Utility::AI_StartActionBladeChange(gf::GF_OBJ_HANDLE *handle, int blade) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
  if (character != nullptr && character->IsProcAI(false)) {
    return character->AI_BladeChange(static_cast<BattleCharacter::ACTION_ID>(character->actionId), blade);
  }

  return false;
}

bool Utility::AI_IsAngry(gf::GF_OBJ_HANDLE *handle) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
  return character != nullptr && character->IsAngry();
}

void Utility::AI_SetAngry(gf::GF_OBJ_HANDLE *handle, f32 time) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
  if (character != nullptr) {
    character->SetAngry(true, time);
  }
}

void Utility::AI_EndAngry(gf::GF_OBJ_HANDLE *handle) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
  if (character != nullptr) {
    character->SetAngry(false, -1.0f);
  }
}

bool Utility::AI_TurnTarget(gf::GF_OBJ_HANDLE *handle) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
  if (character == nullptr || !character->IsEnableTurnAI()) {
    return false;
  }

  character->TurnTarget(false, false, true);
  return true;
}

bool Utility::AI_TurnDirection(gf::GF_OBJ_HANDLE *handle, const mm::Vec3 &direction) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
  if (character == nullptr || !character->IsEnableTurnAI()) {
    return false;
  }

  mm::Vec3 normalized = direction;
  Misc::NormalizeXZ(normalized);
  character->TurnDirection(normalized, false, true);
  return true;
}

void Utility::AI_SetUseNavi(gf::GF_OBJ_HANDLE *handle, bool isUseNavi) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
  if (character != nullptr) {
    character->isUseNavi = isUseNavi;
  }
}

bool Utility::AI_StartMovePosition(gf::GF_OBJ_HANDLE *handle, const mm::Vec3 &position, f32 time) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
  if (character == nullptr) {
    return false;
  }

  BattleCharacter::AI_MOVE_PARAM param;
  param.distance = 0.0f;
  param.time = time;
  param.type = BattleCharacter::MOVE_TYPE_POSITION;
  param.position = &position;
  if (!character->IsProcAI(true)) {
    return false;
  }

  return character->AI_Move(static_cast<BattleCharacter::ACTION_ID>(character->actionId), false, &param);
}

bool Utility::AI_StartMoveTarget(gf::GF_OBJ_HANDLE *handle, int aiId, f32 distance, f32 time) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
  if (character == nullptr) {
    return false;
  }

  BattleCharacter::AI_MOVE_PARAM param;
  param.distance = distance;
  param.time = time;
  param.target = AI_GetCharacterHandle(aiId);
  if (!character->IsProcAI(true)) {
    return false;
  }

  return character->AI_Move(static_cast<BattleCharacter::ACTION_ID>(character->actionId), false, &param);
}

bool Utility::AI_StartMoveFront(gf::GF_OBJ_HANDLE *handle, int aiId, f32 distance, f32 time) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
  if (character == nullptr) {
    return false;
  }

  BattleCharacter::AI_MOVE_PARAM param;
  param.distance = distance;
  param.time = time;
  param.type = BattleCharacter::MOVE_TYPE_FRONT;
  param.target = AI_GetCharacterHandle(aiId);
  if (!character->IsProcAI(true)) {
    return false;
  }

  return character->AI_Move(static_cast<BattleCharacter::ACTION_ID>(character->actionId), false, &param);
}

bool Utility::AI_StartMoveSide(gf::GF_OBJ_HANDLE *handle, int aiId, f32 distance, f32 time) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
  if (character == nullptr) {
    return false;
  }

  BattleCharacter::AI_MOVE_PARAM param;
  param.distance = distance;
  param.time = time;
  param.type = BattleCharacter::MOVE_TYPE_SIDE;
  param.target = AI_GetCharacterHandle(aiId);
  if (!character->IsProcAI(true)) {
    return false;
  }

  return character->AI_Move(static_cast<BattleCharacter::ACTION_ID>(character->actionId), false, &param);
}

bool Utility::AI_StartMoveLeft(gf::GF_OBJ_HANDLE *handle, int aiId, f32 distance, f32 time) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
  if (character == nullptr) {
    return false;
  }

  BattleCharacter::AI_MOVE_PARAM param;
  param.distance = distance;
  param.time = time;
  param.type = BattleCharacter::MOVE_TYPE_LEFT;
  param.target = AI_GetCharacterHandle(aiId);
  if (!character->IsProcAI(true)) {
    return false;
  }

  return character->AI_Move(static_cast<BattleCharacter::ACTION_ID>(character->actionId), false, &param);
}

bool Utility::AI_StartMoveRight(gf::GF_OBJ_HANDLE *handle, int aiId, f32 distance, f32 time) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
  if (character == nullptr) {
    return false;
  }

  BattleCharacter::AI_MOVE_PARAM param;
  param.distance = distance;
  param.time = time;
  param.type = BattleCharacter::MOVE_TYPE_RIGHT;
  param.target = AI_GetCharacterHandle(aiId);
  if (!character->IsProcAI(true)) {
    return false;
  }

  return character->AI_Move(static_cast<BattleCharacter::ACTION_ID>(character->actionId), false, &param);
}

bool Utility::AI_StartMoveBack(gf::GF_OBJ_HANDLE *handle, int aiId, f32 distance, f32 time) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
  if (character == nullptr) {
    return false;
  }

  BattleCharacter::AI_MOVE_PARAM param;
  param.distance = distance;
  param.time = time;
  param.type = BattleCharacter::MOVE_TYPE_BACK;
  param.target = AI_GetCharacterHandle(aiId);
  if (!character->IsProcAI(true)) {
    return false;
  }

  return character->AI_Move(static_cast<BattleCharacter::ACTION_ID>(character->actionId), false, &param);
}

bool Utility::AI_StartMoveFriendBack(gf::GF_OBJ_HANDLE *handle, f32 distance, f32 time) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
  if (character == nullptr) {
    return false;
  }

  mm::mtl::FixedVector<u8, 90> list;
  if (GetCharacterList(list,
                       handle,
                       CHECK_CHR_NUM_MODE_FRIEND,
                       CHARACTER_LIST_BATTLE | CHARACTER_LIST_ALIVE | CHARACTER_LIST_EXCLUDE_BLADE | CHARACTER_LIST_EXCLUDE_SELF) < 1) {
    return false;
  }

  mm::Vec3 position = character->position;
  CharacterManager *characterManager = CharacterManager::get();
  gf::GF_OBJ_HANDLE *friendHandle = INVALID_HANDLE;
  f32 nearestLength = FLT_MAX;
  for (u8 id : list) {
    BattleCharacter *friendCharacter = characterManager->GetCharacterConst(id);
    mm::Vec3 friendPosition;
    Misc::GetObjectTransform(friendCharacter->handle, friendPosition, Misc::TRANS_TYPE_POSITION);
    f32 length = Misc::CalcSquareLength(friendPosition, position);
    if (length < nearestLength) {
      nearestLength = length;
      friendHandle = friendCharacter->handle;
    }
  }

  if (friendHandle == INVALID_HANDLE) {
    return false;
  }

  BattleCharacter::AI_MOVE_PARAM param;
  param.distance = distance;
  param.time = time;
  param.type = BattleCharacter::MOVE_TYPE_BACK;
  param.target = friendHandle;
  if (!character->IsProcAI(true)) {
    return false;
  }

  return character->AI_Move(static_cast<BattleCharacter::ACTION_ID>(character->actionId), false, &param);
}

bool Utility::AI_StartMoveSatellite(gf::GF_OBJ_HANDLE *handle, bool isClockwise, f32 frame) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
  if (character == nullptr) {
    return false;
  }

  BattleCharacter::AI_MOVE_PARAM param;
  param.distance = 0.0f;
  param.time = frame * FRAME_TO_SECOND;
  param.type = isClockwise ? BattleCharacter::MOVE_TYPE_SATELLITE_CLOCKWISE : BattleCharacter::MOVE_TYPE_SATELLITE_COUNTERCLOCKWISE;
  if (!character->IsProcAI(true)) {
    return false;
  }

  return character->AI_Move(static_cast<BattleCharacter::ACTION_ID>(character->actionId), false, &param);
}

bool Utility::AI_StartMoveBackward(gf::GF_OBJ_HANDLE *handle, f32 distance, f32 time) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
  if (character == nullptr) {
    return false;
  }

  BattleCharacter::AI_MOVE_PARAM param;
  param.distance = distance;
  param.time = time;
  param.type = BattleCharacter::MOVE_TYPE_BACKWARD;
  if (!character->IsProcAI(true)) {
    return false;
  }

  return character->AI_Move(static_cast<BattleCharacter::ACTION_ID>(character->actionId), false, &param);
}

bool Utility::AI_StartMovePosBackward(gf::GF_OBJ_HANDLE *handle, mm::Vec3 &position, f32 time) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
  if (character == nullptr) {
    return false;
  }

  mm::Vec3 destination;
  if (Misc::CalcDirectionXZ(character->position, position, destination)) {
    destination *= POS_BACKWARD_DISTANCE;
    destination += position;
  } else {
    destination = position;
  }

  BattleCharacter::AI_MOVE_PARAM param;
  param.distance = 0.0f;
  param.time = time;
  param.type = BattleCharacter::MOVE_TYPE_BACKWARD;
  param.position = &destination;
  if (!character->IsProcAI(true)) {
    return false;
  }

  return character->AI_Move(static_cast<BattleCharacter::ACTION_ID>(character->actionId), false, &param);
}

void Utility::AI_MoveStop(gf::GF_OBJ_HANDLE *handle, bool isImmediate) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
  if (character != nullptr) {
    character->MoveStop(isImmediate);
  }
}

bool Utility::AI_IsDestruct(gf::GF_OBJ_HANDLE *handle) { return false; }

int Utility::AI_GetTargetDirection(gf::GF_OBJ_HANDLE *handle, gf::GF_OBJ_HANDLE *target) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(target);
  if (character == nullptr) {
    return 0;
  }

  bool isOut;
  u8 position = character->CheckAttackPosition(handle, false, &isOut);
  if (isOut) {
    return 0;
  }

  return position < 4 ? position + 1 : 0;
}

int Utility::AI_CheckCharacterNum(gf::GF_OBJ_HANDLE *handle, int direction, CHECK_CHR_NUM_MODE mode) {
  mm::mtl::FixedVector<u8, 90> list;
  if (GetCharacterList(
          list, handle, mode, CHARACTER_LIST_BATTLE | CHARACTER_LIST_ALIVE | CHARACTER_LIST_EXCLUDE_BLADE | CHARACTER_LIST_EXCLUDE_SELF) < 1) {
    return 0;
  }

  int position = direction >= 1 && direction <= 4 ? direction - 1 : -1;
  CharacterManager *characterManager = CharacterManager::get();
  int count = 0;
  for (u8 id : list) {
    bool isOut;
    u8 attackPosition = characterManager->GetCharacterConst(id)->CheckAttackPosition(handle, false, &isOut);
    if (!isOut && attackPosition == position) {
      count++;
    }
  }

  return count;
}

int Utility::AI_CheckHpRateCharacterNum(gf::GF_OBJ_HANDLE *handle, int percent, CHECK_CHR_NUM_MODE mode) {
  mm::mtl::FixedVector<u8, 90> list;
  if (GetCharacterList(list, handle, mode, CHARACTER_LIST_BATTLE | CHARACTER_LIST_ALIVE | CHARACTER_LIST_EXCLUDE_BLADE) < 1) {
    return 0;
  }

  f32 rate = percent * 0.01f;
  CharacterManager *characterManager = CharacterManager::get();
  int count = 0;
  for (u8 id : list) {
    const CharacterParameter *parameter = characterManager->GetCharacterConst(id)->GetCharacterParameterConst(true);
    if (parameter != nullptr) {
      count += parameter->GetHPRate() <= rate;
    }
  }

  return count;
}

int Utility::AI_GetDeadCharacterNum(gf::GF_OBJ_HANDLE *handle, CHECK_CHR_NUM_MODE mode) {
  mm::mtl::FixedVector<u8, 90> list;
  return GetCharacterList(
      list, handle, mode, CHARACTER_LIST_BATTLE | CHARACTER_LIST_DEAD | CHARACTER_LIST_EXCLUDE_BLADE | CHARACTER_LIST_EXCLUDE_SELF);
}

void Utility::AI_AddKizuna(gf::GF_OBJ_HANDLE *handle, int kizuna) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
  if (character != nullptr) {
    character->AddKizuna(kizuna);
  }
}

int Utility::AI_GetKizunaStage(gf::GF_OBJ_HANDLE *handle) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
  if (character == nullptr) {
    return 0;
  }

  return character->GetKizunaStage(nullptr);
}

bool Utility::AI_StartSpAttack(gf::GF_OBJ_HANDLE *handle) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
  if (character != nullptr && character->IsProcAI(false)) {
    return character->AI_SpAttack(static_cast<BattleCharacter::ACTION_ID>(character->actionId), false, false);
  }

  return false;
}

bool Utility::AI_IsBattleOpening(gf::GF_OBJ_HANDLE *handle) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
  bool isBattleOpening = false;
  if (character != nullptr) {
    isBattleOpening = character->isBattleOpening;
    character->isBattleOpening = false;
  }

  return isBattleOpening;
}

bool Utility::AI_IsInAttackRange(gf::GF_OBJ_HANDLE *handle) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
  return character != nullptr && character->IsInAttackRange(-1, nullptr);
}

bool Utility::AI_IsEnableArts(gf::GF_OBJ_HANDLE *handle, int slot, int aiId) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
  if (character == nullptr) {
    return false;
  }

  return character->IsEnableArts(-1, slot, 0, AI_GetCharacterHandle(aiId)) == 0;
}

bool Utility::AI_IsEnableArtsByID(gf::GF_OBJ_HANDLE *handle, int arts, int aiId) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
  if (character == nullptr) {
    return false;
  }

  int slot = character->GetArtsSlotIndex(arts);
  if (slot < 0) {
    return false;
  }

  return AI_IsEnableArts(handle, slot, aiId);
}

int Utility::AI_SearchVoiceCodeCharacter(int voiceCode) {
  CharacterManager *characterManager = CharacterManager::get();
  for (int id = 0; id < CHARACTER_COUNT; id++) {
    BattleCharacter *character = characterManager->GetCharacterConst(id);
    if (character != nullptr && atoi(character->voiceCode) == voiceCode) {
      return AI_GetCharacterAIID(character);
    }
  }

  return -1;
}

int Utility::AI_GetVoiceCode(gf::GF_OBJ_HANDLE *handle) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
  if (character == nullptr) {
    return 0;
  }

  return atoi(character->voiceCode);
}

void Utility::AI_PlayVoice(gf::GF_OBJ_HANDLE *handle, int voice) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
  if (character != nullptr) {
    TalkManager::get()->PlayVoice(character->id, voice);
  }
}

int Utility::AI_GetPlayVoiceID(gf::GF_OBJ_HANDLE *handle) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
  if (character == nullptr) {
    return 0;
  }

  return TalkManager::get()->GetPlayVoiceID(character->id);
}

bool Utility::AI_IsBuff(gf::GF_OBJ_HANDLE *handle, int buff) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
  if (character != nullptr) {
    CharacterParameter *parameter = character->GetCharacterParameter(true);
    if (parameter != nullptr) {
      return parameter->IsBuff(buff);
    }
  }

  return false;
}

bool Utility::AI_IsProcSpAttack() { return SpAttackManager::get()->procCount > 0; }

int Utility::AI_GetBdatID(gf::GF_OBJ_HANDLE *handle) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
  if (character == nullptr) {
    return 0;
  }

  return character->bdatId;
}

bool Utility::AI_GetCharacterGimmickPoint(gf::GF_OBJ_HANDLE *handle, mm::Vec3 &position) {
  return gf::GfGameUtil::getGmkTargetPointPos(position, handle);
}

bool Utility::AI_GetGimmickPoint(mm::Vec3 &position, u32 gimmick) { return gf::GfGameUtil::getGmkTargetPointPos(position, gimmick); }

void Utility::AI_SetScout(gf::GF_OBJ_HANDLE *handle, bool isScout) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
  if (character != nullptr) {
    character->SetScout(isScout);
  }
}

void Utility::AI_SetSuperArmor(gf::GF_OBJ_HANDLE *handle, f32 time) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
  if (character != nullptr) {
    character->SetSuperArmorTime(time);
  }
}

int Utility::AI_EnemyKillNum() { return BattleGlobal::get()->enemyKillNum; }

bool Utility::AI_IsBenkeiWeather() { return DataManager::get()->IsSpecialEffects(SPECIAL_EFFECT_BENKEI_WEATHER); }

} // namespace btl
