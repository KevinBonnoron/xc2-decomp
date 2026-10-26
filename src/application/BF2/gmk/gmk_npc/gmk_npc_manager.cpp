#include "gmk/gmk_npc/gmk_npc_manager.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "gmk/gmk_npc/gmk_npc.h"
#include "mm_mtl/intrusive_list.h"

namespace gmk {

int GmkNpcManager::getNpcIdInfoIdxFromNpcId(int npcId) {
  u8 *chrDr = gf::GfDataBdat::getFP(gf::BDAT_CHR_DR);
  u8 *chrBl = gf::GfDataBdat::getFP(gf::BDAT_CHR_BL);
  u8 *npcList = gf::GfDataBdat::getFP(gf::BDAT_RSC_NPC_LIST);
  if (Bdat::getIdTop(chrDr) <= npcId && npcId < Bdat::getIdTop(chrDr) + Bdat::getIdCount(chrDr)) {
    return npcId - Bdat::getIdTop(chrDr);
  }
  if (Bdat::getIdTop(chrBl) <= npcId && npcId < Bdat::getIdTop(chrBl) + Bdat::getIdCount(chrBl)) {
    return Bdat::getIdCount(chrDr) + npcId - Bdat::getIdTop(chrBl);
  }
  int drCount = Bdat::getIdCount(chrDr);
  int blCount = Bdat::getIdCount(chrBl);
  int listTop = Bdat::getIdTop(npcList);
  return drCount + npcId + blCount - listTop;
}

void GmkNpcIdInfo::addGmkNpc(AGmkNpc *npc) {
  for (mm::mtl::IntrusiveList<AGmkNpc>::iterator position = unknown10->begin(); position != unknown10->end(); ++position) {
    if (position.get()->getBindedBdatId() >= npc->getBindedBdatId()) {
      unknown10->insert(position, npc);
      break;
    }
  }
  if (!npc->intoNode()) {
    unknown10->push_back(npc);
  }
  npc->unknown18 = this;
}

// Inferred role: destroys the game object right away and activates the first NPC whose pop condition is matched; original name unknown.
inline void GmkNpcIdInfo::unknown001() {
  unknown18->unbindToGameObj(unknown30);
  gf::GfObjUtil::destroy(unknown30);
  unknown30 = gf::INVALID_HANDLE;
  unknown18 = nullptr;
  for (mm::mtl::IntrusiveList<AGmkNpc>::iterator it = unknown10->begin(); it != unknown10->end(); ++it) {
    if (it.get()->isPopCondMatched()) {
      setActiveGmkNpc(it.get());
      break;
    }
  }
}

void GmkNpcIdInfo::dispose() {
  if (unknown30 != gf::INVALID_HANDLE) {
    unknown001();
  }
  setActiveGmkNpc(nullptr);
  if (unknown10 != nullptr) {
    delete unknown10;
    unknown10 = nullptr;
  }
  unknown00 = 0;
  unknown08 = nullptr;
}

void GmkNpcIdInfo::removeGmkNpc(AGmkNpc *npc) {
  if (npc == nullptr) {
    return;
  }
  npc->unknown18 = nullptr;
  if (unknown18 == npc) {
    if (unknown30 != gf::INVALID_HANDLE) {
      unknown001();
    }
    unknown18 = nullptr;
  }
  unknown10->erase(npc);
}

} // namespace gmk
