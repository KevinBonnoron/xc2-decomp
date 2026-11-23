#include "gmk/gmk_map_jump.h"
#include "gmk/gmk_list_impl.h" // IWYU pragma: keep

#include "gf/data/gf_bdat_wrapper.h"
#include "gf/game/gf_game_cond.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/sequential_play/gf_play_factory.h"
#include "gf/request/gf_req_command.h"
#include "gmk/gmk_bdat.h"

namespace gmk {

template bool TGmkList<GmkMapJump, GmkMapJump::BdatInfo, 1347047501u, 2u, GmkMapJumpGob>::initGmkBdatInfo(GmkMapJump::BdatInfo &, int &, const AGmkBase &);

GmkMapJump::GmkMapJump() : m_gmkPhantom(nullptr), unknowne0(false), unknowne1(false) {}

void GmkMapJump::debugDraw() const { isValid(); }

void GmkMapJump::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  unknown00 = bdat.getValCheck("MapJumpId", id, BDAT_TYPE_UNKNOWN_2);
  m_scenarioFlagCond = ScenarioFlagCond(bdat.getValCheck("ScenarioFlagMin", id, BDAT_TYPE_UNKNOWN_2), bdat.getValCheck("ScenarioFlagMax", id, BDAT_TYPE_UNKNOWN_2));
  m_questFlagCond =
      QuestFlagCond(bdat.getValCheck("QuestFlag", id, BDAT_TYPE_UNKNOWN_2), bdat.getValCheck("QuestFlagMin", id, BDAT_TYPE_UNKNOWN_1), bdat.getValCheck("QuestFlagMax", id, BDAT_TYPE_UNKNOWN_1));
  unknown02 = bdat.getValCheck("Condition", id, BDAT_TYPE_UNKNOWN_2);
}

bool GmkMapJump::BdatInfo::isCondMatched() const {
  if (m_scenarioFlagCond.isEnable() && !m_scenarioFlagCond.isMatch()) {
    return false;
  }
  if (m_questFlagCond.isEnable() && !m_questFlagCond.isMatch()) {
    return false;
  }
  if (unknown02 != 0 && !gf::GfGameCond::isGameCond(unknown02)) {
    return false;
  }
  return true;
}

GmkType GmkMapJump::getGmkType() const { return GMK_TYPE; }

void GmkMapJump::createGmkPhantom() {
  if (canCreateGameEntity()) {
    m_gmkPhantom.create(*this, nullptr, false);
  }
}

void GmkMapJump::dispose() {
  m_gmkPhantom.dispose();
  AGmkBase::dispose();
}

void GmkMapJump::update(f32 deltaTime) {
  debugUpdateMmf();
  if (!isValid()) {
    return;
  }
  bool isCondMatched = getBdatInfo()->isCondMatched();
  if (unknowne0 != isCondMatched) {
    if (isCondMatched) {
      createGmkPhantom();
    } else {
      m_gmkPhantom.dispose();
    }
    unknowne0 = isCondMatched;
  }
  if (m_gmkPhantom.unknown83) {
    beginEvent();
  } else {
    endEvent();
  }
}

void GmkMapJump::beginEvent() {
  if (!unknowne1 && gf::GfGameManager::isMapjumpOK()) {
    unknowne1 = true;
    gf::GfMapjumpInfo info(getBdatInfo()->unknown00);
    gf::GfPlayFactory::createMapjump(info);
  }
}

void GmkMapJump::endEvent() {
  if (unknowne1) {
    unknowne1 = false;
  }
}

} // namespace gmk

template void mm::mtl::Vector<gmk::GmkMapJump::BdatInfo>::expand(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkMapJump::BdatInfo>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkMapJump::BdatInfo>::resize(size_t);
template void mm::mtl::Vector<gmk::GmkMapJump>::expand(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkMapJump>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkMapJump>::resize(size_t);
