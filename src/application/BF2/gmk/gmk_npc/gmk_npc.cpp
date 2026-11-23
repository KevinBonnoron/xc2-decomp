#include "gmk/gmk_npc/gmk_npc.h"
#include "gmk/gmk_list_impl.h" // IWYU pragma: keep

#include "gf/data/gf_bdat_wrapper.h"
#include "gf/game/gf_game_manager.h"
#include "gf/object/component/behavior/gf_com_behavior_npc.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "gmk/gmk_bdat.h"
#include "gmk/gmk_npc/gmk_npc_manager.h"
#include "gmk/gmk_set.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/vector.h"

namespace gmk {

template bool TGmkList<GmkNpc, GmkNpc::BdatInfo, 4411470u, 4u, GmkNpcGob>::initGmkBdatInfo(GmkNpc::BdatInfo &, int &, const AGmkBase &);

void AGmkNpc::debugUpdate(f32 deltaTime) {}

GmkNpcList::GmkNpcList(u32 updateGmkNumPerFrame) : TGmkList(0) {}

void GmkNpcList::createGmk(void *data) {
  TGmkList::createGmk(data);
  GmkNpcManager *manager = &getCreateInfo().m_gmkSet->m_gmkNpcManager;
  u32 num = getInstNum();
  for (u32 i = 0; i < num; i++) {
    manager->addGmkNpc(&gmkInsts[i]);
  }
}

void GmkNpcList::disposeGmk() {
  GmkSet *set = getCreateInfo().m_gmkSet;
  if (set != nullptr) {
    GmkNpcManager *manager = &set->m_gmkNpcManager;
    u32 num = getInstNum();
    for (u32 i = 0; i < num; i++) {
      manager->removeGmkNpc(&gmkInsts[i]);
    }
  }
  TGmkList::disposeGmk();
}

GmkType GmkNpc::getGmkType() const { return GMK_TYPE; }

gf::GF_OBJ_HANDLE *GmkNpc::getGobInst() const {
  if (AGmkNpc::m_gmkNpcIdInfo == nullptr) {
    return gf::unknown020;
  }
  gf::GF_OBJ_HANDLE *handle = AGmkNpc::m_gmkNpcIdInfo->unknown30;
  if (this != getBindedGmkInst(handle)) {
    return gf::unknown020;
  }
  return handle;
}

void GmkNpc::validateDisp() const {
  gf::GF_OBJ_HANDLE *handle = getGobInst();
  if (handle != gf::unknown020) {
    bool isDisp = unknown68 && debugIsDispGmkType(getGmkType());
    setEventDisp(handle, isDisp);
  }
}

void GmkNpc::onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) {
  AGmkBase::onGobEvent(event, handle);
  if (event == gf::IGfObjListener::OBJEVT_UNKNOWN_3) {
    unbindToGameObj(handle);
    if (AGmkNpc::m_gmkNpcIdInfo->unknown30 == handle) {
      AGmkNpc::m_gmkNpcIdInfo->disposeGobInst(false);
    }
  }
}

u8 *GmkNpc::getBindedBdatFp() const { return AGmkBase::getBindedBdatFp(); }

void GmkNpc::debugDraw() const {
  if (isValid()) {
    getBdatInfo()->isPopCommonCondMatched(*this);
  }
}

void GmkNpc::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  unknown02 = bdat.getValCheck("Group", id, BDAT_TYPE_UNKNOWN_2);
  unknown04 = bdat.getValCheck("BattleReaction", id, BDAT_TYPE_UNKNOWN_2);
  if (unknown02 == 0) {
    m_scenarioFlagCond = ScenarioFlagCond(bdat.getValCheck("ScenarioFlagMin", id, BDAT_TYPE_UNKNOWN_2), bdat.getValCheck("ScenarioFlagMax", id, BDAT_TYPE_UNKNOWN_2));
    m_questFlagCond =
        QuestFlagCond(bdat.getValCheck("QuestFlag", id, BDAT_TYPE_UNKNOWN_2), bdat.getValCheck("QuestFlagMin", id, BDAT_TYPE_UNKNOWN_1), bdat.getValCheck("QuestFlagMax", id, BDAT_TYPE_UNKNOWN_1));
    u16 timeRange = bdat.getValCheck("TimeRange", id, BDAT_TYPE_UNKNOWN_2);
    m_timeCond.unknown08 = timeRange;
    unknown00 = bdat.getValCheck("Condition", id, BDAT_TYPE_UNKNOWN_2);
  }
  u16 visibleXZ = bdat.getValCheck("Visible_XZ", id, BDAT_TYPE_UNKNOWN_2);
  u16 visibleY = bdat.getValCheck("Visible_Y", id, BDAT_TYPE_UNKNOWN_2);
  unknown20.set(visibleXZ, visibleY);
  u16 invisibleXZ = DistHvCond::clampDepopDist(bdat.getValCheck("Invisible_XZ", id, BDAT_TYPE_UNKNOWN_2), visibleXZ);
  u16 invisibleY = DistHvCond::clampDepopDist(bdat.getValCheck("Invisible_Y", id, BDAT_TYPE_UNKNOWN_2), visibleY);
  unknown28.set(invisibleXZ, invisibleY);
}

void GmkNpc::BdatInfo::debugDraw(const AGmkBase &gmk) const {}

void GmkNpc::bindToGameObj(gf::GF_OBJ_HANDLE *handle) const {
  AGmkBase::bindToGameObj(handle);
  gf::GfObjAcc acc(handle);
  gf::GfObj *obj = acc.getObj();
  if (obj == nullptr || acc.isDestroy() || acc.testFlag(gf::OBJ_FLAG_UNKNOWN_17)) {
    return;
  }
  gf::GfComBehaviorNpc *behavior = obj->getComponent<gf::GfComBehaviorNpc>();
  if (behavior != nullptr) {
    behavior->validateBindedGmkInstInfo(true);
  }
}

bool GmkNpc::findPopPosRot(mm::Vec3 &position, mm::Vec3 &rotation) const {
  position = AGmkBase::m_createBaseInfo.m_xform->unknown00;
  rotation = AGmkBase::m_createBaseInfo.m_xform->unknown10;
  return true;
}

bool GmkNpc::isPopDistCondMatched() const {
  if (!isValid()) {
    return false;
  }
  return getBdatInfo()->unknown20.isMatch(AGmkBase::m_createBaseInfo.m_xform->unknown00);
}

bool GmkNpc::isDepopDistCondMatched() const {
  if (!isValid()) {
    return false;
  }
  return !getBdatInfo()->unknown28.isMatch(AGmkBase::m_createBaseInfo.m_xform->unknown00);
}

bool GmkNpc::isPopCondMatchedExceptDist() const {
  if (AGmkNpc::m_gmkNpcIdInfo != nullptr && AGmkNpc::m_gmkNpcIdInfo->m_aGmkNpc == this) {
    return isPopCondMatched();
  }
  return false;
}

bool GmkNpc::isPopCondMatched() const {
  if (!isValid()) {
    return false;
  }
  const BdatInfo *info = getBdatInfo();
  if (!gf::GfGameManager::isBattle() || info->unknown04 != 0) {
    return info->isPopCommonCondMatched(*this);
  }
  return false;
}

bool GmkNpc::isDepopCondMatched() const {
  if (!isValid()) {
    return false;
  }
  return !getBdatInfo()->isPopCommonCondMatched(*this);
}

} // namespace gmk

template void mm::mtl::Vector<gmk::GmkNpc::BdatInfo>::expand(size_t, size_t);

template void mm::mtl::Vector<gmk::GmkNpc::BdatInfo>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkNpc::BdatInfo>::resize(size_t);
template void mm::mtl::Vector<gmk::GmkNpc>::expand(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkNpc>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkNpc>::resize(size_t);
