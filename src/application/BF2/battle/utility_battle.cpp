#include "battle/utility_battle.h"
#include "bdat.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_blade.h"
#include "gf/game/gf_game_cond.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_util.h"
#include "gf/object/gf_obj_util.h"
#include "gf/scom/gf_scom_achiev.h"
#include "gf/scom/gf_scom_enbook.h"

namespace btl {

enum {
  BDAT_BTL_CONDITION = 0x1e,
  BDAT_BTL_SE = 0x35,
};

constexpr int WEAPON_TYPE_COUNT = 26;
constexpr int ATTRIBUTE_COUNT = 8;

static const u16 s_weaponSeTypes[WEAPON_TYPE_COUNT] = {12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30};
static const u16 s_attributeSeTypes[ATTRIBUTE_COUNT] = {4, 5, 6, 7, 8, 9, 10, 11};
static const s8 s_antiAttributes[ATTRIBUTE_COUNT + 1] = {-1, 2, 1, 6, 5, 4, 3, 8, 7};

gf::GF_OBJ_HANDLE *Utility::GetLeader() { return gf::GfGameManager::getPartyLeaderDriver(); }

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

int Utility::GetTrustRank(int blade) { return gf::GfDataBlade::getTrustRank(blade); }

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

bool Utility::AI_GetCharacterGimmickPoint(gf::GF_OBJ_HANDLE *handle, mm::Vec3 &position) {
  return gf::GfGameUtil::getGmkTargetPointPos(position, handle);
}

bool Utility::AI_GetGimmickPoint(mm::Vec3 &position, u32 gimmick) { return gf::GfGameUtil::getGmkTargetPointPos(position, gimmick); }

} // namespace btl
