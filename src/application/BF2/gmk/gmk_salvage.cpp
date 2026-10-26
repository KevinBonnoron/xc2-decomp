#include "gmk/gmk_salvage.h"

#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_game_flag.h"
#include "gf/game/gf_game_cond.h"
#include "gmk/gmk_bdat.h"
#include "mm_mtl/vector.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace gmk {

void GmkSalvage::debugDraw() const {
  isValid();
  isValid();
}

bool GmkSalvageLocator::isValid() const { return unknown08.unknown00 != nullptr && unknown20.unknown08 != nullptr; }

void GmkSalvage::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) { unknown00 = bdat.getValCheck("Condition", id, BDAT_TYPE_U16); }

bool GmkSalvage::BdatInfo::isCondMatched() const {
  if (unknown00 != 0 && !gf::GfGameCond::isGameCond(unknown00)) {
    return false;
  }
  return true;
}

GmkType GmkSalvage::getGmkType() const { return GMK_TYPE; }

int GmkSalvage::getGameFlagId() const { return unknown20.unknown18 + 0x2e1c; }

int GmkSalvage::getGmkSalvageLocatorNum() const { return getData()->unknown14 - getData()->unknown10; }

void GmkSalvage::onPlayerAccessed(gf::GF_OBJ_HANDLE *handle) { gf::GfGameFlag::setLocal(1, getGameFlagId(), 1); }

GmkType GmkSalvageLocator::getGmkType() const { return GMK_TYPE; }

void GmkSalvageLocator::onEnemyDead(gf::GF_OBJ_HANDLE *handle) { unknownF1 = true; }

void GmkSalvageLocator::onEnemyHomeToPlayerAccess(gf::GF_OBJ_HANDLE *handle) { unknownF2 = true; }

void GmkSalvageLocator::onPlayerAccessed(gf::GF_OBJ_HANDLE *handle) { unknownC8 = true; }

void GmkSalvageLocator::setEnemyPopInfo(int enemyPopId, int enemyId, s8 flag) {
  unknownE8 = enemyPopId;
  unknownEC = enemyId;
  unknownF0 = flag;
}

void GmkSalvageLocator::reqDisposeTboxGobInst(f32 waitTime) const {
  unknownE0 = waitTime;
  unknownE4 = 0;
}

void GmkSalvageLocator::initWaitPopTime(f32 waitTime) {
  unknownD8 = waitTime;
  unknownDC = 0;
  unknown48 = &GmkSalvageLocator::seqWaitPop;
}

void GmkSalvageLocator::syncDepopTboxes() {
  if (getData()->unknown00 == 4 && !unknownF1 && !unknownF2 && unknownD0 != nullptr) {
    unknownD0->unknown129 = true;
  }
}

void GmkSalvageLocator::seqWaitPop(f32 deltaTime) {
  unknownDC += deltaTime;
  if (!(unknownDC < unknownD8)) {
    unknown48 = &GmkSalvageLocator::seqPop;
  }
}

const IGmkList *GmkSetOfSalvageChildren::getGmkList(GmkType type) const { return unknown1b8[type]; }

void GmkSalvageList::debugDraw() const { TGmkList::debugDraw(); }

void GmkSalvageList::debugUpdateMmf() { TGmkList::debugUpdateMmf(); }

const AGmkBase *GmkSalvageLocatorList::getInst(u32 index) const { return &gmkInsts[index]; }

} // namespace gmk
