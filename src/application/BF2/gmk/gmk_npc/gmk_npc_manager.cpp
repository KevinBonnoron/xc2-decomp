#include "gmk/gmk_npc/gmk_npc_manager.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_object_type.h"
#include "gf/game/gf_game_manager.h"
#include "gf/object/component/behavior/gf_com_behavior_npc.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_factory.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "gmk/gmk_manager.h"
#include "gmk/gmk_npc/gmk_npc.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/intrusive_list.h"

namespace gmk {

int GmkNpcManager::getNpcIdInfoIdxFromNpcId(int npcId) {
  u8 *chrDr = gf::GfDataBdat::getFP(gf::BDAT_CHR_DR);
  u8 *chrBl = gf::GfDataBdat::getFP(gf::BDAT_CHR_BL);
  u8 *npcList = gf::GfDataBdat::getFP(gf::BDAT_RSC_NPC_LIST);
  if (Bdat::getIdTop(chrDr) <= npcId && npcId < Bdat::getIdTop(chrDr) + Bdat::getIdCount(chrDr)) {
    return npcId - Bdat::getIdTop(chrDr);
  }
  if (Bdat::getIdTop(chrBl) <= npcId && npcId < Bdat::getIdTop(chrBl) + Bdat::getIdCount(chrBl)) {
    return Bdat::getIdCount(chrDr) + npcId - Bdat::getIdTop(chrBl);
  }
  int drCount = Bdat::getIdCount(chrDr);
  int blCount = Bdat::getIdCount(chrBl);
  int listTop = Bdat::getIdTop(npcList);
  return drCount + npcId + blCount - listTop;
}

void GmkNpcIdInfo::addGmkNpc(AGmkNpc *npc) {
  for (mm::mtl::IntrusiveList<AGmkNpc>::iterator position = unknown10->begin(); position != unknown10->end(); ++position) {
    if (position.get()->getBindedBdatId() >= npc->getBindedBdatId()) {
      unknown10->insert(position, npc);
      break;
    }
  }
  if (!npc->intoNode()) {
    unknown10->push_back(npc);
  }
  npc->unknown18 = this;
}

// Inferred role: destroys the game object right away and activates the first NPC whose pop condition is matched; original name unknown.
inline void GmkNpcIdInfo::unknown001() {
  unknown18->unbindToGameObj(unknown30);
  gf::GfObjUtil::destroy(unknown30);
  unknown30 = gf::INVALID_HANDLE;
  unknown18 = nullptr;
  for (mm::mtl::IntrusiveList<AGmkNpc>::iterator it = unknown10->begin(); it != unknown10->end(); ++it) {
    if (it.get()->isPopCondMatched()) {
      setActiveGmkNpc(it.get());
      break;
    }
  }
}

void GmkNpcIdInfo::dispose() {
  if (unknown30 != gf::INVALID_HANDLE) {
    unknown001();
  }
  setActiveGmkNpc(nullptr);
  if (unknown10 != nullptr) {
    delete unknown10;
    unknown10 = nullptr;
  }
  unknown00 = 0;
  unknown08 = nullptr;
}

void GmkNpcIdInfo::disposeGobInst(bool isFadeOut) {
  if (unknown30 == gf::INVALID_HANDLE) {
    return;
  }
  if (isFadeOut) {
    gmk::disposeGobInst(unknown30, 1.0f);
  } else {
    unknown001();
  }
}

void GmkNpcIdInfo::update(f32 deltaTime, bool isCreate) {
  if (!unknown002()) {
    return;
  }
  if (!isInterestPosExist()) {
    return;
  }
  {
    gf::GfObjAcc acc(unknown30);
    gf::GfObj *obj = acc.getObj();
    if (obj != nullptr) {
      if (obj->unknown28 == gf::OBJECT_TYPE_ENEMY) {
        if (acc.isBattle()) {
          return;
        }
      } else if (obj->unknown28 == gf::OBJECT_TYPE_NPC) {
        gf::GfComBehaviorNpc *behavior = obj->getComponent<gf::GfComBehaviorNpc>();
        if (behavior != nullptr && behavior->unknown100) {
          return;
        }
      }
    }
  }
  for (mm::mtl::IntrusiveList<AGmkNpc>::iterator it = unknown10->begin(); it != unknown10->end(); ++it) {
    if (it.get()->isPopCondMatched()) {
      setActiveGmkNpc(it.get());
      break;
    }
  }
  if (unknown30 == gf::INVALID_HANDLE) {
    if (isCreate && unknown18 != nullptr && unknown18->isPopDistCondMatched()) {
      createGobInst();
    }
  } else if (unknown18->isDepopCondMatched() || unknown18->isDepopDistCondMatched()) {
    disposeGobInst(true);
  }
}

void GmkNpcIdInfo::createGobInst() {
  if (unknown30 != gf::INVALID_HANDLE) {
    unknown001();
  }
  unknown30 = gf::GfObjFactory::createGmkNpc({unknown18->getBindedBdatFp()}, unknown18->getBindedBdatId());
  if (unknown30 != gf::INVALID_HANDLE) {
    unknown18->bindToGameObj(unknown30);
    unknown18->validateDisp();
    gf::GfObjSetupNpc *setup = gf::GfObjUtil::getObjSetup<gf::GfObjSetupNpc>(unknown30);
    mm::Vec3 position;
    mm::Vec3 rotation;
    unknown18->findPopPosRot(position, rotation);
    setup->unknown20 = position;
    setup->unknown30 = rotation;
  }
}

void GmkNpcManager::update(f32 deltaTime) {
  bool isFadeout = gf::GfGameManager::isFadeout();
  u32 num = unknown08.size();
  if (isFadeout) {
    for (u32 i = 0; i < num; i++) {
      GmkNpcIdInfo &info = unknown08[i];
      if (info.unknown002()) {
        info.update(deltaTime, unknown3c);
      }
    }
    return;
  }
  if (num <= unknown38) {
    unknown38 = 0;
  }
  u32 updateNum = unknown34 < num ? unknown34 : num;
  for (u32 i = 0; i < updateNum; i++, unknown38++) {
    if (num <= unknown38) {
      unknown38 = 0;
      return;
    }
    GmkNpcIdInfo &info = unknown08[unknown38];
    if (info.unknown002()) {
      info.update(deltaTime, unknown3c);
    }
  }
}

void GmkNpcIdInfo::removeGmkNpc(AGmkNpc *npc) {
  if (npc == nullptr) {
    return;
  }
  npc->unknown18 = nullptr;
  if (unknown18 == npc) {
    if (unknown30 != gf::INVALID_HANDLE) {
      unknown001();
    }
    unknown18 = nullptr;
  }
  unknown10->erase(npc);
}

} // namespace gmk
