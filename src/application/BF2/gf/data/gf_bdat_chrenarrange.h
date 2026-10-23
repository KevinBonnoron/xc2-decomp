#pragma once
#include "gf/data/gf_bdat_wrapper.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

class GfBdatChrEnArrange : public mm::mtl::PtrSingleton<GfBdatChrEnArrange>, public GfBdatRefresh {
public:
  GfBdatChrEnArrange();
  virtual ~GfBdatChrEnArrange();
  void destroyFP();
  void createFP();
  void bdatRefresh() override;
  u32 getChrEnArrangeStart() const;
  u32 getChrEnArrangeEnd() const;
  u32 getChrEnArrangeParamID(u32 id) const;
  u32 getChrEnArrangeEnemyBladeID(u32 id) const;
  u32 getChrEnArrangeBladeID(u32 id) const;
  u32 getChrEnArrangeBladeAtr(u32 id) const;
  u32 getChrEnArrangeExtraParts(u32 id) const;
  u32 getChrEnArrangeName(u32 id) const;
  const char *getChrEnArrangeDebug_Name(u32 id) const;
  u32 getChrEnArrangeLv(u32 id) const;
  u32 getChrEnArrangeLvRand(u32 id) const;
  u32 getChrEnArrangeHpOver(u32 id) const;
  u32 getChrEnArrangeExpRev(u32 id) const;
  u32 getChrEnArrangeGoldRev(u32 id) const;
  u32 getChrEnArrangeWPRev(u32 id) const;
  u32 getChrEnArrangeSPRev(u32 id) const;
  u32 getChrEnArrangeDropTableID(u32 id) const;
  u32 getChrEnArrangeDropTableID2(u32 id) const;
  u32 getChrEnArrangeDropTableID3(u32 id) const;
  u32 getChrEnArrangePreciousID(u32 id) const;
  u32 getChrEnArrangeScale(u32 id) const;
  u32 getChrEnArrangeChrSize(u32 id) const;
  u32 getChrEnArrangeTurnSize(u32 id) const;
  bool isChrEnArrangeFlagNamed(u32 id) const;
  bool isChrEnArrangeFlagmBoss(u32 id) const;
  bool isChrEnArrangeFlagChild(u32 id) const;
  bool isChrEnArrangeFlagFAOff(u32 id) const;
  bool isChrEnArrangeFlagNoEcSkip(u32 id) const;
  bool isChrEnArrangeFlagLinkType(u32 id) const;
  bool isChrEnArrangeFlagChrColiOff(u32 id) const;
  bool isChrEnArrangeFlagNoTarget(u32 id) const;
  bool isChrEnArrangeFlagHikariSP4(u32 id) const;
  bool isChrEnArrangeFlagHomuri(u32 id) const;
  bool isChrEnArrangeFlagHikari(u32 id) const;
  bool isChrEnArrangeFlagNoNaviMesh(u32 id) const;
  bool isChrEnArrangeFlagFixed(u32 id) const;
  bool isChrEnArrangeFlagDropFront(u32 id) const;
  bool isChrEnArrangeFlagNoWarp(u32 id) const;
  bool isChrEnArrangeFlagIgnoreLevPow(u32 id) const;
  bool isChrEnArrangeFlagAlwaysAttack(u32 id) const;
  bool isChrEnArrangeFlagPGMax(u32 id) const;
  bool isChrEnArrangeFlagSalvage(u32 id) const;
  u32 getChrEnArrangeLinkRadius(u32 id) const;
  u32 getChrEnArrangeDetects(u32 id) const;
  u32 getChrEnArrangeSearchRange(u32 id) const;
  u32 getChrEnArrangeSearchAngle(u32 id) const;
  u32 getChrEnArrangeSearchRadius(u32 id) const;
  u32 getChrEnArrangeBatInterval(u32 id) const;
  u32 getChrEnArrangeBatArea(u32 id) const;
  u32 getChrEnArrangeBatAreaType(u32 id) const;
  u32 getChrEnArrangeAiGroup(u32 id) const;
  u32 getChrEnArrangeAiGroupNum(u32 id) const;
  u32 getChrEnArrangeBookID(u32 id) const;
  u32 getChrEnArrangeEnhanceID1(u32 id) const;
  u32 getChrEnArrangeEnhanceID2(u32 id) const;
  u32 getChrEnArrangeEnhanceID3(u32 id) const;
  u32 getChrEnArrangeParamRev(u32 id) const;
  u32 getChrEnArrangeRstDebuffRev(u32 id) const;
  u32 getChrEnArrangeHealPotTypeRev(u32 id) const;
  u32 getChrEnArrangeSummonID(u32 id) const;
  u32 getChrEnArrangeBGMID(u32 id) const;
  u32 getChrEnArrangeSeEnvID(u32 id) const;
  u32 getChrEnArrangeZoneID(u32 id) const;
  u32 getChrEnArrangeTimeSet(u32 id) const;
  u32 getChrEnArrangeWeatherSet(u32 id) const;
  u32 getChrEnArrangeDriverLev(u32 id) const;
  u32 getBTL_EnBookStart() const;
  u32 getBTL_EnBookEnd() const;
  u32 getBTL_EnBookBaseEnemyID(u32 id) const;
  u32 getBTL_EnBookBOOK_POP_TIME(u32 id) const;
  u32 getBTL_EnBookBOOK_popWeather(u32 id) const;
  bool searchByEnParamId(mm::mtl::FixedVector<u16, 128> &arranges, u32 paramId) const;

private:
  CBdatWrapper *m_chrEnArrange;
  CBdatWrapper *m_BTL_EnBook;
};

} // namespace gf
