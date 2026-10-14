#pragma once
#include "gf/data/gf_bdat_wrapper.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

class GfBdatChrEnParam : public mm::mtl::PtrSingleton<GfBdatChrEnParam>, public GfBdatRefresh {
public:
  GfBdatChrEnParam();
  virtual ~GfBdatChrEnParam();
  void destroyFP();
  void createFP();
  void bdatRefresh() override;
  u32 getChrEnParamStart() const;
  u32 getChrEnParamEnd() const;
  const char *getChrEnParamDebug_Name(u32 id) const;
  u32 getChrEnParamResourceID(u32 id) const;
  u32 getChrEnParamAiID(u32 id) const;
  u32 getChrEnParamEnemyRole(u32 id) const;
  u32 getChrEnParamWalkSpeed(u32 id) const;
  u32 getChrEnParamRunSpeed(u32 id) const;
  u32 getChrEnParamBtlSpeed(u32 id) const;
  u32 getChrEnParamHpDefault(u32 id) const;
  u32 getChrEnParamHpLimit(u32 id) const;
  u32 getChrEnParamScoutStartHp(u32 id) const;
  u32 getChrEnParamScoutEndHp(u32 id) const;
  u32 getChrEnParamHpMaxRev(u32 id) const;
  u32 getChrEnParamStrengthRev(u32 id) const;
  u32 getChrEnParamPowEtherRev(u32 id) const;
  u32 getChrEnParamDexRev(u32 id) const;
  u32 getChrEnParamAgilityRev(u32 id) const;
  u32 getChrEnParamLuckRev(u32 id) const;
  u32 getChrEnParamParmor(u32 id) const;
  u32 getChrEnParamEarmor(u32 id) const;
  s32 getChrEnParamRstPower(u32 id) const;
  s32 getChrEnParamRstEther(u32 id) const;
  u32 getChrEnParamAtr(u32 id) const;
  u32 getChrEnParamCriticalRate(u32 id) const;
  u32 getChrEnParamGuardRate(u32 id) const;
  bool isChrEnParamFlagGrdDirFront(u32 id) const;
  bool isChrEnParamFlagGrdDirLeft(u32 id) const;
  bool isChrEnParamFlagGrdDirRight(u32 id) const;
  bool isChrEnParamFlagGrdDirBack(u32 id) const;
  bool isChrEnParamFlagFldDmgType(u32 id) const;
  u32 getChrEnParamHealPotDrop(u32 id) const;
  u32 getChrEnParamRstFiCombo(u32 id) const;
  u32 getChrEnParamIvdFiCombo(u32 id) const;
  u32 getChrEnParamAura(u32 id) const;
  u32 getChrEnParamDyingHP(u32 id) const;
  u32 getChrEnParamWTNormal(u32 id) const;
  u32 getChrEnParamWTDying(u32 id) const;
  u32 getChrEnParamHate0Target(u32 id) const;
  u32 getChrEnParamDeathArts(u32 id) const;
  u32 getChrEnParamDeathArtsStop(u32 id) const;
  u32 getChrEnParamArtsNum1(u32 id) const;
  u32 getChrEnParamArtsNum2(u32 id) const;
  u32 getChrEnParamArtsNum3(u32 id) const;
  u32 getChrEnParamArtsNum4(u32 id) const;
  u32 getChrEnParamArtsNum5(u32 id) const;
  u32 getChrEnParamArtsNum6(u32 id) const;
  u32 getChrEnParamArtsNum7(u32 id) const;
  u32 getChrEnParamArtsNum8(u32 id) const;
  u32 getChrEnParamArtsNum9(u32 id) const;
  u32 getChrEnParamArtsNum10(u32 id) const;
  u32 getChrEnParamArtsNum11(u32 id) const;
  u32 getChrEnParamArtsNum12(u32 id) const;
  u32 getChrEnParamArtsNum13(u32 id) const;
  u32 getChrEnParamArtsNum14(u32 id) const;
  u32 getChrEnParamArtsNum15(u32 id) const;
  u32 getChrEnParamArtsNum16(u32 id) const;
  u32 getChrEnParamArtsNum(u32 id, u32 index) const;
  u32 getChrEnParamTableStart() const;
  u32 getChrEnParamTableEnd() const;
  u32 getChrEnParamTableHpMaxBase(u32 id) const;
  u32 getChrEnParamTableStrengthBase(u32 id) const;
  u32 getChrEnParamTablePowEtherBase(u32 id) const;
  u32 getChrEnParamTableDexBase(u32 id) const;
  u32 getChrEnParamTableAgilityBase(u32 id) const;
  u32 getChrEnParamTableLuckBase(u32 id) const;
  u32 getChrEnParamRevStart() const;
  u32 getChrEnParamRevEnd() const;
  u32 getChrEnParamRevHpMaxRev(u32 id) const;
  u32 getChrEnParamRevStrengthRev(u32 id) const;
  u32 getChrEnParamRevPowEtherRev(u32 id) const;
  u32 getChrEnParamRevDexRev(u32 id) const;
  u32 getChrEnParamRevAgilityRev(u32 id) const;
  u32 getChrEnParamRevLuckRev(u32 id) const;
  u32 getChrEnRstDebuffRevStart() const;
  u32 getChrEnRstDebuffRevEnd() const;
  u32 getChrEnRstDebuffRevRevType(u32 id) const;
  u32 getChrEnRstDebuffRevRstFiCombo(u32 id) const;
  u32 getChrEnRstDebuffRevIvdFiCombo(u32 id) const;
  u32 getEnemyGroupStart() const;
  u32 getEnemyGroupEnd() const;
  u32 getEnemyGroupEnemyID1(u32 id) const;
  u32 getEnemyGroupEnemyID2(u32 id) const;
  u32 getEnemyGroupEnemyID3(u32 id) const;
  u32 getEnemyGroupEnemyID4(u32 id) const;
  u32 getEnemyGroupEnemyID5(u32 id) const;
  u32 getEnemyGroupEnemyID6(u32 id) const;
  u32 getEnemyGroupEnemyID7(u32 id) const;
  u32 getEnemyGroupEnemyID8(u32 id) const;
  u32 getEnemyGroupEnemyID(u32 id, u32 index) const;
  bool searchByRscEn(mm::mtl::FixedVector<u16, 128> &enemies, u32 resourceId) const;

private:
  CBdatWrapper *unknown10; // Inferred label: mChrEnParam; original member name unknown.
  CBdatWrapper *unknown18; // Inferred label: mChrEnParamTable; original member name unknown.
  CBdatWrapper *unknown20; // Inferred label: mChrEnParamRev; original member name unknown.
  CBdatWrapper *unknown28; // Inferred label: mChrEnRstDebuffRev; original member name unknown.
  CBdatWrapper *unknown30; // Inferred label: mEnemyGroup; original member name unknown.
};

} // namespace gf
