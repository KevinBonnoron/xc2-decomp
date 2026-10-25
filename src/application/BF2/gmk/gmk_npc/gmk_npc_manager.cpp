#include "gmk/gmk_npc/gmk_npc_manager.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"

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

} // namespace gmk
