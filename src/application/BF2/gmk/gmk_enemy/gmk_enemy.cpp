#include "gmk/gmk_enemy/gmk_enemy.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/game/gf_game_manager.h"
#include "gmk/gmk_bdat.h"
#include "mm_mtl/vector.h"

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

GmkType GmkEnemy::getGmkType() const { return GMK_TYPE; }

IGmkList *GmkEnemy::getOwnerGmkEnemyList() const { return unknown08.unknown00; }

bool GmkEnemy::isValid() const {
  if (unknown08.unknown00 == nullptr || unknown20.unknown08 == nullptr || unknown20.unknown10 == nullptr) {
    return false;
  }
  if (unknown48 == nullptr || unknown50 == nullptr) {
    return false;
  }
  return unknown58 > 0;
}

GmkEnemyList::GmkEnemyList(u32 updateGmkNumPerFrame) : TGmkList(updateGmkNumPerFrame), unknown240(0xffffffff) {}

void GmkEnemyList::create(const CreateInfo &info) {
  if (!unknown228.create()) {
    dispose();
    return;
  }
  TGmkList::create(info);
}

void GmkEnemyList::dispose() {
  unknown240.dispose();
  TGmkList::dispose();
}

void GmkEnemyList::update(f32 deltaTime) {
  unknown240.update(deltaTime);
  TGmkList::update(deltaTime);
}

const AGmkBase *GmkEnemyList::getInst(u32 index) const { return &gmkInsts[index]; }

void GmkEnemyList::setUpdateGmkNumPerFrame(u32 num) {
  TGmkList::setUpdateGmkNumPerFrame(num);
  unknown240.setUpdateGmkNumPerFrame(num);
}

void GmkEnemyList::debugDraw() const {
  TGmkList::debugDraw();
  unknown240.debugDraw();
}

void GmkEnemyList::debugUpdateMmf() {
  TGmkList::debugUpdateMmf();
  unknown240.debugUpdateMmf();
}

} // namespace gmk
