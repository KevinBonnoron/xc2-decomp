#include "gmk/gmk_salvage.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_game_flag.h"
#include "gf/game/gf_game_cond.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_factory.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "gmk/gmk_bdat.h"
#include "gmk/gmk_form_pc.h"
#include "gmk/gmk_list_impl.h" // IWYU pragma: keep
#include "mm_mtl/rtti.h"
#include "mm_mtl/vector.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace gmk {

GmkSalvage::RaffleResult::RaffleResult() {
  unknown08 = -1;
  unknown0c = -1;
  unknown10 = -1;
  unknown20 = -1;
  unknown24 = -1;
  unknown28 = -1;
  unknown38 = -1;
  unknown00 = 0;
  unknown18 = 0;
  unknown30 = 0;
  unknown44 = 0;
  unknown46 = 0;
  unknown48 = 0;
  unknown4a = 0;
  unknown4c = 0;
  unknown4e = 0;
  unknown3c = -1;
  unknown40 = -1;
}

template bool TGmkList<GmkSalvage, GmkSalvage::BdatInfo, 1447838035u, 2u, GmkSalvageGobCustom>::initGmkBdatInfo(GmkSalvage::BdatInfo &, int &, const AGmkBase &);
template bool TGmkList<GmkSalvageLocator, GmkSalvageLocator::BdatInfo, 1129073747u, 1u, GmkSalvageLocatorGob>::initGmkBdatInfo(GmkSalvageLocator::BdatInfo &, int &, const AGmkBase &);

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

GmkSalvage::GmkSalvage()
    : unknown48(nullptr), unknown58(gf::INVALID_HANDLE), unknown60(0.0f), unknown64(0.0f), unknown68(), unknown88(), unknownA8(nullptr), unknownB0(), unknownd0(0), unknownd8(), unknown128(true),
      unknown129(false) {}

GmkType GmkSalvage::getGmkType() const { return GMK_TYPE; }

int GmkSalvage::getGameFlagId() const { return unknown20.unknown18 + 0x2e1c; }

int GmkSalvage::getGmkSalvageLocatorNum() const { return getData()->unknown14 - getData()->unknown10; }

void GmkSalvage::onPlayerAccessed(gf::GF_OBJ_HANDLE *handle) { gf::GfGameFlag::setLocal(1, getGameFlagId(), 1); }

const GmkSalvageLocator *GmkSalvage::getGmkSalvageLocator(u32 index) const {
  const GmkSalvageLocatorList *list = static_cast<const GmkSalvageLocatorList *>(static_cast<const GmkSalvageList *>(unknown08.unknown00)->unknown230.getGmkList(GMK_TYPE_SALVAGE_LOCATOR));
  if (list != nullptr) {
    u32 listIndex = getData()->unknown10 + index;
    if (list->getInstNum() > listIndex) {
      return list->unknown001(listIndex);
    }
  }
  return nullptr;
}

const GmkFormPc *GmkSalvage::getGmkFormPc() const {
  u32 index = getData()->unknown08;
  int num = getData()->unknown0c - index;
  if (num > 0) {
    const IGmkList *list = static_cast<const GmkSalvageList *>(unknown08.unknown00)->unknown230.getGmkList(GMK_TYPE_FORM_PC);
    if (list->getInstNum() > index) {
      return static_cast<const GmkFormPc *>(list->getInst(index));
    }
  }
  return nullptr;
}

void GmkSalvage::disposeGfObjHandle() {
  if (unknown58 != gf::INVALID_HANDLE) {
    gf::GfObjAcc acc(unknown58);
    if (acc.isValid()) {
      acc.setUserData(gf::OBJ_USER_DATA_GMK, 0);
    }
    gf::GfObjUtil::destroy(unknown58);
    unknown58 = gf::INVALID_HANDLE;
  }
}

void GmkSalvage::disposeTboxes(bool isFadeOut) {
  u32 count = unknown88.size();
  for (u32 i = 0; i < count; i++) {
    GmkSalvageLocator *locator = unknown88[i];
    if (locator != nullptr) {
      locator->unknownC8 = false;
      locator->disposeGobInst(isFadeOut);
    }
  }
}

void GmkSalvage::disposeEnemies(bool isFadeOut) {
  u32 count = unknownB0.size();
  for (u32 i = 0; i < count; i++) {
    GmkSalvageLocator *locator = unknownB0[i];
    if (locator != nullptr) {
      locator->disposeGobInst(isFadeOut);
    }
  }
}

void GmkSalvage::create(const CreateInfo &info) {
  const int unknown001 = 30; // Inferred role: wildcard data row of the first distance; original name unknown.
  const int unknown002 = 58; // Inferred role: wildcard data row of the second distance; original name unknown.
  AGmkBase::create(info);
  u8 *wildcard = gf::GfDataBdat::getFP(gf::BDAT_FLD_WILDCARD_DATA);
  f32 distance = Bdat::getValCheck(wildcard, 0, unknown001, BDAT_TYPE_F32).valueF32;
  unknown60 = distance * distance;
  distance = Bdat::getValCheck(wildcard, 0, unknown002, BDAT_TYPE_F32).valueF32;
  unknown64 = distance * distance;
  unknown48 = &GmkSalvage::seqValidateGmkSalvageLocatorDetails;
}

void GmkSalvage::dispose() {
  disposeRaffle(false);
  unknown48 = nullptr;
  unknownB0.clear();
  unknownA8 = nullptr;
  unknown88.clear();
  unknown68.clear();
  disposeGfObjHandle();
  AGmkBase::dispose();
}

void GmkSalvage::validateDisp() const {
  bool isDisp = unknown128 && debugIsDispGmkType(getGmkType());
  if (unknown58 != gf::INVALID_HANDLE) {
    setEventDisp(unknown58, isDisp);
  }
}

void GmkSalvage::createGfObjHandle() {
  if (!canCreateGameEntity()) {
    return;
  }
  disposeGfObjHandle();
  CBdatWrapper bdat = {getBindedBdatFp()};
  unknown58 = gf::GfObjFactory::createGmkCollection(bdat, unknown20.unknown18);
  bindToGameObj(unknown58);
  validateDisp();
  unknown002(unknown58, true);
  gf::GfObjSetupGimmick *setup = mm::mtl::dynamicCast<gf::GfObjSetupGimmick>(gf::GfObjManager::getObjInfo(unknown58)->unknown30);
  unknown003(setup, unknown08.unknown08);
}

void GmkSalvage::update(f32 deltaTime) {
  debugUpdateMmf();
  if (!isValid()) {
    return;
  }
  if (unknown129) {
    unknown129 = false;
    disposeTboxes(true);
  }
  if (unknown48) {
    (this->*unknown48)(deltaTime);
  }
}

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

void GmkSalvageLocator::update(f32 deltaTime) {
  debugUpdateMmf();
  if (unknown48) {
    (this->*unknown48)(deltaTime);
  }
}

void GmkSalvageLocator::disposeGobInst(bool isFadeOut) {
  if (unknownC0 == gf::INVALID_HANDLE) {
    return;
  }
  syncDepopTboxes();
  if (isFadeOut) {
    gmk::disposeGobInst(unknownC0, 1.0f);
  } else {
    unbindToGameObj(unknownC0);
    gf::GfObjUtil::destroy(unknownC0);
    unknownC0 = gf::INVALID_HANDLE;
  }
}

void GmkSalvageLocator::setTargetable(bool isTargetable) const {
  gf::GF_OBJ_HANDLE *handle = unknownC0;
  if (handle == gf::INVALID_HANDLE) {
    return;
  }
  unknown002(handle, isTargetable);
}

const IGmkList *GmkSetOfSalvageChildren::getGmkList(GmkType type) const { return unknown1b8[type]; }

GmkSalvageList::GmkSalvageList(u32 updateGmkNumPerFrame) : TGmkList(updateGmkNumPerFrame) {}

void GmkSalvageList::createGmk(void *data) {
  TGmkList::createGmk(data);
  unknown230.create(getCreateInfo().unknown08->unknown10);
}

void GmkSalvageList::disposeGmk() {
  unknown230.dispose();
  TGmkList::disposeGmk();
}

void GmkSalvageList::update(f32 deltaTime) {
  TGmkList::update(deltaTime);
  unknown230.update(deltaTime);
}

void GmkSalvageList::debugDraw() const { TGmkList::debugDraw(); }

void GmkSalvageList::debugUpdateMmf() { TGmkList::debugUpdateMmf(); }

const AGmkBase *GmkSalvageLocatorList::getInst(u32 index) const { return &gmkInsts[index]; }

} // namespace gmk
