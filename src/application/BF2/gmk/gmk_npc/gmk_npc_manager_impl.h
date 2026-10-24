#pragma once
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/game/quest/gf_quest_id.h"
#include "gmk/gmk_bdat.h"
#include "gmk/gmk_npc/gmk_npc_manager.h"
#include "types.h"

namespace gmk {

GmkNpcIdInfo::BdatInfo::BdatInfo() { dispose(); }

void GmkNpcIdInfo::BdatInfo::create(CBdatWrapper bdat, int id) {
  unknown00.unknown00 = bdat.getValCheck("QuestID", id, BDAT_TYPE_U16);
  unknown00.unknown02 = 0;
  unknown04 = bdat.getValCheck("ShopID", id, BDAT_TYPE_U16);
  unknown06 = bdat.getValCheck("MountPoint", id, BDAT_TYPE_U16);
  unknown08 = bdat.getValCheck("MountObject", id, BDAT_TYPE_U16);
  unknown0a = bdat.getValCheck("MountPoint2", id, BDAT_TYPE_U16);
  unknown0c = bdat.getValCheck("MountObject2", id, BDAT_TYPE_U16);
}

void GmkNpcIdInfo::BdatInfo::dispose() {
  unknown00.unknown00 = 0;
  unknown00.unknown02 = 0;
  unknown04 = 0;
  unknown06 = 0;
  unknown08 = 0;
  unknown0a = 0;
  unknown0c = 0;
}

GmkNpcManager::GmkNpcManager(u32 updateNpcNumPerFrame) : _30(), unknown34(updateNpcNumPerFrame), unknown38(0), unknown3c(true) { create(); }

} // namespace gmk
