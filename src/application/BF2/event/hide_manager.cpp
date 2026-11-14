#include "event/hide_manager.h"

#include <stddef.h>

#include "event/memory_manager.h"
#include "gf/game/event/gf_game_event.h"
#include "gmk/gmk_manager.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"

namespace event {

constexpr u32 PRIMARY_LIST_DISP_UNKNOWN_6 = 6;   // Inferred role: primary list disp type; original name unknown.
constexpr u32 SECONDARY_LIST_DISP_UNKNOWN_5 = 5; // Inferred role: secondary list disp type; original name unknown.

HideManager::Obj::Obj(OBJ_TYPE type, u32 id) : m_type(type), unknown04(id), unknown08(false), m_now(false) {
  switch (type) {
  case OBJ_TYPE_UNKNOWN_1:
    unknown08 = false;
    break;
  case OBJ_TYPE_UNKNOWN_2:
    unknown08 = false;
    break;
  case OBJ_TYPE_UNKNOWN_3:
    unknown08 = false;
    break;
  case OBJ_TYPE_UNKNOWN_4:
    unknown08 = false;
    break;
  case OBJ_TYPE_UNKNOWN_5:
    unknown08 = false;
    break;
  case OBJ_TYPE_UNKNOWN_6:
    unknown08 = !gf::GfGameEvent::isMapLodDisp(id);
    break;
  default:
    break;
  }
  m_now = unknown08;
}

void HideManager::Obj::clear() {
  switch (m_type) {
  case OBJ_TYPE_UNKNOWN_1:
    gf::GfGameEvent::setGmkBdatDisp(gmk::GMK_TYPE_NPC, unknown04, !unknown08);
    break;
  case OBJ_TYPE_UNKNOWN_2:
    gf::GfGameEvent::setGmkBdatDisp(gmk::GMK_TYPE_ROUTED_NPC, unknown04, !unknown08);
    break;
  case OBJ_TYPE_UNKNOWN_3:
    gf::GfGameEvent::setGmkBdatDisp(gmk::GMK_TYPE_MAP_OBJ, unknown04, !unknown08);
    break;
  case OBJ_TYPE_UNKNOWN_4:
    gf::GfGameEvent::setGmkIdDisp(gmk::GMK_TYPE_EFFECT, unknown04 - 1, !unknown08);
    break;
  case OBJ_TYPE_UNKNOWN_5:
    gf::GfGameEvent::setGmkBdatDisp(gmk::GMK_TYPE_SE, unknown04, !unknown08);
    break;
  case OBJ_TYPE_UNKNOWN_6:
    gf::GfGameEvent::setMapLodDisp(unknown04, !unknown08);
    break;
  default:
    break;
  }
  m_now = unknown08;
}

void HideManager::Obj::exec(bool isHide) {
  switch (m_type) {
  case OBJ_TYPE_UNKNOWN_1:
    gf::GfGameEvent::setGmkBdatDisp(gmk::GMK_TYPE_NPC, unknown04, !isHide);
    break;
  case OBJ_TYPE_UNKNOWN_2:
    gf::GfGameEvent::setGmkBdatDisp(gmk::GMK_TYPE_ROUTED_NPC, unknown04, !isHide);
    break;
  case OBJ_TYPE_UNKNOWN_3:
    gf::GfGameEvent::setGmkBdatDisp(gmk::GMK_TYPE_MAP_OBJ, unknown04, !isHide);
    break;
  case OBJ_TYPE_UNKNOWN_4:
    gf::GfGameEvent::setGmkIdDisp(gmk::GMK_TYPE_EFFECT, unknown04 - 1, !isHide);
    break;
  case OBJ_TYPE_UNKNOWN_5:
    gf::GfGameEvent::setGmkBdatDisp(gmk::GMK_TYPE_SE, unknown04, !isHide);
    break;
  case OBJ_TYPE_UNKNOWN_6:
    gf::GfGameEvent::setMapLodDisp(unknown04, !isHide);
    break;
  default:
    break;
  }
  m_now = isHide;
}

HideManager::OBJ_TYPE HideManager::Obj::getType() const { return m_type; }

bool HideManager::Obj::getNow() const { return m_now; }

HideManager::HideManager() : unknown10(0), m_group(GRP_TYPE_UNKNOWN_0) {}

void HideManager::clear() {
  hideGroup(false);
  hideList(false);
  resetHideObj();
  unknown10 = 0;
  m_group = GRP_TYPE_UNKNOWN_0;
}

void HideManager::hideList(bool isHide) {
  if (isHide) {
    if (!(unknown10 & FLAG_UNKNOWN_1)) {
      gf::GfGameEvent::setDisp(PRIMARY_LIST_DISP_UNKNOWN_6, unknown18, false);
      gf::GfGameEvent::setDisp(SECONDARY_LIST_DISP_UNKNOWN_5, unknown1020, false);
      unknown10 |= FLAG_UNKNOWN_1;
    }
  } else if (unknown10 & FLAG_UNKNOWN_1) {
    gf::GfGameEvent::setDisp(PRIMARY_LIST_DISP_UNKNOWN_6, unknown18, true);
    gf::GfGameEvent::setDisp(SECONDARY_LIST_DISP_UNKNOWN_5, unknown1020, true);
    unknown10 &= ~FLAG_UNKNOWN_1;
  }
}

void HideManager::resetHideObj() {
  for (Obj **it = unknown2028.begin(); it != unknown2028.end(); it++) {
    Obj *obj = *it;
    obj->clear();
    delete obj;
  }
  unknown2028.clear();
}

void HideManager::update() {}

void HideManager::defineGroup(GRP_TYPE group) { m_group = group; }

HideManager::GRP_TYPE HideManager::getGroup() const { return m_group; }

void HideManager::defineList(mm::mtl::FixedVector<u32, DEFINE_LIST_UNKNOWN_256> primaryList, mm::mtl::FixedVector<u32, DEFINE_LIST_UNKNOWN_256> secondaryList) {
  unknown18.clear();
  for (size_t i = 0; i < primaryList.size(); i++) {
    unknown18.push_back(primaryList[i]);
  }
  unknown1020.clear();
  for (size_t i = 0; i < secondaryList.size(); i++) {
    unknown1020.push_back(secondaryList[i]);
  }
}

void HideManager::hideObj(OBJ_TYPE type, u32 id, bool isHide) {
  Obj *obj = searchObj(type, id);
  if (obj == nullptr) {
    obj = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) Obj(type, id);
    unknown2028.push_back(obj);
  }
  obj->exec(isHide);
}

HideManager::Obj *HideManager::searchObj(OBJ_TYPE type, u32 id) {
  for (size_t i = 0; i < unknown2028.size(); i++) {
    if (unknown2028[i]->getType() == type && unknown2028[i]->getID() == id) {
      return unknown2028[i];
    }
  }
  return nullptr;
}

void HideManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_UNKNOWN_4:
  case MSG_TYPE_UNKNOWN_12:
    clear();
    break;
  case MSG_TYPE_UNKNOWN_10:
    hideGroup(false);
    hideList(false);
    resetHideObj();
    break;
  default:
    break;
  }
}

} // namespace event
