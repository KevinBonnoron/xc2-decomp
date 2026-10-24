#pragma once
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/game/quest/gf_quest_id.h"
#include "gmk/gmk_bdat.h"
#include "gmk/gmk_npc/gmk_npc_manager.h"
#include "types.h"

namespace gmk {

GmkNpcIdInfo::BdatInfo::BdatInfo() { dispose(); }

void GmkNpcIdInfo::BdatInfo::create(CBdatWrapper bdat, int id) {
  quest.unknown00 = bdat.getValCheck("QuestID", id, BDAT_TYPE_U16);
  quest.unknown02 = 0;
  shopId = bdat.getValCheck("ShopID", id, BDAT_TYPE_U16);
  mountPoint = bdat.getValCheck("MountPoint", id, BDAT_TYPE_U16);
  mountObject = bdat.getValCheck("MountObject", id, BDAT_TYPE_U16);
  mountPoint2 = bdat.getValCheck("MountPoint2", id, BDAT_TYPE_U16);
  mountObject2 = bdat.getValCheck("MountObject2", id, BDAT_TYPE_U16);
}

void GmkNpcIdInfo::BdatInfo::dispose() {
  quest.unknown00 = 0;
  quest.unknown02 = 0;
  shopId = 0;
  mountPoint = 0;
  mountObject = 0;
  mountPoint2 = 0;
  mountObject2 = 0;
}

GmkNpcManager::GmkNpcManager(u32 updateNpcNumPerFrame) : _30(), updateNpcNumPerFrame(updateNpcNumPerFrame), updateNpcIndex(0), isCreateGameEntity(true) { create(); }

} // namespace gmk
