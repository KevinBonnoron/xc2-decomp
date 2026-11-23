#include "gmk/gmk_event.h"
#include "gmk/gmk_list_impl.h" // IWYU pragma: keep

#include "gf/data/gf_bdat_wrapper.h"
#include "gf/game/gf_game_cond.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/sequential_play/gf_play_factory.h"
#include "gf/scom/gf_scom_obj.h"
#include "gmk/gmk_active_list.h"
#include "gmk/gmk_bdat.h"
#include "gmk/gmk_set.h"

namespace gmk {

template bool TGmkList<GmkEvent, GmkEvent::BdatInfo, 1414420037u, 4u, GmkEventGob>::initGmkBdatInfo(GmkEvent::BdatInfo &, int &, const AGmkBase &);

template class TGmkActiveList<GmkEvent>;

GmkEvent::GmkEvent() : IntrusiveListNode(), m_gmkPhantom(nullptr), unknownf0(false), unknownf1(false), unknownf2(false) {}

void GmkEvent::debugDraw() const { isValid(); }

void GmkEvent::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  m_scenarioFlagCond = ScenarioFlagCond(bdat.getValCheck("ScenarioFlagMin", id, BDAT_TYPE_UNKNOWN_2), bdat.getValCheck("ScenarioFlagMax", id, BDAT_TYPE_UNKNOWN_2));
  m_questFlagCond =
      QuestFlagCond(bdat.getValCheck("QuestFlag", id, BDAT_TYPE_UNKNOWN_2), bdat.getValCheck("QuestFlagMin", id, BDAT_TYPE_UNKNOWN_1), bdat.getValCheck("QuestFlagMax", id, BDAT_TYPE_UNKNOWN_1));
  unknown00 = bdat.getValCheck("Condition", id, BDAT_TYPE_UNKNOWN_2);
  unknown02 = bdat.getValCheck("EventID", id, BDAT_TYPE_UNKNOWN_2);
  unknown04 = bdat.getValCheck("Icon", id, BDAT_TYPE_UNKNOWN_2);
}

bool GmkEvent::BdatInfo::isCondMatched() const {
  if (m_scenarioFlagCond.isEnable() && !m_scenarioFlagCond.isMatch()) {
    return false;
  }
  if (m_questFlagCond.isEnable() && !m_questFlagCond.isMatch()) {
    return false;
  }
  if (unknown00 != 0 && !gf::GfGameCond::isGameCond(unknown00)) {
    return false;
  }
  return true;
}

void GmkEvent::beginEvent() {
  if (!unknownf1 && gf::GfPlayFactory::createOneEventForGimmick(m_createInfo.unknown10->unknown02)) {
    unknownf1 = true;
    unknownf2 = false;
    gf::SCOM_QUEST_REACH::createArrivePlace(m_createInfo.unknown18);
  }
}

void GmkEvent::disposeGmkPhantom() {
  if (this != nullptr && intoNode() && TGmkActiveList<GmkEvent>::get() != nullptr) {
    TGmkActiveList<GmkEvent>::get()->unknown08.erase(this);
  }
  m_gmkPhantom.dispose();
}

void GmkEvent::update(f32 deltaTime) {
  debugUpdateMmf();
  if (!isValid()) {
    return;
  }
  bool isCondMatched = unknown001()->isCondMatched();
  if (unknownf0 != isCondMatched) {
    if (isCondMatched) {
      createGmkPhantom();
    } else {
      disposeGmkPhantom();
    }
    unknownf0 = isCondMatched;
  }
  if (m_gmkPhantom.unknown83) {
    unknownf2 = true;
  }
  if (unknownf1 && gf::GfGameManager::isControlFree()) {
    unknownf1 = false;
  }
}

// The game tests the result of isPlayEventOK (1.0.0: 0x7100319a4c) with `tbz w0, #0` (here 0x71005fddbc, the body of this function), while the
// callee returns the property flag as it loads it (`ldrb w0`, no extension): a plain conversion of the u8 gives `and w8, w0, #0xff; cbz` (55
// instead of 54 instructions) and a bool return type of the callee gives `cmp; cset` in the callee.
void GmkEvent::updateInActiveList(f32 deltaTime) {
  if (m_gmkPhantom.unknown83 && unknown001()->isCondMatched() && (gf::GfGameManager::isPlayEventOK() & 1) != 0) {
    beginEvent();
  }
}

void GmkEvent::createGmkPhantom() {
  const GmkSet *set = AGmkBase::m_createBaseInfo.m_ownerGmkEnemyList->getCreateInfo().m_gmkSet;
  if (set != nullptr && set->m_createInfo.unknown24) {
    return;
  }
  m_gmkPhantom.create(*this, nullptr, false);
  TGmkActiveList<GmkEvent>::unknown002(this);
}

void GmkEvent::create(const CreateInfo &info) { AGmkBase::create(info); }

void GmkEvent::dispose() {
  unknownf2 = false;
  unknownf0 = false;
  unknownf1 = false;
  disposeGmkPhantom();
  AGmkBase::dispose();
}

GmkType GmkEvent::getGmkType() const { return GMK_TYPE; }

} // namespace gmk

template void mm::mtl::Vector<gmk::GmkEvent::BdatInfo>::expand(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkEvent::BdatInfo>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkEvent::BdatInfo>::resize(size_t);
template void mm::mtl::Vector<gmk::GmkEvent>::expand(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkEvent>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkEvent>::resize(size_t);
