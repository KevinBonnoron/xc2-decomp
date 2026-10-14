#pragma once
#include "types.h"

namespace mm {
struct Vec3;
}

namespace gf {
struct GF_OBJ_HANDLE;
}

namespace btl {

class Utility {
public:
  enum BTL_ACHIEVE_COND {
    BTL_ACHIEVE_COND_BLADE_ARTS,
    BTL_ACHIEVE_COND_BLADE_ARTS_SP,
    BTL_ACHIEVE_COND_BLADE_N_ARTS,
    BTL_ACHIEVE_COND_KIZUNA,
    BTL_ACHIEVE_COND_FIGHT_COMBO,
    BTL_ACHIEVE_COND_FIGHT_COMBO_FINISH,
    BTL_ACHIEVE_COND_ELEMENTAL_COMBO,
    BTL_ACHIEVE_COND_ELEMENTAL_COMBO_FINISH,
    BTL_ACHIEVE_COND_CHAIN_ATTACK,
    BTL_ACHIEVE_COND_BUTTON_CHALLENGE,
    BTL_ACHIEVE_COND_HELP,
    BTL_ACHIEVE_COND_POT_GET,
    BTL_ACHIEVE_COND_AVOID,
    BTL_ACHIEVE_COND_GUARD,
    BTL_ACHIEVE_COND_BLADE_CHANGE,
    BTL_ACHIEVE_COND_RECOVER,
    BTL_ACHIEVE_COND_BACK_ATTACK,
  };

  enum ENBOOK_TYPE {
    ENBOOK_TYPE_IN_BATTLE,
    ENBOOK_TYPE_BOSS_TIME,
    ENBOOK_TYPE_DEFEAT_ENEMY,
    ENBOOK_TYPE_DEAD_PLAYER,
  };

  static gf::GF_OBJ_HANDLE *GetLeader();
  static bool IsSatisfyCondition(int condition);
  static bool IsSatisfyConditionFld(int condition);
  static void AchieveCondition(BTL_ACHIEVE_COND condition, gf::GF_OBJ_HANDLE *handle, u32 value);
  static int GetSeType(const char *packName);
  static int GetWeaponSeType(int weaponType);
  static int GetAttrSeType(int attribute);
  static int GetAntiAttribute(u32 attribute);
  static int GetTrustRank(int blade);
  static bool IsThirdCharacter(gf::GF_OBJ_HANDLE *handle);
  static bool IsBladeArtsBuff(int buff);
  static void RegisterEnemyBook(ENBOOK_TYPE type, gf::GF_OBJ_HANDLE *handle, int value);
  static bool AI_GetCharacterGimmickPoint(gf::GF_OBJ_HANDLE *handle, mm::Vec3 &position);
  static bool AI_GetGimmickPoint(mm::Vec3 &position, u32 gimmick);
};

} // namespace btl
