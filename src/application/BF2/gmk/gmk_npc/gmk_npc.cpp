#include "gmk/gmk_npc/gmk_npc.h"

#include "gf/data/gf_bdat_wrapper.h"
#include "gmk/gmk_bdat.h"

namespace gmk {

void GmkNpc::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  group = bdat.getValCheck("Group", id, BDAT_TYPE_U16);
  battleReaction = bdat.getValCheck("BattleReaction", id, BDAT_TYPE_U16);
  if (group == 0) {
    scenarioFlag = ScenarioFlagCond(bdat.getValCheck("ScenarioFlagMin", id, BDAT_TYPE_U16), bdat.getValCheck("ScenarioFlagMax", id, BDAT_TYPE_U16));
    questFlag = QuestFlagCond(bdat.getValCheck("QuestFlag", id, BDAT_TYPE_U16),
                              bdat.getValCheck("QuestFlagMin", id, BDAT_TYPE_U8),
                              bdat.getValCheck("QuestFlagMax", id, BDAT_TYPE_U8));
    u16 timeRange = bdat.getValCheck("TimeRange", id, BDAT_TYPE_U16);
    timeCond.timeRangeBits = timeRange;
    condition = bdat.getValCheck("Condition", id, BDAT_TYPE_U16);
  }
  u16 visibleXZ = bdat.getValCheck("Visible_XZ", id, BDAT_TYPE_U16);
  u16 visibleY = bdat.getValCheck("Visible_Y", id, BDAT_TYPE_U16);
  popDist.set(visibleXZ, visibleY);
  u16 invisibleXZ = DistHvCond::clampDepopDist(bdat.getValCheck("Invisible_XZ", id, BDAT_TYPE_U16), visibleXZ);
  u16 invisibleY = DistHvCond::clampDepopDist(bdat.getValCheck("Invisible_Y", id, BDAT_TYPE_U16), visibleY);
  depopDist.set(invisibleXZ, invisibleY);
}

void GmkNpc::BdatInfo::debugDraw(const AGmkBase &gmk) const {}

} // namespace gmk
