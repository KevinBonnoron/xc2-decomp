#include "gmk/gmk_blade.h"

#include "gf/data/gf_bdat_wrapper.h"
#include "gf/game/gf_game_cond.h"
#include "gf/game/gf_game_manager.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
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

GmkType GmkBlade::getGmkType() const { return GMK_TYPE; }

void GmkBlade::validateDisp() const {
  if (unknown48 == gf::INVALID_HANDLE) {
    return;
  }
  setEventDisp(unknown48, unknown55 && debugIsDispGmkType(getGmkType()));
}

void GmkBlade::dispose() {
  if (unknown48 != gf::INVALID_HANDLE) {
    unbindToGameObj(unknown48);
    gf::GfObjUtil::destroy(unknown48);
    unknown48 = gf::INVALID_HANDLE;
  }
  AGmkBase::dispose();
}

void GmkBlade::disposeGobInst(bool isFadeOut) {
  if (unknown48 == gf::INVALID_HANDLE) {
    return;
  }
  if (isFadeOut) {
    gmk::disposeGobInst(unknown48, 1.0f);
  } else {
    unbindToGameObj(unknown48);
    gf::GfObjUtil::destroy(unknown48);
    unknown48 = gf::INVALID_HANDLE;
  }
}

bool GmkBlade::canPopGobInst() const {
  if (unknown48 != gf::INVALID_HANDLE || unknown50 == 0) {
    return false;
  }
  return getBdatInfo()->isPopCondMatched(unknown08.unknown08->unknown00);
}

bool GmkBlade::canDepopGobInst() const {
  if (!unknown54) {
    if (unknown48 == gf::INVALID_HANDLE) {
      return false;
    }
    if (unknown50 != 0) {
      return getBdatInfo()->isDepopCondMatched(unknown08.unknown08->unknown00);
    }
  }
  return true;
}

} // namespace gmk
