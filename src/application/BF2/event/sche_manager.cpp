#include "event/sche_manager.h"

#include <stddef.h>

#include "event/frame_manager.h"
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

ScheManager::ScheManager() : unknown10(0) {}

void ScheManager::create() {}

void ScheManager::destroy() {
  for (size_t i = 0; i < unknown18.size(); i++) {
    if (unknown18[i] != nullptr) {
      delete unknown18[i];
      unknown18[i] = nullptr;
    }
  }
  unknown18.clear();
}

void ScheManager::update() {
  if (mm::mtl::Singleton<FrameManager>::getPtr()->frameInfo().unknown0c > 0.0f) {
    for (Scheduler **it = unknown18.begin(); it != unknown18.end(); it++) {
      (*it)->exec();
    }
  }
  bool isErased;
  do {
    isErased = false;
    for (Scheduler **it = unknown18.begin(); it != unknown18.end(); it++) {
      if ((*it)->isPlay(Scheduler::ORDER_EVT2FLD)) {
        continue;
      }
      if (*it != nullptr) {
        delete *it;
        *it = nullptr;
      }
      unknown18.erase(it);
      isErased = true;
      break;
    }
  } while (isErased);
}

bool ScheManager::isPlay(Scheduler::ORDER order, gf::GF_OBJ_HANDLE *handle) {
  if (handle == gf::INVALID_HANDLE) {
    for (Scheduler **it = unknown18.begin(); it != unknown18.end(); it++) {
      if ((*it)->isPlay(order)) {
        return true;
      }
    }
    return false;
  } else {
    for (Scheduler **it = unknown18.begin(); it != unknown18.end(); it++) {
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
  unknown10 = 0;
}

void ScheManager::push(gf::GF_OBJ_HANDLE *handle, u32 type) {
  for (Scheduler **it = unknown18.begin(); it != unknown18.end(); it++) {
    if ((*it)->getHandle() == handle) {
      Scheduler *scheduler = new (mm::mtl::Singleton<MemoryManager>::get().getSysHandle(), nullptr, 0, 4, false) Scheduler(*it, type);
      unknown18.push_back(scheduler);
      if (*it != nullptr) {
        delete *it;
        *it = nullptr;
      }
      unknown18.erase(it);
      return;
    }
  }
  Scheduler *scheduler = new (mm::mtl::Singleton<MemoryManager>::get().getSysHandle(), nullptr, 0, 4, false) Scheduler(handle, type);
  unknown18.push_back(scheduler);
}

bool ScheManager::isExist(gf::GF_OBJ_HANDLE *handle) {
  for (Scheduler **it = unknown18.begin(); it != unknown18.end(); it++) {
    if ((*it)->getHandle() == handle) {
      return true;
    }
  }
  return false;
}

void ScheManager::play(Scheduler::ORDER order, gf::GF_OBJ_HANDLE *handle) {
  if (handle == gf::INVALID_HANDLE) {
    for (Scheduler **it = unknown18.begin(); it != unknown18.end(); it++) {
      (*it)->play(order);
    }
  } else {
    for (Scheduler **it = unknown18.begin(); it != unknown18.end(); it++) {
      if ((*it)->getHandle() == handle) {
        (*it)->play(order);
      }
    }
  }
}

void ScheManager::setUse(Scheduler::USE use, bool isUse, gf::GF_OBJ_HANDLE *handle) {
  for (Scheduler **it = unknown18.begin(); it != unknown18.end(); it++) {
    if ((*it)->getHandle() == handle) {
      (*it)->setUse(use, isUse);
      return;
    }
  }
}

bool ScheManager::chkUse(Scheduler::USE use, gf::GF_OBJ_HANDLE *handle) {
  for (Scheduler **it = unknown18.begin(); it != unknown18.end(); it++) {
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
    unknown10 |= FLAG_FLD2EVT;
    break;
  case MSG_TYPE_START_SCENE:
    if ((unknown10 & FLAG_EVT2IDLE) == 0) {
      play(Scheduler::ORDER_EVT2IDLE, gf::INVALID_HANDLE);
      unknown10 |= FLAG_EVT2IDLE;
    }
    break;
  case MSG_TYPE_CLEAR:
    if ((unknown10 & FLAG_EVT2FLD) == 0) {
      play(Scheduler::ORDER_EVT2FLD, gf::INVALID_HANDLE);
      unknown10 |= FLAG_EVT2FLD;
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
