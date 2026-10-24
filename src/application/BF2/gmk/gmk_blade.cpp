#include "gmk/gmk_blade.h"

#include "gf/data/gf_bdat_wrapper.h"
#include "gf/game/gf_game_cond.h"
#include "gf/game/gf_game_manager.h"
#include "gmk/gmk_bdat.h"

namespace gmk {

constexpr u16 BATTLE_REACTION_DEPOP = 0;
constexpr u16 BATTLE_REACTION_HIDE = 1;

void GmkBlade::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  unknown00 = bdat.getValCheck("BladeSizeCheck", id, BDAT_TYPE_U8);
  unknown06 = ScenarioFlagCond(bdat.getValCheck("ScenarioFlagMin", id, BDAT_TYPE_U16), bdat.getValCheck("ScenarioFlagMax", id, BDAT_TYPE_U16));
  u16 timeRange = bdat.getValCheck("TimeRange", id, BDAT_TYPE_U16);
  unknown10.unknown08 = timeRange;
  unknown02 = bdat.getValCheck("Condition", id, BDAT_TYPE_U16);
  unknown04 = bdat.getValCheck("BattleReaction", id, BDAT_TYPE_U16);
  u16 visibleXZ = bdat.getValCheck("Visible_XZ", id, BDAT_TYPE_U16);
  u16 visibleY = bdat.getValCheck("Visible_Y", id, BDAT_TYPE_U16);
  unknown20.set(visibleXZ, visibleY);
  u16 invisibleXZ = DistHvCond::clampDepopDist(bdat.getValCheck("Invisible_XZ", id, BDAT_TYPE_U16), visibleXZ);
  u16 invisibleY = DistHvCond::clampDepopDist(bdat.getValCheck("Invisible_Y", id, BDAT_TYPE_U16), visibleY);
  unknown28.set(invisibleXZ, invisibleY);
}

bool GmkBlade::BdatInfo::isPopCondMatched(const mm::Vec3 &position) const {
  if (unknown06.isEnable() && !unknown06.isMatch()) {
    return false;
  }
  if (unknown10.isEnable() && !unknown10.isMatch()) {
    return false;
  }
  if (unknown02 != 0 && !gf::GfGameCond::isGameCond(unknown02)) {
    return false;
  }
  if (gf::GfGameManager::isBattle() && unknown04 == BATTLE_REACTION_HIDE) {
    return false;
  }
  if (!unknown20.isMatch(position)) {
    return false;
  }
  if (gf::GfGameManager::isBattle() && unknown04 == BATTLE_REACTION_DEPOP) {
    return false;
  }
  return true;
}

bool GmkBlade::BdatInfo::isPopCommonCondMatched() const {
  if (unknown06.isEnable() && !unknown06.isMatch()) {
    return false;
  }
  if (unknown10.isEnable() && !unknown10.isMatch()) {
    return false;
  }
  if (unknown02 != 0 && !gf::GfGameCond::isGameCond(unknown02)) {
    return false;
  }
  if (gf::GfGameManager::isBattle() && unknown04 == BATTLE_REACTION_HIDE) {
    return false;
  }
  return true;
}

bool GmkBlade::BdatInfo::isDepopCondMatched(const mm::Vec3 &position) const {
  if (!isPopCommonCondMatched()) {
    return true;
  }
  return !unknown28.isMatch(position);
}

} // namespace gmk
