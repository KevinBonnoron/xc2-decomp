#include "gf/data/gf_bdat_chrenarrange.h"
#include "bdat.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/gf_allocator.h"

namespace gf {
namespace _gfbcb {

enum {
  ChrEnArrangeParamID,
  ChrEnArrangeEnemyBladeID,
  ChrEnArrangeBladeID,
  ChrEnArrangeBladeAtr,
  ChrEnArrangeExtraParts,
  ChrEnArrangeName,
  ChrEnArrangeDebug_Name,
  ChrEnArrangeLv,
  ChrEnArrangeLvRand,
  ChrEnArrangeHpOver,
  ChrEnArrangeExpRev,
  ChrEnArrangeGoldRev,
  ChrEnArrangeWPRev,
  ChrEnArrangeSPRev,
  ChrEnArrangeDropTableID,
  ChrEnArrangeDropTableID2,
  ChrEnArrangeDropTableID3,
  ChrEnArrangePreciousID,
  ChrEnArrangeScale,
  ChrEnArrangeChrSize,
  ChrEnArrangeTurnSize,
  ChrEnArrangeFlagNamed,
  ChrEnArrangeFlagNamedFlag,
  ChrEnArrangeFlagmBoss,
  ChrEnArrangeFlagmBossFlag,
  ChrEnArrangeFlagChild,
  ChrEnArrangeFlagChildFlag,
  ChrEnArrangeFlagFAOff,
  ChrEnArrangeFlagFAOffFlag,
  ChrEnArrangeFlagNoEcSkip,
  ChrEnArrangeFlagNoEcSkipFlag,
  ChrEnArrangeFlagLinkType,
  ChrEnArrangeFlagLinkTypeFlag,
  ChrEnArrangeFlagChrColiOff,
  ChrEnArrangeFlagChrColiOffFlag,
  ChrEnArrangeFlagNoTarget,
  ChrEnArrangeFlagNoTargetFlag,
  ChrEnArrangeFlagHikariSP4,
  ChrEnArrangeFlagHikariSP4Flag,
  ChrEnArrangeFlagHomuri,
  ChrEnArrangeFlagHomuriFlag,
  ChrEnArrangeFlagHikari,
  ChrEnArrangeFlagHikariFlag,
  ChrEnArrangeFlagNoNaviMesh,
  ChrEnArrangeFlagNoNaviMeshFlag,
  ChrEnArrangeFlagFixed,
  ChrEnArrangeFlagFixedFlag,
  ChrEnArrangeFlagDropFront,
  ChrEnArrangeFlagDropFrontFlag,
  ChrEnArrangeFlagNoWarp,
  ChrEnArrangeFlagNoWarpFlag,
  ChrEnArrangeFlagIgnoreLevPow,
  ChrEnArrangeFlagIgnoreLevPowFlag,
  ChrEnArrangeFlagAlwaysAttack,
  ChrEnArrangeFlagAlwaysAttackFlag,
  ChrEnArrangeFlagPGMax,
  ChrEnArrangeFlagPGMaxFlag,
  ChrEnArrangeFlagSalvage,
  ChrEnArrangeFlagSalvageFlag,
  ChrEnArrangeLinkRadius,
  ChrEnArrangeDetects,
  ChrEnArrangeSearchRange,
  ChrEnArrangeSearchAngle,
  ChrEnArrangeSearchRadius,
  ChrEnArrangeBatInterval,
  ChrEnArrangeBatArea,
  ChrEnArrangeBatAreaType,
  ChrEnArrangeAiGroup,
  ChrEnArrangeAiGroupNum,
  ChrEnArrangeBookID,
  ChrEnArrangeEnhanceID1,
  ChrEnArrangeEnhanceID2,
  ChrEnArrangeEnhanceID3,
  ChrEnArrangeParamRev,
  ChrEnArrangeRstDebuffRev,
  ChrEnArrangeHealPotTypeRev,
  ChrEnArrangeSummonID,
  ChrEnArrangeBGMID,
  ChrEnArrangeSeEnvID,
  ChrEnArrangeZoneID,
  ChrEnArrangeTimeSet,
  ChrEnArrangeWeatherSet,
  ChrEnArrangeDriverLev,
  BTL_EnBookBaseEnemyID,
  BTL_EnBookBOOK_POP_TIME,
  BTL_EnBookBOOK_popWeather,
  MEMBER_COUNT,
};

static u8 *s_members[MEMBER_COUNT];

void initChrEnArrangeParamID(const CBdatWrapper &wrapper) { s_members[ChrEnArrangeParamID] = Bdat::getMember(wrapper.data, "ParamID"); }

u32 getChrEnArrangeParamID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeParamID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnArrangeParamID], id, 2).valueU16;
}

void initChrEnArrangeEnemyBladeID(const CBdatWrapper &wrapper) {
  s_members[ChrEnArrangeEnemyBladeID] = Bdat::getMember(wrapper.data, "EnemyBladeID");
}

u32 getChrEnArrangeEnemyBladeID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeEnemyBladeID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnArrangeEnemyBladeID], id, 2).valueU16;
}

void initChrEnArrangeBladeID(const CBdatWrapper &wrapper) { s_members[ChrEnArrangeBladeID] = Bdat::getMember(wrapper.data, "BladeID"); }

u32 getChrEnArrangeBladeID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeBladeID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnArrangeBladeID], id, 2).valueU16;
}

void initChrEnArrangeBladeAtr(const CBdatWrapper &wrapper) { s_members[ChrEnArrangeBladeAtr] = Bdat::getMember(wrapper.data, "BladeAtr"); }

u32 getChrEnArrangeBladeAtr(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeBladeAtr] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnArrangeBladeAtr], id, 1).valueU8;
}

void initChrEnArrangeExtraParts(const CBdatWrapper &wrapper) { s_members[ChrEnArrangeExtraParts] = Bdat::getMember(wrapper.data, "ExtraParts"); }

u32 getChrEnArrangeExtraParts(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeExtraParts] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnArrangeExtraParts], id, 1).valueU8;
}

void initChrEnArrangeName(const CBdatWrapper &wrapper) { s_members[ChrEnArrangeName] = Bdat::getMember(wrapper.data, "Name"); }

u32 getChrEnArrangeName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeName] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnArrangeName], id, 2).valueU16;
}

void initChrEnArrangeDebug_Name(const CBdatWrapper &wrapper) { s_members[ChrEnArrangeDebug_Name] = Bdat::getMember(wrapper.data, "Debug_Name"); }

const char *getChrEnArrangeDebug_Name(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeDebug_Name] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[ChrEnArrangeDebug_Name], id, 7).valueString;
}

void initChrEnArrangeLv(const CBdatWrapper &wrapper) { s_members[ChrEnArrangeLv] = Bdat::getMember(wrapper.data, "Lv"); }

u32 getChrEnArrangeLv(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeLv] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnArrangeLv], id, 1).valueU8;
}

void initChrEnArrangeLvRand(const CBdatWrapper &wrapper) { s_members[ChrEnArrangeLvRand] = Bdat::getMember(wrapper.data, "LvRand"); }

u32 getChrEnArrangeLvRand(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeLvRand] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnArrangeLvRand], id, 1).valueU8;
}

void initChrEnArrangeHpOver(const CBdatWrapper &wrapper) { s_members[ChrEnArrangeHpOver] = Bdat::getMember(wrapper.data, "HpOver"); }

u32 getChrEnArrangeHpOver(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeHpOver] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnArrangeHpOver], id, 1).valueU8;
}

void initChrEnArrangeExpRev(const CBdatWrapper &wrapper) { s_members[ChrEnArrangeExpRev] = Bdat::getMember(wrapper.data, "ExpRev"); }

u32 getChrEnArrangeExpRev(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeExpRev] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnArrangeExpRev], id, 2).valueU16;
}

void initChrEnArrangeGoldRev(const CBdatWrapper &wrapper) { s_members[ChrEnArrangeGoldRev] = Bdat::getMember(wrapper.data, "GoldRev"); }

u32 getChrEnArrangeGoldRev(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeGoldRev] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnArrangeGoldRev], id, 2).valueU16;
}

void initChrEnArrangeWPRev(const CBdatWrapper &wrapper) { s_members[ChrEnArrangeWPRev] = Bdat::getMember(wrapper.data, "WPRev"); }

u32 getChrEnArrangeWPRev(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeWPRev] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnArrangeWPRev], id, 2).valueU16;
}

void initChrEnArrangeSPRev(const CBdatWrapper &wrapper) { s_members[ChrEnArrangeSPRev] = Bdat::getMember(wrapper.data, "SPRev"); }

u32 getChrEnArrangeSPRev(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeSPRev] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnArrangeSPRev], id, 2).valueU16;
}

void initChrEnArrangeDropTableID(const CBdatWrapper &wrapper) { s_members[ChrEnArrangeDropTableID] = Bdat::getMember(wrapper.data, "DropTableID"); }

u32 getChrEnArrangeDropTableID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeDropTableID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnArrangeDropTableID], id, 2).valueU16;
}

void initChrEnArrangeDropTableID2(const CBdatWrapper &wrapper) {
  s_members[ChrEnArrangeDropTableID2] = Bdat::getMember(wrapper.data, "DropTableID2");
}

u32 getChrEnArrangeDropTableID2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeDropTableID2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnArrangeDropTableID2], id, 2).valueU16;
}

void initChrEnArrangeDropTableID3(const CBdatWrapper &wrapper) {
  s_members[ChrEnArrangeDropTableID3] = Bdat::getMember(wrapper.data, "DropTableID3");
}

u32 getChrEnArrangeDropTableID3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeDropTableID3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnArrangeDropTableID3], id, 2).valueU16;
}

void initChrEnArrangePreciousID(const CBdatWrapper &wrapper) { s_members[ChrEnArrangePreciousID] = Bdat::getMember(wrapper.data, "PreciousID"); }

u32 getChrEnArrangePreciousID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangePreciousID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnArrangePreciousID], id, 2).valueU16;
}

void initChrEnArrangeScale(const CBdatWrapper &wrapper) { s_members[ChrEnArrangeScale] = Bdat::getMember(wrapper.data, "Scale"); }

u32 getChrEnArrangeScale(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeScale] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnArrangeScale], id, 2).valueU16;
}

void initChrEnArrangeChrSize(const CBdatWrapper &wrapper) { s_members[ChrEnArrangeChrSize] = Bdat::getMember(wrapper.data, "ChrSize"); }

u32 getChrEnArrangeChrSize(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeChrSize] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnArrangeChrSize], id, 1).valueU8;
}

void initChrEnArrangeTurnSize(const CBdatWrapper &wrapper) { s_members[ChrEnArrangeTurnSize] = Bdat::getMember(wrapper.data, "TurnSize"); }

u32 getChrEnArrangeTurnSize(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeTurnSize] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnArrangeTurnSize], id, 1).valueU8;
}

void initChrEnArrangeFlagNamed(const CBdatWrapper &wrapper) {
  s_members[ChrEnArrangeFlagNamed] = Bdat::getMember(wrapper.data, "Flag");
  s_members[ChrEnArrangeFlagNamedFlag] = Bdat::getMember(wrapper.data, "Named");
}

bool isChrEnArrangeFlagNamed(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeFlagNamed] == nullptr || s_members[ChrEnArrangeFlagNamedFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[ChrEnArrangeFlagNamed], id, s_members[ChrEnArrangeFlagNamedFlag]) != 0;
}

void initChrEnArrangeFlagmBoss(const CBdatWrapper &wrapper) {
  s_members[ChrEnArrangeFlagmBoss] = Bdat::getMember(wrapper.data, "Flag");
  s_members[ChrEnArrangeFlagmBossFlag] = Bdat::getMember(wrapper.data, "mBoss");
}

bool isChrEnArrangeFlagmBoss(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeFlagmBoss] == nullptr || s_members[ChrEnArrangeFlagmBossFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[ChrEnArrangeFlagmBoss], id, s_members[ChrEnArrangeFlagmBossFlag]) != 0;
}

void initChrEnArrangeFlagChild(const CBdatWrapper &wrapper) {
  s_members[ChrEnArrangeFlagChild] = Bdat::getMember(wrapper.data, "Flag");
  s_members[ChrEnArrangeFlagChildFlag] = Bdat::getMember(wrapper.data, "Child");
}

bool isChrEnArrangeFlagChild(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeFlagChild] == nullptr || s_members[ChrEnArrangeFlagChildFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[ChrEnArrangeFlagChild], id, s_members[ChrEnArrangeFlagChildFlag]) != 0;
}

void initChrEnArrangeFlagFAOff(const CBdatWrapper &wrapper) {
  s_members[ChrEnArrangeFlagFAOff] = Bdat::getMember(wrapper.data, "Flag");
  s_members[ChrEnArrangeFlagFAOffFlag] = Bdat::getMember(wrapper.data, "FAOff");
}

bool isChrEnArrangeFlagFAOff(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeFlagFAOff] == nullptr || s_members[ChrEnArrangeFlagFAOffFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[ChrEnArrangeFlagFAOff], id, s_members[ChrEnArrangeFlagFAOffFlag]) != 0;
}

void initChrEnArrangeFlagNoEcSkip(const CBdatWrapper &wrapper) {
  s_members[ChrEnArrangeFlagNoEcSkip] = Bdat::getMember(wrapper.data, "Flag");
  s_members[ChrEnArrangeFlagNoEcSkipFlag] = Bdat::getMember(wrapper.data, "NoEcSkip");
}

bool isChrEnArrangeFlagNoEcSkip(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeFlagNoEcSkip] == nullptr || s_members[ChrEnArrangeFlagNoEcSkipFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[ChrEnArrangeFlagNoEcSkip], id, s_members[ChrEnArrangeFlagNoEcSkipFlag]) != 0;
}

void initChrEnArrangeFlagLinkType(const CBdatWrapper &wrapper) {
  s_members[ChrEnArrangeFlagLinkType] = Bdat::getMember(wrapper.data, "Flag");
  s_members[ChrEnArrangeFlagLinkTypeFlag] = Bdat::getMember(wrapper.data, "LinkType");
}

bool isChrEnArrangeFlagLinkType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeFlagLinkType] == nullptr || s_members[ChrEnArrangeFlagLinkTypeFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[ChrEnArrangeFlagLinkType], id, s_members[ChrEnArrangeFlagLinkTypeFlag]) != 0;
}

void initChrEnArrangeFlagChrColiOff(const CBdatWrapper &wrapper) {
  s_members[ChrEnArrangeFlagChrColiOff] = Bdat::getMember(wrapper.data, "Flag");
  s_members[ChrEnArrangeFlagChrColiOffFlag] = Bdat::getMember(wrapper.data, "ChrColiOff");
}

bool isChrEnArrangeFlagChrColiOff(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeFlagChrColiOff] == nullptr || s_members[ChrEnArrangeFlagChrColiOffFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[ChrEnArrangeFlagChrColiOff], id, s_members[ChrEnArrangeFlagChrColiOffFlag]) != 0;
}

void initChrEnArrangeFlagNoTarget(const CBdatWrapper &wrapper) {
  s_members[ChrEnArrangeFlagNoTarget] = Bdat::getMember(wrapper.data, "Flag");
  s_members[ChrEnArrangeFlagNoTargetFlag] = Bdat::getMember(wrapper.data, "NoTarget");
}

bool isChrEnArrangeFlagNoTarget(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeFlagNoTarget] == nullptr || s_members[ChrEnArrangeFlagNoTargetFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[ChrEnArrangeFlagNoTarget], id, s_members[ChrEnArrangeFlagNoTargetFlag]) != 0;
}

void initChrEnArrangeFlagHikariSP4(const CBdatWrapper &wrapper) {
  s_members[ChrEnArrangeFlagHikariSP4] = Bdat::getMember(wrapper.data, "Flag");
  s_members[ChrEnArrangeFlagHikariSP4Flag] = Bdat::getMember(wrapper.data, "HikariSP4");
}

bool isChrEnArrangeFlagHikariSP4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeFlagHikariSP4] == nullptr || s_members[ChrEnArrangeFlagHikariSP4Flag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[ChrEnArrangeFlagHikariSP4], id, s_members[ChrEnArrangeFlagHikariSP4Flag]) != 0;
}

void initChrEnArrangeFlagHomuri(const CBdatWrapper &wrapper) {
  s_members[ChrEnArrangeFlagHomuri] = Bdat::getMember(wrapper.data, "Flag");
  s_members[ChrEnArrangeFlagHomuriFlag] = Bdat::getMember(wrapper.data, "Homuri");
}

bool isChrEnArrangeFlagHomuri(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeFlagHomuri] == nullptr || s_members[ChrEnArrangeFlagHomuriFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[ChrEnArrangeFlagHomuri], id, s_members[ChrEnArrangeFlagHomuriFlag]) != 0;
}

void initChrEnArrangeFlagHikari(const CBdatWrapper &wrapper) {
  s_members[ChrEnArrangeFlagHikari] = Bdat::getMember(wrapper.data, "Flag");
  s_members[ChrEnArrangeFlagHikariFlag] = Bdat::getMember(wrapper.data, "Hikari");
}

bool isChrEnArrangeFlagHikari(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeFlagHikari] == nullptr || s_members[ChrEnArrangeFlagHikariFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[ChrEnArrangeFlagHikari], id, s_members[ChrEnArrangeFlagHikariFlag]) != 0;
}

void initChrEnArrangeFlagNoNaviMesh(const CBdatWrapper &wrapper) {
  s_members[ChrEnArrangeFlagNoNaviMesh] = Bdat::getMember(wrapper.data, "Flag");
  s_members[ChrEnArrangeFlagNoNaviMeshFlag] = Bdat::getMember(wrapper.data, "NoNaviMesh");
}

bool isChrEnArrangeFlagNoNaviMesh(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeFlagNoNaviMesh] == nullptr || s_members[ChrEnArrangeFlagNoNaviMeshFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[ChrEnArrangeFlagNoNaviMesh], id, s_members[ChrEnArrangeFlagNoNaviMeshFlag]) != 0;
}

void initChrEnArrangeFlagFixed(const CBdatWrapper &wrapper) {
  s_members[ChrEnArrangeFlagFixed] = Bdat::getMember(wrapper.data, "Flag");
  s_members[ChrEnArrangeFlagFixedFlag] = Bdat::getMember(wrapper.data, "Fixed");
}

bool isChrEnArrangeFlagFixed(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeFlagFixed] == nullptr || s_members[ChrEnArrangeFlagFixedFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[ChrEnArrangeFlagFixed], id, s_members[ChrEnArrangeFlagFixedFlag]) != 0;
}

void initChrEnArrangeFlagDropFront(const CBdatWrapper &wrapper) {
  s_members[ChrEnArrangeFlagDropFront] = Bdat::getMember(wrapper.data, "Flag");
  s_members[ChrEnArrangeFlagDropFrontFlag] = Bdat::getMember(wrapper.data, "DropFront");
}

bool isChrEnArrangeFlagDropFront(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeFlagDropFront] == nullptr || s_members[ChrEnArrangeFlagDropFrontFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[ChrEnArrangeFlagDropFront], id, s_members[ChrEnArrangeFlagDropFrontFlag]) != 0;
}

void initChrEnArrangeFlagNoWarp(const CBdatWrapper &wrapper) {
  s_members[ChrEnArrangeFlagNoWarp] = Bdat::getMember(wrapper.data, "Flag");
  s_members[ChrEnArrangeFlagNoWarpFlag] = Bdat::getMember(wrapper.data, "NoWarp");
}

bool isChrEnArrangeFlagNoWarp(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeFlagNoWarp] == nullptr || s_members[ChrEnArrangeFlagNoWarpFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[ChrEnArrangeFlagNoWarp], id, s_members[ChrEnArrangeFlagNoWarpFlag]) != 0;
}

void initChrEnArrangeFlagIgnoreLevPow(const CBdatWrapper &wrapper) {
  s_members[ChrEnArrangeFlagIgnoreLevPow] = Bdat::getMember(wrapper.data, "Flag");
  s_members[ChrEnArrangeFlagIgnoreLevPowFlag] = Bdat::getMember(wrapper.data, "IgnoreLevPow");
}

bool isChrEnArrangeFlagIgnoreLevPow(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeFlagIgnoreLevPow] == nullptr || s_members[ChrEnArrangeFlagIgnoreLevPowFlag] == nullptr ||
      id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[ChrEnArrangeFlagIgnoreLevPow], id, s_members[ChrEnArrangeFlagIgnoreLevPowFlag]) != 0;
}

void initChrEnArrangeFlagAlwaysAttack(const CBdatWrapper &wrapper) {
  s_members[ChrEnArrangeFlagAlwaysAttack] = Bdat::getMember(wrapper.data, "Flag");
  s_members[ChrEnArrangeFlagAlwaysAttackFlag] = Bdat::getMember(wrapper.data, "AlwaysAttack");
}

bool isChrEnArrangeFlagAlwaysAttack(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeFlagAlwaysAttack] == nullptr || s_members[ChrEnArrangeFlagAlwaysAttackFlag] == nullptr ||
      id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[ChrEnArrangeFlagAlwaysAttack], id, s_members[ChrEnArrangeFlagAlwaysAttackFlag]) != 0;
}

void initChrEnArrangeFlagPGMax(const CBdatWrapper &wrapper) {
  s_members[ChrEnArrangeFlagPGMax] = Bdat::getMember(wrapper.data, "Flag");
  s_members[ChrEnArrangeFlagPGMaxFlag] = Bdat::getMember(wrapper.data, "PGMax");
}

bool isChrEnArrangeFlagPGMax(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeFlagPGMax] == nullptr || s_members[ChrEnArrangeFlagPGMaxFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[ChrEnArrangeFlagPGMax], id, s_members[ChrEnArrangeFlagPGMaxFlag]) != 0;
}

void initChrEnArrangeFlagSalvage(const CBdatWrapper &wrapper) {
  s_members[ChrEnArrangeFlagSalvage] = Bdat::getMember(wrapper.data, "Flag");
  s_members[ChrEnArrangeFlagSalvageFlag] = Bdat::getMember(wrapper.data, "Salvage");
}

bool isChrEnArrangeFlagSalvage(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeFlagSalvage] == nullptr || s_members[ChrEnArrangeFlagSalvageFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[ChrEnArrangeFlagSalvage], id, s_members[ChrEnArrangeFlagSalvageFlag]) != 0;
}

void initChrEnArrangeLinkRadius(const CBdatWrapper &wrapper) { s_members[ChrEnArrangeLinkRadius] = Bdat::getMember(wrapper.data, "LinkRadius"); }

u32 getChrEnArrangeLinkRadius(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeLinkRadius] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnArrangeLinkRadius], id, 1).valueU8;
}

void initChrEnArrangeDetects(const CBdatWrapper &wrapper) { s_members[ChrEnArrangeDetects] = Bdat::getMember(wrapper.data, "Detects"); }

u32 getChrEnArrangeDetects(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeDetects] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnArrangeDetects], id, 1).valueU8;
}

void initChrEnArrangeSearchRange(const CBdatWrapper &wrapper) { s_members[ChrEnArrangeSearchRange] = Bdat::getMember(wrapper.data, "SearchRange"); }

u32 getChrEnArrangeSearchRange(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeSearchRange] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnArrangeSearchRange], id, 2).valueU16;
}

void initChrEnArrangeSearchAngle(const CBdatWrapper &wrapper) { s_members[ChrEnArrangeSearchAngle] = Bdat::getMember(wrapper.data, "SearchAngle"); }

u32 getChrEnArrangeSearchAngle(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeSearchAngle] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnArrangeSearchAngle], id, 2).valueU16;
}

void initChrEnArrangeSearchRadius(const CBdatWrapper &wrapper) {
  s_members[ChrEnArrangeSearchRadius] = Bdat::getMember(wrapper.data, "SearchRadius");
}

u32 getChrEnArrangeSearchRadius(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeSearchRadius] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnArrangeSearchRadius], id, 1).valueU8;
}

void initChrEnArrangeBatInterval(const CBdatWrapper &wrapper) { s_members[ChrEnArrangeBatInterval] = Bdat::getMember(wrapper.data, "BatInterval"); }

u32 getChrEnArrangeBatInterval(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeBatInterval] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnArrangeBatInterval], id, 1).valueU8;
}

void initChrEnArrangeBatArea(const CBdatWrapper &wrapper) { s_members[ChrEnArrangeBatArea] = Bdat::getMember(wrapper.data, "BatArea"); }

u32 getChrEnArrangeBatArea(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeBatArea] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnArrangeBatArea], id, 1).valueU8;
}

void initChrEnArrangeBatAreaType(const CBdatWrapper &wrapper) { s_members[ChrEnArrangeBatAreaType] = Bdat::getMember(wrapper.data, "BatAreaType"); }

u32 getChrEnArrangeBatAreaType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeBatAreaType] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnArrangeBatAreaType], id, 1).valueU8;
}

void initChrEnArrangeAiGroup(const CBdatWrapper &wrapper) { s_members[ChrEnArrangeAiGroup] = Bdat::getMember(wrapper.data, "AiGroup"); }

u32 getChrEnArrangeAiGroup(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeAiGroup] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnArrangeAiGroup], id, 1).valueU8;
}

void initChrEnArrangeAiGroupNum(const CBdatWrapper &wrapper) { s_members[ChrEnArrangeAiGroupNum] = Bdat::getMember(wrapper.data, "AiGroupNum"); }

u32 getChrEnArrangeAiGroupNum(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeAiGroupNum] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnArrangeAiGroupNum], id, 1).valueU8;
}

void initChrEnArrangeBookID(const CBdatWrapper &wrapper) { s_members[ChrEnArrangeBookID] = Bdat::getMember(wrapper.data, "BookID"); }

u32 getChrEnArrangeBookID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeBookID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnArrangeBookID], id, 2).valueU16;
}

void initChrEnArrangeEnhanceID1(const CBdatWrapper &wrapper) { s_members[ChrEnArrangeEnhanceID1] = Bdat::getMember(wrapper.data, "EnhanceID1"); }

u32 getChrEnArrangeEnhanceID1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeEnhanceID1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnArrangeEnhanceID1], id, 2).valueU16;
}

void initChrEnArrangeEnhanceID2(const CBdatWrapper &wrapper) { s_members[ChrEnArrangeEnhanceID2] = Bdat::getMember(wrapper.data, "EnhanceID2"); }

u32 getChrEnArrangeEnhanceID2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeEnhanceID2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnArrangeEnhanceID2], id, 2).valueU16;
}

void initChrEnArrangeEnhanceID3(const CBdatWrapper &wrapper) { s_members[ChrEnArrangeEnhanceID3] = Bdat::getMember(wrapper.data, "EnhanceID3"); }

u32 getChrEnArrangeEnhanceID3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeEnhanceID3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnArrangeEnhanceID3], id, 2).valueU16;
}

void initChrEnArrangeParamRev(const CBdatWrapper &wrapper) { s_members[ChrEnArrangeParamRev] = Bdat::getMember(wrapper.data, "ParamRev"); }

u32 getChrEnArrangeParamRev(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeParamRev] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnArrangeParamRev], id, 2).valueU16;
}

void initChrEnArrangeRstDebuffRev(const CBdatWrapper &wrapper) {
  s_members[ChrEnArrangeRstDebuffRev] = Bdat::getMember(wrapper.data, "RstDebuffRev");
}

u32 getChrEnArrangeRstDebuffRev(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeRstDebuffRev] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnArrangeRstDebuffRev], id, 2).valueU16;
}

void initChrEnArrangeHealPotTypeRev(const CBdatWrapper &wrapper) {
  s_members[ChrEnArrangeHealPotTypeRev] = Bdat::getMember(wrapper.data, "HealPotTypeRev");
}

u32 getChrEnArrangeHealPotTypeRev(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeHealPotTypeRev] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnArrangeHealPotTypeRev], id, 1).valueU8;
}

void initChrEnArrangeSummonID(const CBdatWrapper &wrapper) { s_members[ChrEnArrangeSummonID] = Bdat::getMember(wrapper.data, "SummonID"); }

u32 getChrEnArrangeSummonID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeSummonID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnArrangeSummonID], id, 2).valueU16;
}

void initChrEnArrangeBGMID(const CBdatWrapper &wrapper) { s_members[ChrEnArrangeBGMID] = Bdat::getMember(wrapper.data, "BGMID"); }

u32 getChrEnArrangeBGMID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeBGMID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnArrangeBGMID], id, 1).valueU8;
}

void initChrEnArrangeSeEnvID(const CBdatWrapper &wrapper) { s_members[ChrEnArrangeSeEnvID] = Bdat::getMember(wrapper.data, "SeEnvID"); }

u32 getChrEnArrangeSeEnvID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeSeEnvID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnArrangeSeEnvID], id, 1).valueU8;
}

void initChrEnArrangeZoneID(const CBdatWrapper &wrapper) { s_members[ChrEnArrangeZoneID] = Bdat::getMember(wrapper.data, "ZoneID"); }

u32 getChrEnArrangeZoneID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeZoneID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnArrangeZoneID], id, 1).valueU8;
}

void initChrEnArrangeTimeSet(const CBdatWrapper &wrapper) { s_members[ChrEnArrangeTimeSet] = Bdat::getMember(wrapper.data, "TimeSet"); }

u32 getChrEnArrangeTimeSet(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeTimeSet] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnArrangeTimeSet], id, 1).valueU8;
}

void initChrEnArrangeWeatherSet(const CBdatWrapper &wrapper) { s_members[ChrEnArrangeWeatherSet] = Bdat::getMember(wrapper.data, "WeatherSet"); }

u32 getChrEnArrangeWeatherSet(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeWeatherSet] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnArrangeWeatherSet], id, 1).valueU8;
}

void initChrEnArrangeDriverLev(const CBdatWrapper &wrapper) { s_members[ChrEnArrangeDriverLev] = Bdat::getMember(wrapper.data, "DriverLev"); }

u32 getChrEnArrangeDriverLev(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnArrangeDriverLev] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnArrangeDriverLev], id, 1).valueU8;
}

void initBTL_EnBookBaseEnemyID(const CBdatWrapper &wrapper) { s_members[BTL_EnBookBaseEnemyID] = Bdat::getMember(wrapper.data, "BaseEnemyID"); }

u32 getBTL_EnBookBaseEnemyID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_EnBookBaseEnemyID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_EnBookBaseEnemyID], id, 2).valueU16;
}

void initBTL_EnBookBOOK_POP_TIME(const CBdatWrapper &wrapper) { s_members[BTL_EnBookBOOK_POP_TIME] = Bdat::getMember(wrapper.data, "BOOK_POP_TIME"); }

u32 getBTL_EnBookBOOK_POP_TIME(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_EnBookBOOK_POP_TIME] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_EnBookBOOK_POP_TIME], id, 3).valueU32;
}

void initBTL_EnBookBOOK_popWeather(const CBdatWrapper &wrapper) {
  s_members[BTL_EnBookBOOK_popWeather] = Bdat::getMember(wrapper.data, "BOOK_popWeather");
}

u32 getBTL_EnBookBOOK_popWeather(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_EnBookBOOK_popWeather] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_EnBookBOOK_popWeather], id, 1).valueU8;
}

} // namespace _gfbcb

enum {
  BDAT_BTL_EN_BOOK = 0x26,
  BDAT_CHR_EN_ARRANGE = 0x79,
};

GfBdatChrEnArrange::GfBdatChrEnArrange() : mChrEnArrange(nullptr), mBTL_EnBook(nullptr) { bdatRefresh(); }

GfBdatChrEnArrange::~GfBdatChrEnArrange() { destroyFP(); }

void GfBdatChrEnArrange::destroyFP() {
  if (mChrEnArrange != nullptr) {
    delete mChrEnArrange;
    mChrEnArrange = nullptr;
  }

  if (mBTL_EnBook != nullptr) {
    delete mBTL_EnBook;
    mBTL_EnBook = nullptr;
  }
}

#define NEW_BDAT_WRAPPER(bdat)                                                                                                                       \
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) CBdatWrapper { GfDataBdat::getFP(bdat) }

void GfBdatChrEnArrange::createFP() {
// The line numbers passed to the allocator decide between mov and orr.
#line 60
  mChrEnArrange = NEW_BDAT_WRAPPER(BDAT_CHR_EN_ARRANGE);
  mBTL_EnBook = NEW_BDAT_WRAPPER(BDAT_BTL_EN_BOOK);
}

void GfBdatChrEnArrange::bdatRefresh() {
  destroyFP();
  createFP();
  _gfbcb::initChrEnArrangeParamID(*mChrEnArrange);
  _gfbcb::initChrEnArrangeEnemyBladeID(*mChrEnArrange);
  _gfbcb::initChrEnArrangeBladeID(*mChrEnArrange);
  _gfbcb::initChrEnArrangeBladeAtr(*mChrEnArrange);
  _gfbcb::initChrEnArrangeExtraParts(*mChrEnArrange);
  _gfbcb::initChrEnArrangeName(*mChrEnArrange);
  _gfbcb::initChrEnArrangeDebug_Name(*mChrEnArrange);
  _gfbcb::initChrEnArrangeLv(*mChrEnArrange);
  _gfbcb::initChrEnArrangeLvRand(*mChrEnArrange);
  _gfbcb::initChrEnArrangeHpOver(*mChrEnArrange);
  _gfbcb::initChrEnArrangeExpRev(*mChrEnArrange);
  _gfbcb::initChrEnArrangeGoldRev(*mChrEnArrange);
  _gfbcb::initChrEnArrangeWPRev(*mChrEnArrange);
  _gfbcb::initChrEnArrangeSPRev(*mChrEnArrange);
  _gfbcb::initChrEnArrangeDropTableID(*mChrEnArrange);
  _gfbcb::initChrEnArrangeDropTableID2(*mChrEnArrange);
  _gfbcb::initChrEnArrangeDropTableID3(*mChrEnArrange);
  _gfbcb::initChrEnArrangePreciousID(*mChrEnArrange);
  _gfbcb::initChrEnArrangeScale(*mChrEnArrange);
  _gfbcb::initChrEnArrangeChrSize(*mChrEnArrange);
  _gfbcb::initChrEnArrangeTurnSize(*mChrEnArrange);
  _gfbcb::initChrEnArrangeFlagNamed(*mChrEnArrange);
  _gfbcb::initChrEnArrangeFlagmBoss(*mChrEnArrange);
  _gfbcb::initChrEnArrangeFlagChild(*mChrEnArrange);
  _gfbcb::initChrEnArrangeFlagFAOff(*mChrEnArrange);
  _gfbcb::initChrEnArrangeFlagNoEcSkip(*mChrEnArrange);
  _gfbcb::initChrEnArrangeFlagLinkType(*mChrEnArrange);
  _gfbcb::initChrEnArrangeFlagChrColiOff(*mChrEnArrange);
  _gfbcb::initChrEnArrangeFlagNoTarget(*mChrEnArrange);
  _gfbcb::initChrEnArrangeFlagHikariSP4(*mChrEnArrange);
  _gfbcb::initChrEnArrangeFlagHomuri(*mChrEnArrange);
  _gfbcb::initChrEnArrangeFlagHikari(*mChrEnArrange);
  _gfbcb::initChrEnArrangeFlagNoNaviMesh(*mChrEnArrange);
  _gfbcb::initChrEnArrangeFlagFixed(*mChrEnArrange);
  _gfbcb::initChrEnArrangeFlagDropFront(*mChrEnArrange);
  _gfbcb::initChrEnArrangeFlagNoWarp(*mChrEnArrange);
  _gfbcb::initChrEnArrangeFlagIgnoreLevPow(*mChrEnArrange);
  _gfbcb::initChrEnArrangeFlagAlwaysAttack(*mChrEnArrange);
  _gfbcb::initChrEnArrangeFlagPGMax(*mChrEnArrange);
  _gfbcb::initChrEnArrangeFlagSalvage(*mChrEnArrange);
  _gfbcb::initChrEnArrangeLinkRadius(*mChrEnArrange);
  _gfbcb::initChrEnArrangeDetects(*mChrEnArrange);
  _gfbcb::initChrEnArrangeSearchRange(*mChrEnArrange);
  _gfbcb::initChrEnArrangeSearchAngle(*mChrEnArrange);
  _gfbcb::initChrEnArrangeSearchRadius(*mChrEnArrange);
  _gfbcb::initChrEnArrangeBatInterval(*mChrEnArrange);
  _gfbcb::initChrEnArrangeBatArea(*mChrEnArrange);
  _gfbcb::initChrEnArrangeBatAreaType(*mChrEnArrange);
  _gfbcb::initChrEnArrangeAiGroup(*mChrEnArrange);
  _gfbcb::initChrEnArrangeAiGroupNum(*mChrEnArrange);
  _gfbcb::initChrEnArrangeBookID(*mChrEnArrange);
  _gfbcb::initChrEnArrangeEnhanceID1(*mChrEnArrange);
  _gfbcb::initChrEnArrangeEnhanceID2(*mChrEnArrange);
  _gfbcb::initChrEnArrangeEnhanceID3(*mChrEnArrange);
  _gfbcb::initChrEnArrangeParamRev(*mChrEnArrange);
  _gfbcb::initChrEnArrangeRstDebuffRev(*mChrEnArrange);
  _gfbcb::initChrEnArrangeHealPotTypeRev(*mChrEnArrange);
  _gfbcb::initChrEnArrangeSummonID(*mChrEnArrange);
  _gfbcb::initChrEnArrangeBGMID(*mChrEnArrange);
  _gfbcb::initChrEnArrangeSeEnvID(*mChrEnArrange);
  _gfbcb::initChrEnArrangeZoneID(*mChrEnArrange);
  _gfbcb::initChrEnArrangeTimeSet(*mChrEnArrange);
  _gfbcb::initChrEnArrangeWeatherSet(*mChrEnArrange);
  _gfbcb::initChrEnArrangeDriverLev(*mChrEnArrange);
  _gfbcb::initBTL_EnBookBaseEnemyID(*mBTL_EnBook);
  _gfbcb::initBTL_EnBookBOOK_POP_TIME(*mBTL_EnBook);
  _gfbcb::initBTL_EnBookBOOK_popWeather(*mBTL_EnBook);
}

u32 GfBdatChrEnArrange::getChrEnArrangeStart() const { return Bdat::getIdTop(mChrEnArrange->data); }

u32 GfBdatChrEnArrange::getChrEnArrangeEnd() const { return Bdat::getIdTop(mChrEnArrange->data) + Bdat::getIdCount(mChrEnArrange->data); }

u32 GfBdatChrEnArrange::getChrEnArrangeParamID(u32 id) const { return _gfbcb::getChrEnArrangeParamID(*mChrEnArrange, id); }

u32 GfBdatChrEnArrange::getChrEnArrangeEnemyBladeID(u32 id) const { return _gfbcb::getChrEnArrangeEnemyBladeID(*mChrEnArrange, id); }

u32 GfBdatChrEnArrange::getChrEnArrangeBladeID(u32 id) const { return _gfbcb::getChrEnArrangeBladeID(*mChrEnArrange, id); }

u32 GfBdatChrEnArrange::getChrEnArrangeBladeAtr(u32 id) const { return _gfbcb::getChrEnArrangeBladeAtr(*mChrEnArrange, id); }

u32 GfBdatChrEnArrange::getChrEnArrangeExtraParts(u32 id) const { return _gfbcb::getChrEnArrangeExtraParts(*mChrEnArrange, id); }

u32 GfBdatChrEnArrange::getChrEnArrangeName(u32 id) const { return _gfbcb::getChrEnArrangeName(*mChrEnArrange, id); }

const char *GfBdatChrEnArrange::getChrEnArrangeDebug_Name(u32 id) const { return _gfbcb::getChrEnArrangeDebug_Name(*mChrEnArrange, id); }

u32 GfBdatChrEnArrange::getChrEnArrangeLv(u32 id) const { return _gfbcb::getChrEnArrangeLv(*mChrEnArrange, id); }

u32 GfBdatChrEnArrange::getChrEnArrangeLvRand(u32 id) const { return _gfbcb::getChrEnArrangeLvRand(*mChrEnArrange, id); }

u32 GfBdatChrEnArrange::getChrEnArrangeHpOver(u32 id) const { return _gfbcb::getChrEnArrangeHpOver(*mChrEnArrange, id); }

u32 GfBdatChrEnArrange::getChrEnArrangeExpRev(u32 id) const { return _gfbcb::getChrEnArrangeExpRev(*mChrEnArrange, id); }

u32 GfBdatChrEnArrange::getChrEnArrangeGoldRev(u32 id) const { return _gfbcb::getChrEnArrangeGoldRev(*mChrEnArrange, id); }

u32 GfBdatChrEnArrange::getChrEnArrangeWPRev(u32 id) const { return _gfbcb::getChrEnArrangeWPRev(*mChrEnArrange, id); }

u32 GfBdatChrEnArrange::getChrEnArrangeSPRev(u32 id) const { return _gfbcb::getChrEnArrangeSPRev(*mChrEnArrange, id); }

u32 GfBdatChrEnArrange::getChrEnArrangeDropTableID(u32 id) const { return _gfbcb::getChrEnArrangeDropTableID(*mChrEnArrange, id); }

u32 GfBdatChrEnArrange::getChrEnArrangeDropTableID2(u32 id) const { return _gfbcb::getChrEnArrangeDropTableID2(*mChrEnArrange, id); }

u32 GfBdatChrEnArrange::getChrEnArrangeDropTableID3(u32 id) const { return _gfbcb::getChrEnArrangeDropTableID3(*mChrEnArrange, id); }

u32 GfBdatChrEnArrange::getChrEnArrangePreciousID(u32 id) const { return _gfbcb::getChrEnArrangePreciousID(*mChrEnArrange, id); }

u32 GfBdatChrEnArrange::getChrEnArrangeScale(u32 id) const { return _gfbcb::getChrEnArrangeScale(*mChrEnArrange, id); }

u32 GfBdatChrEnArrange::getChrEnArrangeChrSize(u32 id) const { return _gfbcb::getChrEnArrangeChrSize(*mChrEnArrange, id); }

u32 GfBdatChrEnArrange::getChrEnArrangeTurnSize(u32 id) const { return _gfbcb::getChrEnArrangeTurnSize(*mChrEnArrange, id); }

bool GfBdatChrEnArrange::isChrEnArrangeFlagNamed(u32 id) const { return _gfbcb::isChrEnArrangeFlagNamed(*mChrEnArrange, id); }

bool GfBdatChrEnArrange::isChrEnArrangeFlagmBoss(u32 id) const { return _gfbcb::isChrEnArrangeFlagmBoss(*mChrEnArrange, id); }

bool GfBdatChrEnArrange::isChrEnArrangeFlagChild(u32 id) const { return _gfbcb::isChrEnArrangeFlagChild(*mChrEnArrange, id); }

bool GfBdatChrEnArrange::isChrEnArrangeFlagFAOff(u32 id) const { return _gfbcb::isChrEnArrangeFlagFAOff(*mChrEnArrange, id); }

bool GfBdatChrEnArrange::isChrEnArrangeFlagNoEcSkip(u32 id) const { return _gfbcb::isChrEnArrangeFlagNoEcSkip(*mChrEnArrange, id); }

bool GfBdatChrEnArrange::isChrEnArrangeFlagLinkType(u32 id) const { return _gfbcb::isChrEnArrangeFlagLinkType(*mChrEnArrange, id); }

bool GfBdatChrEnArrange::isChrEnArrangeFlagChrColiOff(u32 id) const { return _gfbcb::isChrEnArrangeFlagChrColiOff(*mChrEnArrange, id); }

bool GfBdatChrEnArrange::isChrEnArrangeFlagNoTarget(u32 id) const { return _gfbcb::isChrEnArrangeFlagNoTarget(*mChrEnArrange, id); }

bool GfBdatChrEnArrange::isChrEnArrangeFlagHikariSP4(u32 id) const { return _gfbcb::isChrEnArrangeFlagHikariSP4(*mChrEnArrange, id); }

bool GfBdatChrEnArrange::isChrEnArrangeFlagHomuri(u32 id) const { return _gfbcb::isChrEnArrangeFlagHomuri(*mChrEnArrange, id); }

bool GfBdatChrEnArrange::isChrEnArrangeFlagHikari(u32 id) const { return _gfbcb::isChrEnArrangeFlagHikari(*mChrEnArrange, id); }

bool GfBdatChrEnArrange::isChrEnArrangeFlagNoNaviMesh(u32 id) const { return _gfbcb::isChrEnArrangeFlagNoNaviMesh(*mChrEnArrange, id); }

bool GfBdatChrEnArrange::isChrEnArrangeFlagFixed(u32 id) const { return _gfbcb::isChrEnArrangeFlagFixed(*mChrEnArrange, id); }

bool GfBdatChrEnArrange::isChrEnArrangeFlagDropFront(u32 id) const { return _gfbcb::isChrEnArrangeFlagDropFront(*mChrEnArrange, id); }

bool GfBdatChrEnArrange::isChrEnArrangeFlagNoWarp(u32 id) const { return _gfbcb::isChrEnArrangeFlagNoWarp(*mChrEnArrange, id); }

bool GfBdatChrEnArrange::isChrEnArrangeFlagIgnoreLevPow(u32 id) const { return _gfbcb::isChrEnArrangeFlagIgnoreLevPow(*mChrEnArrange, id); }

bool GfBdatChrEnArrange::isChrEnArrangeFlagAlwaysAttack(u32 id) const { return _gfbcb::isChrEnArrangeFlagAlwaysAttack(*mChrEnArrange, id); }

bool GfBdatChrEnArrange::isChrEnArrangeFlagPGMax(u32 id) const { return _gfbcb::isChrEnArrangeFlagPGMax(*mChrEnArrange, id); }

bool GfBdatChrEnArrange::isChrEnArrangeFlagSalvage(u32 id) const { return _gfbcb::isChrEnArrangeFlagSalvage(*mChrEnArrange, id); }

u32 GfBdatChrEnArrange::getChrEnArrangeLinkRadius(u32 id) const { return _gfbcb::getChrEnArrangeLinkRadius(*mChrEnArrange, id); }

u32 GfBdatChrEnArrange::getChrEnArrangeDetects(u32 id) const { return _gfbcb::getChrEnArrangeDetects(*mChrEnArrange, id); }

u32 GfBdatChrEnArrange::getChrEnArrangeSearchRange(u32 id) const { return _gfbcb::getChrEnArrangeSearchRange(*mChrEnArrange, id); }

u32 GfBdatChrEnArrange::getChrEnArrangeSearchAngle(u32 id) const { return _gfbcb::getChrEnArrangeSearchAngle(*mChrEnArrange, id); }

u32 GfBdatChrEnArrange::getChrEnArrangeSearchRadius(u32 id) const { return _gfbcb::getChrEnArrangeSearchRadius(*mChrEnArrange, id); }

u32 GfBdatChrEnArrange::getChrEnArrangeBatInterval(u32 id) const { return _gfbcb::getChrEnArrangeBatInterval(*mChrEnArrange, id); }

u32 GfBdatChrEnArrange::getChrEnArrangeBatArea(u32 id) const { return _gfbcb::getChrEnArrangeBatArea(*mChrEnArrange, id); }

u32 GfBdatChrEnArrange::getChrEnArrangeBatAreaType(u32 id) const { return _gfbcb::getChrEnArrangeBatAreaType(*mChrEnArrange, id); }

u32 GfBdatChrEnArrange::getChrEnArrangeAiGroup(u32 id) const { return _gfbcb::getChrEnArrangeAiGroup(*mChrEnArrange, id); }

u32 GfBdatChrEnArrange::getChrEnArrangeAiGroupNum(u32 id) const { return _gfbcb::getChrEnArrangeAiGroupNum(*mChrEnArrange, id); }

u32 GfBdatChrEnArrange::getChrEnArrangeBookID(u32 id) const { return _gfbcb::getChrEnArrangeBookID(*mChrEnArrange, id); }

u32 GfBdatChrEnArrange::getChrEnArrangeEnhanceID1(u32 id) const { return _gfbcb::getChrEnArrangeEnhanceID1(*mChrEnArrange, id); }

u32 GfBdatChrEnArrange::getChrEnArrangeEnhanceID2(u32 id) const { return _gfbcb::getChrEnArrangeEnhanceID2(*mChrEnArrange, id); }

u32 GfBdatChrEnArrange::getChrEnArrangeEnhanceID3(u32 id) const { return _gfbcb::getChrEnArrangeEnhanceID3(*mChrEnArrange, id); }

u32 GfBdatChrEnArrange::getChrEnArrangeParamRev(u32 id) const { return _gfbcb::getChrEnArrangeParamRev(*mChrEnArrange, id); }

u32 GfBdatChrEnArrange::getChrEnArrangeRstDebuffRev(u32 id) const { return _gfbcb::getChrEnArrangeRstDebuffRev(*mChrEnArrange, id); }

u32 GfBdatChrEnArrange::getChrEnArrangeHealPotTypeRev(u32 id) const { return _gfbcb::getChrEnArrangeHealPotTypeRev(*mChrEnArrange, id); }

u32 GfBdatChrEnArrange::getChrEnArrangeSummonID(u32 id) const { return _gfbcb::getChrEnArrangeSummonID(*mChrEnArrange, id); }

u32 GfBdatChrEnArrange::getChrEnArrangeBGMID(u32 id) const { return _gfbcb::getChrEnArrangeBGMID(*mChrEnArrange, id); }

u32 GfBdatChrEnArrange::getChrEnArrangeSeEnvID(u32 id) const { return _gfbcb::getChrEnArrangeSeEnvID(*mChrEnArrange, id); }

u32 GfBdatChrEnArrange::getChrEnArrangeZoneID(u32 id) const { return _gfbcb::getChrEnArrangeZoneID(*mChrEnArrange, id); }

u32 GfBdatChrEnArrange::getChrEnArrangeTimeSet(u32 id) const { return _gfbcb::getChrEnArrangeTimeSet(*mChrEnArrange, id); }

u32 GfBdatChrEnArrange::getChrEnArrangeWeatherSet(u32 id) const { return _gfbcb::getChrEnArrangeWeatherSet(*mChrEnArrange, id); }

u32 GfBdatChrEnArrange::getChrEnArrangeDriverLev(u32 id) const { return _gfbcb::getChrEnArrangeDriverLev(*mChrEnArrange, id); }

u32 GfBdatChrEnArrange::getBTL_EnBookStart() const { return Bdat::getIdTop(mBTL_EnBook->data); }

u32 GfBdatChrEnArrange::getBTL_EnBookEnd() const { return Bdat::getIdTop(mBTL_EnBook->data) + Bdat::getIdCount(mBTL_EnBook->data); }

u32 GfBdatChrEnArrange::getBTL_EnBookBaseEnemyID(u32 id) const { return _gfbcb::getBTL_EnBookBaseEnemyID(*mBTL_EnBook, id); }

u32 GfBdatChrEnArrange::getBTL_EnBookBOOK_POP_TIME(u32 id) const { return _gfbcb::getBTL_EnBookBOOK_POP_TIME(*mBTL_EnBook, id); }

u32 GfBdatChrEnArrange::getBTL_EnBookBOOK_popWeather(u32 id) const { return _gfbcb::getBTL_EnBookBOOK_popWeather(*mBTL_EnBook, id); }

bool GfBdatChrEnArrange::searchByEnParamId(mm::mtl::FixedVector<u16, 128> &arranges, u32 paramId) const {
  for (u32 id = getChrEnArrangeStart(), end = getChrEnArrangeEnd(); id < end; id++) {
    if (getChrEnArrangeParamID(id) == paramId) {
      arranges.push_back(id);
    }
  }

  return !arranges.empty();
}

} // namespace gf
