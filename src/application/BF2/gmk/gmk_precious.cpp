#include "gmk/gmk_precious.h"

#include "gf/data/gf_bdat_wrapper.h"
#include "gf/game/gf_game_cond.h"
#include "gf/util/gf_item_util.h"
#include "gmk/gmk_bdat.h"

namespace gmk {

void GmkPrecious::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  dispose();
  unknown00 = bdat.getValCheck("itmID", id, BDAT_TYPE_U16);
  gf::GfItemUtil::isPrecious(unknown00);
  unknown02 = bdat.getValCheck("Condition", id, BDAT_TYPE_U16);
  unknown04 = bdat.getValCheck("QuestID", id, BDAT_TYPE_U16);
  unknown06 = ScenarioFlagCond(bdat.getValCheck("ScenarioFlagMin", id, BDAT_TYPE_U16), bdat.getValCheck("ScenarioFlagMax", id, BDAT_TYPE_U16));
  unknown0a = QuestFlagCond(bdat.getValCheck("QuestFlag", id, BDAT_TYPE_U16), bdat.getValCheck("QuestFlagMin", id, BDAT_TYPE_U8), bdat.getValCheck("QuestFlagMax", id, BDAT_TYPE_U8));
  unknown10.unknown08 = bdat.getValCheck("POP_TIME", id, BDAT_TYPE_U32);
  unknown20.unknown08 = bdat.getValCheck("popWeather", id, BDAT_TYPE_U8);
}

void GmkPrecious::BdatInfo::dispose() { unknown00 = 0; }

bool GmkPrecious::BdatInfo::isPopCondMatched() const {
  if (unknown06.isEnable() && !unknown06.isMatch()) {
    return false;
  }
  if (unknown0a.isEnable() && !unknown0a.isMatch()) {
    return false;
  }
  if (unknown10.isEnable() && !unknown10.isMatch()) {
    return false;
  }
  if (unknown20.isEnable() && !unknown20.isMatch()) {
    return false;
  }
  if (unknown02 != 0 && !gf::GfGameCond::isGameCond(unknown02)) {
    return false;
  }
  return true;
}

} // namespace gmk
