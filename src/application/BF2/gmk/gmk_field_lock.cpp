#include "gmk/gmk_field_lock.h"
#include "gmk/gmk_list_impl.h" // IWYU pragma: keep

#include "gf/data/gf_bdat_wrapper.h"
#include "gf/game/gf_game_cond.h"
#include "gmk/gmk_bdat.h"

namespace gmk {

template bool TGmkList<GmkFieldLock, GmkFieldLock::BdatInfo, 1129071686u, 2u, GmkFieldLockGob>::initGmkBdatInfo(GmkFieldLock::BdatInfo &, int &, const AGmkBase &);

void GmkFieldLock::debugDraw() const { isValid(); }

void GmkFieldLock::dispose() {
  unknown50.dispose();
  AGmkBase::dispose();
}

void GmkFieldLock::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  unknown06 = ScenarioFlagCond(bdat.getValCheck("ScenarioFlagMin", id, BDAT_TYPE_U16), bdat.getValCheck("ScenarioFlagMax", id, BDAT_TYPE_U16));
  unknown0a = QuestFlagCond(bdat.getValCheck("QuestFlag", id, BDAT_TYPE_U16), bdat.getValCheck("QuestFlagMin", id, BDAT_TYPE_U8), bdat.getValCheck("QuestFlagMax", id, BDAT_TYPE_U8));
  unknown00 = bdat.getValCheck("Condition", id, BDAT_TYPE_U16);
  unknown02 = bdat.getValCheck("rockTYPE", id, BDAT_TYPE_U8);
  unknown04 = bdat.getValCheck("txtID", id, BDAT_TYPE_U16);
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

void GmkFieldLock::create(const CreateInfo &info) { AGmkBase::create(info); }

GmkType GmkFieldLock::getGmkType() const { return GMK_TYPE; }

} // namespace gmk
