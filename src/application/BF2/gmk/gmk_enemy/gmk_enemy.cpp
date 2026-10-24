#include "gmk/gmk_enemy/gmk_enemy.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/game/gf_game_manager.h"
#include "gmk/gmk_bdat.h"

namespace gmk {

static u32 getU8OrU16(const CBdatWrapper &bdat, const char *name, int id) {
  if (Bdat::getVarType(bdat.unknown00, name) == BDAT_TYPE_U16) {
    return static_cast<u16>(bdat.getValCheck(name, id, BDAT_TYPE_U16));
  }
  return static_cast<u8>(bdat.getValCheck(name, id, BDAT_TYPE_U8));
}

void GmkEnemy::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  unknown00 = bdat.getValCheck("tagetpoint_name", id, BDAT_TYPE_U16);
  unknown02 = Bdat::getFlagVal(bdat.unknown00, "flag", id, "pop_smn") != 0;
  unknown04 = getU8OrU16(bdat, "ene_disp_r", id);
  unknown06 = getU8OrU16(bdat, "ene_disp_h", id);
}

bool GmkEnemyList::BdatInfo::create() {
  u8 *mapList = gf::GfDataBdat::getFP(gf::BDAT_FLD_MAPLIST);
  if (mapList == nullptr) {
    unknown00 = -1;
    return false;
  }
  unknown00 = gf::GfGameManager::getMapID();
  if (unknown00 < Bdat::getIdTop(mapList) || Bdat::getIdTop(mapList) + Bdat::getIdCount(mapList) <= unknown00) {
    unknown00 = -1;
    return false;
  }
  unknown04 = Bdat::getValCheck(mapList, "ene_disp_r", unknown00, BDAT_TYPE_U8);
  unknown05 = Bdat::getValCheck(mapList, "ene_disp_h", unknown00, BDAT_TYPE_U8);
  unknown06 = Bdat::getValCheck(mapList, "ene_release_r", unknown00, BDAT_TYPE_U8);
  unknown07 = Bdat::getValCheck(mapList, "ene_release_h", unknown00, BDAT_TYPE_U8);
  unknown08 = Bdat::getValCheck(mapList, "e_repoptime", unknown00, BDAT_TYPE_U8);
  return true;
}

} // namespace gmk
