#include "gf/data/gf_bdat_rsc.h"
#include "gf/data/gf_data_achievement.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_npc.h"
#include "gf/data/gf_data_util.h"
#include "gf/game/achiev/gf_achiev_manager.h"
#include "gf/game/quest/gf_achiev_quest.h"
#include "gf/scom/gf_scom_achiev.h"
#include "gf/util/gf_item_util.h"
#include "mm_mtl/algorithm.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
struct MsgObjectNotifyDamage;

// Inferred role: achievement statistics ids; original enum and enumerator names unknown.
enum unknown001 {
  unknown001_32 = 0x20,
  unknown001_33 = 0x21,
  unknown001_57 = 0x39,
  unknown001_59 = 0x3b,
  unknown001_38 = 0x26,
  unknown001_39 = 0x27,
  unknown001_40 = 0x28,
  unknown001_41 = 0x29,
  unknown001_42 = 0x2a,
  unknown001_43 = 0x2b,
  unknown001_44 = 0x2c,
  unknown001_45 = 0x2d,
  unknown001_46 = 0x2e,
  unknown001_47 = 0x2f,
  unknown001_48 = 0x30,
  unknown001_56 = 0x38,
  unknown001_67 = 0x43,
  unknown001_3 = 0x3,
  unknown001_22 = 0x16,
  unknown001_24 = 0x18,
  unknown001_25 = 0x19,
  unknown001_26 = 0x1a,
  unknown001_27 = 0x1b,
  unknown001_28 = 0x1c,
  unknown001_29 = 0x1d,
  unknown001_30 = 0x1e,
  unknown001_31 = 0x1f,
};

// Inferred role: counts of the blades of the party and the reserve; no game symbol, original type and member names unknown.
struct unknown002 {
  u32 unknown00; // Inferred role: all blades.
  u32 unknown04; // Inferred role: male blades.
  u32 unknown08; // Inferred role: female blades.
  u32 unknown0c; // Inferred role: blades of race 2.
  u32 unknown10; // Inferred role: blades of weapon type 10.
  u32 unknown14; // Inferred role: blades of weapon type 11.
  u32 unknown18; // Inferred role: blades of weapon type 12.
  u32 unknown1c; // Inferred role: blades of weapon type 13.
  u32 unknown20; // Inferred role: blades of weapon type 14.
  u32 unknown24; // Inferred role: blades of weapon type 15.
  u32 unknown28; // Inferred role: blades of weapon type 16.
};

// Inferred role: counts the blades of the party and the reserve, except one; no game symbol, original name unknown.
static void unknown003(unknown002 &counts, u16 except) {
  mm::mtl::FixedVector<u16, BLADE_COUNT> blades;
  GfDataBlade::getListParty(blades);
  GfDataBlade::getListReserver(blades);
  GfDataBlade::removeSameBlade(blades);
  u16 *it = mm::mtl::find(blades.begin(), blades.end(), except);
  if (it != blades.end()) {
    blades.erase(it);
  }
  counts.unknown00 = blades.size();
  u16 *end = blades.end();
  for (u16 *it = blades.begin(); it != end; it++) {
    u32 blade = *it;
    u32 gender = GfDataBlade::getGender(blade);
    if (gender == 1) {
      counts.unknown04++;
    } else if (gender == 2) {
      counts.unknown08++;
    }
    if (GfDataBlade::getRace(blade) == 2) {
      counts.unknown0c++;
    }
    switch (GfDataBlade::getBladeWpnType(blade)) {
    case 10:
      counts.unknown10++;
      break;
    case 11:
      counts.unknown14++;
      break;
    case 12:
      counts.unknown18++;
      break;
    case 13:
      counts.unknown1c++;
      break;
    case 14:
      counts.unknown20++;
      break;
    case 15:
      counts.unknown24++;
      break;
    case 16:
      counts.unknown28++;
      break;
    }
  }
}

void GfAchievStats::checkBuyItemFromShop(u32 item, u32 count, u32 shop, u32 money) {
  SCOM_ACHIEV_INC::addTotalCount(unknown001_32, count);
  SCOM_ACHIEV_INC::create(unknown001_32, count, 0);
  SCOM_ACHIEV_INC::addTotalCount(unknown001_57, money);
  SCOM_ACHIEV_INC::create(unknown001_57, money, 0);
}

void GfAchievStats::checkSellItemFromShop(u32 item, u32 count, u32 shop, u32 money) {
  SCOM_ACHIEV_INC::addTotalCount(unknown001_33, count);
  SCOM_ACHIEV_INC::create(unknown001_33, count, 0);
  SCOM_ACHIEV_INC::addTotalCount(unknown001_59, money);
  SCOM_ACHIEV_INC::create(unknown001_59, money, 0);
}

void GfAchievStats::checkFallLength(GF_OBJ_HANDLE *, const MsgObjectNotifyDamage &) {}

u32 GfAchievStats::checkMove(u32 move, u32) { return move; }

void GfAchievStats::checkBladeActivate(u32 blade) {
  unknown002 counts = {};
  unknown003(counts, blade);
  SCOM_ACHIEV_INC::createParty(unknown001_38, counts.unknown00);
  SCOM_ACHIEV_INC::createParty(unknown001_39, counts.unknown04);
  SCOM_ACHIEV_INC::createParty(unknown001_40, counts.unknown08);
  SCOM_ACHIEV_INC::createParty(unknown001_41, counts.unknown0c);
  SCOM_ACHIEV_INC::createParty(unknown001_42, counts.unknown10);
  SCOM_ACHIEV_INC::createParty(unknown001_43, counts.unknown14);
  SCOM_ACHIEV_INC::createParty(unknown001_44, counts.unknown18);
  SCOM_ACHIEV_INC::createParty(unknown001_45, counts.unknown1c);
  SCOM_ACHIEV_INC::createParty(unknown001_46, counts.unknown20);
  SCOM_ACHIEV_INC::createParty(unknown001_47, counts.unknown24);
  SCOM_ACHIEV_INC::createParty(unknown001_48, counts.unknown28);
}

// Inferred role: last object whose talk was counted by checkTalk; no game symbol, original name unknown.
static GF_OBJ_HANDLE *unknown004;

void GfAchievStats::checkTalk(u32 npc, GF_OBJ_HANDLE *handle) {
  if (unknown004 == handle) {
    return;
  }
  unknown004 = handle;
  SCOM_ACHIEV_INC::create(unknown001_3, 1, 0);
  SCOM_ACHIEV_INC::addTotalCount(unknown001_22, 1);
  SCOM_ACHIEV_INC::create(unknown001_22, 1, 0);
  if (npc > 2000) {
    switch (GfBdatRsc::get()->getRscNpcListRoots(npc)) {
    case 1:
      SCOM_ACHIEV_INC::createParty(unknown001_26, 1);
      break;
    case 2:
      SCOM_ACHIEV_INC::createParty(unknown001_25, 1);
      break;
    case 3:
      SCOM_ACHIEV_INC::createParty(unknown001_27, 1);
      break;
    case 4:
      SCOM_ACHIEV_INC::createParty(unknown001_29, 1);
      break;
    case 5:
      SCOM_ACHIEV_INC::createParty(unknown001_24, 1);
      break;
    case 6:
      SCOM_ACHIEV_INC::createParty(unknown001_28, 1);
      break;
    }
  }
  u32 gender = GfDataNpc::getGender(npc);
  if (gender == 1) {
    SCOM_ACHIEV_INC::createParty(unknown001_30, 1);
  } else if (gender == 2) {
    SCOM_ACHIEV_INC::createParty(unknown001_31, 1);
  }
}

s32 GfAchievStats::getAchievementTotalCount(const AchievQuest &achievQuest) {
  unknown002 counts = {};
  unknown003(counts, achievQuest.unknown16);
  if (GfDataAchievement::getAchievementTotalFlgIndex(achievQuest.unknown0e) >= 0) {
    return GfDataAchievement::getTotalCount(achievQuest.unknown0e);
  }
  switch (achievQuest.unknown0e) {
  case unknown001_38:
    return counts.unknown00;
  case unknown001_39:
    return counts.unknown04;
  case unknown001_40:
    return counts.unknown08;
  case unknown001_41:
    return counts.unknown0c;
  case unknown001_42:
    return counts.unknown10;
  case unknown001_43:
    return counts.unknown14;
  case unknown001_44:
    return counts.unknown18;
  case unknown001_45:
    return counts.unknown1c;
  case unknown001_46:
    return counts.unknown20;
  case unknown001_47:
    return counts.unknown24;
  case unknown001_48:
    return counts.unknown28;
  case unknown001_56:
    return GfDataUtil::getMoney();
  case unknown001_67:
    return GfItemUtil::getCrystalNum();
  default:
    return -1;
  }
}

} // namespace gf
