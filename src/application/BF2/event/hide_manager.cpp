#include "event/hide_manager.h"

#include <stddef.h>

#include "event/memory_manager.h"
#include "gf/game/event/gf_game_event.h"
#include "gmk/gmk_manager.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"

namespace event {

constexpr u32 PRIMARY_LIST_DISP_TYPE = 6;
constexpr u32 SECONDARY_LIST_DISP_TYPE = 5;

HideManager::Obj::Obj(OBJ_TYPE type, u32 id) : mType(type), mID(id), mIsHideOrg(false), mIsHide(false) {
  switch (type) {
  case OBJ_TYPE_NPC:
    mIsHideOrg = false;
    break;
  case OBJ_TYPE_ROUTED_NPC:
    mIsHideOrg = false;
    break;
  case OBJ_TYPE_MAP_OBJ:
    mIsHideOrg = false;
    break;
  case OBJ_TYPE_EFFECT:
    mIsHideOrg = false;
    break;
  case OBJ_TYPE_SE:
    mIsHideOrg = false;
    break;
  case OBJ_TYPE_MAP_LOD:
    mIsHideOrg = !gf::GfGameEvent::isMapLodDisp(id);
    break;
  default:
    break;
  }
  mIsHide = mIsHideOrg;
}

void HideManager::Obj::clear() {
  switch (mType) {
  case OBJ_TYPE_NPC:
    gf::GfGameEvent::setGmkBdatDisp(gmk::GMK_TYPE_NPC, mID, !mIsHideOrg);
    break;
  case OBJ_TYPE_ROUTED_NPC:
    gf::GfGameEvent::setGmkBdatDisp(gmk::GMK_TYPE_ROUTED_NPC, mID, !mIsHideOrg);
    break;
  case OBJ_TYPE_MAP_OBJ:
    gf::GfGameEvent::setGmkBdatDisp(gmk::GMK_TYPE_MAP_OBJ, mID, !mIsHideOrg);
    break;
  case OBJ_TYPE_EFFECT:
    gf::GfGameEvent::setGmkIdDisp(gmk::GMK_TYPE_EFFECT, mID - 1, !mIsHideOrg);
    break;
  case OBJ_TYPE_SE:
    gf::GfGameEvent::setGmkBdatDisp(gmk::GMK_TYPE_SE, mID, !mIsHideOrg);
    break;
  case OBJ_TYPE_MAP_LOD:
    gf::GfGameEvent::setMapLodDisp(mID, !mIsHideOrg);
    break;
  default:
    break;
  }
  mIsHide = mIsHideOrg;
}

void HideManager::Obj::exec(bool isHide) {
  switch (mType) {
  case OBJ_TYPE_NPC:
    gf::GfGameEvent::setGmkBdatDisp(gmk::GMK_TYPE_NPC, mID, !isHide);
    break;
  case OBJ_TYPE_ROUTED_NPC:
    gf::GfGameEvent::setGmkBdatDisp(gmk::GMK_TYPE_ROUTED_NPC, mID, !isHide);
    break;
  case OBJ_TYPE_MAP_OBJ:
    gf::GfGameEvent::setGmkBdatDisp(gmk::GMK_TYPE_MAP_OBJ, mID, !isHide);
    break;
  case OBJ_TYPE_EFFECT:
    gf::GfGameEvent::setGmkIdDisp(gmk::GMK_TYPE_EFFECT, mID - 1, !isHide);
    break;
  case OBJ_TYPE_SE:
    gf::GfGameEvent::setGmkBdatDisp(gmk::GMK_TYPE_SE, mID, !isHide);
    break;
  case OBJ_TYPE_MAP_LOD:
    gf::GfGameEvent::setMapLodDisp(mID, !isHide);
    break;
  default:
    break;
  }
  mIsHide = isHide;
}

HideManager::OBJ_TYPE HideManager::Obj::getType() const { return mType; }

bool HideManager::Obj::getNow() const { return mIsHide; }

HideManager::HideManager() : flags(0), mGroup(GRP_TYPE_NONE) {}

void HideManager::clear() {
  hideGroup(false);
  hideList(false);
  resetHideObj();
  flags = 0;
  mGroup = GRP_TYPE_NONE;
}

void HideManager::hideList(bool isHide) {
  if (isHide) {
    if (!(flags & FLAG_HIDE_LIST)) {
      gf::GfGameEvent::setDisp(PRIMARY_LIST_DISP_TYPE, mPrimaryList, false);
      gf::GfGameEvent::setDisp(SECONDARY_LIST_DISP_TYPE, mSecondaryList, false);
      flags |= FLAG_HIDE_LIST;
    }
  } else if (flags & FLAG_HIDE_LIST) {
    gf::GfGameEvent::setDisp(PRIMARY_LIST_DISP_TYPE, mPrimaryList, true);
    gf::GfGameEvent::setDisp(SECONDARY_LIST_DISP_TYPE, mSecondaryList, true);
    flags &= ~FLAG_HIDE_LIST;
  }
}

void HideManager::resetHideObj() {
  for (Obj **it = objs.begin(); it != objs.end(); it++) {
    Obj *obj = *it;
    obj->clear();
    delete obj;
  }
  objs.clear();
}

void HideManager::update() {}

void HideManager::defineGroup(GRP_TYPE group) { mGroup = group; }

HideManager::GRP_TYPE HideManager::getGroup() const { return mGroup; }

void HideManager::defineList(mm::mtl::FixedVector<u32, DEFINE_LIST_COUNT> primaryList, mm::mtl::FixedVector<u32, DEFINE_LIST_COUNT> secondaryList) {
  mPrimaryList.clear();
  for (size_t i = 0; i < primaryList.size(); i++) {
    mPrimaryList.push_back(primaryList[i]);
  }
  mSecondaryList.clear();
  for (size_t i = 0; i < secondaryList.size(); i++) {
    mSecondaryList.push_back(secondaryList[i]);
  }
}

void HideManager::hideObj(OBJ_TYPE type, u32 id, bool isHide) {
  Obj *obj = searchObj(type, id);
  if (obj == nullptr) {
    obj = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) Obj(type, id);
    objs.push_back(obj);
  }
  obj->exec(isHide);
}

HideManager::Obj *HideManager::searchObj(OBJ_TYPE type, u32 id) {
  for (size_t i = 0; i < objs.size(); i++) {
    if (objs[i]->getType() == type && objs[i]->getID() == id) {
      return objs[i];
    }
  }
  return nullptr;
}

void HideManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_INIT:
  case MSG_TYPE_CLEAR:
    clear();
    break;
  case MSG_TYPE_END_SCENE:
    hideGroup(false);
    hideList(false);
    resetHideObj();
    break;
  default:
    break;
  }
}

} // namespace event
