#include "gmk/gmk_foot_print.h"

#include "gf/data/gf_bdat_wrapper.h"
#include "gf/game/gf_game_cond.h"
#include "gmk/gmk_bdat.h"

namespace gmk {

void GmkRoutedFootPrint::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  unknown00 = reinterpret_cast<const char *>(bdat.getValCheck("FootEffect", id, BDAT_TYPE_STRING));
  unknown0a = ScenarioFlagCond(bdat.getValCheck("ScenarioFlagMin", id, BDAT_TYPE_U16), bdat.getValCheck("ScenarioFlagMax", id, BDAT_TYPE_U16));
  unknown0e = QuestFlagCond(bdat.getValCheck("QuestFlag", id, BDAT_TYPE_U16), bdat.getValCheck("QuestFlagMin", id, BDAT_TYPE_U8), bdat.getValCheck("QuestFlagMax", id, BDAT_TYPE_U8));
  unknown08 = bdat.getValCheck("Condition", id, BDAT_TYPE_U16);
}

bool GmkRoutedFootPrint::BdatInfo::isPopCondMatched() const {
  if (unknown0a.isEnable() && !unknown0a.isMatch()) {
    return false;
  }
  if (unknown0e.isEnable() && !unknown0e.isMatch()) {
    return false;
  }
  if (unknown08 != 0 && !gf::GfGameCond::isGameCond(unknown08)) {
    return false;
  }
  return true;
}

} // namespace gmk
