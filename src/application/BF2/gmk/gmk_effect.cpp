#include "gmk/gmk_effect.h"

#include "framework/effect/effect_manager.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/game/gf_game_cond.h"
#include "gmk/gmk_bdat.h"

namespace gmk {

void GmkEffect::debugDraw() const { isValid(); }

void GmkEffect::debugUpdateMmf() {}

void GmkEffect::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  unknown02 = ScenarioFlagCond(bdat.getValCheck("ScenarioFlagMin", id, BDAT_TYPE_U16), bdat.getValCheck("ScenarioFlagMax", id, BDAT_TYPE_U16));
  unknown06 = QuestFlagCond(bdat.getValCheck("QuestFlag", id, BDAT_TYPE_U16), bdat.getValCheck("QuestFlagMin", id, BDAT_TYPE_U8), bdat.getValCheck("QuestFlagMax", id, BDAT_TYPE_U8));
  unknown00 = bdat.getValCheck("Condition", id, BDAT_TYPE_U16);
}

bool GmkEffect::BdatInfo::isPopCondMatched() const {
  if (unknown02.isEnable() && !unknown02.isMatch()) {
    return false;
  }
  if (unknown06.isEnable() && !unknown06.isMatch()) {
    return false;
  }
  if (unknown00 != 0 && !gf::GfGameCond::isGameCond(unknown00)) {
    return false;
  }
  return true;
}

GmkType GmkEffectLocator::getGmkType() const { return GMK_TYPE; }

bool GmkEffectLocator::isValid() const { return unknown08.unknown00 != nullptr && unknown20.unknown08 != nullptr; }

GmkType GmkEffect::getGmkType() const { return GMK_TYPE; }

void GmkEffect::dispose() {
  unknownB8_0 = false;
  unknownB8_1 = false;
  unknownB8_2 = false;
  if (unknownAC != 0) {
    fw::EffectManager::get()->remove(unknownAC);
    unknownAC = 0;
  }
  AGmkBase::dispose();
  unknown90 = nullptr;
  unknownA0 = nullptr;
}

void GmkEffect::validateDisp() const {
  if (unknownAC == 0) {
    return;
  }
  bool isDisp = unknownB0 && debugIsDispGmkType(getGmkType());
  fw::EffectManager::get()->setDisp(unknownAC, isDisp);
}

bool GmkEffect::canPopInst() const {
  if (unknownAC != 0) {
    return false;
  }
  if (!unknownB8_0) {
    return false;
  }
  return unknownB8_1;
}

bool GmkEffect::canDepopInst() const {
  if (unknownAC == 0) {
    return false;
  }
  if (!unknownB8_0) {
    return true;
  }
  return unknownB8_2;
}

} // namespace gmk
