#include "gmk/gmk_salvage.h"

#include "bdat.h"
#include "framework/debug/debug_draw.h"
#include "gf/data/gf_bdat_chrenarrange.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_game_flag.h"
#include "gf/game/gf_game_cond.h"
#include "gf/game/gf_game_manager.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_factory.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "gmk/gmk_bdat.h"
#include "gmk/gmk_cond.h"
#include "gmk/gmk_form_pc.h"
#include "gmk/gmk_list_impl.h" // IWYU pragma: keep
#include "mm_math/mm_col3.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/rtti.h"
#include "mm_mtl/vector.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace gmk {

GmkSalvage::RaffleResult::RaffleResult() {
  unknown08[0] = -1;
  unknown08[1] = -1;
  unknown08[2] = -1;
  unknown20[0] = -1;
  unknown20[1] = -1;
  unknown20[2] = -1;
  unknown38[0] = -1;
  unknown00 = 0;
  unknown18 = 0;
  unknown30 = 0;
  unknown44[0].unknown00 = 0;
  unknown44[0].unknown02 = 0;
  unknown44[1].unknown00 = 0;
  unknown44[1].unknown02 = 0;
  unknown44[2].unknown00 = 0;
  unknown44[2].unknown02 = 0;
  unknown38[1] = -1;
  unknown38[2] = -1;
}

// The loop copies each entry (range-for by value) and keeps `enemyLevel` in a local: the local scope and the `continue` give the game's cleanup dispatch of the loop body
// (`cset ls; csel hi; cbnz` at 0x710060982c, `orr #2; cmp #2; cset ne` at the end). Without the local (`level <= enemy.getLevel(arrange)`) the function is 78 instructions, with a
// nested `if (enemy.unknown00 != 0)` instead of `continue` 60, with an index loop or a reference loop variable 63 (`cmp; b.hs`).
bool GmkSalvage::RaffleResult::isPowerfullEnemyExist() const {
  if (gf::GfGameManager::getControlMover() == gf::unknown020) {
    return false;
  }
  gf::DataParamAcc acc(gf::GfGameManager::getControlMover());
  u32 level = acc.getLevel(false) + 5;
  const gf::GfBdatChrEnArrange *arrange = gf::GfBdatChrEnArrange::get();
  for (RaffleResult::unknown001 enemy : unknown44) {
    if (enemy.unknown00 == 0) {
      continue;
    }
    u32 enemyLevel = enemy.getLevel(arrange);
    if (level <= enemyLevel) {
      return true;
    }
  }
  return false;
}

template bool TGmkList<GmkSalvage, GmkSalvage::BdatInfo, 1447838035u, 2u, GmkSalvageGobCustom>::initGmkBdatInfo(GmkSalvage::BdatInfo &, int &, const AGmkBase &);
template bool TGmkList<GmkSalvageLocator, GmkSalvageLocator::BdatInfo, 1129073747u, 1u, GmkSalvageLocatorGob>::initGmkBdatInfo(GmkSalvageLocator::BdatInfo &, int &, const AGmkBase &);

void GmkSalvage::debugDraw() const {
  isValid();
  isValid();
}

bool GmkSalvageLocator::isValid() const { return m_createBaseInfo.m_ownerGmkEnemyList != nullptr && m_createInfo.unknown08 != nullptr; }

GmkSalvageLocator::GmkSalvageLocator()
    : unknown48(nullptr), unknown58(false), m_dropitemEmitter(nullptr), unknownc0(gf::unknown020), unknownc8(0), m_gmkSalvage(nullptr), unknownd8(0.0f), unknowndc(0.0f), unknowne0(0.0f),
      unknowne4(0.0f), unknowne8(-1), unknownec(0), unknownf0(0), unknownf1(false), unknownf2(false) {}

void GmkSalvage::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) { unknown00 = bdat.getValCheck("Condition", id, BDAT_TYPE_UNKNOWN_2); }

bool GmkSalvage::BdatInfo::isCondMatched() const {
  if (unknown00 != 0 && !gf::GfGameCond::isGameCond(unknown00)) {
    return false;
  }
  return true;
}

GmkSalvage::GmkSalvage()
    : unknown48(nullptr), unknown58(gf::unknown020), unknown60(0.0f), unknown64(0.0f), unknown68(), unknown88(), m_gmkSalvageLocator(nullptr), unknownb0(), unknownd0(0), unknownd1(0),
      m_raffleResult(), unknown128(true), unknown129(false) {}

GmkType GmkSalvage::getGmkType() const { return GMK_TYPE; }

int GmkSalvage::getGameFlagId() const { return m_createInfo.unknown18 + 0x2e1c; }

int GmkSalvage::getGmkSalvageLocatorNum() const { return getData()->unknown14 - getData()->unknown10; }

void GmkSalvage::onPlayerAccessed(gf::GF_OBJ_HANDLE *handle) { gf::GfGameFlag::setLocal(1, getGameFlagId(), 1); }

GmkSalvageLocator *GmkSalvage::getGmkSalvageLocator(u32 index) const {
  GmkSalvageLocatorList *list =
      static_cast<GmkSalvageLocatorList *>(static_cast<GmkSalvageList *>(m_createBaseInfo.m_ownerGmkEnemyList)->m_gmkSetOfSalvageChildren.getGmkList(GMK_TYPE_SALVAGE_LOCATOR));
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
    const IGmkList *list = static_cast<const GmkSalvageList *>(m_createBaseInfo.m_ownerGmkEnemyList)->m_gmkSetOfSalvageChildren.getGmkList(GMK_TYPE_FORM_PC);
    if (list->getInstNum() > index) {
      return static_cast<const GmkFormPc *>(list->getInst(index));
    }
  }
  return nullptr;
}

void GmkSalvage::disposeGfObjHandle() {
  if (unknown58 != gf::unknown020) {
    gf::GfObjAcc acc(unknown58);
    if (acc.isValid()) {
      acc.setUserData(gf::OBJ_USER_DATA_UNKNOWN_0, 0);
    }
    gf::GfObjUtil::destroy(unknown58);
    unknown58 = gf::unknown020;
  }
}

void GmkSalvage::seqValidateGmkSalvageLocatorDetails(f32 deltaTime) {
  u32 num = getGmkSalvageLocatorNum();
  if (num != 0) {
    if (getGmkSalvageLocator(0) == nullptr) {
      return;
    }
    for (u32 i = 0; i < num; i++) {
      GmkSalvageLocator *locator = getGmkSalvageLocator(i);
      locator->m_gmkSalvage = this;
      switch (locator->getData()->unknown00) {
      case 1:
        if (unknown68.size() != unknown68.capacity()) {
          unknown68.push_back(locator);
        }
        break;
      case 2:
        if (unknown88.size() != unknown88.capacity()) {
          unknown88.push_back(locator);
        }
        break;
      case 3:
        if (m_gmkSalvageLocator == nullptr) {
          m_gmkSalvageLocator = locator;
        }
        break;
      case 4:
        if (unknownb0.size() != unknownb0.capacity()) {
          unknownb0.push_back(locator);
        }
        break;
      }
    }
  }
  unknown48 = &GmkSalvage::seqUpdatePopDepop;
}

void GmkSalvage::seqUpdatePopDepop(f32 deltaTime) {
  if (getBdatInfo()->isCondMatched() && DistCond::isMatch(unknown60, m_createBaseInfo.m_xform->unknown00)) {
    if (unknown58 == gf::unknown020) {
      createGfObjHandle();
    }
  } else {
    disposeGfObjHandle();
  }
  if (unknownd1) {
    u32 enemyCount = unknownb0.size();
    for (u32 i = 0; i < enemyCount; i++) {
      if ((1ul << i) & m_raffleResult.unknown30) {
        GmkSalvageLocator *locator = unknownb0[i];
        if (locator != nullptr) {
          locator->update(deltaTime);
        }
      }
    }
    u32 locatorCount = unknown68.size();
    for (u32 i = 0; i < locatorCount; i++) {
      if ((1ul << i) & m_raffleResult.unknown00) {
        GmkSalvageLocator *locator = unknown68[i];
        if (locator != nullptr) {
          locator->update(deltaTime);
        }
      }
    }
    u32 tboxCount = unknown88.size();
    for (u32 i = 0; i < tboxCount; i++) {
      if ((1ul << i) & m_raffleResult.unknown18) {
        GmkSalvageLocator *locator = unknown88[i];
        if (locator != nullptr) {
          locator->update(deltaTime);
        }
      }
    }
    if (!gf::GfGameManager::isBattle() && !DistCond::isMatch(unknown64, m_createBaseInfo.m_xform->unknown00)) {
      u32 count = unknownb0.size();
      for (u32 i = 0; i < count; i++) {
        GmkSalvageLocator *locator = unknownb0[i];
        if (locator != nullptr) {
          locator->disposeGobInst(true);
        }
      }
    }
  }
}

void GmkSalvage::onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) {
  AGmkBase::onGobEvent(event, handle);
  if (event == gf::IGfObjListener::OBJEVT_UNKNOWN_3) {
    u32 enemyCount = unknownb0.size();
    if (enemyCount != 0) {
      bool isFound = false;
      for (u32 i = 0; i < enemyCount; i++) {
        GmkSalvageLocator *locator = unknownb0[i];
        if (locator != nullptr && locator->isValid() && !locator->unknownf1) {
          isFound |= locator->unknownc0 == handle;
          if (locator->unknownc0 == handle) {
            break;
          }
        }
      }
      if (isFound) {
        u32 tboxCount = unknown88.size();
        for (u32 i = 0; i < tboxCount; i++) {
          GmkSalvageLocator *locator = unknown88[i];
          if (locator != nullptr) {
            locator->unknownc8 = false;
            locator->disposeGobInst(true);
          }
        }
      }
    }
    unknown58 = gf::unknown020;
  }
}

void GmkSalvage::disposeTboxes(bool isFadeOut) {
  u32 count = unknown88.size();
  for (u32 i = 0; i < count; i++) {
    GmkSalvageLocator *locator = unknown88[i];
    if (locator != nullptr) {
      locator->unknownc8 = false;
      locator->disposeGobInst(isFadeOut);
    }
  }
}

void GmkSalvage::disposeEnemies(bool isFadeOut) {
  u32 count = unknownb0.size();
  for (u32 i = 0; i < count; i++) {
    GmkSalvageLocator *locator = unknownb0[i];
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
  f32 distance = Bdat::getValCheck(wildcard, 0, unknown001, BDAT_TYPE_UNKNOWN_8).valueF32;
  unknown60 = distance * distance;
  distance = Bdat::getValCheck(wildcard, 0, unknown002, BDAT_TYPE_UNKNOWN_8).valueF32;
  unknown64 = distance * distance;
  unknown48 = &GmkSalvage::seqValidateGmkSalvageLocatorDetails;
}

void GmkSalvage::dispose() {
  disposeRaffle(false);
  unknown48 = nullptr;
  unknownb0.clear();
  m_gmkSalvageLocator = nullptr;
  unknown88.clear();
  unknown68.clear();
  disposeGfObjHandle();
  AGmkBase::dispose();
}

void GmkSalvage::validateDisp() const {
  bool isDisp = unknown128 && debugIsDispGmkType(getGmkType());
  if (unknown58 != gf::unknown020) {
    setEventDisp(unknown58, isDisp);
  }
}

void GmkSalvage::createGfObjHandle() {
  if (!canCreateGameEntity()) {
    return;
  }
  disposeGfObjHandle();
  CBdatWrapper bdat = {getBindedBdatFp()};
  unknown58 = gf::GfObjFactory::createGmkCollection(bdat, m_createInfo.unknown18);
  bindToGameObj(unknown58);
  validateDisp();
  unknown002(unknown58, true);
  gf::GfObjSetupGimmick *setup = mm::mtl::dynamicCast<gf::GfObjSetupGimmick>(gf::GfObjManager::getObjInfo(unknown58)->unknown30);
  unknown003(setup, m_createBaseInfo.m_xform);
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

void GmkSalvageLocator::onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) {
  AGmkBase::onGobEvent(event, handle);
  if (event == gf::IGfObjListener::OBJEVT_UNKNOWN_3) {
    disposeGobInst(false);
  }
}

void GmkSalvageLocator::onEnemyDead(gf::GF_OBJ_HANDLE *handle) { unknownf1 = true; }

void GmkSalvageLocator::onEnemyHomeToPlayerAccess(gf::GF_OBJ_HANDLE *handle) { unknownf2 = true; }

void GmkSalvageLocator::onPlayerAccessed(gf::GF_OBJ_HANDLE *handle) { unknownc8 = true; }

void GmkSalvageLocator::setEnemyPopInfo(int enemyPopId, int enemyId, s8 flag) {
  unknowne8 = enemyPopId;
  unknownec = enemyId;
  unknownf0 = flag;
}

void GmkSalvageLocator::reqDisposeTboxGobInst(f32 waitTime) const {
  unknowne0 = waitTime;
  unknowne4 = 0;
}

void GmkSalvageLocator::initWaitPopTime(f32 waitTime) {
  unknownd8 = waitTime;
  unknowndc = 0;
  unknown48 = &GmkSalvageLocator::seqWaitPop;
}

void GmkSalvageLocator::syncDepopTboxes() {
  if (getData()->unknown00 == 4 && !unknownf1 && !unknownf2 && m_gmkSalvage != nullptr) {
    m_gmkSalvage->unknown129 = true;
  }
}

void GmkSalvageLocator::seqWaitPop(f32 deltaTime) {
  unknowndc += deltaTime;
  if (!(unknowndc < unknownd8)) {
    unknown48 = &GmkSalvageLocator::seqPop;
  }
}

void GmkSalvageLocator::seqPop(f32 deltaTime) {
  switch (getData()->unknown00) {
  case 1:
    if (!unknown58) {
      createCollectDropitemEmitter();
    }
    m_dropitemEmitter.update(deltaTime);
    break;
  case 2: {
    bool isWaitDepop = unknowne0 > 0.0f;
    if (unknownc0 == gf::unknown020) {
      if (!isWaitDepop) {
        createTboxGobInst();
      }
    } else if (isWaitDepop) {
      unknowne4 += deltaTime;
      if (unknowne0 <= unknowne4) {
        unknownc8 = false;
        disposeGobInst(true);
      }
    }
  } break;
  case 4:
    if (unknownc0 == gf::unknown020) {
      createEnemyGobInst();
    }
    break;
  }
  unknown48 = nullptr;
}

void GmkSalvageLocator::update(f32 deltaTime) {
  debugUpdateMmf();
  if (unknown48) {
    (this->*unknown48)(deltaTime);
  }
}

void GmkSalvageLocator::dispose() {
  unknownf0 = 0;
  unknowne8 = -1;
  unknownec = 0;
  reqDisposeTboxGobInst(0.0f);
  unknown58 = false;
  m_dropitemEmitter.dispose();
  unknownc8 = false;
  disposeGobInst(false);
  AGmkBase::dispose();
}

void GmkSalvageLocator::disposeGobInst(bool isFadeOut) {
  if (unknownc0 == gf::unknown020) {
    return;
  }
  syncDepopTboxes();
  if (isFadeOut) {
    gmk::disposeGobInst(unknownc0, 1.0f);
  } else {
    unbindToGameObj(unknownc0);
    gf::GfObjUtil::destroy(unknownc0);
    unknownc0 = gf::unknown020;
  }
}

void GmkSalvageLocator::debugDraw() const {
  if (isValid()) {
    mm::Vec3 end = unknown095(mm::Vec3::unitZ, m_createBaseInfo.m_xform->unknown10) + m_createBaseInfo.m_xform->unknown00;
    mm::Col4 color(mm::Col3::green.r, mm::Col3::green.g, mm::Col3::green.b, 1.0f);
    fw::debug::drawArrow(m_createBaseInfo.m_xform->unknown00, end, color);
  }
}

void GmkSalvageLocator::createCollectDropitemEmitter() {
  unknown58 = false;
  m_dropitemEmitter.dispose();
  gf::GfDropitemEmitter::CreateInfo info;
  const Xform *xform = m_createBaseInfo.m_xform;
  info.unknown00 = xform->unknown00;
  info.unknown00.y += 0.8f;
  info.unknown10 = xform->unknown10.y;
  info.unknown14 = 3.1415927f;
  info.unknown28 = gf::GfDataBdat::getFP(gf::BDAT_FLD_SALVAGE_ITEM_SET);
  info.unknown30 = unknowne8;
  info.unknown20 = 0.25f;
  m_dropitemEmitter.create(info);
  unknown58 = true;
}

void GmkSalvageLocator::createTboxGobInst() {
  unknownc8 = false;
  disposeGobInst(false);
  CBdatWrapper bdat = {gf::GfDataBdat::getFP(gf::BDAT_FLD_SALVAGE_ITEM_SET)};
  unknownc0 = gf::GfObjFactory::createGmkTbox(bdat, unknowne8);
  bindToGameObj(unknownc0);
  setEventDisp(unknownc0, debugIsDispGmkType(getGmkType()));
  gf::GfObjSetupGimmick *setup = gf::GfObjUtil::getObjSetup<gf::GfObjSetupGimmick>(unknownc0);
  unknown003(setup, m_createBaseInfo.m_xform);
  setup->unknown70 = "S_drop";
  setTargetable(true);
}

void GmkSalvageLocator::createEnemyGobInst() {
  disposeGobInst(false);
  const Xform *xform = m_createBaseInfo.m_xform;
  unknownc0 = gf::GfObjFactory::createGmkEnemy(unknownec, unknownf0, 2, xform->unknown00, xform->unknown10, true);
  if (unknownc0 == gf::unknown020) {
    return;
  }
  gf::GfObjSetupEnemy *setup = gf::GfObjUtil::getObjSetup<gf::GfObjSetupEnemy>(unknownc0);
  setup->validateBy_pop_act_type(Bdat::getValCheck(gf::GfDataBdat::getFP(gf::BDAT_FLD_SALVAGE_ENEMY_SET), "pop_act_type", unknowne8, BDAT_TYPE_UNKNOWN_1));
  bindToGameObj(unknownc0);
  unknownf1 = false;
  unknownf2 = false;
}

void GmkSalvageLocator::setTargetable(bool isTargetable) const {
  gf::GF_OBJ_HANDLE *handle = unknownc0;
  if (handle == gf::unknown020) {
    return;
  }
  unknown002(handle, isTargetable);
}

IGmkList *GmkSetOfSalvageChildren::getGmkList(GmkType type) const { return unknown1b8[type]; }

GmkSalvageList::GmkSalvageList(u32 updateGmkNumPerFrame) : TGmkList(updateGmkNumPerFrame) {}

void GmkSalvageList::createGmk(void *data) {
  TGmkList::createGmk(data);
  m_gmkSetOfSalvageChildren.create(getCreateInfo().m_gmkSet->m_createInfo);
}

void GmkSalvageList::disposeGmk() {
  m_gmkSetOfSalvageChildren.dispose();
  TGmkList::disposeGmk();
}

void GmkSalvageList::update(f32 deltaTime) {
  TGmkList::update(deltaTime);
  m_gmkSetOfSalvageChildren.update(deltaTime);
}

void GmkSalvageList::debugDraw() const { TGmkList::debugDraw(); }

void GmkSalvageList::debugUpdateMmf() { TGmkList::debugUpdateMmf(); }

const AGmkBase *GmkSalvageLocatorList::getInst(u32 index) const { return &gmkInsts[index]; }

} // namespace gmk

template void mm::mtl::Vector<gmk::GmkSalvage::BdatInfo>::expand(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkSalvage::BdatInfo>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkSalvage::BdatInfo>::resize(size_t);
template void mm::mtl::Vector<gmk::GmkSalvageLocator::BdatInfo>::expand(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkSalvageLocator::BdatInfo>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkSalvageLocator::BdatInfo>::resize(size_t);
template void mm::mtl::Vector<gmk::GmkSalvageLocator>::expand(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkSalvageLocator>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkSalvageLocator>::resize(size_t);
