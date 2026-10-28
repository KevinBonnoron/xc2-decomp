#include "gmk/gmk_mob/gmk_mob.h"

#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_object_type.h"
#include "gf/gf_allocator.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "gmk/gmk_bdat.h"
#include "gmk/gmk_list_impl.h"        // IWYU pragma: keep
#include "gmk/gmk_mob/gmk_mob_impl.h" // IWYU pragma: keep
#include "gmk/gmk_squad.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/reference_object.h"
#include "mm_mtl/vector.h"

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

bool GmkMobInsts::BdatInfo::isMobPopDistCondMatched(const mm::Vec3 &position) const {
  if (!isInterestPosExist()) {
    return false;
  }
  const mm::Vec3 &interestPos = getInterestPos();
  f32 x = interestPos.x - position.x;
  f32 y = interestPos.y - position.y;
  f32 z = interestPos.z - position.z;
  f32 distSq = x * x + y * y + z * z;
  return !(getMobPopDistSq() < distSq);
}

void GmkMobInsts::PopInfo::dispose() {
  unknown40 = 0;
  unknown18.clear();
}

GmkMobInsts::GmkMobInsts() : unknowna0(true), unknowna8(nullptr), unknownb0(nullptr), unknownb8(0), unknownc0(nullptr) {}

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
  if (unknowna8 != nullptr) {
    if (unknown18.unknown04 == 0 || (unknownb0 != nullptr && unknownb0->isValid())) {
      return true;
    }
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

void GmkMobInsts::validateDisp() const {
  if (!isValid()) {
    return;
  }
  u32 num = unknowna8->size();
  for (u32 i = 0; i < num; i++) {
    validateDisp((*unknowna8)[i]);
  }
}

void GmkMobInsts::update(const UpdateInfo &info) {
  if (isValid() && unknownc0) {
    (this->*unknownc0)(info);
  }
}

bool GmkMob::PopXformFinder::findPosRot(mm::Vec3 &position, mm::Vec3 &rotation) const {
  GmkSquad *squad = unknown08->unknown48.unknownb0;
  bool isPlaced = false;
  if (squad != nullptr) {
    mm::mtl::Vector<gf::GF_OBJ_HANDLE *> *handles = unknown08->unknown48.unknowna8;
    u32 num = handles->size();
    if (num != 0 && num < static_cast<u32>(squad->unknown70)) {
      gf::GfObjAcc acc((*handles)[0]);
      if (!acc.isValidTransform()) {
        return false;
      }
      squad->getPosRotY(position, rotation.y, unknown08->unknown48.unknowna8->size());
      rotation.z = 0.0f;
      rotation.x = 0.0f;
      isPlaced = true;
    }
  }
  if (!isPlaced) {
    if (unknown08->unknown48.unknown58.unknown40 == 1) {
      position = unknown08->unknown08.unknown08->unknown00;
    } else {
      unknown08->getPositionInShape(position, false);
    }
  }
  rotation = unknown08->unknown08.unknown08->unknown10;
  if (unknown08->getData()->unknown00 != 0) {
    f32 halfLength = unknown08->getYSnapRayLength() * 0.5f;
    mm::Vec3 start;
    start.x = position.x;
    start.y = halfLength + position.y;
    start.z = position.z;
    if (!getYSnapPos(position, start, halfLength + halfLength)) {
      return false;
    }
  }
  return true;
}

void GmkMob::PopXformFinder::onPopGob(gf::GF_OBJ_HANDLE *handle) const {}

void GmkMob::PopXformFinder::onCreateGobInsts(u32 num) const {}

void GmkMobInsts::seqWaitToFadeOutOfGobInst(const UpdateInfo &info) {
  u32 num = unknowna8->size();
  if (num == 0) {
    unknowna8->destroy();
    unknown58.dispose();
    unknownc0 = &GmkMobInsts::seqUpdatePopDepop;
  }
}

void GmkMobInsts::disposeGobInsts(bool isFadeOut) {
  if (isGobInstExist()) {
    size_t num = unknowna8->size();
    for (size_t i = 0; i < num; i++) {
      gf::GF_OBJ_HANDLE *handle = (*unknowna8)[i];
      if (handle != gf::INVALID_HANDLE) {
        if (isFadeOut) {
          gmk::disposeGobInst(handle, 1.0f);
        } else {
          unknown00.unknown00->unbindToGameObj(handle);
          gf::GfObjUtil::destroy(handle);
        }
      }
    }
    if (isFadeOut) {
      unknownc0 = &GmkMobInsts::seqWaitToFadeOutOfGobInst;
      return;
    }
    unknowna8->destroy();
    unknown58.dispose();
  }
}

void GmkMobInsts::createGobInsts() {
  disposeGobInsts(false);
  CBdatWrapper bdat = {unknown00.unknown08};
  unknown58.create(bdat, unknown00.unknown10);
  unknowna8->destroy();
  unknowna8->setAllocator(gf::getAllocator(gf::ALLOCATOR_DEFAULT));
  unknowna8->reserve(unknown58.unknown40);
}

void GmkMobInsts::disposeSquad() { mm::mtl::safeRelease(unknownb0); }

void GmkMobInsts::dispose() {
  unknownc0 = nullptr;
  unknownb8 &= ~(MATCHED_UNKNOWN_0 | MATCHED_UNKNOWN_1 | MATCHED_UNKNOWN_2);
  disposeSquad();
  disposeGobInsts(false);
  if (unknowna8 != nullptr) {
    delete unknowna8;
    unknowna8 = nullptr;
  }
  unknown00 = CreateInfo();
}

bool GmkMob::isValid() const {
  if (AGmkBase::isValid() && unknown48.isValid()) {
    return true;
  }
  return false;
}

void GmkMob::create(const CreateInfo &info) {
  if (info.unknown10 != nullptr) {
    AGmkBase::create(info);
    GmkMobInsts::CreateInfo createInfo;
    createInfo.unknown00 = this;
    createInfo.unknown08 = unknown08.unknown00->getBindedBdatFp();
    createInfo.unknown10 = info.unknown18;
    unknown48.create(createInfo);
  }
}

void GmkMob::dispose() {
  unknown48.dispose();
  AGmkBase::dispose();
}

void GmkMobList::onResetUpdateGmkIndex() {
  unknown228++;
  if (unknown228 > 1) {
    unknown228 = 0;
    resetMobPopDistSq();
  }
}

void GmkMob::onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) {
  if (event == gf::IGfObjListener::OBJEVT_DESTROY && handle != gf::INVALID_HANDLE) {
    gf::GfObjAcc acc(handle);
    if (acc.isValid()) {
      acc.setUserData(gf::OBJ_USER_DATA_GMK, 0);
    }
    unknown48.removeGobInst(handle);
  }
}

void GmkMob::update(f32 deltaTime) {
  debugUpdateMmf();
  if (!isValid()) {
    return;
  }
  GmkMobInsts::UpdateInfo info;
  PopXformFinder finder;
  finder.unknown08 = this;
  info.unknown00 = deltaTime;
  info.unknown08 = &unknown08.unknown08->unknown00;
  info.unknown10 = &finder;
  unknown48.update(info);
}

GmkType GmkMob::getGmkType() const { return GMK_TYPE; }

void GmkMob::debugDraw() const { isValid(); }

} // namespace gmk

template void mm::mtl::Vector<gmk::GmkMob::BdatInfo>::expand(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkMob::BdatInfo>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkMob::BdatInfo>::resize(size_t);
