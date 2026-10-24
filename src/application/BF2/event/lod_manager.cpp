#include "event/lod_manager.h"

#include <stddef.h>

#include "event/memory_manager.h"
#include "gf/game/event/gf_game_event.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"

namespace event {

LodManager::Obj::Obj(u32 id) : unknown00(id) { unknown04 = gf::GfGameEvent::isMapLodAnimReverse(id); }

void LodManager::Obj::clear() { gf::GfGameEvent::setMapLodAnim(unknown00, unknown04, true); }

void LodManager::Obj::exec(bool isReverse, bool isSkip) {
  if (!isSkip) {
    gf::GfGameEvent::setMapLodAnim(unknown00, !isReverse, true);
  }
  gf::GfGameEvent::setMapLodAnim(unknown00, isReverse, isSkip);
}

LodManager::LodManager() {}

void LodManager::clear() {
  for (Obj **it = unknown10.begin(); it != unknown10.end(); it++) {
    Obj *obj = *it;
    obj->clear();
    delete obj;
  }
  unknown10.clear();
}

void LodManager::resetPlayAnm() {
  for (Obj **it = unknown10.begin(); it != unknown10.end(); it++) {
    Obj *obj = *it;
    obj->clear();
    delete obj;
  }
  unknown10.clear();
}

void LodManager::update() {}

void LodManager::playAnm(u32 id, bool isReverse, bool isSkip) {
  Obj *obj = searchObj(id);
  if (obj == nullptr) {
    obj = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) Obj(id);
    unknown10.push_back(obj);
  }
  obj->exec(isReverse, isSkip);
}

LodManager::Obj *LodManager::searchObj(u32 id) {
  for (size_t i = 0; i < unknown10.size(); i++) {
    if (unknown10[i]->getID() == id) {
      return unknown10[i];
    }
  }
  return nullptr;
}

void LodManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_INIT:
    clear();
    break;
  case MSG_TYPE_CLEAR:
    clear();
    break;
  case MSG_TYPE_END_SCENE:
    resetPlayAnm();
    break;
  default:
    break;
  }
}

} // namespace event
