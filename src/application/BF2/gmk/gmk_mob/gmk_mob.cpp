#include "gmk/gmk_mob/gmk_mob.h"

#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_object_type.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gmk/gmk_bdat.h"
#include "gmk/gmk_list_impl.h" // IWYU pragma: keep
#include "gmk/gmk_squad.h"
#include "mm_mtl/reference_object.h"
#include "mm_mtl/vector.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace gmk {

template bool TGmkList<GmkMob, GmkMob::BdatInfo, 4345677u, 2u, GmkMobGob>::initGmkBdatInfo(GmkMob::BdatInfo &, int &, const AGmkBase &);

void GmkMobInsts::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  unknown02 = bdat.getValCheck("Group", id, BDAT_TYPE_U16);
  unknown04 = bdat.getValCheck("squadId", id, BDAT_TYPE_U16);
  if (unknown02 == 0) {
    unknown12 = ScenarioFlagCond(bdat.getValCheck("ScenarioFlagMin", id, BDAT_TYPE_U16), bdat.getValCheck("ScenarioFlagMax", id, BDAT_TYPE_U16));
    unknown16 = QuestFlagCond(bdat.getValCheck("QuestFlag", id, BDAT_TYPE_U16), bdat.getValCheck("QuestFlagMin", id, BDAT_TYPE_U8), bdat.getValCheck("QuestFlagMax", id, BDAT_TYPE_U8));
    u16 timeRange = bdat.getValCheck("TimeRange", id, BDAT_TYPE_U16);
    unknown20.unknown08 = timeRange;
    unknown00 = bdat.getValCheck("Condition", id, BDAT_TYPE_U16);
  }
  unknown06 = bdat.getValCheck("Mot", id, BDAT_TYPE_U16);
  unknown08 = static_cast<u16>(bdat.getValCheck("Collision", id, BDAT_TYPE_U16));
  unknown0a = bdat.getValCheck("ReactionRange", id, BDAT_TYPE_U16);
  unknown0c = static_cast<u16>(bdat.getValCheck("ReactionPercent", id, BDAT_TYPE_U16));
  unknown0e = bdat.getValCheck("ReactionMot", id, BDAT_TYPE_U16);
  unknown10 = bdat.getValCheck("BattleReaction", id, BDAT_TYPE_U16);
  u16 visibleXZ = bdat.getValCheck("Visible_XZ", id, BDAT_TYPE_U16);
  u16 visibleY = bdat.getValCheck("Visible_Y", id, BDAT_TYPE_U16);
  unknown30.set(visibleXZ, visibleY);
  u16 invisibleXZ = DistHvCond::clampDepopDist(bdat.getValCheck("Invisible_XZ", id, BDAT_TYPE_U16), visibleXZ);
  u16 invisibleY = DistHvCond::clampDepopDist(bdat.getValCheck("Invisible_Y", id, BDAT_TYPE_U16), visibleY);
  unknown38.set(invisibleXZ, invisibleY);
}

void GmkMobInsts::BdatInfo::debugDraw(const AGmkBase &gmk) const {}

void GmkMobInsts::PopInfo::dispose() {
  unknown40 = 0;
  unknown18.clear();
}

void GmkMobInsts::validateDisp(gf::GF_OBJ_HANDLE *handle) const {
  AGmkBase *gmk = getBindedGmkInst(handle);
  if (gmk == nullptr) {
    return;
  }
  bool isDisp = debugIsDispGmkType(gmk->getGmkType()) && unknowna0;
  setEventDisp(handle, isDisp);
}

bool GmkMobInsts::isPopFinished() const {
  if (!isGfObjNumFull(gf::OBJECT_TYPE_MOB) && (unknownb8 & MATCHED_UNKNOWN_0) && (unknownb8 & MATCHED_UNKNOWN_1)) {
    u32 num = unknowna8->size();
    return unknown58.unknown40 == num;
  }
  return true;
}

bool GmkMobInsts::isValid() const {
  if (unknowna8 == nullptr) {
    return false;
  }
  if (unknown18.unknown04 == 0) {
    return true;
  }
  if (unknownb0 != nullptr && unknownb0->isValid()) {
    return true;
  }
  return false;
}

bool GmkMobInsts::isGobInstExist() const {
  if (unknowna8 == nullptr) {
    return false;
  }
  size_t num = unknowna8->size();
  for (size_t i = 0; i < num; i++) {
    if ((*unknowna8)[i] != gf::INVALID_HANDLE) {
      return true;
    }
  }
  return false;
}

bool GmkMobInsts::canPopGobInst(const mm::Vec3 &position) const {
  if (isGobInstExist()) {
    return false;
  }
  if (unknownb8 & MATCHED_UNKNOWN_0) {
    return (unknownb8 & MATCHED_UNKNOWN_1) != 0;
  }
  return false;
}

bool GmkMobInsts::canDepopGobInst(const mm::Vec3 &position) const {
  if (!isGobInstExist()) {
    return false;
  }
  if (unknownb8 & MATCHED_UNKNOWN_0) {
    return (unknownb8 & MATCHED_UNKNOWN_2) == 0;
  }
  return true;
}

void GmkMobInsts::removeGobInst(gf::GF_OBJ_HANDLE *handle) {
  if (handle == gf::INVALID_HANDLE || unknowna8->size() == 0) {
    return;
  }
  for (gf::GF_OBJ_HANDLE **it = unknowna8->begin(); it != unknowna8->end(); ++it) {
    if (*it == handle) {
      unknowna8->erase(it);
      return;
    }
  }
}

void GmkMobInsts::disposeSquad() { mm::mtl::safeRelease(unknownb0); }

void GmkMob::onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) {
  if (event == gf::IGfObjListener::OBJEVT_DESTROY && handle != gf::INVALID_HANDLE) {
    gf::GfObjAcc acc(handle);
    if (acc.isValid()) {
      acc.setUserData(gf::OBJ_USER_DATA_GMK, 0);
    }
    unknown48.removeGobInst(handle);
  }
}

GmkType GmkMob::getGmkType() const { return GMK_TYPE; }

void GmkMob::debugDraw() const { isValid(); }

} // namespace gmk
