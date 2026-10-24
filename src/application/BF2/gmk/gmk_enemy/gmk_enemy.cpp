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
  targetPointName = bdat.getValCheck("tagetpoint_name", id, BDAT_TYPE_U16);
  isPopSummon = Bdat::getFlagVal(bdat.unknown00, "flag", id, "pop_smn") != 0;
  displayRadius = getU8OrU16(bdat, "ene_disp_r", id);
  displayHeight = getU8OrU16(bdat, "ene_disp_h", id);
}

bool GmkEnemyList::BdatInfo::create() {
  u8 *mapList = gf::GfDataBdat::getFP(gf::BDAT_FLD_MAPLIST);
  if (mapList == nullptr) {
    mapId = -1;
    return false;
  }
  mapId = gf::GfGameManager::getMapID();
  if (mapId < Bdat::getIdTop(mapList) || Bdat::getIdTop(mapList) + Bdat::getIdCount(mapList) <= mapId) {
    mapId = -1;
    return false;
  }
  enemyDisplayRadius = Bdat::getValCheck(mapList, "ene_disp_r", mapId, BDAT_TYPE_U8);
  enemyDisplayHeight = Bdat::getValCheck(mapList, "ene_disp_h", mapId, BDAT_TYPE_U8);
  enemyReleaseRadius = Bdat::getValCheck(mapList, "ene_release_r", mapId, BDAT_TYPE_U8);
  enemyReleaseHeight = Bdat::getValCheck(mapList, "ene_release_h", mapId, BDAT_TYPE_U8);
  enemyRepopTime = Bdat::getValCheck(mapList, "e_repoptime", mapId, BDAT_TYPE_U8);
  return true;
}

} // namespace gmk
