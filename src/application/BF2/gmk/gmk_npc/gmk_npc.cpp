#include "gmk/gmk_npc/gmk_npc.h"

#include "gf/data/gf_bdat_wrapper.h"
#include "gmk/gmk_bdat.h"

namespace gmk {

void GmkNpc::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  unknown02 = bdat.getValCheck("Group", id, BDAT_TYPE_U16);
  unknown04 = bdat.getValCheck("BattleReaction", id, BDAT_TYPE_U16);
  if (unknown02 == 0) {
    unknown06 = ScenarioFlagCond(bdat.getValCheck("ScenarioFlagMin", id, BDAT_TYPE_U16), bdat.getValCheck("ScenarioFlagMax", id, BDAT_TYPE_U16));
    unknown0a = QuestFlagCond(bdat.getValCheck("QuestFlag", id, BDAT_TYPE_U16), bdat.getValCheck("QuestFlagMin", id, BDAT_TYPE_U8), bdat.getValCheck("QuestFlagMax", id, BDAT_TYPE_U8));
    u16 timeRange = bdat.getValCheck("TimeRange", id, BDAT_TYPE_U16);
    unknown10.unknown08 = timeRange;
    unknown00 = bdat.getValCheck("Condition", id, BDAT_TYPE_U16);
  }
  u16 visibleXZ = bdat.getValCheck("Visible_XZ", id, BDAT_TYPE_U16);
  u16 visibleY = bdat.getValCheck("Visible_Y", id, BDAT_TYPE_U16);
  unknown20.set(visibleXZ, visibleY);
  u16 invisibleXZ = DistHvCond::clampDepopDist(bdat.getValCheck("Invisible_XZ", id, BDAT_TYPE_U16), visibleXZ);
  u16 invisibleY = DistHvCond::clampDepopDist(bdat.getValCheck("Invisible_Y", id, BDAT_TYPE_U16), visibleY);
  unknown28.set(invisibleXZ, invisibleY);
}

void GmkNpc::BdatInfo::debugDraw(const AGmkBase &gmk) const {}

} // namespace gmk
