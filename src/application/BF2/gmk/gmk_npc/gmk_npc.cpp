#include "gmk/gmk_npc/gmk_npc.h"

#include "gf/data/gf_bdat_wrapper.h"
#include "gf/game/gf_game_manager.h"
#include "gmk/gmk_bdat.h"
#include "gmk/gmk_npc/gmk_npc_manager.h"
#include "gmk/gmk_set.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/vector.h"

namespace gmk {

GmkNpcList::GmkNpcList(u32 updateGmkNumPerFrame) : TGmkList(0) {}

void GmkNpcList::createGmk(void *data) {
  TGmkList::createGmk(data);
  GmkNpcManager *manager = &getCreateInfo().unknown08->unknown178;
  u32 num = getInstNum();
  for (u32 i = 0; i < num; i++) {
    manager->addGmkNpc(&gmkInsts[i]);
  }
}

void GmkNpcList::disposeGmk() {
  GmkSet *set = getCreateInfo().unknown08;
  if (set != nullptr) {
    GmkNpcManager *manager = &set->unknown178;
    u32 num = getInstNum();
    for (u32 i = 0; i < num; i++) {
      manager->removeGmkNpc(&gmkInsts[i]);
    }
  }
  TGmkList::disposeGmk();
}

GmkType GmkNpc::getGmkType() const { return GMK_TYPE; }

u8 *GmkNpc::getBindedBdatFp() const { return AGmkBase::getBindedBdatFp(); }

void GmkNpc::debugDraw() const {
  if (isValid()) {
    getBdatInfo()->isPopCommonCondMatched(*this);
  }
}

void GmkNpc::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  unknown02 = bdat.getValCheck("Group", id, BDAT_TYPE_U16);
  unknown04 = bdat.getValCheck("BattleReaction", id, BDAT_TYPE_U16);
  if (unknown02 == 0) {
    unknown06 = ScenarioFlagCond(bdat.getValCheck("ScenarioFlagMin", id, BDAT_TYPE_U16), bdat.getValCheck("ScenarioFlagMax", id, BDAT_TYPE_U16));
    unknown0a = QuestFlagCond(bdat.getValCheck("QuestFlag", id, BDAT_TYPE_U16), bdat.getValCheck("QuestFlagMin", id, BDAT_TYPE_U8), bdat.getValCheck("QuestFlagMax", id, BDAT_TYPE_U8));
    u16 timeRange = bdat.getValCheck("TimeRange", id, BDAT_TYPE_U16);
    unknown10.unknown08 = timeRange;
    unknown00 = bdat.getValCheck("Condition", id, BDAT_TYPE_U16);
  }
  u16 visibleXZ = bdat.getValCheck("Visible_XZ", id, BDAT_TYPE_U16);
  u16 visibleY = bdat.getValCheck("Visible_Y", id, BDAT_TYPE_U16);
  unknown20.set(visibleXZ, visibleY);
  u16 invisibleXZ = DistHvCond::clampDepopDist(bdat.getValCheck("Invisible_XZ", id, BDAT_TYPE_U16), visibleXZ);
  u16 invisibleY = DistHvCond::clampDepopDist(bdat.getValCheck("Invisible_Y", id, BDAT_TYPE_U16), visibleY);
  unknown28.set(invisibleXZ, invisibleY);
}

void GmkNpc::BdatInfo::debugDraw(const AGmkBase &gmk) const {}

bool GmkNpc::findPopPosRot(mm::Vec3 &position, mm::Vec3 &rotation) const {
  position = AGmkBase::unknown08.unknown08->unknown00;
  rotation = AGmkBase::unknown08.unknown08->unknown10;
  return true;
}

bool GmkNpc::isPopDistCondMatched() const {
  if (!isValid()) {
    return false;
  }
  return getBdatInfo()->unknown20.isMatch(AGmkBase::unknown08.unknown08->unknown00);
}

bool GmkNpc::isDepopDistCondMatched() const {
  if (!isValid()) {
    return false;
  }
  return !getBdatInfo()->unknown28.isMatch(AGmkBase::unknown08.unknown08->unknown00);
}

bool GmkNpc::isPopCondMatchedExceptDist() const {
  if (AGmkNpc::unknown18 != nullptr && AGmkNpc::unknown18->unknown18 == this) {
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
