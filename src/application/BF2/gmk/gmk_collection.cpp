#include "gmk/gmk_collection.h"

#include "bdat.h"
#include "framework/debug/debug_draw.h"
#include "framework/effect/effect_manager.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_game_flag.h"
#include "gf/game/gf_game_cond.h"
#include "gf/game/gf_game_manager.h"
#include "gf/object/gf_obj_factory.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_manager.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "gmk/gmk_bdat.h"
#include "gmk/gmk_list_impl.h" // IWYU pragma: keep
#include "mm_math/mm_col4.h"
#include "mm_math/mm_vec2.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/rtti.h"

namespace fw {
enum EF_CATEGORY : int;
} // namespace fw

namespace gmk {

template bool TGmkList<GmkCollection, GmkCollection::BdatInfo, 1413696579u, 5u, GmkCollectionGob>::initGmkBdatInfo(GmkCollection::BdatInfo &, int &, const AGmkBase &);

GmkCollection::GmkCollection() : unknown48(gf::INVALID_HANDLE), unknown50(0), unknown54(0.0f), unknown58(nullptr), unknown68(0.0f), unknown6c(true) {}

constexpr int WILDCARD_COLLECTION_POP_DIST_ROW = 1;

void GmkCollection::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  unknown08.unknown08 = bdat.getValCheck("POP_TIME", id, BDAT_TYPE_U32);
  unknown18.unknown08 = bdat.getValCheck("popWeather", id, BDAT_TYPE_U8);
  unknown00 = bdat.getValCheck("nameRadius", id, BDAT_TYPE_U16);
  unknown02 = bdat.getValCheck("Condition", id, BDAT_TYPE_U16);
  f32 popDist = Bdat::getValCheck(gf::GfDataBdat::getFP(gf::BDAT_FLD_WILDCARD_DATA), 0, WILDCARD_COLLECTION_POP_DIST_ROW, BDAT_TYPE_F32).valueF32;
  unknown28.unknown00 = popDist * popDist;
}

bool GmkCollection::BdatInfo::isPopCondMatchedExceptDist() const {
  if (unknown02 != 0 && !gf::GfGameCond::isGameCond(unknown02)) {
    return false;
  }
  if (unknown08.isEnable() && !unknown08.isMatch()) {
    return false;
  }
  if (unknown18.isEnable() && !unknown18.isMatch()) {
    return false;
  }
  return true;
}

void GmkCollection::BdatInfo::debugDraw(const AGmkBase &gmk) const {}

bool GmkCollectionList::BdatInfo::create() {
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
  unknown04 = Bdat::getValCheck(mapList, "m_repoptime", unknown00, BDAT_TYPE_U8);
  return true;
}

GmkCollectionList::GmkCollectionList(u32 updateGmkNumPerFrame) : TGmkList(updateGmkNumPerFrame) {}

void GmkCollectionList::create(const CreateInfo &info) {
  if (!unknown228.create()) {
    dispose();
    return;
  }
  TGmkList::create(info);
}

void GmkCollection::disposeIcon(bool isFadeOut) {
  if (unknown50 != 0) {
    if (isFadeOut) {
      fw::EffectManager::get()->fadeOutDead(unknown50, 5);
    } else {
      fw::EffectManager::get()->remove(unknown50);
    }
    unknown50 = 0;
  }
}

void GmkCollection::seqUpdatePopDepop(f32 deltaTime) {
  if (isValid()) {
    if (canPopGobInst()) {
      createGfObjHandle();
    } else if (canDepopGobInst()) {
      disposeGfObjHandle();
    }
    if (unknown48 != gf::INVALID_HANDLE && DistCond::isMatch(unknown54, unknown08.unknown08->unknown00)) {
      if (unknown50 == 0) {
        createIcon();
      }
    } else {
      disposeIcon(true);
    }
  }
}

void GmkCollection::createIcon() {
  if (!canCreateGameEntity()) {
    return;
  }
  disposeIcon(false);
  void *effect = fw::EffectManager::get()->search("cmn_200_000", nullptr);
  if (effect != nullptr) {
    unknown50 = fw::EffectManager::get()->create(effect, true);
    if (unknown50 != 0) {
      fw::EffectManager::get()->setCategory(unknown50, static_cast<fw::EF_CATEGORY>(1));
      validateIconPos();
    }
  }
}

void GmkCollection::disposeGfObjHandle() {
  if (unknown48 != gf::INVALID_HANDLE) {
    unbindToGameObj(unknown48);
    gf::GfObjUtil::destroy(unknown48);
    unknown48 = gf::INVALID_HANDLE;
  }
}

void GmkCollection::createGfObjHandle() {
  if (!canCreateGameEntity()) {
    return;
  }
  disposeGfObjHandle();
  CBdatWrapper bdat = {getBindedBdatFp()};
  unknown48 = gf::GfObjFactory::createGmkCollection(bdat, unknown20.unknown18);
  bindToGameObj(unknown48);
  validateDisp();
  gf::GfObjSetupGimmick *setup = mm::mtl::dynamicCast<gf::GfObjSetupGimmick>(gf::GfObjManager::getObjInfo(unknown48)->unknown30);
  unknown003(setup, unknown08.unknown08);
  setTargetable(gf::GfGameFlag::getLocal(1, getGameFlagId()) == 0);
}

void GmkCollection::debugDraw() const {
  AGmkBase::debugDraw();
  if (isValid() && unknown68 > 0.0f) {
    mm::Vec2 screen;
    if (toScreenPos(screen, AGmkBase::unknown08.unknown08->unknown00)) {
      mm::mtl::FixStr<128> text;
      text.format("repop-time=%.1f", unknown68);
      fw::debug::drawFont(static_cast<int>(screen.x), static_cast<int>(screen.y) + 24, mm::Col4::green, text.c_str());
    }
  }
}

void GmkCollection::update(f32 deltaTime) {
  AGmkBase::update(deltaTime);
  if (unknown58) {
    (this->*unknown58)(deltaTime);
  }
}

void GmkCollection::validateDisp() const {
  bool isDisp = unknown6c && debugIsDispGmkType(getGmkType());
  if (unknown48 != gf::INVALID_HANDLE) {
    setEventDisp(unknown48, isDisp);
  }
  if (unknown50 != 0) {
    fw::EffectManager::get()->setDisp(unknown50, isDisp);
  }
}

void GmkCollection::dispose() {
  if (unknown50 != 0) {
    fw::EffectManager::get()->remove(unknown50);
    unknown50 = 0;
  }
  disposeGfObjHandle();
  AGmkBase::dispose();
}

GmkType GmkCollection::getGmkType() const { return GMK_TYPE; }

void GmkCollection::create(const CreateInfo &info) {
  AGmkBase::create(info);
  if (!isValid()) {
    dispose();
    return;
  }
  bool isTargetable = true;
  if (gf::GfGameManager::isMapjumpWithSaveData()) {
    isTargetable = gf::GfGameFlag::getLocal(1, getGameFlagId()) == 0;
  }
  setTargetable(isTargetable);
  f32 popDist = Bdat::getValCheck(gf::GfDataBdat::getFP(gf::BDAT_FLD_WILDCARD_DATA), 0, WILDCARD_COLLECTION_POP_DIST_ROW, BDAT_TYPE_F32).valueF32;
  unknown54 = popDist * popDist;
}

int GmkCollection::getGameFlagId() const { return unknown20.unknown18 + 0x715c; }

bool GmkCollection::isWaitRepop() const { return gf::GfGameFlag::getLocal(1, getGameFlagId()) != 0; }

void GmkCollection::seqUpdateRepopCounter(f32 deltaTime) {
  unknown68 -= deltaTime;
  if (unknown68 > 0.0f) {
    return;
  }
  setTargetable(true);
}

void GmkCollection::onPlayerAccessed(gf::GF_OBJ_HANDLE *handle) { setTargetable(false); }

bool GmkCollection::canPopGobInst() const {
  if (unknown48 != gf::INVALID_HANDLE) {
    return false;
  }
  const BdatInfo *info = getBdatInfo();
  if (!info->isPopCondMatchedExceptDist()) {
    return false;
  }
  return DistCond::isMatch(info->unknown28.unknown00, unknown08.unknown08->unknown00);
}

bool GmkCollection::canDepopGobInst() const {
  if (unknown48 == gf::INVALID_HANDLE) {
    return false;
  }
  const BdatInfo *info = getBdatInfo();
  if (info->isPopCondMatchedExceptDist() && DistCond::isMatch(info->unknown28.unknown00, unknown08.unknown08->unknown00)) {
    return false;
  }
  return true;
}

} // namespace gmk
