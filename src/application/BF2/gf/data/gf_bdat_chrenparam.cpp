#include "gf/data/gf_bdat_chrenparam.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/gf_allocator.h"
#include "mm_mtl/fixed_vector.h"

namespace gf {
namespace _gfbep {

enum {
  ChrEnParamDebug_Name,
  ChrEnParamResourceID,
  ChrEnParamAiID,
  ChrEnParamEnemyRole,
  ChrEnParamWalkSpeed,
  ChrEnParamRunSpeed,
  ChrEnParamBtlSpeed,
  ChrEnParamHpDefault,
  ChrEnParamHpLimit,
  ChrEnParamScoutStartHp,
  ChrEnParamScoutEndHp,
  ChrEnParamHpMaxRev,
  ChrEnParamStrengthRev,
  ChrEnParamPowEtherRev,
  ChrEnParamDexRev,
  ChrEnParamAgilityRev,
  ChrEnParamLuckRev,
  ChrEnParamParmor,
  ChrEnParamEarmor,
  ChrEnParamRstPower,
  ChrEnParamRstEther,
  ChrEnParamAtr,
  ChrEnParamCriticalRate,
  ChrEnParamGuardRate,
  ChrEnParamFlagGrdDirFront,
  ChrEnParamFlagGrdDirFrontFlag,
  ChrEnParamFlagGrdDirLeft,
  ChrEnParamFlagGrdDirLeftFlag,
  ChrEnParamFlagGrdDirRight,
  ChrEnParamFlagGrdDirRightFlag,
  ChrEnParamFlagGrdDirBack,
  ChrEnParamFlagGrdDirBackFlag,
  ChrEnParamFlagFldDmgType,
  ChrEnParamFlagFldDmgTypeFlag,
  ChrEnParamHealPotDrop,
  ChrEnParamRstFiCombo,
  ChrEnParamIvdFiCombo,
  ChrEnParamAura,
  ChrEnParamDyingHP,
  ChrEnParamWTNormal,
  ChrEnParamWTDying,
  ChrEnParamHate0Target,
  ChrEnParamDeathArts,
  ChrEnParamDeathArtsStop,
  ChrEnParamArtsNum1,
  ChrEnParamArtsNum2,
  ChrEnParamArtsNum3,
  ChrEnParamArtsNum4,
  ChrEnParamArtsNum5,
  ChrEnParamArtsNum6,
  ChrEnParamArtsNum7,
  ChrEnParamArtsNum8,
  ChrEnParamArtsNum9,
  ChrEnParamArtsNum10,
  ChrEnParamArtsNum11,
  ChrEnParamArtsNum12,
  ChrEnParamArtsNum13,
  ChrEnParamArtsNum14,
  ChrEnParamArtsNum15,
  ChrEnParamArtsNum16,
  ChrEnParamTableHpMaxBase,
  ChrEnParamTableStrengthBase,
  ChrEnParamTablePowEtherBase,
  ChrEnParamTableDexBase,
  ChrEnParamTableAgilityBase,
  ChrEnParamTableLuckBase,
  ChrEnParamRevHpMaxRev,
  ChrEnParamRevStrengthRev,
  ChrEnParamRevPowEtherRev,
  ChrEnParamRevDexRev,
  ChrEnParamRevAgilityRev,
  ChrEnParamRevLuckRev,
  ChrEnRstDebuffRevRevType,
  ChrEnRstDebuffRevRstFiCombo,
  ChrEnRstDebuffRevIvdFiCombo,
  EnemyGroupEnemyID1,
  EnemyGroupEnemyID2,
  EnemyGroupEnemyID3,
  EnemyGroupEnemyID4,
  EnemyGroupEnemyID5,
  EnemyGroupEnemyID6,
  EnemyGroupEnemyID7,
  EnemyGroupEnemyID8,
  MEMBER_COUNT,
};

static u8 *s_members[MEMBER_COUNT];

void initChrEnParamDebug_Name(const CBdatWrapper &wrapper) { s_members[ChrEnParamDebug_Name] = Bdat::getMember(wrapper.data, "Debug_Name"); }

const char *getChrEnParamDebug_Name(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamDebug_Name] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[ChrEnParamDebug_Name], id, 7).valueString;
}

void initChrEnParamResourceID(const CBdatWrapper &wrapper) { s_members[ChrEnParamResourceID] = Bdat::getMember(wrapper.data, "ResourceID"); }

u32 getChrEnParamResourceID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamResourceID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamResourceID], id, 2).valueU16;
}

void initChrEnParamAiID(const CBdatWrapper &wrapper) { s_members[ChrEnParamAiID] = Bdat::getMember(wrapper.data, "AiID"); }

u32 getChrEnParamAiID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamAiID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamAiID], id, 2).valueU16;
}

void initChrEnParamEnemyRole(const CBdatWrapper &wrapper) { s_members[ChrEnParamEnemyRole] = Bdat::getMember(wrapper.data, "EnemyRole"); }

u32 getChrEnParamEnemyRole(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamEnemyRole] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamEnemyRole], id, 1).valueU8;
}

void initChrEnParamWalkSpeed(const CBdatWrapper &wrapper) { s_members[ChrEnParamWalkSpeed] = Bdat::getMember(wrapper.data, "WalkSpeed"); }

u32 getChrEnParamWalkSpeed(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamWalkSpeed] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamWalkSpeed], id, 1).valueU8;
}

void initChrEnParamRunSpeed(const CBdatWrapper &wrapper) { s_members[ChrEnParamRunSpeed] = Bdat::getMember(wrapper.data, "RunSpeed"); }

u32 getChrEnParamRunSpeed(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamRunSpeed] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamRunSpeed], id, 1).valueU8;
}

void initChrEnParamBtlSpeed(const CBdatWrapper &wrapper) { s_members[ChrEnParamBtlSpeed] = Bdat::getMember(wrapper.data, "BtlSpeed"); }

u32 getChrEnParamBtlSpeed(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamBtlSpeed] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamBtlSpeed], id, 1).valueU8;
}

void initChrEnParamHpDefault(const CBdatWrapper &wrapper) { s_members[ChrEnParamHpDefault] = Bdat::getMember(wrapper.data, "HpDefault"); }

u32 getChrEnParamHpDefault(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamHpDefault] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamHpDefault], id, 1).valueU8;
}

void initChrEnParamHpLimit(const CBdatWrapper &wrapper) { s_members[ChrEnParamHpLimit] = Bdat::getMember(wrapper.data, "HpLimit"); }

u32 getChrEnParamHpLimit(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamHpLimit] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamHpLimit], id, 1).valueU8;
}

void initChrEnParamScoutStartHp(const CBdatWrapper &wrapper) { s_members[ChrEnParamScoutStartHp] = Bdat::getMember(wrapper.data, "ScoutStartHp"); }

u32 getChrEnParamScoutStartHp(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamScoutStartHp] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamScoutStartHp], id, 1).valueU8;
}

void initChrEnParamScoutEndHp(const CBdatWrapper &wrapper) { s_members[ChrEnParamScoutEndHp] = Bdat::getMember(wrapper.data, "ScoutEndHp"); }

u32 getChrEnParamScoutEndHp(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamScoutEndHp] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamScoutEndHp], id, 1).valueU8;
}

void initChrEnParamHpMaxRev(const CBdatWrapper &wrapper) { s_members[ChrEnParamHpMaxRev] = Bdat::getMember(wrapper.data, "HpMaxRev"); }

u32 getChrEnParamHpMaxRev(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamHpMaxRev] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamHpMaxRev], id, 2).valueU16;
}

void initChrEnParamStrengthRev(const CBdatWrapper &wrapper) { s_members[ChrEnParamStrengthRev] = Bdat::getMember(wrapper.data, "StrengthRev"); }

u32 getChrEnParamStrengthRev(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamStrengthRev] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamStrengthRev], id, 2).valueU16;
}

void initChrEnParamPowEtherRev(const CBdatWrapper &wrapper) { s_members[ChrEnParamPowEtherRev] = Bdat::getMember(wrapper.data, "PowEtherRev"); }

u32 getChrEnParamPowEtherRev(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamPowEtherRev] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamPowEtherRev], id, 2).valueU16;
}

void initChrEnParamDexRev(const CBdatWrapper &wrapper) { s_members[ChrEnParamDexRev] = Bdat::getMember(wrapper.data, "DexRev"); }

u32 getChrEnParamDexRev(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamDexRev] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamDexRev], id, 2).valueU16;
}

void initChrEnParamAgilityRev(const CBdatWrapper &wrapper) { s_members[ChrEnParamAgilityRev] = Bdat::getMember(wrapper.data, "AgilityRev"); }

u32 getChrEnParamAgilityRev(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamAgilityRev] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamAgilityRev], id, 2).valueU16;
}

void initChrEnParamLuckRev(const CBdatWrapper &wrapper) { s_members[ChrEnParamLuckRev] = Bdat::getMember(wrapper.data, "LuckRev"); }

u32 getChrEnParamLuckRev(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamLuckRev] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamLuckRev], id, 2).valueU16;
}

void initChrEnParamParmor(const CBdatWrapper &wrapper) { s_members[ChrEnParamParmor] = Bdat::getMember(wrapper.data, "Parmor"); }

u32 getChrEnParamParmor(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamParmor] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamParmor], id, 2).valueU16;
}

void initChrEnParamEarmor(const CBdatWrapper &wrapper) { s_members[ChrEnParamEarmor] = Bdat::getMember(wrapper.data, "Earmor"); }

u32 getChrEnParamEarmor(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamEarmor] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamEarmor], id, 2).valueU16;
}

void initChrEnParamRstPower(const CBdatWrapper &wrapper) { s_members[ChrEnParamRstPower] = Bdat::getMember(wrapper.data, "RstPower"); }

s32 getChrEnParamRstPower(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamRstPower] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamRstPower], id, 4).valueS8;
}

void initChrEnParamRstEther(const CBdatWrapper &wrapper) { s_members[ChrEnParamRstEther] = Bdat::getMember(wrapper.data, "RstEther"); }

s32 getChrEnParamRstEther(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamRstEther] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamRstEther], id, 4).valueS8;
}

void initChrEnParamAtr(const CBdatWrapper &wrapper) { s_members[ChrEnParamAtr] = Bdat::getMember(wrapper.data, "Atr"); }

u32 getChrEnParamAtr(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamAtr] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamAtr], id, 1).valueU8;
}

void initChrEnParamCriticalRate(const CBdatWrapper &wrapper) { s_members[ChrEnParamCriticalRate] = Bdat::getMember(wrapper.data, "CriticalRate"); }

u32 getChrEnParamCriticalRate(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamCriticalRate] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamCriticalRate], id, 1).valueU8;
}

void initChrEnParamGuardRate(const CBdatWrapper &wrapper) { s_members[ChrEnParamGuardRate] = Bdat::getMember(wrapper.data, "GuardRate"); }

u32 getChrEnParamGuardRate(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamGuardRate] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamGuardRate], id, 1).valueU8;
}

void initChrEnParamFlagGrdDirFront(const CBdatWrapper &wrapper) {
  s_members[ChrEnParamFlagGrdDirFront] = Bdat::getMember(wrapper.data, "Flag");
  s_members[ChrEnParamFlagGrdDirFrontFlag] = Bdat::getMember(wrapper.data, "GrdDirFront");
}

bool isChrEnParamFlagGrdDirFront(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamFlagGrdDirFront] == nullptr || s_members[ChrEnParamFlagGrdDirFrontFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[ChrEnParamFlagGrdDirFront], id, s_members[ChrEnParamFlagGrdDirFrontFlag]) != 0;
}

void initChrEnParamFlagGrdDirLeft(const CBdatWrapper &wrapper) {
  s_members[ChrEnParamFlagGrdDirLeft] = Bdat::getMember(wrapper.data, "Flag");
  s_members[ChrEnParamFlagGrdDirLeftFlag] = Bdat::getMember(wrapper.data, "GrdDirLeft");
}

bool isChrEnParamFlagGrdDirLeft(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamFlagGrdDirLeft] == nullptr || s_members[ChrEnParamFlagGrdDirLeftFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[ChrEnParamFlagGrdDirLeft], id, s_members[ChrEnParamFlagGrdDirLeftFlag]) != 0;
}

void initChrEnParamFlagGrdDirRight(const CBdatWrapper &wrapper) {
  s_members[ChrEnParamFlagGrdDirRight] = Bdat::getMember(wrapper.data, "Flag");
  s_members[ChrEnParamFlagGrdDirRightFlag] = Bdat::getMember(wrapper.data, "GrdDirRight");
}

bool isChrEnParamFlagGrdDirRight(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamFlagGrdDirRight] == nullptr || s_members[ChrEnParamFlagGrdDirRightFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[ChrEnParamFlagGrdDirRight], id, s_members[ChrEnParamFlagGrdDirRightFlag]) != 0;
}

void initChrEnParamFlagGrdDirBack(const CBdatWrapper &wrapper) {
  s_members[ChrEnParamFlagGrdDirBack] = Bdat::getMember(wrapper.data, "Flag");
  s_members[ChrEnParamFlagGrdDirBackFlag] = Bdat::getMember(wrapper.data, "GrdDirBack");
}

bool isChrEnParamFlagGrdDirBack(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamFlagGrdDirBack] == nullptr || s_members[ChrEnParamFlagGrdDirBackFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[ChrEnParamFlagGrdDirBack], id, s_members[ChrEnParamFlagGrdDirBackFlag]) != 0;
}

void initChrEnParamFlagFldDmgType(const CBdatWrapper &wrapper) {
  s_members[ChrEnParamFlagFldDmgType] = Bdat::getMember(wrapper.data, "Flag");
  s_members[ChrEnParamFlagFldDmgTypeFlag] = Bdat::getMember(wrapper.data, "FldDmgType");
}

bool isChrEnParamFlagFldDmgType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamFlagFldDmgType] == nullptr || s_members[ChrEnParamFlagFldDmgTypeFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[ChrEnParamFlagFldDmgType], id, s_members[ChrEnParamFlagFldDmgTypeFlag]) != 0;
}

void initChrEnParamHealPotDrop(const CBdatWrapper &wrapper) { s_members[ChrEnParamHealPotDrop] = Bdat::getMember(wrapper.data, "HealPotDrop"); }

u32 getChrEnParamHealPotDrop(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamHealPotDrop] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamHealPotDrop], id, 1).valueU8;
}

void initChrEnParamRstFiCombo(const CBdatWrapper &wrapper) { s_members[ChrEnParamRstFiCombo] = Bdat::getMember(wrapper.data, "RstFiCombo"); }

u32 getChrEnParamRstFiCombo(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamRstFiCombo] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamRstFiCombo], id, 2).valueU16;
}

void initChrEnParamIvdFiCombo(const CBdatWrapper &wrapper) { s_members[ChrEnParamIvdFiCombo] = Bdat::getMember(wrapper.data, "IvdFiCombo"); }

u32 getChrEnParamIvdFiCombo(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamIvdFiCombo] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamIvdFiCombo], id, 2).valueU16;
}

void initChrEnParamAura(const CBdatWrapper &wrapper) { s_members[ChrEnParamAura] = Bdat::getMember(wrapper.data, "Aura"); }

u32 getChrEnParamAura(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamAura] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamAura], id, 2).valueU16;
}

void initChrEnParamDyingHP(const CBdatWrapper &wrapper) { s_members[ChrEnParamDyingHP] = Bdat::getMember(wrapper.data, "DyingHP"); }

u32 getChrEnParamDyingHP(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamDyingHP] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamDyingHP], id, 1).valueU8;
}

void initChrEnParamWTNormal(const CBdatWrapper &wrapper) { s_members[ChrEnParamWTNormal] = Bdat::getMember(wrapper.data, "WTNormal"); }

u32 getChrEnParamWTNormal(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamWTNormal] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamWTNormal], id, 1).valueU8;
}

void initChrEnParamWTDying(const CBdatWrapper &wrapper) { s_members[ChrEnParamWTDying] = Bdat::getMember(wrapper.data, "WTDying"); }

u32 getChrEnParamWTDying(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamWTDying] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamWTDying], id, 1).valueU8;
}

void initChrEnParamHate0Target(const CBdatWrapper &wrapper) { s_members[ChrEnParamHate0Target] = Bdat::getMember(wrapper.data, "Hate0Target"); }

u32 getChrEnParamHate0Target(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamHate0Target] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamHate0Target], id, 1).valueU8;
}

void initChrEnParamDeathArts(const CBdatWrapper &wrapper) { s_members[ChrEnParamDeathArts] = Bdat::getMember(wrapper.data, "DeathArts"); }

u32 getChrEnParamDeathArts(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamDeathArts] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamDeathArts], id, 2).valueU16;
}

void initChrEnParamDeathArtsStop(const CBdatWrapper &wrapper) { s_members[ChrEnParamDeathArtsStop] = Bdat::getMember(wrapper.data, "DeathArtsStop"); }

u32 getChrEnParamDeathArtsStop(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamDeathArtsStop] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamDeathArtsStop], id, 3).valueU32;
}

void initChrEnParamArtsNum1(const CBdatWrapper &wrapper) { s_members[ChrEnParamArtsNum1] = Bdat::getMember(wrapper.data, "ArtsNum1"); }

u32 getChrEnParamArtsNum1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamArtsNum1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamArtsNum1], id, 2).valueU16;
}

void initChrEnParamArtsNum2(const CBdatWrapper &wrapper) { s_members[ChrEnParamArtsNum2] = Bdat::getMember(wrapper.data, "ArtsNum2"); }

u32 getChrEnParamArtsNum2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamArtsNum2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamArtsNum2], id, 2).valueU16;
}

void initChrEnParamArtsNum3(const CBdatWrapper &wrapper) { s_members[ChrEnParamArtsNum3] = Bdat::getMember(wrapper.data, "ArtsNum3"); }

u32 getChrEnParamArtsNum3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamArtsNum3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamArtsNum3], id, 2).valueU16;
}

void initChrEnParamArtsNum4(const CBdatWrapper &wrapper) { s_members[ChrEnParamArtsNum4] = Bdat::getMember(wrapper.data, "ArtsNum4"); }

u32 getChrEnParamArtsNum4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamArtsNum4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamArtsNum4], id, 2).valueU16;
}

void initChrEnParamArtsNum5(const CBdatWrapper &wrapper) { s_members[ChrEnParamArtsNum5] = Bdat::getMember(wrapper.data, "ArtsNum5"); }

u32 getChrEnParamArtsNum5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamArtsNum5] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamArtsNum5], id, 2).valueU16;
}

void initChrEnParamArtsNum6(const CBdatWrapper &wrapper) { s_members[ChrEnParamArtsNum6] = Bdat::getMember(wrapper.data, "ArtsNum6"); }

u32 getChrEnParamArtsNum6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamArtsNum6] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamArtsNum6], id, 2).valueU16;
}

void initChrEnParamArtsNum7(const CBdatWrapper &wrapper) { s_members[ChrEnParamArtsNum7] = Bdat::getMember(wrapper.data, "ArtsNum7"); }

u32 getChrEnParamArtsNum7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamArtsNum7] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamArtsNum7], id, 2).valueU16;
}

void initChrEnParamArtsNum8(const CBdatWrapper &wrapper) { s_members[ChrEnParamArtsNum8] = Bdat::getMember(wrapper.data, "ArtsNum8"); }

u32 getChrEnParamArtsNum8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamArtsNum8] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamArtsNum8], id, 2).valueU16;
}

void initChrEnParamArtsNum9(const CBdatWrapper &wrapper) { s_members[ChrEnParamArtsNum9] = Bdat::getMember(wrapper.data, "ArtsNum9"); }

u32 getChrEnParamArtsNum9(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamArtsNum9] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamArtsNum9], id, 2).valueU16;
}

void initChrEnParamArtsNum10(const CBdatWrapper &wrapper) { s_members[ChrEnParamArtsNum10] = Bdat::getMember(wrapper.data, "ArtsNum10"); }

u32 getChrEnParamArtsNum10(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamArtsNum10] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamArtsNum10], id, 2).valueU16;
}

void initChrEnParamArtsNum11(const CBdatWrapper &wrapper) { s_members[ChrEnParamArtsNum11] = Bdat::getMember(wrapper.data, "ArtsNum11"); }

u32 getChrEnParamArtsNum11(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamArtsNum11] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamArtsNum11], id, 2).valueU16;
}

void initChrEnParamArtsNum12(const CBdatWrapper &wrapper) { s_members[ChrEnParamArtsNum12] = Bdat::getMember(wrapper.data, "ArtsNum12"); }

u32 getChrEnParamArtsNum12(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamArtsNum12] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamArtsNum12], id, 2).valueU16;
}

void initChrEnParamArtsNum13(const CBdatWrapper &wrapper) { s_members[ChrEnParamArtsNum13] = Bdat::getMember(wrapper.data, "ArtsNum13"); }

u32 getChrEnParamArtsNum13(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamArtsNum13] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamArtsNum13], id, 2).valueU16;
}

void initChrEnParamArtsNum14(const CBdatWrapper &wrapper) { s_members[ChrEnParamArtsNum14] = Bdat::getMember(wrapper.data, "ArtsNum14"); }

u32 getChrEnParamArtsNum14(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamArtsNum14] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamArtsNum14], id, 2).valueU16;
}

void initChrEnParamArtsNum15(const CBdatWrapper &wrapper) { s_members[ChrEnParamArtsNum15] = Bdat::getMember(wrapper.data, "ArtsNum15"); }

u32 getChrEnParamArtsNum15(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamArtsNum15] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamArtsNum15], id, 2).valueU16;
}

void initChrEnParamArtsNum16(const CBdatWrapper &wrapper) { s_members[ChrEnParamArtsNum16] = Bdat::getMember(wrapper.data, "ArtsNum16"); }

u32 getChrEnParamArtsNum16(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamArtsNum16] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamArtsNum16], id, 2).valueU16;
}

void initChrEnParamTableHpMaxBase(const CBdatWrapper &wrapper) { s_members[ChrEnParamTableHpMaxBase] = Bdat::getMember(wrapper.data, "HpMaxBase"); }

u32 getChrEnParamTableHpMaxBase(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamTableHpMaxBase] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamTableHpMaxBase], id, 3).valueU32;
}

void initChrEnParamTableStrengthBase(const CBdatWrapper &wrapper) {
  s_members[ChrEnParamTableStrengthBase] = Bdat::getMember(wrapper.data, "StrengthBase");
}

u32 getChrEnParamTableStrengthBase(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamTableStrengthBase] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamTableStrengthBase], id, 2).valueU16;
}

void initChrEnParamTablePowEtherBase(const CBdatWrapper &wrapper) {
  s_members[ChrEnParamTablePowEtherBase] = Bdat::getMember(wrapper.data, "PowEtherBase");
}

u32 getChrEnParamTablePowEtherBase(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamTablePowEtherBase] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamTablePowEtherBase], id, 2).valueU16;
}

void initChrEnParamTableDexBase(const CBdatWrapper &wrapper) { s_members[ChrEnParamTableDexBase] = Bdat::getMember(wrapper.data, "DexBase"); }

u32 getChrEnParamTableDexBase(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamTableDexBase] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamTableDexBase], id, 2).valueU16;
}

void initChrEnParamTableAgilityBase(const CBdatWrapper &wrapper) {
  s_members[ChrEnParamTableAgilityBase] = Bdat::getMember(wrapper.data, "AgilityBase");
}

u32 getChrEnParamTableAgilityBase(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamTableAgilityBase] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamTableAgilityBase], id, 2).valueU16;
}

void initChrEnParamTableLuckBase(const CBdatWrapper &wrapper) { s_members[ChrEnParamTableLuckBase] = Bdat::getMember(wrapper.data, "LuckBase"); }

u32 getChrEnParamTableLuckBase(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamTableLuckBase] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamTableLuckBase], id, 2).valueU16;
}

void initChrEnParamRevHpMaxRev(const CBdatWrapper &wrapper) { s_members[ChrEnParamRevHpMaxRev] = Bdat::getMember(wrapper.data, "HpMaxRev"); }

u32 getChrEnParamRevHpMaxRev(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamRevHpMaxRev] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamRevHpMaxRev], id, 2).valueU16;
}

void initChrEnParamRevStrengthRev(const CBdatWrapper &wrapper) { s_members[ChrEnParamRevStrengthRev] = Bdat::getMember(wrapper.data, "StrengthRev"); }

u32 getChrEnParamRevStrengthRev(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamRevStrengthRev] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamRevStrengthRev], id, 2).valueU16;
}

void initChrEnParamRevPowEtherRev(const CBdatWrapper &wrapper) { s_members[ChrEnParamRevPowEtherRev] = Bdat::getMember(wrapper.data, "PowEtherRev"); }

u32 getChrEnParamRevPowEtherRev(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamRevPowEtherRev] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamRevPowEtherRev], id, 2).valueU16;
}

void initChrEnParamRevDexRev(const CBdatWrapper &wrapper) { s_members[ChrEnParamRevDexRev] = Bdat::getMember(wrapper.data, "DexRev"); }

u32 getChrEnParamRevDexRev(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamRevDexRev] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamRevDexRev], id, 2).valueU16;
}

void initChrEnParamRevAgilityRev(const CBdatWrapper &wrapper) { s_members[ChrEnParamRevAgilityRev] = Bdat::getMember(wrapper.data, "AgilityRev"); }

u32 getChrEnParamRevAgilityRev(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamRevAgilityRev] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamRevAgilityRev], id, 2).valueU16;
}

void initChrEnParamRevLuckRev(const CBdatWrapper &wrapper) { s_members[ChrEnParamRevLuckRev] = Bdat::getMember(wrapper.data, "LuckRev"); }

u32 getChrEnParamRevLuckRev(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnParamRevLuckRev] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnParamRevLuckRev], id, 2).valueU16;
}

void initChrEnRstDebuffRevRevType(const CBdatWrapper &wrapper) { s_members[ChrEnRstDebuffRevRevType] = Bdat::getMember(wrapper.data, "RevType"); }

u32 getChrEnRstDebuffRevRevType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnRstDebuffRevRevType] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnRstDebuffRevRevType], id, 1).valueU8;
}

void initChrEnRstDebuffRevRstFiCombo(const CBdatWrapper &wrapper) {
  s_members[ChrEnRstDebuffRevRstFiCombo] = Bdat::getMember(wrapper.data, "RstFiCombo");
}

u32 getChrEnRstDebuffRevRstFiCombo(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnRstDebuffRevRstFiCombo] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnRstDebuffRevRstFiCombo], id, 2).valueU16;
}

void initChrEnRstDebuffRevIvdFiCombo(const CBdatWrapper &wrapper) {
  s_members[ChrEnRstDebuffRevIvdFiCombo] = Bdat::getMember(wrapper.data, "IvdFiCombo");
}

u32 getChrEnRstDebuffRevIvdFiCombo(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrEnRstDebuffRevIvdFiCombo] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrEnRstDebuffRevIvdFiCombo], id, 2).valueU16;
}

void initEnemyGroupEnemyID1(const CBdatWrapper &wrapper) { s_members[EnemyGroupEnemyID1] = Bdat::getMember(wrapper.data, "EnemyID1"); }

u32 getEnemyGroupEnemyID1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[EnemyGroupEnemyID1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[EnemyGroupEnemyID1], id, 2).valueU16;
}

void initEnemyGroupEnemyID2(const CBdatWrapper &wrapper) { s_members[EnemyGroupEnemyID2] = Bdat::getMember(wrapper.data, "EnemyID2"); }

u32 getEnemyGroupEnemyID2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[EnemyGroupEnemyID2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[EnemyGroupEnemyID2], id, 2).valueU16;
}

void initEnemyGroupEnemyID3(const CBdatWrapper &wrapper) { s_members[EnemyGroupEnemyID3] = Bdat::getMember(wrapper.data, "EnemyID3"); }

u32 getEnemyGroupEnemyID3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[EnemyGroupEnemyID3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[EnemyGroupEnemyID3], id, 2).valueU16;
}

void initEnemyGroupEnemyID4(const CBdatWrapper &wrapper) { s_members[EnemyGroupEnemyID4] = Bdat::getMember(wrapper.data, "EnemyID4"); }

u32 getEnemyGroupEnemyID4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[EnemyGroupEnemyID4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[EnemyGroupEnemyID4], id, 2).valueU16;
}

void initEnemyGroupEnemyID5(const CBdatWrapper &wrapper) { s_members[EnemyGroupEnemyID5] = Bdat::getMember(wrapper.data, "EnemyID5"); }

u32 getEnemyGroupEnemyID5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[EnemyGroupEnemyID5] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[EnemyGroupEnemyID5], id, 2).valueU16;
}

void initEnemyGroupEnemyID6(const CBdatWrapper &wrapper) { s_members[EnemyGroupEnemyID6] = Bdat::getMember(wrapper.data, "EnemyID6"); }

u32 getEnemyGroupEnemyID6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[EnemyGroupEnemyID6] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[EnemyGroupEnemyID6], id, 2).valueU16;
}

void initEnemyGroupEnemyID7(const CBdatWrapper &wrapper) { s_members[EnemyGroupEnemyID7] = Bdat::getMember(wrapper.data, "EnemyID7"); }

u32 getEnemyGroupEnemyID7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[EnemyGroupEnemyID7] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[EnemyGroupEnemyID7], id, 2).valueU16;
}

void initEnemyGroupEnemyID8(const CBdatWrapper &wrapper) { s_members[EnemyGroupEnemyID8] = Bdat::getMember(wrapper.data, "EnemyID8"); }

u32 getEnemyGroupEnemyID8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[EnemyGroupEnemyID8] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[EnemyGroupEnemyID8], id, 2).valueU16;
}

} // namespace _gfbep

GfBdatChrEnParam::GfBdatChrEnParam()
    : m_chrEnParam(nullptr), m_chrEnParamTable(nullptr), m_chrEnParamRev(nullptr), m_chrEnRstDebuffRev(nullptr), m_enemyGroup(nullptr) {
  bdatRefresh();
}

GfBdatChrEnParam::~GfBdatChrEnParam() { destroyFP(); }

void GfBdatChrEnParam::destroyFP() {
  if (m_chrEnParam != nullptr) {
    delete m_chrEnParam;
    m_chrEnParam = nullptr;
  }

  if (m_chrEnParamTable != nullptr) {
    delete m_chrEnParamTable;
    m_chrEnParamTable = nullptr;
  }

  if (m_chrEnParamRev != nullptr) {
    delete m_chrEnParamRev;
    m_chrEnParamRev = nullptr;
  }

  if (m_chrEnRstDebuffRev != nullptr) {
    delete m_chrEnRstDebuffRev;
    m_chrEnRstDebuffRev = nullptr;
  }

  if (m_enemyGroup != nullptr) {
    delete m_enemyGroup;
    m_enemyGroup = nullptr;
  }
}

#define NEW_BDAT_WRAPPER(bdat)                                                                                                                       \
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) CBdatWrapper { GfDataBdat::getFP(bdat) }

// __LINE__ of the allocations changes the instruction order.
#line 1030
void GfBdatChrEnParam::createFP() {
  m_chrEnParam = NEW_BDAT_WRAPPER(BDAT_CHR_EN_PARAM);
  m_chrEnParamTable = NEW_BDAT_WRAPPER(BDAT_CHR_EN_PARAM_TABLE);
  m_chrEnParamRev = NEW_BDAT_WRAPPER(BDAT_CHR_EN_PARAM_REV);
  m_chrEnRstDebuffRev = NEW_BDAT_WRAPPER(BDAT_CHR_EN_RST_DEBUFF_REV);
  m_enemyGroup = NEW_BDAT_WRAPPER(BDAT_FLD_ENEMY_GROUP);
}

void GfBdatChrEnParam::bdatRefresh() {
  destroyFP();
  createFP();
  _gfbep::initChrEnParamDebug_Name(*m_chrEnParam);
  _gfbep::initChrEnParamResourceID(*m_chrEnParam);
  _gfbep::initChrEnParamAiID(*m_chrEnParam);
  _gfbep::initChrEnParamEnemyRole(*m_chrEnParam);
  _gfbep::initChrEnParamWalkSpeed(*m_chrEnParam);
  _gfbep::initChrEnParamRunSpeed(*m_chrEnParam);
  _gfbep::initChrEnParamBtlSpeed(*m_chrEnParam);
  _gfbep::initChrEnParamHpDefault(*m_chrEnParam);
  _gfbep::initChrEnParamHpLimit(*m_chrEnParam);
  _gfbep::initChrEnParamScoutStartHp(*m_chrEnParam);
  _gfbep::initChrEnParamScoutEndHp(*m_chrEnParam);
  _gfbep::initChrEnParamHpMaxRev(*m_chrEnParam);
  _gfbep::initChrEnParamStrengthRev(*m_chrEnParam);
  _gfbep::initChrEnParamPowEtherRev(*m_chrEnParam);
  _gfbep::initChrEnParamDexRev(*m_chrEnParam);
  _gfbep::initChrEnParamAgilityRev(*m_chrEnParam);
  _gfbep::initChrEnParamLuckRev(*m_chrEnParam);
  _gfbep::initChrEnParamParmor(*m_chrEnParam);
  _gfbep::initChrEnParamEarmor(*m_chrEnParam);
  _gfbep::initChrEnParamRstPower(*m_chrEnParam);
  _gfbep::initChrEnParamRstEther(*m_chrEnParam);
  _gfbep::initChrEnParamAtr(*m_chrEnParam);
  _gfbep::initChrEnParamCriticalRate(*m_chrEnParam);
  _gfbep::initChrEnParamGuardRate(*m_chrEnParam);
  _gfbep::initChrEnParamFlagGrdDirFront(*m_chrEnParam);
  _gfbep::initChrEnParamFlagGrdDirLeft(*m_chrEnParam);
  _gfbep::initChrEnParamFlagGrdDirRight(*m_chrEnParam);
  _gfbep::initChrEnParamFlagGrdDirBack(*m_chrEnParam);
  _gfbep::initChrEnParamFlagFldDmgType(*m_chrEnParam);
  _gfbep::initChrEnParamHealPotDrop(*m_chrEnParam);
  _gfbep::initChrEnParamRstFiCombo(*m_chrEnParam);
  _gfbep::initChrEnParamIvdFiCombo(*m_chrEnParam);
  _gfbep::initChrEnParamAura(*m_chrEnParam);
  _gfbep::initChrEnParamDyingHP(*m_chrEnParam);
  _gfbep::initChrEnParamWTNormal(*m_chrEnParam);
  _gfbep::initChrEnParamWTDying(*m_chrEnParam);
  _gfbep::initChrEnParamHate0Target(*m_chrEnParam);
  _gfbep::initChrEnParamDeathArts(*m_chrEnParam);
  _gfbep::initChrEnParamDeathArtsStop(*m_chrEnParam);
  _gfbep::initChrEnParamArtsNum1(*m_chrEnParam);
  _gfbep::initChrEnParamArtsNum2(*m_chrEnParam);
  _gfbep::initChrEnParamArtsNum3(*m_chrEnParam);
  _gfbep::initChrEnParamArtsNum4(*m_chrEnParam);
  _gfbep::initChrEnParamArtsNum5(*m_chrEnParam);
  _gfbep::initChrEnParamArtsNum6(*m_chrEnParam);
  _gfbep::initChrEnParamArtsNum7(*m_chrEnParam);
  _gfbep::initChrEnParamArtsNum8(*m_chrEnParam);
  _gfbep::initChrEnParamArtsNum9(*m_chrEnParam);
  _gfbep::initChrEnParamArtsNum10(*m_chrEnParam);
  _gfbep::initChrEnParamArtsNum11(*m_chrEnParam);
  _gfbep::initChrEnParamArtsNum12(*m_chrEnParam);
  _gfbep::initChrEnParamArtsNum13(*m_chrEnParam);
  _gfbep::initChrEnParamArtsNum14(*m_chrEnParam);
  _gfbep::initChrEnParamArtsNum15(*m_chrEnParam);
  _gfbep::initChrEnParamArtsNum16(*m_chrEnParam);
  _gfbep::initChrEnParamTableHpMaxBase(*m_chrEnParamTable);
  _gfbep::initChrEnParamTableStrengthBase(*m_chrEnParamTable);
  _gfbep::initChrEnParamTablePowEtherBase(*m_chrEnParamTable);
  _gfbep::initChrEnParamTableDexBase(*m_chrEnParamTable);
  _gfbep::initChrEnParamTableAgilityBase(*m_chrEnParamTable);
  _gfbep::initChrEnParamTableLuckBase(*m_chrEnParamTable);
  _gfbep::initChrEnParamRevHpMaxRev(*m_chrEnParamRev);
  _gfbep::initChrEnParamRevStrengthRev(*m_chrEnParamRev);
  _gfbep::initChrEnParamRevPowEtherRev(*m_chrEnParamRev);
  _gfbep::initChrEnParamRevDexRev(*m_chrEnParamRev);
  _gfbep::initChrEnParamRevAgilityRev(*m_chrEnParamRev);
  _gfbep::initChrEnParamRevLuckRev(*m_chrEnParamRev);
  _gfbep::initChrEnRstDebuffRevRevType(*m_chrEnRstDebuffRev);
  _gfbep::initChrEnRstDebuffRevRstFiCombo(*m_chrEnRstDebuffRev);
  _gfbep::initChrEnRstDebuffRevIvdFiCombo(*m_chrEnRstDebuffRev);
  _gfbep::initEnemyGroupEnemyID1(*m_enemyGroup);
  _gfbep::initEnemyGroupEnemyID2(*m_enemyGroup);
  _gfbep::initEnemyGroupEnemyID3(*m_enemyGroup);
  _gfbep::initEnemyGroupEnemyID4(*m_enemyGroup);
  _gfbep::initEnemyGroupEnemyID5(*m_enemyGroup);
  _gfbep::initEnemyGroupEnemyID6(*m_enemyGroup);
  _gfbep::initEnemyGroupEnemyID7(*m_enemyGroup);
  _gfbep::initEnemyGroupEnemyID8(*m_enemyGroup);
}

u32 GfBdatChrEnParam::getChrEnParamStart() const { return Bdat::getIdTop(m_chrEnParam->data); }

u32 GfBdatChrEnParam::getChrEnParamEnd() const { return Bdat::getIdTop(m_chrEnParam->data) + Bdat::getIdCount(m_chrEnParam->data); }

const char *GfBdatChrEnParam::getChrEnParamDebug_Name(u32 id) const { return _gfbep::getChrEnParamDebug_Name(*m_chrEnParam, id); }

u32 GfBdatChrEnParam::getChrEnParamResourceID(u32 id) const { return _gfbep::getChrEnParamResourceID(*m_chrEnParam, id); }

u32 GfBdatChrEnParam::getChrEnParamAiID(u32 id) const { return _gfbep::getChrEnParamAiID(*m_chrEnParam, id); }

u32 GfBdatChrEnParam::getChrEnParamEnemyRole(u32 id) const { return _gfbep::getChrEnParamEnemyRole(*m_chrEnParam, id); }

u32 GfBdatChrEnParam::getChrEnParamWalkSpeed(u32 id) const { return _gfbep::getChrEnParamWalkSpeed(*m_chrEnParam, id); }

u32 GfBdatChrEnParam::getChrEnParamRunSpeed(u32 id) const { return _gfbep::getChrEnParamRunSpeed(*m_chrEnParam, id); }

u32 GfBdatChrEnParam::getChrEnParamBtlSpeed(u32 id) const { return _gfbep::getChrEnParamBtlSpeed(*m_chrEnParam, id); }

u32 GfBdatChrEnParam::getChrEnParamHpDefault(u32 id) const { return _gfbep::getChrEnParamHpDefault(*m_chrEnParam, id); }

u32 GfBdatChrEnParam::getChrEnParamHpLimit(u32 id) const { return _gfbep::getChrEnParamHpLimit(*m_chrEnParam, id); }

u32 GfBdatChrEnParam::getChrEnParamScoutStartHp(u32 id) const { return _gfbep::getChrEnParamScoutStartHp(*m_chrEnParam, id); }

u32 GfBdatChrEnParam::getChrEnParamScoutEndHp(u32 id) const { return _gfbep::getChrEnParamScoutEndHp(*m_chrEnParam, id); }

u32 GfBdatChrEnParam::getChrEnParamHpMaxRev(u32 id) const { return _gfbep::getChrEnParamHpMaxRev(*m_chrEnParam, id); }

u32 GfBdatChrEnParam::getChrEnParamStrengthRev(u32 id) const { return _gfbep::getChrEnParamStrengthRev(*m_chrEnParam, id); }

u32 GfBdatChrEnParam::getChrEnParamPowEtherRev(u32 id) const { return _gfbep::getChrEnParamPowEtherRev(*m_chrEnParam, id); }

u32 GfBdatChrEnParam::getChrEnParamDexRev(u32 id) const { return _gfbep::getChrEnParamDexRev(*m_chrEnParam, id); }

u32 GfBdatChrEnParam::getChrEnParamAgilityRev(u32 id) const { return _gfbep::getChrEnParamAgilityRev(*m_chrEnParam, id); }

u32 GfBdatChrEnParam::getChrEnParamLuckRev(u32 id) const { return _gfbep::getChrEnParamLuckRev(*m_chrEnParam, id); }

u32 GfBdatChrEnParam::getChrEnParamParmor(u32 id) const { return _gfbep::getChrEnParamParmor(*m_chrEnParam, id); }

u32 GfBdatChrEnParam::getChrEnParamEarmor(u32 id) const { return _gfbep::getChrEnParamEarmor(*m_chrEnParam, id); }

s32 GfBdatChrEnParam::getChrEnParamRstPower(u32 id) const { return _gfbep::getChrEnParamRstPower(*m_chrEnParam, id); }

s32 GfBdatChrEnParam::getChrEnParamRstEther(u32 id) const { return _gfbep::getChrEnParamRstEther(*m_chrEnParam, id); }

u32 GfBdatChrEnParam::getChrEnParamAtr(u32 id) const { return _gfbep::getChrEnParamAtr(*m_chrEnParam, id); }

u32 GfBdatChrEnParam::getChrEnParamCriticalRate(u32 id) const { return _gfbep::getChrEnParamCriticalRate(*m_chrEnParam, id); }

u32 GfBdatChrEnParam::getChrEnParamGuardRate(u32 id) const { return _gfbep::getChrEnParamGuardRate(*m_chrEnParam, id); }

bool GfBdatChrEnParam::isChrEnParamFlagGrdDirFront(u32 id) const { return _gfbep::isChrEnParamFlagGrdDirFront(*m_chrEnParam, id); }

bool GfBdatChrEnParam::isChrEnParamFlagGrdDirLeft(u32 id) const { return _gfbep::isChrEnParamFlagGrdDirLeft(*m_chrEnParam, id); }

bool GfBdatChrEnParam::isChrEnParamFlagGrdDirRight(u32 id) const { return _gfbep::isChrEnParamFlagGrdDirRight(*m_chrEnParam, id); }

bool GfBdatChrEnParam::isChrEnParamFlagGrdDirBack(u32 id) const { return _gfbep::isChrEnParamFlagGrdDirBack(*m_chrEnParam, id); }

bool GfBdatChrEnParam::isChrEnParamFlagFldDmgType(u32 id) const { return _gfbep::isChrEnParamFlagFldDmgType(*m_chrEnParam, id); }

u32 GfBdatChrEnParam::getChrEnParamHealPotDrop(u32 id) const { return _gfbep::getChrEnParamHealPotDrop(*m_chrEnParam, id); }

u32 GfBdatChrEnParam::getChrEnParamRstFiCombo(u32 id) const { return _gfbep::getChrEnParamRstFiCombo(*m_chrEnParam, id); }

u32 GfBdatChrEnParam::getChrEnParamIvdFiCombo(u32 id) const { return _gfbep::getChrEnParamIvdFiCombo(*m_chrEnParam, id); }

u32 GfBdatChrEnParam::getChrEnParamAura(u32 id) const { return _gfbep::getChrEnParamAura(*m_chrEnParam, id); }

u32 GfBdatChrEnParam::getChrEnParamDyingHP(u32 id) const { return _gfbep::getChrEnParamDyingHP(*m_chrEnParam, id); }

u32 GfBdatChrEnParam::getChrEnParamWTNormal(u32 id) const { return _gfbep::getChrEnParamWTNormal(*m_chrEnParam, id); }

u32 GfBdatChrEnParam::getChrEnParamWTDying(u32 id) const { return _gfbep::getChrEnParamWTDying(*m_chrEnParam, id); }

u32 GfBdatChrEnParam::getChrEnParamHate0Target(u32 id) const { return _gfbep::getChrEnParamHate0Target(*m_chrEnParam, id); }

u32 GfBdatChrEnParam::getChrEnParamDeathArts(u32 id) const { return _gfbep::getChrEnParamDeathArts(*m_chrEnParam, id); }

u32 GfBdatChrEnParam::getChrEnParamDeathArtsStop(u32 id) const { return _gfbep::getChrEnParamDeathArtsStop(*m_chrEnParam, id); }

u32 GfBdatChrEnParam::getChrEnParamArtsNum1(u32 id) const { return _gfbep::getChrEnParamArtsNum1(*m_chrEnParam, id); }

u32 GfBdatChrEnParam::getChrEnParamArtsNum2(u32 id) const { return _gfbep::getChrEnParamArtsNum2(*m_chrEnParam, id); }

u32 GfBdatChrEnParam::getChrEnParamArtsNum3(u32 id) const { return _gfbep::getChrEnParamArtsNum3(*m_chrEnParam, id); }

u32 GfBdatChrEnParam::getChrEnParamArtsNum4(u32 id) const { return _gfbep::getChrEnParamArtsNum4(*m_chrEnParam, id); }

u32 GfBdatChrEnParam::getChrEnParamArtsNum5(u32 id) const { return _gfbep::getChrEnParamArtsNum5(*m_chrEnParam, id); }

u32 GfBdatChrEnParam::getChrEnParamArtsNum6(u32 id) const { return _gfbep::getChrEnParamArtsNum6(*m_chrEnParam, id); }

u32 GfBdatChrEnParam::getChrEnParamArtsNum7(u32 id) const { return _gfbep::getChrEnParamArtsNum7(*m_chrEnParam, id); }

u32 GfBdatChrEnParam::getChrEnParamArtsNum8(u32 id) const { return _gfbep::getChrEnParamArtsNum8(*m_chrEnParam, id); }

u32 GfBdatChrEnParam::getChrEnParamArtsNum9(u32 id) const { return _gfbep::getChrEnParamArtsNum9(*m_chrEnParam, id); }

u32 GfBdatChrEnParam::getChrEnParamArtsNum10(u32 id) const { return _gfbep::getChrEnParamArtsNum10(*m_chrEnParam, id); }

u32 GfBdatChrEnParam::getChrEnParamArtsNum11(u32 id) const { return _gfbep::getChrEnParamArtsNum11(*m_chrEnParam, id); }

u32 GfBdatChrEnParam::getChrEnParamArtsNum12(u32 id) const { return _gfbep::getChrEnParamArtsNum12(*m_chrEnParam, id); }

u32 GfBdatChrEnParam::getChrEnParamArtsNum13(u32 id) const { return _gfbep::getChrEnParamArtsNum13(*m_chrEnParam, id); }

u32 GfBdatChrEnParam::getChrEnParamArtsNum14(u32 id) const { return _gfbep::getChrEnParamArtsNum14(*m_chrEnParam, id); }

u32 GfBdatChrEnParam::getChrEnParamArtsNum15(u32 id) const { return _gfbep::getChrEnParamArtsNum15(*m_chrEnParam, id); }

u32 GfBdatChrEnParam::getChrEnParamArtsNum16(u32 id) const { return _gfbep::getChrEnParamArtsNum16(*m_chrEnParam, id); }

u32 GfBdatChrEnParam::getChrEnParamArtsNum(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbep::getChrEnParamArtsNum1,
                                                              _gfbep::getChrEnParamArtsNum2,
                                                              _gfbep::getChrEnParamArtsNum3,
                                                              _gfbep::getChrEnParamArtsNum4,
                                                              _gfbep::getChrEnParamArtsNum5,
                                                              _gfbep::getChrEnParamArtsNum6,
                                                              _gfbep::getChrEnParamArtsNum7,
                                                              _gfbep::getChrEnParamArtsNum8,
                                                              _gfbep::getChrEnParamArtsNum9,
                                                              _gfbep::getChrEnParamArtsNum10,
                                                              _gfbep::getChrEnParamArtsNum11,
                                                              _gfbep::getChrEnParamArtsNum12,
                                                              _gfbep::getChrEnParamArtsNum13,
                                                              _gfbep::getChrEnParamArtsNum14,
                                                              _gfbep::getChrEnParamArtsNum15,
                                                              _gfbep::getChrEnParamArtsNum16};
  return getters[index](*m_chrEnParam, id);
}

u32 GfBdatChrEnParam::getChrEnParamTableStart() const { return Bdat::getIdTop(m_chrEnParamTable->data); }

u32 GfBdatChrEnParam::getChrEnParamTableEnd() const { return Bdat::getIdTop(m_chrEnParamTable->data) + Bdat::getIdCount(m_chrEnParamTable->data); }

u32 GfBdatChrEnParam::getChrEnParamTableHpMaxBase(u32 id) const { return _gfbep::getChrEnParamTableHpMaxBase(*m_chrEnParamTable, id); }

u32 GfBdatChrEnParam::getChrEnParamTableStrengthBase(u32 id) const { return _gfbep::getChrEnParamTableStrengthBase(*m_chrEnParamTable, id); }

u32 GfBdatChrEnParam::getChrEnParamTablePowEtherBase(u32 id) const { return _gfbep::getChrEnParamTablePowEtherBase(*m_chrEnParamTable, id); }

u32 GfBdatChrEnParam::getChrEnParamTableDexBase(u32 id) const { return _gfbep::getChrEnParamTableDexBase(*m_chrEnParamTable, id); }

u32 GfBdatChrEnParam::getChrEnParamTableAgilityBase(u32 id) const { return _gfbep::getChrEnParamTableAgilityBase(*m_chrEnParamTable, id); }

u32 GfBdatChrEnParam::getChrEnParamTableLuckBase(u32 id) const { return _gfbep::getChrEnParamTableLuckBase(*m_chrEnParamTable, id); }

u32 GfBdatChrEnParam::getChrEnParamRevStart() const { return Bdat::getIdTop(m_chrEnParamRev->data); }

u32 GfBdatChrEnParam::getChrEnParamRevEnd() const { return Bdat::getIdTop(m_chrEnParamRev->data) + Bdat::getIdCount(m_chrEnParamRev->data); }

u32 GfBdatChrEnParam::getChrEnParamRevHpMaxRev(u32 id) const { return _gfbep::getChrEnParamRevHpMaxRev(*m_chrEnParamRev, id); }

u32 GfBdatChrEnParam::getChrEnParamRevStrengthRev(u32 id) const { return _gfbep::getChrEnParamRevStrengthRev(*m_chrEnParamRev, id); }

u32 GfBdatChrEnParam::getChrEnParamRevPowEtherRev(u32 id) const { return _gfbep::getChrEnParamRevPowEtherRev(*m_chrEnParamRev, id); }

u32 GfBdatChrEnParam::getChrEnParamRevDexRev(u32 id) const { return _gfbep::getChrEnParamRevDexRev(*m_chrEnParamRev, id); }

u32 GfBdatChrEnParam::getChrEnParamRevAgilityRev(u32 id) const { return _gfbep::getChrEnParamRevAgilityRev(*m_chrEnParamRev, id); }

u32 GfBdatChrEnParam::getChrEnParamRevLuckRev(u32 id) const { return _gfbep::getChrEnParamRevLuckRev(*m_chrEnParamRev, id); }

u32 GfBdatChrEnParam::getChrEnRstDebuffRevStart() const { return Bdat::getIdTop(m_chrEnRstDebuffRev->data); }

u32 GfBdatChrEnParam::getChrEnRstDebuffRevEnd() const {
  return Bdat::getIdTop(m_chrEnRstDebuffRev->data) + Bdat::getIdCount(m_chrEnRstDebuffRev->data);
}

u32 GfBdatChrEnParam::getChrEnRstDebuffRevRevType(u32 id) const { return _gfbep::getChrEnRstDebuffRevRevType(*m_chrEnRstDebuffRev, id); }

u32 GfBdatChrEnParam::getChrEnRstDebuffRevRstFiCombo(u32 id) const { return _gfbep::getChrEnRstDebuffRevRstFiCombo(*m_chrEnRstDebuffRev, id); }

u32 GfBdatChrEnParam::getChrEnRstDebuffRevIvdFiCombo(u32 id) const { return _gfbep::getChrEnRstDebuffRevIvdFiCombo(*m_chrEnRstDebuffRev, id); }

u32 GfBdatChrEnParam::getEnemyGroupStart() const { return Bdat::getIdTop(m_enemyGroup->data); }

u32 GfBdatChrEnParam::getEnemyGroupEnd() const { return Bdat::getIdTop(m_enemyGroup->data) + Bdat::getIdCount(m_enemyGroup->data); }

u32 GfBdatChrEnParam::getEnemyGroupEnemyID1(u32 id) const { return _gfbep::getEnemyGroupEnemyID1(*m_enemyGroup, id); }

u32 GfBdatChrEnParam::getEnemyGroupEnemyID2(u32 id) const { return _gfbep::getEnemyGroupEnemyID2(*m_enemyGroup, id); }

u32 GfBdatChrEnParam::getEnemyGroupEnemyID3(u32 id) const { return _gfbep::getEnemyGroupEnemyID3(*m_enemyGroup, id); }

u32 GfBdatChrEnParam::getEnemyGroupEnemyID4(u32 id) const { return _gfbep::getEnemyGroupEnemyID4(*m_enemyGroup, id); }

u32 GfBdatChrEnParam::getEnemyGroupEnemyID5(u32 id) const { return _gfbep::getEnemyGroupEnemyID5(*m_enemyGroup, id); }

u32 GfBdatChrEnParam::getEnemyGroupEnemyID6(u32 id) const { return _gfbep::getEnemyGroupEnemyID6(*m_enemyGroup, id); }

u32 GfBdatChrEnParam::getEnemyGroupEnemyID7(u32 id) const { return _gfbep::getEnemyGroupEnemyID7(*m_enemyGroup, id); }

u32 GfBdatChrEnParam::getEnemyGroupEnemyID8(u32 id) const { return _gfbep::getEnemyGroupEnemyID8(*m_enemyGroup, id); }

u32 GfBdatChrEnParam::getEnemyGroupEnemyID(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbep::getEnemyGroupEnemyID1,
                                                              _gfbep::getEnemyGroupEnemyID2,
                                                              _gfbep::getEnemyGroupEnemyID3,
                                                              _gfbep::getEnemyGroupEnemyID4,
                                                              _gfbep::getEnemyGroupEnemyID5,
                                                              _gfbep::getEnemyGroupEnemyID6,
                                                              _gfbep::getEnemyGroupEnemyID7,
                                                              _gfbep::getEnemyGroupEnemyID8};
  return getters[index](*m_enemyGroup, id);
}

bool GfBdatChrEnParam::searchByRscEn(mm::mtl::FixedVector<u16, 128> &enemies, u32 resourceId) const {
  for (u32 id = getChrEnParamStart(); id < getChrEnParamEnd(); id++) {
    if (getChrEnParamResourceID(id) == resourceId) {
      enemies.push_back(id);
    }
  }

  return !enemies.empty();
}

} // namespace gf
