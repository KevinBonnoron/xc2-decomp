#include "gmk/gmk_blade.h"

#include "gf/data/gf_bdat_wrapper.h"
#include "gf/game/gf_game_cond.h"
#include "gf/game/gf_game_manager.h"
#include "gmk/gmk_bdat.h"

namespace gmk {

constexpr u16 BATTLE_REACTION_DEPOP = 0;
constexpr u16 BATTLE_REACTION_HIDE = 1;

void GmkBlade::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  bladeSizeCheck = bdat.getValCheck("BladeSizeCheck", id, BDAT_TYPE_U8);
  scenarioFlag = ScenarioFlagCond(bdat.getValCheck("ScenarioFlagMin", id, BDAT_TYPE_U16), bdat.getValCheck("ScenarioFlagMax", id, BDAT_TYPE_U16));
  u16 timeRange = bdat.getValCheck("TimeRange", id, BDAT_TYPE_U16);
  timeCond.timeRangeBits = timeRange;
  condition = bdat.getValCheck("Condition", id, BDAT_TYPE_U16);
  battleReaction = bdat.getValCheck("BattleReaction", id, BDAT_TYPE_U16);
  u16 visibleXZ = bdat.getValCheck("Visible_XZ", id, BDAT_TYPE_U16);
  u16 visibleY = bdat.getValCheck("Visible_Y", id, BDAT_TYPE_U16);
  popDist.set(visibleXZ, visibleY);
  u16 invisibleXZ = DistHvCond::clampDepopDist(bdat.getValCheck("Invisible_XZ", id, BDAT_TYPE_U16), visibleXZ);
  u16 invisibleY = DistHvCond::clampDepopDist(bdat.getValCheck("Invisible_Y", id, BDAT_TYPE_U16), visibleY);
  depopDist.set(invisibleXZ, invisibleY);
}

bool GmkBlade::BdatInfo::isPopCondMatched(const mm::Vec3 &position) const {
  if (scenarioFlag.isEnable() && !scenarioFlag.isMatch()) {
    return false;
  }
  if (timeCond.isEnable() && !timeCond.isMatch()) {
    return false;
  }
  if (condition != 0 && !gf::GfGameCond::isGameCond(condition)) {
    return false;
  }
  if (gf::GfGameManager::isBattle() && battleReaction == BATTLE_REACTION_HIDE) {
    return false;
  }
  if (!popDist.isMatch(position)) {
    return false;
  }
  if (gf::GfGameManager::isBattle() && battleReaction == BATTLE_REACTION_DEPOP) {
    return false;
  }
  return true;
}

bool GmkBlade::BdatInfo::isPopCommonCondMatched() const {
  if (scenarioFlag.isEnable() && !scenarioFlag.isMatch()) {
    return false;
  }
  if (timeCond.isEnable() && !timeCond.isMatch()) {
    return false;
  }
  if (condition != 0 && !gf::GfGameCond::isGameCond(condition)) {
    return false;
  }
  if (gf::GfGameManager::isBattle() && battleReaction == BATTLE_REACTION_HIDE) {
    return false;
  }
  return true;
}

bool GmkBlade::BdatInfo::isDepopCondMatched(const mm::Vec3 &position) const {
  if (!isPopCommonCondMatched()) {
    return true;
  }
  return !depopDist.isMatch(position);
}

} // namespace gmk
