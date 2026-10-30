#include "gmk/gmk_effect.h"

#include "framework/effect/effect_manager.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/field/gf_field_manager.h"
#include "gf/game/gf_game_cond.h"
#include "gmk/gmk_bdat.h"
#include "gmk/gmk_list_impl.h" // IWYU pragma: keep

namespace fw {
class EffectPack;
enum EF_CATEGORY : int;
} // namespace fw

namespace gmk {

template bool TGmkList<GmkEffect, GmkEffect::BdatInfo, 1413695045u, 8u, GmkEffectGobCustom>::initGmkBdatInfo(GmkEffect::BdatInfo &, int &, const AGmkBase &);
template bool TGmkList<GmkEffectLocator, GmkEffectLocator::BdatInfo, 1129072197u, 1u, GmkEffectLocatorGob>::initGmkBdatInfo(GmkEffectLocator::BdatInfo &, int &, const AGmkBase &);

GmkEffect::GmkEffect()
    : unknown48(0), unknown90(nullptr), unknowna0(nullptr), unknowna8(false), unknownac(0), unknownb0(true), unknownB8_0(false), unknownB8_1(false), unknownB8_2(false), unknownB8_3(0),
      unknownc0(false), unknownc1(false) {}

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
  if (unknownac != 0) {
    fw::EffectManager::get()->remove(unknownac);
    unknownac = 0;
  }
  AGmkBase::dispose();
  unknown90 = nullptr;
  unknowna0 = nullptr;
}

void GmkEffect::update(f32 deltaTime) {
  debugUpdateMmf();
  if (!isValid()) {
    return;
  }
  updatePopDepopCond();
  if (unknown90) {
    (this->*unknown90)(deltaTime);
  }
}

void GmkEffect::seqValidateResHandle(f32 deltaTime) {
  fw::EffectPack *pack = gf::GfFieldManager::getEffectPack();
  if (pack != nullptr) {
    const char *name = getData()->unknown00;
    unknowna0 = fw::EffectManager::get()->search(name, pack);
    if (unknowna0 != nullptr) {
      unknowna8 = fw::EffectManager::get()->containsCamAxis(unknowna0);
      unknown90 = &GmkEffect::seqUpdate;
    }
  }
}

void GmkEffect::createInst() {
  if (!canCreateGameEntity()) {
    return;
  }
  unknownac = fw::EffectManager::get()->create(unknowna0, true);
  fw::EffectManager::get()->setCategory(unknownac, static_cast<fw::EF_CATEGORY>(1));
  applyEffectParam(false);
}

void GmkEffect::validateDisp() const {
  if (unknownac == 0) {
    return;
  }
  bool isDisp = unknownb0 && debugIsDispGmkType(getGmkType());
  fw::EffectManager::get()->setDisp(unknownac, isDisp);
}

bool GmkEffect::canPopInst() const {
  if (unknownac != 0) {
    return false;
  }
  if (!unknownB8_0) {
    return false;
  }
  return unknownB8_1;
}

bool GmkEffect::canDepopInst() const {
  if (unknownac == 0) {
    return false;
  }
  if (!unknownB8_0) {
    return true;
  }
  return unknownB8_2;
}

} // namespace gmk

template void mm::mtl::Vector<gmk::GmkEffect::BdatInfo>::expand(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkEffect::BdatInfo>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkEffect::BdatInfo>::resize(size_t);
template void mm::mtl::Vector<gmk::GmkEffectLocator::BdatInfo>::expand(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkEffectLocator::BdatInfo>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkEffectLocator::BdatInfo>::resize(size_t);
template void mm::mtl::Vector<gmk::GmkEffectLocator>::expand(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkEffectLocator>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkEffectLocator>::resize(size_t);
