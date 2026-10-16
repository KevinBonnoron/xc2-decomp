#include "event/sche_manager.h"

#include "event/memory_manager.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace event {

ScheManager::ScheManager() : flags(0) {}

void ScheManager::create() {}

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

} // namespace event
