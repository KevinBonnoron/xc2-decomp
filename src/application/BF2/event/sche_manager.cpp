#include "event/sche_manager.h"

#include <stddef.h>

#include "event/manager.h"
#include "event/memory_manager.h"
#include "gf/game/gf_game_party.h"
#include "gf/object/gf_obj_handle.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace event {

ScheManager::ScheManager() : flags(0) {}

void ScheManager::create() {}

void ScheManager::destroy() {
  for (size_t i = 0; i < mSchedulers.size(); i++) {
    if (mSchedulers[i] != nullptr) {
      delete mSchedulers[i];
      mSchedulers[i] = nullptr;
    }
  }
  mSchedulers.clear();
}

bool ScheManager::isPlay(Scheduler::ORDER order, gf::GF_OBJ_HANDLE *handle) {
  if (handle == gf::INVALID_HANDLE) {
    for (Scheduler **it = mSchedulers.begin(); it != mSchedulers.end(); it++) {
      if ((*it)->isPlay(order)) {
        return true;
      }
    }
    return false;
  } else {
    for (Scheduler **it = mSchedulers.begin(); it != mSchedulers.end(); it++) {
      if ((*it)->getHandle() == handle && (*it)->isPlay(order)) {
        return true;
      }
    }
    return false;
  }
}

void ScheManager::init() {
  gf::GF_OBJ_HANDLE *handle = mm::mtl::PtrSingleton<Manager>::get()->getObjHandle();
  if (handle != gf::INVALID_HANDLE) {
    push(handle, mm::mtl::PtrSingleton<Manager>::get()->getPlayParam(1));
  }
  gf::GF_OBJ_HANDLE *leader = gf::GfGameParty::getLeader();
  if (leader != gf::INVALID_HANDLE) {
    push(leader, 0);
  }
  flags = 0;
}

void ScheManager::push(gf::GF_OBJ_HANDLE *handle, u32 type) {
  for (Scheduler **it = mSchedulers.begin(); it != mSchedulers.end(); it++) {
    if ((*it)->getHandle() == handle) {
      Scheduler *scheduler = new (mm::mtl::Singleton<MemoryManager>::get().getSysHandle(), nullptr, 0, 4, false) Scheduler(*it, type);
      mSchedulers.push_back(scheduler);
      if (*it != nullptr) {
        delete *it;
        *it = nullptr;
      }
      mSchedulers.erase(it);
      return;
    }
  }
  Scheduler *scheduler = new (mm::mtl::Singleton<MemoryManager>::get().getSysHandle(), nullptr, 0, 4, false) Scheduler(handle, type);
  mSchedulers.push_back(scheduler);
}

bool ScheManager::isExist(gf::GF_OBJ_HANDLE *handle) {
  for (Scheduler **it = mSchedulers.begin(); it != mSchedulers.end(); it++) {
    if ((*it)->getHandle() == handle) {
      return true;
    }
  }
  return false;
}

void ScheManager::play(Scheduler::ORDER order, gf::GF_OBJ_HANDLE *handle) {
  if (handle == gf::INVALID_HANDLE) {
    for (Scheduler **it = mSchedulers.begin(); it != mSchedulers.end(); it++) {
      (*it)->play(order);
    }
  } else {
    for (Scheduler **it = mSchedulers.begin(); it != mSchedulers.end(); it++) {
      if ((*it)->getHandle() == handle) {
        (*it)->play(order);
      }
    }
  }
}

void ScheManager::setUse(Scheduler::USE use, bool isUse, gf::GF_OBJ_HANDLE *handle) {
  for (Scheduler **it = mSchedulers.begin(); it != mSchedulers.end(); it++) {
    if ((*it)->getHandle() == handle) {
      (*it)->setUse(use, isUse);
      return;
    }
  }
}

bool ScheManager::chkUse(Scheduler::USE use, gf::GF_OBJ_HANDLE *handle) {
  for (Scheduler **it = mSchedulers.begin(); it != mSchedulers.end(); it++) {
    if ((*it)->getHandle() == handle) {
      return (*it)->chkUse(use);
    }
  }
  return false;
}

void ScheManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_INIT_BEGIN:
    init();
    play(Scheduler::ORDER_FLD2EVT, gf::INVALID_HANDLE);
    flags |= FLAG_FLD2EVT;
    break;
  case MSG_TYPE_START_SCENE:
    if ((flags & FLAG_EVT2IDLE) == 0) {
      play(Scheduler::ORDER_EVT2IDLE, gf::INVALID_HANDLE);
      flags |= FLAG_EVT2IDLE;
    }
    break;
  case MSG_TYPE_CLEAR:
    if ((flags & FLAG_EVT2FLD) == 0) {
      play(Scheduler::ORDER_EVT2FLD, gf::INVALID_HANDLE);
      flags |= FLAG_EVT2FLD;
    }
    break;
  case MSG_TYPE_UPDATE_POST:
    update();
    break;
  default:
    break;
  }
}

} // namespace event
