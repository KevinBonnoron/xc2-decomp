#include "gmk/gmk_grave.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/game/gf_game_manager.h"
#include "gmk/gmk_bdat.h"
#include "gmk/gmk_set.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace gmk {

void GmkGrave::BdatInfo::create(u8 *bdat, int id, const AGmkBase &gmk) {
  dispose();
  enemyPopId = Bdat::getValCheck(bdat, "en_popID", id, BDAT_TYPE_U16);
  u8 *mapList = gf::GfDataBdat::getFP(gf::BDAT_FLD_MAPLIST);
  if (mapList != nullptr) {
    int map = gf::GfGameManager::getMapID();
    if (map >= Bdat::getIdTop(mapList) && Bdat::getIdTop(mapList) + Bdat::getIdCount(mapList) > map) {
      u8 displayRadius = Bdat::getValCheck(mapList, "ene_disp_r", map, BDAT_TYPE_U8);
      u8 displayHeight = Bdat::getValCheck(mapList, "ene_disp_h", map, BDAT_TYPE_U8);
      popDist.set(displayRadius, displayHeight);
      u8 releaseRadius = Bdat::getValCheck(mapList, "ene_release_r", map, BDAT_TYPE_U8);
      u8 releaseHeight = Bdat::getValCheck(mapList, "ene_release_h", map, BDAT_TYPE_U8);
      depopDist.set(displayRadius + releaseRadius, displayHeight + releaseHeight);
      const GmkSet *set = gmk.baseInfo.list->getCreateInfo().set;
      u8 *enemyBdat;
      if (set->lists[GMK_TYPE_ENEMY] == nullptr || (enemyBdat = set->lists[GMK_TYPE_ENEMY]->getBindedBdatFp()) == nullptr) {
        if (set->lists[GMK_TYPE_ROUTED_ENEMY] == nullptr) {
          return;
        }
        enemyBdat = set->lists[GMK_TYPE_ROUTED_ENEMY]->getBindedBdatFp();
        if (enemyBdat == nullptr) {
          return;
        }
      }
      enemyId = Bdat::getValCheck(enemyBdat, "ene1ID", enemyPopId, BDAT_TYPE_U16);
      return;
    }
  }
  dispose();
}

bool GmkGrave::BdatInfo::isPopCondMatched(const mm::Vec3 &position) const { return popDist.isMatch(position); }

bool GmkGrave::BdatInfo::isDepopCondMatched(const mm::Vec3 &position) const { return !depopDist.isMatch(position); }

void GmkGrave::BdatInfo::debugDraw(const AGmkBase &gmk) const {}

} // namespace gmk
