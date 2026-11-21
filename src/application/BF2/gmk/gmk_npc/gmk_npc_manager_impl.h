#pragma once
#include "bdat.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/game/quest/gf_quest_id.h"
#include "gf/gf_allocator.h"
#include "gf/object/gf_obj_handle.h"
#include "gmk/gmk_bdat.h"
#include "gmk/gmk_npc/gmk_npc.h"
#include "gmk/gmk_npc/gmk_npc_manager.h"
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace gmk {

GmkNpcIdInfo::BdatInfo::BdatInfo() { dispose(); }

void GmkNpcIdInfo::BdatInfo::create(CBdatWrapper bdat, int id) {
  unknown00.unknown00 = bdat.getValCheck("QuestID", id, BDAT_TYPE_UNKNOWN_2);
  unknown00.unknown02 = 0;
  unknown04 = bdat.getValCheck("ShopID", id, BDAT_TYPE_UNKNOWN_2);
  unknown06 = bdat.getValCheck("MountPoint", id, BDAT_TYPE_UNKNOWN_2);
  unknown08 = bdat.getValCheck("MountObject", id, BDAT_TYPE_UNKNOWN_2);
  unknown0a = bdat.getValCheck("MountPoint2", id, BDAT_TYPE_UNKNOWN_2);
  unknown0c = bdat.getValCheck("MountObject2", id, BDAT_TYPE_UNKNOWN_2);
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

GmkNpcIdInfo::GmkNpcIdInfo(const CreateInfo *info) : unknown10(nullptr), unknown18(nullptr), unknown30(gf::unknown020) {
  if (info != nullptr) {
    create(*info);
  }
}

// __LINE__ must be 97 as in the original file: it is the line argument of the allocation (the game's operator new of
// GmkNpcIdInfo::create, inlined in GmkNpcManager::addGmkNpc, passes the line 0x61 of this header).
#line 94
void GmkNpcIdInfo::create(const CreateInfo &info) {
  dispose();
  unknown00 = info;
  unknown10 = new (gf::getAllocator(gf::ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) mm::mtl::IntrusiveList<AGmkNpc>;
}

GmkNpcManager::GmkNpcManager(u32 updateNpcNumPerFrame) : unknown30(0), unknown34(updateNpcNumPerFrame), unknown38(0), unknown3c(true) { create(); }

GmkNpcIdInfo *GmkNpcManager::getNpcIdInfoByNpcId(int npcId) { return &unknown08[getNpcIdInfoIdxFromNpcId(npcId)]; }

const GmkNpcIdInfo *GmkNpcManager::getNpcIdInfoByNpcId(int npcId) const { return &unknown08[getNpcIdInfoIdxFromNpcId(npcId)]; }

void GmkNpcManager::dispose() {
  unknown30 = 0;
  if (!unknown08.empty()) {
    for (GmkNpcIdInfo *it = unknown08.begin(); it != unknown08.end(); ++it) {
      it->dispose();
    }
  }
  unknown08.destroy();
}

void GmkNpcManager::removeGmkNpc(AGmkNpc *npc) {
  if (npc == nullptr) {
    return;
  }
  u8 *bdat = npc->getBindedBdatFp();
  int id = npc->getBindedBdatId();
  if (id < Bdat::getIdTop(bdat)) {
    return;
  }
  u16 npcId = Bdat::getValCheck(bdat, "NpcID", id, BDAT_TYPE_UNKNOWN_2);
  unknown08[getNpcIdInfoIdxFromNpcId(npcId)].removeGmkNpc(npc);
}

} // namespace gmk
