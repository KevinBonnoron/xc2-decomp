#include "gmk/gmk_field_lock.h"
#include "gmk/gmk_list_impl.h" // IWYU pragma: keep

#include "gf/data/gf_bdat_wrapper.h"
#include "gf/game/gf_game_cond.h"
#include "gf/game/gf_game_manager.h"
#include "gmk/gmk_bdat.h"

namespace gmk {

template bool TGmkList<GmkFieldLock, GmkFieldLock::BdatInfo, 1129071686u, 2u, GmkFieldLockGob>::initGmkBdatInfo(GmkFieldLock::BdatInfo &, int &, const AGmkBase &);

void GmkFieldLock::debugDraw() const { isValid(); }

void GmkFieldLock::dispose() {
  unknown50.dispose();
  AGmkBase::dispose();
}

void GmkFieldLock::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  unknown06 = ScenarioFlagCond(bdat.getValCheck("ScenarioFlagMin", id, BDAT_TYPE_UNKNOWN_2), bdat.getValCheck("ScenarioFlagMax", id, BDAT_TYPE_UNKNOWN_2));
  unknown0a =
      QuestFlagCond(bdat.getValCheck("QuestFlag", id, BDAT_TYPE_UNKNOWN_2), bdat.getValCheck("QuestFlagMin", id, BDAT_TYPE_UNKNOWN_1), bdat.getValCheck("QuestFlagMax", id, BDAT_TYPE_UNKNOWN_1));
  unknown00 = bdat.getValCheck("Condition", id, BDAT_TYPE_UNKNOWN_2);
  unknown02 = bdat.getValCheck("rockTYPE", id, BDAT_TYPE_UNKNOWN_1);
  unknown04 = bdat.getValCheck("txtID", id, BDAT_TYPE_UNKNOWN_2);
}

bool GmkFieldLock::BdatInfo::isCondMatched() const {
  if (unknown06.isEnable() && !unknown06.isMatch()) {
    return false;
  }
  if (unknown0a.isEnable() && !unknown0a.isMatch()) {
    return false;
  }
  if (unknown00 != 0 && !gf::GfGameCond::isGameCond(unknown00)) {
    return false;
  }
  return true;
}

GmkFieldLock::GmkFieldLock() : unknownc0(1.0e12f) {}

void GmkFieldLock::create(const CreateInfo &info) { AGmkBase::create(info); }

void GmkFieldLock::update(f32 deltaTime) {
  debugUpdateMmf();
  if (!isValid()) {
    return;
  }
  if (unknown50.unknown60 && unknownc0 > 2.0f && gf::GfGameManager::isFieldLockMsgOK()) {
    reqDrawCmnMsg(getBdatInfo()->unknown04);
  }
  unknown50.update(deltaTime);
  if (unknown50.unknown62) {
    unknownc0 = 0.0f;
  } else {
    unknownc0 += deltaTime;
  }
  if (getBdatInfo()->isCondMatched()) {
    if (unknown50.unknown58 == nullptr) {
      createGmkCollision();
    }
  } else if (unknown50.unknown58 != nullptr) {
    unknown50.dispose();
  }
}

void GmkFieldLock::createGmkCollision() {
  if (!canCreateGameEntity()) {
    return;
  }
  unknown50.create(*this, getBdatInfo()->unknown02 == 0);
}

GmkType GmkFieldLock::getGmkType() const { return GMK_TYPE; }

} // namespace gmk

template void mm::mtl::Vector<gmk::GmkFieldLock::BdatInfo>::expand(size_t, size_t);

template void mm::mtl::Vector<gmk::GmkFieldLock::BdatInfo>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkFieldLock::BdatInfo>::resize(size_t);
template void mm::mtl::Vector<gmk::GmkFieldLock>::expand(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkFieldLock>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkFieldLock>::resize(size_t);
