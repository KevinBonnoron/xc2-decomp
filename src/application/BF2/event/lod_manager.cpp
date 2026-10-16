#include "event/lod_manager.h"

#include <stddef.h>

#include "event/memory_manager.h"
#include "gf/game/event/gf_game_event.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"

namespace event {

LodManager::Obj::Obj(u32 id) : mID(id) { mIsReverse = gf::GfGameEvent::isMapLodAnimReverse(id); }

void LodManager::Obj::clear() { gf::GfGameEvent::setMapLodAnim(mID, mIsReverse, true); }

void LodManager::Obj::exec(bool isReverse, bool isSkip) {
  if (!isSkip) {
    gf::GfGameEvent::setMapLodAnim(mID, !isReverse, true);
  }
  gf::GfGameEvent::setMapLodAnim(mID, isReverse, isSkip);
}

LodManager::LodManager() {}

void LodManager::clear() {
  for (Obj **it = objs.begin(); it != objs.end(); it++) {
    Obj *obj = *it;
    obj->clear();
    delete obj;
  }
  objs.clear();
}

void LodManager::resetPlayAnm() {
  for (Obj **it = objs.begin(); it != objs.end(); it++) {
    Obj *obj = *it;
    obj->clear();
    delete obj;
  }
  objs.clear();
}

void LodManager::update() {}

void LodManager::playAnm(u32 id, bool isReverse, bool isSkip) {
  Obj *obj = searchObj(id);
  if (obj == nullptr) {
    obj = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) Obj(id);
    objs.push_back(obj);
  }
  obj->exec(isReverse, isSkip);
}

LodManager::Obj *LodManager::searchObj(u32 id) {
  for (size_t i = 0; i < objs.size(); i++) {
    if (objs[i]->getID() == id) {
      return objs[i];
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
